#version 300 es
precision highp float;

// Raymarching : pas de maillage, pas de triangles.
// Une fonction de distance, et pour chaque pixel on avance le long d'un rayon
// jusqu'a toucher la surface. Ce fichier s'execute une fois par pixel.

uniform vec2  u_resolution;
uniform float u_time;
uniform int   u_steps;   // branche sur $clicks : le nombre de pas augmente au clic

out vec4 fragColor;

const vec3 ORANGE = vec3(0.918, 0.314, 0.153);
const vec3 CREAM  = vec3(0.929, 0.933, 0.855);

mat2 rot(float a) { return mat2(cos(a), -sin(a), sin(a), cos(a)); }

// La scene : une sphere evidee par une gyroide — une forme qu'aucune main
// ne modeliserait, obtenue en trois lignes de mathematiques — et, dedans,
// un coeur incandescent qui eclaire la coque de l'interieur.

float shell(vec3 p) {
  float sph = length(p) - 1.15;
  float k = 6.0;
  float gyr = dot(sin(p * k), cos(p.zxy * k)) / k;
  return max(sph, abs(gyr) - 0.07);
}

float core(vec3 p) {
  return length(p) - (0.42 + 0.03 * sin(u_time * 2.0));
}

vec3 spin(vec3 p) {
  p.xz *= rot(u_time * 0.25);
  p.yz *= rot(0.3 + 0.35 * sin(u_time * 0.17));
  return p;
}

float map(vec3 p) {
  p = spin(p);
  return min(shell(p), core(p));
}

vec3 normalAt(vec3 p) {
  vec2 e = vec2(0.0015, 0.0);
  return normalize(vec3(
    map(p + e.xyy) - map(p - e.xyy),
    map(p + e.yxy) - map(p - e.yxy),
    map(p + e.yyx) - map(p - e.yyx)
  ));
}

void main() {
  vec2 uv = (gl_FragCoord.xy * 2.0 - u_resolution) / u_resolution.y;

  vec3 ro = vec3(0.0, 0.12 * sin(u_time * 0.4), -3.4);
  vec3 rd = normalize(vec3(uv, 1.75));

  // progression quadratique : les premiers clics montrent un fantome,
  // la forme ne se resout qu'aux derniers
  int maxSteps = clamp(8 + u_steps * u_steps * 8, 8, 120);

  float d = 0.0;
  float nearMiss = 1e3;
  bool hit = false;
  vec3 p = ro;

  for (int i = 0; i < 120; i++) {
    if (i >= maxSteps) break;
    p = ro + rd * d;
    float s = map(p);
    nearMiss = min(nearMiss, s);
    if (s < 0.002) { hit = true; break; }
    d += s * 0.75;          // la gyroide ment un peu sur les distances : on avance prudent
    if (d > 9.0) break;
  }

  vec3 col = vec3(0.0);    // fond noir, raccord avec le layout demo

  if (hit) {
    vec3 q = spin(p);
    vec3 n = normalAt(p);

    if (core(q) < shell(q)) {
      // le coeur : emissif, il n'a pas besoin de lumiere
      float pulse = 0.75 + 0.25 * sin(u_time * 2.0);
      col = ORANGE * 1.5 + vec3(1.0, 0.75, 0.45) * pulse * 0.9;
      col += CREAM * pow(max(dot(n, -rd), 0.0), 3.0) * 0.3;
    } else {
      vec3 l = normalize(vec3(-0.55, 0.75, -0.65));
      float diff = max(dot(n, l), 0.0);
      float rim  = pow(1.0 - max(dot(n, -rd), 0.0), 3.0);
      float spec = pow(max(dot(reflect(-l, n), -rd), 0.0), 48.0);
      // lumiere venue du coeur : les faces internes s'embrasent
      float c = core(q);
      float inner = max(dot(n, normalize(-p)), 0.0) / (1.0 + 2.5 * c * c);

      col  = CREAM * 0.04 + CREAM * diff * 0.3;
      col += ORANGE * inner * 1.7;
      col += CREAM * rim * 0.5;
      col += vec3(1.0) * spec * 0.45;
    }
    // brume de profondeur legere
    col *= exp(-0.06 * max(d - 2.0, 0.0));
  } else {
    // halo : les rayons passes pres de la surface laissent une lueur
    float halo = pow(clamp(1.0 - nearMiss * 1.8, 0.0, 1.0), 5.0);
    col += ORANGE * halo * 0.55;
  }

  // vignette douce
  col *= 1.0 - 0.22 * dot(uv * 0.62, uv * 0.62);

  // gamma
  fragColor = vec4(pow(col, vec3(0.4545)), 1.0);
}

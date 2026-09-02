#version 300 es
precision highp float;

// Survol d'un paysage au soleil couchant, entierement raymarche :
// pas de maillage, pas de textures — un champ de hauteur en bruit fractal,
// un plan d'eau qui reflete le ciel, et de la lumiere.
// Ce fichier s'execute une fois par pixel.

uniform vec2  u_resolution;
uniform float u_time;
uniform int   u_steps;   // present pour compatibilite ShaderCanvas (qualite fixe ici)

out vec4 fragColor;

const vec3  ORANGE  = vec3(0.918, 0.314, 0.153);
const float WATER_Y = 0.25;

float hash(vec2 p) {
  p = fract(p * vec2(123.34, 456.21));
  p += dot(p, p + 45.32);
  return fract(p.x * p.y);
}

float noise(vec2 p) {
  vec2 i = floor(p), f = fract(p);
  vec2 u = f * f * (3.0 - 2.0 * f);
  return mix(mix(hash(i),                hash(i + vec2(1.0, 0.0)), u.x),
             mix(hash(i + vec2(0.0, 1.0)), hash(i + vec2(1.0, 1.0)), u.x), u.y);
}

float fbm(vec2 p, int oct) {
  float v = 0.0, a = 0.5;
  mat2 m = mat2(1.6, 1.2, -1.2, 1.6);
  for (int i = 0; i < 6; i++) {
    if (i >= oct) break;
    v += a * noise(p);
    p = m * p;
    a *= 0.5;
  }
  return v;
}

// Bruit a derivees analytiques (technique iq, « Rainforest ») : la derivee
// sert a attenuer les octaves sur les pentes deja accidentees — l'erosion.
vec3 noised(vec2 p) {
  vec2 i = floor(p), f = fract(p);
  vec2 u = f * f * (3.0 - 2.0 * f);
  vec2 du = 6.0 * f * (1.0 - f);
  float a = hash(i);
  float b = hash(i + vec2(1.0, 0.0));
  float c = hash(i + vec2(0.0, 1.0));
  float d = hash(i + vec2(1.0, 1.0));
  float k1 = b - a, k2 = c - a, k3 = a - b - c + d;
  return vec3(a + k1 * u.x + k2 * u.y + k3 * u.x * u.y,
              du * vec2(k1 + k3 * u.y, k2 + k3 * u.x));
}

// Champ de hauteur : montagnes erodees sur les cotes, vallee inondee au centre.
float terrain(vec2 p, int oct) {
  vec2 q = p * 0.35;
  mat2 m = mat2(1.6, 1.2, -1.2, 1.6);
  float h = 0.0, b = 0.5;
  vec2 d = vec2(0.0);
  for (int i = 0; i < 6; i++) {
    if (i >= oct) break;
    vec3 n = noised(q);
    d += n.yz;
    h += b * n.x / (1.0 + dot(d, d));
    b *= 0.5;
    q = m * q;
  }
  h = h * h * 3.1;
  h *= 0.15 + 0.85 * smoothstep(0.8, 3.5, abs(p.x));
  return h;
}

// Ombres douces (technique iq) : une marche courte vers le soleil,
// seulement pour les pixels qui ont touche le sol.
float softShadow(vec3 ro, vec3 rd) {
  float res = 1.0;
  float t = 0.15;
  for (int i = 0; i < 28; i++) {
    vec3 p = ro + rd * t;
    float h = p.y - terrain(p.xz, 4);
    res = min(res, 6.0 * h / t);
    if (res < 0.015 || p.y > 3.2) break;
    t += clamp(h, 0.08, 0.5);
  }
  return clamp(res, 0.0, 1.0);
}

vec3 skyColor(vec3 rd, vec3 sun) {
  float horiz = pow(1.0 - max(rd.y, 0.0), 5.0);
  vec3 sky = mix(vec3(0.06, 0.10, 0.24), vec3(0.98, 0.40, 0.16), horiz);
  // bande rose juste au-dessus de l'horizon
  sky += vec3(0.55, 0.18, 0.25) * pow(1.0 - abs(rd.y - 0.10), 14.0) * 0.55;
  float s = max(dot(rd, sun), 0.0);
  sky += ORANGE * pow(s, 6.0) * 0.45;
  sky += vec3(1.0, 0.72, 0.45) * pow(s, 48.0) * 0.75;
  sky += vec3(1.0, 0.92, 0.78) * smoothstep(0.9972, 0.9994, s) * 3.2;   // le disque
  // cirrus etires, teintes par le soleil
  if (rd.y > 0.02) {
    vec2 cp = vec2(rd.x / (rd.y + 0.18), 1.0 / (rd.y + 0.12));
    float cl = fbm(cp * vec2(0.6, 0.35) + vec2(u_time * 0.004, 0.0), 4);
    float cm = smoothstep(0.45, 0.75, cl) * smoothstep(0.55, 0.12, rd.y);
    sky = mix(sky, vec3(1.0, 0.55, 0.35) * (0.5 + 0.5 * s), cm * 0.45);
  }
  return sky;
}

float sdSeg(vec2 p, vec2 a, vec2 b) {
  vec2 pa = p - a, ba = b - a;
  float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
  return length(pa - ba * h);
}

// L'oiseau : une silhouette, une trajectoire trigonometrique, et des
// battements d'ailes par bouffees entre deux planes.
float bird(vec2 uv, float t) {
  vec2 pos = vec2(0.55 * sin(t * 0.10) + 0.18 * sin(t * 0.23),
                  0.32 + 0.09 * sin(t * 0.17 + 1.7) + 0.04 * sin(t * 0.31));
  float burst = smoothstep(0.15, 0.55, 0.5 + 0.5 * sin(t * 0.7));
  float flap = mix(0.18, sin(t * 11.0) * 0.75, burst);
  pos.y += 0.012 * sin(t * 11.0 - 1.2) * burst;

  vec2 q = (uv - pos) / 0.07;
  q.x = abs(q.x);                       // deux ailes symetriques
  float d = min(
    sdSeg(q, vec2(0.0, 0.0), vec2(0.5, flap * 0.4)),
    sdSeg(q, vec2(0.5, flap * 0.4), vec2(1.0, flap))
  );
  float th = 0.17 - 0.08 * min(q.x, 1.0);   // ailes effilees vers la pointe
  return smoothstep(th, th - 0.05, d);
}

bool march(vec3 ro, vec3 rd, out float tHit) {
  float t = 0.1, ph = 0.0, pt = 0.1;
  for (int i = 0; i < 130; i++) {
    vec3 p = ro + rd * t;
    float h = p.y - terrain(p.xz, 4);
    if (h < 0.002 * t) {
      // interpolation entre les deux derniers pas : adoucit les silhouettes
      tHit = mix(pt, t, clamp(ph / (ph - h + 1e-6), 0.0, 1.0));
      return true;
    }
    ph = h; pt = t;
    t += 0.35 * h + 0.004 * t;
    if (t > 60.0) return false;
  }
  return false;
}

vec3 terrainNormal(vec3 p, float t) {
  float e = 0.001 * t + 0.001;
  return normalize(vec3(
    terrain(p.xz - vec2(e, 0.0), 6) - terrain(p.xz + vec2(e, 0.0), 6),
    2.0 * e,
    terrain(p.xz - vec2(0.0, e), 6) - terrain(p.xz + vec2(0.0, e), 6)
  ));
}

vec3 shadeTerrain(vec3 p, vec3 n, vec3 rd, vec3 sun, float t, float sh) {
  float diff = max(dot(n, sun), 0.0) * sh;
  vec3 rock  = vec3(0.27, 0.17, 0.12);
  vec3 grass = vec3(0.13, 0.20, 0.08);
  float flat_ = smoothstep(0.55, 0.85, n.y);
  float low   = smoothstep(1.3, 0.35, p.y);
  vec3 alb = mix(rock, grass, flat_ * low);
  // l'herbe frissonne pres de la camera
  alb *= 0.88 + 0.24 * noise(p.xz * 24.0 + vec2(0.0, u_time * 1.6))
               * flat_ * smoothstep(9.0, 2.0, t);
  // ombres froides (bleu du ciel), lumiere chaude (soleil bas)
  vec3 col = alb * (vec3(0.16, 0.20, 0.38) * 0.5
                    + vec3(1.0, 0.55, 0.28) * diff * 2.2);
  float rim = pow(1.0 - max(dot(n, -rd), 0.0), 3.0);
  col += ORANGE * rim * (0.2 + diff * 0.4);
  return col;
}

void main() {
  vec2 uv = (gl_FragCoord.xy * 2.0 - u_resolution) / u_resolution.y;

  vec3 sun = normalize(vec3(0.25, 0.14, 1.0));

  // la camera avance ; leger roulis, comme portee par l'air
  float ct = u_time * 1.4;
  float roll = 0.03 * sin(u_time * 0.5);
  uv = mat2(cos(roll), -sin(roll), sin(roll), cos(roll)) * uv;

  vec3 ro = vec3(0.35 * sin(u_time * 0.21), 0.0, ct);
  ro.y = max(terrain(ro.xz, 4), WATER_Y) + 0.85 + 0.06 * sin(u_time * 0.7);
  vec3 rd = normalize(vec3(uv.x, uv.y - 0.14, 1.55));

  float tT;
  bool hitT = march(ro, rd, tT);
  float tW = (rd.y < -0.0001) ? (WATER_Y - ro.y) / rd.y : 1e4;

  vec3 col;
  float tFog;

  if (hitT && tT < tW) {
    // le sol
    vec3 p = ro + rd * tT;
    vec3 n = terrainNormal(p, tT);
    float sh = softShadow(p + n * 0.05, sun);
    col = shadeTerrain(p, n, rd, sun, tT, sh);
    tFog = tT;
  } else if (tW < 1e3) {
    // l'eau : le ciel et le soleil s'y refletent
    vec3 p = ro + rd * tW;
    vec2 rip = vec2(noise(p.xz * 3.5 + u_time * 0.8),
                    noise(p.xz * 3.5 - u_time * 0.6)) - 0.5;
    vec3 n = normalize(vec3(rip.x * 0.25, 1.0, rip.y * 0.25));
    vec3 rr = reflect(rd, n);
    rr.y = abs(rr.y);
    vec3 refl = skyColor(rr, sun) * 0.8;
    float fres = pow(1.0 - max(dot(n, -rd), 0.0), 5.0);
    col = mix(vec3(0.02, 0.05, 0.06), refl, 0.08 + 0.92 * fres);
    tFog = tW;
  } else {
    col = skyColor(rd, sun);
    tFog = 1e4;
  }

  // brume atmospherique : le lointain fond dans le ciel
  if (tFog < 1e3) {
    float fog = 1.0 - exp(-tFog * 0.024);
    col = mix(col, skyColor(rd, sun) * 0.85, fog);
  }

  // l'oiseau, en silhouette contre le ciel
  float b = bird(uv, u_time);
  col = mix(col, vec3(0.03, 0.02, 0.03), b * 0.9);

  // etalonnage : un peu de saturation, hautes lumieres chaudes, ombres froides
  float luma = dot(col, vec3(0.299, 0.587, 0.114));
  col = mix(vec3(luma), col, 1.15);
  col += ORANGE * 0.05 * smoothstep(0.45, 1.2, luma);
  col += vec3(0.01, 0.03, 0.07) * smoothstep(0.35, 0.0, luma);

  // vignette douce
  col *= 1.0 - 0.25 * dot(uv * 0.6, uv * 0.6);

  // gamma
  fragColor = vec4(pow(max(col, 0.0), vec3(0.4545)), 1.0);
}

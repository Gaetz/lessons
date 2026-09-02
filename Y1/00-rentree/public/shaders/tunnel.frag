#version 300 es
precision highp float;

// Tunnel fractal par diatribes — https://www.shadertoy.com/view/3ccyD7
// Licence Shadertoy par defaut (CC BY-NC-SA 3.0), attribution affichee sur la diapo.
// Adaptation ShaderCanvas : GLSL ES 3.0, uniforms u_*, initialisations explicites
// (l'ES ne met pas les variables a zero), constructeur vec3 explicite.

uniform vec2  u_resolution;
uniform float u_time;
uniform int   u_steps;   // compat ShaderCanvas (non utilise ici)

out vec4 fragColor;

#define T (u_time*6.)
#define P(z) vec3(cos((z) *  .05) * 16., \
                 cos((z) *  .1) * 8., (z))
#define R(a) mat2(cos(a+vec4(0,33,11,0)))
#define N normalize

float light = 0.;

float orb(vec3 p) {
    vec3 q = P(p.z);
    return length(p - vec3(
            q.x+(sin(p.z*.4) * .4),
            q.y+sin(sin(p.z*.3)+T) * .5,
           5.+T+tan(cos(T*.2)*.5)*3.2));
}

#define MENGERLAYER(scale, minmax, hole)\
    s /= (scale), \
    p = abs(fract(q/s)*s - s*.5), \
    d = minmax(d, min(max(p.x, p.y), \
                  min(max(p.y, p.z), \
                  max(p.x, p.z))) - s/(hole))
float fractal(vec3 q){
    vec3 p;

    float s = 4., d = 9e9;
    MENGERLAYER(1., min, 6.);
    MENGERLAYER(4., max, 3.5);
    return d;
}

float map(vec3 p) {
    float s, o;
    vec3 q = p;
    p.xy -= P(p.z).xy;
    p.y += .1;
    s = max(1. - abs(p.x),1. - abs(p.y));
    s = min(s, fractal(p));
    s = min(s, o = orb(q) - .01);
    light += 1./max(o,.001);
    return min(o, max(-q.y-5.35, s));
}

void main() {
    vec2 u = gl_FragCoord.xy;
    float s = 0., d = 0., i = 0.;
    vec4  o = vec4(0.);
    vec3  r = vec3(u_resolution, 1.),
          p = P(T), ro = p,
          Z = N( P(T+3.) - p),
          X = N(vec3(Z.z, 0., -Z.x)),
          D = vec3(R(sin(T*.2)*.3)*(u-r.xy/2.)/r.y, 1.)
              * mat3(-X, cross(X, Z), Z);
    for(; i++ < 5e1 && d < 5e1;
        o += vec4(2,1e1,4,0)/s
          + 6e1*vec4(2,1,8,0)*light / d)
        p = ro + D * d,
        d += s = .01+.65*abs(map(p));
    fragColor = tanh(o*o/4e8);
    fragColor.a = 1.0;
}

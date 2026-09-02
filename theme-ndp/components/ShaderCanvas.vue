<script setup lang="ts">
/**
 * Fragment shader plein cadre, pilotable au clic Slidev.
 *
 *   <ShaderCanvas :frag="src" :steps="$clicks" />
 *   <ShaderCanvas src="/shaders/raymarch.frag" />   (fichier dans public/)
 *
 * Uniforms fournis : u_time (s), u_resolution (px), u_steps (int), u_mouse.
 * La boucle rAF est coupee des que la diapo n'est plus active : sans ca,
 * douze canvas tournent en parallele et la machine de la salle s'effondre.
 */
import { ref, shallowRef, watch, watchEffect, onBeforeUnmount, onMounted } from 'vue'
import { useIsSlideActive } from '@slidev/client'

const props = withDefaults(defineProps<{
  frag?: string
  src?: string
  steps?: number
  height?: string
  paused?: boolean
  /** plafond de devicePixelRatio : baisser a 1 pour les shaders lourds en plein cadre */
  dpr?: number
}>(), { steps: 0, height: '340px', paused: false, dpr: 2 })

const canvas = shallowRef<HTMLCanvasElement | null>(null)
const error = ref('')
const active = useIsSlideActive()

let gl: WebGL2RenderingContext | null = null
let program: WebGLProgram | null = null
let raf = 0
let start = 0
let uni: Record<string, WebGLUniformLocation | null> = {}
const mouse = { x: 0, y: 0 }

const VERT = `#version 300 es
in vec2 a_pos;
void main() { gl_Position = vec4(a_pos, 0.0, 1.0); }`

const FALLBACK = `#version 300 es
precision highp float;
uniform vec2  u_resolution;
uniform float u_time;
uniform int   u_steps;
out vec4 fragColor;
void main() {
  vec2 uv = (gl_FragCoord.xy * 2.0 - u_resolution) / u_resolution.y;
  float d = length(uv) - 0.55 - 0.05 * sin(u_time * 1.5);
  float ring = smoothstep(0.012, 0.0, abs(d));
  float grid = float(u_steps) * 0.12;
  vec3 col = mix(vec3(0.93, 0.31, 0.15), vec3(0.93, 0.93, 0.85), ring);
  col *= 0.75 + grid;
  fragColor = vec4(col, 1.0);
}`

function compile(g: WebGL2RenderingContext, type: number, source: string) {
  const sh = g.createShader(type)!
  g.shaderSource(sh, source)
  g.compileShader(sh)
  if (!g.getShaderParameter(sh, g.COMPILE_STATUS))
    throw new Error(g.getShaderInfoLog(sh) || 'compilation shader')
  return sh
}

async function build() {
  error.value = ''
  const el = canvas.value
  if (!el) return

  let source = props.frag
  if (!source && props.src) {
    try { source = await (await fetch(props.src)).text() }
    catch { error.value = `shader introuvable : ${props.src}` }
  }
  source ||= FALLBACK

  gl = el.getContext('webgl2', { antialias: true, powerPreference: 'high-performance' })
  if (!gl) { error.value = 'WebGL2 indisponible sur cette machine'; return }

  try {
    const p = gl.createProgram()!
    gl.attachShader(p, compile(gl, gl.VERTEX_SHADER, VERT))
    gl.attachShader(p, compile(gl, gl.FRAGMENT_SHADER, source))
    gl.linkProgram(p)
    if (!gl.getProgramParameter(p, gl.LINK_STATUS))
      throw new Error(gl.getProgramInfoLog(p) || 'link')
    program = p
  } catch (e: any) { error.value = String(e.message).slice(0, 400); return }

  gl.useProgram(program)
  const buf = gl.createBuffer()
  gl.bindBuffer(gl.ARRAY_BUFFER, buf)
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array([-1, -1, 3, -1, -1, 3]), gl.STATIC_DRAW)
  const loc = gl.getAttribLocation(program, 'a_pos')
  gl.enableVertexAttribArray(loc)
  gl.vertexAttribPointer(loc, 2, gl.FLOAT, false, 0, 0)

  uni = {
    time: gl.getUniformLocation(program, 'u_time'),
    res: gl.getUniformLocation(program, 'u_resolution'),
    steps: gl.getUniformLocation(program, 'u_steps'),
    mouse: gl.getUniformLocation(program, 'u_mouse'),
  }
  start = performance.now()
}

function resize() {
  const el = canvas.value
  if (!el || !gl) return
  const dpr = Math.min(window.devicePixelRatio || 1, props.dpr)
  const w = Math.round(el.clientWidth * dpr)
  const h = Math.round(el.clientHeight * dpr)
  if (el.width !== w || el.height !== h) { el.width = w; el.height = h }
  gl.viewport(0, 0, el.width, el.height)
}

function frame() {
  if (!gl || !program) return
  resize()
  gl.uniform1f(uni.time!, (performance.now() - start) / 1000)
  gl.uniform2f(uni.res!, canvas.value!.width, canvas.value!.height)
  gl.uniform1i(uni.steps!, props.steps)
  gl.uniform2f(uni.mouse!, mouse.x, mouse.y)
  gl.drawArrays(gl.TRIANGLES, 0, 3)
  raf = requestAnimationFrame(frame)
}

function stop() { if (raf) { cancelAnimationFrame(raf); raf = 0 } }

function onMove(e: MouseEvent) {
  const r = (e.target as HTMLElement).getBoundingClientRect()
  mouse.x = e.clientX - r.left
  mouse.y = r.height - (e.clientY - r.top)
}

// Perte de contexte WebGL : le navigateur limite le nombre de contextes (~16)
// et tue silencieusement les plus anciens (canvas noir). Frequent en dev, ou
// chaque hot-reload remonte les canvas. On previent le defaut pour que
// `webglcontextrestored` se declenche, et on reconstruit a ce moment-la.
function onContextLost(e: Event) { e.preventDefault(); stop() }
async function onContextRestored() { gl = null; await build(); if (active.value) frame() }

onMounted(async () => {
  canvas.value?.addEventListener('webglcontextlost', onContextLost)
  canvas.value?.addEventListener('webglcontextrestored', onContextRestored)
  await build()
  if (active.value) frame()
})
watchEffect(() => {
  // Lire les valeurs reactives AVANT tout return : si l'effet sort sur
  // `!gl` sans les avoir lues (diapo pre-montee par Slidev, build async
  // pas fini), Vue ne le reabonne a rien et il ne se relancera jamais.
  const on = active.value && !props.paused
  if (!gl) return
  if (on) {
    if (gl.isContextLost()) return   // on attend webglcontextrestored
    if (!raf) frame()
  } else stop()
})
watch(() => [props.frag, props.src], async () => { stop(); await build(); if (active.value) frame() })
onBeforeUnmount(() => {
  stop()
  canvas.value?.removeEventListener('webglcontextlost', onContextLost)
  canvas.value?.removeEventListener('webglcontextrestored', onContextRestored)
  // libere le contexte immediatement : sans ca, les remontages successifs
  // (hot-reload, navigation) epuisent le quota de contextes du navigateur
  gl?.getExtension('WEBGL_lose_context')?.loseContext()
  gl = null
})
</script>

<template>
  <div class="shader-wrap" :style="{ height }">
    <canvas ref="canvas" @mousemove="onMove" />
    <pre v-if="error" class="shader-err">{{ error }}</pre>
  </div>
</template>

<style scoped>
.shader-wrap { position: relative; width: 100%; overflow: hidden; background: #000; }
canvas { width: 100%; height: 100%; display: block; }
.shader-err {
  position: absolute; inset: 0; margin: 0; padding: .8rem;
  background: rgba(0,0,0,.88); color: #EA5027;
  font: 500 .68rem/1.4 'JetBrains Mono', monospace; white-space: pre-wrap; overflow: auto;
}
</style>

<script setup lang="ts">
/**
 * Image cliquable : un clic l'ouvre en plein ecran, un clic la referme,
 * avec une animation FLIP — l'image part de sa vignette et y revient.
 * Le @click.stop empeche Slidev d'avancer d'un clic de presentation.
 * Le Teleport vers body echappe au scale() du canvas Slidev.
 *
 *   <ZoomImage src="/x.jpg" alt="..." class="h-44 w-full object-cover" />
 */
import { ref, nextTick } from 'vue'

defineOptions({ inheritAttrs: false })
defineProps<{ src: string; alt?: string }>()

const open = ref(false)
const closing = ref(false)
const thumbEl = ref<HTMLImageElement>()
const bigEl = ref<HTMLImageElement>()
const DUR = 300

// transformation qui ramene l'image plein ecran sur sa vignette
function invert(): string {
  const t = thumbEl.value!.getBoundingClientRect()
  const b = bigEl.value!.getBoundingClientRect()
  const dx = t.left + t.width / 2 - (b.left + b.width / 2)
  const dy = t.top + t.height / 2 - (b.top + b.height / 2)
  return `translate(${dx}px, ${dy}px) scale(${t.width / b.width}, ${t.height / b.height})`
}

async function openZoom() {
  if (open.value) return
  open.value = true
  closing.value = false
  await nextTick()
  const img = bigEl.value
  if (!img) return
  img.style.transition = 'none'
  img.style.transform = invert()
  void img.getBoundingClientRect()   // force le reflow avant de lancer la transition
  img.style.transition = `transform ${DUR}ms cubic-bezier(.2, .8, .2, 1)`
  img.style.transform = 'none'
}

function closeZoom() {
  const img = bigEl.value
  if (!img || closing.value) return
  closing.value = true
  img.style.transform = invert()
  window.setTimeout(() => { open.value = false; closing.value = false }, DUR)
}
</script>

<template>
  <img ref="thumbEl" :src="src" :alt="alt" v-bind="$attrs" class="cursor-zoom-in" @click.stop="openZoom" />
  <Teleport to="body">
    <div v-if="open" class="ndp-zoom-overlay" :class="{ closing }" @click.stop="closeZoom">
      <img ref="bigEl" :src="src" :alt="alt" />
    </div>
  </Teleport>
</template>

<style scoped>
.ndp-zoom-overlay {
  position: fixed; inset: 0; z-index: 200;
  background: rgba(0, 0, 0, .92);
  display: flex; align-items: center; justify-content: center;
  cursor: zoom-out;
  animation: ndp-zoom-fade .3s ease;
  transition: background .3s ease;
}
.ndp-zoom-overlay.closing { background: rgba(0, 0, 0, 0); }
@keyframes ndp-zoom-fade { from { background: rgba(0, 0, 0, 0); } }
.ndp-zoom-overlay img { max-width: 92vw; max-height: 92vh; object-fit: contain; }
</style>

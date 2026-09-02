<script setup lang="ts">
/**
 * Budget de frame : 16,6 ms a 60 fps, decoupe en postes.
 * Revele poste par poste si on branche :steps="$clicks".
 *
 *   <FrameBudget :steps="$clicks" :fps="60" />
 */
import { computed } from 'vue'

const props = withDefaults(defineProps<{
  fps?: number
  steps?: number
  tasks?: { label: string; ms: number }[]
}>(), {
  fps: 60,
  steps: 99,
  tasks: () => ([
    { label: 'Input & logique de jeu', ms: 1.2 },
    { label: 'Physique', ms: 2.4 },
    { label: 'Animation & skinning', ms: 1.8 },
    { label: 'Culling & préparation des draw calls', ms: 2.1 },
    { label: 'Rendu GPU (geometry, lighting, post)', ms: 7.4 },
    { label: 'Audio, réseau, streaming', ms: 0.9 },
  ]),
})

const budget = computed(() => 1000 / props.fps)
const shown = computed(() => props.tasks.slice(0, Math.max(0, props.steps)))
const used = computed(() => shown.value.reduce((s, t) => s + t.ms, 0))
const left = computed(() => budget.value - used.value)
const pct = (ms: number) => (ms / budget.value) * 100
</script>

<template>
  <div class="fb">
    <div class="fb-head">
      <span class="fb-target">{{ fps }} fps</span>
      <span class="fb-eq">=</span>
      <span class="fb-budget">{{ budget.toFixed(1) }} ms</span>
      <span class="fb-note">par image, pour tout faire</span>
    </div>

    <div class="fb-bar">
      <div
        v-for="(t, i) in shown" :key="t.label"
        class="fb-seg" :style="{ width: pct(t.ms) + '%', opacity: 0.55 + i * 0.075 }"
        :title="`${t.label} — ${t.ms} ms`"
      />
      <div class="fb-free" :style="{ width: Math.max(0, pct(left)) + '%' }" />
    </div>

    <ul class="fb-list">
      <li v-for="t in shown" :key="t.label">
        <span class="fb-ms">{{ t.ms.toFixed(1) }}</span>
        <span class="fb-label">{{ t.label }}</span>
      </li>
    </ul>

    <div class="fb-foot" :class="{ over: left < 0 }">
      <template v-if="left >= 0">Il reste <b>{{ left.toFixed(1) }} ms</b>. Puis on recommence.</template>
      <template v-else>Dépassement de <b>{{ (-left).toFixed(1) }} ms</b> — l'image saute.</template>
    </div>
  </div>
</template>

<style scoped>
.fb { font-family: 'Raleway', sans-serif; }
.fb-head { display: flex; align-items: baseline; gap: .5rem; margin-bottom: .7rem; }
.fb-target { font-weight: 900; font-size: 1.6rem; }
.fb-eq { color: var(--ndp-grey); }
.fb-budget { font-weight: 900; font-size: 1.6rem; color: var(--ndp-orange); }
.fb-note { font-size: .8rem; color: var(--ndp-grey); }

.fb-bar { display: flex; height: 2rem; border: 1px solid var(--ndp-ink); background: #fff; }
.fb-seg { background: var(--ndp-orange); border-right: 1px solid #fff; transition: width .35s ease; }
.fb-free { background: repeating-linear-gradient(45deg, #fff 0 5px, #eee 5px 10px); transition: width .35s ease; }

.fb-list { list-style: none; margin: .8rem 0 0; padding: 0; font-size: .78rem; }
.fb-list li { display: flex; gap: .7rem; margin: .18em 0; }
.fb-ms { font-family: 'JetBrains Mono', monospace; font-weight: 700; color: var(--ndp-orange); min-width: 2.6rem; text-align: right; }

.fb-foot { margin-top: .9rem; font-size: .9rem; }
.fb-foot.over { color: var(--ndp-orange); font-weight: 800; }
</style>

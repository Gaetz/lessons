<script setup lang="ts">
// Plein cadre noir pour une démo qui doit occuper tout l'écran.
// Le slot par défaut reçoit le visuel, le slot `caption` la phrase du bas.
defineProps<{ breadcrumb?: string }>()
</script>

<template>
  <div class="slidev-layout ndp-dark ndp-demo">
    <Breadcrumb :text="breadcrumb" />
    <div class="ndp-demo-stage"><slot /></div>
    <div class="ndp-demo-caption"><slot name="caption" /></div>
  </div>
</template>

<style scoped>
.ndp-demo { padding: 0; display: flex; flex-direction: column; }
.ndp-demo-stage { flex: 1; min-height: 0; display: flex; align-items: stretch; justify-content: center; }
.ndp-demo-stage :deep(> *) { width: 100%; height: 100%; }
.ndp-demo-caption { padding: 1.1rem 3rem 1.5rem; }
.ndp-demo-caption :deep(p),
.ndp-demo-caption :deep(h2) {
  margin: 0; color: var(--ndp-cream); font-weight: 800; font-size: 1.5rem; line-height: 1.15;
}
.ndp-demo-caption :deep(em) { color: var(--ndp-orange); font-style: normal; }
</style>

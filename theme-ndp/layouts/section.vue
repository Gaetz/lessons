<script setup lang="ts">
defineProps<{ breadcrumb?: string }>()
</script>

<template>
  <div class="slidev-layout ndp-dark ndp-section">
    <Breadcrumb :text="breadcrumb" />
    <div class="ndp-section-body"><slot /></div>
    <div class="ndp-rule" />
    <BrandLogos place="bottom" dark />
  </div>
</template>

<style scoped>
.ndp-section { display: flex; align-items: flex-end; }
.ndp-section-body { padding-bottom: 1.2rem; }
.ndp-section-body :deep(h1) { font-weight: 400; font-size: 3rem; line-height: 1.08; }
.ndp-section-body :deep(p) { color: var(--ndp-orange); font-weight: 700; margin-top: .5rem; }
</style>

<script setup lang="ts">
defineProps<{ breadcrumb?: string }>()
</script>

<template>
  <div class="slidev-layout ndp-content">
    <Breadcrumb :text="breadcrumb" />
    <BrandLogos place="top" />
    <div class="ndp-split">
      <div class="ndp-split-l"><slot /></div>
      <div class="ndp-split-r"><slot name="right" /></div>
    </div>
    <div class="ndp-rule" />
    <BrandLogos place="bottom" />
  </div>
</template>

<style scoped>
.ndp-content { padding-top: 2.4rem; }
.ndp-split { display: grid; grid-template-columns: 1fr 1fr; gap: 2rem; height: 100%; }
.ndp-split-r { display: flex; align-items: center; justify-content: center; }
</style>

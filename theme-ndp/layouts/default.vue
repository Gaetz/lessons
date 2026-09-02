<script setup lang="ts">
defineProps<{ breadcrumb?: string }>()
</script>

<template>
  <div class="slidev-layout ndp-content">
    <Breadcrumb :text="breadcrumb" />
    <BrandLogos place="top" />
    <div class="ndp-content-body"><slot /></div>
    <div class="ndp-rule" />
    <BrandLogos place="bottom" />
  </div>
</template>

<style scoped>
.ndp-content { padding-top: 2.4rem; }
.ndp-content-body { padding-right: 6rem; }
</style>

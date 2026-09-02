<script setup lang="ts">
defineProps<{ text?: string }>()
</script>

<template>
  <div class="ndp-breadcrumb" v-if="text">{{ text }}</div>
</template>

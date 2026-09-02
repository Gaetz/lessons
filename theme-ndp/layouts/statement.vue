<template>
  <div class="slidev-layout ndp-brand ndp-statement">
    <div><slot /></div>
  </div>
</template>

<style scoped>
.ndp-statement { display: flex; align-items: center; justify-content: center; text-align: center; }
.ndp-statement :deep(h1) { color: #fff; font-size: 2.9rem; max-width: 22ch; }
.ndp-statement :deep(p) { color: #000; font-weight: 700; font-size: 1.1rem; margin-top: .8rem; }
</style>

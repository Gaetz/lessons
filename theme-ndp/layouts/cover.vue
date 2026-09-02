<script setup lang="ts">
import artfxLockup from '../assets/artfx-lockup.png'
defineProps<{ subtitle?: string; kicker?: string }>()
</script>

<template>
  <div class="slidev-layout ndp-brand ndp-cover">
    <div class="ndp-cover-head">
      <div class="ndp-cover-school">
        NOTRE-DAME PROVIDENCE<br />
        <span>Collège &mdash; Lycée</span>
      </div>
    </div>

    <div class="ndp-cover-body"><slot /></div>

    <!-- Bandeau ARTFX sur la tranche droite, comme sur le deck institutionnel :
         le lockup [ARTFX | sceau | SCHOOLS OF DIGITAL ARTS] pivoté d'un quart de tour,
         ARTFX en bas, lecture de bas en haut. -->
    <div class="ndp-cover-artfx">
      <img :src="artfxLockup" alt="ARTFX — Schools of Digital Arts" />
    </div>
  </div>
</template>

<style scoped>
.ndp-cover { display: flex; flex-direction: column; justify-content: space-between; padding: 2.4rem 3rem; }

.ndp-cover-school { text-align: right; font-weight: 800; font-size: 1.35rem; letter-spacing: .01em; color: #000; margin-right: 6.5rem; }
.ndp-cover-school span { font-weight: 500; font-size: 1rem; }

.ndp-cover-body { padding-right: 7rem; }
.ndp-cover-body :deep(h1) { color: #fff; font-size: 3.1rem; margin-bottom: .2rem; }
.ndp-cover-body :deep(h2) { color: #000; font-weight: 800; font-size: 2.5rem; line-height: 1.06; }
.ndp-cover-body :deep(p)  { color: #fff; font-size: .8rem; max-width: 26rem; margin-top: 1rem; }

.ndp-cover-artfx {
  position: absolute; top: 0; bottom: 0; right: 1.2rem;
  width: 4.6rem;
  display: flex; align-items: center; justify-content: center;
  pointer-events: none;
}
.ndp-cover-artfx img {
  width: 29rem; max-width: none; height: auto;
  transform: rotate(-90deg);
  filter: invert(1);
}
</style>

<script setup lang="ts">
// Coin haut-droit : sceau ARTFX + logo Notre-Dame Providence
// Coin bas-gauche : lockup ARTFX + NDP, comme dans le deck institutionnel
import artfxSeal from '../assets/artfx-seal.png'
import artfxStack from '../assets/artfx-stack.png'
import ndp from '../assets/ndp.png'

withDefaults(defineProps<{ place?: 'top' | 'bottom'; dark?: boolean }>(), {
  place: 'bottom', dark: false,
})
</script>

<template>
  <div v-if="place === 'top'" class="ndp-logos" style="top: 1.1rem; right: 1.4rem;">
    <img :src="artfxSeal" alt="ARTFX" style="height: 2.1rem" :style="dark ? 'filter: invert(1)' : ''" />
    <img :src="ndp" alt="Notre-Dame Providence" style="height: 1.9rem" />
  </div>
  <!-- centre verticalement entre le filet (a 2.1rem du bas) et le bord : (2.1 - 1.35) / 2 -->
  <div v-else class="ndp-logos" style="bottom: .375rem; left: 3rem;">
    <img :src="artfxStack" alt="ARTFX" style="height: 1.35rem" :style="dark ? 'filter: invert(1)' : ''" />
    <img :src="ndp" alt="Notre-Dame Providence" style="height: 1.35rem" />
  </div>
</template>

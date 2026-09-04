---
layout: section
breadcrumb: Le module
---

# Apprendre le C++ en fabriquant des images

Manipulation d'image et de couleur avec openFrameworks

<!--
Le contrat du module : chaque notion de C++ est apprise parce qu'une image
en a besoin, jamais pour elle-même. À la fin : un projet de peinture
générative qui combine tout.
-->

---
layout: default
breadcrumb: Le module
---

# Ce qu'on va fabriquer

<div class="mt-6 grid grid-cols-3 gap-6" style="margin-right:-6rem">

<div v-click="0">
<ZoomImage src="/ressources/cours/img/08-trainee.png" alt="Traînée de cercles colorés" class="h-44 w-full object-cover" />
<p class="mt-1 text-xs op-60 text-center">des animations</p>
</div>

<div v-click>
<ZoomImage src="/ressources/cours/img/11-filtres.png" alt="Filtres d'image" class="h-44 w-full object-cover" />
<p class="mt-1 text-xs op-60 text-center">des filtres d'image</p>
</div>

<div v-click>
<ZoomImage src="/ressources/cours/img/18-peinture.png" alt="Peinture par particules" class="h-44 w-full object-cover" />
<p class="mt-1 text-xs op-60 text-center">une peinture générative</p>
</div>

</div>

<div v-click class="mt-6 text-base">
Tout en <b>C++</b>, avec <b>openFrameworks</b> — le langage et le genre d'outils
des moteurs de jeu et des logiciels de VFX.
</div>

<!--
Cliquer pour agrandir les images. Montrer que la progression va du cercle qui
suit la souris jusqu'à la peinture générative : tout ce qu'il y a entre les
deux, c'est ce module.
-->

---
layout: default
breadcrumb: Le module
---

# La carte du cours

<div class="mt-6 grid grid-cols-2 gap-x-10 gap-y-2 text-base">

<v-clicks>

- **1 — Les bases** <span class="op-60 text-sm">dessiner, variables, boucles, listes (cours 00-05)</span>
- **2 — Le mouvement** <span class="op-60 text-sm">animation, traînées (06-08)</span>
- **3 — La couleur** <span class="op-60 text-sm">RGB, HSB, la couleur au cinéma et dans le jeu (09, 09a)</span>
- **4 — L'image et ses pixels** <span class="op-60 text-sm">lire, écrire, filtrer (10, 11)</span>
- **5 — La géométrie** <span class="op-60 text-sm">distance, trigonométrie, transformations (12-16)</span>
- **6 — La convolution** <span class="op-60 text-sm">un pixel et ses huit voisins (17)</span>
- **7 — La couleur avancée** <span class="op-60 text-sm">gamma, HDR, LUT, OKLab, dithering… (11a-11g)</span>
- **8 — Le projet final** <span class="op-60 text-sm">peinture par particules (18)</span>

</v-clicks>

</div>

<p class="ndp-credit">Sommaire complet : <a href="/ressources/INDEX.md" download>INDEX.md</a> · <a href="/ressources/cours/README.md" download>cours/README.md</a></p>

<!--
Huit blocs, dix-neuf cours plus le bloc couleur avancée. Ne pas dérouler le
détail : donner le sentiment d'un chemin. La couleur avancée (numérotée 11a-11g
dans les documents) vient APRÈS la géométrie et la convolution : elle utilise
la distance (12), les gros pixels (14), le polaire (16) et l'indice y·w+x (17).
C'est le bloc le plus « métier » — la couleur telle que la manipulent les
studios. Le 18 est le projet qui synthétise tout.
-->

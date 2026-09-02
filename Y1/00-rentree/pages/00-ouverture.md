---
layout: default
breadcrumb: Ouverture
---

# Notre-Dame Providence

<div class="mt-2 flex justify-center" style="margin-right:-6rem">
<iframe
  class="w-180 aspect-video"
  src="https://www.youtube.com/embed/Mfy50qYgGMY"
  title="Notre-Dame Providence"
  allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
  allowfullscreen
/>
</div>

<!--
La vidéo porte la présentation de l'établissement. Lancer, laisser jouer,
puis une ou deux phrases de ta main sur le projet de l'établissement et
pourquoi NDP a monté CETTE formation — c'est ça qui les concerne.
PLAN B : l'embed YouTube suppose le réseau de la salle. Prévoir la vidéo
téléchargée en repli (public/heavy/, via assets.json).
-->

---
layout: default
breadcrumb: Ouverture
---

# ARTFX

<div class="mt-2 flex justify-center" style="margin-right:-6rem">
<iframe
  class="w-180 aspect-video"
  src="https://www.youtube.com/embed/VBuz3azkzDQ"
  title="ARTFX"
  allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
  allowfullscreen
/>
</div>

<!--
Beaucoup ne connaissent ARTFX que de nom, ou pas du tout. Laisser la vidéo
parler, puis dire à l'oral ce qu'ARTFX apporte à la formation : les workshops,
les intervenants, l'année 3, le demoreel — et la culture studio (on rend un
projet, pas une copie), c'est le vrai choc pour un sortant de lycée.
PLAN B : même repli que la diapo NDP si le réseau de la salle lâche.
-->

---
layout: default
breadcrumb: Ouverture
---

# La direction

<div class="mt-10 flex justify-center gap-20 text-center text-sm" style="margin-right:-6rem">

<div class="w-52">
<img src="/direction/frederic-ronsmans.jpg" alt="Frédéric Ronsmans" class="w-full aspect-square object-cover grayscale" />
<p class="mt-3 mb-0"><b>Frédéric Ronsmans</b></p>
<p class="mt-1 op-60 text-xs">Chef d'établissement<br/>Notre-Dame Providence</p>
</div>

<div class="w-52">
<img src="/direction/simon-vanesse.jpg" alt="Simon Vanesse" class="w-full aspect-square object-cover grayscale" />
<p class="mt-3 mb-0"><b>Simon Vanesse</b></p>
<p class="mt-1 op-60 text-xs">Directeur général<br/>ARTFX</p>
</div>

</div>

<!--
C'est ICI que le directeur prend le micro — décision actée. Il rend la parole
juste avant la diapo suivante, et le cold open relance la salle.
-->

---
layout: demo
---

<ShaderCanvas src="/shaders/sunset.frag" :steps="12" :dpr="1" height="100%" />

::caption::

Dans quelques semaines, vous saurez écrire *ça*.

<!--
LE COLD OPEN. 90 secondes, pas plus, et c'est ici que ma prise de parole commence
vraiment — après l'institutionnel, avant l'abstrait.

Ne rien expliquer techniquement. Laisser tourner, laisser le silence travailler,
puis la phrase. Enchaîner directement sur la diapo suivante.

PLAN B : si WebGL2 ne passe pas sur la machine de la salle, le composant affiche
le message d'erreur en clair — prévoir une capture vidéo dans public/heavy/.
-->

---
layout: statement
---

# Le premier BTS mêlant informatique, infrastructure, IA et simulation 3D

Et vous êtes la première promotion.

<!--
Le mot « première » fait deux choses : il flatte, et il engage. Les deux sont utiles
un jour de rentrée. Enchaîner sans pause.
-->

---
layout: default
breadcrumb: Ouverture / Les métiers
---

# Les métiers classiques de la 3D

<div class="mt-6 grid grid-cols-2 gap-8 text-sm" style="margin-right:-6rem">

<div v-click>
<img src="/metiers/jeu-video.jpg" alt="Jeu vidéo" class="h-56 w-full object-cover" />
<p class="mt-2"><b>Jeu vidéo</b> — des mondes qui répondent au joueur</p>
</div>

<div v-click>
<img src="/metiers/cinema-vfx.jpg" alt="Cinéma d'effets spéciaux : performance capture" class="h-56 w-full object-cover" />
<p class="mt-2"><b>Cinéma d'effets spéciaux</b> — des images que la caméra ne peut pas filmer</p>
</div>

</div>

<!--
Les métiers classiques de la 3D — le cœur historique du domaine, et d'ARTFX.
L'image de droite : Alita, l'actrice en performance capture et le personnage
final. Dire en une phrase que derrière chacune de ces images il y a du code.
-->

---
layout: default
breadcrumb: Ouverture / Les métiers
---

# De nouveaux métiers

<div class="mt-6 grid grid-cols-2 gap-8 text-sm" style="margin-right:-6rem">

<div v-click>
<img src="/metiers/jumeau-numerique.jpg" alt="Jumeau numérique automobile" class="h-56 w-full object-cover" />
<p class="mt-2"><b>Jumeaux numériques</b> — concevoir et tester en 3D avant de construire</p>
</div>

<div v-click>
<img src="/metiers/simulation-spatiale.jpg" alt="Simulation spatiale" class="h-56 w-full object-cover" />
<p class="mt-2"><b>Simulation</b> — spatial, défense, énergie, médecine</p>
</div>

</div>

<!--
Reprise des diapos « métiers » du deck d'origine. Le cold open a montré le rêve ;
ici on montre que le même savoir-faire s'achète partout — l'argument pour ceux
(et les parents) qui s'inquiètent d'un secteur « passion ».
-->

---
layout: default
breadcrumb: Ouverture / Les métiers
---

# Des technologies universelles

<div class="mt-6 grid grid-cols-2 gap-8 text-sm" style="margin-right:-6rem">

<div v-click>
<img src="/metiers/industrie.jpg" alt="Bras robotiques dans un laboratoire" class="h-56 w-full object-cover" />
<p class="mt-2"><b>Industrie</b> — robotique, automatisation, contrôle</p>
</div>

<div v-click>
<img src="/metiers/finance.jpg" alt="Bureau, courbe de marché sur la vitre" class="h-56 w-full object-cover" />
<p class="mt-2"><b>Finance</b> — données massives, temps réel</p>
</div>

</div>

<div v-click class="mt-4 text-base">
Partout, les mêmes outils qu'ici : <b>le C++</b> pour la performance,
<b>les technologies web</b> pour les interfaces.
</div>

<!--
Le pont : ce ne sont pas des mondes séparés, ce sont les mêmes langages et les
mêmes outils que ceux du programme. Photo industrie : laboratoire NIH, domaine
public (Wikimedia Commons, « Chemical Genomics Robot »).
-->

---
layout: default
breadcrumb: Ouverture / Les métiers
---

# Ce n'est plus une niche

<div v-click class="mt-6 flex justify-center" style="margin-right:-6rem">
<img src="/metiers/presse-unreal.png" alt="Article de presse : Unreal Engine s'est imposé dans les industries créatives" class="w-4/5" />
</div>

<div v-click class="mt-5 text-base text-center" style="margin-right:-6rem">
Fortnite, une série animée, les JT de TF1 et M6, des logiciels embarqués — <b>le même moteur</b>.
</div>

<!--
La preuve par la presse généraliste : quand Notre Temps explique Unreal Engine,
c'est que le sujet a quitté le monde des initiés. Une phrase, pas plus,
et on enchaîne sur la promo.
-->

---
layout: default
breadcrumb: Ouverture
---

# Et vous ?

<div class="mt-8 text-lg">

Vous venez de filières générales, technologiques
et professionnelles. 

</div>

<div v-click class="mt-8">
Vous avez des expériences différentes, des connaissances différentes.
</div>

<div v-click class="mt-8">
Certains et certaines ont déjà poursuivi des études ou exercé des métiers. D'autres sortent du lycée.
</div>

<!--
TODO : le nombre d'étudiants, et vérifier les filières d'origine réelles.
Moment de respiration : les faire réellement se regarder, sourire, laisser
le brouhaha monter deux secondes. Première graine du thème « vous ne
travaillerez jamais seuls » qui revient en partie 2.
-->

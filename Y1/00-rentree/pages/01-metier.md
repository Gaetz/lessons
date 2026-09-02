---
layout: section
breadcrumb: 1 — Le métier a changé
---

# Le métier a changé

Ce que vous allez réellement apprendre

---
layout: statement
---

# Qui a déjà demandé du code à une IA ?

Levez la main.

<!--
Faire lever les mains — la plupart se lèveront, c'est le but. Laisser un temps.
Le déni me décrédibiliserait en trente secondes ; l'honnêteté frontale achète
le droit de dire tout le reste de cette partie.
-->

---
layout: default
breadcrumb: 1 — Le métier a changé
---

# Ce code a l'air juste

```cpp
// Déplacer le personnage vers la droite
player.x += speed;
```

<v-clicks>

<p class="mt-6">Il compile. Il tourne. La démo marche.</p>

<p>Sur un écran 144 Hz, votre personnage court <b>2,4 fois plus vite</b>
que sur un écran 60 Hz. Même code, même jeu.</p>

</v-clicks>

<div v-click class="mt-10">

```cpp
player.x += speed * dt;   // delta-time
```

</div>

<v-clicks>

<p class="mt-6">L'IA ne remplace pas votre compréhension.</p>

</v-clicks>

<!--
Premier vrai moment technique de la journée — ne pas l'expliquer à fond,
le planter. Une frame = une exécution ; plus l'écran est rapide, plus le
personnage avance. Le facteur 2,4 c'est juste 144/60. La correction s'affiche
sans commentaire long : « vous comprendrez dt dans quelques semaines, et ce
jour-là vous saurez quelque chose que le prompt ne sait pas ».
Cette diapo prépare le budget de frame de la partie 2.
-->

---
layout: split
breadcrumb: 1 — Le métier a changé / Trois âges
---

# Âge 1 — La machine est rare

<div class="mt-8 text-base">

<v-clicks>

- Un ordinateur remplit une pièce, et coûte une fortune
- L'humain est abondant : on écrit au plus près du métal
- <b>Ce qui est rare : le cycle machine</b>

</v-clicks>

</div>

::right::

<div>
<img src="/ages/eniac.jpg" alt="Deux opératrices programment l'ENIAC" class="w-full object-cover" />
<p class="mt-2 text-xs op-60">ENIAC, 1946 — ses six premiers programmeurs étaient des programmeuses.</p>
</div>

<!--
Premier des trois âges : une diapo chacun, une idée chacun.
La grille à retenir : à chaque âge, ce qui est rare est ce qui est cher.
L'anecdote des programmeuses de l'ENIAC est vraie et utile — le métier
n'a pas toujours été un monde d'hommes.
-->

---
layout: split
breadcrumb: 1 — Le métier a changé / Trois âges
---

# Âge 2 — L'abstraction est reine

<div class="mt-8 text-base">

<v-clicks>

- Un ordinateur sur chaque bureau, puis dans chaque poche
- Langages, OS, réseau, cloud : des couches pour oublier le métal
- <b>Ce qui est rare : le code produit par rapport au besoin de code</b>

</v-clicks>

</div>

::right::

<div>
<img src="/ages/ibm-pc.jpg" alt="IBM PC 5150" class="w-full h-70 object-cover" />
<p class="mt-2 text-xs op-60">IBM PC, 1981 — photo CC BY-SA, Wikimedia Commons.</p>
</div>

<!--
L'âge qu'ils connaissent sans le savoir : tout ce qu'ils utilisent est fait
de couches d'abstraction. Ne pas dérouler l'histoire — une phrase, l'image
fait le reste.
-->

---
layout: split
breadcrumb: 1 — Le métier a changé / Trois âges
---

# Âge 3 — Le code se génère

<div class="mt-8 text-base">

<v-clicks>

- Nous y sommes : l'IA écrit du code plausible en une seconde
- <b>Ce qui est rare : connaitre les bonnes solutions, concevoir le bon logiciel</b>

</v-clicks>

</div>

::right::

<div>
<img src="/ages/code-genere.jpg" alt="Écran de code" class="w-full object-cover" />
<p class="mt-2 text-xs op-60">Écrire n'a jamais été aussi peu cher. Comprendre, si.</p>
</div>

<!--
Généraliser la diapo du dt : écrire ne coûte rien, savoir si c'est juste coûte
tout. C'est la seule grille qui compte pour comprendre la suite — la rappeler
explicitement : « à chaque âge, ce qui est rare est ce qui est cher ».
-->

---
layout: split
breadcrumb: 1 — Le métier a changé
---

# Ce que l'IA a fait baisser

<v-clicks>

- Le boilerplate
- Le prototype jetable
- La documentation
- La traduction d'un langage à l'autre
- L'exploration d'une API inconnue

</v-clicks>

::right::

<div>

# Ce qu'elle n'a pas fait baisser

<v-clicks at="6">

- **La spécification** — savoir ce qu'on veut
- **La vérification** — savoir si c'est juste
- **La performance** — 16,6 ms ne se négocient pas
- **La responsabilité** — quelqu'un signe

</v-clicks>

</div>

<!--
Être honnête et frontal : ils utilisent déjà ces outils. Un discours de déni
me décrédibilise en trente secondes. Le message : « vous les utiliserez ici,
tous les jours, sans culpabilité. La formation vous entraîne à ce que l'outil ne fait pas. »

Sur « 16,6 ms » : ne pas expliquer ici. Annoncer que la partie suivante montre
d'où vient ce chiffre — c'est le teaser de la partie 2.
-->

---
layout: statement
---

# Ce qui devient rare devient cher

Le code est devenu abondant. La compréhension est devenue rare.

<!--
Le pont économique : la grille des trois âges appliquée à leur propre salaire.
À chaque âge, ce qui est rare est ce qui est payé. Ne pas développer — la
diapo suivante donne la version concrète côté junior.
-->

---
layout: default
breadcrumb: 1 — Le métier a changé
---

<div class="h-full flex flex-col justify-center pb-20">

# « Si l'IA fait tout votre travail,<br/>vous valez le prix de l'IA »

<p class="text-2xl mt-6">Deux cents euros par mois.</p>

</div>

<!--
La version concrète du statement précédent : le prix d'un abonnement IA
haut de gamme. Laisser le chiffre tomber, sans commentaire — c'est lui
qui fait le travail. Vérifier le tarif courant avant le jour J.
-->

---
layout: full
---

<img src="/metier/lecture-ecran.jpg" alt="" class="absolute inset-0 w-full h-full object-cover" style="filter: blur(5px) brightness(0.55); transform: scale(1.06)" />

<div class="absolute inset-0 flex flex-col justify-center px-20" style="color:#EDEEDA">

<h1 style="color:#EDEEDA">Ce que nous allons apprendre</h1>

<div class="mt-6 text-lg">

<v-clicks>

- **Comprendre les besoins**
- **Concevoir**
- **Organiser l'utilisation du logiciel**
- **Comprendre le contexte**
- **Apporter de la connaissance**

</v-clicks>

</div>

</div>

<!--
La réponse positive au « deux cents euros » : voilà ce qui, chez vous, ne
s'abonne pas. Cinq verbes, un par clic, sans commentaire long.
Fin de la partie 1. Transition vers la partie 2, à l'oral :
« Et il existe un domaine où tout ça se voit à l'œil nu. Allons-y. »
Photo : CC0 (Unsplash / Wikimedia Commons), floutée en CSS.
-->

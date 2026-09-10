---
layout: section
breadcrumb: 1 — Les bases
---

# Les bases

Dessiner, nommer, répéter, ranger

---
layout: split
breadcrumb: 1 — Les bases / Cours 00
---

# Cours 00 — Premier contact

Aujourd'hui on va apprendre les bases de la programmation
en créant des images. Nous allons utiliser le langage **C++** :
il s'agira de modifier les fichiers `ofApp.cpp` et `ofApp.h`.

<div class="mt-6 text-sm">

<v-clicks>

- Un concept à la fois, **pas à pas**
- À chaque étape, **ton programme tourne**
- À la fin : une tête qui suit la souris

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/00-visage.png" alt="Tête blanche translucide aux yeux rouges" class="w-full object-cover" />
<p class="mt-2 text-xs op-60">L'objectif de la séance — construit en sept étapes.</p>
</div>

<!--
Le contrat : on avance par petites versions qui compilent toutes. Personne
n'est censé tout comprendre du premier coup — on tape, on lance, on observe.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 00
---

# L'écran est un quadrillage

<div class="mt-4 text-base">

<v-clicks>

- L'origine `(0, 0)` est **en haut à gauche**, pas au centre
- `y` augmente **vers le bas** — ça surprend tout le monde
- Chaque pixel a une adresse : deux nombres, `x` et `y`

</v-clicks>

</div>

::right::

<div>
<img src="/ressources/cours/img/00-repere.png" alt="Repère de l'écran, origine en haut à gauche" class="w-full object-contain" />
</div>

<!--
Les deux surprises du repère écran. Elles reviendront tout le semestre.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Étape 1 — une fenêtre

```cpp
#include "ofApp.h"

void ofApp::setup() {
	ofSetWindowShape(800, 800);
}

void ofApp::update() {

}

void ofApp::draw() {

}
```

<div class="mt-3 text-base">

<v-clicks>

- Le `.h` (l'emballage, recopié tel quel) annonce trois blocs ; on remplit `ofApp.cpp`
- Une fenêtre grise de 800 × 800 — c'est peu, mais c'est **ton** programme

</v-clicks>

</div>

<!--
Essaie : 400,400 puis 1200,300. Le .h minimal est donné dans le document,
section 2.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Lire la ligne : un appel de fonction

```cpp
ofSetWindowShape(800, 800);
```

<div class="mt-4">
<img src="/ressources/cours/img/00-anatomie-appel.png" alt="Anatomie de l'appel : nom, paramètres, point-virgule" class="w-4/5 mx-auto object-contain" />
</div>

<div v-click class="mt-4 text-base text-center">
Un appel de fonction = <b>demander à l'ordinateur de faire quelque chose</b>.
Cette anatomie sert toute l'année.
</div>

<!--
Et tout ce qui suit // est un commentaire : note pour les humains, ignorée
par l'ordinateur.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# `setup()` : une fois, au lancement

```cpp
void ofApp::setup() {
	ofSetWindowShape(800, 800);      // la taille de la fenêtre
}
```

<div class="mt-5 text-base">

<v-clicks>

- Le bloc `setup()` est exécuté **une seule fois**, au démarrage du programme
- C'est là qu'on règle **ce qui ne change pas**
- Les deux autres blocs attendent leur tour — chaque chose en son temps

</v-clicks>

</div>

<!--
Ne pas expliquer update/draw maintenant : ils viennent avec le besoin.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Étape 2 — dessiner un cercle

```cpp
void ofApp::draw() {
	ofDrawCircle(400, 400, 100);
}
```

<div class="mt-5 text-base">

<v-clicks>

- Trois paramètres : position `x` du **centre**, position `y`, et le **rayon** — pas le diamètre
- Le dessin s'écrit dans le bloc `draw()` — ce qui le distingue de `setup` viendra en fin de séance
- L'autre forme à connaître : `ofDrawRectangle(x, y, largeur, hauteur)` — son `(x, y)` est le coin **haut-gauche**

</v-clicks>

</div>

<!--
Essaie : le cercle dans chaque coin ; collé au bord, il dépasse — rien ne
plante, ce qui sort de l'écran est juste invisible.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Étape 3 — la couleur

```cpp
void ofApp::draw() {
	ofSetColor(255, 0, 0);
	ofDrawCircle(400, 400, 100);
}
```

<div class="mt-5 text-base">

<v-clicks>

- Trois nombres de 0 à 255 : **rouge, vert, bleu** — l'écran mélange de la lumière
- `(255, 255, 255)` blanc · `(0, 0, 0)` noir · `(255, 255, 0)` jaune
- La couleur choisie reste active pour **toutes les formes qui suivent**

</v-clicks>

</div>

<!--
Essaie : un cercle vert, un jaune.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 00
---

# Le quatrième nombre : l'opacité

```cpp
ofSetColor(255, 0, 0, 150);     // rouge semi-transparent
```

<div class="mt-5 text-base">

<v-clicks>

- Facultatif : 255 = opaque, 0 = invisible
- Deux formes qui se chevauchent + de la transparence = les couleurs se **mélangent**
- La tête finale s'en servira pour ses yeux

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/00-opacite.png" alt="Opacité 255 : recouvre ; 150 : se mélange" class="w-full object-contain" />
</div>

<!--
Essaie : deux cercles qui se chevauchent, le deuxième semi-transparent.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Étape 4 — les variables

```cpp
void ofApp::draw() {
	int x { 0 };
	int y { 0 };

	ofSetColor(255, 255, 255);
	ofDrawCircle(200 + x, 300 + y, 50);
	ofDrawCircle(400 + x, 300 + y, 50);
	ofDrawRectangle(250 + x, 400 + y, 100, 30);
}
```

<div class="mt-3 text-base">

<v-clicks>

- `int x { 0 };` crée une **variable** : un nombre qui porte un nom, utilisable partout où un nombre est attendu
- Change **une seule ligne** — `int x { 100 };` — et les trois formes se décalent **d'un coup**

</v-clicks>

</div>

<!--
Essaie : y { -150 }, puis x et y en même temps. C'est LA démo : un nombre
écrit une fois, utilisé partout.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 00
---

# Une variable est une boîte en mémoire

<div class="mt-4 text-base">

<v-clicks>

- Une **étiquette** : le nom (`x`), pour retrouver la boîte
- Une **taille** : qui dépend du **type** (`int`)
- Un contenu : la valeur qu'on y range (`{ 100 }`)

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/00-variable-boite.png" alt="Une variable : une boîte en mémoire avec étiquette et taille" class="w-full object-contain" />
</div>

<!--
L'image mentale de l'année : lire = ouvrir la boîte, affecter = remplacer
son contenu.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 00
---

# Le type `int` : 4 octets

<div class="mt-4 text-base">

<v-clicks>

- Un **octet** = 8 **bits** ; un bit vaut 0 ou 1
- Compter en bits = compter en base 2 : chaque case vaut le double de la précédente
- 8 bits → les nombres de 0 à 255 ; les 32 bits d'un `int` → environ ±2 milliards

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/00-octet-binaire.png" alt="Un octet : 8 bits et le comptage binaire" class="w-full object-contain" />
</div>

<!--
Faire compter la salle : 2⁸ = 256. Le détail est dans l'encadré du document.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Étape 5 — à toi : dessine une figure

<div class="mt-5 text-base">

<v-clicks>

- **1 ·** Au moins **quatre formes** (cercles et rectangles)
- **2 ·** Au moins **deux couleurs**
- **3 ·** Toutes les positions **par rapport à `x` et `y`** (comme `200 + x`) — pour déplacer toute la figure en changeant deux nombres

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
Dix minutes, papier autorisé. Un visage, un robot, un animal — ce que tu veux.
</div>

<!--
Pendant qu'ils dessinent : circuler. Erreur type : des positions absolues,
sans + x. La contrainte 3 prépare la fonction.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Notre proposition — une tête

```cpp
void ofApp::draw() {
	int x { 0 };
	int y { 0 };

	// Le visage
	ofSetColor(255, 255, 255, 255);
	ofDrawCircle(200 + x, 200 + y, 225);
	// La bouche
	ofDrawRectangle(100 + x, 200 + y, 250, 50);

	// Les yeux : rouge (255, 0, 0) — essaie (0, 255, 0)
	ofSetColor(255, 0, 0, 150);
	ofDrawCircle(55 + x, 75 + y, 50);
	ofDrawCircle(375 + x, 75 + y, 50);
}
```

<div class="mt-2 text-sm">

- Sept formes, deux couleurs, tout par rapport à `(x, y)` — c'est la référence `ofApp00`, téléchargeable

</div>

<!--
Essaie, sur notre tête ou sur ta figure : deux oreilles, un nez (coin
haut-gauche !), des yeux carrés.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Étape 6 — deux têtes ? La fonction

```cpp
void ofApp::funnyFace(int x, int y) {
	ofSetColor(255, 255, 255, 255);
	ofDrawCircle(200 + x, 200 + y, 225);
	ofDrawRectangle(100 + x, 200 + y, 250, 50);
	ofSetColor(255, 0, 0, 150);
	ofDrawCircle(55 + x, 75 + y, 50);
	ofDrawCircle(375 + x, 75 + y, 50);
}

void ofApp::draw() {
	funnyFace(100, 100);
	funnyFace(400, 400);
}
```

<div class="mt-2 text-base">

<v-clicks>

- Copier-coller huit lignes par tête ? Non : on range le dessin dans une **fonction à nous**
- Un appel = une tête. Deux appels = deux têtes

</v-clicks>

</div>

<!--
Le geste : déplacer le dessin de draw() vers funnyFace. Les int x / int y
locaux disparaissent — voir diapo suivante.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 00
---

# Les paramètres, et l'annonce dans le `.h`

```cpp
// dans ofApp.h, une ligne, sans le corps :
	void funnyFace(int x, int y);
```

<div class="mt-5 text-base">

<v-clicks>

- `x` et `y` sont les **paramètres** de la fonction : celui qui appelle fournit les valeurs — `funnyFace(100, 100)` dessine autour de (100, 100)
- Le `.h` est la **table des matières** du programme : toute nouvelle fonction s'y annonce, sinon le compilateur ne la connaît pas

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/00-fonction-tampon.png" alt="La fonction est un tampon appliqué à chaque appel" class="w-full object-contain" />
</div>

<!--
C'est exactement pour ça que la figure devait être écrite « par rapport à
x, y » à l'étape 5.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# La magie : la souris

```cpp
void ofApp::draw() {
	funnyFace(mouseX, mouseY);
}
```

<div class="mt-5 text-base">

<v-clicks>

- La tête **suit la souris**
- `mouseX` et `mouseY` : deux variables mises à jour toutes seules — la position de la souris, utilisable partout où un nombre est attendu

</v-clicks>

</div>

<!--
Essaie : funnyFace(mouseX + 200, mouseY) — la tête suit avec un décalage.
Puis une deuxième tête fixe pendant que la première suit.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Étape 7 — le fond

```cpp
void ofApp::draw() {
	ofBackground(30);
	funnyFace(mouseX, mouseY);
}
```

<div class="mt-5 text-base">

<v-clicks>

- Sans lui : les anciennes positions restent affichées — des **traînées**
- `ofBackground` repeint toute la fenêtre, en **première ligne** de `draw()` : chaque image repart d'un fond propre
- Un nombre = un gris (0 noir, 255 blanc) ; trois nombres = une couleur

</v-clicks>

</div>

<!--
Montrer d'abord SANS ofBackground : le bug motive la solution. Essaie : un
fond de couleur ; un fond blanc — que deviennent les yeux semi-transparents ?
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Le programme est découpé en blocs

<div class="mt-4 text-base">

| Bloc | Quand | Rôle |
|---|---|---|
| `setup()` | une fois, au lancement | régler ce qui ne change pas |
| `update()` | 60 fois par seconde | encore **vide** — les nombres y changeront tout seuls (cours 05) |
| `draw()` | 60 fois par seconde | dessiner |
| `funnyFace(x, y)` | quand on l'appelle | notre fonction à nous |

</div>

<div v-click class="mt-5 text-base">
C'est l'état final — la référence <code>ofApp00a</code>. <b>Garde ta figure à toi.</b>
</div>

<!--
L'organisation setup/update/draw est celle de TOUS les programmes du module.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — sur papier ou dans Paint, dessine ce que ce `draw()` affiche. Puis tape-le et compare :

```cpp
void ofApp::draw() {
	ofBackground(30);
	int x { 50 };
	ofSetColor(255, 255, 0);
	ofDrawCircle(150 + x, 100, 60);
	ofSetColor(0, 120, 255);
	ofDrawRectangle(150 + x, 100, 200, 40);
}
```

Trois pièges à déjouer : le troisième nombre du cercle, le coin du rectangle, et qui est dessiné devant.

</div>

<div v-click class="mt-3 text-base">

**2 · La bouche vivante** — dans `funnyFace`, remplace la largeur de la bouche par `mouseX` : elle s'étire quand la souris va à droite. `mouseX` s'utilise partout où un nombre est attendu — pas seulement dans une position.

</div>

<!--
Ex 1 : cercle jaune centré en (200,100), rectangle bleu DEVANT (dessiné
après), dont (200,100) est le coin haut-gauche.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · Le fond piloté** — `ofBackground(mouseX, 100, 200);` : le fond change avec la souris. Observe : passé une certaine position, il ne change plus. Pourquoi ? (Indice : 255. La vraie réponse au cours 11.)

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Ta deuxième fonction** — écris `void decor()` (sans paramètres : un soleil, une maison, des étoiles…), annonce-la dans le `.h`, et appelle-la dans `draw()` **avant** `funnyFace`. Puis essaie de l'appeler **après** : l'ordre des appels décide de qui est devant.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/00-premier-contact.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/00-premier-contact.md" download>md</a> · <a href="/ressources/ofApp00.h" download>ofApp00.h</a> · <a href="/ressources/ofApp00.cpp" download>ofApp00.cpp</a> · <a href="/ressources/ofApp00a.h" download>ofApp00a.h</a> · <a href="/ressources/ofApp00a.cpp" download>ofApp00a.cpp</a></p>

<!--
Ex 3 : mouseX dépasse 255, la composante sature. Ex 4 : decor() après
funnyFace passe DEVANT la tête.
-->
---
layout: split
breadcrumb: 1 — Les bases / Cours 01
---

# Cours 01 — Variables et opérations

Au cours 00, deux variables déplaçaient une figure.
Ce cours les regarde de près : les **types de nombres**,
les **calculs** — et deux pièges célèbres.

<div class="mt-6 text-sm">

<v-clicks>

- **Déduire** une position au lieu de la deviner
- Le piège de la **division entière**
- Le piège du **rayon**

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/01-cercles.png" alt="Un cercle et une rangée de cercles" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">Des positions déduites de la taille de la fenêtre.</p>
</div>

<!--
Créer un nouveau projet 02_Variables avec le Project Generator.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# Étape 1 — repartir propre

```cpp
void ofApp::setup() {
	ofSetWindowShape(400, 400);
	ofBackground(200);
}
```

<div class="mt-5 text-base">

<v-clicks>

- L'emballage minimal du cours 00 dans le `.h`, `update` et `draw` vides — une fenêtre gris clair
- Le fond est dans `setup()` cette fois : ce dessin **ne bouge pas**, le peindre une fois suffit — dès que ça bougera (cours 05), il redescendra dans `draw()`

</v-clicks>

</div>

<!--
Essaie : ofBackground(255), (0), puis une couleur à trois nombres.
Rappel : un seul nombre = un gris.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# Étape 2 — les types : `int` et `float`

```cpp
void ofApp::draw() {
	int sizeX { 400 };
	int sizeY { 400 };
}
```

<div class="mt-4 text-base">

| Type | Contenu | Exemples |
|---|---|---|
| `int` | un nombre **entier** | `-3`, `0`, `400` |
| `float` | un nombre **à virgule** | `37.5f`, `0.25f`, `3.0f` |

<v-clicks>

- Le `f` à la fin dit « ce nombre est un `float` » — prends l'habitude : `37.5f`
- Accolades `{ 400 }` pour une valeur de départ ; `=` quand la valeur est **calculée**

</v-clicks>

</div>

<!--
Rien de neuf à l'écran : ces boîtes attendent l'étape 3. On en profite pour
les regarder de près (deux diapos).
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# Une variable est une case en mémoire

<div class="mt-8 flex justify-center items-end gap-1">
  <div class="w-14 h-14 border-2 border-gray-300 rounded flex items-center justify-center text-gray-300 text-lg">·</div>
  <div class="w-14 h-14 border-2 border-gray-300 rounded flex items-center justify-center text-gray-300 text-lg">·</div>
  <div class="text-center">
    <div class="text-sm font-bold mb-1" style="color:#EA5027">sizeX</div>
    <div class="w-20 h-14 rounded flex items-center justify-center text-xl font-bold" style="border:3px solid #EA5027">400</div>
    <div class="text-xs op-60 mt-1"><code>int</code></div>
  </div>
  <div class="w-14 h-14 border-2 border-gray-300 rounded flex items-center justify-center text-gray-300 text-lg">·</div>
  <div class="text-center">
    <div class="text-sm font-bold mb-1" style="color:#0F6FA5">x</div>
    <div class="w-20 h-14 rounded flex items-center justify-center text-xl font-bold" style="border:3px solid #0F6FA5">37.5</div>
    <div class="text-xs op-60 mt-1"><code>float</code></div>
  </div>
  <div class="w-14 h-14 border-2 border-gray-300 rounded flex items-center justify-center text-gray-300 text-lg">·</div>
  <div class="w-14 h-14 border-2 border-gray-300 rounded flex items-center justify-center text-gray-300 text-lg">·</div>
</div>

<div class="mt-8 text-sm">

<v-clicks>

- La mémoire de l'ordinateur est une **immense rangée de cases numérotées**
- Déclarer fait trois choses : **réserver** une case, lui donner un **nom**, y ranger une **valeur**
- Le **type** est la règle de la case — fixé une fois pour toutes ; le nom n'existe que pour nous

</v-clicks>

</div>

<!--
Rappel du cours 00, approfondi : lire = ouvrir la case, affecter = remplacer
son contenu.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# Dans la case : ranger un `int`, ranger un `float`

<div class="mt-6 text-sm">

<div class="flex items-center gap-4 mb-3">
  <code class="font-bold" style="color:#EA5027">int&nbsp;400</code>
  <div class="flex">
    <div class="px-3 py-2 font-mono text-base rounded" style="border:2px solid #EA5027">1 1 0 0 1 0 0 0 0</div>
  </div>
  <span class="op-60">le nombre lui-même, écrit en binaire — <b>exact</b></span>
</div>

<div class="flex items-center gap-4">
  <code class="font-bold" style="color:#0F6FA5">float&nbsp;37.5</code>
  <div class="flex gap-1">
    <div class="px-2 py-2 font-mono text-base rounded" style="border:2px solid #0F6FA5">+</div>
    <div class="px-2 py-2 font-mono text-base rounded" style="border:2px solid #0F6FA5">2⁵</div>
    <div class="px-3 py-2 font-mono text-base rounded" style="border:2px solid #0F6FA5">1,001011</div>
  </div>
  <span class="op-60">signe · exposant · chiffres significatifs — comme 3,75 × 10¹</span>
</div>

</div>

<div class="mt-6 text-sm">

<v-clicks>

- L'`int` **compte** en binaire (cours 00) : exact, mais borné — ±2 147 483 647
- Le `float` range une **notation scientifique en binaire** : plage énorme, mais ~7 chiffres significatifs
- Beaucoup de nombres à virgule sont stockés **en arrondi** — ne compare jamais deux `float` avec `==`

</v-clicks>

</div>

<!--
0.1 n'est pas exactement 0.1. Pour des pixels, on s'en moque ; pour un ==,
jamais.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# Construire un `float` — 1. la partie entière

<div class="mt-6 text-center text-2xl font-mono">
37 = <span style="color:#EA5027">32</span> + <span style="color:#EA5027">4</span> + <span style="color:#EA5027">1</span>
</div>

<div class="mt-6 flex justify-center gap-2">
  <div class="text-center"><div class="px-4 py-3 font-mono text-2xl font-bold rounded" style="border:3px solid #EA5027;background:#fce9e2;color:#EA5027">1</div><div class="text-sm mt-1" style="color:#0F6FA5">32</div></div>
  <div class="text-center"><div class="px-4 py-3 font-mono text-2xl rounded border-2 border-gray-300 text-gray-400">0</div><div class="text-sm mt-1 op-40">16</div></div>
  <div class="text-center"><div class="px-4 py-3 font-mono text-2xl rounded border-2 border-gray-300 text-gray-400">0</div><div class="text-sm mt-1 op-40">8</div></div>
  <div class="text-center"><div class="px-4 py-3 font-mono text-2xl font-bold rounded" style="border:3px solid #EA5027;background:#fce9e2;color:#EA5027">1</div><div class="text-sm mt-1" style="color:#0F6FA5">4</div></div>
  <div class="text-center"><div class="px-4 py-3 font-mono text-2xl rounded border-2 border-gray-300 text-gray-400">0</div><div class="text-sm mt-1 op-40">2</div></div>
  <div class="text-center"><div class="px-4 py-3 font-mono text-2xl font-bold rounded" style="border:3px solid #EA5027;background:#fce9e2;color:#EA5027">1</div><div class="text-sm mt-1" style="color:#0F6FA5">1</div></div>
</div>

<div class="mt-8 text-base text-center">

<v-click>

37 en binaire s'écrit <code class="text-xl font-bold">100101</code> — le comptage du cours 00 : chaque case vaut le double de la précédente

</v-click>

</div>

<!--
On construit UN exemple de bout en bout : 37.5. D'abord la partie entière —
c'est exactement le comptage binaire déjà vu.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# 2. Après la virgule

<div class="mt-6 text-center text-lg">
Après la virgule, chaque chiffre vaut la <b>moitié</b> du précédent :
</div>

<div class="mt-5 flex justify-center gap-2">
  <div class="text-center"><div class="px-4 py-3 font-mono text-2xl rounded" style="border:3px solid #0F6FA5">,</div><div class="text-sm mt-1 op-0">-</div></div>
  <div class="text-center"><div class="px-4 py-3 font-mono text-2xl font-bold rounded" style="border:3px solid #EA5027;background:#fce9e2;color:#EA5027">1</div><div class="text-sm mt-1" style="color:#0F6FA5">1/2</div></div>
  <div class="text-center"><div class="px-4 py-3 font-mono text-2xl rounded border-2 border-gray-300 text-gray-400">0</div><div class="text-sm mt-1 op-40">1/4</div></div>
  <div class="text-center"><div class="px-4 py-3 font-mono text-2xl rounded border-2 border-gray-300 text-gray-400">0</div><div class="text-sm mt-1 op-40">1/8</div></div>
</div>

<div class="mt-8 text-base text-center">

<v-clicks>

<p>0,5 c'est <b>un demi</b> → en binaire : <code class="text-xl font-bold">,1</code></p>

<p class="mt-4 text-xl">37,5 = <code class="font-bold">100101,1</code></p>

</v-clicks>

</div>

<!--
0,75 s'écrirait ,11 (un demi + un quart) ; 0,25 s'écrirait ,01. Faire
deviner : comment s'écrit 0,625 ? (,101 : 1/2 + 1/8.)
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# 3. Décaler la virgule

<div class="mt-5 text-center text-lg">
Souviens-toi de l'école : 3750 = 3,75 × 10³ — la virgule décalée de 3 crans.<br>
En binaire, pareil, mais en base 2 :
</div>

<div class="mt-8 text-center font-mono text-3xl">
<span>100101<span style="color:#EA5027;font-weight:bold">,</span>1</span>
<span class="mx-6 op-60">→</span>
<span>1<span style="color:#EA5027;font-weight:bold">,</span>001011 × 2<sup style="color:#EA5027">5</sup></span>
</div>

<div class="mt-8 text-base text-center">

<v-clicks>

<p>On décale la virgule jusqu'à n'avoir <b>qu'un seul 1 devant</b></p>

<p>Ici : <b>5 crans</b> vers la gauche → l'exposant est <b style="color:#EA5027">5</b></p>

</v-clicks>

</div>

<!--
Compter les crans ensemble au tableau : 100101,1 → 10010,11 → ... →
1,001011. Cinq décalages.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# 4. Ranger dans la case

<div class="mt-8 flex justify-center items-end gap-2">
  <div class="text-center"><div class="px-5 py-4 font-mono text-3xl font-bold rounded" style="border:3px solid #0F6FA5">+</div><div class="text-sm mt-2" style="color:#0F6FA5">le signe</div></div>
  <div class="text-center"><div class="px-5 py-4 font-mono text-3xl font-bold rounded" style="border:3px solid #0F6FA5">2⁵</div><div class="text-sm mt-2" style="color:#0F6FA5">l'exposant</div></div>
  <div class="text-center"><div class="px-5 py-4 font-mono text-3xl font-bold rounded" style="border:3px solid #0F6FA5">1,001011</div><div class="text-sm mt-2" style="color:#0F6FA5">les chiffres significatifs</div></div>
</div>

<div class="mt-8 text-base text-center">

<v-clicks>

<p><code>37.5f</code> est rangé : trois compartiments dans la case de 4 octets</p>

<p><b>À toi, sur papier</b> : construis <code>5.0</code>, puis <code>0.5</code>, puis <code>-12.25</code></p>

</v-clicks>

</div>

<!--
Réponses : 5.0 = [+][2²][1,01] ; 0.5 = [+][2⁻¹][1,0] ;
-12.25 = [−][2³][1,10001] (12,25 = 8 + 4 + 1/4 = 1100,01).
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# Et `0.1` ?

<div class="mt-6 text-center font-mono text-2xl">
0.1 = 0,0001<span style="color:#EA5027;font-weight:bold">1001</span><span style="color:#EA5027;font-weight:bold">1001</span><span style="color:#EA5027;font-weight:bold">1001</span>…
</div>

<div class="mt-8 text-base">

<v-clicks>

- Le motif <b style="color:#EA5027">1001</b> se répète **à l'infini** — comme 1/3 = 0,333… en décimal : un nombre tout simple à écrire en base 10, impossible en base 2
- La case n'a que ~7 chiffres significatifs : elle **coupe** — `0.1` est stocké **arrondi**
- C'est LA raison du « jamais `==` entre deux `float` » : deux calculs censés donner 0.1 peuvent différer d'une miette

</v-clicks>

</div>

<!--
La chute de la séquence : toutes les « bizarreries » des float viennent de
là. Pour des pixels on s'en moque ; pour un ==, jamais.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 01
---

# Étape 3 — déduire au lieu de deviner

```cpp
	float x = sizeX / 2.0f;        // 200 : le milieu de la largeur
	float y = sizeY * 3 / 4.0f;    // 300 : les trois quarts de la hauteur

	ofSetColor(255);
	ofFill();
	ofDrawCircle(x, y, 37.5f);
```

<div class="mt-5 text-base">

<v-clicks>

- `x` et `y` ne sont plus devinés : ils sont **déduits** de la taille de la fenêtre
- Passe `ofSetWindowShape` **et** `sizeX`/`sizeY` à 800 : le cercle reste au milieu, sans toucher au calcul
- Les quatre opérations : `+`, `-`, `*`, `/` — variables et nombres se mélangent

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/01-deduire.png" alt="Le même code dans deux fenêtres : le cercle reste au milieu" class="w-full object-contain" />
</div>

<!--
« Déduire plutôt que deviner » : le dessin résiste aux changements. C'est le
réflexe à installer.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 01
---

# Le piège du rayon

```cpp
ofDrawCircle(x, y, 37.5f);
```

<div class="mt-5 text-base">

<v-clicks>

- Le troisième nombre est le **rayon** : la distance du centre au bord
- Un cercle de **75 pixels de large** a un rayon de **37.5**
- Si tu penses en « taille », divise par deux

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/01-rayon-diametre.png" alt="Un cercle avec son rayon et son diamètre annotés" class="w-full object-contain" />
</div>

<!--
Erreur ultra-fréquente : des cercles deux fois trop gros.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 01
---

# Étape 4 — le piège de la division entière

```cpp
	int moitie = 7 / 2;
	ofDrawCircle(100, 100, moitie * 20);   // prédis le rayon avant de lancer !
```

<div class="mt-5 text-base">

<v-clicks>

- Rayon **60**, pas 70 : `7 / 2` vaut **3** — entier divisé par entier, C++ **jette la virgule** (`3 / 4` vaut 0)
- Le remède : un `float` dans la division — `7 / 2.0f` vaut `3.5f`
- Règle de survie : un calcul donne 0 sans raison ? Pense **division entière**

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/01-division-entiere.png" alt="7 / 2 vaut 3 : la virgule est jetée" class="w-full object-contain" />
</div>

<!--
Le détail qui compte : sizeY * 3 / 4 donne 300 (multiplication d'abord),
mais sizeY * (3 / 4) donne 0. Essaie : 7 / 2.0f et compare.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# Étape 5 — `=` veut dire « reçoit »

```cpp
	x = 0;
	float step { 75 };
	ofDrawCircle(x, y, 37.5f);
	x = x + step;
	ofDrawCircle(x, y, 37.5f);
	x = x + step;
	// ... et ainsi de suite, 10 cercles en tout
```

<div class="mt-4 text-base">

<v-clicks>

- `x = x + step;` n'est **pas une équation** : « calcule, puis range le résultat dans `x` »
- Plus de `float` devant `x` : la boîte existe déjà — la redéclarer serait une erreur
- La limite : trente cercles = quarante lignes de plus… il manque « **répète ça** » — cours 02

</v-clicks>

</div>

<!--
Essaie : espacer de 50 puis 25 (une ligne !) ; variable rayon commune —
change-la, tout grandit ensemble.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — sur papier ou dans Paint, place les deux cercles avant de lancer :

```cpp
int sizeX { 600 };
float a = sizeX * (1 / 2.0f);
float b = sizeX * (1 / 2);
ofDrawCircle(a, 200, 40);
ofDrawCircle(b, 200, 40);
```

Où atterrissent-ils, et pourquoi ?

</div>

<div v-click class="mt-4 text-base">

**2 · La cible** — des cercles concentriques au centre **exact** de la fenêtre : tout est déduit de `sizeX`, `sizeY` et d'une variable `rayon` (le suivant fait `rayon - 30`, etc.). Alterne deux couleurs. Redimensionne la fenêtre : la cible doit rester centrée.

</div>

<!--
Ex 1 : a = 300 (division flottante), b = 0 (division entière dans la
parenthèse !) — le deuxième cercle est collé au bord gauche.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · Le drapeau** — trois bandes verticales de couleurs, chacune large d'un **tiers** de la fenêtre, déduites de `sizeX`. Attention à la division.

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **La rangée réglable** — une rangée de 10 cercles qui traverse **toute** la fenêtre quel que soit `sizeX` : `step` est déduit de `sizeX`, et le rayon est déduit de `step` pour que les cercles se **touchent exactement**.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/01-variables.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/01-variables.md" download>md</a> · <a href="/ressources/ofApp01.h" download>ofApp01.h</a> · <a href="/ressources/ofApp01.cpp" download>ofApp01.cpp</a></p>

<!--
Ex 3 : sizeX / 3.0f. Ex 4 : step = sizeX / 10.0f, rayon = step / 2.
-->
---
layout: split
breadcrumb: 1 — Les bases / Cours 02
---

# Cours 02 — La boucle `for`

Le cours 01 finissait sur vingt lignes pour dix cercles.
La boucle `for` dit : « **répète ce bloc dix fois** » —
et comme on peut changer des variables à chaque tour,
les dix cercles pourront tous être différents.

```cpp
for (int i = 0; i < 10; i++) {
    // exécuté 10 fois, i de 0 à 9
}
```

- **initialisation** : une fois, au début
- **condition** : vérifiée avant chaque tour
- **incrément** : `i++` = `i = i + 1`, en fin de tour

::right::

<div>
<ZoomImage src="/ressources/cours/img/02-boucle.png" alt="Cercles croissants en diagonale" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">Dix cercles, un seul bloc de code.</p>
</div>

<!--
Dérouler à voix haute : i vaut 0, corps, i passe à 1, condition, corps…
10 < 10 est faux, on sort. JAMAIS 10. Et i n'existe que dans la boucle.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 02
---

# Étape 1 — la rangée du cours 01, en quatre lignes

```cpp
void ofApp::draw() {
	float x = 0;
	for (int i = 0; i < 10; i++) {
		ofDrawCircle(x, 100, 37.5f);
		x = x + 75;
	}
}
```

<div class="mt-5 text-base">

<v-clicks>

- La même rangée de dix cercles — le fichier a **fondu**
- Le corps tourne dix fois, `i` valant 0, 1, … 9 — **jamais 10**
- Dans un `for`, l'initialisation s'écrit avec `=` : la syntaxe universelle de cette ligne

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/02-deroule-boucle.png" alt="Le déroulé de la boucle : dix tours, jamais 10" class="w-full object-contain" />
</div>

<!--
Essaie : i < 20, puis ajuster le 75. Combien de lignes modifiées, contre
combien au cours 01 ?
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 02
---

# Étape 2 — accumuler à chaque tour

```cpp
	float x { 0 };                  // créées AVANT la boucle :
	float y { 0 };                  // elles gardent leur valeur
	float taille { 10 };            // de tour en tour
	int   b { 0 };

	for (int i = 0; i < 10; i++) {
		ofDrawCircle(x, y, taille / 2);

		x = x + 40;
		y = y + 40;
		taille = taille + 20;
		b = b + 25;
	}
```

<div class="mt-3 text-base">

<v-clicks>

- Une diagonale de cercles qui grossissent : les variables **accumulent** de tour en tour
- Créées **dans** la boucle, elles repartiraient de zéro — **où l'on déclare décide de la durée de vie**
- `b` accumule aussi, sans servir encore : il attend l'étape 3

</v-clicks>

</div>

<!--
La table des tours est dans le document. Essaie : partir d'en haut à droite.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 02
---

# Les deux styles

```cpp
// style accumulé : des variables qui avancent
x = x + 40;  taille = taille + 20;

// style « tout depuis i » : aucun état
ofDrawCircle(i * 40, i * 40, (10 + i * 20) / 2);
```

<div class="mt-5 text-base">

<v-clicks>

- Les deux produisent **le même dessin**
- Accumuler : plus lisible quand il y a beaucoup de variables
- Calculer depuis `i` : plus sûr quand on saute des tours — et c'est la lecture « formule » du cours 03

</v-clicks>

</div>

<!--
Essaie : réécrire la diagonale entière sans variable accumulée.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 02
---

# Étape 3 — remplissage et contour : deux passes

```cpp
		// 1) le remplissage : rouge → magenta, un peu transparent
		ofFill();
		ofSetColor(255, 0, b, 180);
		ofDrawCircle(x, y, taille / 2);

		// 2) le contour : orange
		ofNoFill();
		ofSetColor(255, 150, 0);
		ofDrawCircle(x, y, taille / 2);
```

<div class="mt-4 text-base">

<v-clicks>

- `ofFill()` / `ofNoFill()` : un interrupteur — pour avoir les deux, dessiner **deux fois le même cercle**
- La couleur contient la variable `b` : rouge pur au départ, presque magenta à la fin — **un nombre peut être une variable**

</v-clicks>

</div>

<!--
Le dernier cercle sort de l'écran : rien ne plante (moins vrai au cours 10).
Essaie : varier le vert ; puis les deux, un qui monte, un qui descend.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 02
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — sur papier ou dans Paint, place les cercles avant de lancer :

```cpp
for (int i = 0; i < 5; i++) {
	ofDrawCircle(50 + i * 80, 200, 10 + i * 10);
}
```

Combien de cercles, où, et de quelle taille ?

</div>

<div v-click class="mt-4 text-base">

**2 · La piste** — des rectangles régulièrement espacés qui traversent **toute** la fenêtre, quel que soit `sizeX` : l'espacement est déduit (cours 01), la répétition est une boucle (cours 02).

</div>

<!--
Ex 1 : cinq cercles sur une ligne, de plus en plus gros, espacés de 80.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 02
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · La cible, en boucle** — reprends la cible du cours 01 : des cercles concentriques au centre, en une **seule boucle**. Le rayon descend à chaque tour, et une composante de couleur glisse (comme `b`).

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Deux boucles, deux styles** — dans le même `draw()` : une rangée horizontale écrite en style *accumulé*, puis une diagonale écrite en style *tout depuis `i`*, sans aucune variable accumulée.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/02-boucle-for.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/02-boucle-for.md" download>md</a> · <a href="/ressources/ofApp02.h" download>ofApp02.h</a> · <a href="/ressources/ofApp02.cpp" download>ofApp02.cpp</a></p>

<!--
Ex 3 : même dessin que la cible du 01, code divisé par cinq.
-->
---
layout: split
breadcrumb: 1 — Les bases / Cours 03
---

# Cours 03 — L'aléatoire

Un dessin fait uniquement de règles est trop régulier.
Le hasard casse la régularité — mais le hasard, dans
un programme qui redessine 60 fois par seconde,
réserve une surprise.

<div class="mt-6 text-base">

<v-click>

Ce cours commence par un **bug volontaire**.

</v-click>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/03-aleatoire.png" alt="Cercles aléatoires, rangée, colonne, diagonale" class="w-full object-contain" />
</div>

<!--
Lancer la version sans graine EN PREMIER : le scintillement est la surprise
pédagogique du cours.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 03
---

# Étape 1 — cinquante cercles au hasard (et un bug)

```cpp
void ofApp::draw() {
	ofFill();
	ofSetColor(255);

	for (int i = 0; i < 50; i++) {
		float x = ofRandom(0, 800);
		float y = ofRandom(0, 800);
		float taille = ofRandom(10, 50);
		ofDrawCircle(x, y, taille / 2);
	}
}
```

<div class="mt-3 text-base">

<v-clicks>

- `ofRandom(a, b)` : un `float` au hasard entre `a` et `b` — nouveau à chaque appel
- Les variables sont créées **dans** la boucle, exprès : trois nouveaux tirages par tour
- Lance : les cercles **sautent partout** — ce n'est pas un accident, c'est la leçon

</v-clicks>

</div>

<!--
Essaie : couleur aléatoire par cercle (trois ofRandom dans un ofSetColor) —
le scintillement devient un feu d'artifice.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 03
---

# Pourquoi ça scintille

<div class="mt-6 text-base">

<v-clicks>

- `draw()` tourne 60 fois par seconde — et chaque exécution tire cinquante **nouvelles** positions
- Un programme ne fait pas la différence entre « un dessin fixe » et « un dessin refait à l'identique »
- Dès qu'il y a du hasard, il faut choisir : le **fixer**, ou le **stocker**

</v-clicks>

</div>

<!--
Le concept central du cours. La solution « fixer » arrive tout de suite ;
« stocker » est pour le cours 04.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 03
---

# Étape 2 — fixer le hasard : la graine

```cpp
void ofApp::draw() {
	ofSeedRandom(42);        // même graine → même suite → même dessin
	// ... les cinquante tirages redonnent les mêmes valeurs
```

<div class="mt-5 text-base">

<v-clicks>

- L'ordinateur ne tire pas vraiment au hasard : il calcule une suite qui **en a l'air**, à partir de la **graine**
- Remise à 42 à chaque `draw()`, la suite redonne les mêmes valeurs : le dessin est stable
- 43 ? Un autre dessin, tout aussi stable — la graine est un **numéro de dessin**

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/03-graine.png" alt="Même graine, même suite, même dessin" class="w-full object-contain" />
</div>

<!--
Essaie : ofSeedRandom(mouseX) — pourquoi le dessin change-t-il en bougeant ?
Puis : tout déplacer dans setup() sans graine — pourquoi pas encore la bonne
solution ? (→ cours 04 : stocker.)
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 03
---

# Étape 3 — la boucle à pas

```cpp
	ofSetColor(0, 0, 255);
	for (int i = 0; i < 50; i += 5) {
		ofDrawCircle(i * 16, 100, i / 2.0f);
	}
```

<div class="mt-5 text-base">

<v-clicks>

- Le troisième morceau du `for` est libre : `i += 5` — le compteur vaut 0, 5, 10, … 45, dix tours au lieu de cinquante
- Le `i / 2.0f` : `i` est un entier, `i / 2` serait une division entière (cours 01)

</v-clicks>

</div>

<!--
Essaie : un pas de 2, puis de 10 — prédire le nombre de cercles avant de
lancer.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 03
---

# Étape 4 — lire un dessin comme une formule

```cpp
	ofSetColor(255, 0, 0);                    // colonne rouge, de bas en haut
	for (int i = 0; i < 50; i++) {
		ofDrawCircle(200, 800 - i * 16, i / 2.0f);
	}

	ofSetColor(255, 255, 0);                  // et celle-ci... devine !
	for (int i = 0; i < 50; i++) {
		float taille = ofRandom(5, 40);
		ofDrawCircle(i * 16, 800 - i * 16, taille / 2);
	}
```

<div class="mt-3 text-base">

<v-clicks>

- `800 - i * 16` : on part du bas et on remonte — le rayon grandit avec `i`
- Avant de lancer la deuxième boucle : **devine son dessin** depuis sa formule
- Prédire le dessin depuis la formule, et la formule depuis le dessin voulu : **l'essentiel de ce cours**

</v-clicks>

</div>

<!--
La deuxième : diagonale jaune montante, tailles au hasard. Essaie : la
formule d'une ligne en bas, cercles grossissant vers la gauche.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 03
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — sur papier ou dans Paint, dessine ce que produisent ces deux boucles, puis vérifie :

```cpp
for (int i = 0; i < 40; i += 4) {
	ofDrawCircle(400, i * 20, 5 + i);
}
for (int i = 0; i < 10; i++) {
	ofDrawCircle(i * 80, i * 40, 10);
}
```

</div>

<div v-click class="mt-4 text-base">

**2 · La constellation** — fond noir, une centaine de petites étoiles blanches au hasard, plus une dizaine de grosses (deux boucles, deux plages de tailles). Choisis ta graine préférée : c'est **ton** ciel, il doit rester immobile.

</div>

<!--
Ex 1 : une colonne de cercles grossissants (pas de 4), puis une diagonale
douce de petits cercles.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 03
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · L'herbe** — une centaine de rectangles verts fins et verticaux, alignés sur le **bas** de la fenêtre, de hauteurs aléatoires. Piège : pour que le bas soit aligné, le `y` du rectangle se **déduit** de sa hauteur.

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Le désordre croissant** — une rangée de cercles de gauche à droite, dont la position verticale s'éparpille de plus en plus : `float y = 400 + ofRandom(-i * 4, i * 4);`. Sages à gauche, chaotiques à droite — la règle et le hasard dans la même formule.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<!--
Ex 3 : y = 800 - hauteur. La suite : l'Autonomie, deux diapos.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 03
---

# Autonomie — le carré de cercles

<div class="mt-3 text-base">

Un exercice à faire **seul**, avec les cours 01 à 03 : dessine **quatre lignes de dix cercles** qui forment un carré. Le long de chaque ligne, la taille et la couleur changent progressivement :

| Ligne | Départ | Arrivée |
|---|---|---|
| haut, de gauche à droite | petits cercles noirs | gros cercles rouges |
| droite, de haut en bas | gros cercles rouges | petits cercles magenta |
| bas, de droite à gauche | petits cercles magenta | gros cercles blancs |
| gauche, de bas en haut | gros cercles blancs | petits cercles noirs |

</div>

<div v-click class="mt-3 text-base">

Le dernier cercle d'une ligne a la même taille et la même couleur que le premier de la suivante : **le tour est continu**, et il se referme sur le noir de départ.

</div>

<!--
Le premier vrai travail en autonomie : prévoir du temps. Le 08 sera le
corrigé d'un exercice similaire au 07.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 03
---

# Autonomie — ce qu'on attend

<div class="mt-4 text-base">

<v-clicks>

- Quatre boucles `for` à la suite, une par côté, dix tours chacune
- Une taille et une couleur qui **s'accumulent** dans la boucle, comme au cours 02
- Le sens de parcours change à chaque côté : la position augmente sur deux côtés, diminue sur les deux autres
- Les couleurs évoluent **canal par canal** : noir `(0,0,0)`, rouge `(255,0,0)`, magenta `(255,0,255)`, blanc `(255,255,255)` — d'un coin au suivant, un seul canal change (sauf le dernier côté : les trois descendent)

</v-clicks>

</div>

<div v-click class="mt-4 text-base">

**La méthode** : avant d'écrire la deuxième boucle, fais marcher la première parfaitement. Avant chaque ligne de code, décide **sur papier** de combien la taille et la couleur changent par tour pour arriver juste au dixième cercle.

</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/03-aleatoire.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/03-aleatoire.md" download>md</a> · <a href="/ressources/ofApp03.h" download>ofApp03.h</a> · <a href="/ressources/ofApp03.cpp" download>ofApp03.cpp</a></p>

<!--
Circuler pendant l'autonomie. Erreurs types : les raccords aux coins, et
les pas de couleur mal calculés (255 / 9 par tour, pas 255 / 10).
-->
---
layout: split
breadcrumb: 1 — Les bases / Cours 04
---

# Cours 04 — Les listes

Une variable contient **un** nombre. Pour cinquante
positions, il faudrait cinquante variables. Une liste
en contient autant qu'on veut, sous un seul nom.

<div class="mt-4 text-sm">

<v-clicks>

- Ce cours affiche surtout du **texte** : console et fenêtre
- À la fin : la **vraie** solution du scintillement du cours 03

</v-clicks>

</div>

::right::

<div>
<img src="/ressources/cours/img/04-vector.png" alt="Liste de prénoms avec indices 0 à 8" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">Le premier élément est à l'indice 0, le dernier à size() − 1.</p>
</div>

<!--
La console est visible en configuration Debug dans Visual Studio.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# Étape 1 — `std::vector`, le type liste

```cpp
class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	std::vector<std::string> noms;
	std::vector<int> chiffres;
};
```

<div class="mt-4 text-base">

<v-clicks>

- Entre les chevrons `< >` : le **type des éléments** — une liste ne mélange pas les types
- Une liste fraîchement déclarée est **vide**

</v-clicks>

</div>

<!--
Essaie : déclarer une troisième liste std::vector<float> rayons; pour plus
tard.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 04
---

# Pourquoi dans le `.h` ?

<div class="mt-6 text-base">

<v-clicks>

- Une variable du `.h` est **partagée** : visible dans `setup()`, `update()` et `draw()`
- Et **vivante** pendant toute la vie du programme
- On remplira dans `setup()`, on lira dans `draw()` : les listes doivent **survivre entre les deux**
- C'est la suite de « où tu déclares décide de la durée de vie » (cours 02)

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/04-trajet-listes.png" alt="Déclarer dans le .h, remplir dans setup, lire dans draw" class="w-full object-contain" />
</div>

<!--
Première fois que le .h porte l'essentiel : le faire remarquer.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# Étape 2 — la console

```cpp
void ofApp::setup() {
	ofSetWindowShape(400, 400);
	ofBackground(30);

	int x { 50 };
	std::string nom = "Gaetan";

	std::cout << x << std::endl;
	std::cout << "Hello " + nom << std::endl;
}
```

<div class="mt-3 text-base">

<v-clicks>

- `std::cout << ... << std::endl;` : les `<<` s'enchaînent, `endl` termine la ligne
- `std::string` : le type **texte**, entre guillemets — le `+` colle deux textes
- La console est un **outil de travail** : un dessin qui déraille ? **Affiche tes variables**

</v-clicks>

</div>

<!--
Essaie : afficher pi, x + pi, une phrase qui les mélange. La console servira
toute l'année pour enquêter.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# Étape 3 — remplir : `push_back`

```cpp
	noms.push_back("Annie");
	noms.push_back("Brand");
	noms.push_back("Callista");
	// ... jusqu'à 9
```

<div class="mt-5 text-base">

<v-clicks>

- `push_back(...)` ajoute **à la fin** de la liste
- La syntaxe avec le point — `variable.action(...)` : certains types embarquent leurs actions, tu la reverras partout

</v-clicks>

</div>

<!--
L'image des indices est sur la diapo d'intro (et dans le document).
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# Lire : les indices

```cpp
	std::cout << noms[1] << std::endl;                 // Brand
	std::cout << noms[0] << std::endl;                 // Annie
	std::cout << noms[noms.size() - 1] << std::endl;   // le dernier
```

<div class="mt-5 text-base">

<v-clicks>

- `noms[i]` lit l'élément numéro `i` — **le premier est le numéro 0**
- `noms.size()` compte ; le dernier est à `size() - 1`
- Lire `noms[9]` dans une liste de 9 : C++ **ne vérifie pas** — n'importe quoi, ou plantage. Rester dans les bornes est **ta** responsabilité

</v-clicks>

</div>

<!--
Essaie : le troisième prénom, puis l'avant-dernier (déduit de size()).
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# Étape 4 — parcourir : LE motif de l'année

```cpp
	for (int i = 0; i < 10; i++) {
		chiffres.push_back(i);             // remplir avec une boucle
	}

	for (int i = 0; i < chiffres.size(); i++) {
		std::cout << chiffres[i] << " ";   // parcourir
	}
```

<div class="mt-5 text-base">

<v-clicks>

- La boucle du cours 02 avec `size()` comme limite : `i` va de 0 au dernier indice, exactement
- « **Pour chaque élément de la liste** » : le motif le plus fréquent de tout le C++ que tu écriras cette année

</v-clicks>

</div>

<!--
Le marteler. Essaie : un prénom sur deux (i += 2 ou noms[i * 2] — lequel
risque de sortir ?) ; la somme des chiffres, accumulée puis affichée.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# Étape 5 — écrire dans la fenêtre

```cpp
void ofApp::draw() {
	ofSetColor(255);
	for (int i = 0; i < noms.size(); i++) {
		ofDrawBitmapString(ofToString(i) + " : " + noms[i], 20, 30 + i * 20);
	}
}
```

<div class="mt-5 text-base">

<v-clicks>

- `ofDrawBitmapString(texte, x, y)` écrit dans la fenêtre — position du **bas** de la première lettre, pas d'accents
- Un **nombre** dans un texte ? `ofToString(nombre)` d'abord
- La console, c'est pour toi ; la fenêtre, c'est pour le public

</v-clicks>

</div>

<!--
Dans le document : la phrase qui s'allonge (accumulation de texte, cours 02).
Essaie : espacer de 30, décaler la colonne — combien de nombres changés ?
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# Étape 6 — le retour sur le cours 03

```cpp
void ofApp::setup() {
	for (int i = 0; i < 50; i++) {
		xs.push_back(ofRandom(0, 800));     // on tire UNE fois...
		ys.push_back(ofRandom(0, 800));
	}
}

void ofApp::draw() {
	ofSetColor(255);
	for (int i = 0; i < xs.size(); i++) {
		ofDrawCircle(xs[i], ys[i], 10);     // ...et on dessine autant qu'on veut
	}
}
```

<div class="mt-3 text-base">

<v-clicks>

- Le hasard est **stocké** : plus de graine, plus de scintillement
- Le geste le plus important du cours : **déclarer dans le `.h`, remplir dans `setup()`, lire dans `draw()`**

</v-clicks>

</div>

<!--
xs[i] et ys[i] forment la position i : deux listes en paires, à modifier
toujours ensemble (le cours 07 en reparle). Essaie : la liste rayons.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — qu'affiche la console ? Réponds avant de taper :

```cpp
std::vector<int> v;
for (int i = 0; i < 5; i++) {
	v.push_back(i * i);
}
std::cout << v[2] << " " << v[v.size() - 1] << std::endl;
```

</div>

<div v-click class="mt-4 text-base">

**2 · La constellation, propre** — reprends la constellation du cours 03 (petites et grosses étoiles) avec des **listes** : tout est tiré dans `setup()`, plus aucune graine. Le ciel est immobile *par construction*.

</div>

<!--
Ex 1 : « 4 16 » — la liste contient 0 1 4 9 16.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · Le générique** — une liste avec les prénoms de ta rangée, affichés en colonne numérotée dans la fenêtre. Ajoute un prénom au milieu du code : la numérotation et la mise en page doivent suivre **toutes seules** (aucun autre changement).

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **La moyenne** — remplis une liste avec dix nombres aléatoires entre 0 et 100, affiche-les, puis calcule et affiche leur **moyenne**. Piège : `somme / chiffres.size()` cache une division entière (cours 01) — obtiens une vraie moyenne à virgule.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/04-listes.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/04-listes.md" download>md</a> · <a href="/ressources/ofApp04.h" download>ofApp04.h</a> · <a href="/ressources/ofApp04.cpp" download>ofApp04.cpp</a></p>

<!--
Ex 4 : somme / (float)chiffres.size(), ou une somme en float.
-->
---
layout: split
breadcrumb: 1 — Les bases / Cours 05
---

# Cours 05 — Le cycle et la souris

Un cercle qui suit la souris. Le programme est minuscule,
mais il met en place l'organisation qu'on garde
jusqu'à la fin de l'année :

<div class="mt-6 text-base">

<v-clicks>

- `update()` **calcule** — aucun appel de dessin
- `draw()` **dessine** — aucun calcul

</v-clicks>

</div>

::right::

<div>
<img src="/ressources/cours/img/05-cycle.png" alt="setup une fois, puis update et draw en boucle" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">setup() une fois, puis update() et draw(), 60 fois par seconde.</p>
</div>

<!--
Tout mettre dans draw() marcherait — mais séparer rend le code lisible :
quand un dessin est faux, on sait si l'erreur est calcul ou affichage.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 05
---

# Étape 1 — le programme entier

```cpp
// ofApp.h :   float x { 0 };   float y { 0 };

void ofApp::update() {
	x = mouseX;
	y = mouseY;
}

void ofApp::draw() {
	ofBackground(255, 0, 0);
	ofSetColor(255);
	ofFill();
	ofDrawCircle(x, y, 50);
}
```

<div class="mt-3 text-base">

<v-clicks>

- Un cercle blanc suit la souris, sur fond rouge
- Les rôles sont respectés : `update()` calcule la position, `draw()` la dessine

</v-clicks>

</div>

<!--
Essaie : un décalage — x = mouseX + 100.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 05
---

# Des variables qui traversent les frames

<div class="mt-6 text-base">

<v-clicks>

- `x` est **écrite** dans `update()`, **lue** dans `draw()` : deux blocs → elle doit être **partagée** (le `.h`, cours 04)
- Elle est aussi **persistante** : sa valeur reste d'une frame à l'autre — c'est ce qui permettra au cours 06 d'avancer *petit à petit*
- `mouseX` et `mouseY` : deux variables partagées fournies par openFrameworks, mises à jour toutes seules

</v-clicks>

</div>

<!--
Essaie : y fixe à 200 (horizontale seule) ; rayon = mouseX / 4.0f calculé
dans update().
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 05
---

# Étape 3 — effacer avant de redessiner

```cpp
	ofBackground(255, 0, 0);     // en PREMIÈRE ligne de draw()
```

<div class="mt-5 text-base">

<v-clicks>

- Enlève cette ligne et bouge la souris : les cercles s'accumulent en **traînée**
- `ofBackground` en début de `draw()` efface la frame précédente — un fond propre à chaque image
- La traînée est parfois ce qu'on **veut** (le cours 18 peindra avec) : un choix, pas un accident
- Au cours 01 il était dans `setup()` — **dès que ça bouge, il va dans `draw()`**

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/05-trainee.png" alt="Sans ofBackground : traînée ; avec : fond propre" class="w-full object-contain" />
</div>

<!--
Essaie : ofBackground à la FIN de draw() — tout disparaît. Pourquoi ?
L'ordre DANS draw compte : on a peint par-dessus le cercle.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 05
---

# Relire le cours 00 avec les bons mots

<div class="mt-6 text-base">

<v-clicks>

- `funnyFace` : une fonction à nous, annoncée dans le `.h`, avec deux paramètres
- `draw()` : efface avec `ofBackground(30)`, puis dessine la tête à `(mouseX, mouseY)`
- `update()` y était resté **vide** — tu sais maintenant à quoi il sert : dès le cours 06, il fera bouger les choses tout seul

</v-clicks>

</div>

<!--
La boucle est bouclée : plus aucun mystère dans ofApp00a.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 05
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — décris ce que fait ce programme avant de le taper :

```cpp
void ofApp::update() {
	x = mouseX;
	y = 300;
}

void ofApp::draw() {
	ofBackground(30);
	ofDrawCircle(x, y, mouseY / 4.0f);
}
```

Sur quelle trajectoire le cercle se déplace-t-il ? Qu'est-ce qui le fait grossir ?

</div>

<div v-click class="mt-4 text-base">

**2 · L'opposé** — le cercle va à l'inverse de la souris : souris à droite, cercle à gauche (et pareil verticalement). Indice : `ofGetWidth()` et `ofGetHeight()` donnent la taille de la fenêtre.

</div>

<!--
Ex 1 : le cercle glisse sur la ligne horizontale y = 300, et grossit quand
la souris descend. Ex 2 : x = ofGetWidth() - mouseX.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 05
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · Le kaléidoscope** — quatre cercles à la fois : la souris, son symétrique horizontal, son symétrique vertical, et le symétrique des deux. Bouge la souris : les quatre dansent ensemble.

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Le pinceau** — enlève `ofBackground`, et fais de la traînée un outil : le cercle suit la souris, et son rayon vaut `mouseY / 10.0f` — plus la souris est basse, plus le trait est épais. Tu viens d'écrire ton premier logiciel de dessin.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/05-cycle-souris.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/05-cycle-souris.md" download>md</a> · <a href="/ressources/ofApp05.h" download>ofApp05.h</a> · <a href="/ressources/ofApp05.cpp" download>ofApp05.cpp</a></p>

<!--
Ex 3 : les quatre = (mx,my), (W-mx,my), (mx,H-my), (W-mx,H-my).
-->

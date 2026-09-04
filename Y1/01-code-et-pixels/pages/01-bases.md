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

Aujourd'hui on n'explique presque rien : on lance un programme
qui dessine, on change des nombres, on relance, on regarde.

<div class="mt-6 text-sm">

<v-clicks>

- L'écran est un **quadrillage de pixels**
- Une ligne de code est un **appel de fonction**
- Une couleur, c'est **quatre nombres**

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/00-visage.png" alt="Tête blanche translucide aux yeux rouges" class="w-full object-cover" />
<p class="mt-2 text-xs op-60">Deux versions : la tête (ofApp00), puis la tête qui suit la souris (ofApp00a).</p>
</div>

<!--
Le contrat de la séance : personne n'est censé comprendre, tout le monde est
censé OBSERVER. On modifie des nombres, on prédit, on relance.
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

# Lire une ligne de code

```cpp
ofDrawCircle(200 + x, 200 + y, 225);   // un appel de fonction : « dessine un cercle »
ofSetColor(255, 0, 0, 150);            // rouge, vert, bleu, opacité (0-255)
```

<div class="mt-4 text-sm">

<v-clicks>

- `ofDrawCircle` — le **nom** de la fonction ; les fonctions de dessin commencent par `ofDraw`
- `( ... )` — les **paramètres** : les informations dont la fonction a besoin, séparés par des virgules
- `;` — termine l'appel ; sans lui, rien ne compile
- `// ...` — un **commentaire** : note pour les humains, ignorée par l'ordinateur
- La couleur choisie reste active pour **toutes les formes qui suivent**

</v-clicks>

</div>

<!--
L'anatomie d'un appel de fonction, une fois pour toutes. L'écran fabrique tout en
mélangeant de la lumière rouge, verte et bleue — (255,255,255) blanc,
(255,255,0) jaune. Le 4e nombre (opacité) est facultatif.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# `ofApp00` — dessiner le visage

```cpp
void ofApp::setup() {
    ofSetWindowShape(800, 800);      // taille de la fenêtre : essaie 400, 400
}

void ofApp::draw() {
    float x = 0;                     // deux VARIABLES : déplacent
    float y = 0;                     // toute la tête d'un coup

    ofSetColor(255, 255, 255, 255);              // le visage
    ofDrawCircle(200 + x, 200 + y, 225);
    ofDrawRectangle(100 + x, 200 + y, 250, 50);  // la bouche

    ofSetColor(255, 0, 0, 150);                  // les yeux — essaie (0, 255, 0)
    ofDrawCircle(55 + x, 75 + y, 50);
    ofDrawCircle(375 + x, 75 + y, 50);
}
```

<div class="mt-2 text-sm">

- La version **minimale** : rien ne bouge, on dessine une fois — et tout est déjà là
- `ofDrawCircle` est une **fonction** toute faite : on l'*appelle* en lui donnant des **paramètres** entre parenthèses
- `x` et `y` sont des **variables** : des nombres nommés — change `x` en 100, toute la tête se décale

</div>

<!--
Les trois concepts du module posés sur le plus petit programme possible :
appeler une fonction, lui passer des paramètres, nommer un nombre dans une
variable. Ne pas s'attarder sur setup/draw ici (cours 05), ni sur class/public
(« l'emballage, on le recopie tel quel pendant des semaines »).
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# `ofApp00a` — la version vivante : le `.h` et `setup()`

```cpp
// ofApp00a.h : la table des matières du programme
class ofApp : public ofBaseApp {
public:
    void setup();  void update();  void draw();
    void funnyFace(float x, float y);
    float r = 0;  float g = 0;  float b = 0;   // partagées entre les blocs
};

// ofApp00a.cpp
void ofApp::setup() {
    ofSetWindowShape(800, 800);
}
```

<div class="mt-3 text-sm">

<v-clicks>

- La deuxième version du même programme : la tête va **suivre la souris**, le fond va **changer tout seul**
- Le `.h` **liste** les blocs et les variables qui existent — une table des matières
- `r`, `g`, `b` y sont déclarées : elles seront **visibles dans tous les blocs**

</v-clicks>

</div>

<!--
Le passage ofApp00 → ofApp00a est la promesse du module : le même dessin,
plus trois variables et deux blocs, et ça devient vivant.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Étape `update()` — les nombres changent

```cpp
void ofApp::update() {
    float t = ofGetElapsedTimef();          // le temps écoulé, en secondes
    r = (cos(t * 1.5f)  / 2 + 0.5f) * 255;  // essaie 0.2f, puis 10.0f
    g = (cos(t * 0.75f) / 2 + 0.5f) * 255;
    b = (cos(t * 1.0f)  / 2 + 0.5f) * 255;
}
```

<div class="mt-4 text-sm">

<v-clicks>

- `update()` tourne **60 fois par seconde**, juste avant le dessin
- Il recalcule `r`, `g`, `b` à partir du temps : le fond changera tout seul
- La formule avec `cos` reste un **mystère assumé** — elle sera expliquée aux cours 06 et 13. Aujourd'hui : changez `1.5f` et regardez

</v-clicks>

</div>

<!--
Assumer le mystère à voix haute : « vous n'avez pas à comprendre cette ligne
aujourd'hui, seulement à voir ce qu'elle fait quand on la modifie ».
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Étape `funnyFace()` — notre propre fonction

```cpp
void ofApp::funnyFace(float x, float y) {
    ofSetColor(255, 255, 255, 100);        // blanc à moitié transparent
    ofDrawCircle(200 + x, 200 + y, 225);   // le visage
    ofDrawRectangle(100 + x, 200 + y, 250, 50);   // la bouche

    ofSetColor(255, 0, 0, 150);            // essaie (0, 255, 0)
    ofDrawCircle(55 + x, 75 + y, 50);      // les yeux
    ofDrawCircle(375 + x, 75 + y, 50);
}
```

<div class="mt-4 text-sm">

<v-clicks>

- Une fonction **fabriquée par nous** : « dessine une tête autour du point (x, y) »
- Toutes les positions sont écrites **par rapport à `(x, y)`** — c'est ce qui rend la tête déplaçable
- On apprendra à en écrire au cours 07 ; aujourd'hui on le lit et on le modifie

</v-clicks>

</div>

<!--
À faire en séance, dans ce bloc : ajouter deux yeux (ofDrawCircle), un nez
(ofDrawRectangle — attention, x,y est le coin haut-gauche pour un rectangle).
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# Étape `draw()` — on dessine

```cpp
void ofApp::draw() {
    ofBackground(r, g, b);          // remplace par ofBackground(0) : fond noir fixe
    funnyFace(mouseX, mouseY);      // remplace par 100, 100 : que se passe-t-il ?
}
```

<div class="mt-4 text-sm">

<v-clicks>

- `draw()` tourne 60 fois par seconde, **juste après** `update()`
- `ofBackground` peint tout : le fond prend la couleur calculée dans `update()`
- `mouseX` et `mouseY` : deux nombres mis à jour tout seuls — la position de la souris, utilisable partout où un nombre est attendu

</v-clicks>

</div>

<div v-click class="mt-5 text-base">
<b>Prédire avant de relancer</b> : c'est le geste de la séance.
</div>


<!--
Le tableau des expériences est dans le document : rapetisser fenêtre/tête/
yeux, changer couleurs et opacité, funnyFace(100,100), fond noir fixe,
accélérer le fond. Chacune : prédire, lancer, constater.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 00
---

# À vous — compléter la tête

<div class="mt-6 text-base">

<v-clicks>

- **1 · Ajoute deux oreilles** en haut du visage : deux `ofDrawCircle` — et une couleur avant
- **2 · Ajoute un nez** avec `ofDrawRectangle(x, y, largeur, hauteur)` — piège : `x, y` est le coin haut-gauche, pas le centre
- **3 · Décale la tête** par rapport à la souris : `funnyFace(mouseX + 200, mouseY)`

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
À chaque fois : <b>prédire, lancer, constater</b>. La suite des expériences est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/00-premier-contact.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/00-premier-contact.md" download>md</a> · <a href="/ressources/ofApp00.h" download>ofApp00.h</a> · <a href="/ressources/ofApp00.cpp" download>ofApp00.cpp</a> · <a href="/ressources/ofApp00a.h" download>ofApp00a.h</a> · <a href="/ressources/ofApp00a.cpp" download>ofApp00a.cpp</a></p>

<!--
Exercices 1, 2 et 4 du document. Circuler dans la salle : l'erreur type est
d'oublier le + x, + y (l'oreille ne suit plus la tête).
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 01
---

# Cours 01 — Variables et opérations

Au cours 00, tous les nombres étaient écrits en dur.
Pour construire un dessin, il faut pouvoir **nommer**
des nombres et les **calculer** à partir d'autres.

<div class="mt-4 text-sm">

| | |
|---|---|
| `int` | un nombre **entier** : `-3`, `0`, `400` |
| `float` | un nombre **à virgule** : `37.5f` — avec le `f` |

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/01-cercles.png" alt="Un cercle et une rangée de cercles" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">Des positions déduites de la taille de la fenêtre.</p>
</div>

<!--
Une variable = une boîte avec un type (fixé une fois pour toutes), un nom,
une valeur. Prendre l'habitude du f : 37.5f.
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
- `int sizeX = 400;` fait trois choses : **réserve** une case, lui donne un **nom**, y range une **valeur**
- Le **type** est la règle de la case : ce qu'elle peut contenir, et comment lire ce qu'il y a dedans — fixé une fois pour toutes
- Le nom n'existe que pour nous : à la fin, le programme ne connaît que des numéros de case

</v-clicks>

</div>

<!--
L'image mentale qui sert toute l'année : lire une variable = ouvrir la case,
l'affecter = remplacer son contenu. Les cases grises : la mémoire ne nous
appartient pas toute — d'où l'importance de déclarer.
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

- L'`int` **compte** en binaire : exact, mais borné — sur 4 octets, jusqu'à ±2 147 483 647 environ
- Le `float` range une **notation scientifique en binaire** : une plage énorme, mais un nombre limité de chiffres significatifs (environ 7)
- Conséquence : beaucoup de nombres à virgule sont stockés **en arrondi** — 0.1 n'est pas exactement 0.1. Pour des pixels, on s'en moque ; pour comparer deux `float` avec `==`, jamais
- C'est pour distinguer ces deux rangements que C++ exige le type — et le `f` de `37.5f` dit « range-moi en `float` »

</v-clicks>

</div>

<!--
37.5 = 100101,1 en binaire = 1,001011 × 2⁵ — même geste que la notation
scientifique de l'école. Ne pas entrer dans IEEE 754 : l'idée signe/exposant/
chiffres suffit. La division entière du prochain écran découle du premier
point : un int ne PEUT pas contenir 0,75.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# Étape `draw()` (1/2) — nommer et calculer

```cpp
void ofApp::draw() {
    int sizeX = 400;                 // deux variables pour la taille de l'écran
    int sizeY = 400;

    float x = sizeX / 2.0f;          // le milieu de la largeur : 200
    float y = sizeY * 3 / 4.0f;      // les trois quarts de la hauteur : 300

    ofSetColor(255);
    ofFill();
    ofDrawCircle(x, y, 37.5f);       // RAYON, pas diamètre !
}
```

<div class="mt-3 text-sm">

<v-clicks>

- `x` et `y` ne sont plus devinés : ils sont **déduits** — passe `sizeX` à 800, le cercle reste au milieu
- **Piège n°1** : `3 / 4` vaut **0** — entier divisé par entier, C++ jette la virgule. Le remède : `4.0f`
- **Piège n°2** : le 3ᵉ nombre de `ofDrawCircle` est le **rayon** — un cercle de 75 de large a un rayon de 37,5

</v-clicks>

</div>

<!--
Les deux pièges reviendront toute l'année. Un calcul qui donne 0 sans raison ?
Division entière. setup() du cours : ofSetWindowShape(400,400) + ofBackground(200).
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# Étape `draw()` (2/2) — la répétition manuelle

```cpp
    x = 0;                          // la boîte existe déjà : pas de "float"
    float step = 75;
    y = sizeY * 1 / 4.0f;
    ofDrawCircle(x, y, 37.5f);
    x = x + step;                   // « = » veut dire « reçoit »
    ofDrawCircle(x, y, 37.5f);
    x = x + step;
    ofDrawCircle(x, y, 37.5f);
    x = x + step;
    // ... encore 7 fois
```

<div class="mt-3 text-sm">

<v-clicks>

- `x = x + step;` n'est pas une équation : c'est une **instruction** — « calcule, puis range le résultat dans `x` »
- Espacer de 50 au lieu de 75 : **une seule ligne** à changer — la force des variables
- Mais en vouloir 30 : **quarante lignes de plus** — leur limite. La boucle `for` règle ça au cours suivant

</v-clicks>

</div>


<!--
Exercices du document : espacer de 50 puis 25, variable rayon commune,
7/2 vs 7/2.0f, centrer un cercle avec sizeX/sizeY seulement.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 01
---

# À vous — tout déduire

<div class="mt-6 text-base">

<v-clicks>

- **1 · Espace les cercles de 50**, puis de 25 — combien de lignes as-tu changées ?
- **2 · Une variable `float rayon = 37.5f;`** utilisée par tous les cercles : change-la, tout grandit ensemble
- **3 · Un cercle exactement au centre** de la fenêtre, en n'utilisant que `sizeX` et `sizeY`

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
À chaque fois : <b>prédire, lancer, constater</b>. L'exercice 3 du document fait toucher du doigt la division entière.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/01-variables.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/01-variables.md" download>md</a> · <a href="/ressources/ofApp01.h" download>ofApp01.h</a> · <a href="/ressources/ofApp01.cpp" download>ofApp01.cpp</a></p>

<!--
Le n°3 révèle qui a compris « déduit » : sizeX / 2.0f, pas 200 écrit en dur.
Redimensionner mentalement la fenêtre pour vérifier.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 02
---

# Cours 02 — La boucle `for`

« Répète ce bloc dix fois » — et comme on peut changer
des variables à chaque tour, les dix cercles peuvent
tous être différents.

```cpp
for (int i = 0; i < 10; i++) {
    // exécuté 10 fois, i de 0 à 9 — jamais 10
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
10 < 10 est faux, on sort. Et i n'existe que dans la boucle.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 02
---

# Étape `draw()` — accumuler à chaque tour

```cpp {1-4|6-15|16-19}
    float x = 0;                    // créées AVANT la boucle :
    float y = 0;                    // elles gardent leur valeur
    float taille = 10;              // de tour en tour
    int   b = 0;

    for (int i = 0; i < 10; i++) {
        ofFill();                            // 1) le remplissage
        ofSetColor(255, 0, b, 180);
        ofDrawCircle(x, y, taille / 2);

        ofNoFill();                          // 2) le contour
        ofSetColor(255, 150, 0);
        ofDrawCircle(x, y, taille / 2);

        x = x + 40;
        y = y + 40;
        taille = taille + 20;
        b = b + 25;
    }
```

<div class="mt-2 text-sm">

- Créées **dans** la boucle, ces variables repartiraient de zéro : dix cercles au même endroit
- Remplissage **et** contour = dessiner deux fois, `ofFill()` puis `ofNoFill()`
- La couleur aussi est une variable : `b` grimpe de 25 par tour, du rouge pur au presque violet

</div>


<!--
Trois clics = trois zones du code en surbrillance : les variables accumulées,
les deux passes de dessin, l'accumulation de fin de tour.
Le dernier cercle sort de l'écran : rien ne plante, c'est juste invisible.
Exercices : i < 20, sens inversé, varier le vert, tout recalculer depuis i.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 02
---

# À vous — la boucle aux commandes

<div class="mt-6 text-base">

<v-clicks>

- **1 · `i < 20`** — puis fais tenir les vingt cercles dans la fenêtre : quel nombre changer ?
- **2 · Inverse le sens** : les cercles partent d'en haut à droite et descendent vers la gauche
- **3 ·** 🔥 Supprime les variables accumulées — **tout se calcule depuis `i`**

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
À chaque fois : <b>prédire, lancer, constater</b> · <b>🔥</b> = exercice avancé · les autres variantes (couleurs) sont dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/02-boucle-for.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/02-boucle-for.md" download>md</a> · <a href="/ressources/ofApp02.h" download>ofApp02.h</a> · <a href="/ressources/ofApp02.cpp" download>ofApp02.cpp</a></p>

<!--
Le n°3 est le pont vers le cours 03 (lire un dessin comme une formule) :
x = i * 40, taille = 10 + i * 20, b = i * 25.
-->

---
layout: split
breadcrumb: 1 — Les bases / Cours 03
---

# Cours 03 — L'aléatoire

Un dessin fait uniquement de règles est trop régulier.
Le hasard casse la régularité — mais dans un programme
qui redessine 60 fois par seconde, il réserve une surprise.

<div class="mt-6 text-sm">

<v-clicks>

- Sans précaution : les cercles **scintillent** — 50 nouveaux tirages à chaque frame
- Un programme ne distingue pas « dessin fixe » et « dessin refait à l'identique »
- Fixer le hasard, ou le stocker : il faut **choisir**

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/03-aleatoire.png" alt="Cercles aléatoires, rangée, colonne, diagonale" class="w-full object-contain" />
</div>

<!--
Lancer d'abord SANS ofSeedRandom pour montrer le scintillement — c'est la
surprise pédagogique du cours.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 03
---

# Étape `draw()` (1/2) — la graine, puis le hasard

```cpp
void ofApp::draw() {
    ofSeedRandom(42);        // même graine → même suite → dessin stable

    ofFill();
    ofSetColor(255);
    for (int i = 0; i < 50; i++) {
        float x = ofRandom(0, 800);          // un float au hasard entre 0 et 800
        float y = ofRandom(0, 800);
        float taille = ofRandom(10, 50);
        ofDrawCircle(x, y, taille / 2);
    }
```

<div class="mt-3 text-sm">

<v-clicks>

- L'ordinateur ne tire pas vraiment au hasard : il calcule une suite qui **en a l'air**, à partir de la **graine** — 43 donne un autre dessin, tout aussi stable
- Ici les variables sont créées **dans** la boucle, exprès : on veut 50 tirages, pas une accumulation
- C'est la solution rapide — la propre (tirer une fois, stocker dans une liste) arrive au cours 04

</v-clicks>

</div>

<!--
La graine est un « numéro de dessin ». Exercice 1 du document :
ofSeedRandom(mouseX) — le dessin change en bougeant la souris. Pourquoi ?
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 03
---

# Étape `draw()` (2/2) — lire un dessin comme une formule

```cpp
    ofSetColor(0, 0, 255);                    // ligne bleue, de 5 en 5
    for (int i = 0; i < 50; i += 5) {
        ofDrawCircle(i * 16, 100, i / 2.0f);
    }

    ofSetColor(255, 0, 0);                    // colonne rouge, de bas en haut
    for (int i = 0; i < 50; i++) {
        ofDrawCircle(200, 800 - i * 16, i / 2.0f);
    }

    ofSetColor(255, 255, 0);                  // diagonale jaune, tailles au hasard
    for (int i = 0; i < 50; i++) {
        float taille = ofRandom(5, 40);
        ofDrawCircle(i * 16, 800 - i * 16, taille / 2);
    }
}
```

<div class="mt-2 text-sm">

- `i += 5` : le compteur avance de 5 en 5 — dix tours au lieu de cinquante
- `800 - i * 16` : on part du bas et on remonte ; le rayon `i / 2.0f` grandit (et le `2.0f` évite la division entière)
- **Prédire le dessin depuis la formule, et la formule depuis le dessin voulu : l'essentiel de ce cours**

</div>


<!--
Avant de lancer, faire deviner la diagonale jaune à partir de son code.
Ce cours porte l'AUTONOMIE « carré de quatre lignes de dix cercles »
(voir document) : tailles et couleurs qui se raccordent d'un côté à l'autre —
à préparer sur papier avant de coder.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 03
---

# À vous — le hasard apprivoisé

<div class="mt-6 text-base">

<v-clicks>

- **1 · `ofSeedRandom(mouseX)`** : prédis ce qui se passe quand la souris bouge — puis vérifie
- **2 · Chaque cercle blanc en couleur aléatoire** : trois `ofRandom(0, 255)` dans un `ofSetColor`, dans la boucle
- **3 ·** 🔥 **L'« Autonomie » du document** : le carré de quatre lignes de dix cercles — à préparer **sur papier** avant de coder

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
À chaque fois : <b>prédire, lancer, constater</b> · <b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/03-aleatoire.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/03-aleatoire.md" download>md</a> · <a href="/ressources/ofApp03.h" download>ofApp03.h</a> · <a href="/ressources/ofApp03.cpp" download>ofApp03.cpp</a></p>

<!--
Le n°1 : la graine change à chaque frame où la souris bouge → nouveau dessin,
stable dès qu'elle s'arrête. Le n°3 est le premier travail en autonomie —
prévoir du temps.
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

Ce cours affiche du texte plutôt que des formes :
des prénoms et des chiffres, dans la **console**
et dans la fenêtre.

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

# Le `.h` — des listes partagées

```cpp
class ofApp : public ofBaseApp {
public:
    void setup();
    void draw();

    std::vector<std::string> noms;      // une liste de textes
    std::vector<int> chiffres;          // une liste d'entiers
};
```

<div class="mt-4 text-sm">

<v-clicks>

- `std::vector` est le type « liste » ; entre les chevrons `< >`, le **type des éléments** — une liste ne mélange pas les types
- Déclarées dans le `.h`, elles sont **partagées** : remplies dans `setup()`, lues dans `draw()`, vivantes toute la vie du programme
- Une liste fraîchement déclarée est **vide**

</v-clicks>

</div>

<!--
C'est la première fois que le .h porte l'essentiel : le faire remarquer.
Où on déclare décide de la durée de vie (rappel du cours 02).
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# Étape `setup()` (1/2) — la console

```cpp
void ofApp::setup() {
    ofSetWindowShape(400, 400);
    ofBackground(30);

    int x = 50;
    float pi = 3.14159f;
    std::string nom = "Gaetan";          // le type « texte »

    std::cout << x << std::endl;         // affiche dans la console
    std::cout << "Hello " + nom << std::endl;   // + colle deux textes
```

<div class="mt-4 text-sm">

<v-clicks>

- `std::cout << ... << std::endl;` : les `<<` s'enchaînent, `endl` termine la ligne
- La console est un **outil de travail** : quand un dessin ne fait pas ce que tu veux, **affiche tes variables**
- Pour coller un nombre à un texte : `ofToString(nombre)`

</v-clicks>

</div>

<!--
print(x) devient std::cout — l'équivalent openFrameworks ofLogNotice() existe
aussi, même destination.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# Étape `setup()` (2/2) — remplir, lire, compter

```cpp
    noms.push_back("Annie");             // ajoute à la FIN
    noms.push_back("Brand");
    noms.push_back("Callista");
    // ... 6 autres

    std::cout << noms[1] << std::endl;                // Brand — le 1er est le 0 !
    std::cout << noms[noms.size() - 1] << std::endl;  // le dernier

    for (int i = 0; i < 10; i++) {
        chiffres.push_back(i);           // remplir avec une boucle
    }
    for (int i = 0; i < chiffres.size(); i++) {
        std::cout << chiffres[i] << " ";  // parcourir : LE motif de l'année
    }
```

<div class="mt-2 text-sm">

- La syntaxe `variable.action(...)` avec le point : certains types embarquent leurs actions — tu la reverras partout
- Lire `noms[9]` dans une liste de 9 : C++ **ne vérifie pas** — n'importe quoi, ou plantage. Rester entre 0 et `size() - 1` est ta responsabilité

</div>

<!--
« Pour chaque élément de la liste » : le motif le plus fréquent de tout le
C++ qu'ils écriront cette année. Le marteler.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# Étape `draw()` — écrire dans la fenêtre

```cpp
void ofApp::draw() {
    ofSetColor(255);
    for (int i = 0; i < noms.size(); i++) {
        ofDrawBitmapString(ofToString(i) + " : " + noms[i], 20, 30 + i * 20);
    }

    std::string ligne = "Chiffres : ";
    for (int i = 0; i < chiffres.size(); i++) {
        ligne = ligne + ofToString(chiffres[i]) + " ";   // la phrase s'allonge
    }
    ofDrawBitmapString(ligne, 20, 260);
}
```

<div class="mt-3 text-sm">

<v-clicks>

- `ofDrawBitmapString(texte, x, y)` écrit dans la fenêtre — position du **bas** de la première lettre, pas d'accents
- La phrase qui s'allonge : l'**accumulation** du cours 02, appliquée à du texte
- Retour sur le cours 03 : tirer les positions **une fois** dans `setup()`, dans des listes partagées, les dessiner dans `draw()` — plus besoin de `ofSeedRandom`

</v-clicks>

</div>


<!--
Le retour sur 03 est l'exercice 1 du document — à faire en séance. Autres :
liste des rayons, un prénom sur deux, somme et pairs de 1 à 20.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 04
---

# À vous — des listes à la place du hasard

<div class="mt-6 text-base">

<v-clicks>

- **1 · Reprends le cours 03** : positions tirées **une fois** dans `setup()`, rangées dans deux listes `xs`, `ys`, dessinées dans `draw()` — plus besoin de `ofSeedRandom`
- **2 · Une troisième liste** pour les rayons
- **3 · Dans la console** : la somme des entiers de 1 à 20, puis les pairs seulement

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
À chaque fois : <b>prédire, lancer, constater</b>. 
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/04-listes.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/04-listes.md" download>md</a> · <a href="/ressources/ofApp04.h" download>ofApp04.h</a> · <a href="/ressources/ofApp04.cpp" download>ofApp04.cpp</a></p>

<!--
Le n°1 est LE geste du cours : déclarer dans le .h, remplir dans setup,
lire dans draw. Le n°3 se corrige au tableau (somme = 210).
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
quand un dessin est faux, on sait si l'erreur est dans le calcul ou dans
l'affichage.
-->

---
layout: default
breadcrumb: 1 — Les bases / Cours 05
---

# Le programme entier — `.h`, `update()`, `draw()`

```cpp
// ofApp05.h — deux variables qui traversent les frames
float x = 0;
float y = 0;

// ofApp05.cpp
void ofApp::update() {
    x = mouseX;                    // mouseX, mouseY : mis à jour tout seuls
    y = mouseY;
}

void ofApp::draw() {
    ofBackground(255, 0, 0);       // efface la frame précédente
    ofSetColor(255);
    ofFill();
    ofDrawCircle(x, y, 50);
}
```

<div class="mt-3 text-sm">

<v-clicks>

- `x` et `y` : écrites dans `update()`, lues dans `draw()` → **partagées** (le `.h`), et **persistantes** d'une frame à l'autre — c'est ce qui permettra au cours 06 d'avancer petit à petit
- `ofBackground` en **début** de `draw()` efface la frame précédente ; enlève-le : les cercles s'accumulent en traînée
- Au cours 01 il était dans `setup()` — ça marchait car rien ne bougeait. **Dès que ça bouge, il va dans `draw()`**

</v-clicks>

</div>


<!--
Relire ensuite le cours 00 avec les bons mots : r,g,b partagées, update les
recalcule, draw efface et dessine. Seul le cos reste mystérieux (cours 06/13).
Exercices : décalage, horizontale seule, ofBackground à la FIN de draw
(pourquoi tout disparaît ?), aller à l'opposé (ofGetWidth), rayon = mouseX/4.
-->
---
layout: default
breadcrumb: 1 — Les bases / Cours 05
---

# À vous — jouer avec le cycle

<div class="mt-6 text-base">

<v-clicks>

- **1 · Un décalage** : le cercle suit la souris 100 pixels plus à droite
- **2 · L'opposé** : souris à droite, cercle à gauche — indice : `ofGetWidth()`
- **3 · Question** : déplace `ofBackground` à la **fin** de `draw()`. Pourquoi tout disparaît-il ?

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
À chaque fois : <b>prédire, lancer, constater</b>. L'exercice 5 du document fait grossir le cercle avec la souris.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/05-cycle-souris.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/05-cycle-souris.md" download>md</a> · <a href="/ressources/ofApp05.h" download>ofApp05.h</a> · <a href="/ressources/ofApp05.cpp" download>ofApp05.cpp</a></p>

<!--
Le n°2 : x = ofGetWidth() - mouseX. Le n°3 vérifie la compréhension du cycle :
on dessine, puis on repeint par-dessus — l'ordre DANS draw compte.
-->


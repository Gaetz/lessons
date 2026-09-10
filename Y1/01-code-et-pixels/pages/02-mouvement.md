---
layout: section
breadcrumb: 2 — Le mouvement
---

# Le mouvement

Vitesse, temps, mémoire des frames

---
layout: split
breadcrumb: 2 — Le mouvement / Cours 06
---

# Cours 06 — Animation

Deux formes qui traversent l'écran et rebondissent,
sur un fond dont la couleur change en continu.

<div class="mt-6 text-base">

Trois idées nouvelles, une par étape :

<v-clicks>

- une **vitesse**
- le **temps** entre deux frames
- la **condition** `if`

</v-clicks>

</div>

::right::

<div>
<img src="/ressources/cours/img/06-rebond.png" alt="Rectangle et ellipse avec flèches de vitesse" class="w-full object-contain" />
</div>

<!--
Les petits pas s'additionnent parce que la position est persistante
(cours 05).
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 06
---

# Étape 1 — une forme qui avance

```cpp
// ofApp.h :  float posX { 0 };   float posY { 0 };
//            float vx { 60 };    float vy { 120 };    // pixels par seconde

void ofApp::update() {
	float dt = ofGetLastFrameTime();
	posX = posX + vx * dt;
	posY = posY + vy * dt;
}

void ofApp::draw() {
	ofBackground(30);
	ofSetColor(255);
	ofFill();
	ofDrawRectangle(posX + 100, posY + 100, 100, 100);
	ofDrawEllipse(posX + 50, posY + 150, 200, 150);
}
```

<div class="mt-2 text-base">

<v-clicks>

- **Bouger = ajouter une vitesse à une position**, à chaque frame — la persistance du cours 05 fait le reste
- Les deux formes partagent `(posX, posY)` : elles bougent ensemble… puis sortent de l'écran — étape 3

</v-clicks>

</div>

<!--
ofDrawEllipse(x, y, largeur, hauteur) : centre + deux diamètres, alors que
le rectangle part du coin haut-gauche. Essaie : double vx ; vy à 0 ;
vitesses négatives.
-->

---
layout: split
breadcrumb: 2 — Le mouvement / Cours 06
---

# Étape 2 — le delta time

```cpp
float dt = ofGetLastFrameTime();
posX = posX + vx * dt;
```

<div class="mt-4 text-base">

<v-clicks>

- `dt` : la **durée de la frame précédente**, en secondes (~0.0167 à 60 fps)
- Le nombre de frames par seconde n'est **pas garanti** — `+ 1` par frame irait deux fois moins vite à 30 fps
- La règle de l'année : **une vitesse s'exprime en unités par seconde et se multiplie par `dt`**

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/06-sans-deltatime.png" alt="Sans delta time, la machine à 30 fps parcourt moitié moins de chemin" class="w-full object-contain" />
</div>

<!--
C'est le player.x += speed de la rentrée — et cette fois on écrit la version
juste. Essaie : afficher dt dans la console (cours 04).
-->

---
layout: split
breadcrumb: 2 — Le mouvement / Cours 06
---

# Étape 3 — la condition `if` : le rebond

```cpp
	if (posY > 180) vy = -vy;     // dépassé ? on inverse la vitesse
	if (posY < -80) vy = -vy;
	if (posX > 250) vx = -vx;
	if (posX < 0)   vx = -vx;
```

<div class="mt-5 text-base">

<v-clicks>

- `if (condition) instruction;` — l'instruction ne s'exécute que si la condition est vraie
- Rebondir = **inverser la vitesse** : `-vx` fait de 60 un −60, la forme repart
- Plusieurs instructions sous un `if` ? Des **accolades**

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/06-rebond-vitesse.png" alt="Rebondir : +60 devient −60 au mur" class="w-full object-contain" />
</div>

<!--
Essaie : rebondir sur les VRAIS bords (taille des formes !) ; puis un cercle
qui réapparaît à gauche au lieu de rebondir — un seul if.
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 06
---

# Les comparaisons — et le piège du `==`

```cpp
if (x == 5)  { ... }     // égal : DEUX signes
if (x = 5)   { ... }     // compile... et ne fait pas ce que tu crois
```

<div class="mt-5 text-base">

<v-clicks>

- Les comparaisons : `<`, `>`, `<=`, `>=`, `==` (égal), `!=` (différent)
- Un seul `=` est l'affectation du cours 01 : « `x` reçoit 5 » — jamais une comparaison
- `if (x = 5)` affecte, puis teste 5 (toujours vrai) : le bug silencieux classique

</v-clicks>

</div>

<!--
À écrire au tableau. Certains compilateurs préviennent — apprendre à lire
leurs avertissements.
-->

---
layout: split
breadcrumb: 2 — Le mouvement / Cours 06
---

# Étape 4 — une couleur en allers-retours

```cpp
// .h : float r { 0 }, g { 0 }, b { 0 };
//      float vr { 300 }, vg { 240 }, vb { 180 };

	r = r + vr * dt;
	if (r >= 255) vr = -vr;
	if (r <= 0)   vr = -vr;
	// ... idem g et b

	ofBackground(r, g, b);
```

<div class="mt-3 text-base">

<v-clicks>

- **Exactement le rebond**, appliqué à une composante de couleur
- Trois vitesses différentes : le fond ne se répète pas de sitôt
- **Un nombre animé pilote n'importe quoi** : position, taille, couleur, transparence

</v-clicks>

</div>

::right::

<div>
<img src="/ressources/cours/img/06-allers-retours.png" alt="Courbe en dents de scie entre 0 et 255" class="w-full object-contain" />
</div>

<!--
Essaie : une variable taille qui fait des allers-retours entre 50 et 150 sur
le rectangle.
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 06
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — avec `posX { 0 }` et `vx { -100 }`, et ces deux conditions :

```cpp
if (posX > 300) vx = -vx;
if (posX < 100) vx = -vx;
```

Dans quel sens la forme part-elle ? Que se passe-t-il au tout début ? Entre quelles bornes finit-elle par osciller ?

</div>

<div v-click class="mt-4 text-base">

**2 · L'écran de veille** — un carré qui rebondit sur les quatre **vrais bords** de la fenêtre, et qui change de couleur **à chaque rebond** (une couleur aléatoire tirée dans le `if` — cours 03). Le mythe du logo DVD, à toi.

</div>

<!--
Ex 1 : elle part vers la gauche (vx négatif), franchit 100 aussitôt (le if
la renvoie), puis oscille entre 100 et 300.
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 06
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · La course** — deux cercles partent du bord gauche à des vitesses différentes ; quand l'un sort à droite, il réapparaît à gauche. Regarde-les se doubler : au bout de combien de temps se retrouvent-ils alignés ?

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Le fond apaisé** — remplace les allers-retours du fond par une formule plus douce : `r = (cos(t * 1.5f) / 2 + 0.5f) * 255;` avec `float t = ofGetElapsedTimef();` (le temps écoulé depuis le lancement, en secondes). `cos` oscille entre −1 et 1 ; `/ 2 + 0.5` le ramène entre 0 et 1 ; `* 255` entre 0 et 255. Compare avec les dents de scie — on expliquera tout au cours 13.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/06-animation.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/06-animation.md" download>md</a> · <a href="/ressources/ofApp06.h" download>ofApp06.h</a> · <a href="/ressources/ofApp06.cpp" download>ofApp06.cpp</a></p>

<!--
Ex 3 : ils s'alignent quand la différence de distances vaut un tour complet
de fenêtre.
-->
---
layout: split
breadcrumb: 2 — Le mouvement / Cours 07
---

# Cours 07 — La traînée

Un ours suit la souris, et les cinquante positions
précédentes restent affichées derrière lui.

<div class="mt-6 text-sm">

<v-clicks>

- Écrire **nos propres fonctions** de dessin
- Une liste comme **mémoire** des dernières frames

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/07-trainee.png" alt="Traînée d'ours blancs" class="w-full object-contain" />
</div>

<!--
C'est le cours qui explique enfin le funnyFace du cours 00.
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 07
---

# Étape `bear()` — fabriquer sa propre fonction

```cpp
// annoncé dans le .h :   void bear(float x, float y);
void ofApp::bear(float x, float y) {
    ofDrawCircle(x - 25, y - 25, 25);      // tout est écrit
    ofDrawCircle(x + 25, y - 25, 25);      // par rapport à (x, y)
    ofDrawCircle(x, y, 50);
    ofDrawCircle(x, y, 10);
    ofDrawCircle(x - 30, y - 20, 10);
    ofDrawCircle(x + 30, y - 20, 10);
    ofDrawRectangle(x, y + 20, 50, 10);
}
```

<div class="mt-3 text-sm">

<v-clicks>

- `void` : la fonction ne renvoie rien, elle **fait**. `float x, float y` : ses **paramètres**, fournis par l'appelant
- Les positions relatives à `(x, y)` rendent l'ours **déplaçable** : `bear(mouseX, mouseY)` le met sous la souris
- La ligne d'annonce dans le `.h` (sans le corps) est obligatoire : sans elle, le compilateur ne connaît pas `bear` en lisant `draw()`

</v-clicks>

</div>

<!--
Le .h du cours porte aussi : x, y et les deux listes xCoords / yCoords.
setup() : juste la fenêtre.
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 07
---

# Les paramètres sont des copies

<div class="mt-8 flex justify-center items-center gap-6 text-sm">
  <div class="text-center">
    <div class="text-sm font-bold mb-1">mouseX</div>
    <div class="w-24 h-14 rounded flex items-center justify-center text-xl font-bold" style="border:3px solid #000">412</div>
    <div class="text-xs op-60 mt-1">chez l'appelant</div>
  </div>
  <div class="text-center op-70">
    <div class="text-2xl">→</div>
    <div class="text-xs">copie<br>à l'appel</div>
  </div>
  <div class="text-center">
    <div class="text-sm font-bold mb-1" style="color:#EA5027">x</div>
    <div class="w-24 h-14 rounded flex items-center justify-center text-xl font-bold" style="border:3px dashed #EA5027">412</div>
    <div class="text-xs op-60 mt-1">dans <code>bear</code> — naît à l'appel,<br>meurt à l'accolade fermante</div>
  </div>
</div>

<div class="mt-8 text-sm">

<v-clicks>

- `bear(mouseX, mouseY)` : la fonction reçoit des **copies** — ses cases `x` et `y` sont neuves à chaque appel
- Modifier `x` à l'intérieur de `bear` ne change **pas** `mouseX` : l'original est intact
- Quand une fonction devra *fabriquer* une valeur pour son appelant, elle la **renverra** — c'est `return`, au cours 11

</v-clicks>

</div>

<!--
C'est le passage par valeur. Conséquence heureuse : une fonction ne peut pas
abîmer les variables de l'appelant. Conséquence à comprendre : filtre() du
cours 11 doit return sa couleur, modifier son paramètre c ne servirait à rien.
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 07
---

# Étape `update()` — la file

```cpp
void ofApp::update() {
    xCoords.push_back(x);                    // 1. mémoriser la position courante
    yCoords.push_back(y);

    if (xCoords.size() >= 50) {              // 2. borner la mémoire :
        xCoords.erase(xCoords.begin());      //    retirer la plus ancienne
        yCoords.erase(yCoords.begin());
    }

    x = mouseX;                              // 3. mettre à jour
    y = mouseY;
}
```

<div class="mt-3 text-sm">

<v-clicks>

- Ajouter à la fin + retirer au début = une **file** ; bornée à 50, elle contient toujours les 50 dernières positions
- L'ordre compte : **mémoriser avant de mettre à jour**, sinon la position courante serait en double
- Deux listes parallèles (`xCoords[i]`, `yCoords[i]` = la position `i`) : fragile — la **`struct`**, juste après le `draw()`, les regroupe sous un seul nom

</v-clicks>

</div>

<!--
erase(begin()) = « supprime l'élément d'indice 0 », les autres se décalent.
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 07
---

# Étape `draw()` — dessiner toute la mémoire

```cpp
void ofApp::draw() {
    ofBackground(0);
    ofFill();
    ofSetColor(255);

    for (int i = 0; i < xCoords.size(); i++) {
        bear(xCoords[i], yCoords[i]);        // un ours par position mémorisée
    }
    bear(x, y);                              // puis l'ours courant, par-dessus
}
```

<div class="mt-3 text-sm">

<v-clicks>

- La boucle du cours 04 : l'indice 0 est le plus ancien, `size() - 1` le plus récent
- Cinquante ours blancs identiques se fondent en une masse — **c'est exprès** : le cours 08 fait varier couleur, transparence et taille selon `i`

</v-clicks>

</div>


<!--
IMPORTANT : ce cours porte la grande AUTONOMIE « traînée évoluée » (tableau de
paramètres dans le document). Le cours 08 en est le corrigé : ne l'ouvrir
qu'une fois sa version terminée.
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 07
---

# La `struct` en mémoire — et un `vector` de structs

```cpp
struct Position { float x; float y; };      // un type fabriqué par NOUS
```

<div class="mt-4 text-sm">

<div class="flex items-center gap-4 mb-4">
  <code class="font-bold w-42">Position p</code>
  <div class="flex rounded overflow-hidden" style="border:3px solid #000">
    <div class="w-18 h-12 flex flex-col items-center justify-center" style="border-right:2px dashed #999"><span class="text-xs font-bold" style="color:#EA5027">x</span><span>120</span></div>
    <div class="w-18 h-12 flex flex-col items-center justify-center"><span class="text-xs font-bold" style="color:#0F6FA5">y</span><span>80</span></div>
  </div>
  <span class="op-60">deux <code>float</code> <b>collés</b> : une case double</span>
</div>

<div class="flex items-center gap-4">
  <code class="font-bold w-42">vector&lt;Position&gt;</code>
  <div class="flex items-center gap-0">
    <div class="flex rounded overflow-hidden" style="border:3px solid #000"><div class="w-11 h-12 flex items-center justify-center font-bold" style="color:#EA5027;border-right:2px dashed #999">x</div><div class="w-11 h-12 flex items-center justify-center font-bold" style="color:#0F6FA5">y</div></div>
    <div class="flex rounded overflow-hidden" style="border:3px solid #000;border-left:none"><div class="w-11 h-12 flex items-center justify-center font-bold" style="color:#EA5027;border-right:2px dashed #999">x</div><div class="w-11 h-12 flex items-center justify-center font-bold" style="color:#0F6FA5">y</div></div>
    <div class="flex rounded overflow-hidden" style="border:3px solid #000;border-left:none"><div class="w-11 h-12 flex items-center justify-center font-bold" style="color:#EA5027;border-right:2px dashed #999">x</div><div class="w-11 h-12 flex items-center justify-center font-bold" style="color:#0F6FA5">y</div></div>
    <span class="ml-2 text-lg op-60">…</span>
  </div>
  <span class="op-60">les paires se suivent, <b>bout à bout</b></span>
</div>

<div class="flex gap-4 mt-1">
  <span class="w-42"></span>
  <span class="flex"><span class="w-22 text-center text-xs op-60">[0]</span><span class="w-22 text-center text-xs op-60">[1]</span><span class="w-22 text-center text-xs op-60">[2]</span></span>
</div>

</div>

<div class="mt-4 text-sm">

<v-clicks>

- Les membres d'une `struct` vivent dans des **cases collées** (cours 01) : `p` occupe une case double, 2 × 4 octets
- On ouvre un compartiment avec le **point** : `p.x` — la syntaxe de `noms.size()` du cours 04
- Le `vector` de structs remplace **les deux listes parallèles par une seule** : `positions[i].x`, `positions[i].y` — impossible d'oublier un `push_back` sur l'une des deux

</v-clicks>

</div>

<!--
L'encart du document donne le code complet (push_back d'une Position).
glm::vec2 d'openFrameworks est exactement cette struct avec des opérations
en plus, et ofColor fonctionne pareil : c.r, c.g, c.b (cours 10).
En mémoire le vector est un seul ruban x y x y x y — l'image resservira
en 11d (trois « images » de floats) et 11f (matrice dans une liste).
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 07
---

# La file, version `struct`

```cpp
// ofApp07.h :  struct Position { float x; float y; };
//              std::vector<Position> positions;     // UNE liste remplace les deux

void ofApp::update() {
    Position p;                              // une case double...
    p.x = x;  p.y = y;
    positions.push_back(p);                  // ...mémorisée d'un seul geste

    if (positions.size() >= 50) {
        positions.erase(positions.begin());  // un seul erase aussi
    }
    x = mouseX;  y = mouseY;
}

void ofApp::draw() {
    // fond et couleur inchangés
    for (int i = 0; i < positions.size(); i++) {
        bear(positions[i].x, positions[i].y);
    }
    bear(x, y);
}
```

<div class="mt-2 text-sm">

<v-clicks>

- `xCoords` et `yCoords` disparaissent : **un seul** `push_back`, **un seul** `erase` — la file ne peut plus se désynchroniser
- `positions[i].x` : l'indice choisit la paire, le point ouvre le compartiment
- À l'écran, **rien ne change** : on a réécrit pour *nous* — plus sûr, plus lisible. Ce geste a un nom : **remanier** (*refactoring*), et vous le referez toute votre vie

</v-clicks>

</div>

<!--
Le code complet est dans l'encart « Pour aller plus loin » du document.
glm::vec2 d'openFrameworks est exactement cette struct avec des opérations
en plus — on pourrait remplacer Position par glm::vec2 sans rien changer
d'autre. ofColor fonctionne pareil : c.r, c.g, c.b (cours 10).
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 07
---

# À vous — ta propre fonction

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Change `50` en 10, puis en 200 : la longueur de la mémoire
- **2 ·** Écris une fonction `etoile(float x, float y)` et remplace l'ours
- **3 ·** 🔥 Ajoute un paramètre `float taille` à `bear` — tout doit devenir **proportionnel**

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/07-trainee.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/07-trainee.md" download>md</a> · <a href="/ressources/ofApp07.h" download>ofApp07.h</a> · <a href="/ressources/ofApp07.cpp" download>ofApp07.cpp</a></p>

<!--
C'est le cours de l'AUTONOMIE (document) : prévoir du temps pour la forme
personnelle. N°3 : x - taille / 2, etc.
-->

---
layout: split
breadcrumb: 2 — Le mouvement / Cours 08
---

# Cours 08 — Traînée évoluée

Le **corrigé de l'autonomie** du cours 07 : chaque élément
a sa taille, sa transparence et sa teinte, calculées depuis
son **indice** dans la file et le **temps**.

<div class="mt-4 text-sm">

Rien de nouveau dans les outils : c'est un cours sur ce
qu'on peut faire quand on **combine** ceux qu'on a.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/08-trainee.png" alt="Traînée de cercles bleutés" class="w-full object-contain" />
</div>

<!--
Une solution possible, pas LA solution : toute version qui respecte les
contraintes de l'autonomie est valable. Le dire explicitement.
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 08
---

# Étape `forme()` — tout se déduit de `i` et `t`

```cpp {1-2|4-7|9-17}
void ofApp::forme(float x, float y, int i, float t, float r, float g, float b) {
    float offset = i * 10;                        // 0 → 240 le long de la traînée

    // taille : ondule selon i, et pulse selon t (plus fort à l'arrière)
    float taille = (cos(i / 5.0f) + 5) * 20;
    float variation = (cos(t * 1.2f) + 5) * 100;
    float tailleFinale = taille + variation * (25 - i) / 50.0f;

    ofFill();                                     // remplissage : alpha croissant
    ofSetColor(r + offset, g + offset, b + offset, offset);
    ofDrawCircle(x, y, tailleFinale / 2);

    ofNoFill();                                   // contour : alpha inverse
    ofSetColor(r + offset, g + offset, b + offset, 255 - offset);
    ofDrawCircle(x, y, tailleFinale / 2);
}
```

<div class="mt-2 text-sm">

- Sept paramètres : la fonction **ne décide rien toute seule**, elle déduit tout de `i` (sa place) et `t` (le moment)
- Transparences croisées (`offset` / `255 - offset`) : les anciens n'ont qu'un contour, les récents un remplissage — la profondeur
- `r + offset` peut dépasser 255 : openFrameworks arrondit ici, mais la vraie solution (`ofClamp`) arrive au cours 10

</div>

<!--
Trois clics = trois zones : la signature et offset, la taille combinée i+t,
les deux passes. Les 5.0f et 50.0f évitent la division entière (cours 01).
-->

---
layout: default
breadcrumb: 2 — Le mouvement / Cours 08
---

# Étapes `update()` et `draw()` — le temps, la file, la boucle

```cpp
void ofApp::update() {
    t = ofGetElapsedTimef();                      // le temps écoulé, en secondes
    r = (cos(t * 1.2f)  / 2 + 0.5f) * 255;        // LE motif : osciller entre 0 et 255
    g = (cos(t * 1.0f)  / 2 + 0.5f) * 255;
    b = (cos(t * 0.86f) / 2 + 0.5f) * 255;

    prevX.push_back(mouseX);                      // la file du cours 07 (bornée à 25)
    prevY.push_back(mouseY);
    if (prevX.size() > 25) { prevX.erase(prevX.begin()); prevY.erase(prevY.begin()); }
}

void ofApp::draw() {
    ofBackground(0);
    for (int i = 0; i < prevX.size(); i++) {
        forme(prevX[i], prevY[i], i, t, r, g, b);   // 25 cercles, tous différents
    }
}
```

<div class="mt-2 text-sm">

- `cos(t)` oscille entre −1 et 1 ; `/ 2 + 0.5f` le ramène entre 0 et 1, `* 255` entre 0 et 255 — **le motif à retenir** (c'était le fond mystérieux du cours 00)
- L'autre façon d'animer : au lieu d'ajouter un pas (cours 06), on **calcule directement** depuis le temps
- Limite assumée : trois cosinus, ça bouge, mais on ne contrôle rien — la couleur passe par des gris. Le cours 09 donne le bon outil : la **teinte**

</div>


<!--
Exercices : offset / 2, remplacer (25 - i) par i, l'ours avec un paramètre de
taille, cercle si i pair / carré si impair (i % 2 == 0).
-->
---
layout: default
breadcrumb: 2 — Le mouvement / Cours 08
---

# À vous — variations sur la traînée

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** La transparence : que donne `offset / 2` à la place d'`offset` ?
- **2 ·** Les tailles : remplace `(25 - i)` par `i` — prédis d'abord
- **3 ·** 🔥 Un cercle pour `i` pair, un carré pour `i` impair : `i % 2 == 0`

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/08-trainee-evoluee.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/08-trainee-evoluee.md" download>md</a> · <a href="/ressources/ofApp08.h" download>ofApp08.h</a> · <a href="/ressources/ofApp08.cpp" download>ofApp08.cpp</a></p>

<!--
N°3 introduit % en douceur (il revient au cours 13). Le 08 est le corrigé
de l'autonomie du 07 : ne l'ouvrir qu'après.
-->


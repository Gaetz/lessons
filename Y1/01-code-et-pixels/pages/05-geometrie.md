---
layout: section
breadcrumb: 5 — La géométrie
---

# La géométrie

Distance, trigonométrie, transformations

---
layout: split
breadcrumb: 5 — La géométrie / Cours 12
---

# Cours 12 — Pointillisme et distance

L'image n'est plus affichée : elle est **redessinée**
en cercles, un tous les 20 pixels, chacun de la couleur
du pixel qu'il remplace. Et près de la souris,
les cercles rétrécissent.

<div class="mt-4 text-sm">

L'image comme **source de données** — la remarque
de la fin du cours 10, en action.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/12-pointillisme.png" alt="Le panda en gros points, trou autour du curseur" class="w-full object-contain" />
</div>

<!--
Mise en place : le .h porte img et tailleCercle = 20 ; setup charge
pandaroux.jpg (avec la vérification du bool, réflexe du cours 10).
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 12
---

# Étape `distance()` — Pythagore

```cpp
float ofApp::distance(float ax, float ay, float bx, float by) {
    float dx = bx - ax;
    float dy = by - ay;
    return sqrt(dx * dx + dy * dy);
}
```

<div class="mt-4 text-sm">

<v-clicks>

- Deux points, un écart horizontal, un écart vertical : la distance est l'**hypoténuse** — `sqrt` est la racine carrée
- La fonction renvoie un `float` avec `return`, comme `filtre` renvoyait une `ofColor` au cours 11
- openFrameworks fournit `ofDist(ax, ay, bx, by)` qui fait exactement ceci — on l'écrit une fois pour la voir, ensuite `ofDist`

</v-clicks>

</div>

<!--
Cette distance se généralise en 3D pour les couleurs (cours 09) : elle
servira au plusProche du 11g.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 12
---

# Étape `draw()` — la grille, et l'effet local

```cpp
for (int li = 0; li < windowHeight; li += tailleCercle) {      // pas de 20
    for (int co = 0; co < windowWidth; co += tailleCercle) {

        float d = distance(mouseX, mouseY, co, li);

        float rayon = tailleCercle / 2.0f;
        if (d <= 150) {
            float proportion = d / 150.0f;     // 0 sous la souris, 1 à 150 px
            rayon = rayon * proportion;
        }

        ofColor c = img.getColor(co, li);      // le pixel à cet endroit
        ofSetColor(c);
        ofDrawCircle(co, li, rayon);
    }
}
```

<div class="mt-2 text-sm">

- La double boucle du cours 11 **avec un pas** : un pixel sur 400, un cercle par point de grille
- **Ramener entre 0 et 1, puis multiplier** : faire dépendre une chose d'une autre *en douceur* — un dégradé au lieu d'un `if` brutal
- Un effet local = un filtre + un **masque** défini par une distance — combinable avec tous les filtres du cours 11

</div>


<!--
Variante en commentaire dans le code : carrés + anneau qui s'élargit avec le
temps (d / (200 + t)) — distance + temps = animations riches pour trois lignes.
Exercice 5 : l'image en cinq couleurs par distance RGB — prépare le 11g.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 12
---

# À vous — autour de la distance

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Remplace les cercles par des carrés, puis par des rectangles dont la **hauteur dépend de la luminosité**
- **2 ·** Inverse l'effet : les cercles **grossissent** près de la souris
- **3 ·** 🔥 L'image en **cinq couleurs** : la distance dans le cube RGB vers cinq couleurs choisies, on dessine avec la plus proche — il prépare le 11g

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/12-pointillisme.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/12-pointillisme.md" download>md</a> · <a href="/ressources/ofApp12.h" download>ofApp12.h</a> · <a href="/ressources/ofApp12.cpp" download>ofApp12.cpp</a></p>

<!--
N°3 : sqrt(dr*dr + dg*dg + db*db), ou comparer les carrés. L'ex 3 du
document (filtre local) pour les rapides.
-->

---
layout: split
breadcrumb: 5 — La géométrie / Cours 13
---

# Cours 13 — Des cercles sur un cercle

Douze cercles répartis sur un cercle invisible, qui
respirent ensemble. Placer un point « à tel angle,
à telle distance » : c'est `cos` et `sin`.

<div class="mt-4 text-sm">

<v-clicks>

- Les angles sont en **radians** : un tour = `TWO_PI` ≈ 6,28
- Répartir `n` éléments sur un tour : `i * TWO_PI / n`
- Le même `cos` que le cours 08 : quand l'angle avance, le point tourne, et sa coordonnée `x` oscille

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/13-cercles.png" alt="Douze cercles RVB en fusion additive" class="w-full object-contain" />
</div>

<!--
Le schéma img/13-trigo.png du document : cos(a) est la coordonnée horizontale
sur le cercle de rayon 1, sin(a) la verticale — on multiplie par le rayon voulu.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 13
---

# Étapes `update()` et `draw()` — l'orbite qui respire

```cpp {1-3|5-9|11-19}
void ofApp::update() {
    t = cos(ofGetElapsedTimef() * 0.6f);       // oscille entre -1 et 1
}

void ofApp::draw() {
    ofBackground(0);
    ofPushMatrix();
    ofTranslate(400, 400);                     // l'origine au centre
    ofEnableBlendMode(OF_BLENDMODE_ADD);       // les lumières s'ajoutent

    for (int i = 0; i < nbCercles; i++) {
        if (i % 3 == 0)      ofSetColor(255, 0, 0);     // alterner par le reste
        else if (i % 3 == 1) ofSetColor(0, 255, 0);
        else                 ofSetColor(0, 0, 255);

        float angle = i * TWO_PI / nbCercles;
        float x = cos(angle) * rayonOrbite * t;
        float y = -sin(angle) * rayonOrbite * t;   // - : l'axe y pointe vers le bas
        ofDrawCircle(x, y, 100);
    }
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);     // retour au mode normal
    ofPopMatrix();
}
```

<div class="mt-2 text-sm">

- `ofPushMatrix / ofTranslate / ofPopMatrix` : **déplacer l'origine** le temps d'un bloc — toujours par paire
- `i % 3` : le **reste** de la division — 0, 1, 2, 0, 1, 2… l'outil pour alterner et cycler (`fmod` pour les `float`)
- Mode **additif** : rouge sur vert donne jaune, les trois donnent blanc — le cube RGB du cours 09 rendu visible
- Une seule variable `t` multiplie le rayon : douze cercles qui respirent ensemble

</div>


<!--
La coïncidence heureuse (variante en commentaire) : la roue des teintes EST
un cercle — fromHsb(i * 255 / n) donne au cercle i la couleur de son secteur.
Exercices : n = 3, 7, 36 ; faire tourner l'ensemble ; deux anneaux inverses ;
l'ours de 07.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 13
---

# À vous — orbites

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Change `nbCercles` : 3, 7, 36 — puis le rayon des cercles
- **2 ·** Fais **tourner** l'ensemble : ajoute `ofGetElapsedTimef()` à `angle`
- **3 ·** 🔥 **Deux anneaux** : un second `for`, un autre rayon d'orbite, un sens de rotation inverse

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/13-cercle-de-cercles.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/13-cercle-de-cercles.md" download>md</a> · <a href="/ressources/ofApp13.h" download>ofApp13.h</a> · <a href="/ressources/ofApp13.cpp" download>ofApp13.cpp</a></p>

<!--
N°3 : le sens inverse = soustraire le temps. Ex 4 (l'ours en orbite) fait
toujours rire — le garder pour la fin.
-->

---
layout: split
breadcrumb: 5 — La géométrie / Cours 14
---

# Cours 14 — Filtres géométriques

Au cours 11, chaque pixel changeait de couleur mais
restait à sa place. Ici c'est l'inverse : la couleur ne
change pas, on va la **chercher ailleurs**.

<div class="mt-4 text-base">

```cpp
resultat(x, y) = source(f(x, y))
```

On raisonne toujours **depuis le résultat** : chaque pixel
de sortie est rempli exactement une fois — jamais de trous.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/14-geometrie.png" alt="Miroir, rotation, pixelisation, vagues, glitch" class="w-full object-contain" />
</div>

<!--
L'intuition « déplacer chaque pixel de la source » ne marche pas : doublons
et trous. La lecture « à l'envers » est la façon de penser de TOUS les effets
d'image, jusqu'aux shaders. Schéma img/14-lecture-inverse.png.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 14
---

# Étape `lire()` — une lecture qui ne sort jamais de l'image

```cpp
ofColor ofApp::lire(float x, float y) {
    int px = ofClamp((int)x, 0, source.getWidth() - 1);
    int py = ofClamp((int)y, 0, source.getHeight() - 1);
    return source.getColor(px, py);
}
```

<div class="mt-4 text-sm">

<v-clicks>

- Un miroir ou une vague peut demander le pixel −5 ou le pixel 800 : on borne **une fois pour toutes, dans une fonction**
- `(int)x` **convertit** le `float` en entier en coupant la virgule — les coordonnées d'un pixel sont entières
- Effet secondaire : au bord, le dernier pixel est répété (l'image semble étirée) — le choix le plus simple ; répéter par modulo est l'exercice 3

</v-clicks>

</div>

<!--
Le problème d'indice hors limites, encore (cours 04, 10) — cette fois
encapsulé proprement.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 14
---

# Étape `update()` — cinq formules, cinq effets

```cpp
switch (effet) {
case 1:                                       // miroir horizontal
    c = lire(w - 1 - x, y);  break;
case 2:                                       // rotation 180°
    c = lire(w - 1 - x, h - 1 - y);  break;
case 3: {                                     // pixelisation
    int n = 2 + parametre * 40;
    c = lire(x / n * n, y / n * n);  break;   // division entière VOLONTAIRE
}
case 4: {                                     // vagues
    float dx = parametre * 40 * sin(y / 20.0f + t * 3);
    c = lire(x + dx, y);  break;
}
case 5: {                                     // glitch : un canal, un endroit
    float d = parametre * 30;
    c = ofColor(lire(x - d, y).r, lire(x, y).g, lire(x + d, y).b);  break;
}
default: c = lire(x, y);                      // identité
}
resultat.setColor(x, y, c);
```

<div class="mt-2 text-sm">

- La double boucle du cours 11, un `switch` — mais la formule porte sur **les coordonnées**, plus sur la couleur
- Les vagues reprennent `sin` du cours 13 : oscille selon `y`, glisse avec `t`
- Le glitch, c'est l'**aberration chromatique** : rien n'oblige les trois canaux à venir du même pixel — l'effet « écran abîmé » des jeux en trois lectures

</div>


<!--
Pixelisation : x / n * n n'est pas x — 137/20*20 = 120, toute la case lit son
coin (même calcul que le centre de case du 15 et les blocs du 11d).
Exercices : kaléidoscope, vagues verticales, modulo (attention au négatif),
glitch aléatoire, zoom. Loupe et tourbillon attendent le polaire du cours 16.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 14
---

# À vous — tordre l'image

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Le miroir **vertical**. Puis le « kaléidoscope » : la moitié droite est le reflet de la gauche — `if (x > w / 2)`
- **2 ·** Des vagues **verticales** : décaler `y` selon `x`. Puis les deux à la fois
- **3 ·** 🔥 Le **glitch** : des lignes entières décalées d'une valeur `ofRandom` — avec `ofSeedRandom` pour que ça ne scintille pas… ou sans, pour que ça scintille (cours 03)

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/14-filtres-geometriques.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/14-filtres-geometriques.md" download>md</a> · <a href="/ressources/ofApp14.h" download>ofApp14.h</a> · <a href="/ressources/ofApp14.cpp" download>ofApp14.cpp</a></p>

<!--
L'ex 5 du document (le zoom : pourquoi ces nombres ?) est une excellente
question de compréhension à poser à la salle.
-->

---
layout: split
breadcrumb: 5 — La géométrie / Cours 15
---

# Cours 15 — La grille en rotation

Une grille de 15 × 15 cases ; dans chacune, un point
tourne autour du centre de sa case. Même vitesse
partout, mais chaque case a un **décalage** d'angle :
l'ensemble ondule comme un drapeau.

<div class="mt-4 text-sm">

Le motif à retenir : **une grandeur commune à tous,
plus un décalage propre à chacun** — la traînée du
cours 08 le faisait déjà avec la taille.

</div>

::right::

<div>
<img src="/ressources/cours/img/15-grille.png" alt="Grille de points avec cercles de construction" class="w-full object-contain" />
</div>

<!--
Mise en place : tileSize = screenSize / (float)rows — le (float) évite la
division entière (400/15 = 26 en int, la grille ne remplirait pas la fenêtre).
update() : globalAngle += speed * dt — une vitesse ANGULAIRE, en radians par
seconde, traitée comme toute vitesse (cours 06).
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 15
---

# Étape `drawPoint()` — une case, un déphasage

```cpp
void ofApp::drawPoint(int i, int j, float angle) {
    angle = angle + i * angleOffset + j * angleOffset;   // le déphasage

    float x0 = i * tileSize + tileSize / 2;              // centre de la case
    float y0 = j * tileSize + tileSize / 2;

    float x = radius * cos(angle) + x0;                  // tourner AUTOUR
    float y = radius * sin(angle) + y0;                  // de ce centre

    ofFill();
    ofSetColor(0);
    ofDrawCircle(x, y, 5);
}

// draw() : la double boucle appelle drawPoint(i, j, globalAngle)
```

<div class="mt-3 text-sm">

<v-clicks>

- La formule du cours 13 **plus le centre** : au lieu d'`ofTranslate`, on ajoute `(x0, y0)` à la main — même résultat
- Les voisines sont légèrement en avance ou en retard : une **vague** traverse la grille
- `angleOffset` à 0.1 : une houle. À **75** : ça semble aléatoire… alors que c'est parfaitement régulier — 75 radians tombe « au hasard » sur le cercle à chaque case
- Séparer « parcourir » (la boucle) et « dessiner un élément » (la fonction) : les deux restent lisibles

</v-clicks>

</div>


<!--
Décommenter les deux lignes de construction dans le code pour voir cercles et
rayons. Exercices : offset 0.3, offset selon i seulement (colonnes), rayon
selon la case, traits-aiguilles, teinte selon l'angle, ondes circulaires
(déphasage par la distance au centre).
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 15
---

# À vous — déphasages

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** `angleOffset` à 0.3 — puis un déphasage qui ne dépend **que de `i`** : les colonnes ondulent ensemble
- **2 ·** Remplace le point par un **trait du centre au point** : `ofDrawLine(x0, y0, x, y)` — un champ d'aiguilles
- **3 ·** 🔥 Le déphasage par la **distance au centre de la fenêtre** au lieu d'`i + j` : des ondes circulaires

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/15-grille-rotation.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/15-grille-rotation.md" download>md</a> · <a href="/ressources/ofApp15.h" download>ofApp15.h</a> · <a href="/ressources/ofApp15.cpp" download>ofApp15.cpp</a></p>

<!--
N°3 réutilise la distance du cours 12 — le faire remarquer. Ex 4 : la
teinte est un angle (fromHsb), joli pont vers le 13.
-->

---
layout: split
breadcrumb: 5 — La géométrie / Cours 16
---

# Cours 16 — Fleurs polaires

Un point peut se décrire par `(x, y)` — ou par
`(angle, rayon)` : les coordonnées **polaires**.
Certaines formes y deviennent simples.

<div class="mt-4 text-sm">

<v-clicks>

- Un cercle : « rayon constant ». Une spirale : « rayon qui grandit avec l'angle »
- Une fleur : un rayon qui **ondule** le long du tour — elle tient en deux nombres

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/16-fleurs.png" alt="Fleurs emboîtées en mode additif" class="w-full object-contain" />
</div>

<!--
Schéma img/16-polaire.png : cercle gris de rayon r, fleur dont le rayon
oscille autour de r. Quatorze fleurs emboîtées, en mode additif (deux
couleurs sombres alternées : les recouvrements s'éclaircissent).
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 16
---

# Étape `drawFlower()` — une forme libre, point par point

```cpp
void ofApp::drawFlower(int fIndex, float r, float rotation) {
    ofBeginShape();
    for (int i = 0; i < nbPoints; i++) {                  // 200 sommets
        float angle = i * TWO_PI / nbPoints;
        float fRadius = amplitude * cos(angle * period);  // period pétales !
        float x = (r + fRadius) * cos(angle + rotation);  // polaire → cartésien
        float y = (r + fRadius) * sin(angle + rotation);
        ofVertex(x, y);
    }
    ofEndShape(true);          // true : fermer la forme
}
```

<div class="mt-3 text-sm">

<v-clicks>

- `ofBeginShape / ofVertex / ofEndShape` : une forme quelconque, sommet par sommet — 200 points et la courbe paraît lisse
- `cos(angle * period)` oscille `period` fois sur un tour : `period` **pétales**, de hauteur `amplitude`
- Le `+ rotation` fait tourner la fleur entière

</v-clicks>

</div>

<!--
update() : une rotation par fleur — rotations = std::vector<float>(nbFlowers, 0)
(liste de n zéros d'un coup), vitesse f * 0.12 * sens, où sens alterne par
(f % 2 == 0) ? 1 : -1 — le raccourci « condition ? a : b », un if qui renvoie
une valeur.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 16
---

# L'exercice final — loupe et tourbillon : quatre cours se rejoignent

<div class="mt-4 text-base">

Avec la lecture « à l'envers » du cours 14, pour chaque pixel `(x, y)` du résultat :

<v-clicks>

1. **Cartésien → polaire** autour de la souris : `r = sqrt(dx² + dy²)`, `angle = atan2(dy, dx)` — `atan2` fait l'inverse de `cos`/`sin` : il retrouve l'angle d'un vecteur
2. **Modifier** : loupe → `r * 0.5f` si `r < R` ; tourbillon → `angle + k * (1 - r / R)` — la proportion du cours 12, pour raccorder sans cassure
3. **Polaire → cartésien** : `sx = mouseX + r * cos(angle)`, `sy = …`
4. **Lire** la source en `(sx, sy)` avec la fonction bornée, écrire en `(x, y)`

</v-clicks>

</div>

<div v-click class="mt-6 text-base">
Distance <i>(12)</i> + trigonométrie <i>(13)</i> + lecture inverse <i>(14)</i> +
polaire <i>(16)</i> : <b>quatre cours dans un seul effet.</b>
</div>


<!--
Commencer par la loupe, sans animation. Autres exercices : spirale
(rayon = angle * 10, ofNoFill), amplitude qui pulse, period à la souris
(conversion (int)), teinte selon f.
-->
---
layout: default
breadcrumb: 5 — La géométrie / Cours 16
---

# À vous — polaire en liberté

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Une **spirale** : `rayon = angle * 10`, l'angle allant jusqu'à `6 * TWO_PI` — avec `ofNoFill()`
- **2 ·** Remplis chaque fleur d'une **teinte selon `f`** avec `ofColor::fromHsb`
- **3 ·** 🔥 **L'exercice final** (diapo précédente) : commence par la loupe, sans animation

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/16-fleurs-polaires.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/16-fleurs-polaires.md" download>md</a> · <a href="/ressources/ofApp16.h" download>ofApp16.h</a> · <a href="/ressources/ofApp16.cpp" download>ofApp16.cpp</a></p>

<!--
La loupe et le tourbillon sont le sommet du bloc : y consacrer le temps
qu'il faut, le tourbillon peut attendre la séance suivante.
-->


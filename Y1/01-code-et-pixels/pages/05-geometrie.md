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

Pour ça, il faut savoir mesurer une **distance** —
et l'image devient une **source de données**, la remarque
de la fin du cours 10 en action.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/12-pointillisme.png" alt="Le panda en gros points, trou autour du curseur" class="w-full object-contain" />
</div>

<!--
Mise en place : le .h porte img, windowWidth 774, windowHeight 516 et
tailleCercle 20 ; setup charge pandaroux.jpg avec la vérification du bool
(réflexe du cours 10). pandaroux.jpg va dans bin/data.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 12
---

# Étape 1 — la grille de points

```cpp
void ofApp::draw() {
    ofBackground(0);
    ofFill();

    for (int li = 0; li < windowHeight; li += tailleCercle) {      // chaque ligne...
        for (int co = 0; co < windowWidth; co += tailleCercle) {   // ...chaque colonne
            ofColor c = img.getColor(co, li);
            ofSetColor(c);
            ofDrawCircle(co, li, tailleCercle / 2.0f);
        }
    }
}
```

<div class="mt-3 text-sm">

<v-clicks>

- La double boucle du cours 11, mais les compteurs avancent **de 20 en 20** (`+= tailleCercle`, le pas du cours 03) : un pixel sur 400, un cercle par visite
- Les cercles se touchent, l'image se reconstitue — en gros points
- `img.draw` n'est **jamais** appelé : on lit les pixels, on dessine autre chose

</v-clicks>

</div>

<!--
Essaie : tailleCercle à 5, 10, puis 40 — à partir de quand ne reconnaît-on
plus l'image ? Puis des rectangles dont la hauteur dépend de la luminosité
du pixel.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 12
---

# Étape 2 — la distance : Pythagore

```cpp
// annoncée dans le .h :  float distance(float ax, float ay, float bx, float by);
float ofApp::distance(float ax, float ay, float bx, float by) {
    float dx = bx - ax;
    float dy = by - ay;
    return sqrt(dx * dx + dy * dy);
}
```

<div class="mt-4 text-sm">

<v-clicks>

- Deux points, un écart horizontal `dx`, un écart vertical `dy` : la distance est l'**hypoténuse** — `sqrt` est la racine carrée de `dx² + dy²`
- La fonction **renvoie un `float`** avec `return`, comme `filtre` renvoyait une `ofColor` au cours 11
- openFrameworks fournit `ofDist(ax, ay, bx, by)`, qui fait exactement ceci — on l'écrit une fois pour la voir, ensuite `ofDist`

</v-clicks>

</div>

<!--
Schéma img/12-pythagore.png dans le document : le triangle rectangle dx, dy, d.
Essaie : afficher dans la fenêtre la distance entre la souris et le centre de
l'image, vérifier à l'œil sur deux ou trois positions.
Cette distance se généralise en 3D pour les couleurs (cours 09) : exercice 4,
et le plusProche du 11g.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 12
---

# Étape 3 — la proportion : l'effet local

```cpp
            float d = distance(mouseX, mouseY, co, li);

            float rayon = tailleCercle / 2.0f;
            if (d <= 150) {
                float proportion = d / 150.0f;     // 0 sous la souris, 1 à 150 px
                rayon = rayon * proportion;
            }
            // ... puis ofDrawCircle(co, li, rayon)
```

<div class="mt-3 text-sm">

<v-clicks>

- À moins de 150 pixels, `d / 150` vaut entre 0 et 1 : le rayon est multiplié par cette **proportion** — nul sous la souris, normal à la frontière, un fondu entre les deux
- Le motif à retenir : **ramener entre 0 et 1, puis multiplier** — faire dépendre une chose d'une autre *en douceur*, au lieu d'un `if` brutal « près / loin »
- Un effet **local** = n'importe quel effet + un **masque** défini par une distance

</v-clicks>

</div>

<!--
Essaie : inverser l'effet — les cercles grossissent près de la souris. Une
seule expression à changer (1 - proportion, ou rayon / proportion bornée).
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 12
---

# Étape 4 — le temps dans la formule

```cpp
            float t = ofGetElapsedTimef() * 60;
            float prop = d / (200.0f + t);
            ofDrawRectangle(co, li, tailleCercle * prop, tailleCercle * prop);
```

<div class="mt-4 text-sm">

<v-clicks>

- Même mécanique, un `t` en plus dans la proportion : l'effet **grandit** — un anneau qui s'élargit depuis la souris
- Distance **et** temps (cours 07) dans la même formule : des animations riches pour trois lignes

</v-clicks>

</div>

<!--
Variante d'un autre sketch (en commentaire dans ofApp12.cpp). Essaie :
ralentir (* 10 au lieu de * 60), puis faire repartir l'anneau régulièrement
avec fmod (cours 09).
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 12
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — fenêtre 774 × 516, pas de 20 : combien de cercles la grille dessine-t-elle, environ ? Calcule, puis fais afficher le vrai compte dans la console.

</div>

<div v-click class="mt-4 text-base">

**2 · Le filtre local** — reprends un filtre du cours 11 (négatif, gris, seuil) et applique-le **seulement** aux cercles à moins de 150 pixels de la souris. Un filtre + un masque.

</div>

<div v-click class="mt-4 text-base">

**3 · Le projecteur** — l'image en points **gris** (luminance) partout… sauf près de la souris, où les points retrouvent leur **couleur**. Le color splash du cours 11, devenu local.

</div>

<!--
Ex 1 : 774 / 20 → 39 colonnes (0 à 760), 516 / 20 → 26 lignes (0 à 500) :
39 × 26 = 1014 cercles. Compter avec un int incrémenté dans la boucle, affiché
avec std::cout.
Ex 2 et 3 : le if (d <= 150) sert de masque — à l'intérieur, on transforme c
avant ofSetColor.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 12
---

# À vous (2/2)

<div class="mt-4 text-base">

**4 ·** 🔥 **L'image en cinq couleurs** — choisis cinq couleurs. Pour chaque cercle, calcule la distance dans le **cube RGB** (cours 09) entre le pixel et chacune des cinq — `sqrt(dr*dr + dg*dg + db*db)`, Pythagore en trois dimensions — et dessine avec la plus proche. Ton premier rendu en palette limitée.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/12-pointillisme.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/12-pointillisme.md" download>md</a> · <a href="/ressources/ofApp12.h" download>ofApp12.h</a> · <a href="/ressources/ofApp12.cpp" download>ofApp12.cpp</a> · <a href="/ressources/data/pandaroux.jpg" download>pandaroux.jpg</a></p>

<!--
Ex 4 : une variable meilleure distance initialisée très grande, un if par
couleur (ou une boucle sur un vector<ofColor>). Comparer les carrés évite le
sqrt. Il prépare le 11g.
-->

---
layout: split
breadcrumb: 5 — La géométrie / Cours 13
---

# Cours 13 — Des cercles sur un cercle

Douze cercles répartis sur un cercle invisible, qui
se rapprochent et s'éloignent du centre. Placer un point
« à tel angle, à telle distance » : c'est `cos` et `sin`.

<div class="mt-4 text-sm">

Le premier des quatre cours de trigonométrie.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/13-cercles.png" alt="Douze cercles RVB en fusion additive" class="w-full object-contain" />
</div>

<!--
Mise en place : le .h porte nbCercles 12, rayonOrbite 200 et t 1 ; fenêtre
800 × 800 dans setup.
-->

---
layout: split
breadcrumb: 5 — La géométrie / Cours 13
---

# Étape 1 — placer un point avec un angle

```cpp
    for (int i = 0; i < nbCercles; i++) {
        float angle = i * TWO_PI / nbCercles;
        float x = 400 + cos(angle) * rayonOrbite;
        float y = 400 - sin(angle) * rayonOrbite;
        ofDrawCircle(x, y, 40);
    }
```

<div class="mt-3 text-sm">

<v-clicks>

- `cos(a)` : la coordonnée **horizontale** d'un point du cercle de rayon 1 à l'angle `a` ; `sin(a)` : la **verticale**. On multiplie par le rayon, on ajoute le centre
- Le `-` devant `sin` : l'axe `y` de l'écran pointe vers le **bas** (cours 00)
- Les angles sont en **radians** : un tour = `TWO_PI` ≈ 6,28. Répartir `n` cercles : `i * TWO_PI / n`
- Le même `cos` que le cours 07 : quand l'angle avance, le point tourne — et son `x` oscille

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/13-trigo.png" alt="Cercle trigonométrique : le point est en (cos × rayon, −sin × rayon)" class="w-full object-contain" />
</div>

<!--
ofDegToRad(90) pour qui préfère penser en degrés.
Essaie : nbCercles à 3, 7, puis 36. Puis le rayon des petits cercles.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 13
---

# Étape 2 — déplacer l'origine

```cpp
    ofPushMatrix();
    ofTranslate(400, 400);                      // (0, 0) est maintenant au centre

    for (int i = 0; i < nbCercles; i++) {
        float angle = i * TWO_PI / nbCercles;
        float x = cos(angle) * rayonOrbite;     // plus de 400 +
        float y = -sin(angle) * rayonOrbite;
        ofDrawCircle(x, y, 40);
    }

    ofPopMatrix();
```

<div class="mt-3 text-sm">

<v-clicks>

- `ofTranslate(400, 400)` : tout ce qui est dessiné ensuite a son `(0, 0)` au centre de la fenêtre
- `ofPushMatrix` mémorise l'origine, `ofPopMatrix` la restaure — **toujours par paire** : après, on redessine normalement

</v-clicks>

</div>

<!--
Essaie : ofTranslate(mouseX, mouseY) — tout l'anneau suit la souris, sans
toucher aux formules.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 13
---

# Étape 3 — `%` : le reste qui fait alterner

```cpp
        if (i % 3 == 0)      ofSetColor(255, 0, 0);
        else if (i % 3 == 1) ofSetColor(0, 255, 0);
        else                 ofSetColor(0, 0, 255);
```

<div class="mt-4 text-sm">

<v-clicks>

- `i % 3` : le **reste** de la division entière de `i` par 3 — 0, 1, 2, 0, 1, 2… l'outil pour alterner, cycler, répartir en groupes
- `else if` enchaîne les conditions : la première vraie gagne, `else` attrape le reste
- `%` ne marche que sur des **entiers** ; pour les `float`, c'est `fmod` (cours 09)

</v-clicks>

</div>

<!--
Essaie : la roue des teintes du cours 09 EST un cercle —
ofSetColor(ofColor::fromHsb(i * 255.0f / nbCercles, 255, 255)) : chaque
cercle prend la couleur de son secteur. Deux idées de deux cours qui étaient
la même.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 13
---

# Étape 4 — les modes de fusion

```cpp
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    // ... la boucle de dessin
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);   // retour au mode normal
```

<div class="mt-4 text-sm">

<v-clicks>

- Par défaut, une forme **recouvre** ce qu'il y a dessous (en tenant compte de la transparence)
- En mode **additif**, les lumières s'**ajoutent** : rouge sur vert donne jaune, les trois donnent blanc — le cube RGB du cours 09, rendu visible aux intersections
- Autres modes : `SUBTRACT`, `MULTIPLY`, `SCREEN`. On revient **toujours** à `ALPHA` après

</v-clicks>

</div>

<!--
Essaie : fond blanc et OF_BLENDMODE_SUBTRACT — le négatif du mélange.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 13
---

# Étape 5 — l'animation : l'anneau qui respire

```cpp
void ofApp::update() {
    t = cos(ofGetElapsedTimef() * 0.6f);       // oscille entre -1 et 1
}

// dans draw() :
        float x = cos(angle) * rayonOrbite * t;
        float y = -sin(angle) * rayonOrbite * t;
```

<div class="mt-4 text-sm">

<v-clicks>

- `t` oscille entre −1 et 1 (cours 07) : les cercles se rapprochent du centre, **traversent** de l'autre côté quand `t` devient négatif, et repartent
- Une seule variable de temps, douze cercles qui respirent ensemble

</v-clicks>

</div>

<!--
Le .h porte float t { 1 }.
Essaie : faire aussi tourner l'ensemble — ajouter ofGetElapsedTimef() à angle.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 13
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — avec `nbCercles = 4` et le `- sin`, où sont les quatre cercles : haut / bas / gauche / droite, ou dans les coins ? Et le cercle `i = 1`, où exactement ? Réponds, puis vérifie.

</div>

<div v-click class="mt-4 text-base">

**2 · Les deux anneaux** — un second `for` : autre rayon d'orbite, autre nombre de cercles, et un sens de rotation **inverse** (soustrais le temps au lieu de l'ajouter).

</div>

<div v-click class="mt-4 text-base">

**3 · L'horloge** — une aiguille des secondes : un trait (`ofDrawLine`) du centre vers un point sur le cercle, qui fait exactement **un tour en 60 secondes**. Quelle formule d'angle ? Bonus : le sens horaire est l'inverse du sens trigonométrique.

</div>

<!--
Ex 1 : angles 0, π/2, π, 3π/2 → droite, HAUT (le - sin), gauche, bas. Le
cercle i = 1 est en haut : (400, 200).
Ex 3 : angle = ofGetElapsedTimef() * TWO_PI / 60 ; pour le sens horaire,
retirer le - devant sin (ou soustraire l'angle), et partir de midi : PI / 2.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 13
---

# À vous (2/2)

<div class="mt-4 text-base">

**4 ·** 🔥 **Le cercle cassé** — la variante du sketch d'origine : 120 petits cercles (rayon 10), fond blanc, mode `SUBTRACT`, et un décalage qui casse le cercle parfait :

```cpp
x += cos(i * 2.0f) * 20;
y += sin(i / 20.0f) * 100;
```

Observe comme deux petites perturbations suffisent à faire naître une forme organique.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/13-cercle-de-cercles.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/13-cercle-de-cercles.md" download>md</a> · <a href="/ressources/ofApp13.h" download>ofApp13.h</a> · <a href="/ressources/ofApp13.cpp" download>ofApp13.cpp</a></p>

<!--
Ex 4 : la variante est en commentaire à la fin d'ofApp13.cpp (rayon d'orbite
400). Le i / 20.0f : sans le .0f, division entière, la perturbation devient un
escalier.
-->

---
layout: split
breadcrumb: 5 — La géométrie / Cours 14
---

# Cours 14 — Filtres géométriques

Au cours 11, chaque pixel changeait de **couleur** mais
restait à sa place. Ici c'est l'inverse : la couleur ne
change pas, c'est la **position de lecture** qui change.

<div class="mt-4 text-sm">

Miroir, pixelisation, vagues, glitch — et une façon
de penser qui sert jusqu'aux shaders.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/14-geometrie.png" alt="Miroir, rotation, pixelisation, vagues, glitch" class="w-full object-contain" />
</div>

<!--
Mise en place : la même qu'au cours 11 (source, resultat, effet, parametre),
plus float t { 0 } et la liste des noms d'effets. pandaroux.jpg dans bin/data.
-->

---
layout: split
breadcrumb: 5 — La géométrie / Cours 14
---

# Lire à l'envers

```cpp
resultat(x, y) = source(f(x, y))
```

<div class="mt-4 text-sm">

<v-clicks>

- L'intuition — « prends chaque pixel de la source et déplace-le » — **ne marche pas** : des pixels du résultat recevraient deux couleurs, d'autres aucune — des trous
- On raisonne toujours **depuis le résultat** : pour chaque pixel `(x, y)` de sortie, où aller **chercher** sa couleur dans la source
- La boucle visite chaque pixel du résultat exactement une fois : l'image est toujours pleine
- C'est la façon de penser de **tous** les effets d'image, jusqu'aux shaders

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/14-lecture-inverse.png" alt="Pour chaque pixel du résultat, une flèche vers le pixel de la source à lire" class="w-full object-contain" />
</div>

<!--
Prendre le temps sur ce schéma : c'est l'idée du cours, le reste n'est que
des formules f.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 14
---

# Étape 1 — une lecture blindée, et la machine

```cpp
ofColor ofApp::lire(float x, float y) {                  // annoncée dans le .h
    int px = ofClamp((int)x, 0, source.getWidth() - 1);
    int py = ofClamp((int)y, 0, source.getHeight() - 1);
    return source.getColor(px, py);
}

// update() :  parametre = mouseX / (float)ofGetWidth();   t = ofGetElapsedTimef();
    int w = source.getWidth();
    int h = source.getHeight();
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            ofColor c = lire(x, y);          // identité : lire au même endroit
            resultat.setColor(x, y, c);
        }
    }
    resultat.update();
```

<div class="mt-2 text-sm">

- Un miroir ou une vague peut demander le pixel −5 ou le pixel 800 : on borne **une fois pour toutes**, dans une fonction (cours 10)
- `(int)x` **convertit** le `float` en entier en coupant la virgule — les coordonnées d'un pixel sont entières
- La machine commence par l'identité : l'image s'affiche, copiée pixel par pixel

</div>

<!--
Essaie : lire(x, y + 50) — l'image MONTE de 50 pixels. Lire plus bas fait
remonter l'image : la lecture à l'envers, à ressentir. Et regarder le bord :
le dernier pixel s'étire (l'effet du ofClamp).
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 14
---

# Étape 2 — miroir et rotation

```cpp
            switch (effet) {
            case 1:                              // miroir horizontal
                c = lire(w - 1 - x, y);
                break;
            case 2:                              // rotation de 180 degrés
                c = lire(w - 1 - x, h - 1 - y);
                break;
            default:
                c = lire(x, y);
            }
```

<div class="mt-3 text-sm">

<v-clicks>

- Le `switch` du cours 11 dans la boucle, et son `keyPressed` pour choisir l'effet — mais la formule porte sur **les coordonnées**, plus sur la couleur
- Le miroir : la colonne `x` du résultat vient de la colonne **opposée** de la source. La rotation : les deux axes retournés
- `break;` à la fin de chaque `case` : ici les branches ne font pas `return` (on est au milieu d'une boucle), c'est lui qui sort du `switch`

</v-clicks>

</div>

<!--
Essaie : le miroir vertical. Puis prédire : lire(w - 1 - x, h - 1 - y)
appliqué deux fois de suite ? (L'identité.)
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 14
---

# Étape 3 — la pixelisation

```cpp
            case 3: {
                int n = 2 + parametre * 40;
                c = lire(x / n * n, y / n * n);
                break;
            }
```

<div class="mt-4 text-sm">

<v-clicks>

- La **division entière** du cours 01, devenue un outil : `x / n * n` n'est **pas** `x` !
- Avec `n = 20` : `137 / 20 * 20 = 120` — tous les `x` de 120 à 139 lisent la colonne 120
- L'image se lit par cases de `n × n` : de gros pixels, réglés à la souris

</v-clicks>

</div>

<!--
Les accolades du case : nécessaires pour déclarer n à l'intérieur.
Essaie : fixer n à 2, 10, puis 60 — à partir de quand l'image devient-elle
méconnaissable ? Comparer avec la grille du cours 12 : deux chemins vers le
même effet. Même calcul que le centre de case du 15 et les blocs du 11d.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 14
---

# Étape 4 — les vagues

```cpp
            case 4: {
                float amplitude = parametre * 40;
                float dx = amplitude * sin(y / 20.0f + t * 3);
                c = lire(x + dx, y);
                break;
            }
```

<div class="mt-4 text-sm">

<v-clicks>

- Chaque **ligne** est décalée d'un sinus : `sin(y / 20.0f)` oscille le long de la hauteur
- `+ t * 3` fait glisser l'ondulation avec le temps ; `amplitude` la dose en pixels
- Le `sin` du cours 13, appliqué à une **position de lecture** — l'image ondule comme un drapeau

</v-clicks>

</div>

<!--
Essaie : des vagues verticales (décaler y selon x). Puis les deux à la fois.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 14
---

# Étape 5 — le glitch : un canal, un endroit

```cpp
            case 5: {
                float d = parametre * 30;
                ofColor gauche = lire(x - d, y);
                ofColor centre = lire(x, y);
                ofColor droite = lire(x + d, y);
                c = ofColor(gauche.r, centre.g, droite.b);
                break;
            }
```

<div class="mt-4 text-sm">

<v-clicks>

- Rien n'oblige les trois canaux à venir du **même** pixel : le rouge est lu à gauche, le bleu à droite
- Les contours se dédoublent en franges colorées — l'**aberration chromatique**, l'effet « écran abîmé » des jeux
- Trois lectures, une recomposition avec les `.r`, `.g`, `.b` de la struct `ofColor` (cours 09)

</v-clicks>

</div>

<!--
Essaie : pousser d très haut. Puis décaler un seul canal — lequel se voit le
plus ? (Le vert porte l'essentiel de la luminance : son décalage se voit le
plus.)
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 14
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — que fait `c = lire(x + 50, y);` : l'image se décale-t-elle vers la gauche ou vers la droite ? Et `lire(x * 2, y)` : zoom avant, ou arrière ? Réponds, puis vérifie — c'est LE test de la lecture à l'envers.

</div>

<div v-click class="mt-4 text-base">

**2 · Le kaléidoscope** — la moitié droite de l'image est le reflet de la moitié gauche : un `if (x > w / 2)` dans la formule. Puis fais pareil verticalement, pour un quadruple reflet.

</div>

<div v-click class="mt-4 text-base">

**3 · Le glitch de lignes** — des lignes entières décalées d'une valeur `ofRandom(-30, 30)` — avec `ofSeedRandom` pour que ça ne scintille pas (cours 03)… ou sans, pour que ça scintille exprès. Le vrai look « VHS abîmée ».

</div>

<!--
Ex 1 : lire plus à droite déplace l'image vers la GAUCHE ; x * 2 lit deux
fois plus loin : zoom ARRIÈRE (l'image rétrécit, le bord s'étire).
Ex 2 : if (x > w / 2) c = lire(w - 1 - x, y); else c = lire(x, y);
Ex 3 : tirer le décalage une fois par ligne (dans la boucle y, avant celle
sur x), pas par pixel.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 14
---

# À vous (2/2)

<div class="mt-4 text-base">

**4 ·** 🔥 **Le zoom** — `c = lire(x * 0.5f + w / 4, y * 0.5f + h / 4);` : un zoom ×2 centré. D'où viennent le `0.5f` et le `w / 4` ? Explique chaque nombre, puis écris le zoom **arrière**.

</div>

<div v-click class="mt-4 text-sm">

La loupe et le tourbillon, eux, demandent de passer en coordonnées polaires : on y revient à la fin du cours 16.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/14-filtres-geometriques.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/14-filtres-geometriques.md" download>md</a> · <a href="/ressources/ofApp14.h" download>ofApp14.h</a> · <a href="/ressources/ofApp14.cpp" download>ofApp14.cpp</a> · <a href="/ressources/data/pandaroux.jpg" download>pandaroux.jpg</a></p>

<!--
Ex 4 : 0.5f lit deux fois moins loin, donc agrandit ×2 ; w / 4 recentre : le
pixel central w/2 lit w/4 + w/4 = w/2. Zoom arrière : x * 2 - w / 2.
Excellente question de compréhension à poser à la salle.
-->

---
layout: split
breadcrumb: 5 — La géométrie / Cours 15
---

# Cours 15 — La grille en rotation

Une grille de 15 × 15 points, chacun tournant autour
du centre de sa case — mais pas tout à fait ensemble :
chaque case est légèrement décalée sur ses voisines,
et une **vague** traverse la grille.

<div class="mt-4 text-sm">

Ce décalage a un nom, le **déphasage** —
c'est l'idée du cours.

</div>

::right::

<div>
<img src="/ressources/cours/img/15-grille.png" alt="Grille de points avec cercles de construction" class="w-full object-contain" />
</div>

<!--
Le .h porte screenSize 400, rows et cols 15, tileSize et radius calculés
dans setup, speed 2.4, globalAngle, angleOffset.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 15
---

# Étape 1 — la grille de centres

```cpp
// setup() :
    ofSetWindowShape(screenSize, screenSize);
    tileSize = screenSize / (float)rows;
    radius = tileSize / 2;

// draw() :
    ofBackground(220);
    ofFill();
    ofSetColor(0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float x0 = i * tileSize + tileSize / 2;
            float y0 = j * tileSize + tileSize / 2;
            ofDrawCircle(x0, y0, 5);
        }
    }
```

<div class="mt-2 text-sm">

- 225 points immobiles, un au **centre** de chaque case : la case `(i, j)` commence en `(i * tileSize, j * tileSize)`, son centre est un demi-côté plus loin — la grille du cours 12, plus `+ tileSize / 2`
- `(float)rows` : `400 / 15` entre deux `int` donnerait 26 (division entière, cours 01) et la grille ne remplirait pas la fenêtre. La **conversion explicite** `(type)valeur`, déjà vue dans l'autre sens au cours 14 avec `(int)x`

</div>

<!--
Essaie : rows et cols à 5, puis à 30 — la grille s'adapte toute seule.
Pourquoi ? (tileSize est recalculé depuis rows.)
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 15
---

# Étape 2 — un point en orbite dans chaque case

```cpp
void ofApp::update() {
    globalAngle = globalAngle + speed * ofGetLastFrameTime();
}

void ofApp::drawPoint(int i, int j, float angle) {       // annoncée dans le .h
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

<div class="mt-2 text-sm">

- Les 225 points tournent **à l'unisson**. La formule du cours 13 **plus le centre** : au lieu d'`ofTranslate`, on ajoute `(x0, y0)` à la main — même résultat
- `globalAngle` avance à `speed` **radians par seconde** × `dt` : le cours 06 avec un angle à la place d'une position
- La double boucle **parcourt**, la fonction **dessine une case** : `drawPoint` ne sait rien de la grille

</div>

<!--
Essaie : décommenter les lignes de construction dans ofApp15.cpp — le cercle
et le rayon de chaque case : ofNoFill(); ofSetColor(180);
ofDrawCircle(x0, y0, radius); ofDrawLine(x0, y0, x, y). La mécanique devient
visible.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 15
---

# Étape 3 — le déphasage

```cpp
    angle = angle + i * angleOffset + j * angleOffset;   // première ligne de drawPoint
```

<div class="mt-4 text-sm">

<v-clicks>

- Même angle partout : tout tourne en bloc. Un décalage **qui dépend de la position de la case** : les voisines sont en avance ou en retard — et l'œil voit une **onde** traverser la grille
- La traînée évoluée du cours 07, généralisée : **une grandeur commune à tous, plus un décalage propre à chacun** — la grandeur commune est `globalAngle` (le temps), le décalage propre, la position
- `angleOffset` à 0.2 : une houle. À **75** : ça *semble* aléatoire alors que c'est parfaitement régulier — le tour fait 6.28, et 75 retombe « n'importe où » sur le cercle à chaque case

</v-clicks>

</div>

<!--
float angleOffset { 0.2f } dans le .h pour commencer ; la référence ofApp15
est livrée à 75.
Essaie : angleOffset à 0.1, 0.5, 1, puis 75. Puis un déphasage qui ne dépend
que de i : les colonnes ondulent ensemble.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 15
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — si `angleOffset` vaut exactement `PI`, que font deux cases voisines l'une par rapport à l'autre ? À quoi ressemble la grille ? Réponds, puis vérifie.

</div>

<div v-click class="mt-4 text-base">

**2 · Le champ d'aiguilles** — remplace le point par un **trait du centre au point** : `ofDrawLine(x0, y0, x, y);`. La grille devient un champ d'aiguilles magnétiques.

</div>

<div v-click class="mt-4 text-base">

**3 · La grille arc-en-ciel** — colore chaque point selon son angle : la teinte est un angle (cours 13, encore) — `ofColor::fromHsb(...)` en convertissant l'angle en 0-255. La vague devient une vague de couleur.

</div>

<!--
Ex 1 : deux voisines sont à l'opposé sur leur cercle (un demi-tour) — un
damier qui tourne, deux familles de points en opposition de phase.
Ex 3 : fmod(angle, TWO_PI) / TWO_PI * 255 — l'angle après déphasage, pour que
la couleur suive la vague.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 15
---

# À vous (2/2)

<div class="mt-4 text-base">

**4 ·** 🔥 **Les ondes circulaires** — remplace le déphasage `i + j` par un déphasage proportionnel à la **distance au centre de la fenêtre** (cours 12). Les vagues ne traversent plus la grille en diagonale : elles rayonnent depuis le centre, comme une pierre dans l'eau.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/15-grille-rotation.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/15-grille-rotation.md" download>md</a> · <a href="/ressources/ofApp15.h" download>ofApp15.h</a> · <a href="/ressources/ofApp15.cpp" download>ofApp15.cpp</a></p>

<!--
Ex 4 : angle + ofDist(x0, y0, 200, 200) * k, avec k petit (0.05) — la
distance du cours 12 revient, le faire remarquer.
-->

---
layout: split
breadcrumb: 5 — La géométrie / Cours 16
---

# Cours 16 — Fleurs polaires

Quatorze fleurs concentriques qui tournent à des
vitesses différentes. Derrière l'image : une nouvelle
façon de décrire un point, et une nouvelle façon
de dessiner.

<div class="mt-4 text-sm">

À la fin, l'exercice qui referme le cours 14 :
la loupe et le tourbillon.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/16-fleurs.png" alt="Fleurs emboîtées en mode additif" class="w-full object-contain" />
</div>

<!--
Le .h porte nbPoints 200, period, amplitude, nbFlowers 14 et la liste
rotations. Fenêtre 400 × 400.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 16
---

# Coordonnées polaires

```cpp
float x = rayon * cos(angle);
float y = rayon * sin(angle);
```

<div class="mt-5 text-sm">

<v-clicks>

- Un point était `(x, y)`. On peut aussi le décrire par `(angle, rayon)` : dans quelle **direction**, à quelle **distance** du centre — les coordonnées **polaires**
- Le passage vers `(x, y)` est la formule du cours 13
- Certaines formes sont simples en polaire et compliquées en cartésien : un cercle, « rayon constant » ; une spirale, « rayon qui grandit avec l'angle » ; une fleur… c'est l'étape 1

</v-clicks>

</div>

<!--
Schéma img/16-polaire.png du document : cercle gris de rayon r, fleur dont
le rayon oscille autour de r.
-->

---
layout: split
breadcrumb: 5 — La géométrie / Cours 16
---

# Étape 1 — une forme libre, point par point

```cpp
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    ofFill();
    ofSetColor(60, 20, 90);
    ofBeginShape();
    for (int i = 0; i < nbPoints; i++) {                  // 200 sommets
        float angle = i * TWO_PI / nbPoints;
        float fRadius = amplitude * cos(angle * period);
        float x = (100 + fRadius) * cos(angle);
        float y = (100 + fRadius) * sin(angle);
        ofVertex(x, y);
    }
    ofEndShape(true);                                     // true : fermer la forme

    ofPopMatrix();
```

<div class="mt-2 text-sm">

- **La forme libre** : `ofBeginShape()` ouvre, chaque `ofVertex(x, y)` ajoute un sommet, `ofEndShape(true)` ferme et remplit. 200 sommets, la courbe paraît lisse
- **Le rayon qui ondule** : `100 + amplitude * cos(angle * period)` — sur un tour, le cosinus oscille `period` fois : `period` **pétales**, hauts de `amplitude`

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/16-polaire.png" alt="Cercle gris de rayon r, fleur dont le rayon oscille autour de r" class="w-full object-contain" />
</div>

<!--
Essaie : period à 3, 5, 12 ; amplitude à 5, 40. Deux nombres contrôlent la
fleur.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 16
---

# Étape 2 — quatorze fleurs, quatorze vitesses (1/2)

```cpp
// setup() :
    rotations = std::vector<float>(nbFlowers, 0.0f);     // 14 zéros d'un coup

// update() :
    float dt = ofGetLastFrameTime();
    for (int f = 0; f < nbFlowers; f++) {
        float sens = (f % 2 == 0) ? 1.0f : -1.0f;
        float speed = f * 0.12f * sens;
        rotations[f] = rotations[f] + speed * dt;
    }
```

<div class="mt-3 text-sm">

<v-clicks>

- `std::vector<float>(n, valeur)` : une liste de `n` éléments d'un coup — au lieu de quatorze `push_back` (cours 04)
- Chaque fleur a sa **vitesse angulaire** (cours 15), proportionnelle à `f`, alternée en sens par le `%` du cours 13
- `condition ? valeurSiVrai : valeurSiFaux` : un `if` qui tient sur une ligne et **renvoie une valeur**

</v-clicks>

</div>

<!--
L'équivalent long : float sens; if (f % 2 == 0) sens = 1.0f; else sens = -1.0f;
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 16
---

# Étape 2 — quatorze fleurs, quatorze vitesses (2/2)

```cpp
void ofApp::drawFlower(int fIndex, float r, float rotation) {
    ofBeginShape();
    for (int i = 0; i < nbPoints; i++) {
        float angle = i * TWO_PI / nbPoints;
        float fRadius = amplitude * cos(angle * period);
        float x = (r + fRadius) * cos(angle + rotation);  // + rotation : la fleur tourne
        float y = (r + fRadius) * sin(angle + rotation);
        ofVertex(x, y);
    }
    ofEndShape(true);
}
// draw(), entre push et pop :
    for (int f = 0; f < nbFlowers; f++) {
        if (f % 2 == 0) ofSetColor(60, 20, 90);
        else            ofSetColor(20, 60, 90);
        drawFlower(f, 150 - f * 10, rotations[f]);
    }
```

<div class="mt-2 text-sm">

- La fleur rangée dans une fonction : le rayon `r` et la `rotation` deviennent des paramètres
- Quatorze rayons décroissants (`150 - f * 10`) : des fleurs emboîtées, les extérieures lentes, les intérieures rapides

</div>

<!--
Essaie : une seule fleur dont period dépend de la souris — period est un
entier, donc mouseX / 50 (division entière assumée). Puis faire pulser
amplitude avec le temps (cours 07).
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 16
---

# Étape 3 — le mode additif au travail

```cpp
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    // ... les quatorze fleurs
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
```

<div class="mt-5 text-sm">

<v-clicks>

- Deux couleurs **sombres** alternées : là où les fleurs se recouvrent, les couleurs s'ajoutent et s'éclaircissent (cours 13)
- Les recouvrements deviennent lisibles — des formes opaques se cacheraient mutuellement

</v-clicks>

</div>

<!--
Essaie : remplacer les deux couleurs fixes par une teinte selon f
(ofColor::fromHsb) — quatorze fleurs, quatorze secteurs de la roue.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 16
---

# L'exercice final — loupe et tourbillon

<div class="mt-4 text-base">

Avec la lecture « à l'envers » du cours 14, pour chaque pixel `(x, y)` du résultat :

<v-clicks>

1. **Cartésien → polaire** autour de la souris : `dx = x - mouseX`, `dy = y - mouseY`, `r = sqrt(dx*dx + dy*dy)`, `angle = atan2(dy, dx)` — `atan2` fait l'inverse de `cos` / `sin` : il retrouve l'angle d'un vecteur
2. **Modifier** : loupe → `r = r * 0.5f` si `r < R` ; tourbillon → `angle = angle + k * (1 - r / R)` si `r < R`
3. **Polaire → cartésien** : `sx = mouseX + r * cos(angle)`, `sy = mouseY + r * sin(angle)`
4. **Lire** la source en `(sx, sy)` avec la fonction bornée, écrire dans le résultat en `(x, y)`

</v-clicks>

</div>

<div v-click class="mt-5 text-base">
Le <code>1 - r / R</code> du tourbillon est la proportion du cours 12 : rotation maximale au centre, nulle au bord, pour raccorder sans cassure. Distance <i>(12)</i> + trigonométrie <i>(13)</i> + lecture inverse <i>(14)</i> + polaire <i>(16)</i> : <b>quatre cours dans un seul effet.</b>
</div>

<!--
Commencer par la loupe, sans animation. Le tourbillon peut attendre la séance
suivante. C'est l'exercice 4 de la diapo À vous (2/2).
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 16
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — avec `period = 1` et `amplitude = 50`, à quoi ressemble la « fleur » ? Et avec `period = 0` ? Réponds en pensant au cosinus, puis vérifie.

</div>

<div v-click class="mt-4 text-base">

**2 · La spirale** — « un rayon qui grandit avec l'angle » : `rayon = angle * 10`, avec un angle qui va de 0 à `6 * TWO_PI` (six tours). `ofNoFill()` avant `ofBeginShape`, et ne ferme pas la forme (`ofEndShape(false)`).

</div>

<div v-click class="mt-4 text-base">

**3 · L'étoile de mer** — une fleur dont l'amplitude **elle-même** ondule lentement avec le temps, et dont la rotation suit la souris (`atan2(mouseY - 200, mouseX - 200)` donne l'angle sous lequel la souris voit le centre — l'inverse de `cos`/`sin`, qui sert aussi dans l'exercice final).

</div>

<!--
Ex 1 : period = 1, une seule bosse — un cercle décentré (un « œuf ») ;
period = 0, cos(0) = 1 partout : un cercle parfait de rayon r + amplitude.
Ex 2 : la boucle va jusqu'à 6 * nbPoints, angle = i * TWO_PI / nbPoints.
-->

---
layout: default
breadcrumb: 5 — La géométrie / Cours 16
---

# À vous (2/2)

<div class="mt-4 text-base">

**4 ·** 🔥 **La loupe, puis le tourbillon** — réalise l'exercice final (diapo précédente), dans cet ordre : la loupe d'abord, sans animation ; le tourbillon ensuite. C'est le sommet des cours 12 à 16 — prends le temps.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/16-fleurs-polaires.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/16-fleurs-polaires.md" download>md</a> · <a href="/ressources/ofApp16.h" download>ofApp16.h</a> · <a href="/ressources/ofApp16.cpp" download>ofApp16.cpp</a></p>

<!--
Ex 4 : repartir de la machine du cours 14 (source / resultat / lire). R = 150,
k = 3 pour commencer. Y consacrer le temps qu'il faut.
-->

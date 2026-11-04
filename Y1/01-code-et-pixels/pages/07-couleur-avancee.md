---
layout: section
breadcrumb: 7 — La couleur avancée
---

# La couleur avancée

Sept leçons : la couleur telle que la manipulent les studios

<!--
Le bloc annoncé par le cours 09a — on y arrive maintenant parce que tous les
outils sont là : la double boucle du 11, la distance du 12, les gros pixels
du 14, le polaire du 16, l'indice y·w+x du 17. Toutes ces leçons utilisent
la machine du cours 11 : double boucle, source, résultat, une formule par
pixel. 11a est nécessaire à 11b, 11e et 11f ; le reste se pioche.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11a Gamma
---

# Cours 11a — Gamma et espace linéaire

Le sujet **le plus important** de la série, et le plus
souvent ignoré : les nombres de 0 à 255 ne mesurent
pas la lumière.

<div class="mt-4 text-sm">

<v-clicks>

- Tant qu'on affiche, aucune importance. **Dès qu'on calcule, tout devient faux**
- Trois vues, touches 1 à 3 : les dégradés, le mélange, l'image

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11a-image.png" alt="Assombrir de moitié : naïf vs linéaire" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">Diviser la lumière par deux : à gauche le calcul naïf, beaucoup trop sombre.</p>
</div>

<!--
Avant : cours 11 (filtre par pixel) et 09a (le voyage de la couleur).
Fichiers : ofApp11a + pandaroux.jpg. Flou, dégradé, transparence : tout
mélange de couleurs a ce problème.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11a Gamma
---

# Étapes 1-2 — `versLineaire()` et `versSRGB()`

```cpp
float ofApp::versLineaire(float c) {   // valeur 0-255 → lumière 0-1
    return pow(c / 255.0f, 2.2f);
}

float ofApp::versSRGB(float l) {       // lumière 0-1 → valeur 0-255
    l = ofClamp(l, 0, 1);
    return 255.0f * pow(l, 1.0f / 2.2f);
}
```

<div class="mt-3 text-sm">

<v-clicks>

- `pow(a, b)` : « a puissance b ». `pow(0.5, 2.2)` vaut 0,22 : **la valeur 128 code 22 % de la lumière** du blanc ; 50 % de lumière se code 186
- L'œil distingue finement les sombres : la courbe **sRGB** (« gamma 2.2 ») dépense les 256 niveaux là où on les voit
- La vraie courbe est en deux morceaux ; **l'approximation 2.2 suffit** pour comprendre et pour presque tous les effets

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11a-degrades.png" alt="Dégradé par valeur et dégradé par lumière" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">En haut la valeur monte régulièrement, en bas la lumière : le milieu du bas s'écrit 186.</p>
</div>

<!--
Vue 1 de la démo : les deux dégradés. Le milieu du dégradé par valeur paraît
déjà clair. Ces deux fonctions reviennent telles quelles en 11b, 11e et 11f —
on ne les remontrera pas.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11a Gamma
---

# Étape 3 — `setup()` : une table pour éviter `pow`

```cpp
// ofApp.h :  std::vector<float> tableLineaire;   // tableLineaire[c] = versLineaire(c)

void ofApp::setup() {
    ofSetWindowShape(774, 516);
    if (!source.load("pandaroux.jpg")) {
        ofLogError() << "pandaroux.jpg introuvable dans bin/data";
    }
    resultat.allocate(source.getWidth(), source.getHeight(), OF_IMAGE_COLOR);

    for (int c = 0; c < 256; c++) {
        tableLineaire.push_back(versLineaire(c));
    }
}
```

<div class="mt-3 text-sm">

<v-clicks>

- `pow` est lent, mais un canal n'a que **256 valeurs d'entrée possibles** : on calcule les 256 résultats une fois, puis on **lit la liste**
- L'indice de la liste est la valeur d'entrée : `tableLineaire[128]` contient `versLineaire(128)` — une **table de correspondance**, l'idée que le cours 11c généralise
- Le retour vers sRGB part d'un `float` quelconque, pas d'une des 256 valeurs : lui garde `pow`

</v-clicks>

</div>

<!--
Mise en place du .h : source, resultat, la table, vue (1-3), facteur et
dernierFacteur. Le cours 11 avait déjà source / resultat / allocate.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11a Gamma
---

# Étape 4 — `calculerImage()` : en linéaire

```cpp {5-6|7-11}
for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
        ofColor c = source.getColor(x, y);
        ofColor sortie;
        if (x < w / 2) {       // NAÏF : on multiplie directement les valeurs 0-255
            sortie = ofColor(ofClamp(c.r * facteur, 0, 255), /* g, b */);
        } else {               // JUSTE : on multiplie la LUMIÈRE
            float r = tableLineaire[c.r] * facteur;      // 1. décoder  2. calculer
            float g = tableLineaire[c.g] * facteur;
            float b = tableLineaire[c.b] * facteur;
            sortie = ofColor(versSRGB(r), versSRGB(g), versSRGB(b));   // 3. réencoder
        }
        resultat.setColor(x, y, sortie);
    }
}
resultat.update();
```

<div class="mt-2 text-sm">

- Diviser la lumière par deux = fermer l'objectif d'un cran. Le calcul naïf divise des valeurs **déjà compressées** : la lumière est divisée par plus de quatre
- C'est le réglage « **Linear** » des moteurs, et la case « sRGB » des textures — la cocher à tort rend un matériau délavé

</div>

<!--
L'image est coupée en deux verticalement : la comparaison se fait à l'écran,
souris = facteur ×0.25 à ×4, et la différence change de sens quand on
éclaircit.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11a Gamma
---

# Étape 5 — `update()` : recalculer au besoin

```cpp
void ofApp::update() {
    // 0.25 à 4 : la souris au milieu donne 1 (image inchangée)
    facteur = pow(2.0f, (mouseX / (float)ofGetWidth()) * 4 - 2);
    if (vue == 3 && facteur != dernierFacteur) {
        calculerImage();
        dernierFacteur = facteur;      // on mémorise, on compare
    }
}

void ofApp::keyPressed(int key) {
    if (key >= '1' && key <= '3') {
        vue = key - '0';
        dernierFacteur = -1;           // force le recalcul de la vue 3
    }
}
```

<div class="mt-3 text-sm">

<v-clicks>

- Recalculer 400 000 pixels à chaque frame ralentirait tout : on mémorise le dernier facteur et on **compare** — l'image n'est recalculée que quand la souris a bougé
- `key - '0'` transforme le caractère `'3'` en nombre 3 (cours 11) ; remettre `dernierFacteur` à −1 force un recalcul au changement de vue

</v-clicks>

</div>

<!--
Le drapeau « recalculer seulement si le paramètre a changé » revient dans
tout le bloc (11b avec deux conditions, 11c, 11f).
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11a Gamma
---

# Étape 6 — `draw()` : le mélange trop sombre

```cpp
// vue 2 : damier rouge / vert de 2 px — recule-toi
for (int y = 100; y < 300; y += 2) {
    for (int x = 60; x < 260; x += 2) {
        bool pair = ((x / 2) + (y / 2)) % 2 == 0;
        if (pair) ofSetColor(255, 0, 0); else ofSetColor(0, 255, 0);
        ofDrawRectangle(x, y, 2, 2);
    }
}
ofSetColor(128, 128, 0);               // moyenne des valeurs
ofDrawRectangle(290, 100, 200, 200);
float v = versSRGB(0.5f);              // moyenne de la lumière : 186
ofSetColor(v, v, 0);
ofDrawRectangle(520, 100, 200, 200);
```

<div class="mt-2 text-sm">

<v-clicks>

- L'œil moyenne les **lumières** et voit un jaune vif ; la moyenne des **valeurs** `(255 + 0) / 2 = 128` donne un olive sombre
- Flou boîte du 17, `getLerped` du 09, transparence à 50 % : **tout mélange calculé naïvement** est trop sombre

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11a-melange.png" alt="Damier rouge-vert, moyenne des valeurs, moyenne de la lumière" class="w-full object-contain" />
</div>

<!--
La vue 1 (dégradés) trace deux bandes ligne par ligne : ofSetColor(p * 255)
contre ofSetColor(versSRGB(p)). La vue 3 affiche resultat avec un trait au
milieu.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11a Gamma
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · La vraie courbe sRGB** — remplace l'approximation 2.2 dans `versLineaire` par la courbe en deux morceaux, où `s` est la valeur entre 0 et 1 :

```cpp
float lineaire = s <= 0.04045 ? s / 12.92 : pow((s + 0.055) / 1.055, 2.4);
```

Compare avec la version 2.2 : la différence est-elle visible ?

</div>

<div v-click class="mt-4 text-base">

**2 ·** 🔥 **Le flou en linéaire** — refais le flou boîte du cours 17 en linéaire : décoder les voisins, moyenner les lumières, réencoder. Compare sur les moustaches blanches du panda : lequel des deux flous les assombrit ?

</div>

<!--
Ex 1 : `? :` est l'opérateur du cours 16. La différence est surtout visible
dans les sombres. Ex 2 : la moyenne naïve assombrit les contours clairs — la
démonstration du damier appliquée à une vraie image.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11a Gamma
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · Le dégradé en linéaire** — le dégradé entre deux couleurs du cours 09, calculé en linéaire : décoder A et B, interpoler, réencoder. Lequel des deux dégradés est le plus lumineux au milieu ?

</div>

<div v-click class="mt-5 text-base">

**4 · Le gris et le damier** — affiche côte à côte un gris `(128, 128, 128)` et un damier noir-blanc de 1 pixel. Sont-ils pareils de loin ? Quel gris uni ressemble au damier ?

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11a-gamma.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11a-gamma.md" download>md</a> · <a href="/ressources/ofApp11a.h" download>ofApp11a.h</a> · <a href="/ressources/ofApp11a.cpp" download>ofApp11a.cpp</a> · <a href="/ressources/data/pandaroux.jpg" download>pandaroux.jpg</a></p>

<!--
Ex 3 : le dégradé linéaire est plus lumineux au milieu, celui de getLerped
passe par un milieu terne. Ex 4 : le damier moyenne les lumières, 50 % de
lumière = valeur 186 : c'est le gris 186 qui ressemble au damier. LA
démonstration du gamma en deux lignes de code.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11b Tone mapping
---

# Cours 11b — HDR, exposition et tone mapping

Dans un moteur, la lumière d'une scène n'a **pas de
plafond** : ciel à 10, lampe à 100, soleil à des milliers.
L'écran, lui, s'arrête à 1.

<div class="mt-4 text-sm">

<v-clicks>

- L'**exposition** multiplie la lumière, en *stops* — chaque stop double
- Le **tone mapping** est la courbe qui ramène tout sous 1
- La troisième courbe est l'**ACES** d'Unreal et d'Unity

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11b-tonemapping.png" alt="Clamp, Reinhard et ACES comparés" class="w-full object-contain" />
</div>

<!--
Avant : 11a. Pas de vraie image HDR ici : on triche en poussant l'exposition
jusqu'à ce que la moitié de l'image dépasse 1. Les moteurs calculent
l'éclairage en float sans se soucier des limites ; le problème arrive à la
fin : afficher. Mise en place : mêmes convertisseurs et table qu'en 11a.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11b Tone mapping
---

# Étape 3 — `toneMap()` : ramener sous 1

```cpp
float ofApp::toneMap(float x) {      // lumière HDR (0 → ∞) → lumière écran (0-1)
    switch (methode) {
    case 2:
        return x / (1.0f + x);       // Reinhard : tend vers 1 sans l'atteindre
    case 3: {                        // ACES (approximation de Narkowicz)
        float a = 2.51f, b = 0.03f, c = 2.43f, d = 0.59f, e = 0.14f;
        return ofClamp((x * (a * x + b)) / (x * (c * x + d) + e), 0, 1);
    }
    default:
        return ofClamp(x, 0, 1);     // couper : tout ce qui dépasse devient 1
    }
}
```

<div class="mt-3 text-sm">

<v-clicks>

- **Couper** : les zones claires deviennent des taches blanches plates — « brûlées »
- **Reinhard** : rien ne brûle, mais tout grise — une entrée de 1 sort à 0,5, les blancs ne sont jamais blancs
- **ACES** : la courbe en S « pellicule » — ombres écrasées, tons moyens contrastés, hautes lumières compressées en douceur

</v-clicks>

</div>

<!--
« ACES » désigne en réalité tout un système de gestion de couleur du cinéma ;
les moteurs n'en prennent que la courbe finale, dans cette approximation à
cinq nombres de Krzysztof Narkowicz que tout le monde copie. Une fonction qui
renvoie un float : f(x) sous forme de code.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11b Tone mapping
---

# Étape 5 — `calculerImage()` : le pipeline complet

```cpp
void ofApp::calculerImage() {
    int w = source.getWidth();
    int h = source.getHeight();
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            ofColor c = source.getColor(x, y);
            // 1. sRGB → lumière   2. exposition   3. tone mapping   4. lumière → sRGB
            float r = toneMap(tableLineaire[c.r] * exposition);
            float g = toneMap(tableLineaire[c.g] * exposition);
            float b = toneMap(tableLineaire[c.b] * exposition);
            resultat.setColor(x, y, ofColor(versSRGB(r), versSRGB(g), versSRGB(b)));
        }
    }
    resultat.update();
}
```

<div class="mt-3 text-sm">

<v-clicks>

- **Décoder → exposer → tone mapper → réencoder** : à peu de choses près, la fin du pipeline de rendu d'un jeu moderne, le « post-process »
- L'« exposition automatique » d'un jeu ne fait que choisir le facteur selon la luminosité moyenne de l'image

</v-clicks>

</div>

<!--
setup() : identique au 11a (fenêtre, image, allocate, table). La scène est
calculée en HDR linéaire, puis exposition + tone mapping, puis encodage pour
l'écran.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11b Tone mapping
---

# Étape 6 — `update()` : l'exposition en stops

```cpp
void ofApp::update() {
    float stops = (mouseX / (float)ofGetWidth()) * 6 - 2;    // -2 à +4
    exposition = pow(2.0f, stops);                           // chaque stop double
    if (exposition != derniereExposition || methode != derniereMethode) {
        calculerImage();
        derniereExposition = exposition;
        derniereMethode = methode;
    }
}

void ofApp::keyPressed(int key) {
    if (key >= '1' && key <= '3') methode = key - '0';
}
```

<div class="mt-3 text-sm">

<v-clicks>

- La souris va de −2 stops (×0,25) à +4 stops (×16) ; à +2, **la moitié de l'image dépasse déjà 1**
- Le drapeau du 11a, avec **deux conditions** reliées par `||` (cours 06 bis) : la souris ou la touche

</v-clicks>

</div>

<!--
C'est à +2 stops que les trois méthodes divergent à l'écran : montrer les
trois touches à cette exposition.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11b Tone mapping
---

# Étape 7 — `draw()` : tracer une courbe

```cpp
// entrée 0..4 en x, sortie 0..1 en y
int gx = 570, gy = 20, gw = 190, gh = 120;
ofDrawRectangle(gx + gw / 4, gy, 1, gh);   // entrée = 1 : le blanc de l'écran

for (int i = 0; i < gw - 1; i++) {
    float x0 = i / (float)gw * 4;
    float x1 = (i + 1) / (float)gw * 4;
    ofDrawLine(gx + i,     gy + gh - toneMap(x0) * gh,
               gx + i + 1, gy + gh - toneMap(x1) * gh);
}
```

<div class="mt-3 text-sm">

<v-clicks>

- La recette pour dessiner **n'importe quelle fonction** : un petit segment par pixel horizontal — calculer l'entrée, appeler la fonction, convertir la sortie en hauteur
- `gy + gh - ...` retourne l'axe : `y` pointe vers le bas (cours 00)
- À droite de « entrée = 1 » : couper est plat, Reinhard monte lentement, ACES s'aplatit près de 1

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11b-courbes.png" alt="Courbes couper, Reinhard, ACES" class="w-full object-contain" />
</div>

<!--
Regarder aussi à gauche de la ligne : Reinhard assombrit déjà les tons
moyens, ACES les garde contrastés. Le reste de draw() : l'image, le cadre
de la courbe, les textes.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11b Tone mapping
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Reinhard étendu** — une quatrième méthode : `x * (1 + x / (Lb * Lb)) / (1 + x)`, où `Lb` est la lumière qui doit devenir exactement blanche. Essaie `Lb = 4` : les blancs redeviennent blancs.

</div>

<div v-click class="mt-5 text-base">

**2 · Sur la luminance seulement** — applique le tone mapping à la **luminance** (cours 11), puis multiplie `r`, `g`, `b` par le rapport `nouvelle / ancienne`. Les couleurs saturées ne virent plus au blanc en surexposition. Compare avec la version par canal.

</div>

<!--
Ex 1 : un case 4 dans toneMap et la touche 4. Ex 2 : luminance 0.299 r +
0.587 g + 0.114 b sur les lumières linéaires ; attention au rapport quand
l'ancienne luminance est 0.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11b Tone mapping
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · L'exposition automatique** — calcule la lumière moyenne de l'image dans `setup()`, et choisis l'exposition pour que cette moyenne tombe à 0.18 : le « gris moyen » des photographes.

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Une vraie image HDR** — `ofFloatImage img; img.load("scene.hdr");` donne directement des valeurs au-dessus de 1. Il en existe des gratuites sur les sites de textures : charge-en une et passe-la par les trois courbes.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11b-tone-mapping.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11b-tone-mapping.md" download>md</a> · <a href="/ressources/ofApp11b.h" download>ofApp11b.h</a> · <a href="/ressources/ofApp11b.cpp" download>ofApp11b.cpp</a> · <a href="/ressources/data/pandaroux.jpg" download>pandaroux.jpg</a></p>

<!--
Ex 3 : exposition = 0.18 / moyenne. Ex 4 : ofFloatImage se lit avec
getColor comme ofImage, mais les composantes sont des float déjà linéaires :
sauter l'étape « décoder ».
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11c LUT
---

# Cours 11c — LUT et étalonnage

**Toute** transformation d'un canal tient dans une table
de 256 valeurs : la LUT (*look-up table*). C'est l'outil
de l'étalonnage cinéma et du color grading des jeux.

<div class="mt-4 text-sm">

<v-clicks>

- Au cours 11, chaque filtre était une formule appliquée 400 000 fois ; au 11a, 256 résultats précalculés
- La différence n'est pas **ce qu'on** calcule, mais **quand** : une fois pour les 256 valeurs possibles, au lieu d'une fois par pixel

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11c-looks.png" alt="Quatre looks et leurs courbes" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">Identité, contraste, teal &amp; orange, vintage — et leurs courbes.</p>
</div>

<!--
Avant : cours 11 (courbes de transfert) et 11a (table précalculée). Tous les
filtres par canal du cours 11 étaient déjà des LUT sans le savoir — le
négatif est le look n°4 pour le prouver.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11c LUT
---

# Étapes 1-2 — `setup()` et `courbeS()`

```cpp
// ofApp.h :  std::vector<int> lutR, lutG, lutB;    // 256 entrées chacune
//            int look = 0;  float force = 1;

void ofApp::setup() {
    ofSetWindowShape(774, 516);
    source.load("pandaroux.jpg");
    resultat.allocate(source.getWidth(), source.getHeight(), OF_IMAGE_COLOR);
    lutR = std::vector<int>(256, 0);      // 256 cases à zéro
    lutG = std::vector<int>(256, 0);
    lutB = std::vector<int>(256, 0);
}

float ofApp::courbeS(float t) {           // 0-1 → 0-1, en S
    return t * t * (3 - 2 * t);
}
```

<div class="mt-2 text-sm">

<v-clicks>

- Une LUT par canal : dans la case numéro `i`, la valeur que doit devenir un pixel dont le canal vaut `i`
- `std::vector<int>(256, 0)` : une liste de 256 cases, toutes à zéro — on les remplira par `lutR[i] = ...`, pas par `push_back`
- La courbe en S est la « **smoothstep** » : 0 en 0, 1 en 1, pente nulle aux deux bouts — elle écrase doucement les extrêmes, on la retrouve partout en animation

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11c-lut.png" alt="Une LUT : l'entrée est l'indice, la sortie le contenu de la case" class="w-full object-contain" />
</div>

<!--
Même idée que tableLineaire[c.r] du 11a, avec trois tables et n'importe
quelle formule dedans. Le .h porte aussi derniereForce / dernierLook pour le
drapeau, et la liste des noms de looks.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11c LUT
---

# Étape 3 — `construireLut()` (1/2) : 256 tours

```cpp {1-4|6-9|10-14}
void ofApp::construireLut() {
    for (int i = 0; i < 256; i++) {
        float t = i / 255.0f;              // l'entrée, entre 0 et 1
        float r = t, g = t, b = t;         // identité par défaut

        switch (look) {
        case 1:                            // contraste : la même courbe en S, trois fois
            r = g = b = courbeS(t);
            break;
        case 2:                            // teal & orange, le look du cinéma d'action
            r = ofClamp(t + 0.12f * sin(t * PI), 0, 1);                      // bosse au milieu : + de rouge
            g = t;
            b = ofClamp(t - 0.12f * sin(t * PI) + 0.10f * (1 - t), 0, 1);  // - de bleu en clair, + en sombre
            break;
```

<div class="mt-2 text-sm">

- Pour chaque entrée possible, on calcule la sortie et on la range : le « filtre » du cours 11, mais calculé **une fois** pour les 256 valeurs
- Trois tables **identiques** = contraste, luminosité. Trois tables **différentes** = on colore : c'est l'**étalonnage**
- Teal &amp; orange : peaux orangées, ombres bleu-vert — un étalonneur passe sa journée à déplacer ces trois courbes

</div>

<!--
Quand il y a moins d'entrées possibles que de pixels, la table gagne
toujours. Le négatif est 1 - t, le seuil t < s ? 0 : 1, la postérisation un
escalier : tous des LUT.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11c LUT
---

# Étape 3 — `construireLut()` (2/2) : la force

```cpp {1-9|11-14}
        case 3:                            // vintage : noirs relevés à 12 %, blancs plafonnés à 92 %
            r = 0.12f + t * 0.80f + 0.04f; // et un léger voile chaud
            g = 0.12f + t * 0.80f;
            b = 0.12f + t * 0.76f;
            break;
        case 4:                            // négatif : la preuve que les filtres du cours 11 sont des LUT
            r = g = b = 1 - t;
            break;
        }

        // force : on interpole entre l'identité (t) et le look (r)
        lutR[i] = ofClamp((t + (r - t) * force) * 255, 0, 255);
        lutG[i] = ofClamp((t + (g - t) * force) * 255, 0, 255);
        lutB[i] = ofClamp((t + (b - t) * force) * 255, 0, 255);
    }
}
```

<div class="mt-2 text-sm">

- La **force** interpole entre l'identité `t` et le look `r` : `getLerped` du cours 09 appliqué à une valeur — 0 donne l'image d'origine, 1 le look complet, 0,5 la moitié
- Le curseur d'intensité de tous les logiciels d'étalonnage est fait **exactement comme ça**

</div>

<!--
La souris règle la force (update). Vintage : les noirs ne sont plus noirs,
voile chaud.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11c LUT
---

# Étape 4 — `appliquerLut()` : trois lectures par pixel

```cpp
void ofApp::appliquerLut() {
    int w = source.getWidth();
    int h = source.getHeight();
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            ofColor c = source.getColor(x, y);
            resultat.setColor(x, y, ofColor(lutR[c.r], lutG[c.g], lutB[c.b]));
        }
    }
    resultat.update();
}
```

<div class="mt-4 text-sm">

<v-clicks>

- Plus **aucun calcul** par pixel : la valeur du pixel sert d'**indice** de la table
- Limite : trois tables indépendantes ne peuvent pas **désaturer** — rendre gris mélange les canaux, et `lutR` ne connaît que le rouge. Le sépia du 11 et le daltonisme du 11f sont des matrices
- Le cinéma utilise des **LUT 3D** (grilles 17³ ou 33³, chaque triplet pointe vers une couleur complète) : le format `.cube` que chargent aussi les moteurs de jeu

</v-clicks>

</div>

<!--
C'est la double boucle du cours 11, avec une lecture à la place de la
formule.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11c LUT
---

# Étapes 5-6 — `update()` et `draw()` : les trois courbes

```cpp
void ofApp::update() {
    force = mouseX / (float)ofGetWidth();
    if (force != derniereForce || look != dernierLook) {   // le drapeau du 11b
        construireLut();
        appliquerLut();
        derniereForce = force;  dernierLook = look;
    }
}

// draw() : les trois courbes, entrée en x, sortie en y — tracées comme au 11b
ofDrawLine(gx, gy + gs, gx + gs, gy);          // la diagonale = identité
for (int i = 0; i < 255; i++) {
    float x0 = gx + i * gs / 255.0f, x1 = gx + (i + 1) * gs / 255.0f;
    ofSetColor(255, 80, 80);
    ofDrawLine(x0, gy + gs - lutR[i] * gs / 255.0f, x1, gy + gs - lutR[i + 1] * gs / 255.0f);
    // idem lutG en vert, lutB en bleu
}
```

<div class="mt-2 text-sm">

<v-clicks>

- Le look, c'est la **forme de ces trois courbes** ; la diagonale grise est l'identité
- `keyPressed` : touches 0 à 4 pour le look, `look = key - '0'`

</v-clicks>

</div>

<!--
Ici la LUT est tracée directement : une case par pixel horizontal, pas
besoin de rappeler la fonction.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11c LUT
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Charger une LUT depuis une image** — une bande de 256 × 1 pixels : `lutR[i] = bande.getColor(i, 0).r`. Fabrique la bande dans un logiciel de retouche : applique tes réglages à un dégradé de 256 pixels et exporte-le. Tes réglages sont maintenant dans ton programme.

</div>

<div v-click class="mt-5 text-base">

**2 · Le cours 11 en LUT** — le seuil, la postérisation et le gamma du cours 11, refaits en LUT : un `case` chacun.

</div>

<!--
Ex 1 est le pont vers le vrai pipeline d'étalonnage : à faire faire
absolument. Ex 2 : seuil t < s ? 0 : 1, postérisation floor(t * n) / n,
gamma pow(t, g).
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11c LUT
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · Le look « nuit »** — tout tire vers le bleu, les rouges sont écrasés. Trois courbes différentes, à toi de les inventer.

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Le fondu** — deux looks et une touche pour passer de l'un à l'autre **en fondu** : interpoler les deux tables avec un `float` qui avance avec le temps (cours 06).

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11c-lut.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11c-lut.md" download>md</a> · <a href="/ressources/ofApp11c.h" download>ofApp11c.h</a> · <a href="/ressources/ofApp11c.cpp" download>ofApp11c.cpp</a> · <a href="/ressources/data/pandaroux.jpg" download>pandaroux.jpg</a></p>

<!--
Ex 4 : construire deux jeux de tables, puis lut[i] = a[i] + (b[i] - a[i]) * t
avec t qui monte de 0 à 1 à la vitesse dt ; reconstruire à chaque frame
tant que t bouge.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11d YCbCr
---

# Cours 11d — YCbCr et compression

La luminance du cours 11, `0.299 r + 0.587 g + 0.114 b`,
est la formule de la télévision. Ce cours sépare l'image en
**une luminance Y** et **deux canaux de couleur** Cb, Cr.

<div class="mt-4 text-sm">

<v-clicks>

- Y contient **tous les détails** ; Cb et Cr sont flous, presque sans contours
- Ce n'est pas un hasard : l'œil voit la luminance finement, la couleur grossièrement
- Et c'est pour ça que JPEG et toute vidéo réduisent la résolution des seconds

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11d-ycbcr.png" alt="Les canaux Y, Cb, Cr" class="w-full object-contain" />
</div>

<!--
Avant : cours 11 (luminance) et cours 17 (indice y * w + x). Un téléviseur
noir et blanc affichait Y.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11d YCbCr
---

# Étapes 1-2 — `decomposer()` : trois listes

```cpp
// ofApp.h :  int w = 0, h = 0;
//            std::vector<float> Y, Cb, Cr;        // trois "images" de w * h valeurs

void ofApp::decomposer() {                        // appelée une fois, dans setup()
    Y  = std::vector<float>(w * h, 0);
    Cb = std::vector<float>(w * h, 0);
    Cr = std::vector<float>(w * h, 0);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            ofColor c = source.getColor(x, y);
            int i = y * w + x;                    // deux coordonnées → un indice (cours 17)
            Y[i]  =       0.299f    * c.r + 0.587f    * c.g + 0.114f    * c.b;
            Cb[i] = 128 - 0.168736f * c.r - 0.331264f * c.g + 0.5f      * c.b;
            Cr[i] = 128 + 0.5f      * c.r - 0.418688f * c.g - 0.081312f * c.b;
        }
    }
}
```

<div class="mt-2 text-sm">

<v-clicks>

- **Y** la luminance, le gris de l'image ; **Cb** vers le bleu plutôt que le jaune ; **Cr** vers le rouge plutôt que le vert — centrés sur 128, « ni l'un ni l'autre »
- Pas des `ofImage` mais trois listes de `float` : des nombres à virgule, jamais affichés directement — l'indice `y * w + x` range les lignes bout à bout

</v-clicks>

</div>

<!--
setup() : fenêtre, image, w et h, allocate, puis decomposer(). Une image
grise a Cb = Cr = 128 partout. Formules de la norme JPEG.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11d YCbCr
---

# Étape 3 — `recomposer()` : l'inverse exact

```cpp
ofColor ofApp::recomposer(float y, float cb, float cr) {
    float r = y + 1.402f    * (cr - 128);
    float g = y - 0.344136f * (cb - 128) - 0.714136f * (cr - 128);
    float b = y + 1.772f    * (cb - 128);
    return ofColor(ofClamp(r, 0, 255), ofClamp(g, 0, 255), ofClamp(b, 0, 255));
}
```

<div class="mt-4 text-sm">

<v-clicks>

- Un changement d'espace, comme HSB au cours 09, mais **linéaire** : chaque nouveau nombre est un mélange pondéré des trois anciens
- `recomposer(Y[i], Cb[i], Cr[i])` refait exactement le chemin inverse : **aller-retour sans perte** — c'est la vue 0
- Les vues ne font que relire les trois listes et recomposer ; la décomposition n'a lieu qu'une fois

</v-clicks>

</div>

<!--
Les vues 1 à 3 affichent un canal seul en gris : ofColor(Y[i]),
ofColor(Cb[i]), ofColor(Cr[i]).
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11d YCbCr
---

# Étape 4 — `moyenneBloc()` : réduire un canal

```cpp
// la valeur moyenne d'un canal sur le bloc n × n qui contient (x, y)
float ofApp::moyenneBloc(std::vector<float>& canal, int x, int y, int n) {
    int x0 = x / n * n;                          // coin du bloc : division entière (cours 14)
    int y0 = y / n * n;
    float somme = 0;
    int compte = 0;
    for (int yy = y0; yy < y0 + n && yy < h; yy++) {
        for (int xx = x0; xx < x0 + n && xx < w; xx++) {
            somme += canal[yy * w + xx];
            compte++;
        }
    }
    return somme / compte;
}
```

<div class="mt-3 text-sm">

<v-clicks>

- Tous les pixels d'un même bloc reçoivent la même valeur : la résolution du canal est **divisée par `n`** — la pixelisation du cours 14, canal par canal
- `&& yy < h` : le bloc ne sort pas de l'image (les bords, cours 17)
- Le `&` devant `canal` : la fonction reçoit la **liste elle-même**, pas une copie de 400 000 valeurs

</v-clicks>

</div>

<!--
Le & est nouveau : passage par référence. Sans lui, chaque appel copierait
toute la liste — 400 000 fois par image. On ne creuse pas plus ici.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11d YCbCr
---

# Étape 5 — `calculerVue()` : l'expérience décisive

```cpp
int i = y * w + x;
ofColor c;
switch (vue) {
case 1: c = ofColor(Y[i]);  break;     // la luminance seule
case 2: c = ofColor(Cb[i]); break;     // Cb seul, en gris
case 3: c = ofColor(Cr[i]); break;
case 4: // la COULEUR en blocs, la luminance intacte
    c = recomposer(Y[i], moyenneBloc(Cb, x, y, tailleBloc),
                         moyenneBloc(Cr, x, y, tailleBloc));
    break;
case 5: // la LUMINANCE en blocs, la couleur intacte
    c = recomposer(moyenneBloc(Y, x, y, tailleBloc), Cb[i], Cr[i]);
    break;
default: c = recomposer(Y[i], Cb[i], Cr[i]);   // aller-retour
}
resultat.setColor(x, y, c);
```

<div class="mt-2 text-sm">

<v-clicks>

- Vue 4 : l'image est **presque inchangée** — il faut chercher les blocs sur les frontières orange / vert
- Vue 5 : l'image est **détruite**
- Même quantité d'information jetée : l'œil reconstruit les formes **à partir de la luminance seule** ; la couleur n'est qu'un vernis

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11d-blocs.png" alt="Couleur en blocs et luminance intacte, contre luminance en blocs" class="w-full object-contain" />
</div>

<!--
update() : tailleBloc = 2 à 32 à la souris, drapeau sur la vue ou la taille.
keyPressed : touches 0 à 5. Dans la double boucle habituelle.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11d YCbCr
---

# Ce que fait la compression

<div class="mt-4 text-base">

<v-clicks>

- JPEG, MPEG, H.264 : tout commence par convertir en YCbCr, puis **réduire la résolution de Cb et Cr**, en général de moitié dans chaque direction
- Un seul échantillon de couleur pour quatre pixels : le **4:2:0** des fiches techniques. Le 4:4:4 garde toute la couleur et coûte deux fois plus ; le 4:2:2 est le compromis du montage
- La vue 4 avec des blocs de 2 montre ce que fait le 4:2:0 : **rien de visible**
- Sauf une frontière nette entre deux couleurs de **même luminance** — texte rouge sur fond bleu : la couleur porte le contour, et la couleur est floue. Le texte bave

</v-clicks>

</div>

<div v-click class="mt-5 text-lg">
<b>Un texte d'interface ne doit jamais compter sur la couleur seule pour rester net dans une capture vidéo.</b>
</div>

<!--
C'est pour ça que les sous-titres sont blancs sur noir. Montrer la vue 4 à
2 px puis à 32 px.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11d YCbCr
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Cb et Cr en couleur** — affiche-les en couleur plutôt qu'en gris : `recomposer(128, Cb[i], 128)` et `recomposer(128, 128, Cr[i])`. On voit vers quoi tire chaque zone.

</div>

<div v-click class="mt-5 text-base">

**2 · Le texte qui bave** — dessine du texte rouge `(255, 0, 0)` sur fond bleu `(0, 0, 255)` dans une image, enregistre-la en JPEG qualité 30, ouvre-la et zoome. Puis refais-le en blanc sur noir. Explique la différence avec la vue 4.

</div>

<!--
Ex 2 : rouge et bleu ont presque la même luminance, le contour n'est porté
que par la chroma sous-échantillonnée ; blanc sur noir, le contour est dans
Y, intact.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11d YCbCr
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · Le débruitage** — le flou boîte (cours 17) sur Cb et Cr seulement, puis sur Y seulement. Le premier est un vrai outil : il enlève le bruit coloré des photos prises de nuit sans les rendre floues.

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Le chromakey propre** — au lieu de sélectionner le vert par sa teinte HSB, sélectionne les pixels dont `(Cb, Cr)` est proche de celui d'un vert de référence, avec la distance du cours 12 en deux dimensions. La luminance n'entre pas dans la sélection : les ombres sur le fond vert ne posent plus problème.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11d-ycbcr.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11d-ycbcr.md" download>md</a> · <a href="/ressources/ofApp11d.h" download>ofApp11d.h</a> · <a href="/ressources/ofApp11d.cpp" download>ofApp11d.cpp</a> · <a href="/ressources/data/pandaroux.jpg" download>pandaroux.jpg</a></p>

<!--
Ex 3 : le flou sur Y abîme l'image, le flou sur Cb/Cr est invisible — la
même expérience que les blocs. Ex 4 : sqrt((cb - cb0)² + (cr - cr0)²) < seuil.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# Cours 11e — Espaces perceptuels : OKLab

La limite de HSB : un jaune et un bleu de même
« luminosité » n'ont pas du tout la même **clarté perçue**,
et un dégradé HSB passe par des couleurs qui n'ont rien à y faire.

<div class="mt-4 text-sm">

<v-clicks>

- **OKLab** est construit pour que les nombres suivent la perception — entré dans le CSS en 2023
- Pas d'image dans ce cours : uniquement du dessin. Touches 1 à 4 pour changer la paire de couleurs

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11e-degrades.png" alt="Dégradé bleu-jaune en RGB, HSB, OKLab" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">RGB grise au milieu, HSB traverse des verts, OKLab fait ce qu'un peintre ferait.</p>
</div>

<!--
Avant : cours 09 (HSB, dégradés), 11a (lumière linéaire), 16 (polaire).
RGB : ligne droite dans le cube, les deux couleurs sont presque opposées,
la moyenne tombe au centre. HSB : chemin le plus court sur la roue, la
clarté fait des bonds.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# Mise en place — une `struct` pour une couleur

```cpp
// ofApp.h — avant la classe : un type à nous (cours 07)
struct Lab {
    float L;   // clarté 0-1
    float a;   // vert (-) / rouge (+)
    float b;   // bleu (-) / jaune (+)
};

// dans la classe :
Lab     versLab(ofColor c);
ofColor versRGB(Lab lab);
ofColor depuisLCH(float L, float C, float h);   // h en radians
void    bande(float y, int mode);               // un dégradé de A vers B : 0 RGB, 1 HSB, 2 OKLab
ofColor A, B;
```

<div class="mt-3 text-sm">

<v-clicks>

- **L** est la clarté perçue, de 0 (noir) à 1 (blanc) ; **a** et **b** sont deux axes de couleur — comme Cb et Cr du 11d, mais gradués selon la perception. Le gris est à `a = 0, b = 0`
- La propriété qui compte : **la distance entre deux couleurs dans OKLab correspond à la différence perçue**. Ni RGB ni HSB ne l'ont — c'est ce qui rend leurs dégradés irréguliers
- Une fonction peut **renvoyer une `struct`** : `versLab` fabrique un `Lab` complet, trois nombres d'un coup

</v-clicks>

</div>

<!--
versLineaire et versSRGB du 11a sont reprises telles quelles. setup() :
fenêtre 800 × 620 et keyPressed('1') pour charger la première paire.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# Étape 3 — `versLab()` : simuler l'œil en trois étapes

```cpp {2|3-5|6-11}
Lab ofApp::versLab(ofColor c) {
    float r = versLineaire(c.r), g = versLineaire(c.g), bl = versLineaire(c.b);
    float l = 0.4122214708f * r + 0.5363325363f * g + 0.0514459929f * bl;
    float m = 0.2119034982f * r + 0.6806995451f * g + 0.1073969566f * bl;
    float s = 0.0883024619f * r + 0.2817188376f * g + 0.6299787005f * bl;
    l = cbrt(l); m = cbrt(m); s = cbrt(s);
    Lab out;
    out.L = 0.2104542553f * l + 0.7936177850f * m - 0.0040720468f * s;
    out.a = 1.9779984951f * l - 2.4285922050f * m + 0.4505937099f * s;
    out.b = 0.0259040371f * l + 0.7827717662f * m - 0.8086757660f * s;
    return out;
}
```

<div class="mt-2 text-sm">

- **1.** sRGB → lumière linéaire (11a) : toute la suite parle de lumière
- **2.** Un mélange vers `l, m, s` : à peu près les réponses des trois types de **cônes** de la rétine — on simule l'œil
- **3.** Racine cubique `cbrt` : l'œil répond de façon **compressée** (dix fois plus de lumière ne paraît pas dix fois plus clair), puis un dernier mélange vers L, a, b
- Les nombres à dix décimales sont ceux publiés par Björn Ottosson en 2020 : **personne ne les retient, on les copie**

</div>

<!--
Trois clics = trois étapes. Le dégradé OKLab devient trivial : convertir A
et B, interpoler L, a, b séparément, reconvertir — la ligne droite est dans
le bon espace.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# Étape 4 — `versRGB()` : les mêmes étapes à l'envers

```cpp
ofColor ofApp::versRGB(Lab lab) {
    float l = lab.L + 0.3963377774f * lab.a + 0.2158037573f * lab.b;   // mélange inverse
    float m = lab.L - 0.1055613458f * lab.a - 0.0638541728f * lab.b;
    float s = lab.L - 0.0894841775f * lab.a - 1.2914855480f * lab.b;
    l = l * l * l; m = m * m * m; s = s * s * s;                       // le cube défait la racine
    float r  =  4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s;
    float g  = -1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s;
    float bl = -0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s;
    return ofColor(versSRGB(r), versSRGB(g), versSRGB(bl));            // réencodage sRGB
}
```

<div class="mt-4 text-sm">

<v-clicks>

- Mélange inverse, cube, mélange inverse, réencodage : chaque étape de `versLab` **défaite dans l'ordre inverse**
- Le `ofClamp` dans `versSRGB` attrape ce que l'écran ne sait pas afficher : toutes les couleurs OKLab n'existent pas en sRGB

</v-clicks>

</div>

<!--
On n'explique pas d'où viennent les coefficients inverses : ce sont ceux
d'Ottosson aussi.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# Étape 5 — `depuisLCH()` : la version polaire

```cpp
// L clarté, C chroma (distance au gris : 0 gris, 0.3 très saturé), h teinte en radians
ofColor ofApp::depuisLCH(float L, float C, float h) {
    Lab lab;
    lab.L = L;
    lab.a = C * cos(h);        // polaire → cartésien (cours 16)
    lab.b = C * sin(h);
    return versRGB(lab);
}
```

<div class="mt-4 text-sm">

<v-clicks>

- Comme HSB est la lecture polaire de RGB, **OKLCH** est la lecture polaire d'OKLab : le point `(a, b)` décrit par sa distance au gris `C` et son angle `h`
- La conversion est celle du cours 16, polaire vers cartésien — rien de nouveau
- Le chroma est **borné** : à `L` donné, toutes les teintes n'acceptent pas le même `C` avant de sortir de l'écran

</v-clicks>

</div>

<!--
C'est l'outil des palettes à clarté constante, montrées dans draw().
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# Étape 7 — `bande()` : trois dégradés entre A et B

```cpp {3-4|5-10|11-16}
for (int x = 0; x < w; x++) {
    float p = x / w;
    if (mode == 0) {                          // RGB : une ligne droite dans le cube (cours 09)
        c = A.getLerped(B, p);
    } else if (mode == 1) {                   // HSB : la teinte par le chemin le plus court
        float h1 = A.getHue(), h2 = B.getHue();
        float d = h2 - h1;
        if (d > 127.5f) d -= 255;  if (d < -127.5f) d += 255;
        float h = fmod(h1 + d * p + 255, 255);
        c = ofColor::fromHsb(h, /* S et B interpolés */);
    } else {                                  // OKLab : ligne droite dans l'espace perceptuel
        Lab la = versLab(A), lb = versLab(B), m;
        m.L = la.L + (lb.L - la.L) * p;
        m.a = la.a + (lb.a - la.a) * p;
        m.b = la.b + (lb.b - la.b) * p;
        c = versRGB(m);
    }
    ofSetColor(c);  ofDrawLine(20 + x, y, 20 + x, y + 50);
}
```

<div class="mt-2 text-sm">

- **RGB** passe souvent par un gris terne ; **HSB** fait des détours et sa clarté saute ; **OKLab** : convertir, interpoler L, a, b séparément (trois `getLerped` sur des `float`), reconvertir
- La ligne droite est dans le **bon espace** : la clarté évolue régulièrement

</div>

<!--
Le chemin le plus court sur la roue (teinte 0-255 chez openFrameworks) : si
l'écart dépasse un demi-tour, on tourne dans l'autre sens. fmod ramène
dans 0-255.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# Étape 8 — `draw()` : luminosité ≠ clarté

```cpp
// 8 teintes HSB à S = 255, B = 255 — et leur clarté OKLab dessous
for (int i = 0; i < 8; i++) {
    ofColor c = ofColor::fromHsb(i * 255 / 8.0f, 255, 255);
    ofSetColor(c);
    ofDrawRectangle(20 + i * 95, 300, 90, 60);
    float L = versLab(c).L;
    ofSetColor(versSRGB(L * L * L));      // L³ ~ lumière, affichée en gris
    ofDrawRectangle(20 + i * 95, 362, 90, 25);
}

// 8 teintes OKLCH à L = 0.75, C = 0.12 : même clarté perçue
for (int i = 0; i < 8; i++) {
    ofSetColor(depuisLCH(0.75f, 0.12f, i * TWO_PI / 8));
    ofDrawRectangle(20 + i * 95, 460, 90, 60);
}
```

<div class="mt-2 text-sm">

<v-clicks>

- Jaune `L = 0.97`, presque blanc ; bleu `L = 0.45`, un ton moyen — HSB appelle ça la **même « luminosité »**. D'où le texte jaune sur blanc illisible
- La rangée OKLCH : huit teintes espacées, **toutes de la même clarté** — une palette d'interface où rien ne crie, impossible en HSB

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11e-clarte.png" alt="Huit teintes HSB et leur clarté ; huit teintes OKLCH à L constant" class="w-full object-contain" />
</div>

<!--
keyPressed : touches 1 à 4, chacune charge une paire A / B (bleu → jaune,
rouge → vert, bleu nuit → blanc, magenta → cyan). Un graphique dont les
séries sont des teintes HSB « équilibrées » a toujours une série qui crie.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · La rotation de teinte en OKLCH** — la rotation de teinte du cours 11, refaite en OKLCH : convertir chaque pixel, ajouter à `h`, revenir. Compare avec la version HSB : les clartés ne bougent plus.

</div>

<div v-click class="mt-5 text-base">

**2 · Le tri** — trie une liste de couleurs par clarté `L`, puis par teinte `h`. Affiche les deux rangées.

</div>

<!--
Ex 1 : h = atan2(b, a), C = sqrt(a² + b²) pour aller dans l'autre sens
(cours 16). Ex 2 : un tri à la main par échanges (cours 06 ter), ou
std::sort pour les curieux.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · Noir ou blanc ?** — « Texte noir ou blanc sur ce fond ? » : si `L > 0.6`, noir, sinon blanc. Teste sur les huit couleurs HSB de la première rangée.

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Les cinq couleurs du 12, en OKLab** — reprends la réduction à cinq couleurs du cours 12 avec la distance dans OKLab au lieu de RGB. Les verts du feuillage et l'orange du pelage sont mieux répartis.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11e-oklab.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11e-oklab.md" download>md</a> · <a href="/ressources/ofApp11e.h" download>ofApp11e.h</a> · <a href="/ressources/ofApp11e.cpp" download>ofApp11e.cpp</a></p>

<!--
Ex 3 est la recette utilisée par les vrais design systems. Ex 4 boucle avec
le 11g (distance OKLab dans plusProche).
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11f Daltonisme
---

# Cours 11f — Daltonisme et accessibilité

Environ un homme sur douze et une femme sur deux cents
ne voient pas les couleurs comme la majorité. Un jeu où
« vert = allié, rouge = ennemi » est **injouable** pour eux
si rien d'autre ne les distingue.

<div class="mt-4 text-sm">

| Déficience | Cône | Fréquence |
|---|---|---|
| protanopie | rouge | environ 1 % des hommes |
| deutéranopie | vert | environ 6 % — la plus courante |
| tritanopie | bleu | très rare |

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11f-daltonisme.png" alt="Vision normale, protanopie, deutéranopie, tritanopie" class="w-full object-contain" />
</div>

<!--
Avant : cours 11 (sépia, mélange des canaux) et 11a. Chiffres du document.
Les formes complètes (cône absent) sont rares ; les partielles fréquentes —
d'où la sévérité réglée à la souris. On simule leur vision avec neuf nombres.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11f Daltonisme
---

# Étape 4 — `simuler()` : une matrice 3 × 3

```cpp
// ofApp.h :  std::vector<float> matrice;    // 9 valeurs, ligne par ligne
// setup() :  matrice = std::vector<float>(9, 0);  + la table du 11a

ofColor ofApp::simuler(ofColor c) {
    float r = tableLineaire[c.r], g = tableLineaire[c.g], b = tableLineaire[c.b];
    float r2 = matrice[0] * r + matrice[1] * g + matrice[2] * b;
    float g2 = matrice[3] * r + matrice[4] * g + matrice[5] * b;
    float b2 = matrice[6] * r + matrice[7] * g + matrice[8] * b;
    return ofColor(versSRGB(r2), versSRGB(g2), versSRGB(b2));
}
```

<div class="mt-3 text-sm">

<v-clicks>

- Chaque canal de sortie est un **mélange pondéré des trois canaux d'entrée** : neuf poids dans une liste, indice `ligne * 3 + colonne` (cours 17)
- Le sépia du cours 11 avait exactement cette forme ; la vision normale est l'**identité** `1 0 0 / 0 1 0 / 0 0 1` — chaque canal ne dépend que de lui-même
- Appliquée à la **lumière linéaire** (11a), pas aux valeurs sRGB : elle décrit une réponse physique de l'œil

</v-clicks>

</div>

<!--
Deux couleurs que l'œil simulé confond donnent la même sortie : la matrice
projette sur ce qu'un œil sans le cône peut encore distinguer.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11f Daltonisme
---

# Étape 5 — `calculerImage()` : cible et sévérité

```cpp {1-9|10-13|14-19}
void ofApp::calculerImage() {
    std::vector<float> cible;
    switch (type) {            // les neuf nombres de chaque type : Machado, Oliveira et Fernandes, 2009
    case 2: cible = { 0.367322f, 0.860646f, -0.227968f,    // deutéranopie
                      0.280085f, 0.672501f,  0.047413f,
                     -0.011820f, 0.042940f,  0.968881f }; break;
    // case 1 protanopie, case 3 tritanopie : neuf autres nombres
    default: cible = { 1, 0, 0,  0, 1, 0,  0, 0, 1 };   // vision normale : l'identité
    }
    std::vector<float> identite = { 1, 0, 0,  0, 1, 0,  0, 0, 1 };
    for (int i = 0; i < 9; i++) {
        matrice[i] = identite[i] + (cible[i] - identite[i]) * severite;
    }
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            resultat.setColor(x, y, simuler(source.getColor(x, y)));
        }
    }
    resultat.update();
}
```

<div class="mt-2 text-sm">

- Les neuf coefficients de chaque type viennent d'une étude de 2009 : **on les copie**, comme ceux d'OKLab
- La **sévérité** interpole case par case entre l'identité et la matrice complète — l'interpolation du cours 09 sur neuf nombres. À mi-course, à peu près ce que voit un daltonien partiel
- Puis la double boucle du 11 : un `simuler` par pixel

</div>

<!--
update() : severite = souris, drapeau sur le type ou la sévérité.
keyPressed : touches 0 à 3.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11f Daltonisme
---

# Étape 7 — `dessinerTest()` : l'interface

```cpp
ofColor vie(40, 190, 60), danger(220, 40, 40);
// à gauche : l'information n'est portée QUE par la couleur
ofSetColor(simuler(vie));    ofDrawRectangle(x, y, 120, 30);
ofSetColor(simuler(danger)); ofDrawRectangle(x + 130, y, 120, 30);

// à droite : couleur + hachures + symbole
ofSetColor(simuler(vie));    ofDrawRectangle(x + 300, y, 120, 30);
ofSetColor(simuler(danger)); ofDrawRectangle(x + 430, y, 120, 30);
ofSetColor(simuler(ofColor(255)));
for (int i = 0; i < 120; i += 10) ofDrawLine(x + 430 + i, y, x + 430 + i + 10, y + 30);
ofDrawBitmapString("+", x + 355, y + 20);
ofDrawBitmapString("!", x + 485, y + 20);
```

<div class="mt-2 text-sm">

<v-clicks>

- En deutéranopie, les deux jauges de gauche sont **du même brun** — le joueur ne sait plus. À droite, la couleur a disparu mais **l'information est intacte**
- Un daltonien voit très bien les différences de **clarté** (11e) : deux couleurs qui diffèrent aussi en L restent distinguables
- Un concepteur qui voit normalement ne peut pas deviner ce qui se confond : **tester tôt, avec un simulateur**, tant que la palette peut changer

</v-clicks>

</div>

<div v-click class="mt-3 text-xl">
<b>Ne jamais coder une information par la couleur seule.</b>
</div>

<!--
Toujours doubler d'une forme, d'un motif, d'un texte, d'une position ou
d'une différence de clarté. Les « modes daltoniens » des jeux remplacent les
palettes qui posent problème, et parfois daltonisent l'image (exercice 1).
Photoshop, Unity, Unreal et les navigateurs ont un simulateur ; celui-ci
tient en trente lignes et s'applique à toute capture d'écran de leur jeu.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11f Daltonisme
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 ·** 🔥 **Daltoniser** pour la deutéranopie — calcule la simulation, mesure l'erreur `r - r2` que le daltonien ne voit pas, et ajoute une partie de cette erreur au canal bleu, qu'il voit. Compare l'image daltonisée passée dans le simulateur avec l'image d'origine passée dans le simulateur : les rouges et les verts sont-ils redevenus distinguables ?

</div>

<div v-click class="mt-5 text-base">

**2 · Le sépia est une matrice** — le sépia du cours 11 a la forme d'une matrice 3 × 3 : ajoute-le comme type 4.

</div>

<!--
Ex 1 : c'est ce que font les modes daltoniens des jeux. Ex 2 : les neuf
coefficients du sépia du cours 11, dans un case 4 ; attention, le sépia du
11 s'appliquait aux valeurs sRGB.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11f Daltonisme
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · Ta palette** — prends la palette d'un jeu que tu aimes, ou la tienne. Affiche ses couleurs en pavés et passe-les dans les trois simulations. Marque les paires qui se confondent, et corrige-les avec une différence de clarté `L` (11e).

</div>

<div v-click class="mt-5 text-base">

**4 · Sans le linéaire** — applique la matrice directement aux valeurs sRGB, sans passer par le linéaire. La différence est petite ; trouve une zone de l'image où elle se voit.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11f-daltonisme.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11f-daltonisme.md" download>md</a> · <a href="/ressources/ofApp11f.h" download>ofApp11f.h</a> · <a href="/ressources/ofApp11f.cpp" download>ofApp11f.cpp</a> · <a href="/ressources/data/pandaroux.jpg" download>pandaroux.jpg</a></p>

<!--
Ex 3 est l'exercice le plus « métier » du bloc : un vrai contrôle qualité
de direction artistique. Ex 4 : chercher dans les tons moyens saturés.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11g Dithering
---

# Cours 11g — Palette indexée et dithering

Quatre couleurs sur Game Boy, seize sur les consoles 8 bits,
256 sur les PC : pour chaque pixel, choisir la couleur
**la plus proche** de la palette — et tromper l'œil
pour les nuances manquantes.

<div class="mt-4 text-sm">

<v-clicks>

- Revenu à la mode avec le pixel art — et c'est le dithering annoncé au cours 09a contre le banding
- Touches 1 à 3 : la méthode. `p` : la palette suivante. Souris : la taille des gros pixels

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11g-dithering.png" alt="Palettes Game Boy et PICO-8, Bayer, Floyd-Steinberg" class="w-full object-contain" />
</div>

<!--
Avant : cours 12 (distance entre couleurs), 14 (gros pixels), 11
(postérisation). La postérisation du cours 11, mais vers des couleurs
choisies.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11g Dithering
---

# Étape 2 — `choisirPalette()` : une liste d'`ofColor`

```cpp
// ofApp.h :  std::vector<ofColor> palette;   int numPalette = 0;

void ofApp::choisirPalette() {
    palette.clear();
    switch (numPalette) {
    case 1:
        palette = { ofColor(0), ofColor(255) };                                   // noir et blanc
        break;
    case 2: // CGA, palette 1 : noir, cyan, magenta, blanc
        palette = { ofColor(0, 0, 0), ofColor(85, 255, 255), ofColor(255, 85, 255), ofColor(255, 255, 255) };
        break;
    case 3: // PICO-8, la console imaginaire : 16 couleurs
        palette = { ofColor(0, 0, 0), ofColor(29, 43, 83), ofColor(126, 37, 83), /* ... */ ofColor(255, 204, 170) };
        break;
    default: // Game Boy : quatre nuances de vert
        palette = { ofColor(15, 56, 15), ofColor(48, 98, 48), ofColor(139, 172, 15), ofColor(155, 188, 15) };
    }
}
```

<div class="mt-2 text-sm">

<v-clicks>

- La palette est une liste d'`ofColor`, remplie par une **liste d'initialisation** (cours 06 ter) ; `clear()` la vide avant de la remplir
- **La palette compte autant que l'algorithme** : seize couleurs réparties en clarté du noir au blanc (11e) rendent une photo reconnaissable — quatre verts, non
- Les palettes des consoles historiques sont étudiées pour ça ; le pixel art moderne en réutilise beaucoup

</v-clicks>

</div>

<!--
setup() : fenêtre, image, allocate, puis choisirPalette(). Passer de Game Boy
à PICO-8 avec p pendant la démo. Choisir une palette est un métier :
réparties en clarté d'abord, en teinte ensuite.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11g Dithering
---

# Étape 3 — `plusProche()` : la distance entre couleurs

```cpp
ofColor ofApp::plusProche(float r, float g, float b) {
    float meilleure = 1e9;                    // un milliard : battu d'office
    ofColor gagnante = palette[0];
    for (int i = 0; i < palette.size(); i++) {
        float dr = r - palette[i].r, dg = g - palette[i].g, db = b - palette[i].b;
        float d = dr * dr + dg * dg + db * db;    // distance AU CARRÉ
        if (d < meilleure) {
            meilleure = d;
            gagnante = palette[i];
        }
    }
    return gagnante;
}
```

<div class="mt-3 text-sm">

<v-clicks>

- La distance dans le **cube RGB** (Pythagore en 3D, cours 09 et 12), et on garde la plus petite — le motif « meilleur score » du cours 06 ter
- Comparée **au carré** : si `d1² < d2²` alors `d1 < d2` — la racine coûte cher pour rien
- Résultat : des aplats. Le dégradé du pelage devient trois zones nettes — la postérisation du 11, vers des couleurs choisies

</v-clicks>

</div>

<!--
1e9 est la notation de un milliard : une valeur de départ que n'importe
quelle vraie distance battra.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11g Dithering
---

# Étape 4 (1/3) — la grille de gros pixels

```cpp
int n = taillePixel;
int gw = w / n, gh = h / n;                 // la grille de gros pixels

// copie flottante de l'image réduite : la méthode 3 va MODIFIER ces valeurs
std::vector<float> R(gw * gh), G(gw * gh), B(gw * gh);
for (int j = 0; j < gh; j++) {
    for (int i = 0; i < gw; i++) {
        ofColor c = source.getColor(i * n + n / 2, j * n + n / 2);    // le pixel au centre de la case
        R[j * gw + i] = c.r;  G[j * gw + i] = c.g;  B[j * gw + i] = c.b;
    }
}

int bayer[16] = { 0, 8, 2, 10,  12, 4, 14, 6,  3, 11, 1, 9,  15, 7, 13, 5 };
float ecart = 255.0f / palette.size();     // l'écart entre deux couleurs de la palette
```

<div class="mt-3 text-sm">

<v-clicks>

- Pour le rendu rétro et pour aller vite : lire le pixel au **centre** de chaque case `n × n`, décider sa couleur, remplir la case — la pixelisation du cours 14
- Trois listes de `float`, indice `j * gw + i` (cours 17) : une copie **modifiable** de l'image réduite, parce que la diffusion d'erreur va corriger les voisins en cours de route

</v-clicks>

</div>

<!--
update() : taillePixel = 1 à 8 à la souris ; drapeau sur la méthode, la
taille ou la palette. Le reste de l'étape suit.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11g Dithering
---

# Étape 4 (2/3) — la matrice de Bayer

```cpp
for (int j = 0; j < gh; j++) {
    for (int i = 0; i < gw; i++) {
        int k = j * gw + i;
        float r = ofClamp(R[k], 0, 255);      // idem g, b
        // ...

        if (methode == 2) {
            // un décalage selon la position dans la grille 4 × 4
            float d = (bayer[(j % 4) * 4 + (i % 4)] / 16.0f - 0.5f) * ecart;
            r += d;  g += d;  b += d;
        }

        ofColor q = plusProche(r, g, b);
```

<div class="mt-3 text-sm">

<v-clicks>

- Avant de chercher la plus proche, on **décale** la couleur entre `-ecart/2` et `+ecart/2` : deux pixels voisins de même couleur reçoivent des décalages différents et peuvent tomber sur deux couleurs de la palette
- Vu de loin, l'œil mélange les deux : une nuance intermédiaire apparaît, faite d'une **trame régulière**
- Rapide et **stable dans le temps** : si l'image bouge, la trame ne grouille pas — Game Boy, impressions de journaux

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11g-bayer.png" alt="La matrice de Bayer et son effet sur un dégradé seuillé" class="w-full object-contain" />
</div>

<!--
Les seize valeurs sont réparties « en désordre ordonné » pour que les
voisines soient toujours très différentes. ecart = 255 / palette.size() :
juste assez grand pour basculer vers la couleur voisine. Le % du cours 13
fait boucler la grille. Le ofClamp borne les valeurs que la diffusion a pu
pousser hors de 0-255.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11g Dithering
---

# Étape 4 (3/3) — Floyd-Steinberg

```cpp
        if (methode == 3) {
            // ce que la palette n'a pas su représenter : l'erreur commise sur ce pixel
            float er = r - q.r, eg = g - q.g, eb = b - q.b;
            if (i + 1 < gw)               { R[k + 1]      += er * 7 / 16;  /* G, B idem */ }   // à droite
            if (j + 1 < gh && i > 0)      { R[k + gw - 1] += er * 3 / 16;  /* ...     */ }   // en bas à gauche
            if (j + 1 < gh)               { R[k + gw]     += er * 5 / 16;  /* ...     */ }   // en bas
            if (j + 1 < gh && i + 1 < gw) { R[k + gw + 1] += er * 1 / 16;  /* ...     */ }   // en bas à droite
        }

        for (int y = j * n; y < j * n + n; y++) {        // remplir la case n × n du résultat
            for (int x = i * n; x < i * n + n; x++) {
                resultat.setColor(x, y, q);
            }
        }
    }
}
```

<div class="mt-2 text-sm">

<v-clicks>

- L'erreur n'est pas perdue : elle est **répartie sur les voisins pas encore traités**, à droite et sur la ligne du dessous, poids 7 + 3 + 5 + 1 = 16/16. Un pixel trop sombre pousse ses voisins vers le clair, l'un d'eux bascule : le ton moyen est respecté
- L'**ordre de parcours** fait partie de l'algorithme : la boucle lit une valeur déjà corrigée par ses voisins de gauche et du dessus. Les `if` évitent d'écrire hors de la grille (cours 04)
- Plus fin que Bayer, sans trame — mais **grouille** sur une image animée : le dithering des GIF

</v-clicks>

</div>

<!--
keyPressed : touches 1 à 3 pour la méthode, p fait tourner numPalette avec
% nomsPalette.size() puis choisirPalette(). draw() affiche l'image et la
palette en pavés en bas à droite.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11g Dithering
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Ta propre palette** — huit couleurs, choisies avec OKLCH (11e) pour couvrir les clartés de 0.2 à 0.9.

</div>

<div v-click class="mt-5 text-base">

**2 ·** 🔥 **La distance OKLab** — remplace la distance RGB dans `plusProche` par la distance dans OKLab (11e). Les verts du feuillage et les tons du pelage sont mieux rendus, surtout en Game Boy.

</div>

<div v-click class="mt-5 text-base">

**3 · Bayer 8 × 8** — 64 seuils, trame plus fine. La matrice se construit en récursif à partir de la 4 × 4 ; cherche « Bayer matrix » et copie-la.

</div>

<!--
Ex 1 : depuisLCH du 11e avec L de 0.2 à 0.9 par pas égaux, C fixe, teintes
espacées. Ex 2 : convertir la palette une fois dans choisirPalette, puis
chaque pixel ; la distance L, a, b au carré. Ex 3 : bayer[64], (j % 8) * 8
+ (i % 8), diviser par 64.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11g Dithering
---

# À vous (2/2)

<div class="mt-4 text-base">

**4 · La moyenne de la case** — la moyenne de la case `n × n` au lieu du pixel central, avec `moyenneBloc` du cours 11d. Moins de scintillement en changeant `n`.

</div>

<div v-click class="mt-5 text-base">

**5 · Le dégradé trahi** — le dithering en noir et blanc d'un dégradé noir vers blanc, avec les trois méthodes côte à côte : on voit exactement ce que fait chacune.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11g-palette-dithering.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11g-palette-dithering.md" download>md</a> · <a href="/ressources/ofApp11g.h" download>ofApp11g.h</a> · <a href="/ressources/ofApp11g.cpp" download>ofApp11g.cpp</a> · <a href="/ressources/data/pandaroux.jpg" download>pandaroux.jpg</a></p>

<!--
Ex 5 : palette noir et blanc, une bande par méthode. Clôture du bloc : la
palette personnelle peut resservir au projet 18.
-->

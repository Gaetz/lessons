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

# 11a — Gamma et espace linéaire

Le sujet **le plus important** de la série, et le plus
souvent ignoré : les nombres de 0 à 255 ne mesurent
pas la lumière.

<div class="mt-4 text-sm">

<v-clicks>

- La valeur 128 code **22 %** de la lumière du blanc — pas la moitié
- L'œil distingue finement les sombres : la courbe sRGB leur donne plus de niveaux
- Tant qu'on affiche, aucune importance. **Dès qu'on calcule, tout devient faux**

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11a-image.png" alt="Assombrir de moitié : naïf vs linéaire" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">Diviser la lumière par deux : à gauche le calcul naïf, beaucoup trop sombre.</p>
</div>

<!--
Démo damier (vue 2) : cases rouge/vert de 2 px — l'œil moyenne les LUMIÈRES
et voit un jaune vif (186,186,0) ; la moyenne des valeurs donne un olive
sombre (128,128,0). Flou, dégradé, transparence : tout mélange a ce problème.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11a Gamma
---

# Étapes `versLineaire()` / `versSRGB()` — les deux convertisseurs

```cpp
float ofApp::versLineaire(float c) {        // valeur 0-255 → lumière 0-1
    return pow(c / 255.0f, 2.2f);
}
float ofApp::versSRGB(float l) {            // lumière 0-1 → valeur 0-255
    return 255.0f * pow(ofClamp(l, 0, 1), 1.0f / 2.2f);
}

// dans setup() : pow est lent, mais il n'y a que 256 entrées possibles
for (int c = 0; c < 256; c++) {
    tableLineaire.push_back(versLineaire(c));   // tableLineaire[128] = 0.22
}
```

<div class="mt-3 text-sm">

<v-clicks>

- `pow(a, b)` : « a puissance b » — `pow(0.5, 2.2)` vaut 0,22 : la valeur 128 code 22 % de lumière ; 50 % de lumière se code 186
- La vraie courbe sRGB est en deux morceaux ; **l'approximation 2.2 suffit** pour comprendre et pour presque tous les effets
- La **table précalculée** : 256 résultats calculés une fois remplacent 400 000 `pow` par frame — l'idée que 11c généralise

</v-clicks>

</div>

<!--
Le retour vers sRGB part d'un float quelconque (pas d'une des 256 valeurs) :
lui garde pow. Ces deux fonctions et la table reviennent telles quelles en
11b, 11e et 11f — on ne les remontrera pas.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11a Gamma
---

# Étape `calculerImage()` — le bon ordre : décoder, calculer, réencoder

```cpp
for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
        ofColor c = source.getColor(x, y);
        ofColor sortie;
        if (x < w / 2) {
            // NAÏF : on multiplie directement les valeurs 0-255
            sortie = ofColor(ofClamp(c.r * facteur, 0, 255), /* g, b */);
        } else {
            // JUSTE : on multiplie la LUMIÈRE
            float r = tableLineaire[c.r] * facteur;     // 1. décoder  2. calculer
            float g = tableLineaire[c.g] * facteur;
            float b = tableLineaire[c.b] * facteur;
            sortie = ofColor(versSRGB(r), versSRGB(g), versSRGB(b));   // 3. réencoder
        }
        resultat.setColor(x, y, sortie);
    }
}
```

<div class="mt-2 text-sm">

- Diviser la lumière par deux = fermer l'objectif d'un cran ; le calcul naïf divise des valeurs **déjà compressées** — donc la lumière par plus de quatre
- C'est le réglage « **Linear** » des moteurs, et la case « sRGB » des textures — la cocher à tort rend un matériau délavé

</div>

<!--
L'image est coupée en deux verticalement : la comparaison se fait à l'écran,
souris = facteur ×0.25 à ×4 (la différence change de sens quand on éclaircit).
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11a Gamma
---

# Étape `update()` — ne recalculer que si nécessaire

```cpp
void ofApp::update() {
    facteur = pow(2.0f, (mouseX / (float)ofGetWidth()) * 4 - 2);  // ×0.25 à ×4
    if (vue == 3 && facteur != dernierFacteur) {
        calculerImage();
        dernierFacteur = facteur;      // on mémorise, on compare
    }
}
```

<div class="mt-4 text-sm">

<v-clicks>

- On mémorise le dernier facteur et on **compare** : l'image n'est recalculée que quand la souris a bougé
- Les vues 1 et 2 (touches) sont dessinées en direct dans `draw()` : les deux dégradés (valeur vs lumière) et le damier rouge-vert face à ses deux moyennes
- `keyPressed` : trois vues, touches 1 à 3

</v-clicks>

</div>


<!--
Exercices : la vraie courbe sRGB (deux morceaux), le flou de 17 en linéaire,
le dégradé getLerped en linéaire, gris 128 vs damier noir-blanc de loin.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11a Gamma
---

# À vous — voir le gamma

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Côte à côte : un gris `(128, 128, 128)` et un **damier noir-blanc de 1 pixel**. Sont-ils pareils de loin ? Quel gris uni ressemble au damier ?
- **2 ·** Le **dégradé** entre deux couleurs du cours 09, calculé en linéaire : décoder, interpoler, réencoder — lequel est le plus lumineux au milieu ?
- **3 ·** 🔥 Refais le **flou boîte du cours 17 en linéaire** — compare sur les moustaches blanches du panda : lequel les assombrit ?

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11a-gamma.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11a-gamma.md" download>md</a> · <a href="/ressources/ofApp11a.h" download>ofApp11a.h</a> · <a href="/ressources/ofApp11a.cpp" download>ofApp11a.cpp</a></p>

<!--
N°1 est LA démonstration du gamma en deux lignes de code. La vraie courbe
sRGB (ex 1 du document) pour les curieux.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11b Tone mapping
---

# 11b — HDR et tone mapping

Dans un moteur, la lumière d'une scène n'a **pas de
plafond** : ciel à 10, lampe à 100, soleil à des milliers.
L'écran, lui, s'arrête à 1.

<div class="mt-4 text-sm">

<v-clicks>

- L'**exposition** multiplie la lumière, en *stops* — chaque stop double
- Le **tone mapping** est la courbe qui ramène tout sous 1

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11b-tonemapping.png" alt="Clamp, Reinhard et ACES comparés" class="w-full object-contain" />
</div>

<!--
Pas de vraie image HDR ici : on triche en poussant l'exposition jusqu'à ce
que la moitié de l'image dépasse 1. Mise en place : mêmes convertisseurs et
table qu'en 11a.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11b Tone mapping
---

# Étape `toneMap()` — trois façons de ramener sous 1

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
- **Reinhard** : rien ne brûle, mais tout grise — les blancs ne sont jamais blancs (1 → 0,5 !)
- **ACES** : la courbe en S « pellicule » — ombres écrasées, tons moyens contrastés, hautes lumières compressées en douceur. **C'est le réglage d'Unreal et d'Unity**

</v-clicks>

</div>

<!--
« ACES » désigne en réalité tout un système de gestion de couleur du cinéma ;
les moteurs n'en prennent que la courbe finale, dans cette approximation à
cinq nombres que tout le monde copie.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11b Tone mapping
---

# Étapes `calculerImage()` et `update()` — le pipeline complet

```cpp
// pour chaque pixel — quatre étapes par canal :
float r = toneMap(tableLineaire[c.r] * exposition);
float g = toneMap(tableLineaire[c.g] * exposition);
float b = toneMap(tableLineaire[c.b] * exposition);
resultat.setColor(x, y, ofColor(versSRGB(r), versSRGB(g), versSRGB(b)));

// dans update() :
float stops = (mouseX / (float)ofGetWidth()) * 6 - 2;      // -2 à +4 stops
exposition = pow(2.0f, stops);                             // chaque stop double
if (exposition != derniereExposition || methode != derniereMethode) {
    calculerImage();   // le drapeau de 11a, avec deux conditions
}
```

<div class="mt-3 text-sm">

<v-clicks>

- **Décoder → exposer → tone mapper → réencoder** : c'est, à peu de choses près, la fin du pipeline de rendu d'un jeu moderne (le « post-process »)
- L'« exposition automatique » d'un jeu ne fait que choisir le facteur selon la luminosité moyenne de l'image

</v-clicks>

</div>

<!--
À +2 stops, la moitié de l'image dépasse déjà 1 : c'est là que les trois
méthodes divergent à l'écran.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11b Tone mapping
---

# Étape `draw()` — tracer une courbe

```cpp
// entrée 0..4 en x, sortie 0..1 en y — un petit segment par pixel
for (int i = 0; i < gw - 1; i++) {
    float x0 = i / (float)gw * 4, x1 = (i + 1) / (float)gw * 4;
    ofDrawLine(gx + i,     gy + gh - toneMap(x0) * gh,
               gx + i + 1, gy + gh - toneMap(x1) * gh);
}
```

<div class="mt-4 text-sm">

<v-clicks>

- La recette pour dessiner **n'importe quelle fonction** : pour chaque pixel horizontal, calculer l'entrée, appeler la fonction, convertir la sortie en hauteur
- Le `gy + gh - ...` retourne l'axe : `y` pointe vers le bas (cours 00)
- Sur la courbe, regarder à droite de « entrée = 1 » : couper est plat, Reinhard monte lentement, ACES s'aplatit près de 1

</v-clicks>

</div>


<!--
Exercices : Reinhard étendu (Lb), tone mapping sur la luminance seule (les
couleurs saturées ne virent plus au blanc), exposition automatique (gris
moyen 0.18), une vraie image HDR avec ofFloatImage.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11b Tone mapping
---

# À vous — dompter la lumière

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Reinhard **étendu** : `x * (1 + x / (Lb * Lb)) / (1 + x)` avec `Lb = 4` — les blancs redeviennent blancs
- **2 ·** 🔥 Le tone mapping sur la **luminance seulement**, puis `r, g, b` multipliés par le rapport — les couleurs saturées ne virent plus au blanc
- **3 ·** 🔥 L'**exposition automatique** : la lumière moyenne calculée dans `setup()`, ramenée à 0.18 — le « gris moyen » des photographes

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11b-tone-mapping.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11b-tone-mapping.md" download>md</a> · <a href="/ressources/ofApp11b.h" download>ofApp11b.h</a> · <a href="/ressources/ofApp11b.cpp" download>ofApp11b.cpp</a></p>

<!--
Une vraie image HDR (.hdr, ofFloatImage) en démonstration si possible —
ex 4 du document.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11c LUT
---

# 11c — LUT et étalonnage

**Toute** transformation d'un canal tient dans une table
de 256 valeurs : la LUT (*look-up table*). C'est l'outil
de l'étalonnage cinéma et du color grading des jeux.

<div class="mt-4 text-sm">

La différence avec le cours 11 n'est pas **ce qu'on**
calcule, mais **quand** : une fois pour les 256 valeurs
possibles, au lieu d'une fois par pixel.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11c-looks.png" alt="Quatre looks et leurs courbes" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">Identité, contraste, teal &amp; orange, vintage — et leurs courbes.</p>
</div>

<!--
La généralisation de tableLineaire (11a). Tous les filtres par canal du
cours 11 étaient déjà des LUT sans le savoir — le négatif est le look n°4
pour le prouver.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11c LUT
---

# Étape `construireLut()` — 256 tours, pas 400 000

```cpp
for (int i = 0; i < 256; i++) {
    float t = i / 255.0f;              // l'entrée, entre 0 et 1
    float r = t, g = t, b = t;         // identité par défaut

    switch (look) {
    case 1:                            // contraste : la courbe en S, trois fois
        r = g = b = courbeS(t);        // t*t*(3-2t) : la « smoothstep »
        break;
    case 2:                            // teal & orange, le look du cinéma d'action
        r = ofClamp(t + 0.12f * sin(t * PI), 0, 1);       // + de rouge au milieu
        g = t;
        b = ofClamp(t - 0.12f * sin(t * PI) + 0.10f * (1 - t), 0, 1);
        break;
    // case 3 vintage, case 4 négatif...
    }

    lutR[i] = ofClamp((t + (r - t) * force) * 255, 0, 255);   // la FORCE du look
    // lutG, lutB : idem
}
```

<div class="mt-2 text-sm">

- Trois tables **identiques** = contraste, luminosité. Trois tables **différentes** = on colore : l'étalonnage
- La **force** interpole entre l'identité `t` et le look — le curseur d'intensité de tous les logiciels d'étalonnage est fait comme ça
- La courbe en S (`smoothstep`) : 0 en 0, 1 en 1, pente nulle aux bouts — vous la retrouverez partout, jusque dans les shaders

</div>

<!--
Teal & orange : peaux orangées, ombres bleu-vert. Un étalonneur passe sa
journée à déplacer ces trois courbes (elles s'affichent en haut à droite de
la démo, tracées comme en 11b).
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11c LUT
---

# Étape `appliquerLut()` — trois lectures par pixel

```cpp
void ofApp::appliquerLut() {
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
- Limite : une LUT 1D ne mélange pas les canaux — elle ne peut pas **désaturer**. Le sépia et le daltonisme (11f) sont des matrices
- Le cinéma utilise des **LUT 3D** (grilles 17³ ou 33³) : le format `.cube` que chargent aussi les moteurs de jeu

</v-clicks>

</div>


<!--
update() : le drapeau habituel (force ou look changés). Exercice à faire faire
absolument : exporter ses réglages Photoshop en appliquant le look à un
dégradé 256×1 et le charger comme LUT — « tes réglages sont dans ton programme ».
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11c LUT
---

# À vous — tes propres looks

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Le **seuil**, la **postérisation** et le **gamma** du cours 11, refaits en LUT
- **2 ·** Un look « **nuit** » : tout tire vers le bleu, les rouges sont écrasés
- **3 ·** 🔥 Deux looks et une touche pour passer de l'un à l'autre **en fondu** : interpoler les deux tables (cours 06)

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11c-lut.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11c-lut.md" download>md</a> · <a href="/ressources/ofApp11c.h" download>ofApp11c.h</a> · <a href="/ressources/ofApp11c.cpp" download>ofApp11c.cpp</a></p>

<!--
L'ex 1 du document (charger une LUT depuis une bande de 256 pixels faite
dans un logiciel de retouche) est le pont vers le vrai pipeline étalonnage.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11d YCbCr
---

# 11d — YCbCr et compression

Une couleur RGB peut se réécrire en **une luminance Y**
et **deux axes de couleur** Cb (bleu-jaune) et Cr
(rouge-vert) — sans perdre d'information.

<div class="mt-4 text-sm">

<v-clicks>

- Y contient **tous les détails** ; Cb et Cr sont flous, presque sans contours
- Ce n'est pas un hasard : l'œil voit la luminance finement, la couleur grossièrement

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11d-ycbcr.png" alt="Les canaux Y, Cb, Cr" class="w-full object-contain" />
</div>

<!--
La luminance 0.299r + 0.587g + 0.114b du cours 11 vient de là : la formule
de la télévision (un téléviseur noir et blanc affichait Y).
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11d YCbCr
---

# Étapes `decomposer()` / `recomposer()` — un aller-retour exact

```cpp
// trois "images" de w*h float chacune — indice du pixel (x, y) : y * w + x
Y[i]  =       0.299f    * c.r + 0.587f    * c.g + 0.114f    * c.b;
Cb[i] = 128 - 0.168736f * c.r - 0.331264f * c.g + 0.5f      * c.b;
Cr[i] = 128 + 0.5f      * c.r - 0.418688f * c.g - 0.081312f * c.b;

// et l'inverse exact :
float r = y + 1.402f    * (cr - 128);
float g = y - 0.344136f * (cb - 128) - 0.714136f * (cr - 128);
float b = y + 1.772f    * (cb - 128);
```

<div class="mt-3 text-sm">

<v-clicks>

- Un changement d'espace **linéaire** : chaque nouveau nombre est un mélange pondéré des trois anciens (formules de la norme JPEG)
- Cb et Cr sont **centrés sur 128** : « ni l'un ni l'autre ». Une image grise a Cb = Cr = 128 partout
- Trois `vector<float>` comme images intermédiaires : des nombres à virgule, jamais affichés directement — et l'indice `y * w + x` qui range les lignes bout à bout (cours 17)

</v-clicks>

</div>

<!--
La décomposition est faite UNE fois dans setup() ; les vues relisent et
recomposent.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11d YCbCr
---

# Étapes `moyenneBloc()` / `calculerVue()` — l'expérience décisive

```cpp
// la moyenne du bloc n × n qui contient (x, y) — le coin par division entière
int x0 = x / n * n;
int y0 = y / n * n;
// ... somme des valeurs du bloc / compte

// vue 4 : la COULEUR en blocs, la luminance intacte  →  presque invisible
c = recomposer(Y[i], moyenneBloc(Cb, x, y, n), moyenneBloc(Cr, x, y, n));

// vue 5 : la LUMINANCE en blocs, la couleur intacte  →  image détruite
c = recomposer(moyenneBloc(Y, x, y, n), Cb[i], Cr[i]);
```

<div class="mt-3 text-sm">

<v-clicks>

- Même quantité d'information jetée dans les deux cas — l'œil reconstruit les formes **à partir de la luminance seule** ; la couleur n'est qu'un vernis
- C'est ce que fait la compression : JPEG et toute vidéo réduisent la résolution de Cb et Cr — le « **4:2:0** » des fiches techniques (un échantillon de couleur pour quatre pixels)
- Le cas qui bave : une frontière entre deux couleurs de **même luminance** — texte rouge sur fond bleu. D'où les sous-titres blancs sur noir

</v-clicks>

</div>


<!--
Souris = taille des blocs (2 à 32). Bel exercice : le chromakey propre dans
le plan (Cb, Cr) — les ombres du fond vert ne gênent plus. Et le flou sur
Cb/Cr seulement : le vrai débruitage couleur des photos de nuit.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11d YCbCr
---

# À vous — jouer avec la chroma

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Affiche **Cb et Cr en couleur** : `recomposer(128, Cb[i], 128)` et `recomposer(128, 128, Cr[i])` — on voit vers quoi tire chaque zone
- **2 ·** Du texte **rouge sur bleu**, enregistré en JPEG qualité 30 — zoome. Puis blanc sur noir. Explique la différence
- **3 ·** 🔥 Le **débruitage** : le flou boîte (cours 17) sur Cb et Cr seulement — le bruit coloré disparaît sans rendre l'image floue

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11d-ycbcr.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11d-ycbcr.md" download>md</a> · <a href="/ressources/ofApp11d.h" download>ofApp11d.h</a> · <a href="/ressources/ofApp11d.cpp" download>ofApp11d.cpp</a></p>

<!--
N°2 : la chroma sous-échantillonnée broie les bords rouge/bleu, pas les
bords de luminance. Le chromakey propre en (Cb, Cr) : ex 4, avancé aussi.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# 11e — Espaces perceptuels : OKLab

La limite de HSB : un jaune et un bleu de même
« luminosité » n'ont pas du tout la même **clarté perçue**
(jaune L = 0,97 ; bleu L = 0,45).

<div class="mt-4 text-sm">

<v-clicks>

- Dans OKLab, **la distance entre deux couleurs correspond à la différence perçue** — ni RGB ni HSB n'ont cette propriété
- Entré dans le CSS en 2023
- Trois nombres dans une `struct` à nous : `L` (clarté), `a` (vert↔rouge), `b` (bleu↔jaune)

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11e-degrades.png" alt="Dégradé bleu-jaune en RGB, HSB, OKLab" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">RGB grise au milieu, HSB traverse des verts, OKLab fait ce qu'un peintre ferait.</p>
</div>

<!--
a et b : comme Cb et Cr de 11d, mais gradués selon la perception. Le gris est
à a = 0, b = 0. Pas d'image dans ce cours : uniquement du dessin.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# Étape `versLab()` — simuler l'œil en trois étapes

```cpp
Lab ofApp::versLab(ofColor c) {
    // 1. sRGB → lumière linéaire (les convertisseurs de 11a)
    float r = versLineaire(c.r), g = versLineaire(c.g), bl = versLineaire(c.b);
    // 2. mélange vers l, m, s : les réponses des trois types de cônes
    float l = 0.4122214708f * r + 0.5363325363f * g + 0.0514459929f * bl;
    float m = 0.2119034982f * r + 0.6806995451f * g + 0.1073969566f * bl;
    float s = 0.0883024619f * r + 0.2817188376f * g + 0.6299787005f * bl;
    // 3. racine cubique (l'œil répond de façon compressée), puis mélange final
    l = cbrt(l); m = cbrt(m); s = cbrt(s);
    Lab out;
    out.L = 0.2104542553f * l + 0.7936177850f * m - 0.0040720468f * s;
    out.a = 1.9779984951f * l - 2.4285922050f * m + 0.4505937099f * s;
    out.b = 0.0259040371f * l + 0.7827717662f * m - 0.8086757660f * s;
    return out;
}
```

<div class="mt-2 text-sm">

- Les nombres à dix décimales sont ceux publiés par Björn Ottosson (2020) : **personne ne les retient, on les copie**
- `versRGB()` fait les mêmes étapes à l'envers : mélange inverse, cube, mélange inverse, réencodage
- Le dégradé OKLab devient trivial : convertir A et B, **interpoler L, a, b séparément**, reconvertir

</div>

<!--
La fonction bande() de la démo compare les trois dégradés (RGB getLerped /
HSB chemin le plus court sur la roue / OKLab) — touches 1-4 pour changer de
paire de couleurs.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# Étape `depuisLCH()` — des palettes à clarté constante

```cpp
ofColor ofApp::depuisLCH(float L, float C, float h) {   // clarté, chroma, teinte
    Lab lab;
    lab.L = L;
    lab.a = C * cos(h);        // polaire → cartésien (cours 16)
    lab.b = C * sin(h);
    return versRGB(lab);
}

// huit teintes espacées sur le cercle, même L, même C :
for (int i = 0; i < 8; i++) {
    ofSetColor(depuisLCH(0.75f, 0.12f, i * TWO_PI / 8));
    ofDrawRectangle(20 + i * 95, 460, 90, 60);
}
```

<div class="mt-3 text-sm">

<v-clicks>

- OKLCH est à OKLab ce que HSB est à RGB : la lecture **polaire** — `C` est la distance au gris, `h` l'angle
- Les huit pavés paraissent **tous de la même clarté** : c'est ainsi qu'on construit une palette d'interface ou de graphique où rien ne crie — et c'est impossible en HSB
- Exercice à garder à vie : « texte noir ou blanc sur ce fond ? » → `L > 0.6` : noir ; sinon blanc

</v-clicks>

</div>


<!--
La démo montre aussi les 8 teintes HSB « équilibrées » avec leur L réel
dessous : jaune 0.97, bleu 0.45 — même « luminosité » HSB. C'est pour ça
qu'un texte jaune sur blanc est illisible. Le chroma est borné : à L donné,
toutes les teintes n'acceptent pas le même C (d'où le clamp de versSRGB).
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11e OKLab
---

# À vous — la clarté qui dit vrai

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** « Texte **noir ou blanc** sur ce fond ? » : si `L > 0.6`, noir, sinon blanc — teste sur les huit couleurs HSB
- **2 ·** **Trie** une liste de couleurs par clarté `L`, puis par teinte `h` — affiche les deux rangées
- **3 ·** 🔥 La **rotation de teinte** du cours 11, en OKLCH — compare avec la version HSB : les clartés ne bougent plus

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11e-oklab.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11e-oklab.md" download>md</a> · <a href="/ressources/ofApp11e.h" download>ofApp11e.h</a> · <a href="/ressources/ofApp11e.cpp" download>ofApp11e.cpp</a></p>

<!--
N°1 est la recette utilisée par les vrais design systems. Ex 4 (les cinq
couleurs du 12 en distance OKLab) boucle avec le 11g.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11f Daltonisme
---

# 11f — Daltonisme et accessibilité

Environ un homme sur douze ne voit pas les couleurs
comme la majorité. Un jeu où « vert = allié,
rouge = ennemi » est **injouable** pour lui si rien
d'autre ne les distingue.

<div class="mt-4 text-sm">

| Déficience | Cône | Fréquence |
|---|---|---|
| protanopie | rouge | ~1 % des hommes |
| deutéranopie | vert | ~6 % — la plus courante |
| tritanopie | bleu | très rare |

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11f-daltonisme.png" alt="Vision normale, protanopie, deutéranopie, tritanopie" class="w-full object-contain" />
</div>

<!--
Chiffres du document (matrices Machado, Oliveira et Fernandes, 2009).
Les formes complètes (cône absent) sont rares ; les partielles fréquentes —
d'où la sévérité réglée à la souris.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11f Daltonisme
---

# Étapes `simuler()` et `calculerImage()` — neuf nombres

```cpp
// chaque canal de sortie = un mélange pondéré des trois canaux d'entrée
ofColor ofApp::simuler(ofColor c) {
    float r = tableLineaire[c.r], g = tableLineaire[c.g], b = tableLineaire[c.b];
    float r2 = matrice[0] * r + matrice[1] * g + matrice[2] * b;
    float g2 = matrice[3] * r + matrice[4] * g + matrice[5] * b;
    float b2 = matrice[6] * r + matrice[7] * g + matrice[8] * b;
    return ofColor(versSRGB(r2), versSRGB(g2), versSRGB(b2));
}

// la sévérité interpole entre l'identité et la matrice cible, case par case :
for (int i = 0; i < 9; i++) {
    matrice[i] = identite[i] + (cible[i] - identite[i]) * severite;
}
```

<div class="mt-3 text-sm">

<v-clicks>

- Une **matrice 3 × 3** rangée dans une liste de 9, indice `ligne * 3 + colonne` — le sépia du cours 11 avait exactement cette forme ; la vision normale est l'identité `1 0 0 / 0 1 0 / 0 0 1`
- Appliquée à la **lumière linéaire** (11a), pas aux valeurs sRGB : elle décrit une réponse physique de l'œil
- Deux couleurs que l'œil simulé confond donnent la **même sortie**

</v-clicks>

</div>

<!--
Les neuf coefficients de chaque type sont dans le code (Machado et al. 2009) —
on les copie, comme ceux d'OKLab.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11f Daltonisme
---

# Étape `dessinerTest()` — la règle tient en une phrase

```cpp
ofColor vie(40, 190, 60), danger(220, 40, 40);
// à gauche : l'information n'est portée QUE par la couleur
ofSetColor(simuler(vie));    ofDrawRectangle(x, y, 120, 30);
ofSetColor(simuler(danger)); ofDrawRectangle(x + 130, y, 120, 30);

// à droite : couleur + hachures + symbole
ofSetColor(simuler(vie));    ofDrawRectangle(x + 300, y, 120, 30);
ofSetColor(simuler(danger)); ofDrawRectangle(x + 430, y, 120, 30);
for (int i = 0; i < 120; i += 10)
    ofDrawLine(x + 430 + i, y, x + 430 + i + 10, y + 30);   // hachures
```

<div class="mt-3 text-sm">

<v-clicks>

- En deutéranopie, les deux jauges de gauche sont **du même brun** — le joueur ne sait plus. À droite, la couleur a disparu mais **l'information est intacte**
- Un daltonien voit très bien les différences de **clarté** (11e) : deux couleurs qui diffèrent aussi en L restent distinguables

</v-clicks>

</div>

<div v-click class="mt-4 text-xl">
<b>Ne jamais coder une information par la couleur seule.</b>
</div>


<!--
Un concepteur qui voit normalement ne peut pas deviner ce qui se confond :
le simulateur est le seul moyen, et il faut tester TÔT. Photoshop, Unity,
Unreal et les navigateurs en ont un ; celui-ci tient en trente lignes et
s'applique à toute capture d'écran de leur jeu.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11f Daltonisme
---

# À vous — tester tes couleurs

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Le **sépia du cours 11 est une matrice** : ajoute-le comme type 4
- **2 ·** 🔥 La **palette d'un jeu que tu aimes** en pavés, passée dans les trois simulations : marque les paires qui se confondent, corrige-les avec une différence de clarté `L` (11e)
- **3 ·** 🔥 **Daltoniser** : mesure l'erreur que le daltonien ne voit pas et réinjecte-la dans le canal bleu, qu'il voit

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11f-daltonisme.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11f-daltonisme.md" download>md</a> · <a href="/ressources/ofApp11f.h" download>ofApp11f.h</a> · <a href="/ressources/ofApp11f.cpp" download>ofApp11f.cpp</a></p>

<!--
N°2 est l'exercice le plus « métier » du bloc : c'est un vrai contrôle
qualité de direction artistique.
-->

---
layout: split
breadcrumb: 7 — La couleur avancée / 11g Dithering
---

# 11g — Palette indexée et dithering

Quatre couleurs sur Game Boy, seize sur PICO-8 :
pour chaque pixel, choisir la couleur **la plus proche**
de la palette — et tromper l'œil pour les nuances
manquantes.

<div class="mt-4 text-sm">

Revenu à la mode avec le pixel art — et c'est le
dithering annoncé au cours 09a contre le banding.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11g-dithering.png" alt="Palettes Game Boy et PICO-8, Bayer, Floyd-Steinberg" class="w-full object-contain" />
</div>

<!--
La postérisation du cours 11, mais vers des couleurs choisies. Touche p :
Game Boy → noir et blanc → CGA → PICO-8. Souris : taille des gros pixels.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11g Dithering
---

# Étape `plusProche()` — la distance entre couleurs

```cpp
ofColor ofApp::plusProche(float r, float g, float b) {
    float meilleure = 1e9;                    // un milliard : battu d'office
    ofColor gagnante = palette[0];
    for (int i = 0; i < palette.size(); i++) {
        float dr = r - palette[i].r, dg = g - palette[i].g, db = b - palette[i].b;
        float d = dr * dr + dg * dg + db * db;    // distance AU CARRÉ
        if (d < meilleure) { meilleure = d; gagnante = palette[i]; }
    }
    return gagnante;
}
```

<div class="mt-3 text-sm">

<v-clicks>

- La distance dans le **cube RGB** (Pythagore en 3D, cours 09 et 12), comparée **au carré** : si `d1² < d2²` alors `d1 < d2` — la racine coûte pour rien
- La palette est un `vector<ofColor>` (`choisirPalette()` : Game Boy, N&B, CGA, PICO-8)
- Pour le rendu rétro, on travaille sur une **grille de gros pixels** : lire le pixel au centre de chaque case, remplir la case

</v-clicks>

</div>

<!--
Les copies R, G, B en float de l'image réduite (indice j * gw + i) : parce
que Floyd-Steinberg va MODIFIER ces valeurs en cours de route.
-->

---
layout: default
breadcrumb: 7 — La couleur avancée / 11g Dithering
---

# Étape `calculerImage()` — Bayer, puis Floyd-Steinberg

```cpp
// méthode 2 — dithering ordonné : un décalage selon la position (grille 4×4)
int bayer[16] = { 0, 8, 2, 10,  12, 4, 14, 6,  3, 11, 1, 9,  15, 7, 13, 5 };
float d = (bayer[(j % 4) * 4 + (i % 4)] / 16.0f - 0.5f) * ecart;
r += d; g += d; b += d;                     // ... puis plusProche(r, g, b)

// méthode 3 — diffusion d'erreur : ce que la palette n'a pas su représenter
// est réparti sur les voisins pas encore traités (7+3+5+1 = 16/16)
float er = r - q.r;                         // l'erreur commise sur ce pixel
R[k + 1]      += er * 7 / 16;               // à droite
R[k + gw - 1] += er * 3 / 16;               // en bas à gauche
R[k + gw]     += er * 5 / 16;               // en bas
R[k + gw + 1] += er * 1 / 16;               // en bas à droite
```

<div class="mt-3 text-sm">

<v-clicks>

- **Bayer** : deux pixels voisins de même couleur reçoivent des décalages différents → vus de loin, une nuance intermédiaire. Trame en damier, **stable dans le temps** — Game Boy, journaux
- **Floyd-Steinberg** : le ton moyen est respecté localement ; plus fin, sans trame — mais **grouille** sur une image animée (les GIF). L'ordre de parcours fait partie de l'algorithme
- Et la palette compte autant que l'algorithme : seize couleurs **réparties en clarté** (11e) rendent une photo reconnaissable — quatre verts, non

</v-clicks>

</div>


<!--
ecart = 255 / palette.size() : le décalage juste assez grand pour faire
basculer vers la couleur voisine. Les if de bord protègent la diffusion
(cours 04). Exercices : sa palette en OKLCH, distance OKLab dans plusProche,
Bayer 8×8, moyenne de case (11d), dégradé N&B avec les trois méthodes.
-->
---
layout: default
breadcrumb: 7 — La couleur avancée / 11g Dithering
---

# À vous — ta palette

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** **Ta propre palette** de huit couleurs, choisies en OKLCH (11e) pour couvrir les clartés de 0.2 à 0.9
- **2 ·** Un **dégradé noir → blanc** passé par les trois méthodes côte à côte : on voit exactement ce que fait chacune
- **3 ·** 🔥 La **distance OKLab** dans `plusProche` à la place de la RGB — les verts du feuillage sont mieux rendus

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11g-palette-dithering.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11g-palette-dithering.md" download>md</a> · <a href="/ressources/ofApp11g.h" download>ofApp11g.h</a> · <a href="/ressources/ofApp11g.cpp" download>ofApp11g.cpp</a></p>

<!--
Bayer 8×8 et la moyenne de case (avec moyenneBloc du 11d) dans le document.
Clôture du bloc : la palette personnelle peut resservir au projet 18.
-->


---
layout: section
breadcrumb: 3 — La couleur
---

# La couleur

Du cube RGB à la roue des teintes — et au métier

---
layout: split
breadcrumb: 3 — La couleur / Cours 09
---

# Cours 09 — RGB, HSB, dégradés

Depuis le cours 00, une couleur est trois nombres.
C'est ainsi que **l'écran** travaille — pas ainsi
que **nous** pensons la couleur.

<div class="mt-6 text-sm">

<v-clicks>

- Une deuxième manière de la décrire : la **teinte**
- Un type pour la manipuler comme une valeur : `ofColor`
- Quatre étapes dans `draw()` : les axes, une teinte animée, un arc-en-ciel, un dégradé

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/09-hsb.png" alt="Trois bandes teinte, saturation, luminosité ; deux cercles ; un dégradé ; une traînée arc-en-ciel" class="w-full object-contain" />
</div>

<!--
« La même couleur, un peu plus claire » ne se calcule pas dans le cube —
c'est pour ça que le cours 07 bricolait trois cosinus. Avant : cours 07.
Référence téléchargeable : ofApp09 (état final).
-->

---
layout: split
breadcrumb: 3 — La couleur / Cours 09
---

# Deux façons de décrire une couleur

<div class="text-sm">

**RGB : un cube.** Trois axes de 0 à 255, le noir à l'origine, le blanc au sommet opposé. Pratique pour l'écran, pénible pour l'humain.

**HSB : une roue.** La couleur comme on la **nomme** :

| Axe | Nom | 0 | 255 |
|---|---|---|---|
| H | **teinte** | rouge, puis jaune, vert, cyan, bleu, magenta… | retour au rouge |
| S | **saturation** | gris | couleur pure |
| B | **luminosité** | noir | couleur pleine |

<v-clicks>

- La teinte est une **position sur une roue** : après 255, retour à 0
- « La couleur suivante » = teinte + 1 ; « plus clair » = luminosité + 1
- En openFrameworks, les trois axes vont de **0 à 255** — pas de degrés

</v-clicks>

</div>

::right::

<div class="flex items-center gap-2 mt-12">
<img src="/ressources/cours/img/09-cube-rgb.png" alt="Cube RGB avec ses huit sommets colorés" class="w-1/2 object-contain" />
<img src="/ressources/cours/img/09-roue.png" alt="Roue des teintes, de 0 à 255 en tournant" class="w-1/2 object-contain" />
</div>

<!--
Le cube : « la couleur suivante de l'arc-en-ciel » n'y est pas une opération
simple. La roue : c'est une addition. Tout le cours tient là.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09
---

# Mise en place — la file du cours 07, et le temps

```cpp
// ofApp.h :  std::vector<float> prevX;   std::vector<float> prevY;
//            float t { 0 };

void ofApp::setup() {
    ofSetWindowShape(800, 600);
}

void ofApp::update() {
    t = ofGetElapsedTimef();

    prevX.push_back(mouseX);                 // les 25 dernières positions de la souris
    prevY.push_back(mouseY);
    if (prevX.size() > 25) {
        prevX.erase(prevX.begin());
        prevY.erase(prevY.begin());
    }
}
```

<div class="mt-3 text-sm">

<v-clicks>

- Rien de neuf : la file bornée et le temps en secondes du cours 07
- Tout le cours se passe dans `draw()`, par ajouts successifs — le fond est `ofBackground(30)`

</v-clicks>

</div>

<!--
Ceux qui ont encore leur traînée évoluée sous la main peuvent repartir d'elle.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09
---

# Étape 1 — voir les trois axes

```cpp {1-2|4-5|7-14}
float largeur = ofGetWidth();
float teinteChoisie = mouseX / largeur * 255;   // la souris choisit la teinte

for (int x = 0; x < largeur; x++) {
    float p = x / largeur * 255;                // 0 à gauche, 255 à droite

    ofSetColor(ofColor::fromHsb(p, 255, 255));              // bande 1 : la teinte
    ofDrawLine(x, 20, x, 60);

    ofSetColor(ofColor::fromHsb(teinteChoisie, p, 255));    // bande 2 : la saturation
    ofDrawLine(x, 70, x, 110);

    ofSetColor(ofColor::fromHsb(teinteChoisie, 255, p));    // bande 3 : la luminosité
    ofDrawLine(x, 120, x, 160);
}
```

<div class="mt-2 text-sm">

- Une ligne verticale par pixel, et à chaque pixel **un seul axe varie** : on *voit* la roue, puis gris → pur, puis noir → plein
- `ofColor` : la couleur entière dans une **struct** (cours 07) — `c.r`, `c.g`, `c.b`, `c.a` ; on la range, on la passe, on la transforme
- `ofColor::fromHsb(h, s, b)` construit la couleur ; le `::` se lit « de la famille `ofColor` ». Dans l'autre sens : `c.getHue()`, `c.getSaturation()`, `c.getBrightness()`
- `ofDrawLine(x1, y1, x2, y2)` : un trait entre deux points

</div>

<!--
Bouger la souris : les bandes 2 et 3 changent de teinte.
Essaie : inverser la première bande (255 - p) ; puis une quatrième bande de
son invention — saturation ET luminosité qui varient ensemble, par exemple.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09
---

# Étape 2 — animer une teinte : cosinus contre HSB

```cpp {1-6|8-11}
// la méthode du cours 07 : trois cosinus déphasés
float r = (cos(t * 1.2f)  / 2 + 0.5f) * 255;
float g = (cos(t * 1.0f)  / 2 + 0.5f) * 255;
float b = (cos(t * 0.86f) / 2 + 0.5f) * 255;
ofSetColor(r, g, b);
ofDrawCircle(150, 260, 60);

// en HSB : la teinte avance, saturation et luminosité pleines
float teinte = fmod(t * 40, 255);
ofSetColor(ofColor::fromHsb(teinte, 255, 255));
ofDrawCircle(400, 260, 60);
```

<div class="mt-3 text-sm">

- À gauche : ça bouge, mais on ne contrôle rien — teintes sales, passages par le gris
- À droite : **toutes les couleurs pures, dans l'ordre**, sans jamais griser
- `fmod(a, b)` : le reste de la division pour les `float` — `t * 40` grandit sans fin, `fmod(t * 40, 255)` repart à 0 après 255 : la teinte fait le tour de la roue, encore et encore

</div>

<!--
Les deux cercles côte à côte : laisser tourner et comparer.
Essaie : t * 200 au lieu de t * 40. Puis calculer la durée d'un tour de roue
à t * 40 : 255 / 40, un peu plus de six secondes.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09
---

# Étape 3 — la traînée arc-en-ciel

```cpp
for (int i = 0; i < prevX.size(); i++) {
    ofSetColor(ofColor::fromHsb(i * 10, 255, 255));
    ofDrawCircle(prevX[i], prevY[i], 5 + i);
}
```

<div class="mt-5 text-base">

<v-clicks>

- La traînée évoluée du cours 07, en **une** ligne de couleur
- Teinte = `i * 10` : le motif « nombre qui dépend de l'indice », avec le bon outil — un arc-en-ciel
- 25 éléments × 10 = 250 : la traînée parcourt presque toute la roue

</v-clicks>

</div>

<!--
Essaie : faire tourner l'arc-en-ciel avec le temps — i * 10 + t * 40. Il
faudra fmod pour rester sur la roue.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09
---

# Étape 4 — le dégradé : l'interpolation

```cpp
ofColor depart(255, 80, 0);
ofColor arrivee(0, 120, 255);
for (int x = 520; x < 780; x++) {
    float p = (x - 520) / 260.0f;                 // 0 → 1
    ofSetColor(depart.getLerped(arrivee, p));
    ofDrawLine(x, 200, x, 320);
}
```

<div class="mt-4 text-base">

<v-clicks>

- `a.getLerped(b, p)` (*linear interpolation*) : la couleur à la proportion `p` entre les deux — `0` donne `depart`, `1` donne `arrivee`, `0.5` le milieu
- Dans le cube RGB, c'est une **ligne droite** entre deux points
- Retiens le mot : **interpoler**. Il reviendra pour des positions, des tailles — tout ce qu'on veut faire passer en douceur d'une valeur à une autre

</v-clicks>

</div>

<!--
Essaie : comparer avec un dégradé qui interpole la TEINTE —
fromHsb(hDepart + (hArrivee - hDepart) * p, 255, 255). Lequel passe par le
gris ? getLerped : la droite RGB traverse le centre grisâtre du cube ; la
teinte reste sur la roue, toujours saturée.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — décris la bande produite par `ofColor::fromHsb(0, 255, p)` quand `p` va de 0 à 255. Puis celle de `fromHsb(p, 0, 255)`. Vérifie ensuite.

</div>

<div v-click class="mt-5 text-base">

**2 · La traînée apprivoisée** — reprends ta traînée évoluée du cours 07 et remplace les trois cosinus par une teinte qui avance (`fmod(t * 40, 255)`). Même vie, zéro gris.

</div>

<!--
Ex 1 : fromHsb(0, 255, p) = du noir au rouge pur (la luminosité monte, teinte
rouge). fromHsb(p, 0, 255) = saturation nulle : une bande BLANCHE uniforme —
la teinte ne compte plus quand il n'y a pas de couleur. Erreur type : s'attendre
à voir la roue parce que p est en première position.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09
---

# À vous (2/2)

<div class="mt-3 text-base">

**3 · Les couleurs qui vont ensemble** — les cercles du cours 03, colorés de deux façons : teinte aléatoire (saturation et luminosité fixes) contre trois `ofRandom` sur r, g, b. Lequel donne une palette harmonieuse, et pourquoi ?

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Le coucher de soleil** — un fond en dégradé **vertical** (une boucle sur `y`, des lignes horizontales, `getLerped` de l'orange au bleu nuit), et un soleil dont la teinte dépend de sa hauteur : plus la souris descend, plus il rougit.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/09-couleur.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/09-couleur.md" download>md</a> · <a href="/ressources/ofApp09.h" download>ofApp09.h</a> · <a href="/ressources/ofApp09.cpp" download>ofApp09.cpp</a></p>

<!--
Ex 3 : la teinte aléatoire gagne — même saturation, même luminosité, seules
les teintes changent : les couleurs partagent deux axes sur trois. Trois
ofRandom tirent n'importe où dans le cube, gris et bruns compris. C'est
l'argument HSB en une image.
Ex 4 : for (int y = 0; y < ofGetHeight(); y++) { p = y / hauteur ;
ofSetColor(orange.getLerped(bleuNuit, p)) ; ofDrawLine(0, y, largeur, y) ; }
puis le soleil : une teinte qui va du jaune (~42) au rouge (0) quand mouseY
augmente, par exemple fromHsb(42 * (1 - mouseY / hauteur), 255, 255).
Erreur type : la division entière dans p — mettre un .0f ou un float.
-->

---
layout: split
breadcrumb: 3 — La couleur / Cours 09a
---

# Cours 09a — La couleur au cinéma et dans le jeu

Une leçon **sans code** : le trajet que suit une couleur,
de la scène à ton œil.

<div class="mt-4 text-sm">

<v-clicks>

- Pourquoi une image floutée paraît trop sombre
- Pourquoi le ciel d'un jeu montre des bandes
- Pourquoi un rouge diffère d'un téléphone à un moniteur
- Ce que veut dire « ACES » dans un moteur de jeu

</v-clicks>

</div>

<div v-click class="mt-4 text-sm">

Les 256 valeurs ne sont **ni de la lumière, ni de la perception** : elles sont un codage entre les deux. Toutes les bizarreries viennent de là.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/09a-pipeline.png" alt="Le voyage de la couleur : scène, tone mapping, étalonnage, encodage, compression, écran, œil" class="w-full object-contain" />
</div>

<!--
À lire après le 09, avant d'attaquer les images. Cette leçon annonce les sept
leçons 11a à 11g, qui en démontent chaque étape avec du code — on les fera
après la géométrie et la convolution.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09a
---

# À gauche : de la lumière sans limite

<div class="mt-4 text-base">

<v-clicks>

- Une scène réelle, ou calculée par un moteur, contient des **quantités de lumière** : elles s'additionnent, se multiplient, et n'ont **pas de plafond** — le soleil est des milliers de fois plus lumineux qu'un mur à l'ombre
- C'est le **HDR**, *high dynamic range*. Dans cet espace, les calculs sont simples et justes : deux fois plus de lumière, c'est une multiplication par deux
- Un écran n'affiche que de 0 (noir) à 1 (son blanc maximum) : il faut **ramener** tout ce qui dépasse
- Couper brutalement donne des taches blanches sans détail. Le **tone mapping** est la courbe qui écrase les hautes lumières en douceur, comme une pellicule photo — ACES, dans Unreal et Unity, en est une *(→ 11b)*

</v-clicks>

</div>

<!--
Le mot HDR a deux sens pour les étudiants : la lumière sans plafond (ici) et le
label des téléviseurs (10 bits, plus loin). Les distinguer.
-->

---
layout: split
breadcrumb: 3 — La couleur / Cours 09a
---

# Au milieu : le codage

<div class="text-sm">

<v-clicks>

- Lumière ramenée entre 0 et 1, puis stockée sur 8 bits : **256 valeurs par canal**
- Réparties régulièrement en lumière, on gâcherait des niveaux dans les clairs et on en manquerait dans les sombres, où l'œil distingue tout
- D'où la courbe **gamma** ou **sRGB** : la valeur 128 n'est pas la moitié de la lumière, mais environ 22 %. Afficher, ça ne se voit pas ; **calculer** dessus — flou, dégradé, transparence — donne un résultat trop sombre *(→ 11a)*
- Avant l'encodage, l'**étalonnage** : contraste, ambiance, look cinéma — par une **LUT**, une table entrée → sortie *(→ 11c)*

</v-clicks>

</div>

::right::

<div class="flex flex-col gap-3">
<ZoomImage src="/ressources/cours/img/11a-degrades.png" alt="Un dégradé de valeurs 0 à 255 et un dégradé de lumière 0 à 100 % : le milieu n'est pas au même endroit" class="w-full object-contain" />
<ZoomImage src="/ressources/cours/img/11c-avant-apres.png" alt="Trois looks d'étalonnage, avant et après" class="w-full object-contain" />
</div>

<!--
En haut, les deux dégradés du 11a : même noir, même blanc, mais le milieu
de la lumière est à la valeur 186 — le 22 % du document. En bas, trois
looks du 11c : l'étalonnage est une courbe par canal. Revenir en linéaire
pour calculer, réencoder ensuite : c'est le réglage « Linear / Gamma » des
moteurs.
-->

---
layout: split
breadcrumb: 3 — La couleur / Cours 09a
---

# Profondeur de bits et banding

<div class="mt-2 text-sm">

<v-clicks>

- 256 niveaux par canal : **juste assez** pour qu'un dégradé paraisse continu, à condition d'être bien réparti
- À 16 niveaux, des **bandes** apparaissent : le banding des ciels de jeux et des vidéos trop compressées
- Le HDR des téléviseurs travaille sur **10 bits**, 1 024 niveaux, pour éviter ça sur une étendue plus grande
- Vieille astuce d'imprimeur : le **dithering**, qui alterne deux valeurs voisines en une trame fine, trompe l'œil avec peu de niveaux *(→ 11g)*

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/09a-banding.png" alt="Un dégradé sur 256 niveaux, sur 16 niveaux avec bandes visibles, sur 16 niveaux avec dithering" class="w-full object-contain" />
</div>

<!--
Trois bandes de l'image : 256 niveaux, 16 niveaux, 16 niveaux + dithering.
Faire deviner laquelle est laquelle avant de lire la légende.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09a
---

# La compression

<div class="mt-6 text-base">

<v-clicks>

- Une image ou une vidéo est presque toujours compressée — et la compression exploite une faiblesse de l'œil : nous voyons la **luminance** finement, la **couleur** grossièrement
- JPEG et toutes les vidéos séparent l'image en une luminance **Y** et deux canaux de couleur **Cb** et **Cr**, puis réduisent la résolution des deux derniers de moitié ou plus
- C'est le « **4:2:0** » des fiches techniques
- Ça marche remarquablement bien… sauf sur un texte rouge sur fond bleu, qui bave *(→ 11d)*

</v-clicks>

</div>

<!--
Demander où ils ont déjà vu du texte coloré baver : captures de jeu
compressées, vidéos YouTube de pixel art.
-->

---
layout: split
breadcrumb: 3 — La couleur / Cours 09a
---

# À droite : l'écran et son gamut

<div class="text-sm">

Le fer à cheval : toutes les couleurs que l'œil peut voir. Un écran mélange trois lumières et n'affiche que **l'intérieur de leur triangle** — son **gamut**.

| Gamut | Où |
|---|---|
| **sRGB** (= Rec.709 TV HD) | la plupart des moniteurs, le web, ce cours — le plus petit |
| **DCI-P3** | cinéma numérique, iPhone, Mac récents — un tiers plus grand |
| **Rec.2020** | télévision UHD et HDR — aucun écran grand public ne le couvre |

<v-clicks>

- `(255, 0, 0)` = le rouge **le plus saturé que l'écran sait faire** : plus vif sur un P3 que sur un sRGB
- Affichée sans conversion sur un autre écran, une image change de couleurs : c'est le rôle de la **gestion de couleur** du système
- Note honnête : ce diagramme est lui-même affiché en sRGB, donc faux hors du petit triangle

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/09a-gamut.png" alt="Diagramme de chromaticité avec les triangles sRGB, DCI-P3 et Rec.2020" class="w-full object-contain" />
</div>

<!--
Images délavées ou criardes d'un appareil à l'autre : gestion de couleur
absente ou mal faite.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09a
---

# Tout à droite : l'œil

<div class="mt-6 text-base">

<v-clicks>

- Le dernier maillon n'est pas une machine : l'œil ne perçoit **ni la lumière ni les valeurs sRGB** de façon régulière — un jaune et un bleu de même « luminosité » HSB n'ont pas la même clarté perçue
- Des espaces ont été construits pour que **la distance entre deux couleurs corresponde à ce que l'on perçoit** : Lab, et sa version moderne **OKLab**, adoptée par le CSS. Ils changent la façon de faire un dégradé ou une palette *(→ 11e)*
- Tous les yeux ne sont pas identiques : environ 8 % des hommes ont une vision des couleurs déficiente, la plupart confondant rouges et verts
- Un jeu dont une information n'est portée **que** par la couleur est injouable pour eux. Simuler leur vision : une matrice de neuf nombres ; la règle de conception tient en une phrase *(→ 11f)*

</v-clicks>

</div>

<!--
Le 8 % vient du document. La règle de conception (11f) : jamais la couleur
seule — toujours une forme, un symbole ou un texte en plus.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09a
---

# Les sept leçons

<div class="text-sm">

| Leçon | Sujet | Ce qu'on code |
|---|---|---|
| 11a | Gamma et espace linéaire | dégradés, mélange, exposition juste |
| 11b | HDR et tone mapping | exposition, courbes clamp, Reinhard, ACES |
| 11c | LUT et étalonnage | tables de 256 valeurs, looks cinéma |
| 11d | YCbCr et compression | séparation luminance / couleur, sous-échantillonnage |
| 11e | Espaces perceptuels | OKLab, dégradés propres, palettes à clarté constante |
| 11f | Daltonisme | matrices de simulation, test d'interface |
| 11g | Palette et dithering | réduction à une palette, Bayer, Floyd-Steinberg |

<v-clicks>

- Toutes utilisent la **machine du cours 11** : une double boucle, une image source, une image résultat, une formule par pixel
- Dans l'ordre ou à la carte — sauf 11a, nécessaire à 11b, 11e et 11f

</v-clicks>

</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/09a-couleur-jeu-video-cinema.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/09a-couleur-jeu-video-cinema.md" download>md</a></p>

<!--
Cette diapo est le sommaire du bloc couleur avancée (bloc 7, après la
géométrie et la convolution). À retenir : calculer en linéaire, afficher en
sRGB ; 8 bits suffisent tout juste ; la compression sacrifie la couleur, pas
la luminance ; un écran n'affiche que son gamut.
-->

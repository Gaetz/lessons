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

- RGB : un **cube** — pratique pour l'écran, pénible pour l'humain
- HSB : une **roue** (teinte) + deux réglages (saturation, luminosité)
- `ofColor` : la couleur devient une **valeur** qu'on range et transforme
- En openFrameworks, les six axes vont de **0 à 255** (pas de degrés)

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/09-hsb.png" alt="Bandes HSB, cercles animés, dégradé, traînée arc-en-ciel" class="w-full object-contain" />
</div>

<!--
« La même couleur, un peu plus claire » ne se calcule pas dans le cube —
c'est pour ça que le cours 08 bricolait trois cosinus. En HSB : luminosité +1.
Dans ce cours, update() reprend la file de 07/08 (25 positions de souris) —
rien de neuf de ce côté.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09
---

# Étape `draw()` (1/3) — voir les trois axes de HSB

```cpp
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

<div class="mt-3 text-sm">

<v-clicks>

- Une ligne verticale par pixel, et à chaque pixel **un seul axe varie** : on *voit* la roue, puis le gris→pur, puis le noir→plein
- `ofColor::fromHsb(h, s, b)` construit la couleur ; le `::` se lit « de la famille `ofColor` » — un outil rangé avec le type
- `ofDrawLine(x1, y1, x2, y2)` : un trait entre deux points

</v-clicks>

</div>

<!--
Dans l'autre sens : c.getHue(), c.getSaturation(), c.getBrightness() lisent
les axes d'une couleur existante — utilisés au cours 11.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09
---

# Étape `draw()` (2/3) — animer une couleur : 08 contre HSB

```cpp
// la méthode du cours 08 : trois cosinus déphasés
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

<v-clicks>

- À gauche : ça bouge, mais on ne contrôle rien — teintes sales, passages par le gris
- À droite : **toutes les couleurs pures, dans l'ordre**, sans jamais griser
- `fmod(a, b)` : le reste de la division pour les `float` — la teinte repasse à 0 après 255 et fait le tour de la roue

</v-clicks>

</div>

<!--
Les deux cercles côte à côte à l'écran : laisser tourner et comparer.
Le tour de roue prend un peu plus de six secondes (255 / 40).
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09
---

# Étape `draw()` (3/3) — dégradé et traînée arc-en-ciel

```cpp
// dégradé : l'interpolation
ofColor depart(255, 80, 0);
ofColor arrivee(0, 120, 255);
for (int x = 520; x < 780; x++) {
    float p = (x - 520) / 260.0f;                 // 0 → 1
    ofSetColor(depart.getLerped(arrivee, p));
    ofDrawLine(x, 200, x, 320);
}

// la traînée de 08, en UNE ligne de couleur
for (int i = 0; i < prevX.size(); i++) {
    ofSetColor(ofColor::fromHsb(i * 10, 255, 255));
    ofDrawCircle(prevX[i], prevY[i], 5 + i);
}
```

<div class="mt-3 text-sm">

<v-clicks>

- `a.getLerped(b, p)` : la couleur à la proportion `p` entre les deux — une **ligne droite dans le cube RGB**. « Interpoler » reviendra pour tout ce qu'on veut faire passer en douceur
- Teinte = `i * 10` : le motif « nombre selon l'indice » du cours 08, avec le bon outil — un arc-en-ciel
- Une couleur est un point à trois coordonnées : la **distance** entre deux couleurs se calcule comme entre deux points *(→ cours 12)*

</v-clicks>

</div>


<!--
Exercice 4 à souligner : cercles du cours 03 en teinte aléatoire vs trois
ofRandom — lequel donne des couleurs qui « vont ensemble » ? Et l'exercice 3 :
dégradé getLerped vs dégradé par teinte — lequel passe par le gris ?
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09
---

# À vous — la teinte au travail

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Reprends le rendu du cours 08 : remplace les trois cosinus par **une teinte qui avance**
- **2 ·** Colore les cercles du cours 03 avec une **teinte aléatoire** (saturation et luminosité fixes) — compare avec trois `ofRandom` : lequel donne des couleurs qui « vont ensemble » ?
- **3 ·** 🔥 Fais tourner la teinte de la traînée avec le temps : `i * 10 + t * 40` — il faudra `fmod`

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/09-couleur.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/09-couleur.md" download>md</a> · <a href="/ressources/ofApp09.h" download>ofApp09.h</a> · <a href="/ressources/ofApp09.cpp" download>ofApp09.cpp</a></p>

<!--
N°2 est l'argument HSB en une image. Ex 3 du document (les deux dégradés,
lequel passe par le gris) en démonstration si le temps manque.
-->

---
layout: split
breadcrumb: 3 — La couleur / Cours 09a
---

# Cours 09a — La couleur au cinéma et dans le jeu

Une leçon **sans code** : le trajet que suit une couleur,
de la scène à ton œil.

<div class="mt-4 text-sm">

Les 256 valeurs ne sont **ni de la lumière, ni de la
perception** : elles sont un codage entre les deux.
Toutes les bizarreries viennent de là.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/09a-pipeline.png" alt="Le voyage de la couleur : scène, tone mapping, encodage, compression, écran, œil" class="w-full object-contain" />
</div>

<!--
Les questions qu'elle répond : pourquoi une image floutée paraît trop sombre,
pourquoi un ciel de jeu montre des bandes, pourquoi un rouge diffère d'un
écran à l'autre, ce que veut dire « ACES » dans Unreal.
-->

---
layout: default
breadcrumb: 3 — La couleur / Cours 09a
---

# Le voyage d'une couleur

<div class="mt-4 text-base">

<v-clicks>

- **La scène** : de la lumière sans plafond (HDR) — le **tone mapping** l'écrase sous le blanc de l'écran *(→ 11b)*
- **Le codage** : la courbe **gamma/sRGB** donne plus de niveaux aux sombres — calculer dessus sans décoder rend tout faux *(→ 11a)*
- **L'étalonnage** : la **LUT**, table d'entrée→sortie, l'outil des looks cinéma *(→ 11c)*
- **La compression** : l'œil voit la luminance finement, la couleur grossièrement — JPEG et la vidéo en profitent *(→ 11d)*
- **L'écran** : n'affiche que son **gamut** — sRGB, P3, Rec.2020 *(le fer à cheval du document)*
- **L'œil** : ni régulier *(→ OKLab, 11e)*, ni identique chez tous *(→ daltonisme, 11f)*

</v-clicks>

</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/09a-couleur-jeu-video-cinema.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/09a-couleur-jeu-video-cinema.md" download>md</a></p>

<!--
Cette diapo est le sommaire du bloc couleur avancée. Le banding/dithering
(→ 11g) est dans le document, image 09a-banding.png, ainsi que le gamut
(09a-gamut.png) avec l'aveu honnête : le diagramme est lui-même affiché en sRGB.
-->

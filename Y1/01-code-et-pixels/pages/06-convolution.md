---
layout: section
breadcrumb: 6 — La convolution
---

# La convolution

Un pixel et ses huit voisins

---
layout: split
breadcrumb: 6 — La convolution / Cours 17
---

# Cours 17 — La convolution

Au cours 11, un pixel ne dépendait que de lui-même.
Au 14, d'un autre pixel. Ici, il dépend de **neuf** :
lui et ses huit voisins.

<div class="mt-4 text-sm">

Flou, netteté, contours, relief : **un seul code**,
seule une grille de neuf nombres change.
C'est l'outil central du traitement d'image.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/17-convolution.png" alt="Flou, gaussien, netteté, contours, relief" class="w-full object-contain" />
</div>

<!--
Même mise en place qu'au cours 11 : source, resultat, un int effet.
pandaroux.jpg dans bin/data. Trois étapes : la fonction, les noyaux, le
drapeau.
-->

---
layout: split
breadcrumb: 6 — La convolution / Cours 17
---

# Le noyau — une moyenne pondérée des voisins

<div class="text-sm">

Une grille 3 × 3 de **poids**. Pour chaque pixel du résultat :
les 3 × 3 pixels de la source centrés au même endroit,
chacun multiplié par le poids en face, **le tout additionné**.

</div>

<div class="mt-4 text-sm">

<v-clicks>

- Tous à 1/9 : le **flou boîte**, la moyenne des neuf
- 1 2 1 / 2 4 2 / 1 2 1 sur 16 : le **flou gaussien**, le centre pèse plus
- 0 −1 0 / −1 5 −1 / 0 −1 0 : la **netteté**, le centre renforcé
- −1 partout, 8 au centre : les **contours**
- **Somme des poids = 1** : la luminosité est conservée. **Somme = 0** : une zone plate devient noire, seules les différences restent

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/17-noyau.png" alt="Le pixel et ses 8 voisins, multipliés case par case par le noyau, puis additionnés" class="w-full object-contain" />
</div>

<!--
Le relief (−1 en haut à gauche, 1 en bas à droite, somme 0) arrive à
l'étape 2 avec le biais. Faire lire le schéma : multiplier case par case,
puis additionner.
-->

---
layout: default
breadcrumb: 6 — La convolution / Cours 17
---

# Deux coordonnées, un indice — le ruban

<div class="mt-5 flex justify-center items-center gap-8">
  <div>
    <div class="flex gap-1 mb-1"><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #EA5027;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #EA5027;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #EA5027;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #EA5027;"></div></div>
    <div class="flex gap-1 mb-1"><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #0F6FA5;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #0F6FA5;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #0F6FA5;background:#0F6FA5;color:#fff;">★</div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #0F6FA5;"></div></div>
    <div class="flex gap-1"><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #999;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #999;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #999;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #999;"></div></div>
    <div class="text-center text-xs op-60 mt-2">la grille vue à l'écran (w = 4)<br>★ = le pixel (x = 2, y = 1)</div>
  </div>
  <div class="text-2xl op-60">→</div>
  <div>
    <div class="flex gap-1"><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #EA5027;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #EA5027;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #EA5027;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #EA5027;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #0F6FA5;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #0F6FA5;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #0F6FA5;background:#0F6FA5;color:#fff;">★</div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #0F6FA5;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #999;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #999;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #999;"></div><div class="w-9 h-9 flex items-center justify-center text-xs font-bold" style="border:2px solid #999;"></div></div>
    <div class="flex gap-1"><div class="w-9 text-center text-xs op-60">0</div><div class="w-9 text-center text-xs op-60">1</div><div class="w-9 text-center text-xs op-60">2</div><div class="w-9 text-center text-xs op-60">3</div><div class="w-9 text-center text-xs op-60">4</div><div class="w-9 text-center text-xs op-60">5</div><div class="w-9 text-center text-xs op-60">6</div><div class="w-9 text-center text-xs op-60">7</div><div class="w-9 text-center text-xs op-60">8</div><div class="w-9 text-center text-xs op-60">9</div><div class="w-9 text-center text-xs op-60">10</div><div class="w-9 text-center text-xs op-60">11</div></div>
    <div class="text-center text-xs op-60 mt-2">la même grille en mémoire : les lignes bout à bout</div>
  </div>
</div>

<div class="mt-7 text-sm">

<v-clicks>

- La mémoire est une **rangée de cases** (cours 01) : une grille s'y range **ligne après ligne**, bout à bout — un ruban
- La case `(x, y)` est à l'indice **`y * w + x`** : sauter `y` lignes complètes, puis avancer de `x` — le ★ : 1 × 4 + 2 = **6**
- Pour le noyau, la grille fait 3 de large et `dx`, `dy` partent de −1, d'où le `+ 1` : **`(dy + 1) * 3 + (dx + 1)`**

</v-clicks>

</div>

<!--
C'est ce que fait getColor(x, y) sous le capot à chaque appel, et le même
calcul resservira aux cours 11d, 11f et 11g. Les sommes se feront en float
avec un ofClamp final : les poids négatifs sortent de 0-255 (cours 11).
-->

---
layout: default
breadcrumb: 6 — La convolution / Cours 17
---

# Étape 1 (1/2) — `appliquerNoyau()` : quatre boucles

```cpp {1|2-4|5-12|14-16}
void ofApp::appliquerNoyau(std::vector<float> noyau, float biais) {
    for (int y = 0; y < h; y++) {                   // w, h : la taille de source
        for (int x = 0; x < w; x++) {               // tous les pixels (cours 11)
            float r = biais, g = biais, b = biais;
            for (int dy = -1; dy <= 1; dy++) {      // les neuf voisins
                for (int dx = -1; dx <= 1; dx++) {
                    int px = ofClamp(x + dx, 0, w - 1);        // le bord remplace
                    int py = ofClamp(y + dy, 0, h - 1);        // le voisin manquant
                    ofColor v = source.getColor(px, py);
                    float poids = noyau[(dy + 1) * 3 + (dx + 1)];
                    r += v.r * poids;  g += v.g * poids;  b += v.b * poids;
                }
            }
            resultat.setColor(x, y, ofColor(ofClamp(r, 0, 255), ofClamp(g, 0, 255), ofClamp(b, 0, 255)));
        }
    }
    resultat.update();
}
```

<div class="mt-2 text-sm">

- Annoncée dans le `.h` : `void appliquerNoyau(std::vector<float> noyau, float biais);`
- Les deux boucles **extérieures** sont celles du cours 11 ; les deux **intérieures** parcourent les voisins : `dx` et `dy` valent −1, 0 ou 1, `(0, 0)` est le pixel lui-même
- Le poids du voisin : le **ruban** appliqué à la grille 3 × 3 du noyau. Sommes en `float`, `ofClamp` final

</div>

<!--
Quatre clics : la signature (le noyau est un vector de 9 poids), les pixels,
les voisins, l'écriture. r += ... est le raccourci de r = r + ... (cours 06
bis). w et h : int w = source.getWidth(); en tête de fonction.
-->

---
layout: default
breadcrumb: 6 — La convolution / Cours 17
---

# Étape 1 (2/2) — le test de l'identité, et les bords

```cpp
// dans setup(), pour tester tout de suite :
    appliquerNoyau({ 0, 0, 0,
                     0, 1, 0,
                     0, 0, 0 }, 0);
```

<div class="mt-4 text-base">

<v-clicks>

- Le noyau **identité** : poids 1 au centre, 0 partout ailleurs — l'image est copiée telle quelle. Si ce n'est pas le cas, la fonction a un bug
- La liste `{ 0, 0, 0, ... }` est créée **sur place**, dans l'appel — écrite sur trois lignes, elle ressemble à la grille qu'elle représente
- **Le problème des bords** : le pixel `(0, 0)` n'a pas de voisin en `(−1, −1)`. Trois solutions classiques — ignorer les bords, les considérer noirs, ou **réutiliser le pixel du bord**
- C'est la troisième qu'on prend, avec l'`ofClamp` sur `px` / `py` : simple, et sans liseré noir

</v-clicks>

</div>

<!--
Essaie : déplacer le 1 du noyau identité dans un coin — l'image se décale.
Dans quel sens ? (La lecture à l'envers du cours 14 répond : le 1 en bas à
droite lit le voisin (x+1, y+1), l'image monte vers la gauche.)
-->

---
layout: default
breadcrumb: 6 — La convolution / Cours 17
---

# Étape 2 — `calculer()` : les noyaux célèbres

```cpp
    switch (effet) {
    case 1: appliquerNoyau({ 1/9.0f, 1/9.0f, 1/9.0f,       // flou boîte : la moyenne
                             1/9.0f, 1/9.0f, 1/9.0f,
                             1/9.0f, 1/9.0f, 1/9.0f }, 0);  break;
    case 2: appliquerNoyau({ 1/16.0f, 2/16.0f, 1/16.0f,    // flou gaussien : le centre pèse plus
                             2/16.0f, 4/16.0f, 2/16.0f,
                             1/16.0f, 2/16.0f, 1/16.0f }, 0);  break;
    case 3: appliquerNoyau({  0, -1,  0,                    // netteté (somme = 1)
                             -1,  5, -1,
                              0, -1,  0 }, 0);  break;
    case 4: appliquerNoyau({ -1, -1, -1,                    // contours (somme = 0)
                             -1,  8, -1,
                             -1, -1, -1 }, 0);  break;
    case 5: appliquerNoyau({ -1, 0, 0,                      // relief : deux coins opposés
                              0, 0, 0,
                              0, 0, 1 }, 128);  break;
    }
```

<div class="mt-2 text-sm">

- **Somme des poids = 1** : la luminosité est conservée (flou, netteté). **Somme = 0** : les zones plates deviennent noires, seules les **différences** restent (contours)
- Le **biais** : le relief calcule une différence, aussi souvent négative que positive — sans rien, la moitié de l'image serait noire. Ajouté avant de borner, 128 fait d'une différence nulle un gris moyen : un relief éclairé en biais

</div>

<!--
Le code de appliquerNoyau ne change jamais : seule la recette change. Essaie :
chaque noyau un par un, puis le sien — que fait { 0, 0, 0, 1, 0, -1, 0, 0, 0 }
avec un biais de 128 ? (Un relief horizontal : gauche moins droite.)
-->

---
layout: default
breadcrumb: 6 — La convolution / Cours 17
---

# Étape 3 — le drapeau : ne payer qu'une fois

```cpp
// ofApp.h :  bool aRecalculer { true };

void ofApp::update() {
    if (aRecalculer) {
        calculer();
        aRecalculer = false;
    }
}

void ofApp::keyPressed(int key) {
    if (key >= '0' && key <= '9') {
        effet = key - '0';
        aRecalculer = true;
    }
}
```

<div class="mt-3 text-sm">

<v-clicks>

- 400 000 pixels × 9 voisins = 3,6 millions de lectures : trop pour recommencer 60 fois par seconde. Or le résultat ne change que quand on change d'effet
- Un `bool` qui dit « il y a du travail à faire », **levé** par l'événement, **rabaissé** une fois le travail fait : c'est un **drapeau**
- Le motif de tout ce qui coûte cher — il revient au cours 18

</v-clicks>

</div>

<!--
Essaie : enlever le drapeau (recalculer à chaque frame) et comparer la
fluidité, puis le remettre. key - '0' : le caractère '3' moins le caractère
'0' donne l'entier 3.
-->

---
layout: default
breadcrumb: 6 — La convolution / Cours 17
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — que fait ce noyau, avec un biais de 0 ? Et le second ? Réponds, puis vérifie.

```cpp
appliquerNoyau({ 0, 0, 0,  0, 2, 0,  0, 0, 0 }, 0);
appliquerNoyau({ 0, 0, 0,  0, 0, 0,  0, 0, 1 }, 0);
```

</div>

<div v-click class="mt-5 text-base">

**2 · Le dessin au crayon** — le **négatif** des contours (reprends le négatif du cours 11, appliqué au résultat du noyau contours) : traits sombres sur fond clair.

</div>

<!--
Ex 1 : le premier double chaque composante — l'image s'éclaircit et sature
(le clamp coupe à 255). Le second lit le voisin (x+1, y+1) : l'image se
décale d'un pixel vers le haut-gauche.
Ex 2 : 255 - r, 255 - g, 255 - b sur chaque pixel de resultat après le noyau
contours — ou un noyau à poids inversés avec un biais de 255.
-->

---
layout: default
breadcrumb: 6 — La convolution / Cours 17
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · Le double flou** — applique le flou deux fois de suite. Il faut copier `resultat` dans `source` entre les deux passes (ou une troisième image). Compare avec le flou gaussien simple.

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Sobel** — le noyau `{ -1, -2, -1, 0, 0, 0, 1, 2, 1 }` détecte les contours **horizontaux** ; le même tourné d'un quart de tour, les verticaux. Applique les deux, puis combine : `sqrt(h*h + v*v)` sur chaque canal — LE détecteur de contours, celui qui ressert au cours 18 pour suivre les formes.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/17-convolution.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/17-convolution.md" download>md</a> · <a href="/ressources/ofApp17.h" download>ofApp17.h</a> · <a href="/ressources/ofApp17.cpp" download>ofApp17.cpp</a> · <a href="/ressources/data/pandaroux.jpg" download>pandaroux.jpg</a></p>

<!--
Ex 3 : source = resultat; puis calculer() — erreur type : oublier la copie,
le second flou relit la source d'origine et ne change rien. Un flou boîte
appliqué deux fois ressemble beaucoup au gaussien.
Ex 4 : le noyau vertical est { -1, 0, 1, -2, 0, 2, -1, 0, 1 } ; il faut deux
images de résultat (ou garder les sommes en float avant le clamp), puis
sqrt(h*h + v*v) canal par canal. Sobel resservira au 18 (suivre les formes).
-->

---
layout: section
breadcrumb: 4 — L'image et ses pixels
---

# L'image et ses pixels

Lire, écrire, filtrer

---
layout: split
breadcrumb: 4 — L'image et ses pixels / Cours 10
---

# Cours 10 — Image et pixel

Jusqu'ici, tout venait de nos ordres de dessin.
On charge maintenant une image, on l'affiche —
et surtout on **lit** la couleur d'un pixel.

<div class="mt-4 text-sm">

Une image chargée est une **grille** : `largeur × hauteur`
cases, une couleur par case. Même repère que l'écran :
`(0, 0)` en haut à gauche.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/10-pixels.png" alt="Image et zoom pixel avec valeurs RGB" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">Un « bord » n'existe pas : juste des cases de couleurs différentes.</p>
</div>

<!--
image2.png fait 200 × 200 : 40 000 pixels, de (0,0) à (199,199).
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 10
---

# Étape `setup()` — charger, et vérifier

```cpp
// ofApp10.h :   ofImage img;

void ofApp::setup() {
    ofSetWindowShape(200, 200);

    bool ok = img.load("image2.png");    // chemin relatif à bin/data !
    if (!ok) {
        ofLogError() << "image2.png introuvable dans bin/data";
    }
}
```

<div class="mt-4 text-sm">

<v-clicks>

- Les images vont dans **`bin/data`**, jamais à côté du `.cpp`
- `bool` : un type qui ne vaut que `true` ou `false` ; le `!` se lit « non »
- **Toujours vérifier** : une image introuvable ne provoque aucune erreur visible, juste une fenêtre vide — et on cherche longtemps

</v-clicks>

</div>

<!--
ofLogError() << ... : comme std::cout, mais marqué comme erreur dans la console.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 10
---

# Étape `draw()` — afficher, lire un pixel, le montrer

```cpp {1-2|4-6|8-13}
    ofSetColor(255);                     // sans ça : l'image est TEINTÉE
    img.draw(0, 0);

    int px = ofClamp(mouseX, 0, img.getWidth() - 1);    // rester dans l'image
    int py = ofClamp(mouseY, 0, img.getHeight() - 1);
    ofColor c = img.getColor(px, py);    // la couleur du pixel (px, py)

    std::string texte = "R=" + ofToString(c.r) + " G=" + ofToString(c.g)
                      + " B=" + ofToString(c.b);
    ofSetColor(255, 200, 0);
    ofDrawBitmapString(texte, 10, 10);
    ofSetColor(c);                                      // un carré de la couleur lue
    ofDrawRectangle(mouseX + 10, mouseY + 10, 20, 20);
```

<div class="mt-2 text-sm">

- `ofClamp(v, min, max)` **borne** : la souris peut sortir de l'image, la coordonnée lue, non — le problème d'indice du cours 04, encore. Dernier pixel : `largeur - 1`
- `getColor` lit **l'image chargée**, pas l'écran : un cercle dessiné par-dessus est invisible pour elle — l'image est une source de données stable *(exploité au cours 12)*
- On lit l'image **comme un tableau de nombres**

</div>


<!--
Exercices : pandaroux.jpg + fenêtre adaptée, luminosité (r+g+b)/3 (division
entière !), carré proportionnel, image teintée, teinte pure via getHue.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 10
---

# À vous — lire des pixels

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Charge `pandaroux.jpg` à la place — et adapte la fenêtre : `ofSetWindowShape(img.getWidth(), img.getHeight())`
- **2 ·** Affiche la **luminosité** du pixel : `(c.r + c.g + c.b) / 3` — attention à la division entière
- **3 ·** 🔥 Affiche la **teinte** du pixel (`c.getHue()`) et, à côté, un carré de sa couleur « pure » : `ofColor::fromHsb(c.getHue(), 255, 255)`

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/10-image-pixel.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/10-image-pixel.md" download>md</a> · <a href="/ressources/ofApp10.h" download>ofApp10.h</a> · <a href="/ressources/ofApp10.cpp" download>ofApp10.cpp</a> · <a href="/ressources/data/image2.png" download>image2.png</a></p>

<!--
N°2 : le piège du cours 01 revient tout seul. N°3 prépare les filtres HSB
du cours 11.
-->

---
layout: split
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Cours 11 — Les filtres

Un filtre, c'est une règle : « pour chaque pixel,
remplace sa couleur par f(couleur) ».

Dix règles différentes, **une même boucle** qui les
applique. Touches 0-9 pour l'effet, souris pour
le paramètre.

::right::

<div>
<ZoomImage src="/ressources/cours/img/11-filtres.png" alt="Huit filtres appliqués à la même photo" class="w-full object-contain" />
</div>

<!--
Négatif, gris, luminosité, contraste, seuil, postérisation, rotation de
teinte, color splash. Cliquer pour agrandir et comparer.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Mise en place — deux images, jamais une

```cpp
// ofApp11.h :  ofImage source;   ofImage resultat;
//              int effet = 0;    float parametre = 0.5f;

void ofApp::setup() {
    ofSetWindowShape(774, 516);
    if (!source.load("pandaroux.jpg")) {
        ofLogError() << "pandaroux.jpg introuvable dans bin/data";
    }
    resultat.allocate(source.getWidth(), source.getHeight(), OF_IMAGE_COLOR);
}
```

<div class="mt-4 text-sm">

<v-clicks>

- On lit dans la **source**, on écrit dans le **résultat** — on ne modifie jamais la source
- Sinon : changer d'effet partirait d'une image déjà transformée, et deux négatifs ne redonneraient pas l'original
- `allocate` réserve une image vide de la bonne taille, en couleur

</v-clicks>

</div>

<!--
Le .h porte aussi la liste noms des effets, pour l'affichage.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Étape `update()` — le motif fondamental

```cpp
void ofApp::update() {
    parametre = mouseX / (float)ofGetWidth();      // 0 à gauche, 1 à droite

    for (int y = 0; y < source.getHeight(); y++) {      // chaque ligne
        for (int x = 0; x < source.getWidth(); x++) {   //   chaque colonne
            ofColor c = source.getColor(x, y);
            resultat.setColor(x, y, filtre(c, parametre));
        }
    }
    resultat.update();     // envoyer les nouveaux pixels à la carte graphique
}
```

<div class="mt-3 text-sm">

<v-clicks>

- Une boucle **dans** une boucle : le corps tourne `largeur × hauteur` fois — 400 000 fois par frame ici
- `filtre(c, parametre)` est la **recette** appliquée à chaque pixel : la machine d'abord, la recette juste après
- Ce motif revient dans **tous les cours jusqu'à la fin** — et c'est, en esprit, ce que fait un shader (sur GPU, en parallèle)
- Sans `resultat.update()`, `draw()` continue d'afficher l'ancienne version

</v-clicks>

</div>

<!--
Si ça rame : ne recalculer que quand la souris/l'effet a changé (cours 17),
ou lire le tableau de pixels brut au lieu de getColor/setColor.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# L'octet — la petite case qui reboucle

<div class="mt-5 text-sm">

<div class="flex items-center gap-4 mb-3">
  <code class="font-bold w-38">unsigned char</code>
  <div class="w-16 h-11 rounded flex items-center justify-center text-lg font-bold" style="border:3px solid #000">250</div>
  <span class="op-60">1 octet = 8 bits → 256 valeurs : de <b>0 à 255</b>, rien au-delà</span>
</div>

<div class="flex items-center gap-4 mb-3">
  <code class="font-bold w-38">ofColor c</code>
  <div class="flex rounded overflow-hidden" style="border:3px solid #000">
    <div class="w-14 h-11 flex flex-col items-center justify-center" style="border-right:2px dashed #999"><span class="text-xs font-bold" style="color:#EA5027">r</span><span class="text-sm">250</span></div>
    <div class="w-14 h-11 flex flex-col items-center justify-center" style="border-right:2px dashed #999"><span class="text-xs font-bold" style="color:#2a7">g</span><span class="text-sm">80</span></div>
    <div class="w-14 h-11 flex flex-col items-center justify-center"><span class="text-xs font-bold" style="color:#0F6FA5">b</span><span class="text-sm">32</span></div>
  </div>
  <span class="op-60">trois octets collés — la <code>struct</code> du cours 07 : <code>c.r</code>, <code>c.g</code>, <code>c.b</code></span>
</div>

<div class="flex items-center gap-4">
  <span class="font-bold w-38">250 + 10 ?</span>
  <div class="flex items-center gap-1 font-mono text-base">
    <span class="op-40">253</span><span class="op-60">254</span><span class="font-bold">255</span>
    <span class="text-lg" style="color:#EA5027">↺</span>
    <span class="font-bold" style="color:#EA5027">0</span><span class="op-60" style="color:#EA5027">1</span><span class="op-40" style="color:#EA5027">2</span>
  </div>
  <span class="op-60">le compteur <b>reboucle</b> : 250 + 10 = <b style="color:#EA5027">4</b></span>
</div>

</div>

<div class="mt-6 text-sm">

<v-clicks>

- La grande case du cours 01 (`float`, 4 octets) serait un luxe : l'écran ne connaît que 256 niveaux par canal — un octet suffit, l'image pèse 4 × moins
- Mais la petite case **déborde vite** : un filtre « luminosité +60 » sur un pixel clair ferait des taches noires
- D'où le geste qu'on va voir dans `filtre()` : **copier en `float`**, calculer au large, borner avec `ofClamp`, reconstruire

</v-clicks>

</div>

<!--
Le nom unsigned char : un char = un octet, unsigned = sans signe, donc 0-255.
Faire compter la salle : 8 bits, 2^8 = 256. L'image mentale du compteur
kilométrique qui repasse à zéro.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Étape `filtre()` (1/3) — une fonction qui renvoie, et le débordement

```cpp
ofColor ofApp::filtre(ofColor c, float p) {
    float r = c.r;                       // copier en float AVANT de calculer
    float g = c.g;
    float b = c.b;
    float luminance = 0.299f * r + 0.587f * g + 0.114f * b;

    switch (effet) {
    case 1:                              // négatif : chaque canal retourné
        return ofColor(255 - r, 255 - g, 255 - b);
    case 2: {                            // gris : les trois canaux égaux
        float gris = (r + g + b) / 3;
        return ofColor(gris, gris, gris);
    }
    case 3:
        return ofColor(luminance);       // un seul nombre = un gris
```

<div class="mt-2 text-sm">

- La fonction commence par `ofColor` : elle **renvoie** une couleur — `return` donne la valeur et termine. Un pixel entre, un pixel sort : la définition d'un filtre
- La copie en `float` d'abord : les composantes sont les **octets de la diapo précédente** — calculer directement dessus reboucle (`250 + 10 = 4`)
- Deux gris : la moyenne, et la **luminance** — l'œil est plus sensible au vert, un vert pur paraît plus clair qu'un bleu pur

</div>

<!--
switch (variable) : un if à plusieurs branches ; case + return sort de la
fonction (sinon break). Un case qui déclare une variable : accolades.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Étape `filtre()` (2/3) — les formules paramétrées

```cpp
    case 4: {                            // luminosité : tout monte ou descend
        float k = (p - 0.5f) * 256;
        return ofColor(ofClamp(r + k, 0, 255), ofClamp(g + k, 0, 255),
                       ofClamp(b + k, 0, 255));
    }
    case 5: {                            // contraste : écarter du gris moyen
        float k = p * 3;
        return ofColor(ofClamp((r - 128) * k + 128, 0, 255), /* g, b idem */);
    }
    case 6:                              // seuil : noir ou blanc, rien entre
        if (luminance < p * 255) return ofColor(0);
        else                     return ofColor(255);
    case 7: {                            // postérisation : arrondir à un multiple
        float pas = 8 + p * 120;
        return ofColor(floor(r / pas) * pas, floor(g / pas) * pas, floor(b / pas) * pas);
    }
```

<div class="mt-2 text-sm">

- `p` (0 à 1, la souris) paramètre chaque formule — et `ofClamp(…, 0, 255)` **borne avant de reconstruire**
- Le contraste : on écarte (`k > 1`) ou rapproche (`k < 1`) chaque valeur du milieu 128
- La postérisation utilise la division entière du cours 01, **volontairement** : `floor(137 / 32) * 32 = 128` — moins de niveaux, des aplats

</div>

<!--
Les courbes de transfert (entrée → sortie) de chaque formule sont dans le
document, img/11-courbes.png — les montrer si la salle accroche.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Étape `filtre()` (3/3) — les filtres qui passent par HSB

```cpp
    case 8: {   // rotation de teinte : tout se décale sur la roue
        float teinte = fmod(c.getHue() + p * 255, 255);
        return ofColor::fromHsb(teinte, c.getSaturation(), c.getBrightness());
    }
    case 9: {   // color splash : couleur gardée autour d'une teinte cible
        float cible = p * 255;
        float ecart = fabs(c.getHue() - cible);
        if (ecart > 127) ecart = 255 - ecart;   // la roue est circulaire !
        if (ecart < 20) return c;
        return ofColor(luminance);
    }
    default:
        return c;                               // 0 : image d'origine
    }
}
```

<div class="mt-3 text-sm">

<v-clicks>

- **Une ligne en HSB, une horreur en RGB** : c'est pour ces filtres qu'on a fait le cours 09
- `fabs` : la valeur absolue des `float` ; le `if (ecart > 127)` gère la roue circulaire — les teintes 250 et 5 sont voisines
- Lire les axes d'une couleur existante : `getHue()`, `getSaturation()`, `getBrightness()`

</v-clicks>

</div>

<!--
Le color splash : tout passe en gris sauf autour de la teinte visée par la
souris.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Étapes `draw()` et `keyPressed()` — afficher, choisir

```cpp
void ofApp::draw() {
    ofSetColor(255);
    resultat.draw(0, 0);
    ofSetColor(255, 200, 0);
    ofDrawBitmapString("Effet " + ofToString(effet) + " : " + noms[effet]
                       + "   parametre = " + ofToString(parametre, 2), 10, 20);
}

void ofApp::keyPressed(int key) {
    if (key >= '0' && key <= '9') {
        effet = key - '0';           // '0' vaut 48, '1' 49... code → chiffre
    }
}
```

<div class="mt-3 text-sm">

<v-clicks>

- `keyPressed` est appelé automatiquement à chaque touche ; `key` est le **code** du caractère
- `key - '0'` transforme le code en chiffre ; `&&` se lit « et »
- `draw()` ne fait plus qu'afficher : tout le travail est dans `update()`

</v-clicks>

</div>


<!--
Exercices : sépia (chaque canal de sortie mélange les trois d'entrée — la
matrice avant l'heure), échange de canaux, les trois axes HSB en gris, gamma
(prépare 11a), chromakey.
-->
---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# À vous — tes propres filtres

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Échange les canaux : `ofColor(g, b, r)`. Puis isole un canal : `ofColor(r, 0, 0)`
- **2 ·** Affiche la teinte seule en niveaux de gris : `ofColor(c.getHue())` — puis la saturation, puis la luminosité : tu **vois** les trois axes du cours 09
- **3 ·** 🔥 Le **sépia** : chaque canal de sortie mélange les trois canaux d'entrée (les coefficients sont dans le document) — il reviendra en 11f

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11-filtres.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11-filtres.md" download>md</a> · <a href="/ressources/ofApp11.h" download>ofApp11.h</a> · <a href="/ressources/ofApp11.cpp" download>ofApp11.cpp</a> · <a href="/ressources/data/pandaroux.jpg" download>pandaroux.jpg</a></p>

<!--
Gamma et chromakey dans le document pour les rapides. Le sépia est la
première matrice déguisée : y repenser en 11f.
-->


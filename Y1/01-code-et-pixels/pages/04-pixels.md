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
`(0, 0)` en haut à gauche, `y` vers le bas.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/10-pixels.png" alt="Image et zoom pixel avec valeurs RGB" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">Un « bord », un « objet » n'existent pas : juste des cases de couleurs différentes.</p>
</div>

<!--
La porte d'entrée de toute la suite du module. image2.png fait 200 × 200 :
40 000 pixels, de (0,0) à (199,199). Elle va dans bin/data du projet.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 10
---

# Étape 1 — charger, vérifier, afficher

```cpp
// ofApp.h :   ofImage img;

void ofApp::setup() {
    ofSetWindowShape(200, 200);

    bool ok = img.load("image2.png");    // chemin relatif à bin/data !
    if (!ok) {
        ofLogError() << "image2.png introuvable dans bin/data";
    }
}

void ofApp::draw() {
    ofSetColor(255);                     // sans ça : l'image est TEINTÉE
    img.draw(0, 0);
}
```

<div class="mt-2 text-sm">

<v-clicks>

- Les images vont dans **`bin/data`**, jamais à côté du `.cpp`
- `bool` : un type qui ne vaut que `true` ou `false` ; le `!` se lit « non ». **Toujours vérifier** : une image introuvable ne provoque aucune erreur visible, juste une fenêtre vide
- `ofSetColor(255)` avant `img.draw` n'est pas décoratif : sinon l'image prend la dernière couleur utilisée

</v-clicks>

</div>

<!--
ofLogError() << ... : comme std::cout, mais marqué comme erreur dans la console.
Essaie : charger pandaroux.jpg à la place, et adapter la fenêtre
ofSetWindowShape(img.getWidth(), img.getHeight()) APRÈS le chargement.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 10
---

# Étape 2 — lire un pixel, et le montrer

```cpp
    int px = ofClamp(mouseX, 0, img.getWidth() - 1);    // rester dans l'image
    int py = ofClamp(mouseY, 0, img.getHeight() - 1);
    ofColor c = img.getColor(px, py);    // la couleur du pixel (px, py)

    std::string texte = "R=" + ofToString(c.r) + " G=" + ofToString(c.g)
                      + " B=" + ofToString(c.b);
    ofSetColor(255, 200, 0);
    ofDrawBitmapString(texte, 10, 10);

    ofSetColor(c);                       // un carré de la couleur lue
    ofDrawRectangle(mouseX + 10, mouseY + 10, 20, 20);
```

<div class="mt-2 text-sm">

<v-clicks>

- `img.getColor(x, y)` renvoie une `ofColor` (cours 09) qu'on range dans une variable
- `ofClamp(v, min, max)` **borne** : la souris peut sortir de l'image, la coordonnée lue, non — le problème d'indice du cours 04, en deux dimensions. Dernier pixel : `largeur - 1`
- `getColor` lit **l'image chargée**, pas l'écran : le carré jaune est invisible pour elle — une source de données stable, qu'on exploitera au cours 12
- On lit l'image **comme un tableau de nombres** : toute la suite du module tient dans cette phrase

</v-clicks>

</div>

<!--
Essaie : afficher aussi la luminosité (c.r + c.g + c.b) / 3 — division entière
si on veut une virgule — puis faire dépendre la taille du carré de cette
luminosité.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 10
---

# À vous (1/2)

<div class="mt-4 text-base">

**1 · La pipette complète** — en plus du RGB, affiche la **teinte** du pixel (`c.getHue()`), et dessine un second carré de sa couleur « pure » : `ofColor::fromHsb(c.getHue(), 255, 255)`. Compare les deux carrés sur les zones sombres de l'image.

</div>

<div v-click class="mt-5 text-base">

**2 · Le duo teinté** — affiche l'image deux fois côte à côte (fenêtre deux fois plus large), la deuxième teintée en rouge par `ofSetColor(255, 100, 100)` avant son `draw`.

</div>

<!--
Ex 1 : sur une zone sombre, le carré « pur » est vif alors que le pixel est
presque noir — la teinte existe même quand la luminosité est faible. Prépare
les filtres HSB du cours 11.
Ex 2 : ofSetWindowShape(2 * largeur, hauteur) ; second draw à (largeur, 0).
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 10
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · La jauge** — un rectangle horizontal en haut de la fenêtre, dont la **largeur** vaut la luminosité du pixel sous la souris (0 à 255 pixels). L'image devient un instrument de mesure.

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Le scanner** — une boucle `for` sur `x` : pour chaque colonne, lis le pixel `(x, mouseY)` et trace un trait vertical de sa couleur sur toute la hauteur (`ofDrawLine(x, 0, x, 200)`). Monte et descends la souris : tu « scannes » l'image ligne par ligne. C'est déjà, presque, la boucle du cours 11.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/10-image-pixel.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/10-image-pixel.md" download>md</a> · <a href="/ressources/ofApp10.h" download>ofApp10.h</a> · <a href="/ressources/ofApp10.cpp" download>ofApp10.cpp</a> · <a href="/ressources/data/image2.png" download>image2.png</a></p>

<!--
Ex 3 : luminosité = (c.r + c.g + c.b) / 3, ofDrawRectangle(0, 0, lum, 10).
Ex 4 : for (int x = 0; x < img.getWidth(); x++) { ofColor c = img.getColor(x, py);
ofSetColor(c); ofDrawLine(x, 0, x, 200); } — py borné par ofClamp comme dans
l'étape 2. Erreur type : oublier ofSetColor dans la boucle.
-->

---
layout: split
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Cours 11 — Les filtres

Un filtre, c'est une règle : « pour chaque pixel,
remplace sa couleur par f(couleur) ».

Dix règles différentes, **une même machine** qui les
applique. Touches 0 à 9 pour l'effet, souris pour
le paramètre.

<div class="mt-4 text-sm">

Le cours le plus important du module : sa double boucle
reviendra dans tous les suivants.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11-filtres.png" alt="Huit filtres appliqués à la même photo" class="w-full object-contain" />
</div>

<!--
Négatif, gris, luminosité, contraste, seuil, postérisation, rotation de
teinte, color splash. Cliquer pour agrandir et comparer. pandaroux.jpg va
dans bin/data. La machine d'abord, la recette après.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Étape 1 — deux images, jamais une

```cpp
// ofApp.h :  ofImage source;      ofImage resultat;
//            int effet { 0 };     float parametre { 0.5f };

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

- On lit dans la **source**, on écrira dans le **résultat** — on ne modifie jamais la source
- Sinon : changer d'effet partirait d'une image déjà transformée, et deux négatifs ne redonneraient pas l'original
- `allocate` réserve une image vide de la bonne taille, en couleur

</v-clicks>

</div>

<!--
Le .h de la référence porte aussi la liste noms des effets, pour l'affichage.
Essaie : afficher source.getWidth() et getHeight() dans la console — combien
de pixels au total ?
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Étape 2 — la machine : une boucle dans une boucle

```cpp {1-11|13-15}
void ofApp::update() {
    parametre = mouseX / (float)ofGetWidth();      // 0 à gauche, 1 à droite

    for (int y = 0; y < source.getHeight(); y++) {      // chaque ligne...
        for (int x = 0; x < source.getWidth(); x++) {   // ...chaque colonne
            ofColor c = source.getColor(x, y);
            resultat.setColor(x, y, filtre(c, parametre));
        }
    }
    resultat.update();     // envoyer les nouveaux pixels à la carte graphique
}

ofColor ofApp::filtre(ofColor c, float p) {   // la recette PROVISOIRE :
    return c;                                 // le filtre qui ne fait rien
}
```

<div class="mt-2 text-sm">

- Une boucle **dans** une boucle : pour chaque ligne `y`, chaque colonne `x`. Le corps tourne `largeur × hauteur` fois — 774 × 516 = 399 384 fois **par frame**. LE motif de tout le reste du module
- `setColor` écrit un pixel en mémoire ; sans `resultat.update()`, `draw()` affiche l'ancienne version
- `(float)` **convertit** la largeur en nombre à virgule : pas de division entière (cours 01)
- Dans `draw()` : `ofSetColor(255); resultat.draw(0, 0);` — l'image s'affiche, identique, mais chaque pixel est **passé dans ta fonction**

</div>

<!--
Annoncer filtre dans le .h : ofColor filtre(ofColor c, float p);
Essaie : return ofColor(255, 0, 0) — l'image entière devient rouge, la preuve
que la machine visite bien chaque pixel.
Si ça rame : ne recalculer que quand la souris/l'effet a changé (cours 17).
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Étape 3 — l'octet, la petite case qui reboucle

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

<div class="mt-5 text-sm">

<v-clicks>

- La grande case du cours 01 (`float`, 4 octets) serait un luxe : l'écran ne connaît que 256 niveaux par canal — un octet suffit
- Mais la petite case **déborde vite** : un filtre « luminosité + 60 » sur un pixel clair ferait des taches noires
- La règle : `float r = c.r;` — **copier en `float`**, calculer au large, borner avec `ofClamp(valeur, 0, 255)`, reconstruire la couleur

</v-clicks>

</div>

<!--
unsigned char : un char = un octet, unsigned = sans signe, donc 0-255.
Faire compter la salle : 8 bits, 2^8 = 256. Le compteur kilométrique.
Essaie : unsigned char uc = 250; uc = uc + 10; std::cout << (int)uc; — le
(int) force l'affichage en nombre plutôt qu'en caractère.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Étape 4 — les premières recettes : `switch` et `return`

```cpp {1-3|5-16}
ofColor ofApp::filtre(ofColor c, float p) {
    float r = c.r;   float g = c.g;   float b = c.b;    // copier en float AVANT
    float luminance = 0.299f * r + 0.587f * g + 0.114f * b;

    switch (effet) {
    case 1:                              // négatif : chaque canal retourné
        return ofColor(255 - r, 255 - g, 255 - b);
    case 2: {                            // gris : les trois canaux égaux
        float gris = (r + g + b) / 3;
        return ofColor(gris, gris, gris);
    }
    case 3:                              // un seul nombre = un gris
        return ofColor(luminance);
    default:
        return c;                        // 0 : image d'origine
    }
}
```

<div class="mt-2 text-sm">

- La fonction commence par `ofColor`, pas `void` : elle **renvoie** une valeur. `return` livre le résultat et termine — un pixel entre, un pixel sort. Et `c` est une **copie** (cours 07) : la source est intouchable
- `switch (variable)` saute au bon `case` : un `if` à plusieurs branches ; `default` = aucun des cas. Un `case` qui déclare une variable prend des accolades
- Deux gris : la **moyenne**, et la **luminance** — l'œil est plus sensible au vert, d'où les coefficients 0.299 / 0.587 / 0.114

</div>

<!--
Essaie : ajouter un case à soi — l'échange de canaux return ofColor(g, b, r),
puis un canal isolé return ofColor(r, 0, 0).
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Étape 5 — le clavier, et savoir où on en est

```cpp
// ofApp.h :  void keyPressed(int key);

void ofApp::keyPressed(int key) {
    if (key >= '0' && key <= '9') {
        effet = key - '0';           // '0' vaut 48, '1' 49... code → chiffre
    }
}

void ofApp::draw() {
    ofSetColor(255);
    resultat.draw(0, 0);
    ofSetColor(255, 200, 0);
    ofDrawBitmapString("Effet " + ofToString(effet) + "   parametre = "
                       + ofToString(parametre, 2), 10, 20);
}
```

<div class="mt-3 text-sm">

<v-clicks>

- `keyPressed` est appelé automatiquement à chaque touche — comme `update` et `draw`, c'est openFrameworks qui l'appelle
- `key` est le **code** du caractère ; `key - '0'` le transforme en chiffre ; `&&` se lit « et »
- `draw()` ne fait plus qu'afficher : tout le travail est dans `update()`

</v-clicks>

</div>

<!--
Essaie du document : afficher l'effet courant dans la fenêtre — c'est le
draw() ci-dessus. La référence ofApp11 affiche aussi le nom de l'effet
(liste noms dans le .h).
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Étape 6 — les formules paramétrées

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

- `p` (0 à 1, la souris) paramètre chaque formule — et partout la règle de l'étape 3 : calcul en `float`, `ofClamp`, reconstruction
- Le contraste : on écarte (`k > 1`) ou rapproche (`k < 1`) chaque valeur du milieu 128
- La postérisation utilise la division entière du cours 01, **volontairement** : `floor(137 / 32) * 32 = 128` — moins de niveaux, des aplats

</div>

<!--
Le contraste de la référence écrit les trois canaux en entier.
Essaie : inventer sa courbe — le négatif du rouge seul,
return ofColor(255 - r, g, b) — et décrire son effet avant de lancer.
-->

---
layout: split
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Les courbes de transfert

<div class="text-sm">

Pour chaque valeur d'**entrée**, la valeur de **sortie** :

| Effet | Formule |
|---|---|
| Luminosité | `c + k` |
| Contraste | `(c - 128) * k + 128` |
| Seuil | noir si `luminance < s`, blanc sinon |
| Postérisation | `floor(c / pas) * pas` |

<div class="mt-3">

Chaque filtre est une petite formule — et une courbe.

</div>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/11-courbes.png" alt="Courbes de transfert : entrée de 0 à 255 en abscisse, sortie en ordonnée" class="w-full object-contain" />
</div>

<!--
Lire une courbe : la diagonale = l'image d'origine ; au-dessus, plus clair ;
en escalier, la postérisation ; en marche unique, le seuil.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# Étape 7 — les filtres qui passent par HSB

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
```

<div class="mt-3 text-sm">

<v-clicks>

- **Rotation de teinte** : lire la teinte, l'augmenter, boucler avec `fmod`, reconstruire. Une ligne en HSB, pratiquement impossible en RGB — c'est pour ça qu'on a fait le cours 09
- **Color splash** : la couleur n'est gardée qu'autour d'une teinte cible, tout le reste passe en gris
- `fabs` : la valeur absolue des `float` ; le `if (ecart > 127)` gère la roue circulaire — les teintes 250 et 5 sont voisines

</v-clicks>

</div>

<!--
Essaie : afficher la teinte seule en niveaux de gris — return ofColor(c.getHue()) —
puis la saturation, puis la luminosité : on VOIT les trois axes du cours 09 sur
une vraie photo.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# À vous (1/2)

<div class="mt-3 text-base">

**1 · Lire avant de lancer** — que fait ce filtre (même formule sur les trois canaux) ? Décris l'image obtenue, puis vérifie avec le contraste poussé à fond.

```cpp
return ofColor(ofClamp((r - 128) * 8 + 128, 0, 255), ...);
```

</div>

<div v-click class="mt-4 text-base">

**2 · Le sépia** — chaque canal de **sortie** mélange les trois canaux d'**entrée** : `r' = 0.393 r + 0.769 g + 0.189 b`, `g' = 0.349 r + 0.686 g + 0.168 b`, `b' = 0.272 r + 0.534 g + 0.131 b`. Ajoute-le comme effet. Retiens sa forme — neuf coefficients — elle a un nom qu'on découvrira dans le bloc couleur avancée : une matrice.

</div>

<!--
Ex 1 : un contraste × 8 — presque un seuil par canal : chaque canal part à 0
ou 255 sauf tout près de 128. L'image devient une affiche à huit couleurs
(les combinaisons de 0/255 sur trois canaux).
Ex 2 : neuf coefficients, trois ofClamp — la première matrice déguisée, y
repenser en 11f.
-->

---
layout: default
breadcrumb: 4 — L'image et ses pixels / Cours 11
---

# À vous (2/2)

<div class="mt-4 text-base">

**3 · Le gamma** — `255 * pow(r / 255.0f, k)` sur chaque canal, avec `k` allant de 0.3 à 3 selon la souris. Compare avec la luminosité (case 4) : lequel des deux préserve les noirs ?

</div>

<div v-click class="mt-5 text-base">

**4 ·** 🔥 **Le chromakey** — charge une deuxième image de même taille ; si la teinte du pixel est proche du vert, renvoie le pixel de l'autre image à la place. Le fond vert du cinéma, en une dizaine de lignes.

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/11-filtres.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/11-filtres.md" download>md</a> · <a href="/ressources/ofApp11.h" download>ofApp11.h</a> · <a href="/ressources/ofApp11.cpp" download>ofApp11.cpp</a> · <a href="/ressources/data/pandaroux.jpg" download>pandaroux.jpg</a></p>

<!--
Ex 3 : k = 0.3f + p * 2.7f ; le gamma préserve les noirs (0 reste 0 quelle que
soit la puissance), la luminosité les remonte en gris. Prépare 11a.
Ex 4 : la deuxième image se lit avec son propre getColor(x, y) — mais filtre()
ne reçoit pas x, y : soit lui ajouter deux paramètres, soit faire le test dans
la boucle d'update. La teinte du vert ≈ 85 sur 255 ; écart circulaire comme
le color splash.
-->

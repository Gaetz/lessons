---
layout: section
breadcrumb: 8 — Le projet final
---

# Le projet final

Tout le module dans une seule image

---
layout: split
breadcrumb: 8 — Le projet final / Cours 18
---

# Cours 18 — Peinture par particules

Six cents particules se promènent ; chacune dépose,
à chaque frame, un petit cercle de la couleur du pixel
sous elle. **On n'efface jamais** : l'image apparaît
toute seule, comme une peinture qui se fait.

<div class="mt-4 text-sm">

Le projet qui **synthétise tout le module**, construit
en six étapes. Les deux premières suffisent pour un
résultat ; les étapes 3 à 6 s'activent aux touches 3-6,
pour voir ce que chacune apporte.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/18-peinture.png" alt="La peinture terminée, touches de couleur enroulées" class="w-full object-contain" />
</div>

<!--
Espace efface, i change d'image, c montre les contours. Les images
pandaroux.jpg, redpanda.jpg, chibi-redpanda.jpg vont dans bin/data.
Chaque étape rappelle un cours : les nommer au passage.
-->

---
layout: default
breadcrumb: 8 — Le projet final / Cours 18
---

# Étape 1 — des particules qui marchent

```cpp
// ofApp18.h :  std::vector<float> posX, posY, angle;    // trois listes parallèles (07)
//              int nbParticules { 600 };   float vitesse { 80 };   // pixels par seconde

void ofApp::recommencer() {                        // réparties au hasard (03, 04)
    posX.clear();  posY.clear();  angle.clear();
    for (int i = 0; i < nbParticules; i++) {
        posX.push_back(ofRandom(0, source.getWidth()));
        posY.push_back(ofRandom(0, source.getHeight()));
        angle.push_back(ofRandom(0, TWO_PI));
    }
}

// update(), pour chaque particule i :
    posX[i] += cos(angle[i]) * v * dt;             // la direction en cos / sin (13),
    posY[i] += sin(angle[i]) * v * dt;             // la vitesse en pixels par seconde (06)
```

<div class="mt-2 text-sm">

<v-clicks>

- Une particule, c'est une **position** et une **direction** : trois listes remplies au hasard
- L'angle donne la direction, `cos` et `sin` la transforment en déplacement horizontal et vertical
- Une particule qui sort de l'image **réapparaît n'importe où** : les traits restent répartis partout

</v-clicks>

</div>

<!--
Sortie : if (posX[i] < 0 || posX[i] >= w || ...) → nouvelle position et
nouvel angle au hasard. Essaie dès cette étape (petits cercles blancs pour
les voir) : 100 particules lentes, 2000 rapides.
-->

---
layout: default
breadcrumb: 8 — Le projet final / Cours 18
---

# Étape 2 — une toile qui ne s'efface pas

```cpp
// chargerImage() :  toile.allocate(w, h, GL_RGB);     // ofFbo : la SEULE nouveauté du projet

void ofApp::draw() {
    toile.begin();                                 // tout va dans la toile
    if (effacer) { ofClear(0); effacer = false; }  // le SEUL effacement : un drapeau (17)

    for (int i = 0; i < nbParticules; i++) {
        int px = ofClamp(posX[i], 0, w - 1);
        int py = ofClamp(posY[i], 0, h - 1);
        ofColor c = source.getColor(px, py);       // la couleur sous la particule (10)
        ofSetColor(c, 180);
        ofDrawCircle(posX[i], posY[i], 3);
    }
    toile.end();
    toile.draw(0, 0);                              // puis on affiche la toile
}
```

<div class="mt-2 text-sm">

<v-clicks>

- Depuis le cours 05, chaque frame repart d'un fond propre. Ici on veut **l'inverse** : un `ofFbo` est une image **dans laquelle on peut dessiner**
- Entre `begin()` et `end()`, les ordres de dessin vont dans la toile ; ce qui y est dessiné **y reste**, frame après frame
- Dès cette étape, l'image émerge du noir

</v-clicks>

</div>

<!--
img/18-peinture-debut.png : après une seconde et demie, quelques traits
épars. ofSetBackgroundAuto(false) existe mais se comporte différemment
selon les plateformes ; le FBO est la méthode fiable. Essaie : laisser
tourner deux minutes ; puis implémenter l'effacement (espace → drapeau
effacer → ofClear(0) dans la toile) et regarder l'image renaître.
-->

---
layout: default
breadcrumb: 8 — Le projet final / Cours 18
---

# Étape 3 — un champ de direction

```cpp
    if (champDirection) {                          // touche 3
        angle[i] = (sin(x / 80.0f) + cos(y / 80.0f)) * PI + t * 0.1f;
    }
```

<div class="mt-5 text-base">

<v-clicks>

- Au lieu d'une direction au hasard, la direction **dépend de la position** : le déphasage du cours 15, appliqué à un angle
- Deux particules voisines prennent presque le même angle : des traits voisins vont dans le même sens et **s'enroulent ensemble**
- Le `t * 0.1f` fait **dériver lentement** le champ, pour que les mêmes zones ne soient pas repassées éternellement
- Touche 3 : les traits redeviennent des lignes droites au hasard. Réactive : ils tourbillonnent

</v-clicks>

</div>

<!--
Essaie : changer le 80.0f (l'échelle du champ) — 20 : des tourbillons
serrés ; 300 : de grandes vagues lentes.
-->

---
layout: split
breadcrumb: 8 — Le projet final / Cours 18
---

# Étape 4 — des traits qui respectent les formes

```cpp
// calculerContours() : le noyau contours du 17,
// sur la luminance, UNE fois au chargement

// update() :
    float bord = contours.getColor(px, py).r / 255.0f;
    v = vitesse * (1 - 0.7f * bord);     // 0 : plat, 1 : bord net
    angle[i] += bord * ofRandom(-3, 3) * dt;

// draw() :
    taille = 6 - 5 * bord;
```

<div class="mt-3 text-sm">

<v-clicks>

- Sur un bord, la particule **ralentit et dévie** : ses traits se brisent en petites touches sur les détails, restent longs dans les aplats
- Grosses touches dans les aplats, fines sur les bords : **un peintre fait la même chose**

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/18-contours.png" alt="Les contours de l'image, calculés une fois au démarrage" class="w-full object-contain" />
</div>

<!--
Les contours : le calcul le plus lourd, fait une seule fois dans
chargerImage (le drapeau du 17, version « au chargement »). Touche c pour
les montrer. Essaie : le 0.7f dose le ralentissement sur les bords — le
pousser à 0.95, ou le couper à 0.
-->

---
layout: split
breadcrumb: 8 — Le projet final / Cours 18
---

# Étape 5 — une couleur vivante

```cpp
    if (couleurVivante) {                // touche 5
        float decalage = (i % 21) - 10;  // -10 à +10 selon i
        float teinte = fmod(c.getHue() + decalage + 255, 255);
        c = ofColor::fromHsb(teinte, c.getSaturation(),
                             c.getBrightness());
        taille = taille * (0.5f + c.getBrightness() / 255.0f);
    }
    ofSetColor(c, 180);
```

<div class="mt-3 text-sm">

<v-clicks>

- Chaque particule **décale un peu la teinte** du pixel qu'elle lit (cours 09, 11) : un aplat de vert uniforme devient un mélange de verts voisins, comme des touches de pinceau
- Les zones claires reçoivent des touches plus larges
- `180` : une légère transparence, les passages successifs se **mélangent** au lieu de se recouvrir

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/18-peinture-detail.png" alt="Détail agrandi : grosses touches dans le feuillage, petites touches sur le museau" class="w-full object-contain" />
</div>

<!--
Essaie : élargir le décalage de teinte ((i % 21) * 3 - 30) — à partir de
quand la peinture devient-elle fauviste ?
-->

---
layout: default
breadcrumb: 8 — Le projet final / Cours 18
---

# Étape 6 — la souris

```cpp
    if (souris) {                                  // touche 6
        float d = ofDist(mouseX, mouseY, x, y);
        if (d < 100 && d > 0) {
            angle[i] = atan2(y - mouseY, x - mouseX);
            v = vitesse * 3;
        }
    }
```

<div class="mt-5 text-base">

<v-clicks>

- La distance du cours 12 : dans un rayon de 100 pixels, la particule **fuit**
- `atan2(dy, dx)` donne l'angle du vecteur `(dx, dy)` : **l'inverse de `cos` / `sin`** (cours 16). Ici le vecteur va de la souris vers la particule
- Elle prend cette direction et accélère : passer la souris sur la toile **repousse la peinture**

</v-clicks>

</div>

<!--
Essaie : inverser le vecteur (atan2(mouseY - y, mouseX - x)) — la souris
ATTIRE les particules. Laquelle des deux versions fait le plus « pinceau » ?
-->

---
layout: default
breadcrumb: 8 — Le projet final / Cours 18
---

# Le clavier — et ce que le projet récapitule

```cpp
    if (key == '3') champDirection = !champDirection;        // ! inverse un bool (10)
    if (key == 'i') {
        imageCourante = (imageCourante + 1) % images.size();  // % : retour à 0 (13)
        chargerImage(images[imageCourante]);
    }
```

<div class="mt-3 text-sm">

| Étape | Cours |
|---|---|
| listes de particules, hasard | 03, 04, 07 |
| déplacement par angle et `dt` | 06, 13 |
| lire la couleur sous la particule | 10 |
| champ de direction, déphasage | 15 |
| contours calculés une fois, drapeau | 17 |
| teinte et luminosité | 09, 11 |
| distance à la souris, `atan2` | 12, 16 |
| toile persistante | `ofFbo`, la seule nouveauté |

</div>

<!--
Faire l'inventaire à voix haute avec la salle, ligne par ligne. Une ligne
par option au clavier ; chargerImage recharge la source, adapte la fenêtre,
recalcule les contours et relance les particules.
-->

---
layout: default
breadcrumb: 8 — Le projet final / Cours 18
---

# À vous — pousser la peinture

<div class="mt-4 text-base">

<v-clicks>

- **1 ·** Un **trait** au lieu d'un cercle : garder la position précédente et tracer `ofDrawLine`
- **2 ·** **Ta propre image** dans `bin/data` et dans la liste `images`
- **3 ·** La **webcam** à la place de la photo (`ofVideoGrabber`) : la peinture suit ce qui bouge
- **4 ·** **Sauvegarder la toile** : `toile.readToPixels(pixels); ofSaveImage(pixels, "peinture.png");`
- **5 ·** 🔥 Des traits qui **suivent vraiment les formes** : les deux noyaux de Sobel (cours 17) donnent la direction du contour, `atan2(sobelY, sobelX)`, et la particule prend cet angle plus `PI / 2`

</v-clicks>

</div>

<div v-click class="mt-5 text-sm op-75">
<b>🔥</b> = exercice avancé.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/18-peinture-particules.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/18-peinture-particules.md" download>md</a> · <a href="/ressources/ofApp18.h" download>ofApp18.h</a> · <a href="/ressources/ofApp18.cpp" download>ofApp18.cpp</a> · images : <a href="/ressources/data/pandaroux.jpg" download>pandaroux</a>, <a href="/ressources/data/redpanda.jpg" download>redpanda</a>, <a href="/ressources/data/chibi-redpanda.jpg" download>chibi</a></p>

<!--
N°1 : deux listes de plus (prevX, prevY), mises à jour après le déplacement ;
attention au saut quand la particule réapparaît (ne pas tracer ce tour-là).
N°4 : ofPixels pixels; déclarée avant. N°5 : Sobel horizontal et vertical
en float, l'angle du contour est atan2(sobelY, sobelX), + PI / 2 pour
longer le bord au lieu de le traverser. La webcam est l'effet waouh de fin
de module si une caméra traîne dans la salle.
-->

---
layout: statement
---

# Vous savez maintenant lire une image comme un tableau de nombres

Et le transformer en ce que vous voulez.

<!--
Clôture du module. Le pont vers la suite de l'année : ces doubles boucles par
pixel, c'est exactement ce qu'un shader fait en parallèle sur le GPU — le
cold open de la rentrée n'est plus très loin.
-->

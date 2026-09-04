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
en six étapes — les étapes 3 à 6 s'activent aux
touches 3-6, pour voir ce que chacune apporte.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/18-peinture.png" alt="La peinture terminée, touches de couleur enroulées" class="w-full object-contain" />
</div>

<!--
Espace efface, i change d'image, c montre les contours. Les deux premières
étapes suffisent pour un résultat ; l'image émerge du noir en ~20 secondes.
-->

---
layout: default
breadcrumb: 8 — Le projet final / Cours 18
---

# La mise en place — particules et toile

```cpp
// ofApp18.h — une particule = une position et une direction
std::vector<float> posX, posY, angle;          // trois listes parallèles (07)
ofFbo   toile;                                 // ce qui a déjà été peint
ofImage contours;                              // 0 = plat, 255 = bord net

// recommencer() — étape 1 : réparties au hasard (03, 04)
for (int i = 0; i < nbParticules; i++) {
    posX.push_back(ofRandom(0, source.getWidth()));
    posY.push_back(ofRandom(0, source.getHeight()));
    angle.push_back(ofRandom(0, TWO_PI));
}

// chargerImage() — la toile : la SEULE nouveauté du projet
toile.allocate(w, h, GL_RGB);
```

<div class="mt-3 text-sm">

<v-clicks>

- L'`ofFbo` est une image **dans laquelle on peut dessiner** : tout ce qui est dessiné entre `begin()` et `end()` s'y accumule, frame après frame
- `calculerContours()` : exactement le noyau contours du cours 17, sur la luminance, calculé **une fois** au chargement (le calcul le plus lourd)
- `chargerImage()` recharge la source, adapte la fenêtre, recalcule les contours, relance les particules

</v-clicks>

</div>

<!--
Depuis le cours 05, chaque frame repart d'un fond propre — ici on veut
l'inverse. ofSetBackgroundAuto(false) existe mais se comporte différemment
selon les plateformes ; le FBO est la méthode fiable.
-->

---
layout: default
breadcrumb: 8 — Le projet final / Cours 18
---

# Étape `update()` — marcher, s'enrouler, ralentir, fuir

```cpp {1-5|7-12|14-19}
    // étape 3 — champ de direction : l'angle dépend de la POSITION
    // (le déphasage du cours 15) ; t fait dériver lentement le champ
    if (champDirection) {
        angle[i] = (sin(x / 80.0f) + cos(y / 80.0f)) * PI + t * 0.1f;
    }

    // étape 4 — sur un bord (contours de 17), ralentir et dévier :
    // les traits se brisent en touches sur les détails
    if (suivreFormes) {
        float bord = contours.getColor(px, py).r / 255.0f;
        v = vitesse * (1 - 0.7f * bord);
        angle[i] += bord * ofRandom(-3, 3) * dt;
    }

    // étape 6 — la souris repousse : atan2 = l'inverse de cos/sin (16)
    if (souris && ofDist(mouseX, mouseY, x, y) < 100) {
        angle[i] = atan2(y - mouseY, x - mouseX);
        v = vitesse * 3;
    }

    posX[i] += cos(angle[i]) * v * dt;        // le déplacement : 06 + 13
    posY[i] += sin(angle[i]) * v * dt;
```

<div class="mt-2 text-sm">

- Deux particules voisines prennent presque le même angle : des traits qui **s'enroulent ensemble**
- Une particule qui sort réapparaît n'importe où : les traits restent répartis partout
- Chaque `if` est une étape **débrayable** au clavier — c'est la démonstration en direct de ce que chaque idée apporte

</div>

<!--
Trois clics = les trois étapes dans le code. ofDist : la distance du cours 12.
-->

---
layout: default
breadcrumb: 8 — Le projet final / Cours 18
---

# Étape `draw()` — peindre dans la toile

```cpp
    toile.begin();                              // tout va dans la toile
    if (effacer) { ofClear(0); effacer = false; }   // le SEUL effacement

    for (int i = 0; i < nbParticules; i++) {
        ofColor c = source.getColor(px, py);    // la couleur sous la particule (10)
        float taille = 3;
        if (suivreFormes) {                     // touches fines sur les bords
            float bord = contours.getColor(px, py).r / 255.0f;
            taille = 6 - 5 * bord;
        }
        if (couleurVivante) {                   // étape 5 : teinte décalée (09)
            float decalage = (i % 21) - 10;
            float teinte = fmod(c.getHue() + decalage + 255, 255);
            c = ofColor::fromHsb(teinte, c.getSaturation(), c.getBrightness());
            taille = taille * (0.5f + c.getBrightness() / 255.0f);
        }
        ofSetColor(c, 180);                     // transparence : les passages se mélangent
        ofDrawCircle(posX[i], posY[i], taille);
    }
    toile.end();
    toile.draw(0, 0);                           // puis on affiche la toile
```

<div class="mt-2 text-sm">

- Un aplat de vert uniforme devient un **mélange de verts voisins**, comme des touches de pinceau — chaque particule décale la teinte selon son numéro (`i % 21`)
- Grosses touches dans les aplats, fines sur les bords : **un peintre fait la même chose**
- `keyPressed` : `!` inverse un `bool` (une ligne par option), `%` fait défiler les images en boucle

</div>


<!--
Faire l'inventaire à voix haute avec la salle : particules (03, 04, 07),
déplacement (06, 13), couleur sous la particule (10), champ (15), contours
(17), teinte (09, 11), souris (12, 16), drapeaux et clavier (11, 17).
Pour aller plus loin (document) : traits au lieu de cercles, Sobel pour
suivre vraiment les contours (atan2 + PI/2), la webcam, sauvegarder la toile.
-->

---
layout: default
breadcrumb: 8 — Le projet final / Cours 18
---

# À vous — pousser la peinture

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** **Ta propre image** dans `bin/data` et dans la liste `images`
- **2 ·** Un **trait** au lieu d'un cercle : garder la position précédente et tracer `ofDrawLine`
- **3 ·** 🔥 Des traits qui **suivent vraiment les formes** : les deux noyaux de Sobel (cours 17) donnent la direction du contour — `atan2(sobelY, sobelX)`, plus `PI / 2`

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · webcam et sauvegarde de la toile : dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/18-peinture-particules.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/18-peinture-particules.md" download>md</a> · <a href="/ressources/ofApp18.h" download>ofApp18.h</a> · <a href="/ressources/ofApp18.cpp" download>ofApp18.cpp</a> · images : <a href="/ressources/data/redpanda.jpg" download>redpanda</a>, <a href="/ressources/data/chibi-redpanda.jpg" download>chibi</a></p>

<!--
La webcam (ofVideoGrabber) est l'effet waouh de fin de module si une caméra
traîne dans la salle. Sauvegarde : readToPixels + ofSaveImage.
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

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

Un **noyau** = une grille 3 × 3 de poids.
Flou, netteté, contours, relief : **un seul code**,
seule la grille de neuf nombres change.

</div>

::right::

<div>
<ZoomImage src="/ressources/cours/img/17-convolution.png" alt="Flou, gaussien, netteté, contours, relief" class="w-full object-contain" />
</div>

<!--
Le schéma img/17-noyau.png : les 9 pixels multipliés case par case par le
noyau, puis additionnés — une moyenne pondérée des voisins.
-->

---
layout: default
breadcrumb: 6 — La convolution / Cours 17
---

# L'image en mémoire — un ruban de lignes

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
    <div class="text-center text-xs op-60 mt-2">la même image en mémoire : les lignes bout à bout</div>
  </div>
</div>

<div class="mt-7 text-sm">

<v-clicks>

- La mémoire est une **rangée de cases** (cours 01) : une image s'y range **ligne après ligne**, bout à bout
- Le pixel `(x, y)` est donc à l'indice **`y * w + x`** : sauter `y` lignes complètes, puis avancer de `x` — le ★ : 1 × 4 + 2 = **6**
- Le même calcul range **n'importe quelle grille dans une liste** : le noyau 3 × 3 de la diapo suivante, et il resservira en 11d, 11f et 11g

</v-clicks>

</div>

<!--
C'est ce que fait getColor(x, y) sous le capot — et l'exercice 5 du document
(getPixels) le fait à la main pour la vitesse : le rouge du pixel (x, y) est
à l'indice (y * w + x) * 3, comme le ruban x y x y de la struct du cours 07.
-->

---
layout: default
breadcrumb: 6 — La convolution / Cours 17
---

# Étape `appliquerNoyau()` — quatre boucles imbriquées

```cpp
void ofApp::appliquerNoyau(std::vector<float> noyau, float biais) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {              // tous les pixels (cours 11)
            float r = biais, g = biais, b = biais;

            for (int dy = -1; dy <= 1; dy++) {     // les neuf voisins
                for (int dx = -1; dx <= 1; dx++) {
                    int px = ofClamp(x + dx, 0, w - 1);      // le bord remplace
                    int py = ofClamp(y + dy, 0, h - 1);      // le voisin manquant
                    ofColor v = source.getColor(px, py);
                    float poids = noyau[(dy + 1) * 3 + (dx + 1)];
                    r += v.r * poids;  g += v.g * poids;  b += v.b * poids;
                }
            }
            resultat.setColor(x, y, ofColor(ofClamp(r, 0, 255), /* g, b */));
        }
    }
    resultat.update();
}
```

<div class="mt-2 text-sm">

- `dx` et `dy` valent −1, 0 ou 1 : les neuf positions autour de `(x, y)`
- L'indice `(dy + 1) * 3 + (dx + 1)` : le **ruban de la diapo précédente**, appliqué à la grille 3 × 3 du noyau
- Sommes en `float`, `ofClamp` final : les poids négatifs sortent facilement de 0-255 ; le **biais** recentre un résultat signé (le relief : +128)

</div>

<!--
Le pixel (0,0) n'a pas de voisin en (-1,-1) : trois solutions classiques
(ignorer, noir, réutiliser le bord) — on prend la troisième, sans liseré noir.
-->

---
layout: default
breadcrumb: 6 — La convolution / Cours 17
---

# Étape `calculer()` — cinq noyaux, et le drapeau

```cpp
case 1: appliquerNoyau({ 1/9.0f, 1/9.0f, 1/9.0f,       // flou boîte : la moyenne
                         1/9.0f, 1/9.0f, 1/9.0f,
                         1/9.0f, 1/9.0f, 1/9.0f }, 0);  break;
case 3: appliquerNoyau({  0, -1,  0,                    // netteté (somme = 1)
                         -1,  5, -1,
                          0, -1,  0 }, 0);  break;
case 4: appliquerNoyau({ -1, -1, -1,                    // contours (somme = 0)
                         -1,  8, -1,
                         -1, -1, -1 }, 0);  break;
case 5: appliquerNoyau({ -1, 0, 0,                      // relief : deux coins
                          0, 0, 0,                      // opposés, biais 128
                          0, 0, 1 }, 128);  break;

// update() : if (aRecalculer) { calculer(); aRecalculer = false; }
```

<div class="mt-2 text-sm">

- La liste `{ -1, 0, 0, ... }` créée **sur place**, écrite sur trois lignes : elle ressemble à la grille qu'elle représente
- Somme des poids = 1 : luminosité conservée. Somme = 0 : les zones plates deviennent noires — seules les différences restent
- 400 000 pixels × 9 voisins = 3,6 millions de lectures : trop pour 60 fps. Un **drapeau** `bool`, levé par `keyPressed`, ne recalcule que quand l'effet change — le motif de tout ce qui coûte cher

</div>


<!--
Le flou gaussien : 1 2 1 / 2 4 2 / 1 2 1 sur 16 — le centre pèse plus, flou
plus doux. Exercices : dessin au crayon (négatif des contours), double flou
(copier resultat dans source entre les passes), 5×5, Sobel (LE détecteur de
contours), lecture directe de getPixels() pour la vitesse.
-->
---
layout: default
breadcrumb: 6 — La convolution / Cours 17
---

# À vous — tes propres noyaux

<div class="mt-6 text-base">

<v-clicks>

- **1 ·** Le **dessin au crayon** : le négatif des contours (reprends le négatif du cours 11 sur le résultat)
- **2 ·** Applique **deux fois le flou** — il faut copier `resultat` dans `source` entre les passes
- **3 ·** 🔥 **Sobel** : le noyau horizontal `-1 -2 -1 / 0 0 0 / 1 2 1`, puis le vertical, puis la racine de la somme des carrés — un bien meilleur détecteur de contours

</v-clicks>

</div>

<div v-click class="mt-6 text-sm op-75">
<b>🔥</b> = exercice avancé · le reste des exercices est dans le document.
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/17-convolution.pdf" download>cours complet (PDF)</a> · <a href="/ressources/cours/17-convolution.md" download>md</a> · <a href="/ressources/ofApp17.h" download>ofApp17.h</a> · <a href="/ressources/ofApp17.cpp" download>ofApp17.cpp</a></p>

<!--
Sobel resservira au 18 (suivre les formes). Ex 3 (flou 5×5) et 5 (lecture
rapide par getPixels) dans le document pour les rapides.
-->


# Tech Art 1 — conversion Processing (Python) → openFrameworks

19 fichiers de référence (00 à 18), plus le bloc « couleur avancée » (09a sans code, 11a à 11g), un par notion, dans l'ordre pédagogique. Chaque paire `ofAppNN.h` / `ofAppNN.cpp` déclare la classe `ofApp` : un seul exemple est compilable à la fois dans un projet.

**Utilisation** : copier la paire dans `src/`, remplacer `#include "ofApp.h"` par `#include "ofAppNN.h"` dans `main.cpp`. Les images vont dans `bin/data/`.

**Cours écrits** : un document Markdown par leçon dans [`cours/`](cours/README.md), avec illustrations, pour des débutants qui découvrent le C++. Pour installer les outils (Visual Studio 2026, openFrameworks) : [Préparation de l'environnement de développement](cours/00-environnement.md).

## Progression

| # | Notion | Source | Ce qui est nouveau |
|---|---|---|---|
| 00 | Premier contact : tête qui suit la souris | 2024-2025/sketch_01_funny_face | rien n'est expliqué : on modifie des nombres et on relance |
| 01 | Variables et opérations | Cours 1/01_First_operations | types `int` / `float`, division entière, diamètre → rayon |
| 02 | Boucle `for` | Cours 1/02_For_loop_circle | syntaxe C++ du `for`, fill/stroke en deux passes |
| 03 | Aléatoire, boucle à pas | 2022-2023/rendu02_5 | `ofRandom`, `i += 5`, `ofSeedRandom` (dessin stable en boucle) |
| 04 | Listes | Cours 2/04_First_lists + 2024-2025/sketch_01a_list | `std::vector`, `push_back`, `[i]`, `size()`, `std::cout`, `std::string` |
| 05 | Cycle setup / update / draw, souris | Cours 1/03_Circle_follows_mouse | `update()` vs `draw()`, `mouseX`, membres de classe — relit 00 avec les mots |
| 06 | Animation, vitesse, rebond | 2022-2023/rendu01_pde | delta time, `if`, vitesses en px/s, `cos` pour animer (explique le fond de 00) |
| 07 | Traînée (historique) | Cours 3/sketch_05_First_special_fx | fonction de dessin à paramètres (explique `funnyFace` de 00), `vector` comme file bornée, `erase(begin())` |
| 08 | Traînée évoluée | 2024-2025/sketch_02_trail | paramètres multiples, alpha et taille selon l'indice |
| 09 | Couleur : RGB, HSB, dégradés | nouveau | `ofColor::fromHsb` (0–255 partout), teinte selon le temps et l'indice (relit 08), `getLerped`, `fmod` |
| 09a | La couleur dans le jeu vidéo et le cinéma | nouveau, **sans code** | pipeline scène → écran → œil, gamut et écrans (sRGB, P3, Rec.2020), profondeur de bits et banding ; annonce 11a–11g |
| 10 | Image et pixel | 2022-2023/rendu02 | `ofImage`, `bin/data`, `getColor`, `ofDrawBitmapString` |
| 11 | Filtres par pixel | nouveau | double boucle sur tous les pixels, image source / résultat, `setColor` + `update()`, débordement des `unsigned char`, `keyPressed`, `switch` ; négatif, gris, luminosité, contraste, seuil, postérisation, puis rotation de teinte et color splash via HSB |
| 11a | Gamma et espace linéaire | nouveau | courbe sRGB, `pow`, décoder / calculer / réencoder, table de 256 entrées, recalcul sur changement |
| 11b | HDR, exposition et tone mapping | nouveau | stops, clamp / Reinhard / ACES, tracer une courbe, `switch` dans une fonction qui renvoie un `float` |
| 11c | LUT et étalonnage | nouveau | trois `vector<int>` de 256, construction en 256 tours, looks cinéma, force par interpolation |
| 11d | YCbCr et compression | nouveau | trois `vector<float>` de `w*h`, moyenne par blocs, sous-échantillonnage 4:2:0 |
| 11e | Espaces perceptuels : OKLab | nouveau, sans image | `struct Lab`, `cbrt`, dégradés RGB / HSB / OKLab, palette OKLCH à clarté constante |
| 11f | Daltonisme et accessibilité | nouveau | matrice 3×3 en linéaire, sévérité, test d'interface couleur seule / couleur + motif |
| 11g | Palette indexée et dithering | nouveau | plus proche par distance RGB², Bayer 4×4, Floyd-Steinberg, palettes Game Boy / CGA / PICO-8 |
| 12 | Pointillisme, distance | 2022-2023/rendu04 (+ variante sketch_03_image en commentaire) | Pythagore, proportion, effet local autour de la souris |
| 13 | Trigo : cercle de cercles | 2024-2025/sketch_04_circles (+ variantes 04a et TrigoBlend en commentaire) | `cos`/`sin`, radians, `%`, `ofTranslate`, `ofEnableBlendMode` ; variante teinte = angle |
| 14 | Filtres géométriques | nouveau | lecture « à l'envers » `resultat(x, y) = source(f(x, y))`, bornage ; miroir, rotation 180, pixelisation, vagues, glitch |
| 15 | Trigo : grille en rotation | Cours 5/TrigoFlag | centre de case, déphasage |
| 16 | Trigo : fleurs polaires | Cours 5/TrigoFlower | polaire → cartésien, `ofBeginShape`/`ofVertex`/`ofEndShape` ; exercice loupe et tourbillon sur image |
| 17 | Convolution | nouveau | noyau 3×3, somme pondérée des voisins, bords, recalcul à la demande ; flou boîte, gaussien, netteté, contours, relief |
| 18 | Projet final : peinture par particules | nouveau | synthèse en six étapes activables au clavier ; `ofFbo` comme toile persistante (seule nouveauté), `atan2`, contours calculés une fois pour piloter les traits |

Ordre justifié : 00 est une création guidée avant toute théorie (c'était déjà le sketch 01 de la version 2024-2025) ; 01–04 sans état entre frames (statique + console) ; 05–06 introduisent le temps et relisent 00 avec le vocabulaire acquis ; 07–08 les fonctions et le `vector` en usage réel ; 09 la couleur comme valeur, juste avant les images, parce que HSB n'a pas besoin de pixels et que 08 bricole déjà des couleurs avec trois cosinus ; 09a est une fiche sans code sur le trajet de la couleur, lue après 09 ; 10–11 les ressources externes et la transformation pixel par pixel (la double boucle est introduite en 11, ce qui allège 12) ; 11a–11g forment un bloc optionnel « couleur avancée » qui réutilise la machine du 11 (11a est prérequis de 11b, 11e, 11f ; les autres sont indépendantes) ; 12–16 alternent trigonométrie et image : 14 (géométrie) demande `sin` et le temps de 13, la loupe et le tourbillon attendent les coordonnées polaires de 16 ; 17 est le cours le plus lourd et ouvre vers les shaders ; 18 est le projet final : des particules peignent l'image, chaque étape rappelle un cours et produit un rendu montrable, ce qui permet de noter sur la progression atteinte. Les sketches "Cours 5" étaient numérotés après les images dans le Drive ; ils restent en fin de parcours.

## Écartés

- `sketch_02a_blqck_trail` — identique à `sketch_02_trail`, fond blanc
- `rendu03` (2022-2023) — traînée avec bonhomme et dégradé, entièrement couverte par 07 + 08
- `sketch_04a_circles`, `TrigoBlend` — variantes de 13, mentionnées en commentaire dans `ofApp13.cpp`
- `sketch_03_image` — variante de 12, mentionnée en commentaire dans `ofApp12.cpp`
- `Trail Felicien SABY.txt` — rendu d'étudiant
- `TechArtLille2024.7z` — copie exacte de « Cours 2024-2025 »

Correction apportée : `TrigoFlower.pyde` utilisait `flower_index` (non défini) au lieu de `f_index` dans `draw()`.

## Choix de conversion

- **Delta time partout.** Les sketches comptaient en frames (`t = t + 1`, `pos_x + 5`). Toutes les vitesses sont converties en unités par seconde avec `ofGetLastFrameTime()` ou `ofGetElapsedTimef()`, constantes ajustées pour retrouver la vitesse visuelle d'origine à 60 fps. Le fichier 06 introduit la notion ; 00 l'utilise sans l'expliquer.
- **`update()` / `draw()` séparés** dès le fichier 05. Aucun appel de dessin dans `update()`, aucune mutation dans `draw()`.
- **Globales → membres de classe.** Chaque `global x, y` de Python devient une déclaration dans le `.h`.
- **Deux `vector` parallèles** pour les traînées (07, 08), fidèle aux sketches. `glm::vec2` est signalé en commentaire comme étape suivante.
- **`std::cout`** plutôt que `ofLog` pour le fichier 04, afin d'enseigner le C++ standard ; l'équivalent OF est indiqué.
- **`ofBeginShape`** plutôt que `ofPolyline` en 16 pour rester proche de `beginShape`/`vertex` ; `ofPolyline`/`ofPath` signalés.
- **Fichiers sans sketch d'origine** (09, 11, 14, 17) : écrits directement pour openFrameworks. Les filtres lisent `source` et écrivent `resultat`, deux `ofImage` distinctes, avec `getColor`/`setColor` plutôt que le tableau de pixels, pour rester lisibles ; l'accès direct est donné en exercice de 17. L'effet se choisit au clavier (touches `0` à `9`) et le paramètre à la souris ; 17 ne recalcule que sur changement d'effet.

## Aide-mémoire Processing (Python) → openFrameworks

| Processing | openFrameworks | Attention |
|---|---|---|
| `size(w, h)` | `ofSetWindowShape(w, h)` dans `setup()` | |
| `background(r, g, b)` | `ofBackground(r, g, b)` | à appeler dans `draw()` |
| `fill(r, g, b, a)` | `ofFill(); ofSetColor(r, g, b, a)` | |
| `stroke(r, g, b)` | `ofNoFill(); ofSetColor(...)` puis redessiner | **pas de fill+stroke en un appel** : deux passes |
| `noStroke()` | ne pas faire la deuxième passe | |
| `circle(x, y, d)` | `ofDrawCircle(x, y, d / 2)` | **diamètre → rayon** |
| `ellipse(x, y, w, h)` | `ofDrawEllipse(x, y, w, h)` | centrée dans les deux cas |
| `rect(x, y, w, h)` | `ofDrawRectangle(x, y, w, h)` | coin haut-gauche dans les deux cas |
| `line(x1, y1, x2, y2)` | `ofDrawLine(x1, y1, x2, y2)` | |
| `mouseX`, `mouseY` | `mouseX`, `mouseY` | membres hérités de `ofBaseApp` |
| `width`, `height` | `ofGetWidth()`, `ofGetHeight()` | |
| `random(a, b)` | `ofRandom(a, b)` | dessin refait à chaque frame : stocker ou `ofSeedRandom` |
| `PI`, `2 * PI` | `PI`, `TWO_PI` | |
| `cos`, `sin`, `sqrt`, `abs` | idem (`<cmath>`) | `abs` sur float : `fabs` ou `std::abs` |
| `translate(x, y)` | `ofPushMatrix(); ofTranslate(x, y); ... ofPopMatrix();` | |
| `blendMode(ADD)` | `ofEnableBlendMode(OF_BLENDMODE_ADD)` | **pas de `DIFFERENCE`** ; retour par `OF_BLENDMODE_ALPHA` |
| `beginShape()` / `vertex()` / `endShape(CLOSE)` | `ofBeginShape()` / `ofVertex()` / `ofEndShape(true)` | |
| `loadImage("f.png")` | `ofImage img; img.load("f.png")` | chemin relatif à `bin/data` |
| `image(img, x, y)` | `img.draw(x, y)` | `ofSetColor(255)` avant, sinon teinte |
| `get(x, y)` | `img.getColor(x, y)` | lit l'image, pas l'écran ; borner x, y |
| `red(c)` | `c.r` | |
| `text(s, x, y)` | `ofDrawBitmapString(s, x, y)` | pas d'accents |
| `colorMode(HSB); fill(h, s, b)` | `ofSetColor(ofColor::fromHsb(h, s, b))` | **0–255 partout**, pas 360 pour la teinte |
| `hue(c)`, `saturation(c)`, `brightness(c)` | `c.getHue()`, `c.getSaturation()`, `c.getBrightness()` | |
| `lerpColor(a, b, t)` | `a.getLerped(b, t)` | |
| `loadPixels(); pixels[i] = c; updatePixels()` | `img.setColor(x, y, c); img.update()` | écrire dans une image résultat, pas dans la source |
| `filter(INVERT)`, `filter(GRAY)`… | à la main, boucle sur les pixels (11) | c'est le but du cours |
| `def keyPressed():` + `key` | `void keyPressed(int key)` | `key - '0'` pour un chiffre |
| `str(n)` | `ofToString(n)` | |
| `print(x)` | `std::cout << x << std::endl;` | console visible en Debug |
| liste `[]` | `std::vector<T>` | type obligatoire |
| `l.append(v)` | `l.push_back(v)` | |
| `l.pop(0)` | `l.erase(l.begin())` | |
| `len(l)` | `l.size()` | |
| `global x` | membre de classe dans le `.h` | |
| `def f(a, b):` | déclarer dans le `.h`, définir `void ofApp::f(float a, float b)` | |
| `range(0, n)` | `for (int i = 0; i < n; i++)` | |
| `range(0, n, p)` | `for (int i = 0; i < n; i += p)` | |
| frame counter | `ofGetElapsedTimef()`, `ofGetLastFrameTime()` | |

## Exercices (Exercices.docx), à adapter

- **Exercice 1 — carré de cercles** : section « Autonomie » à la fin du cours 03 (`cours/03-aleatoire.md`). Quatre boucles `for`, taille et couleur accumulées, sens de parcours différent par côté. Bonus losange : après 13 (rotation de 45°, ou `ofRotateDeg` avec `ofPushMatrix`).
- **Exercice 2 — listes** : après 04. Les sept items se traduisent directement en `std::vector<int>` / `std::vector<std::string>`, `std::cout`, accumulation dans une `std::string`. Rendu en `.cpp` au lieu de `.pyde`.

# Tech Art 1 — cours

Un document par leçon, pour des débutants qui découvrent le C++ avec openFrameworks. Chaque cours s'appuie sur une paire de fichiers `ofAppNN.h` / `ofAppNN.cpp` du dossier parent ; le document explique les structures du langage et les idées de création d'image qu'il utilise, sans entrer dans l'organisation interne d'openFrameworks.

| # | Cours | Fichiers | Ce qu'on apprend |
|---|---|---|---|
| — | [Préparation de l'environnement](00-environnement.md) | aucun | installer Visual Studio 2026 et openFrameworks, créer un projet, compiler |
| 00 | [Premier contact](00-premier-contact.md) | ofApp00 puis ofApp00a | repère de l'écran, fonctions et paramètres, variables, couleurs RGBA |
| 01 | [Variables et opérations](01-variables.md) | ofApp01 | `int`, `float`, `=`, division entière, rayon |
| 02 | [La boucle `for`](02-boucle-for.md) | ofApp02 | compteur, accumulation, fill et contour |
| 03 | [Aléatoire](03-aleatoire.md) | ofApp03 | `ofRandom`, graine, boucle à pas |
| 04 | [Listes](04-listes.md) | ofApp04 | `std::vector`, `std::string`, console |
| 05 | [Cycle et souris](05-cycle-souris.md) | ofApp05 | `setup` / `update` / `draw`, variables partagées |
| 06 | [Animation](06-animation.md) | ofApp06 | vitesse, `dt`, `if`, rebond |
| 07 | [Traînée](07-trainee.md) | ofApp07 | fonctions, file bornée, `struct` |
| 08 | [Traînée évoluée](08-trainee-evoluee.md) | ofApp08 | grandeurs selon l'indice et le temps |
| 09 | [Couleur](09-couleur.md) | ofApp09 | RGB, HSB, `ofColor`, dégradés |
| 09a | [La couleur dans le jeu vidéo et le cinéma](09a-couleur-jeu-video-cinema.md) | sans code | pipeline, gamut, écrans, banding |
| 10 | [Image et pixel](10-image-pixel.md) | ofApp10 | `ofImage`, `getColor`, `ofClamp`, `bool` |
| 11 | [Filtres](11-filtres.md) | ofApp11 | double boucle, `return`, `switch`, clavier |
| 11a | [Gamma et espace linéaire](11a-gamma.md) | ofApp11a | courbe sRGB, `pow`, table précalculée |
| 11b | [HDR et tone mapping](11b-tone-mapping.md) | ofApp11b | exposition, Reinhard, ACES, tracer une courbe |
| 11c | [LUT et étalonnage](11c-lut.md) | ofApp11c | tables de 256, looks, force |
| 11d | [YCbCr et compression](11d-ycbcr.md) | ofApp11d | luminance / chrominance, blocs |
| 11e | [OKLab](11e-oklab.md) | ofApp11e | `struct`, `cbrt`, dégradés, OKLCH |
| 11f | [Daltonisme](11f-daltonisme.md) | ofApp11f | matrice 3×3, sévérité, accessibilité |
| 11g | [Palette et dithering](11g-palette-dithering.md) | ofApp11g | plus proche, Bayer, Floyd-Steinberg |
| 12 | [Pointillisme](12-pointillisme.md) | ofApp12 | grille, distance, proportion |
| 13 | [Cercle de cercles](13-cercle-de-cercles.md) | ofApp13 | `cos`, `sin`, radians, `%`, fusion |
| 14 | [Filtres géométriques](14-filtres-geometriques.md) | ofApp14 | lecture à l'envers, miroir, vagues, glitch |
| 15 | [Grille en rotation](15-grille-rotation.md) | ofApp15 | centre de case, déphasage, `(float)` |
| 16 | [Fleurs polaires](16-fleurs-polaires.md) | ofApp16 | polaire, forme libre, `? :` |
| 17 | [Convolution](17-convolution.md) | ofApp17 | noyau, voisins, bords, drapeau |
| 18 | [Peinture par particules](18-peinture-particules.md) | ofApp18 | projet final, `ofFbo` |

## Illustrations

Les images du dossier `img/` sont générées par `img/generer_a.py` (formes et schémas), `img/generer_b.py` (traitement d'image sur `data/pandaroux.jpg`) et `img/generer_c.py` (bloc couleur avancée), qui reproduisent les rendus des sketches avec Python. Elles nécessitent Pillow, numpy et matplotlib :

```
python3 -m venv venv && venv/bin/pip install pillow numpy matplotlib
venv/bin/python img/generer_a.py
venv/bin/python img/generer_b.py
venv/bin/python img/generer_c.py
```

Des captures d'écran des vrais programmes openFrameworks peuvent les remplacer en gardant les mêmes noms de fichiers.

## Code complet dans les cours

Chaque cours se termine par une section « Le code complet, pas à pas », générée depuis les fichiers `ofAppNN.h` / `ofAppNN.cpp` par `inserer_code.py`. Après toute modification du code, relancer :

```
python3 cours/inserer_code.py
```

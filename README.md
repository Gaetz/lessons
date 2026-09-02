# lessons

Cours de programmation 3D — Notre-Dame Providence × ARTFX.
Une leçon par dossier, en Markdown, avec des démos 3D qui tournent dans les diapos.

## Organisation

```
theme-ndp/          thème partagé — charte NDP/ARTFX, layouts, composants
_template/          squelette d'une nouvelle leçon
scripts/            lesson.mjs, new-lesson.mjs, fetch-assets.mjs
Y1/ … Y5/           une année par dossier, une leçon par sous-dossier NN-slug
  Y1/00-rentree/    présentation de rentrée 2026
```

Le thème est référencé en chemin relatif (`theme: ../../theme-ndp`) depuis chaque
leçon. Une couleur changée dans `theme-ndp/styles/layout.css` se propage partout.

## Utilisation

```bash
corepack enable            # une fois
pnpm install

pnpm list                              # les leçons existantes
pnpm lesson dev    Y1/00-rentree       # http://localhost:3030
pnpm lesson build  Y1/00-rentree       # SPA statique -> dist/
pnpm lesson export Y1/00-rentree       # PDF de secours -> dist/

pnpm new Y2 01-moteurs "Architecture d'un moteur"
```

## Composants du thème

```md
<ShaderCanvas src="/shaders/raymarch.frag" :steps="$clicks" height="300px" />
<FrameBudget :steps="$clicks" :fps="60" />
```

`:steps="$clicks"` branche le composant sur les clics Slidev : la démo se construit
pendant qu'on parle. `ShaderCanvas` coupe sa boucle rAF dès que la diapo n'est plus
active — sans ça, douze canvas tournent en parallèle et la machine de la salle
s'écroule au milieu du cours.

Layouts disponibles : `cover`, `section`, `default`, `statement`, `split`.
Chacun accepte `breadcrumb:` pour le fil d'ariane en haut à gauche.

## Assets

| Contenu | Où |
|---|---|
| md, vue, glsl, svg, code | git |
| images (avif/webp) | git |
| `.glb` compressés (quelques Mo) | git-lfs — voir `.gitattributes` |
| vidéos, demoreels, renders | hors git — `assets.json` + `pnpm assets` |

Quota git-lfs GitHub gratuit : 1 Go. LFS pour les modèles 3D, pas pour la vidéo.

## Avant de présenter

Sortir le PDF (`pnpm lesson export …`) : il n'a pas la 3D vivante, mais les démos
live tombent en salle, jamais chez soi. Taguer la version présentée.

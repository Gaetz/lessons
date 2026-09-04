# lessons — contexte projet

Cours de programmation 3D pour le BTS SIO SLAM de Notre-Dame Providence,
monté en partenariat avec ARTFX. Présentations Slidev, une leçon par dossier.

Public : étudiants de BTS, souvent débutants en programmation, venus de filières
variées. Le contexte industriel est le cinéma, les VFX et le jeu vidéo.

## Structure

    theme-ndp/          thème partagé — charte NDP/ARTFX
    _template/          squelette copié par `pnpm new`
    scripts/            lesson.mjs, new-lesson.mjs, fetch-assets.mjs
    Y1/ … Y5/           une année par dossier, une leçon par sous-dossier NN-slug

Chaque leçon référence le thème en chemin relatif : `theme: ../../theme-ndp`.

## Commandes

    pnpm list
    pnpm lesson dev    Y1/00-rentree
    pnpm lesson build  Y1/00-rentree
    pnpm lesson export Y1/00-rentree      # PDF
    pnpm new Y2 01-moteurs "Titre"

## Thème

Palette extraite du deck institutionnel, dans `theme-ndp/styles/layout.css` :

| Rôle | Valeur |
|---|---|
| orange ARTFX | `#EA5027` |
| crème (texte sur noir) | `#EDEEDA` |
| bleu logo NDP | `#0F6FA5` |
| encre | `#000000` |

Police : **Raleway** (Black 900 pour les titres, Medium 500 pour le corps),
chargée par Google Fonts via le `fonts` du `package.json` du thème.

Le thème force `colorSchema: light` (package.json) : la charte est fixe, et
sans ça un navigateur en mode sombre rend les extraits de code illisibles
(pastilles sombres sur diapos blanches). Ne pas retirer.

Layouts : `cover` (orange, bandeau ARTFX pivoté sur la tranche droite),
`section` (noir, titre crème en bas), `default` (blanc, fil d'ariane, logos, filet),
`statement` (orange, phrase centrée), `split` (deux colonnes, slot `right`),
`demo` (noir plein cadre, slot `caption` en bas).
Tous acceptent `breadcrumb:`.

Composants : `ShaderCanvas`, `FrameBudget`, `Breadcrumb`, `BrandLogos`,
`ZoomImage` (image cliquable qui s'ouvre plein écran ; `@click.stop` pour ne
pas faire avancer Slidev).

## Règles à ne pas casser

- **Les assets du thème s'importent en module ES** (`import x from '../assets/x.png'`),
  jamais par chemin absolu `/brand/x.png` : Vite ne résout pas le `public/` d'un thème
  et le build casse.
- **`ShaderCanvas` coupe sa boucle rAF hors diapo active** (`useIsSlideActive`).
  Ne pas retirer : sinon tous les canvas tournent en parallèle et la machine de la
  salle s'effondre pendant le cours.
- **pnpm 11** : les scripts d'installation s'autorisent par `allowBuilds:` dans
  `pnpm-workspace.yaml`, pas par `onlyBuiltDependencies` (clé de pnpm 10, ignorée
  en silence).
- **Les shaders sont de vrais fichiers `.frag`** dans `public/shaders/`, chargés par
  `src=`. Jamais de GLSL dans une template string.
- `:steps="$clicks"` branche un composant sur les clics Slidev : la démo se construit
  pendant qu'on parle. C'est le ressort pédagogique principal, l'utiliser.

## Assets

md, vue, glsl, svg, images → git. Modèles `.glb` → git-lfs (voir `.gitattributes`).
Vidéos et renders → **hors git**, déclarés dans le `assets.json` de la leçon et
récupérés par `pnpm assets`. Quota LFS GitHub gratuit : 1 Go.

## Conventions de rédaction

- Tout en français.
- Les intentions de l'orateur vont dans des commentaires HTML `<!-- -->`,
  qui deviennent les notes de présentateur.
- **Ne pas inventer de chiffres.** Pas de durée de rendu, de volume de données ni de
  taux d'insertion sans source. Si un chiffre manque, laisser un TODO explicite.
- Une idée par diapo. Les listes à cinq puces sont un symptôme, pas un format.

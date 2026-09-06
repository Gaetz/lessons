# Y1/01-code-et-pixels — Tech Art 1 : C++ et openFrameworks

## Cadre

Premier module de programmation de l'année : manipulation d'image et de
couleur en C++ avec openFrameworks, pour débutants. 27 cours écrits
(00-18, plus 09a et le bloc couleur avancée 11a-11g), un document markdown
complet par cours, une paire `ofAppNN.h`/`ofAppNN.cpp` compilable par cours.

La présentation est le **squelette des séances** ; le document de cours est
la référence que les étudiants lisent et téléchargent. Ne pas dupliquer le
document dans les diapos : condenser, renvoyer au document.

## Structure

    slides.md               couverture + src des pages
    pages/00-module.md      intro du module (contrat, méthode, carte du semestre)
    pages/00a-installation.md  préliminaire : VS 2026 + openFrameworks sur Windows
    pages/01-bases.md       bloc 1 : cours 00-05
    pages/02-mouvement.md   bloc 2 : cours 06-08
    pages/03-couleur.md     bloc 3 : cours 09, 09a
    pages/04-pixels.md      bloc 4 : cours 10, 11
    pages/05-geometrie.md   bloc 5 : cours 12-16
    pages/06-convolution.md bloc 6 : cours 17
    pages/07-couleur-avancee.md  bloc 7 : cours 11a-11g
    pages/08-projet.md      bloc 8 : cours 18 + statement de clôture
    public/ressources/      copie INTACTE du dossier source of_cours

L'ordre des blocs ne suit PAS la numérotation des cours : la couleur avancée
(11a-11g) vient après la géométrie et la convolution parce que 11d dépend du
17 (indice y·w+x), 11e du 16 (polaire) et 11g des 12 et 14 (distance, gros
pixels) — dépendances déclarées dans les en-têtes « Avant : » des documents.

## Ressources du cours vs fichiers de l'étudiant

Les paires `ofAppNN.h`/`.cpp` sont la **référence de l'auteur** (téléchargeable,
et corrigé). L'étudiant, lui, ne crée aucun fichier : il modifie `ofApp.h` et
`ofApp.cpp`, qui existent par défaut dans son projet. Le document du cours 00
donne le code complet à y coller (section 2) AVANT de l'expliquer ; à partir
du cours 01, la méthode générale est de copier la paire `ofAppNN` dans `src/`
et de changer l'include de `main.cpp` (documentée dans 00-environnement.md).

## Le dossier ressources

`public/ressources/` reproduit la structure d'origine (INDEX.md, ofApp*.h/cpp,
cours/*.md, cours/img/, data/) : les liens relatifs des markdown fonctionnent
sur GitHub, et tout est servi par Slidev, donc téléchargeable depuis les
diapos. **Ne pas renommer ni déplacer** ces fichiers : les documents se lient
entre eux. La source de vérité du contenu pédagogique est ce dossier ; les
diapos suivent.

## Gabarit d'un cours dans les diapos

Les diapos suivent **les étapes de code** du document (sections « Le code
complet, pas à pas »), dans l'ordre du fichier — sauf quand le corps du
document enseigne dans un autre ordre (cours 11 : la double boucle d'update
AVANT la fonction filtre, « la machine d'abord, la recette après ») :

1. `split` — intro : titre « Cours NN — … », l'accroche, l'image du rendu
   (`/ressources/cours/img/NN-*.png`, `ZoomImage` si elle mérite le zoom) ;
2. une diapo « mise en place » quand le `.h` porte de la substance (variables
   partagées, annonces) — sinon le `.h`/`setup()` sont mentionnés en encart ;
3. **une diapo par étape substantielle** (`update()`, `draw()`, fonctions) :
   le code de l'étape épuré (les commentaires dont le contenu passe en puces
   sont retirés), les explications en puces à côté ou dessous ; les blocs
   > ~10 lignes utilisent le line-highlight Slidev (```cpp {1-4|6-9}```) —
   dans ce cas les puces sont statiques (pas de v-clicks concurrents) ;
   les étapes longues sont scindées (1/2, 2/2), jamais plus de ~16 lignes ;
4. les `keyPressed()` triviaux sont des encarts ; `versLineaire`/`versSRGB`
   sont montrées en 11a et seulement rappelées en 11b/11e/11f ;
5. chaque cours à code se clôt sur une diapo « À vous » : 3 exercices tirés
   du document, du plus élémentaire au plus dur, l'avancé marqué 🔥 (légende
   sur la ligne d'envoi), et un renvoi au document pour le reste — elle reste
   affichée pendant que les étudiants pratiquent, les corrigés et erreurs
   types vont dans les notes orateur (seul le 09a, sans code, n'en a pas) ;
6. la dernière diapo du cours — la diapo « À vous » — porte la ligne de
   téléchargements en `ndp-credit` : cours complet + ofAppNN.h + ofAppNN.cpp
   (+ data si besoin).

Les notes orateur portent le fil de séance et les renvois aux exercices du
document (dont les « Autonomie » des cours 03 et 07 — le 08 est le corrigé
du 07, ne l'ouvrir qu'après).

## Commandes

    pnpm lesson dev    Y1/01-code-et-pixels
    pnpm lesson export Y1/01-code-et-pixels    # PDF pour distribution

## À savoir

- **Repère visuel de la pratique : bleu NDP** (orange = information). Dans les
  documents, un bloc d'essai s'écrit en citation commençant par `**Essaie**`
  (ou À toi/Exercice) → encadré bleu dans le PDF ; les sections `## Exercices`
  et `## Autonomie` sont enveloppées de bleu automatiquement par docs-pdf.mjs.
- **Diapos, document, PDF avancent ensemble.** Toute modification de contenu
  dans les diapos se reporte dans le document `cours/*.md` correspondant, et
  les PDF se régénèrent dans la foulée (`node scripts/docs-pdf.mjs
  Y1/01-code-et-pixels`, depuis la racine). Ne jamais laisser les trois
  supports diverger.

- **La source de vérité du contenu est `public/ressources/`** (versionnée) —
  le dossier `~/Downloads/of_cours` d'origine est en retard sur elle.
- Après modification du code ofApp* : `python3 cours/inserer_code.py` (depuis
  public/ressources) régénère les sections « code complet » des documents,
  puis `node scripts/docs-pdf.mjs Y1/01-code-et-pixels` (depuis la racine)
  régénère les PDF téléchargeables de `cours/pdf/`.
- `style.css` (racine de la leçon) masque le pied de page du thème et resserre
  la typographie — un serveur de dev lancé avant sa création doit être
  redémarré pour le charger.
- Les images cours/img sont générées par les scripts generer_*.py (voir
  cours/README.md) ; des captures d'écran des vrais programmes peuvent les
  remplacer à noms constants.

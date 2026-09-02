# Y1/00-rentree — présentation de rentrée 2026

## Cadre

- **Public** : étudiants de 1re année seuls, jour de rentrée. Pas de parents,
  pas de partenaires.
- **Durée** : 45 min de matière (~35 diapos) — l'heure réelle absorbera la prise
  de parole du directeur et les débordements de démo. Ne pas regonfler.
- **Objectif**, dans cet ordre : donner du sens et de l'ambition, poser le niveau
  d'exigence, expliquer le cursus.

Attention : le deck institutionnel dont vient la charte était un support de
**recrutement** (Parcoursup, frais de scolarité, vocation sociale). Ce n'est pas
le même discours. Ici les étudiants sont déjà inscrits.

## La thèse

> L'IA a effondré le coût d'écrire du code. Elle n'a pas effondré le coût de
> comprendre. Le temps réel et la 3D sont précisément le domaine où la
> compréhension reste irréductible — et ce programme est construit pour ça.

Les quatre parties sont les temps de cette phrase. Toute diapo qui ne sert pas
cette progression est à couper.

## Plan

L'ordre suit la phrase de la thèse : métier → cinéma/3D → programme.
Chaque fichier **commence par sa diapo de section** : réordonner les parties,
c'est réordonner les `src:` de `slides.md`.

| Fichier | Partie | Durée |
|---|---|---|
| `slides.md` | titre | — |
| `pages/00-ouverture.md` | NDP, ARTFX, la direction (le directeur parle ici), **cold open**, première promo, métiers en 4 temps (classiques → nouveaux → technologies universelles → presse Unreal), la promo | 7-8 min |
| `pages/01-metier.md` | le métier a changé — concret (`dt`) puis trois âges, baissé / pas baissé | 12 min |
| `pages/02-cinema-3d.md` | le terrain — pourquoi des programmeurs (séquence du deck source : jeu → cinéma ? → Muybridge → pipeline → moteur), points communs, **budget de frame**, moteur, GPU, convergence, collaboration | 18-20 min |
| `pages/03-programme.md` | la réponse — piliers U4/U5/U6, socle, objection « c'est un BTS », projets, attentes, réassurance | 10 min |
| `pages/04-cloture.md` | premières semaines, **bookend** (re-shader, « Rendez-vous dans deux ans »), bienvenue | 5 min |

Le **cold open** (layout `demo`, shader plein cadre, « Dans deux ans, vous saurez
écrire ça ») est placé après la page équipe, pas après le titre : le bloc
institutionnel reste d'un seul tenant, et si un directeur prend la parole il rend
le micro juste avant.

Le **budget de frame** en partie 2 est le point qui boucle sur la partie 1 :
16,6 ms ne se négocient pas avec un prompt. C'est le meilleur argument du discours.
La partie 3 (programme) arrive après le terrain : elle se présente comme une
réponse à un désir, pas comme un règlement.

## Décisions actées

- **Un directeur prend la parole**, après la diapo équipe, et rend le micro
  juste avant le cold open.
- Toutes les diapos sont rédigées ; il ne manque que des données factuelles
  (voir ci-dessous), matérialisées par des placeholders TODO dans les diapos.

## Ce qui manque encore

- Une ou deux phrases sur le projet de l'établissement, de la main de Gaëtan
  (à dire à l'oral après la vidéo NDP)
- La liste matériel/comptes : la diapo placeholder qui la portait a été
  remplacée par l'emploi du temps réel (`04-cloture.md`) — décider si cette
  liste revient sur une diapo ou passe par un autre canal (mail, Discord…)
- Chiffres de poursuite d'études / insertion (« C'est un BTS » dans
  `03-programme.md`) — à sourcer, sinon ne rien annoncer, même à l'oral
- Le nombre d'étudiants et leurs filières d'origine (« Et vous ? » dans
  `00-ouverture.md`)

## Avant de présenter

Sortir le PDF (`pnpm lesson export Y1/00-rentree`) : il n'a pas la 3D vivante,
prévoir une capture de repli pour chaque démo. Taguer la version présentée.

# Tutoriel — Git et GitHub : sauvegarder, partager, collaborer

> **Avant** : savoir ouvrir un terminal et s'y déplacer avec `cd`.
>
> **Comment travailler** : installe **Git** (git-scm.com, options par défaut) et crée un compte sur **github.com**. Sous Windows, toutes les commandes se tapent dans **Git Bash**, installé avec Git (clic droit dans un dossier → *Open Git Bash here*). Sous macOS et Linux, le terminal habituel suffit.

Tu as déjà perdu un fichier, écrasé une bonne version par une mauvaise, ou envoyé `projet_final_v3_VRAIMENT_final.zip` à un camarade ? **Git** règle ces trois problèmes. C'est un logiciel qui garde **l'historique complet** de ton projet : chaque version enregistrée peut être retrouvée, comparée, restaurée. **GitHub** est un site qui héberge une copie de cet historique en ligne : ta sauvegarde, et le point de rendez-vous de ton équipe.

Ce tutoriel explique d'abord les six commandes de base, puis les met en pratique dans deux situations :

- **Tutoriel A** — tu commences un projet : tu crées le dépôt sur GitHub, tu le clones, tu travailles, tu pousses ;
- **Tutoriel B** — le projet existe déjà sur ton disque : tu crées un dépôt vide sur GitHub et tu y relies ton dossier.

Un troisième, le **tutoriel C**, est à garder sous le coude : il déroule pas à pas ce qui se passe quand ton `push` est refusé et que le `rebase` s'arrête sur des conflits.

## 1. Les idées de base

### Dépôt, commit, historique

Un **dépôt** (*repository*, ou *repo*) est un dossier suivi par Git. Git y range, dans un sous-dossier caché `.git`, tout l'historique du projet. Ne touche jamais à ce sous-dossier à la main.

Un **commit** est une **photo** du projet à un instant donné, accompagnée d'un message qui dit ce qui a changé : « ajoute le menu pause », « corrige le rebond du ballon ». L'historique est la suite de ces photos, de la plus ancienne à la plus récente.

### Les trois zones

Un fichier modifié ne part pas directement dans l'historique. Il passe par trois zones :

| Zone | Ce qu'elle contient | Commande pour y entrer |
|---|---|---|
| **Dossier de travail** | tes fichiers, tels que tu les modifies | tu édites, tout simplement |
| **Zone de préparation** (*staging*) | ce qui fera partie du prochain commit | `git add` |
| **Historique local** | les commits, sur ton ordinateur | `git commit` |

À ces trois zones s'ajoute le **dépôt distant** (*remote*), la copie hébergée sur GitHub. Par convention, il s'appelle `origin`.

Pourquoi une zone de préparation ? Pour choisir. Tu as corrigé un bug et commencé une nouvelle fonction dans la même séance : tu peux enregistrer la correction seule, dans un commit propre, et garder la fonction inachevée pour plus tard.

### Local et distant

Tout ce que font `add` et `commit` reste **sur ton ordinateur**. Rien ne part sur GitHub tant que tu n'as pas fait `push`. À l'inverse, ce que tes camarades ont poussé n'arrive chez toi que quand tu le demandes, avec `fetch`. Git ne synchronise jamais rien tout seul.

## 2. Une seule fois par ordinateur : se présenter

Chaque commit porte le nom et l'e-mail de son auteur. Dis à Git qui tu es, une seule fois sur chaque machine :

```bash
git config --global user.name "Prenom Nom"
git config --global user.email "ton.email@exemple.fr"
git config --global init.defaultBranch main
```

Utilise l'e-mail de ton compte GitHub : c'est grâce à lui que GitHub relie tes commits à ton profil. La troisième ligne nomme `main` la branche principale des nouveaux dépôts, comme le fait GitHub.

> **Astuce** : `git config --global --list` affiche ta configuration actuelle.

## 3. Les commandes, une par une

### `git status` — où en suis-je ?

Pas une des six commandes, mais la plus utile de toutes. Elle dit quels fichiers sont modifiés, lesquels sont prêts pour le commit, et si tu es en avance ou en retard sur GitHub. **Tape-la avant et après chaque commande** : c'est la meilleure façon de comprendre ce que fait Git.

```bash
git status
```

### `git add` — préparer

`git add` place des modifications dans la zone de préparation.

```bash
git add main.cpp             # un fichier précis
git add src/                 # tout un dossier
git add .                    # tout ce qui a changé dans le dossier courant
```

`git add .` est le plus courant. Le point désigne le dossier courant et tout ce qu'il contient. Un fichier ajouté puis modifié à nouveau doit être ajouté encore une fois : `add` prend une photo du fichier **au moment** où tu le tapes.

### `git commit` — enregistrer

`git commit` transforme le contenu de la zone de préparation en un commit de l'historique local.

```bash
git commit -m "Ajoute le menu pause"
```

L'option `-m` donne le message. Un bon message dit **ce que fait** le commit, en une phrase courte : « Corrige le rebond sur le bord droit » plutôt que « modif » ou « ça marche ». Dans trois semaines, c'est ce message qui te permettra de retrouver la bonne version.

> **Piège** : sans `-m`, Git ouvre un éditeur de texte dans le terminal (souvent *Vim*), déroutant la première fois. Pour en sortir : touche `Échap`, puis tape `:q!` et `Entrée`. Le commit est annulé, recommence avec `-m`.

> **Astuce** : `git log --oneline` affiche l'historique, un commit par ligne, le plus récent en haut.

### `git push` — envoyer sur GitHub

`git push` envoie tes commits locaux vers le dépôt distant.

```bash
git push
```

Seuls les **commits** partent. Un fichier modifié mais pas commité reste chez toi. La toute première fois, sur un dépôt créé chez toi, il faut préciser où envoyer : `git push -u origin main` (voir le tutoriel B). Ensuite, `git push` seul suffit.

> **Piège** : si un camarade a poussé avant toi, GitHub refuse ton `push` avec un message contenant *rejected* et *fetch first*. Rien n'est perdu : récupère d'abord son travail avec `fetch` et `rebase` (plus bas), puis pousse à nouveau.

### `git clone` — copier un dépôt existant

`git clone` télécharge un dépôt GitHub complet, historique compris, dans un nouveau dossier.

```bash
git clone https://github.com/ton-pseudo/mon-projet.git
```

Le dossier `mon-projet` est créé là où tu te trouves, et il est déjà relié à GitHub sous le nom `origin`. On ne clone qu'**une fois** par ordinateur. Ensuite, on récupère les nouveautés avec `fetch`.

### `git fetch` — regarder ce qui a changé en ligne

`git fetch` télécharge les commits que tu n'as pas encore, **sans toucher à tes fichiers**.

```bash
git fetch
```

Après un `fetch`, `git status` te dit si tu es en retard (*behind*) sur `origin/main`, la copie locale de la branche `main` de GitHub. Tes fichiers, eux, n'ont pas bougé : `fetch` regarde, il n'applique rien.

### `git rebase` — se remettre à jour

`git rebase` intègre les nouveautés récupérées par `fetch` dans ton travail.

```bash
git rebase origin/main
```

L'image à garder en tête : Git **met tes commits de côté**, avance ta branche jusqu'au dernier commit de GitHub, puis **rejoue tes commits par-dessus**, un par un. Résultat : un historique bien droit, comme si tu avais commencé ton travail après celui de ton camarade.

```text
Avant :   origin/main :  A - B - C - D        (D poussé par un camarade)
          ta branche  :  A - B - C - X        (X : ton commit local)

Après :   ta branche  :  A - B - C - D - X'   (X rejoué après D)
```

Tu peux alors pousser sans être refusé.

> **Astuce** : `git pull --rebase` fait `fetch` puis `rebase` en une seule commande. Fais-le d'abord en deux temps pour bien voir les deux étapes.

> **Piège** : `rebase` refuse de démarrer si tu as des modifications **non commitées**. Commite-les d'abord, avec `add` et `commit`.

### Quand le rebase s'arrête : le conflit

Si ton camarade et toi avez modifié **les mêmes lignes** du même fichier, Git ne peut pas choisir à ta place. Le rebase s'arrête et `git status` liste les fichiers en conflit. Dans chacun, Git a encadré les deux versions :

```text
<<<<<<< HEAD
vitesse = 450;
=======
vitesse = 200;
>>>>>>> 4441dfc (Ralentit le ballon)
```

Pour résoudre :

1. ouvre le fichier, garde la bonne version (ou un mélange des deux), et **supprime les trois lignes de marqueurs** `<<<<<<<`, `=======`, `>>>>>>>` ;
2. vérifie que le programme compile ;
3. `git add` le fichier corrigé ;
4. `git rebase --continue`.

Si tu es perdu, `git rebase --abort` annule tout et te ramène exactement à la situation d'avant le rebase.

Le **tutoriel C** déroule ce cas en entier, avec les messages exacts de Git : lis-le avant ton premier conflit.

> **Astuce** : les conflits sont rares si chacun travaille sur des fichiers différents et si vous poussez souvent, par petits commits.

## 4. Tutoriel A — créer le dépôt sur GitHub, le cloner, pousser

Situation : tu démarres un projet neuf.

### A1. Créer le dépôt sur GitHub

1. Sur github.com, clique sur **+** en haut à droite, puis **New repository** ;
2. **Repository name** : un nom court, sans espaces ni accents, par exemple `mon-premier-depot` ;
3. choisis **Public** ou **Private** ;
4. coche **Add a README file** : le dépôt aura déjà un premier commit, ce qui permet de le cloner tout de suite ;
5. dans **Add .gitignore**, tu peux choisir un modèle adapté à ton langage (par exemple *VisualStudio* pour un projet Visual Studio) ;
6. clique sur **Create repository**.

### A2. Cloner

Sur la page du dépôt, clique sur le bouton vert **Code**, onglet **HTTPS**, et copie l'adresse. Dans Git Bash, place-toi dans le dossier où tu ranges tes projets, puis :

```bash
cd ~/Documents
git clone https://github.com/ton-pseudo/mon-premier-depot.git
cd mon-premier-depot
git status
```

`git status` répond que tout est à jour (*nothing to commit, working tree clean*) : ton dossier est une copie exacte de GitHub.

> **Piège** : n'oublie pas le `cd mon-premier-depot`. Les commandes Git ne fonctionnent qu'à l'intérieur du dossier du dépôt ; ailleurs, Git répond *not a git repository*.

### A3. Travailler, préparer, enregistrer

Crée ou modifie des fichiers dans le dossier, avec l'éditeur de ton choix. Par exemple, ajoute une ligne au `README.md` et crée un fichier `notes.txt`. Puis :

```bash
git status
git add .
git status
git commit -m "Ajoute mes notes et complete le README"
git log --oneline
```

Observe les deux `git status` : avant `add`, les fichiers sont en rouge (modifiés) ; après, en vert (prêts pour le commit).

### A4. Pousser

```bash
git push
```

La première fois, Windows ouvre une fenêtre de connexion à GitHub : connecte-toi dans le navigateur, puis Git se souvient de toi. Recharge la page du dépôt sur GitHub : ton commit et tes fichiers y sont.

> **Astuce** : GitHub n'accepte plus le mot de passe du compte dans le terminal. La fenêtre de connexion de Git pour Windows règle la question. Sur une autre machine, si on te demande un mot de passe, il faut un *Personal Access Token* créé dans les réglages GitHub (*Settings → Developer settings*).

### A5. Le cycle de chaque séance

Désormais, une séance de travail suit toujours le même rythme :

```bash
git fetch
git rebase origin/main      # se mettre à jour avant de commencer
# ... travailler ...
git add .
git commit -m "Ce que j'ai fait"
git push                    # sauvegarder et partager
```

> **Essaie** : modifie le `README.md` **directement sur GitHub** (icône crayon, puis *Commit changes*). Chez toi, sans rien toucher, tape `git status` : Git ne sait encore rien. Puis `git fetch` et `git status` de nouveau : tu es en retard d'un commit. Termine par `git rebase origin/main` et ouvre le fichier.

## 5. Tutoriel B — relier un projet existant à un nouveau dépôt GitHub

Situation : ton projet existe déjà sur ton disque, par exemple une solution Visual Studio, et n'a jamais été suivi par Git.

### B1. Créer un dépôt **vide** sur GitHub

Même début que le tutoriel A : **+**, **New repository**, un nom. Mais cette fois, **ne coche rien** : ni README, ni .gitignore, ni licence. Clique sur **Create repository**.

> **Piège** : c'est la différence essentielle avec le tutoriel A. Si tu coches *Add a README file*, le dépôt GitHub contient déjà un commit que ton projet local n'a pas, et ton premier `push` sera refusé. Un dépôt vide est prêt à recevoir ton historique tel quel.

GitHub affiche alors une page d'aide avec l'adresse du dépôt, du type `https://github.com/ton-pseudo/mon-projet.git`. Garde-la ouverte.

### B2. Transformer le dossier en dépôt Git

Ouvre Git Bash **dans le dossier du projet**, puis :

```bash
git init
```

Git crée le sous-dossier caché `.git` : le dossier est devenu un dépôt, encore vide d'historique. `git status` liste tous les fichiers comme non suivis.

### B3. Écarter ce qui ne doit pas être versionné

Avant le premier `add`, crée à la racine du projet un fichier nommé exactement `.gitignore`. Chaque ligne y désigne des fichiers ou dossiers que Git doit ignorer. Pour un projet Visual Studio, un point de départ :

```text
.vs/
x64/
Debug/
Release/
bin/
obj/
*.user
```

Ce sont des fichiers que Visual Studio **régénère** à chaque compilation. Les versionner alourdit le dépôt et crée des conflits inutiles entre camarades.

> **Astuce** : GitHub publie des modèles complets de `.gitignore` pour chaque langage et outil, dans le dépôt *github/gitignore*. C'est le même modèle que propose la case *Add .gitignore* du tutoriel A.

### B4. Premier commit

```bash
git add .
git status
git commit -m "Premier commit : import du projet"
```

Vérifie dans le `git status` intermédiaire qu'aucun dossier `.vs`, `x64` ou `Debug` n'apparaît. S'il y en a un, complète le `.gitignore` avant de commiter.

### B5. Relier au dépôt GitHub

```bash
git branch -M main
git remote add origin https://github.com/ton-pseudo/mon-projet.git
git remote -v
```

- `git branch -M main` renomme ta branche en `main`, pour qu'elle porte le même nom que celle de GitHub. Si tu as fait la configuration de la section 2, c'est déjà le cas : la commande ne change rien.
- `git remote add origin <adresse>` déclare le dépôt distant et lui donne le nom `origin`. C'est ce que `clone` faisait tout seul dans le tutoriel A.
- `git remote -v` affiche les dépôts distants déclarés, pour vérifier l'adresse.

> **Piège** : une faute dans l'adresse ? `git remote set-url origin <bonne-adresse>` la corrige. Refaire `git remote add` donne une erreur, car `origin` existe déjà.

### B6. Premier push

```bash
git push -u origin main
```

L'option `-u` relie ta branche `main` locale à `main` sur `origin`. C'est nécessaire **une seule fois** : ensuite, `git push`, `git fetch` et `git rebase origin/main` fonctionnent comme dans le tutoriel A. Recharge la page GitHub : ton projet y est, avec son premier commit.

Le projet suit maintenant le cycle de séance de l'étape A5.

> **Essaie** : un camarade clone ton dépôt avec le tutoriel A, étape A2. Vérifiez ensemble que sa solution Visual Studio s'ouvre et compile. Si un fichier manque, c'est qu'il est ignoré à tort par le `.gitignore`, ou qu'il n'a jamais été ajouté.

## 6. Tutoriel C — push refusé : le rebase pas à pas

Situation : tu travailles à deux sur le même dépôt. Tu as fait plusieurs commits, tu tapes `git push`… et GitHub refuse. Ce tutoriel suit un cas réel du début à la fin. Les messages de Git sont en anglais : ils sont reproduits tels quels, pour que tu les reconnaisses à l'écran.

### Le décor

Léa et Tom ont cloné le même dépôt. Il contient un fichier `jeu.txt` :

```text
vitesse = 300;
taille = 20;
couleur = rouge;
```

**Léa** fait deux commits et les pousse la première :

- « Accelere le ballon » : `vitesse = 450;`
- « Ballon bleu » : `couleur = bleu;`

**Tom**, de son côté, sans savoir ce que fait Léa, fait trois commits :

- « Ralentit le ballon » : `vitesse = 200;`
- « Ajoute le score » : un nouveau fichier `score.txt`
- « Ballon vert » : `couleur = vert;`

Tu es Tom.

### C1. Le push est refusé

```bash
git push
```

```text
 ! [rejected]        main -> main (fetch first)
error: failed to push some refs to 'https://github.com/...'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally.
```

GitHub contient des commits que tu n'as pas, ceux de Léa. Il refuse ton `push` pour ne pas les écraser. **Rien n'est perdu**, ni chez toi, ni chez Léa. C'est le fonctionnement normal du travail à plusieurs.

### C2. Regarder la situation

```bash
git fetch
git status
```

```text
Your branch and 'origin/main' have diverged,
and have 3 and 2 different commits each, respectively.
```

Les deux histoires ont **divergé** : tu as 3 commits que GitHub n'a pas, GitHub en a 2 que tu n'as pas.

```text
origin/main :  Premier jeu - Accelere - Ballon bleu
ta branche  :  Premier jeu - Ralentit - Ajoute le score - Ballon vert
```

### C3. Lancer le rebase

```bash
git rebase origin/main
```

Git met tes trois commits de côté, se place sur le dernier commit de Léa, puis **rejoue tes commits un par un, dans l'ordre**. C'est le point à comprendre : le rebase n'est pas une seule opération, c'est **une application par commit**. Chacun peut passer tout seul, ou s'arrêter sur un conflit.

Ici, Git s'arrête dès le premier :

```text
Rebasing (1/3)
CONFLICT (content): Merge conflict in jeu.txt
error: could not apply 4441dfc... Ralentit le ballon
hint: Resolve all conflicts manually, mark them as resolved with
hint: "git add/rm <conflicted_files>", then run "git rebase --continue".
```

Lis ce message ligne par ligne :

- `Rebasing (1/3)` : Git rejoue ton commit **1 sur 3** ;
- `could not apply ... Ralentit le ballon` : c'est **ce commit-là** qui coince, et le message te dit son nom ;
- la dernière ligne donne la marche à suivre : corriger, `git add`, `git rebase --continue`.

> **Astuce** : dans Git Bash, l'invite de commande l'affiche aussi : `(main|REBASE 1/3)`. Tant que tu vois `REBASE`, le rebase n'est pas terminé.

### C4. Comprendre où on en est

```bash
git status
```

```text
interactive rebase in progress; onto d9cdb15
Last command done (1 command done):
   pick 4441dfc Ralentit le ballon
Next commands to do (2 remaining commands):
   pick fadc81c Ajoute le score
   pick cf422ff Ballon vert
...
Unmerged paths:
	both modified:   jeu.txt
```

`git status` est ta carte : le commit en cours (« Ralentit le ballon »), ceux qui restent à rejouer, et les fichiers en conflit (*both modified*).

### C5. Résoudre le premier conflit

Ouvre `jeu.txt` :

```text
<<<<<<< HEAD
vitesse = 450;
=======
vitesse = 200;
>>>>>>> 4441dfc (Ralentit le ballon)
taille = 20;
couleur = bleu;
```

> **Piège** : pendant un rebase, **`HEAD` n'est pas ta version**. `HEAD` désigne ce qui est déjà en place : le travail de Léa (`450`), plus tes commits déjà rejoués. Ta version est **en bas**, sous les `=======`, avec le nom de ton commit (`200`, « Ralentit le ballon »). C'est l'inverse de ce qu'on attend, et la source de la plupart des erreurs.

Remarque aussi la dernière ligne : `couleur = bleu;`. C'est le commit de Léa, déjà en place. Ton « Ballon vert » n'a **pas encore** été rejoué. Ne le rajoute pas à la main maintenant : il viendra à son tour.

Choisis la bonne valeur : la tienne, celle de Léa, ou une troisième après discussion avec elle. Ici, `350`. Puis **supprime les trois lignes de marqueurs** :

```text
vitesse = 350;
taille = 20;
couleur = bleu;
```

Ensuite, marque le fichier comme résolu et continue :

```bash
git add jeu.txt
git rebase --continue
```

> **Piège** : `git rebase --continue` **ouvre un éditeur** pour te laisser modifier le message du commit rejoué. Le message proposé est le bon : il suffit de valider. Dans *Vim*, l'éditeur par défaut de Git pour Windows, tape `:wq` puis `Entrée`. Dans le Bloc-notes ou VS Code, enregistre et ferme le fichier. Tant que l'éditeur est ouvert, le terminal attend.

### C6. Le rebase continue… et s'arrête encore

```text
[detached HEAD 7fe4dba] Ralentit le ballon
Rebasing (2/3)
Rebasing (3/3)
CONFLICT (content): Merge conflict in jeu.txt
error: could not apply cf422ff... Ballon vert
```

Trois choses se sont passées d'un coup :

- le commit 1, « Ralentit le ballon », est enregistré avec ta résolution ;
- le commit 2, « Ajoute le score », est passé **tout seul** : il ne touche que `score.txt`, que Léa n'a pas modifié. Aucun conflit, aucune action de ta part ;
- le commit 3, « Ballon vert », coince à son tour.

C'est normal, et c'est **un nouveau conflit**, différent du premier. Un rebase de N commits peut s'arrêter jusqu'à N fois.

> **Astuce** : `detached HEAD` dans le message n'est pas une erreur. Pendant un rebase, Git travaille temporairement hors de la branche, et il y revient à la fin.

### C7. Résoudre le second conflit

```text
vitesse = 350;
taille = 20;
<<<<<<< HEAD
couleur = bleu;
=======
couleur = vert;
>>>>>>> cf422ff (Ballon vert)
```

Même lecture : en haut, `HEAD`, ce qui est en place (le bleu de Léa) ; en bas, ton commit (le vert). Remarque que `vitesse = 350;` est déjà là : c'est ta résolution du premier conflit, intégrée à `HEAD`. On choisit, on supprime les marqueurs, puis :

```bash
git add jeu.txt
git rebase --continue
```

```text
[detached HEAD c91811b] Ballon vert
Successfully rebased and updated refs/heads/main.
```

`Successfully rebased` : c'est fini. L'invite ne montre plus `REBASE`.

### C8. Vérifier, puis pousser

```bash
git log --oneline
```

```text
c91811b Ballon vert
2b99ef7 Ajoute le score
7fe4dba Ralentit le ballon
d9cdb15 Ballon bleu
df228bb Accelere le ballon
dfb7096 Premier jeu
```

Tes trois commits sont maintenant **après** ceux de Léa, sur une seule ligne. Leurs identifiants ont changé (`4441dfc` est devenu `7fe4dba`) : ce sont des copies rejouées, d'où le nom *rebase*. **Compile et teste** le projet, puis :

```bash
git status
git push
```

`git status` annonce `Your branch is ahead of 'origin/main' by 3 commits` : tu es en avance, plus en divergence. Le `push` passe.

### Les sorties de secours

| Commande | Quand l'utiliser | Ce qu'elle fait |
|---|---|---|
| `git rebase --continue` | après avoir résolu et `git add` les fichiers en conflit | enregistre le commit en cours et passe au suivant |
| `git rebase --abort` | tu es perdu, tu veux tout reprendre | annule **tout** le rebase et te ramène à l'état d'avant `git rebase`, tes commits intacts |
| `git rebase --skip` | rarement : ton commit n'a plus de raison d'être | **jette ton commit en cours** et passe au suivant |

> **Piège** : `--skip` ne veut pas dire « passer ce conflit », il veut dire « abandonner ce commit ». Les modifications de ce commit sont perdues. Dans le doute, `--abort`, jamais `--skip`.

> **Piège** : Git ne vérifie pas que tu as **vraiment** supprimé les marqueurs. Si tu fais `git add` sur un fichier qui contient encore `<<<<<<<`, Git l'accepte et enregistre le fichier tel quel, marqueurs compris. Le projet ne compile plus, et le commit est poussé comme ça. Avant chaque `git add`, cherche `<<<<<<<` dans le fichier.

> **Astuce** : `git rebase --continue` sans avoir fait `git add` ne casse rien : Git refuse et répond `needs merge` / `You must edit all merge conflicts and then mark them as resolved using git add`. Fais le `git add` et recommence.

### Le réflexe à retenir

```text
push refusé
  → git fetch
  → git rebase origin/main
  → pour chaque arrêt :
        git status          (quel commit ? quels fichiers ?)
        corriger le fichier (HEAD = déjà en place, en bas = ton commit)
        supprimer les marqueurs, vérifier
        git add <fichier>
        git rebase --continue   (valider le message : :wq)
  → "Successfully rebased"
  → compiler, tester
  → git push
```

> **Essaie** : reproduis ce scénario avec un camarade, sur un dépôt de test. L'un fait deux commits et pousse. L'autre en fait trois, dont deux touchent les mêmes lignes, puis suit ce tutoriel jusqu'au `push`. Recommencez en inversant les rôles, et cette fois terminez le premier arrêt par `git rebase --abort` pour voir que tout revient comme avant.

## 7. Récapitulatif des commandes

| Commande | Ce qu'elle fait | Touche GitHub ? |
|---|---|---|
| `git status` | état du dossier et de la zone de préparation | non |
| `git add .` | prépare toutes les modifications | non |
| `git commit -m "..."` | enregistre la préparation dans l'historique local | non |
| `git log --oneline` | affiche l'historique | non |
| `git push` | envoie les commits locaux sur GitHub | oui, envoie |
| `git clone <adresse>` | copie un dépôt GitHub dans un nouveau dossier | oui, reçoit |
| `git fetch` | télécharge les nouveaux commits sans toucher aux fichiers | oui, reçoit |
| `git rebase origin/main` | rejoue tes commits par-dessus ceux de GitHub | non |
| `git rebase --continue` | après un conflit résolu et ajouté, passe au commit suivant | non |
| `git rebase --abort` | annule le rebase en cours, retour à l'état d'avant | non |
| `git init` | transforme le dossier courant en dépôt | non |
| `git remote add origin <adresse>` | déclare le dépôt GitHub | non |

## Questions et réponses

**J'ai fait `git add` d'un fichier par erreur. Comment l'enlever de la préparation ?**
`git restore --staged nom-du-fichier`. Le fichier garde ses modifications, il sort seulement de la zone de préparation.

**Mon message de commit contient une faute. Je peux le corriger ?**
Tant que le commit n'est pas poussé : `git commit --amend -m "Nouveau message"`. Une fois poussé, laisse-le : réécrire un historique partagé dérange tes camarades.

**Quelle différence entre `pull` et `fetch` + `rebase` ?**
`git pull` fait `fetch` puis intègre les nouveautés. Selon la configuration, il les intègre par *merge*, qui ajoute un commit de fusion, ou par *rebase*. `git pull --rebase` force le rebase. Faire les deux étapes séparément te laisse voir ce qui arrive avant de l'appliquer.

**Je dois pousser à chaque commit ?**
Non, mais pousse au moins à la fin de chaque séance. Un commit non poussé n'existe que sur ton disque : il n'est ni sauvegardé, ni visible par l'équipe.

**Je peux mettre mes images et mes vidéos dans Git ?**
Les images légères, oui. Les gros fichiers binaires, comme les vidéos ou les rendus, alourdissent chaque clone pour toujours, même après suppression. Ils se gèrent avec des outils dédiés, comme Git LFS, ou hors de Git.

## Exercices

1. **Lire avant de lancer.** Un étudiant tape ceci, puis s'étonne de ne rien voir sur GitHub. Pourquoi ?

   ```bash
   git add .
   git commit -m "Ajoute le score"
   ```

2. **Lire avant de lancer.** Une étudiante a créé son dépôt GitHub en cochant *Add a README file*, puis a suivi le tutoriel B. Son `git push -u origin main` est refusé. Que s'est-il passé, et quelles commandes du cours lui permettent de s'en sortir sans recréer le dépôt ?

3. **À deux, le conflit volontaire** *(plus costaud)*. L'un crée un dépôt avec le tutoriel A et ajoute l'autre comme collaborateur (*Settings → Collaborators*). Chacun clone le dépôt. Modifiez tous les deux **la même ligne** du `README.md`, chacun à sa façon, et commitez. Le premier pousse. Le second fait `git push` (refusé), puis `git fetch`, `git rebase origin/main`, résout le conflit, `git add`, `git rebase --continue`, et pousse, en suivant le tutoriel C. Comparez enfin vos `git log --oneline` : ils doivent être identiques.

## Ce qu'il faut retenir

- **Git** garde l'historique du projet sur ton ordinateur ; **GitHub** en héberge une copie en ligne, le dépôt distant `origin`.
- Une modification suit le chemin **dossier de travail → `add` → zone de préparation → `commit` → historique local → `push` → GitHub**.
- `git status` avant et après chaque commande : c'est le tableau de bord.
- `clone` copie un dépôt une fois ; ensuite `fetch` regarde ce qui a changé et `rebase origin/main` rejoue tes commits par-dessus.
- Un conflit se résout à la main : garder la bonne version, supprimer les marqueurs, `add`, `rebase --continue`. En cas de doute, `rebase --abort`.
- Le rebase rejoue tes commits **un par un** : il peut s'arrêter plusieurs fois, une fois par commit en conflit. Pendant un rebase, `HEAD` est la version déjà en place, ta version est **en bas** des marqueurs.
- Projet neuf : dépôt GitHub **avec** README, puis `clone`. Projet existant : dépôt GitHub **vide**, puis `init`, `.gitignore`, `add`, `commit`, `remote add origin`, `push -u origin main`.
- Le cycle d'une séance : `fetch`, `rebase origin/main`, travailler, `add`, `commit`, `push`.

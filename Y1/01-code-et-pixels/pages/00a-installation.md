---
layout: section
breadcrumb: Installation
---

# Avant de commencer : l'installation

Visual Studio 2026 + openFrameworks, sur Windows

<!--
Le préliminaire de la première séance : tout le monde repart avec un
environnement qui compile. Prévoir le temps de téléchargement (VS + OF,
plusieurs Go) — idéalement lancé en début de séance.
-->

---
layout: split
breadcrumb: Installation / 1. Visual Studio
---

# 1 — Installer Visual Studio 2026

<div class="mt-4 text-sm">

<v-clicks>

- Télécharger l'installeur de **Visual Studio Community 2026** (gratuit) sur `visualstudio.microsoft.com`
- Lancer l'installeur
- Dans l'onglet *Charges de travail*, cocher **« Développement Desktop en C++ »** (*Desktop development with C++*)
- Cliquer sur *Installer* — comptez plusieurs Go

</v-clicks>

</div>

<div v-click class="mt-4 text-sm op-70">
openFrameworks supporte Visual Studio 2022 et 2026 ; on prend 2026.
</div>

::right::

<div>
<ZoomImage src="/install/vs-workload.png" alt="Installeur Visual Studio : la charge de travail Développement Desktop en C++ cochée" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">La charge de travail à cocher (capture du guide openFrameworks — l'installeur 2026 a la même case).</p>
</div>

<!--
La capture vient du guide officiel (installeur d'une version antérieure) :
le nom et l'emplacement de la case sont identiques dans l'installeur 2026.
Community suffit largement ; pas besoin de compte payant.
-->

---
layout: split
breadcrumb: Installation / 1. Visual Studio
---

# 1 bis — Ajouter le composant MSVC v143

<div class="mt-4 text-sm">

<v-clicks>

- Toujours dans l'installeur, passer sur l'onglet **Composants individuels**
- Taper **`v143`** dans le champ de recherche
- Cocher **« MSVC v143 — outils de build C++ VS 2022 x64/x86 (v14.44-17.14) »** — s'il y a plusieurs versions, les cocher
- Puis *Installer* / *Modifier*

</v-clicks>

</div>

<div v-click class="mt-4 text-sm op-70">
Pourquoi : le projet openFrameworks compile avec la chaîne
d'outils <b>v143</b> (celle de VS 2022). Sans ce composant,
Visual Studio 2026 refuse de compiler : <i>« Build Tools for
v143 cannot be found »</i>.
</div>

::right::

<div>
<ZoomImage src="/install/vs-composants-individuels.png" alt="Installeur Visual Studio 2026 : l'onglet Composants individuels et son champ de recherche" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">L'onglet Composants individuels de l'installeur 2026 — taper v143 dans la recherche en haut à gauche.</p>
</div>

<!--
Si VS est déjà installé sans le composant : menu Démarrer → Visual Studio
Installer → Modifier → même onglet. C'est l'oubli le plus fréquent après
la charge de travail C++.
-->

---
layout: split
breadcrumb: Installation / 2. openFrameworks
---

# 2 — Installer openFrameworks

<div class="mt-4 text-sm">

<v-clicks>

- Aller sur **`openframeworks.cc/download`**
- Télécharger la dernière version pour **Windows / Visual Studio** (`of_v0.12.1_vs_64_release.zip` ou plus récente)
- Dézipper dans **`C:\OF`** — un chemin **court**, sans espaces ni accents : Windows limite la longueur des chemins, et OF contient des dossiers profonds

</v-clicks>

</div>

::right::

<div class="text-sm">

<div v-click>

La structure attendue après dézippage :

```text
C:\OF\
├── addons\
├── apps\               ← vos projets iront ici
├── examples\
├── libs\               ← le cœur d'openFrameworks
└── projectGenerator\
```

</div>

<div v-click class="mt-3 op-70">
Vérifiez que <code>libs</code> est bien directement dans
<code>C:\OF\libs</code> — si vous voyez
<code>C:\OF\of_v0.12.1…\libs</code>, remontez le contenu
d'un niveau.
</div>

</div>

<!--
Le piège classique du dézippage : le zip contient un dossier racine
of_v0.12.1_vs_64_release — il faut que SON contenu soit dans C:\OF,
pas le dossier lui-même. (Attention : le dossier s'appelle libs, avec un s.)
-->

---
layout: split
breadcrumb: Installation / 3. Project Generator
---

# 3 — Créer un projet avec le Project Generator

<div class="mt-4 text-sm">

<v-clicks>

- Lancer **`C:\OF\projectGenerator\projectGenerator.exe`**
- **Project name** : le nom de votre projet
- **Project path** : `C:\OF\apps\myApps` (le défaut)
- **Platforms** : *Windows (Visual Studio)*
- **Template** : sélectionner **`vs2026`** — vide, il génère pour VS 2022
- **Generate**, puis *Open in IDE*

</v-clicks>

</div>

::right::

<div>
<ZoomImage src="/install/project-generator.png" alt="Project Generator : plateforme Windows Visual Studio et template vs2026" class="h-95 object-contain mx-auto" />
<p class="mt-2 text-xs op-60">Le réglage qui compte pour nous : Template = vs2026.</p>
</div>

<!--
Le Project Generator crée le dossier du projet avec le .sln, src/ (main.cpp,
ofApp.h, ofApp.cpp) et bin/. C'est lui aussi qui ajoutera les addons plus
tard dans l'année.
-->

---
layout: split
breadcrumb: Installation / 4. Vérifier
---

# 4 — Vérifier que tout compile

<div class="mt-4 text-sm">

<v-clicks>

- Le `.sln` s'ouvre dans Visual Studio ; dans `src/` : `main.cpp`, `ofApp.h`, `ofApp.cpp`
- Lancer avec **Local Windows Debugger** (ou `F5`) — la première compilation est longue, c'est normal : OF se compile une fois
- Une **fenêtre grise vide** s'ouvre : gagné.

</v-clicks>

</div>

<div v-click class="mt-4 text-sm">

Pour suivre les cours : copier la paire `ofAppNN.h` /
`ofAppNN.cpp` dans `src\`, et dans `main.cpp` remplacer
l'include par `#include "ofAppNN.h"`.

</div>

::right::

<div>
<ZoomImage src="/install/vs-projet.png" alt="Visual Studio 2026 avec un projet openFrameworks généré ouvert" class="w-full object-contain" />
<p class="mt-2 text-xs op-60">Le projet généré, ouvert dans Visual Studio 2026.</p>
</div>

<p class="ndp-credit">📄 <a href="/ressources/cours/pdf/00-environnement.pdf" download>tutoriel complet (PDF)</a> · <a href="/ressources/cours/00-environnement.md" download>md</a> · Captures : guide openFrameworks (MIT) et documentation Visual Studio (CC BY 4.0, learn.microsoft.com)</p>

<!--
Si la compilation échoue dès le départ : 90 % du temps, c'est le dézippage
(structure C:\OF\libs absente) ou la charge de travail C++ pas installée.
Reprendre les étapes 1 et 2 dans l'ordre.
-->

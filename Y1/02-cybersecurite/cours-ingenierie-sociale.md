# Introduction à l'ingénierie sociale

> **Module :** Cybersécurité — Hacking éthique
> **Source principale :** *Sécurité informatique — Ethical Hacking : Apprendre l'attaque pour mieux se défendre*, chapitre 2 « Éléments d'ingénierie sociale »
> **Objectif :** comprendre comment un attaquant exploite les failles humaines d'un système d'information, pour savoir les détecter et s'en protéger.

---

## Objectifs pédagogiques

À l'issue de ce cours, vous serez capable de :

- définir l'ingénierie sociale appliquée à la sécurité des SI ;
- distinguer les quatre grandes familles de failles d'un système d'information ;
- décrire les principes et le déroulement type d'une attaque par ingénierie sociale ;
- identifier les principaux biais cognitifs et ressorts d'influence exploités ;
- reconnaître les techniques de manipulation classiques et les contre-mesures associées.

> ⚠️ **Cadre éthique et légal.** Les connaissances de ce cours servent à **défendre** une organisation (sensibilisation, audit autorisé, red team contractualisée). Toute mise en œuvre sans mandat écrit est illégale (accès frauduleux à un STAD, usurpation d'identité, escroquerie — Code pénal art. 323-1 et suivants, 226-4-1, 313-1).

---

## 1. Généralités

### 1.1 Définition

Au sens large, l'ingénierie sociale désigne l'art d'**influencer des êtres humains**, individuellement ou en groupe. En sécurité des SI, le terme (traduction littérale de *social engineering*) a un sens restreint :

> **L'ingénierie sociale est une méthodologie d'investigation, d'influence et d'actions clandestines visant à compromettre un système d'information en exploitant principalement ses failles humaines.**

Concrètement, l'attaquant cherche à **provoquer chez une cible un comportement précis** : donner une information, effectuer une opération sensible, cliquer sur un lien, ouvrir une porte…

**Idée clé :** l'ingénierie sociale n'est pas un « don » ou du charisme inné. Les attaquants ont intérêt à entretenir ce mythe (il rend la défense plus difficile et leur donne une aura). En réalité, c'est une compétence qui **se modélise et s'apprend** — et donc qui se contre.

### 1.2 Système d'information ≠ système informatique

| Système d'information (SI) | Système informatique |
|---|---|
| Ensemble de moyens **humains, organisationnels et technologiques** pour acquérir, stocker, traiter, protéger, transmettre et diffuser l'information | Sous-ensemble **outillé** (matériel, logiciels, réseaux) du SI |
| Existe depuis l'invention de l'écriture (scribes, administrations, armées…) | Récent |

Confondre les deux, c'est **oublier les failles humaines et organisationnelles** — exactement là où frappe l'ingénieur social.

### 1.3 Les quatre familles de failles d'un SI

| Famille | Exemples |
|---|---|
| **Techniques / informatiques** | Vulnérabilités logicielles, mauvaise configuration |
| **Structurelles / physiques** | Accès aux locaux, supports contenant de l'information (papiers, disques) |
| **Humaines / psychologiques** | Biais cognitifs, émotions, besoin de reconnaissance |
| **Organisationnelles / managériales** | Processus flous, responsabilités mal définies, absence de procédure de vérification |

Les attaques réelles combinent souvent plusieurs familles : la plus efficace est rarement la plus technique.

### 1.4 Caractéristiques de l'ingénierie sociale

- **Vision non focalisée sur le SI** : l'attaquant considère le système dans son **environnement** — entrées/sorties humaines (téléphone, e-mails, courriers, accueil, salons, entretiens d'embauche, réseaux sociaux, poubelles, post-it…). Le maillon faible se situe souvent aux **interstices** entre sous-systèmes.
- **Risques atypiques** : le facteur humain rend les probabilités difficiles à chiffrer ; le résultat dépend du contexte et de la maturité de la cible.
- **Ressources réduites** : faible investissement initial, souvent un individu seul ou une très petite équipe. C'est une **stratégie du faible au fort**.
- **Méthodes douces** : l'attaquant évite la violence, la coercition ou l'effraction (traces, risques juridiques) et privilégie l'influence discrète.
- **Situations évolutives** : nécessité d'improviser et de réévaluer en temps réel ; l'opportunisme compte autant que la planification.

### 1.5 La problématique de la protection

- La défense contre l'ingénierie sociale est perçue comme **coûteuse et peu productive** ; le marché de la SSI reste dominé par les solutions techniques.
- On entend souvent : « l'humain est le maillon faible », « il n'y a pas de patch pour la bêtise humaine ». Ce discours est **contre-productif** :
  - les victimes ne sont pas stupides — **tout le monde est faillible** dans des conditions favorables à l'attaquant ;
  - stigmatiser les victimes les pousse à **cacher les incidents** ;
  - les failles humaines ont des **raisons biologiques** et des moyens existent pour les réduire (formation, procédures, culture de signalement).
- Les failles humaines sont souvent **exploitables grâce à des failles organisationnelles** : la réponse doit aussi être managériale.

---

## 2. Modes d'action de l'ingénierie sociale

### 2.1 Principes de l'attaque

L'ingénierie sociale reprend des principes proches de ceux de la stratégie militaire :

| Principe | Signification |
|---|---|
| **Liberté d'action** | Rester discret, invisible le plus longtemps possible, gérer les risques et pouvoir effacer ses traces |
| **Unité de commandement** | Un seul décideur, des processus de décision clairs, chacun sait qui donne les ordres |
| **Économie de moyens** | Choisir la simplicité, l'efficacité, la réutilisation |
| **Effet levier** | Exploiter une information anodine (organigramme, jargon, nom d'un responsable) pour en obtenir d'autres plus sensibles, de proche en proche |
| **Adaptation à l'environnement** | Utiliser les moyens de communication de l'époque (téléphone, e-mail, réseaux sociaux, messageries…) |

> 💡 **L'effet levier** (popularisé par Kevin Mitnick) est central : chaque information obtenue rend la suivante plus facile à obtenir, car elle crédibilise l'attaquant.

### 2.2 Processus générique d'une attaque

Contrairement à l'image véhiculée par la fiction, une attaque sérieuse est **planifiée**. On peut la découper en trois phases :

```
┌──────────────────┐    ┌──────────────────┐    ┌──────────────────┐
│ 1. ÉTUDE         │ →  │ 2. PRÉPARATION   │ →  │ 3. EXPLOITATION  │
│   PRÉALABLE      │    │                  │    │                  │
│ Recherche OSINT  │    │ Scénario         │    │ Contact          │
│ Faisabilité      │    │ Répétition       │    │ Élicitation      │
│ Analyse risque   │    │ Préparation      │    │ Camouflage final │
│ Objectifs        │    │ mentale          │    │ Validation       │
└──────────────────┘    └──────────────────┘    └──────────────────┘
        Engagement et risque croissants →
```

#### Phase 1 — Étude préalable

- **Collecte d'« informations blanches »** : informations ouvertes, publiques (sites web, registre du commerce, presse, réseaux sociaux, offres d'emploi, plaquettes, organigrammes affichés…). C'est l'équivalent de l'**OSINT**.
- **Étude de faisabilité et d'opportunité** : vulnérabilité apparente et maturité de la cible, procédures de défense probables, liste des interlocuteurs (fournisseurs, clients…).
- **Bénéfices attendus** et **contraintes** (financières, légales, morales).
- **Analyse de risque** : selon ISO 27001, risque = combinaison de la probabilité d'un événement et de ses conséquences. Définition d'indicateurs d'alerte et de critères *Go / No Go / Arrêt*.
- **Définition des objectifs** : quelles informations, quels objectifs intermédiaires (« informations grises »), quels effets levier, comment valider l'information ?

#### Phase 2 — Préparation

- **Élaboration du scénario d'attaque** : choix des cibles, du langage (jargon), des effets levier, réponses aux questions *qui, quoi, pourquoi, comment, où, quand*.
- **Canevas et aide-mémoire** : glossaire, organigramme, points clés pour rester fluide.
- **Répétition générale / prototypage** : tester le scénario, anticiper les réactions de la cible.
- **Préparation mentale et émotionnelle** : entrer dans le personnage.

#### Phase 3 — Exploitation

- **Approche** : premier contact, souvent le moment le plus délicat ; il pose les bases de crédibilité.
- **Élicitation** : obtenir l'information, souvent en noyant la vraie demande parmi des questions anodines.
- **Camouflage final** : faire en sorte que la cible ne se souvienne pas de l'échange ou n'en mesure pas l'importance. Une information n'a de valeur que tant que l'attaque n'est pas détectée.
- **Validation et recoupement** : vérifier l'information par plusieurs sources.

### 2.3 Compétences de l'ingénieur social

- **Comédie, ruse, subterfuge** : jouer un personnage crédible, cohérent, être capable d'improviser (proche de l'improvisation théâtrale).
- **Lecture de cible** : « typer » rapidement un interlocuteur pour adapter son approche.
- **Lecture des feedbacks** : indicateurs verbaux, non verbaux, posturaux de l'efficacité de son influence (cf. travaux de Paul Ekman).

Il n'est pas nécessaire d'être expert en psychologie, sociologie ou management : quelques outils simples et éprouvés suffisent. C'est ce qui rend la menace **accessible** — et donc fréquente.

---

## 3. Connaissance des organisations attaquées

Pour paraître légitime (employé, client, fournisseur, prestataire de maintenance…), l'attaquant doit **modéliser l'organisation ciblée** : on ne parle pas de la même façon à un cadre de multinationale, à un agent municipal ou au bénévole d'une association.

### 3.1 Typologie générale

Trois grandes finalités : **administrations** (servir le public / l'État), **entreprises** (profit, survie), **associations** (buts ludiques, militants, caritatifs). À croiser avec la taille, l'éclatement géographique, les filiales, les services.

### 3.2 Valeurs et culture

Toute organisation possède une **culture** (valeurs, croyances, jargon, rituels) transmise de proche en proche. Le livre propose une grille simplifiée inspirée de la « spirale dynamique » :

| Type | Valeurs dominantes | Langage |
|---|---|---|
| **Clanique** | Famille, tradition, ancienneté | Respect, rituels |
| **Tyrannique** | Force, honneur, réussite individuelle | Domination, rapport de force |
| **Hiérarchique** | Ordre, règles, obéissance | Autorité, procédures |
| **Productiviste** | Efficacité, compétition, argent, autonomie | Performance, opportunité |
| **Harmonieux** | Consensus, égalité, communauté | Collectif, bienveillance |

> 📝 La spirale dynamique est un **modèle de vulgarisation**, non validé scientifiquement. Il est utile ici comme grille de lecture, pas comme vérité.

### 3.3 Maturité et certifications

Les certifications (ISO 9001, CMMI…) sont des sources d'information **faciles à trouver** : elles révèlent processus et vocabulaire internes. Attention : une certification affichée n'implique pas une maturité réelle.

### 3.4 Exploitation

Connaître le jargon, les codes et les valeurs permet à l'attaquant d'aborder la cible avec le bon registre et de détecter les **failles organisationnelles** (processus non suivis, zones de responsabilité floues).

---

## 4. Failles humaines : bases et modèles

### 4.1 Le cerveau, un système optimisé… donc exploitable

Notre cerveau est **rapide, économe et résilient**, optimisé pour les situations courantes. Il utilise des **heuristiques** (raccourcis mentaux) plutôt qu'un raisonnement exhaustif. Hors de sa zone de confort (surcharge, urgence, situation atypique), il devient facile à leurrer.

Le livre utilise le modèle du cerveau « triunique » (centres **instinctif**, **émotionnel**, **mental**) comme grille fonctionnelle.

> 📝 Ce modèle est **abandonné en neurosciences** ; il reste ici un outil pédagogique pour décrire la tension entre réaction rapide/émotionnelle et réflexion. On peut lui préférer le modèle *Système 1 / Système 2* de Daniel Kahneman.

### 4.2 Les biais cognitifs exploités

| Catégorie | Principe | Exemple d'exploitation |
|---|---|---|
| **Perception** | Contrastes, comparaisons, valeurs extrêmes faussent l'estimation | Présenter une demande comme « petite » après une énorme |
| **Attention** | Surcharge, distraction, confusion, focalisation | Appeler en pleine période de clôture |
| **Mémoire** | Primauté, récence, faux souvenirs | Placer la vraie question au milieu de l'échange pour qu'elle soit oubliée |
| **Jugement** | Erreurs liées à l'expertise, angles morts | « Je connais ce système, ce n'est pas risqué » |
| **Raisonnement** | Besoin de cohérence, dissonance cognitive, engagement, disponibilité de l'information | On rationalise après coup une décision déjà prise |
| **Liés à la personne** | Caractère, culture, langue | Adapter l'approche au profil de la cible |

### 4.3 Cohérence et recherche de « pattern »

Notre cerveau cherche **en permanence** des liens logiques, même là où il n'y en a pas (mieux vaut un faux positif qu'un danger ignoré). Ce **besoin de cohérence** est l'un des moteurs les plus puissants — et l'un des pièges les plus exploités.

### 4.4 Conclusion

Le cerveau n'est pas un ordinateur : il décide souvent de façon instinctive ou émotionnelle, la raison venant justifier *a posteriori*. Il présente donc de nombreux « **backdoors** ». C'est en plaçant la cible **hors de ses conditions normales** (urgence, stress, fatigue, surcharge) que l'attaquant maximise ses chances.

---

## 5. Influence et manipulation

### 5.1 Vocabulaire

- **Influence** : obtenir un changement quelconque dans les conceptions, croyances, motivations ou comportements d'une cible. Notion très large (publicité, pédagogie, management, autorité légitime…).
- **Ressorts externes / internes / internalisés** :
  - *externe* : indépendant de la cible (une récompense) ;
  - *interne* : propre à la cible (la conscience professionnelle) ;
  - *internalisé* : externe devenu interne (l'espoir d'une nouvelle récompense).
  Les ressorts internes produisent des effets **plus durables**.
- **Tentation** : obtenir un comportement en promettant une contrepartie attirante (réelle ou non). La **séduction** en est une forme.
- **Intimidation** : obtenir un comportement en évoquant les conséquences désagréables d'un refus.
  → Tentation et intimidation reposent sur des ressorts externes, laissent des **traces** et sont donc utilisées avec parcimonie.
- **Manipulation** (au sens de la psychologie sociale, Beauvois & Joule) : ensemble des techniques visant à obtenir un comportement **sans que la cible ait conscience** des objectifs réels ni des conséquences, en s'appuyant sur ses ressorts internes.

### 5.2 Les six grands ressorts (Robert Cialdini) et leur défense

Ces ressorts ne sont pas des techniques en soi mais **le moteur** des techniques. Les connaître est le bon niveau pour se défendre.

| Ressort | Mécanisme | Exploitation typique | Défense |
|---|---|---|---|
| **Cohérence / engagement** | On persiste dans ce qu'on a commencé, surtout si l'engagement était libre, coûteux, explicite | Petites demandes successives | Écouter les signaux d'alerte corporels (malaise, « boule au ventre ») ; se demander « referais-je ce choix aujourd'hui ? » |
| **Réciprocité** | Pulsion à rendre une faveur reçue | Conseil gratuit, aide spontanée, fausse concession, « je vous dépanne » | Réévaluer la valeur réelle de la faveur ; une faveur non sollicitée n'engage pas |
| **Preuve sociale** | On imite le groupe en situation d'incertitude | « Tout le monde l'a déjà fait », faux consensus | Remettre en cause la validité des preuves présentées ; débrayer le « pilote automatique » |
| **Autorité** | On se soumet à une figure d'autorité, surtout sous stress (cf. expérience de Milgram) | Se faire passer pour la direction, le support IT, la police ; *name-dropping* | **Authentifier** l'identité et la légitimité de la demande par un canal indépendant ; relativiser l'urgence |
| **Sympathie** | On aide plus volontiers ceux qu'on apprécie | Compliments, similarité, connivence | Accepter la sympathie mais **séparer la personne de sa requête** ; évaluer coût et risque objectivement |
| **Rareté** | On valorise ce qui semble limité | « Offre valable 1 heure », « dernier accès disponible » | Contrôler la réaction émotionnelle (frustration) ; se demander pourquoi on veut vraiment la ressource |

> 🔑 **Règle générale de défense** : la détection d'une manipulation est nécessaire mais **pas suffisante**. Il faut ensuite *ralentir* (gagner du temps, respirer), *revenir au raisonnement* et *vérifier*.

---

## 6. Les techniques de manipulation

La typologie reprend celle de Beauvois et Joule (*Petit traité de manipulation à l'usage des honnêtes gens*). On distingue les **grandes techniques** (la trame de l'opération) et les **petites techniques** (l'habillage qui en augmente l'efficacité).

### 6.1 Grandes techniques

#### L'amorçage et le leurre

On obtient l'accord de la cible **avant** qu'elle dispose de toutes les informations. Une fois engagée, elle tend à persévérer même quand les conditions réelles apparaissent.

- Forme simple : « Je peux te demander un truc ? »
- Forme élaborée : faire accepter de répondre à « un petit questionnaire » sans préciser sa longueur.

#### Le pied dans la porte

Une **première demande peu coûteuse**, presque certainement acceptée, puis une seconde plus coûteuse — qui a davantage de chances d'être acceptée.
- La difficulté : calibrer la première demande (facile à accepter mais suffisamment engageante).
- Le timing compte : la seconde demande peut venir immédiatement ou lors d'un second contact.

#### La porte au nez

L'inverse : une **première demande excessive**, refusée, puis la demande réellement visée, qui paraît raisonnable par **contraste** et par **réciprocité** (l'attaquant « a fait une concession »).

### 6.2 Petites techniques

| Technique | Principe |
|---|---|
| **Pied dans la bouche, politesse, sympathie** | Noyer la cible d'attentions et de marques d'intérêt ; agit sous le seuil conscient |
| **Contact, toucher, regard** | Créer une proximité sensorielle (ton de voix, regard) qui favorise sympathie et réciprocité |
| **Pièges de la cohérence** | Exploiter la dissonance cognitive et la **rationalisation** : faire exprimer à la cible les raisons de son action pour renforcer ses futurs comportements |
| **Étiquetage** | Attribuer une qualité à la cible (« Vous êtes quelqu'un de serviable ») pour qu'elle s'y conforme — effet auto-réalisateur |
| **Déclaration de liberté** | « Vous faites comme vous voulez » : renforce le sentiment de liberté, donc l'engagement et la responsabilité perçue |

---

## 7. Synthèse défensive

Ce que doit retenir un administrateur, un développeur ou un futur RSSI :

1. **Procédures de vérification** : toute demande sensible (mot de passe, virement, accès, information interne) doit être confirmée par un **canal indépendant** (rappel sur un numéro connu, ticket, validation hiérarchique).
2. **Limiter les informations blanches** : maîtriser ce qui est publié (organigrammes, noms, technologies utilisées, offres d'emploi trop détaillées).
3. **Sensibiliser sans stigmatiser** : former régulièrement, simuler (phishing, appels) dans un cadre bienveillant, **valoriser le signalement**.
4. **Combler les failles organisationnelles** : responsabilités claires, droit explicite de refuser une demande non conforme, même venant d'une « autorité ».
5. **Se méfier des déclencheurs** : urgence, autorité, flatterie, rareté, faveur non sollicitée → signal pour **ralentir et vérifier**.
6. **Gérer les supports physiques** : destruction des documents, politique de bureau propre, contrôle d'accès aux locaux.

---

## 8. Exercices

### Exercice 1 — Fiches organisations

Choisissez trois organisations très différentes que vous connaissez (par exemple : une grande entreprise, une mairie, une association). Pour chacune, rédigez une fiche récapitulative :

- statut et éléments légaux ;
- organisation, organigramme connu ;
- implantation géographique, taille ;
- partenaires, clients, fournisseurs ;
- type d'organisation et niveau de maturité estimé ;
- valeurs et croyances dominantes ;
- points d'entrée/sortie humains du SI ;
- **pour chaque point d'entrée : une contre-mesure**.

### Exercice 2 — Le cas du téléphone

Le téléphone reste un outil privilégié des attaquants (vishing). En vous appuyant sur ce cours, listez les avantages qu'il offre à un attaquant (principes, biais, ressorts) puis, pour chacun, la mesure défensive correspondante.

### Exercice 3 — Discrétion et mémoire

À partir des biais de mémoire (primauté, récence, ancrage émotionnel), expliquez pourquoi un attaquant place sa vraie question au milieu d'un échange anodin. Déduisez-en des **bonnes pratiques pour la victime** (prise de notes, signalement, relecture des échanges).

### Exercice 4 — Identifier les ressorts

Analysez un e-mail de phishing réel (fourni par l'enseignant) et identifiez : les ressorts de Cialdini mobilisés, la ou les techniques de manipulation, les indices permettant de le détecter.

---

## Pour aller plus loin

- Robert Cialdini, *Influence et manipulation*
- Jean-Léon Beauvois & Robert-Vincent Joule, *Petit traité de manipulation à l'usage des honnêtes gens*
- Kevin Mitnick, *The Art of Deception* et *The Art of Intrusion*
- Daniel Kahneman, *Système 1 / Système 2*
- Paul Ekman, travaux sur les expressions faciales et le non-verbal
- ANSSI / Cybermalveillance.gouv.fr : guides de sensibilisation à l'hameçonnage et à la fraude au président

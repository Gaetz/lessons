# Cours 06 quater — Fonctions : « Histoire à trous »

> **Avant** : cours 06 bis (conditions, `while`, `rand`) et 06 ter (`string`, `vector`, objets).
> **Comment travailler** : comme aux cours 06 bis et 06 ter, ce sont des **programmes console** — pas d'openFrameworks. Dans Visual Studio, crée un projet *Application console* et écris chaque programme dans son `main.cpp`, un programme à la fois. Lance avec `F5`.

Tous les programmes console que tu as écrits jusqu'ici tenaient dans une seule fonction : `main()`. Passé une certaine taille, un programme écrit comme ça devient impossible à suivre. La parade existe depuis les débuts de la programmation : **découper** le programme en petits morceaux, chacun avec un nom et un rôle. En C++, ces morceaux sont des **fonctions** — tu en appelles depuis le cours 00 (`ofDrawCircle`, `rand()`, `phrase.size()`), ici tu écris les tiennes. Tu vas apprendre à :

- écrire de nouvelles fonctions ;
- leur passer des valeurs par des **paramètres** ;
- en récupérer un résultat par une **valeur de retour** ;
- comprendre la **portée** des variables, et manier variables et constantes globales ;
- donner des **arguments par défaut** à une fonction, et la **surcharger**.

À la fin, tout s'assemble dans un jeu de mots : **« Histoire à trous »** — le programme te demande un nom, un verbe, un nombre… et t'en fait une histoire.

Comme aux 06 bis et 06 ter, chaque programme est suivi d'un **Exercice** à écrire toi-même. C'est là que ça rentre.

## 1. Étape 1 — créer une fonction : les instructions

Tes propres fonctions marchent exactement comme celles de la bibliothèque standard : on les appelle, elles font leur travail, elles rendent la main. Le programme suivant n'affiche que deux lignes de texte — tu aurais pu l'écrire au cours 04. La nouveauté est derrière : ces lignes sont affichées par une fonction à nous.

```cpp
// Instructions
// Ecrire une nouvelle fonction

#include <iostream>
using namespace std;

// prototype (declaration) de la fonction
void instructions();

int main()
{
    instructions();
    return 0;
}

// definition de la fonction
void instructions()
{
    cout << "Bienvenue dans le jeu le plus amusant jamais ecrit en texte !\n\n";
    cout << "Voici comment jouer...\n";
}
```

### Déclarer une fonction

Avant d'appeler une fonction que tu as écrite, il faut la **déclarer**. La façon la plus courante est d'écrire un **prototype** : une ligne qui décrit la fonction — son **type de retour** (ou `void` si elle ne renvoie rien), son **nom**, puis sa liste de **paramètres** entre parenthèses, et un point-virgule. Juste avant `main()` :

```cpp
void instructions();
```

Ce prototype déclare une fonction `instructions` qui ne renvoie rien (`void`) et ne reçoit rien (parenthèses vides). C'est l'**annonce** que tu écrivais déjà dans le `.h` d'openFrameworks : une ligne sans corps, pour que le compilateur connaisse la fonction avant de la rencontrer.

Le prototype n'est pas la seule façon de déclarer : si la **définition** complète de la fonction est écrite *avant* son premier appel, elle sert elle-même de déclaration. Mais le prototype a un gros avantage : il rend le code plus clair, et laisse `main()` en tête du fichier.

### Définir une fonction

**Définir** la fonction, c'est écrire le code qui la fait marcher. L'**en-tête** reprend le prototype sans le point-virgule — type de retour, nom, paramètres —, puis un bloc entre accolades contient les instructions : c'est le **corps** de la fonction.

```cpp
void instructions()
{
    cout << "Bienvenue dans le jeu le plus amusant jamais ecrit en texte !\n\n";
    cout << "Voici comment jouer...\n";
}
```

Comme `instructions()` ne renvoie rien, pas besoin de `return` comme dans `main()` : l'accolade fermante termine la fonction.

> **Piège** : la définition doit **correspondre** au prototype — même type de retour, même nom. Sinon, erreur de compilation.

### Appeler une fonction

On appelle sa propre fonction comme n'importe quelle autre : son nom, suivi de parenthèses contenant les arguments (ici, aucun) :

```cpp
instructions();
```

À cet appel, le programme **saute** dans `instructions()`, en exécute le corps — les deux lignes de texte — puis **revient** là où il était : la ligne suivante de `main()`, `return 0;`, et le programme se termine.

### L'abstraction

En écrivant et en appelant des fonctions, tu pratiques l'**abstraction** : penser à la grande image sans te soucier des détails. Dans `main()`, j'utilise `instructions()` sans me demander comment le texte s'affiche. Une ligne, et c'est fait.

Les gens utilisent l'abstraction tout le temps. Dans un fast-food, quand un employé dit à l'autre « un menu numéro 3, en grand », l'autre comprend : prendre la commande, aller chercher le burger sous la lampe, remplir la plus grande boîte de frites, tirer le plus grand soda, encaisser, rendre la monnaie. Ce niveau de détail serait assommant — et inutile : les deux savent ce que veut dire « un numéro 3, en grand ». C'est de l'abstraction.

> **Essaie** : ajoute une seconde fonction `void auRevoir();` qui affiche « Merci d'avoir joue ! », et appelle-la en fin de `main()`. Puis déplace la définition de `instructions()` *avant* `main()` et supprime son prototype : ça compile toujours. Remets le prototype — c'est la forme qu'on garde.

> **Exercice — la bannière** *(nouveau programme)* :
>
> 1. écris une fonction `void ligne();` qui affiche vingt `=` suivis d'un retour à la ligne (un `for` du cours 06 ter, pas vingt `cout`) ;
> 2. écris une fonction `void titre();` qui appelle `ligne()`, affiche `  MON JEU  `, puis appelle `ligne()` encore ;
> 3. dans `main()`, appelle `titre()`. Trois fonctions, dont une qui en appelle une autre : c'est normal, et c'est le début de tout programme un peu long.

## 2. Étape 2 — paramètres et valeur de retour : oui ou non

Avec les fonctions de la bibliothèque, tu fournis une valeur et tu en reçois une : `rand()` te rend un nombre, `phrase.find("Over")` reçoit une chaîne et rend une position. Tes fonctions peuvent faire pareil, et c'est ce qui leur permet de **communiquer** avec le reste du programme. Le programme suivant pose deux questions typiques d'un jeu : une question générique, puis « Veux-tu sauvegarder ta partie ? ». Chaque question est posée par une fonction différente, qui rend la réponse à `main()`.

```cpp
// Oui ou non
// Valeurs de retour et parametres

#include <iostream>
#include <string>

using namespace std;

string demanderOuiNon1();
string demanderOuiNon2(string question);

int main()
{
    string reponse1 = demanderOuiNon1();
    cout << "Merci d'avoir repondu : " << reponse1 << "\n\n";

    string reponse2 = demanderOuiNon2("Veux-tu sauvegarder ta partie ?");
    cout << "Merci d'avoir repondu : " << reponse2 << "\n";

    return 0;
}

string demanderOuiNon1()
{
    string reponse;
    cout << "Tape 'o' ou 'n' : ";
    cin >> reponse;
    while (reponse != "o" && reponse != "n")
    {
        cout << "Tape 'o' ou 'n' : ";
        cin >> reponse;
    }
    return reponse;
}

string demanderOuiNon2(string question)
{
    string reponse;
    cout << question << " (o/n) : ";
    cin >> reponse;
    while (reponse != "o" && reponse != "n")
    {
        cout << question << " (o/n) : ";
        cin >> reponse;
    }
    return reponse;
}
```

### Renvoyer une valeur

Pour qu'une fonction **renvoie** une valeur à son appelant, deux choses : annoncer un **type de retour**, et **renvoyer** une valeur de ce type avec `return`.

Le type de retour, c'est le mot devant le nom : `demanderOuiNon1()` renvoie une `string`. On le lit dans le prototype comme dans l'en-tête de la définition :

```cpp
string demanderOuiNon1();
```

La fonction demande `o` ou `n` et redemande tant qu'elle n'a pas l'un des deux — le motif du cours 06 bis : une première lecture avant la boucle, une relecture dans la boucle, et le `while` qui compare. Une fois la réponse valable, la fonction se termine par :

```cpp
return reponse;
```

`reponse` est une `string` : c'est ce que le prototype a **promis** de renvoyer, le compilateur y veille. Une fonction se termine dès qu'elle rencontre un `return` — elle peut donc en contenir plusieurs, autant de points de sortie possibles.

> **Astuce** : `return` tout seul, sans valeur, est permis dans une fonction `void` : il la termine sur place.

Dans `main()`, l'appel sert de valeur, qu'on range dans une variable :

```cpp
string reponse1 = demanderOuiNon1();
```

`reponse1` reçoit `"o"` ou `"n"` — ce que l'utilisateur a tapé. La ligne suivante l'affiche.

### Recevoir des valeurs : les paramètres

La façon la plus courante de **donner** une information à une fonction est de la passer dans un **paramètre**. La seconde fonction en déclare un, de type `string` :

```cpp
string demanderOuiNon2(string question);
```

> **Astuce** : dans un prototype, le nom du paramètre est facultatif — `string demanderOuiNon2(string);` est valable. Mais le garder rend le code plus clair, et ça ne coûte qu'un mot.

Dans la **définition**, en revanche, le nom est obligatoire : c'est par lui qu'on utilise la valeur reçue. Dans le corps, `question` se comporte comme n'importe quelle variable :

```cpp
cout << question << " (o/n) : ";
```

> **Piège** : les **types** des paramètres doivent être les mêmes dans le prototype et dans la définition. Sinon, erreur de compilation.

L'appel fournit la valeur — c'est l'**argument** :

```cpp
string reponse2 = demanderOuiNon2("Veux-tu sauvegarder ta partie ?");
```

La chaîne littérale est copiée dans `question`, la fonction pose cette question-là, redemande jusqu'à `o` ou `n`, et renvoie la réponse, que `main()` range dans `reponse2`. Cette seconde fonction est bien meilleure que la première : la même fonction pose **n'importe quelle** question, il suffit de la lui passer.

> **Astuce** : `demanderOuiNon2` est exactement le genre de fonction qu'on **réutilise** d'un programme à l'autre. Poser une question oui / non, demander un nombre dans un intervalle, afficher une bannière : écris-les une fois, bien, et garde-les. C'est la *réutilisation* — les studios en font une règle d'or : un module testé et performant se reprend tel quel plutôt que de le réécrire, avec ses bugs, à chaque jeu. Le cours 08 te montrera comment répartir un programme en plusieurs fichiers pour ça.

### L'encapsulation

Pourquoi une valeur de retour ? Pourquoi ne pas lire directement `reponse` depuis `main()` ? Parce que c'est **impossible** : `reponse` n'existe pas en dehors de la fonction qui l'a déclarée. Aucune variable créée dans une fonction, ses paramètres compris, n'est accessible de l'extérieur. C'est voulu, et ça s'appelle l'**encapsulation** : chaque fonction garde ses détails pour elle, et n'échange avec le reste que ce qui doit l'être — par ses paramètres et sa valeur de retour. Avantage énorme quand le programme grossit : tu n'as pas à te soucier des variables des autres fonctions.

Encapsulation et abstraction se ressemblent, et c'est normal : l'encapsulation est un principe de l'abstraction. L'abstraction t'épargne les détails ; l'encapsulation te les **cache**. Une télécommande : tu montes le volume sans savoir ce qui se passe dans le téléviseur (abstraction). Et tu ne peux pas régler directement « volume 7 » : seulement appuyer sur + et − jusqu'à y arriver — le numéro de volume est encapsulé, hors de ta portée.

> **Essaie** : dans `demanderOuiNon2`, accepte aussi `oui` et `non` (deux `!=` de plus, avec `&&`). Puis supprime la première fonction : `main()` peut poser sa question générique avec la seconde — laquelle ?

> **Exercice — le vérificateur** *(nouveau programme)* :
>
> 1. écris `bool estPair(int n);` qui renvoie `true` si `n` est pair — le `%` du cours 06 bis, et un `return` qui renvoie directement le résultat de la comparaison ;
> 2. écris `string demanderTexte(string question);` : affiche la question, lit un mot, le renvoie ;
> 3. dans `main()`, demande un prénom avec `demanderTexte`, puis affiche `Ton prenom a un nombre pair de lettres` ou `impair` selon `estPair(prenom.size())` — un appel de fonction en argument d'un autre, c'est permis ;
> 4. bonus : `bool estVoyelle(char c);` et une boucle qui compte les voyelles du prénom.

## 3. Étape 3 — la portée des variables

La **portée** (*scope*) d'une variable, c'est la région du programme où elle est visible. C'est elle qui rend l'encapsulation possible : elle tient les fonctions séparées les unes des autres. Le programme suivant crée trois variables **du même nom** dans trois portées différentes, et montre qu'elles sont trois variables bien distinctes.

```cpp
// Portees
// Trois variables du meme nom, trois portees

#include <iostream>
using namespace std;

void autreFonction();

int main()
{
    int valeur { 5 };                   // variable locale a main()
    cout << "Dans main(), valeur vaut : " << valeur << "\n\n";

    autreFonction();

    cout << "De retour dans main(), valeur vaut : " << valeur << "\n\n";

    {
        cout << "Dans un nouveau bloc de main(), valeur vaut : " << valeur << "\n\n";

        cout << "On cree une nouvelle variable dans ce bloc.\n";
        int valeur { 10 };              // masque la variable du meme nom
        cout << "Dans le nouveau bloc, valeur vaut : " << valeur << "\n\n";
    }

    cout << "A la fin de main(), valeur vaut : " << valeur << "\n";

    return 0;
}

void autreFonction()
{
    int valeur { -5 };                  // variable locale a autreFonction()
    cout << "Dans autreFonction(), valeur vaut : " << valeur << "\n\n";
}
```

### Des portées séparées

Chaque paire d'accolades crée une portée, et une fonction en est une. Les variables déclarées dans une portée ne sont pas visibles en dehors : une variable déclarée dans une fonction est **locale** à cette fonction. C'est ce qui rend les fonctions encapsulées.

`main()` déclare `int valeur { 5 };` et l'affiche : 5. Puis on entre dans `autreFonction()` — une autre portée. La `valeur` de `main()` y est invisible, si bien que `int valeur { -5 };` crée une variable **complètement distincte**, qui s'affiche à −5. Les deux n'ont aucun effet l'une sur l'autre : quand tu écris une fonction, tu n'as pas à te demander si une autre fonction utilise les mêmes noms.

Quand une portée se termine, ses variables **cessent d'exister** — on dit qu'elles sortent de portée. À la fin d'`autreFonction()`, sa `valeur` est détruite. Le programme revient dans `main()`, qui affiche de nouveau sa propre `valeur` : 5. Elle n'a pas bougé : pendant l'excursion, l'ordinateur a gardé en sécurité toutes les variables locales de `main()`, et les a retrouvées au retour.

> **Astuce** : les **paramètres** d'une fonction sont des variables locales comme les autres — c'est exactement la « copie » du cours 07 : `x` et `y` naissent à l'appel et meurent à l'accolade fermante.

### Des portées imbriquées

Une paire d'accolades posée au milieu d'une portée en crée une nouvelle, **imbriquée** dans la première. C'est le bloc anonyme au milieu de `main()`. Première ligne du bloc : afficher `valeur`. Elle n'est pas déclarée dans ce bloc — l'ordinateur remonte alors d'un niveau, trouve la `valeur` de `main()`, et affiche 5.

Puis le bloc déclare sa propre `int valeur { 10 };`. Dès lors, `valeur` désigne celle-là : 10 s'affiche, sans remonter d'un niveau. La `valeur` de `main()` existe toujours — elle est simplement **masquée** dans ce bloc.

> **Piège** : déclarer des variables du même nom dans des portées imbriquées est légal… et c'est une très mauvaise idée, source de confusion. Le programme le fait pour montrer le mécanisme, pas pour donner l'exemple.

Le bloc se ferme : la `valeur` à 10 sort de portée et disparaît. La première `valeur` est toujours là, et le dernier `cout` de `main()` affiche 5.

> **Astuce** : les variables déclarées dans un `for`, un `while`, un `if` ou un `switch` suivent la même règle — elles n'existent pas en dehors. Le `i` de `for (int i = 0; i < 10; i++)` est inconnu après la boucle. C'est pour ça qu'au cours 06 ter, la variable qui devait survivre à la boucle était déclarée **avant** le `for`.

> **Essaie** : après la boucle du cours 06 ter `for (int i = 0; i < 10; i++) { ... }`, ajoute `cout << i;` et lis le message du compilateur. Puis, dans le programme des portées, renomme la variable du bloc en `autreValeur` : qu'est-ce qui change à l'affichage ? Rien — et c'est bien plus lisible.

## 4. Étape 4 — les variables globales

Grâce à l'encapsulation, les fonctions vues jusqu'ici sont étanches : l'information entre par les paramètres, sort par la valeur de retour. Enfin, presque. Il existe une autre voie : les **variables globales**, accessibles depuis n'importe quel point du programme. Le programme suivant montre comment lire une globale de partout, la masquer dans une portée, et la modifier de partout.

```cpp
// Portee globale
// Les variables globales

#include <iostream>
using namespace std;

int globale { 10 };                     // variable globale

void lireGlobale();
void masquerGlobale();
void changerGlobale();

int main()
{
    cout << "Dans main(), globale vaut : " << globale << "\n\n";
    lireGlobale();

    masquerGlobale();
    cout << "Dans main(), globale vaut : " << globale << "\n\n";

    changerGlobale();
    cout << "Dans main(), globale vaut : " << globale << "\n\n";

    return 0;
}

void lireGlobale()
{
    cout << "Dans lireGlobale(), globale vaut : " << globale << "\n\n";
}

void masquerGlobale()
{
    int globale { 0 };                  // masque la variable globale
    cout << "Dans masquerGlobale(), globale vaut : " << globale << "\n\n";
}

void changerGlobale()
{
    globale = -10;                      // modifie la variable globale
    cout << "Dans changerGlobale(), globale vaut : " << globale << "\n\n";
}
```

### Déclarer, lire, masquer, modifier

Une variable globale se déclare **en dehors de toute fonction** : `int globale { 10 };` en tête de fichier. Dès lors, `main()` l'affiche (10), et `lireGlobale()` l'affiche aussi (10) : c'est la même variable, visible de partout.

`masquerGlobale()` déclare une variable locale **du même nom** : `int globale { 0 };`. Comme dans le bloc imbriqué de l'étape 3, la locale **masque** la globale le temps de la fonction : 0 s'affiche. Mais la globale n'a pas changé — de retour dans `main()`, elle vaut toujours 10.

`changerGlobale()`, elle, ne déclare rien : `globale = -10;` **affecte** la variable globale elle-même. Elle affiche −10, et de retour dans `main()`… −10 aussi. La modification a traversé les murs.

> **Piège** : déclarer dans une fonction une variable du même nom qu'une globale est légal, et tout aussi déconseillé que dans les portées imbriquées.

### En user le moins possible

« Ce n'est pas parce qu'on peut qu'on doit. » Les variables globales en sont l'exemple parfait : comme n'importe quelle fonction peut les modifier, il devient vite impossible de savoir qui a changé quoi et quand. Un bug sur une globale peut venir de n'importe où dans le programme. **Limite leur usage au strict minimum** — dans ce cours, à rien du tout : passe par les paramètres et les valeurs de retour.

> **Astuce** : les variables du `.h` d'openFrameworks (cours 05) ressemblent à des globales — `setup()`, `update()` et `draw()` les partagent. Elles sont en réalité des **données membres** de l'objet `ofApp` (cours 06 ter) : partagées entre ses fonctions, mais enfermées dans l'objet. C'est l'encapsulation à l'échelle au-dessus — le cours 08 y revient.

### Les constantes globales

À l'inverse des variables globales, les **constantes globales** rendent les programmes *plus* clairs. Elles se déclarent comme une globale, avec `const` :

```cpp
const int MAX_ENNEMIS { 10 };
```

Imagine un jeu d'action où le nombre d'ennemis à l'écran est plafonné. Plutôt qu'un `10` disséminé partout dans le code — un **nombre magique**, dont on finit par oublier le sens —, `MAX_ENNEMIS` dit ce qu'il est, partout où on le lit, et se change en un seul endroit. Et comme elle est `const`, aucune fonction ne peut l'abîmer : le reproche fait aux globales ne tient plus.

Une réserve : n'en fais une globale que si la constante sert dans **plusieurs** parties du programme. Si elle ne sert qu'à une fonction, déclare-la **dans** la fonction, comme `NB_MAX` dans l'inventaire du cours 06 ter.

> **Essaie** : dans le programme, remplace `int globale { 10 };` par `const int globale { 10 };` et compile. Quelle fonction le compilateur refuse-t-il, et pourquoi ?

> **Exercice — le compteur de vies** *(nouveau programme)* :
>
> 1. une constante globale `const int VIES_MAX { 3 };` ;
> 2. une fonction `int perdreVie(int vies);` qui **reçoit** le nombre de vies, retire 1, affiche `Aie ! Il te reste N vies.` et **renvoie** le nouveau nombre — sans aucune variable globale ;
> 3. dans `main()`, `int vies { VIES_MAX };`, puis une boucle `while (vies > 0)` qui appelle `vies = perdreVie(vies);` — la valeur renvoyée écrase l'ancienne, c'est le motif à retenir ;
> 4. affiche `Game over` à la sortie. Puis réfléchis : la même chose avec `vies` en variable globale marcherait — pourquoi est-ce moins bien ?

## 5. Étape 5 — les arguments par défaut : donne-moi un nombre

Quand un paramètre reçoit presque toujours la même valeur, on peut épargner cette répétition à l'appelant avec un **argument par défaut** : la valeur prise par le paramètre si l'appel n'en fournit pas. Exemple concret : une fonction qui règle l'affichage pourrait avoir un paramètre `bool pleinEcran`. Si elle est presque toujours appelée avec `true`, donne-lui `true` par défaut, et l'appelant n'aura plus à le préciser.

Le programme suivant demande deux nombres dans deux intervalles différents, avec **la même fonction**. Le premier appel omet la borne basse, qui a une valeur par défaut ; le second la fournit.

```cpp
// Donne-moi un nombre
// Les arguments par defaut

#include <iostream>
using namespace std;

int demanderNombre(int maximum, int minimum = 1);

int main()
{
    int nombre = demanderNombre(5);
    cout << "Merci d'avoir tape : " << nombre << "\n\n";

    nombre = demanderNombre(10, 5);
    cout << "Merci d'avoir tape : " << nombre << "\n\n";

    return 0;
}

int demanderNombre(int maximum, int minimum)
{
    int n;
    cout << "Tape un nombre entre " << minimum << " et " << maximum << " : ";
    cin >> n;
    while (n > maximum || n < minimum)
    {
        cout << "Tape un nombre entre " << minimum << " et " << maximum << " : ";
        cin >> n;
    }
    return n;
}
```

### Déclarer un argument par défaut

Dans le prototype, le second paramètre a l'air de recevoir une valeur :

```cpp
int demanderNombre(int maximum, int minimum = 1);
```

Et c'est à peu près ça : le `1` est l'argument par défaut. Si l'appel ne fournit rien pour `minimum`, il vaudra 1. La syntaxe : `=` suivi d'une valeur, après le nom du paramètre, **dans le prototype**. On ne le répète pas dans la définition, dont l'en-tête reste `int demanderNombre(int maximum, int minimum)`.

> **Piège** : à partir du premier paramètre qui a une valeur par défaut, **tous les suivants** doivent en avoir une. Ce prototype est valable :
>
> ```cpp
> void reglerAffichage(int largeur, int hauteur, int profondeur = 32, bool pleinEcran = true);
> ```
>
> celui-ci ne l'est pas — `pleinEcran` vient après `profondeur` mais n'a pas de défaut :
>
> ```cpp
> void reglerAffichage(int largeur, int hauteur, int profondeur = 32, bool pleinEcran);
> ```

### Appeler avec et sans

Premier appel :

```cpp
int nombre = demanderNombre(5);
```

`maximum` reçoit 5 ; rien n'est fourni pour `minimum`, qui prend sa valeur par défaut, 1. La fonction demande donc un nombre entre 1 et 5 — et redemande tant qu'on est hors de l'intervalle, un `while` sur un `||` du cours 06 bis. Deuxième appel :

```cpp
nombre = demanderNombre(10, 5);
```

Cette fois `minimum` reçoit 5, qui **remplace** le défaut : un nombre entre 5 et 10. On peut toujours passer un argument à un paramètre qui a un défaut ; la valeur passée l'emporte.

> **Piège** : à l'appel, dès qu'on omet un argument, on doit omettre **tous les suivants**. Avec le prototype de `reglerAffichage` ci-dessus, `reglerAffichage(1680, 1050);` est valable ; `reglerAffichage(1680, 1050, false);` ne l'est pas — ce `false` irait dans `profondeur`, un `int`, et il n'y a aucun moyen de « sauter » `profondeur` pour atteindre `pleinEcran`.

> **Essaie** : donne aussi un défaut à `maximum` — `int demanderNombre(int maximum = 10, int minimum = 1);` — et appelle `demanderNombre()` sans rien. Puis essaie d'appeler `demanderNombre(, 5)` pour ne fournir que le minimum : ça ne compile pas, et le second Piège dit pourquoi.

> **Exercice — le dé générique** *(nouveau programme)* :
>
> 1. `int lancerDe(int faces = 6);` qui renvoie `rand() % faces + 1` (graine `srand` en tête de `main`, cours 06 bis) ;
> 2. dans `main()`, affiche trois lancers : `lancerDe()`, `lancerDe(20)`, `lancerDe(100)` — un dé à six faces, un d20, un pourcentage ;
> 3. ajoute `int lancerDes(int nombre, int faces = 6);` qui lance `nombre` dés et renvoie leur **somme** — une boucle qui appelle `lancerDe(faces)`. Affiche `lancerDes(3)` : trois d6, comme dans les jeux de rôle.

## 6. Étape 6 — la surcharge : le tripleur

Chaque fonction a une liste de paramètres et un type de retour fixés. Et si on veut une fonction plus souple, qui accepte des arguments de types différents ? Par exemple une fonction qui transforme des sommets 3D donnés en `float`, mais qu'on voudrait aussi appeler avec des `int`. Plutôt que deux fonctions de deux noms différents, C++ permet la **surcharge** (*overloading*) : plusieurs définitions **du même nom**, avec des listes de paramètres différentes. Tu l'as déjà rencontrée au cours 06 ter avec le `+`, qui additionne les nombres et concatène les `string` : même principe, appliqué aux fonctions.

Le programme triple le nombre 5 et le mot « joueur », avec une seule fonction `tripler` surchargée pour `int` et pour `string`.

```cpp
// Tripleur
// La surcharge de fonctions

#include <iostream>
#include <string>

using namespace std;

int tripler(int nombre);
string tripler(string texte);

int main()
{
    cout << "Le triple de 5 : " << tripler(5) << "\n\n";
    cout << "Le triple de 'joueur' : " << tripler("joueur") << "\n";
    return 0;
}

int tripler(int nombre)
{
    return nombre * 3;
}

string tripler(string texte)
{
    return texte + texte + texte;
}
```

### Écrire une fonction surchargée

Il suffit d'écrire plusieurs définitions du même nom avec des paramètres différents. Ici, deux prototypes :

```cpp
int tripler(int nombre);
string tripler(string texte);
```

La première reçoit un `int` et renvoie un `int` — le nombre multiplié par trois. La seconde reçoit une `string` et renvoie une `string` — le texte répété trois fois, par le `+` surchargé du cours 06 ter.

> **Piège** : c'est la **liste des paramètres** qui distingue deux surcharges, jamais le type de retour. Deux définitions qui ne diffèrent que par le type de retour sont une erreur de compilation — impossible d'avoir à la fois `int bonus(int);` et `float bonus(int);`.

### Appeler une fonction surchargée

On l'appelle comme n'importe quelle fonction. C'est le **compilateur** qui choisit la définition, d'après les arguments. `tripler(5)` : un `int`, donc la première version, qui renvoie 15. `tripler("joueur")` : une chaîne, donc la seconde, qui renvoie `"joueurjoueurjoueur"`.

> **Essaie** : ajoute une troisième surcharge `float tripler(float nombre);` et appelle `tripler(2.5f)` : 7.5. Puis enlève le `f` : `tripler(2.5)` ne compile plus — « appel ambigu ». Un littéral `2.5` est un `double` (cours 01), et le compilateur hésite entre le convertir en `int` et en `float`. Remets le `f`, ou ajoute une surcharge `double`.

> **Exercice — l'afficheur** *(nouveau programme)* :
>
> 1. `void afficher(int n);` affiche `Entier : n` ; `void afficher(string s);` affiche `Texte : s` ; `void afficher(bool b);` affiche `Vrai` ou `Faux` ;
> 2. dans `main()`, appelle `afficher(42)`, `afficher("bonjour")` et `afficher(true)`. Surprise : le deuxième affiche `Vrai`. Une chaîne entre guillemets n'est pas une `string` mais une chaîne à la C (cours 06 ter), que C++ préfère convertir en `bool` plutôt qu'en `string`. Écris `afficher(string("bonjour"))` pour forcer la bonne version ;
> 3. bonus : `void afficher(vector<int> liste);` qui affiche tous les éléments avec un `for`. Quatre fonctions, un seul nom : c'est comme ça que `cout <<` sait afficher un `int` comme une `string`.

## 7. Étape 7 — le projet : « Histoire à trous »

Le jeu final te demande de l'aide pour écrire une histoire : un prénom, un nom au pluriel, un nombre, une partie du corps et un verbe. Avec tout ça, il compose un récit personnalisé — et généralement absurde. Une partie :

```text
Bienvenue dans Histoire a trous.

Reponds aux questions suivantes pour creer une nouvelle histoire.

Entre un prenom : Gaetan
Entre un nom au pluriel : pandas
Entre un nombre : 12
Entre une partie du corps : nez
Entre un verbe (a la deuxieme personne, ex. manges) : cherches

Voici ton histoire :

Le celebre explorateur Gaetan avait presque renonce a la quete de toute une vie :
trouver la Cite perdue des pandas. Quand un beau jour, ce sont les pandas
qui trouverent l'explorateur. Entoure de 12 pandas, Gaetan sentit une larme
lui monter au nez. Apres tout ce temps, la quete etait enfin terminee.
Puis les pandas devorerent Gaetan sans attendre.
La morale de cette histoire ? Fais attention a ce que tu cherches.
```

Tout le cours y passe : trois fonctions en plus de `main()`, des paramètres `string` et `int`, des valeurs de retour, et un `main()` qui ne fait qu'orchestrer. Construisons-le en quatre morceaux.

### Les prototypes et `main()`

```cpp
// Histoire a trous
// Le jeu des mots a completer

#include <iostream>
#include <string>

using namespace std;

string demanderTexte(string question);
int demanderNombre(string question);
void raconterHistoire(string prenom, string nom, int nombre, string partieDuCorps, string verbe);

int main()
{
    cout << "Bienvenue dans Histoire a trous.\n\n";
    cout << "Reponds aux questions suivantes pour creer une nouvelle histoire.\n\n";

    string prenom = demanderTexte("Entre un prenom : ");
    string nom = demanderTexte("Entre un nom au pluriel : ");
    int nombre = demanderNombre("Entre un nombre : ");
    string partieDuCorps = demanderTexte("Entre une partie du corps : ");
    string verbe = demanderTexte("Entre un verbe (a la deuxieme personne, ex. manges) : ");

    raconterHistoire(prenom, nom, nombre, partieDuCorps, verbe);

    return 0;
}
```

Les trois prototypes annoncent la couleur : `demanderTexte()` et `demanderNombre()` posent une question et renvoient la réponse, `raconterHistoire()` reçoit tout et n'en renvoie rien. Lis `main()` : il se **lit comme le scénario** du jeu — accueillir, demander cinq choses, raconter. Aucun détail ; c'est l'abstraction de l'étape 1 à l'œuvre. Un `main()` qui orchestre des fonctions bien nommées, c'est la forme que prendront tous tes programmes à partir d'ici.

### `demanderTexte()`

```cpp
string demanderTexte(string question)
{
    string texte;
    cout << question;
    cin >> texte;
    return texte;
}
```

Elle lit une `string` au clavier. Comme elle reçoit la question en paramètre, la **même** fonction sert pour le prénom, le nom, la partie du corps et le verbe : quatre appels, une définition.

> **Piège** : `cin >> texte` s'arrête au premier espace. `nez` passe ; `gros orteil` ne donnera que `gros`, et `orteil` restera dans la file d'attente pour la question suivante — qui semblera sauter. Il existe une fonction pour lire une ligne entière (`getline`), mais elle demande quelques précautions : pour l'instant, réponds en un seul mot.

### `demanderNombre()`

```cpp
int demanderNombre(string question)
{
    int n;
    cout << question;
    cin >> n;
    return n;
}
```

Même structure, mais elle lit un `int` et le renvoie. Elle n'est appelée qu'une fois, mais son paramètre `question` la rend prête à resservir.

### `raconterHistoire()`

```cpp
void raconterHistoire(string prenom, string nom, int nombre, string partieDuCorps, string verbe)
{
    cout << "\nVoici ton histoire :\n\n";
    cout << "Le celebre explorateur " << prenom;
    cout << " avait presque renonce a la quete de toute une vie :\n";
    cout << "trouver la Cite perdue des " << nom << ". Quand un beau jour, ce sont les " << nom << "\n";
    cout << "qui trouverent l'explorateur. Entoure de " << nombre << " " << nom << ", " << prenom << " sentit une larme\n";
    cout << "lui monter au " << partieDuCorps << ". Apres tout ce temps, la quete etait enfin terminee.\n";
    cout << "Puis les " << nom << " devorerent " << prenom << " sans attendre.\n";
    cout << "La morale de cette histoire ? Fais attention a ce que tu " << verbe << ".\n";
}
```

Cinq paramètres, aucune valeur de retour : la fonction reçoit **tout ce dont elle a besoin** et affiche. Elle n'invente rien, ne lit rien au clavier, ne touche à aucune variable de `main()` : c'est l'encapsulation en pratique. Assemble les quatre morceaux dans `main.cpp`, lance, et fais-toi raconter une histoire.

> **Essaie** : écris ta propre histoire dans `raconterHistoire()` — avec un sixième trou, donc un sixième paramètre, un sixième prototype à mettre à jour, et un sixième appel à `demanderTexte` dans `main()`. Mots **sans accents** : la console ne les affiche pas bien.

> **Exercice — l'histoire vérifiée.** En suite du jeu :
>
> 1. remplace `demanderNombre(string question)` par une version qui **redemande** tant que le nombre est négatif — la boucle `while` de l'étape 5 ;
> 2. ajoute `string demanderOuiNon(string question);` (étape 2) et, après l'histoire, demande `Une autre histoire ?` : si la réponse est `o`, on recommence — une boucle de jeu autour de tout `main()`, cours 06 bis ;
> 3. bonus : `demanderTexte` refuse une réponse vide ou d'une seule lettre (`texte.size() < 2`), et redemande.

## Questions et réponses

**Pourquoi écrire des fonctions ?**
Pour découper un programme en morceaux logiques — plus petits, plus faciles à lire, à tester et à corriger qu'un seul bloc monolithique. Et pour **réutiliser** : une fonction bien écrite sert dans le programme suivant.

**C'est quoi, l'encapsulation ?**
Garder les choses séparées. Pour une fonction : ses variables sont invisibles de l'extérieur, et elle n'échange avec le reste que par ses paramètres et sa valeur de retour.

**Argument ou paramètre ?**
L'**argument** est la valeur qu'on passe à l'**appel** (`tripler(5)` : 5 est l'argument). Le **paramètre** est la variable qui la reçoit dans la **définition** (`int tripler(int nombre)` : `nombre` est le paramètre). L'argument n'a pas besoin de porter le même nom que le paramètre : seule la valeur voyage.

**Une fonction peut-elle avoir plusieurs `return` ?**
Oui — c'est même pratique pour marquer plusieurs points de sortie, par exemple un `return` dans chaque branche d'un `if`.

**C'est quoi, une variable locale ?**
Une variable définie dans une portée. Toutes les variables définies dans une fonction, paramètres compris, sont locales à cette fonction.

**Que veut dire « masquer » une variable ?**
Déclarer, dans une portée imbriquée, une variable du même nom qu'une variable extérieure. Dans la portée intérieure, le nom désigne la nouvelle ; l'ancienne est inaccessible — mais pas détruite.

**Quand une variable sort-elle de portée ?**
Quand la portée où elle a été créée se termine : elle cesse alors d'exister.

**Une fonction peut-elle en appeler une autre ?**
Évidemment : dès que `main()` appelle une fonction, c'est le cas. Et une fonction autre que `main()` peut en appeler une autre — `titre()` appelait `ligne()` dans l'exercice de l'étape 1. C'est même la règle : les grosses fonctions se construisent avec des petites.

**Et `setup()`, `update()`, `draw()` d'openFrameworks ?**
Des fonctions `void` sans paramètres, définies par toi et **appelées** par openFrameworks — une fois, puis en boucle. Les fonctions `bear` ou `etoile` du cours 07 sont des fonctions à toi avec des paramètres, exactement comme ici ; la seule différence est le `ofApp::` devant leur nom, qui dit qu'elles sont des fonctions membres de l'objet `ofApp`.

**C'est quoi, le *profiling* ?**
Mesurer où un programme passe son temps, avec un outil appelé *profiler*, pour repérer les goulots d'étranglement. On le fait **à la fin** d'un projet, une fois que tout marche. Optimiser trop tôt — l'**optimisation prématurée** — est un piège classique : on complique du code qui n'en avait pas besoin, et on ralentit souvent ce qu'on voulait accélérer. Première règle du programmeur de jeu : d'abord que ça marche, ensuite que ce soit propre, et seulement alors, si la mesure le demande, que ce soit rapide.

## Questions de réflexion

1. En quoi l'encapsulation des fonctions aide-t-elle à écrire de meilleurs programmes ?
2. Comment des variables globales peuvent-elles rendre un programme confus ?
3. Comment des constantes globales peuvent-elles rendre un programme plus clair ?
4. Quels sont les avantages et les inconvénients d'optimiser du code ?
5. En quoi la réutilisation de code profite-t-elle à un studio de jeu vidéo ?

## Exercices

1. **Lire avant de lancer.** Qu'est-ce qui cloche dans ce prototype ?

   ```cpp
   int demanderNombre(int minimum = 1, int maximum);
   ```

2. **Méli-Mélo en fonctions** *(plus costaud)*. Réécris le jeu du cours 06 ter avec des fonctions : au minimum `string melanger(string mot);` qui renvoie la version mélangée, `string demanderProposition();` qui lit la réponse du joueur, et `void accueillir();` pour les règles. `main()` doit se lire comme un scénario : accueillir, tirer, mélanger, boucler, féliciter. Vérifie que la liste `MOTS` n'a pas besoin d'être globale — à qui faut-il la passer ?

3. **Avec et sans défaut.** En utilisant un argument par défaut, écris une fonction qui demande un nombre à l'utilisateur et le renvoie. Elle accepte une question en `string` ; si l'appelant n'en fournit pas, elle utilise une question générique (`Entre un nombre : `). Puis obtiens le **même résultat par surcharge** : deux fonctions du même nom, l'une avec le paramètre, l'autre sans, la seconde appelant la première. Laquelle des deux solutions préfères-tu, et pourquoi ?

## Ce qu'il faut retenir

- Une fonction se **déclare** par un prototype (type de retour, nom, paramètres, point-virgule), se **définit** par un en-tête et un corps entre accolades, et s'**appelle** par son nom et ses arguments. Prototype et définition doivent correspondre.
- Les **paramètres** font entrer des valeurs (ce sont des copies, cours 07) ; `return` en fait sortir une, du type annoncé. Une fonction `void` ne renvoie rien.
- **Abstraction** : utiliser une fonction sans connaître ses détails. **Encapsulation** : ses variables n'existent que dans sa portée. Un `main()` qui orchestre des fonctions bien nommées se lit comme un scénario.
- La **portée** d'une variable est le bloc où elle est déclarée ; à la sortie du bloc, elle disparaît. Une variable d'un bloc intérieur **masque** celle du même nom à l'extérieur — légal, mais à éviter.
- Les **variables globales** se lisent et se modifient de partout : à éviter. Les **constantes globales** (`const int MAX_ENNEMIS { 10 };`) remplacent les nombres magiques : à utiliser quand plusieurs fonctions en ont besoin.
- Un **argument par défaut** (`int minimum = 1` dans le prototype) sert quand l'appel ne fournit rien ; tout paramètre après lui doit en avoir un aussi.
- La **surcharge** : plusieurs fonctions du même nom, distinguées par leurs paramètres, jamais par le type de retour. Le compilateur choisit d'après les arguments.
- Pour lire une réponse valide : une lecture avant le `while`, une relecture dedans — le motif de `demanderOuiNon` et `demanderNombre`, à réutiliser partout.

---

*Ce cours est l'adaptation française du chapitre 5 de « Beginning C++ Through Game Programming » de Michael Dawson (Cengage Learning) : « Functions: Mad Lib ». Par rapport à l'original : les réponses sont lues dans des `string` plutôt que des `char`, les boucles `do … while` sont écrites avec `while`, et la section sur les fonctions `inline` n'est pas reprise.*

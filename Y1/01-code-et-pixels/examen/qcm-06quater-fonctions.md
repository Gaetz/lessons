# QCM — Cours 06 quater : les fonctions

10 questions de compréhension, une idée par question, sans piège. La bonne réponse est marquée **✔** (à retirer avant le report dans le système QCM d'École Directe).

**Q1.** Que déclare ce prototype ?

```cpp
int demanderNombre(int maximum);
```

- A. Une fonction qui reçoit un `int` et renvoie un `int` **✔**
- B. Une fonction qui ne reçoit rien et renvoie un `int`
- C. Une fonction qui reçoit un `int` et ne renvoie rien
- D. Une variable de type `int`

*(type de retour, nom, paramètres : le prototype se lit comme une fiche d'identité)*

**Q2.** Dans ce prototype, que signifie `void` ?

```cpp
void instructions();
```

- A. La fonction ne reçoit aucune valeur
- B. La fonction ne renvoie aucune valeur **✔**
- C. La fonction est vide, elle ne fait rien
- D. La fonction ne peut être appelée qu'une fois

**Q3.** Que vaut `a` à la fin ?

```cpp
#include <iostream>
using namespace std;

int plusCinq(int n);

int main()
{
    int a = plusCinq(10);
    cout << a;
    return 0;
}

int plusCinq(int n)
{
    return n + 5;
}
```

- A. 10
- B. 5
- C. 15 **✔**
- D. n + 5

*(l'appel vaut ce que la fonction renvoie, et on le range dans une variable)*

**Q4.** Pendant l'appel `presenter("Lea", 20);`, que vaut le paramètre `age` ?

```cpp
void presenter(string prenom, int age)
{
    cout << prenom << " a " << age << " ans.";
}
```

- A. 0
- B. 20 **✔**
- C. "Lea"
- D. On ne peut pas savoir

*(les arguments remplissent les paramètres dans l'ordre)*

**Q5.** Dans l'appel `tripler(5);`, comment s'appelle le `5` ?

- A. Le paramètre
- B. L'argument **✔**
- C. Le prototype
- D. La valeur de retour

*(l'argument est la valeur passée à l'appel ; le paramètre est la variable qui la reçoit dans la définition)*

**Q6.** Qu'affiche ce programme ?

```cpp
#include <iostream>
using namespace std;

void autreFonction();

int main()
{
    int valeur { 5 };
    autreFonction();
    cout << valeur;
    return 0;
}

void autreFonction()
{
    int valeur { -5 };
}
```

- A. 5 **✔**
- B. -5
- C. 0
- D. Le programme ne compile pas : `valeur` existe déjà

*(chaque fonction a sa propre portée : deux variables distinctes, même nom)*

**Q7.** Qu'affiche ce programme ?

```cpp
#include <iostream>
using namespace std;

int signe(int n);

int main()
{
    cout << signe(7);
    return 0;
}

int signe(int n)
{
    if (n >= 0)
    {
        return 1;
    }
    return -1;
}
```

- A. 1 **✔**
- B. -1
- C. 1-1
- D. 7

*(une fonction se termine dès qu'elle rencontre un `return` ; le second n'est pas atteint)*

**Q8.** Avec ce prototype, que vaut `minimum` pendant l'appel `demanderNombre(5);` ?

```cpp
int demanderNombre(int maximum, int minimum = 1);
```

- A. 0
- B. 1 **✔**
- C. 5
- D. L'appel ne compile pas : il manque un argument

*(aucun argument fourni pour `minimum` : il prend sa valeur par défaut)*

**Q9.** Ces deux fonctions portent le même nom. Quelle version s'exécute à l'appel `tripler(4);` ?

```cpp
int tripler(int nombre);
string tripler(string texte);
```

- A. La première : le compilateur choisit d'après le type de l'argument **✔**
- B. La seconde : la dernière déclarée l'emporte
- C. Les deux, l'une après l'autre
- D. Aucune : deux fonctions ne peuvent pas porter le même nom

*(c'est la surcharge : même nom, paramètres différents, et le compilateur choisit)*

**Q10.** La variable `reponse` est créée **dans** la fonction `demanderOuiNon()`. Comment `main()` peut-il connaître la réponse de l'utilisateur ?

```cpp
string demanderOuiNon()
{
    string reponse;
    cin >> reponse;
    return reponse;
}
```

- A. En lisant directement `reponse` après l'appel
- B. En récupérant la valeur renvoyée : `string r = demanderOuiNon();` **✔**
- C. Il ne peut pas : la réponse est perdue
- D. En déclarant une deuxième variable `reponse` dans `main()`

*(les variables d'une fonction n'existent que dans sa portée — l'encapsulation ; la valeur sort par le `return`)*

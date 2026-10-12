
## Épreuve 1 — QCM (8 points, 16 questions à 0,5 pt)

**À faire sur l'application QCM d'École Directe.**

Compréhension de code, **un sujet à la fois**. La bonne réponse est marquée **✔** (à retirer avant le report dans le système QCM).

### Variables (3 questions)

**Q1.** Que vaut `prix` à la fin ?

```cpp
int main()
{
    float prix { 10 };
    prix = prix / 4;
    return 0;
}
```

- A. 2
- B. 2,5
- C. 3
- D. 40

**Q2.** Que vaut `b` à la fin ?

```cpp
int main()
{
    int a { 7 };
    int b = a / 2;
    return 0;
}
```

- A. 3,5
- B. 3
- C. 4
- D. Le programme ne compile pas

**Q3.** Que vaut `a` à la fin ?

```cpp
int main()
{
    int a { 2 };
    a = a + a;
    a = a + 1;
    return 0;
}
```

- A. 3
- B. 4
- C. 5
- D. 6

### Fonctions (3 questions)

**Q4.** Pendant l'appel de `dessineCercle`, que vaut le paramètre `r` ?

```cpp
void dessineCercle(float x, float r)
{
    ofDrawCircle(x, 200, r);
}

void ofApp::draw()
{
    dessineCercle(100, 20);
}
```

- A. 100
- B. 20
- C. 200
- D. On ne peut pas savoir

**Q5.** Que fait ce programme ?

```cpp
void carre(float x, float y)
{
    ofDrawRectangle(x, y, 50, 50);
}

void ofApp::draw()
{
    carre(100, 200);
    carre(300, 200);
}
```

- A. Il dessine un seul carré
- B. Il dessine deux carrés à la même position
- C. Il dessine deux carrés, en (100, 200) et en (300, 200)
- D. Il ne compile pas : on ne peut pas appeler deux fois la même fonction

**Q6.** Que vaut `a` à la fin ?

```cpp
int plusDeux(int n)
{
    return n + 2;
}

int main()
{
    int a = plusDeux(3);
    return 0;
}
```

- A. 3
- B. 2
- C. 5
- D. n + 2

### Conditions (3 questions)

**Q7.** Qu'affiche ce programme ?

```cpp
#include <iostream>
using std::cout;

int main()
{
    int code { 5 };
    if (code == 5)
    {
        cout << "ouvert";
    }
    else
    {
        cout << "ferme";
    }
    return 0;
}
```

- A. ouvert
- B. ferme
- C. ouvertferme
- D. Rien

**Q8.** Qu'affiche ce programme ?

```cpp
#include <iostream>
using std::cout;

int main()
{
    int n { 80 };
    if (n >= 90)
    {
        cout << "excellent";
    }
    else if (n >= 70)
    {
        cout << "bien";
    }
    else
    {
        cout << "moyen";
    }
    return 0;
}
```

- A. excellent
- B. bien
- C. bienmoyen
- D. moyen

**Q9.** Qu'affiche ce programme ?

```cpp
#include <iostream>
using std::cout;

int main()
{
    int a { 5 };
    int b { 10 };
    if (a > 3 && b > 20)
    {
        cout << "X";
    }
    else
    {
        cout << "Y";
    }
    return 0;
}
```

- A. X
- B. Y
- C. XY
- D. Rien

### Boucle `for` (3 questions)

**Q10.** Qu'affiche ce programme ?

```cpp
#include <iostream>
using std::cout;

int main()
{
    for (int i = 0; i < 5; i = i + 1)
    {
        cout << i << " ";
    }
    return 0;
}
```

- A. 0 1 2 3 4
- B. 1 2 3 4 5
- C. 0 1 2 3 4 5
- D. 1 2 3 4

**Q11.** Que vaut `total` à la fin ?

```cpp
int main()
{
    int total { 0 };
    for (int i = 1; i <= 4; i = i + 1)
    {
        total = total + i;
    }
    return 0;
}
```

- A. 4
- B. 5
- C. 10
- D. 15

**Q12.** Combien de fois le corps de cette boucle s'exécute-t-il ?

```cpp
#include <iostream>
using std::cout;

int main()
{
    for (int i = 3; i < 7; i = i + 1)
    {
        cout << "tour ";
    }
    return 0;
}
```

- A. 3
- B. 4
- C. 5
- D. 7

### Boucle `while` (2 questions)

**Q13.** Que vaut `n` à la fin ?

```cpp
int main()
{
    int n { 3 };
    while (n < 10)
    {
        n = n + 3;
    }
    return 0;
}
```

- A. 9
- B. 10
- C. 12
- D. La boucle ne s'arrête jamais

**Q14.** Qu'affiche ce programme ?

```cpp
#include <iostream>
using std::cout;

int main()
{
    int c { 3 };
    while (c > 0)
    {
        cout << c;
        c = c - 1;
    }
    return 0;
}
```

- A. 321
- B. 3210
- C. 123
- D. Rien

### Listes (2 questions)

**Q15.** Qu'affiche ce programme ?

```cpp
#include <iostream>
#include <vector>
using std::cout;
using std::vector;

int main()
{
    vector<int> notes;
    notes.push_back(10);
    notes.push_back(14);
    notes.push_back(8);
    cout << notes[1];
    return 0;
}
```

- A. 10
- B. 14
- C. 8
- D. 1

**Q16.** Qu'affiche ce programme ?

```cpp
#include <iostream>
#include <vector>
using std::cout;
using std::vector;

int main()
{
    vector<int> v;
    v.push_back(2);
    v.push_back(5);
    v[0] = v[0] + v[1];
    cout << v[0] << " " << v.size();
    return 0;
}
```

- A. 7 2
- B. 7 3
- C. 2 2
- D. 25 2
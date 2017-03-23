# C++ dla programistów C#
Krótki dokument mapujący zagadnienia z programowania w języku C# do C++

## Struktura programów
C++ jest językiem zorientowanym obiektowo, tak jak C#. To oznacza, że nasze programy również powstają w oparciu o projektowanie klas i
tworzenie obiektów realizujących te klasy.

### Deklaracja klasy
Słowo kluczowe `class`, tak jak w C#.
Istotną różnicą jest działanie `class` vs `struct`: w C# to ma większe znaczenie bo `struct` tworzy typ przekazywany przez wartość,
a nie przez referencję. W C++ to nie ma znaczenia - `struct` oznacza poprostu, że członkowie tej klasy będą domyślnie publiczni.

A co z referencjami vs wartościami? W C++ normalnie typy będą przekazywane przez wartość (kopiowane). Żeby mieć typ referencyjny,
trzeba użyć referencji lub wskaźnika *jawnie*.

### Wskaźniki i referencje
Referencje i wskaźniki pozwalają nam właśnie na przekazywanie dostępu do obiektu bez kopiowania go.
W C++ te typy pojawiają się jawnie, tj. będzie widać w deklaracji typu i w odwołaniu do obiektu lub jego członków, że mamy do czynienia
ze wskaźnikiem/referencją.
```c++
<Typ>* zmienna_wsk;
<Typ>& zmienna_ref;
```
Czyli `*` odpowiada wskaźnikom a `&` referencjom. Różnice pomiędzy referencjami a wskaźnikami nie jest tu w zasadzie istotna (wskaźniki są
ogólnie bardziej elastyczne).
Na ogół będzie wiadomo których użyć: referencje pojawią się głównie jako argumenty procedur, wskaźniki jako typ zwracany przez kod.
Na ogół bezpieczniej jest używać referencji ale np. wskaźnikowi można przypisać NULL,
co jest przydatne jak się chce poinformować kod o błędzie wykonania.

A jak się odwołujemy do obiektów przez wskaźnik? Również jawnie:
```c++
do_something(*obj); // obiekt jako taki
obj->field; // jeśli chcemy pole lub metodę
obj->method(); // '->' zastępuje tutaj '.'
// BTW, komentarze są jak w C#
```
A jak dostać wskaźnik jeśli mamy zwykłą zmienną (wartość)?
```c++
do_something_with_a_pointer(&obj);
```
Tak, można się pogubić co jest od czego bo `*` i `&` mają inne znaczenia w zależności od kontekstu. Kwestia przyzwyczajenia.

## Podsumowanie
To jest wstępna wersja tego samouczka - będę ją rozwijał na podstawie potrzeb innych.

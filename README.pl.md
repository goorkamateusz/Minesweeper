# Minesweeper2 (PL)
![](gui/flag.png) Gra saper w C++.

> **Read [README in english](README.md)!**

## Autor
>   **Górka Mateusz**\
>   **maatiug@gmail.com**

## Spis treści
- [Minesweeper2](#Minesweeper2)
- [Autor](#Autor)
- [Gra](#Gra)
    - [Przygotowanie](#Przygotowanie)
    - [Uruchomienie](#Uruchomienie)
    - [Zasady gry](#Zasady\ gry)
- [Dev](#Dev)
    - [Documentation](#Documentation)
    - [Exception](#Exception)
    - [Specyfikacja](#Specyfikacja)
- [Licencja](#Licencja)

![](gui/mine.png)

## Gra
### Przygotowanie:
Wykorzystaj program [`make`](http://gnuwin32.sourceforge.net/packages/make.htm), by skompilować kod.

### Uruchomienie:
Uruchom poleceniem: `./Minesweeper2.exe`.

Argumenty wywołania:
arg          | pomoc
:-----------:|:--------
 -w \<num>   | szerokość planszy
 -h \<num>   | wysokość planszy
 -m \<num>   | ilość min

np.: `./Minesweeper2.exe -w 20 -h 15 -m 70`

### Zasady gry:
 - Pierwsze naciśnięcie jest zawsze bezpieczne.
 - Gra kończy się gdy wszystkie pola nie zawierające miny są odkryte.


## Dev
### Dokumentacja
Wykorzystaj program [doxygen](http://doxygen.nl), by wygenerować dokumentację.
Możesz wykorzystać polecenie `make doxygen` w folderze głównym programu.
[Link do wygenerowanej dokumentacji](dox/html/index.phtml)

### Wyjątki
...
<!-- todo exceptions ! -->

### Specyfikacja
- Language: C++
- OS: Windows 10
- Kompilator: **minGW**
- GUI: SFML Library

## Licencja
Zobacz w pliku [LICENSE.md](@ref LICENSE.md).
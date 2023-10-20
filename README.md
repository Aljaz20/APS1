# Algoritmi in podatkovne strukture 1

Delo pri predmetu Algoritmi in podatkovne strukture 1 (C++) UNI, Fakulteta za računalništvo in informatiko, Univerza v Ljubljani, 2022/23:

- `Marjan.sh` - bash program za avtomatsko testiranje C++ programov,
- vaje s lastnimi testnimi primeri.

Seznam rešenih vaj:
----------
- V01 -> V02

Testiranje s programom `Marjan.sh` (Current version == 1.4):
---------
Program `Marjan.sh` omogoča samodejno testiranje vašega programa s testnimi primeri.
### Splošna navodila za uporabo:
```shell
./Marjan.sh {ime_vasega_programa_brez_koncnice} {dodatni_parametri v poljubnem vrstnem redu}
```

### Primeri uporabe:
- Torej program `Resitev.cpp` se testira tako (s privzetimi nastavitvami - Timelimit = 2.0 s, Measure_time = 0):
```shell
./Marjan.sh Resitev
```

- Če pa želite izpisati čase posameznih testov (M=1) ali pa spremeniti timelimit (T=1.0) pa naredite to tako:
```shell
./Marjan.sh Resitev T=1.0 M=1
```

Prevajanje in poganjanje posameznih programov:
----------
### Prevajanje:
```shell
g++ -std=c++20 {Ime programa}
```
### Poganjanje:
```shell
./a.out < {test01.in}
```
Torej program `Resitev.cpp` se prevede in požene (izhod se zapiše v terminal) tako:
```shell
g++ -std=c++20 Osvetlitev.cpp
./a.out < test01.in
```

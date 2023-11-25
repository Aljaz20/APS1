# Algoritmi in podatkovne strukture 1

Delo pri predmetu Algoritmi in podatkovne strukture 1 (C++) UNI, Fakulteta za računalništvo in informatiko, Univerza v Ljubljani, 2022/23:

- `Marjan.sh` - bash program za avtomatsko testiranje C++ programov,
- domače naloge s lastnimi testnimi primeri.

Seznam rešenih domačih nalog:
----------
- DN01 -> DN07.

Testiranje s programom `Marjan.sh` (Current version == 1.7.2):
---------
Program `Marjan.sh` omogoča samodejno testiranje vašega programa s testnimi primeri.
### Pred uporabo:
Za dodelitev splošnih pravic:
``` shell
chmod u+x Marjan.sh
```

### Splošna navodila za uporabo:
```shell
./Marjan.sh {ime_vasega_programa_brez_koncnice} {dodatni_parametri v poljubnem vrstnem redu}
```

### Primeri uporabe:
- Torej program `Resitev.cpp` se testira tako (s privzetimi nastavitvami - Timelimit = 2.0 s, Measure_time = 1, Range_of_test = ALL):
```shell
./Marjan.sh Resitev
```
- Možni dodatni parametri:
    - Timelimit (T=?),
    - Measure time (M=0/1; 0: no, 1: yes),
    - Range of tests (R=?; 1-, 2-5, -5).

- Če pa želite uporabiti dodatne parametre pa to lahko naredite na takšne način:
```shell
./Marjan.sh Resitev T=1.0 M=0 R=3-7
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

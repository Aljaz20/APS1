# Algoritmi in podatkovne strukture 1

Delo pri predmetu Algoritmi in podatkovne strukture 1 (C++) UNI, Fakulteta za računalništvo in informatiko, Univerza v Ljubljani, 2022/23:

- `Marjan.sh` - program za avtomatsko testiranje,
- vaje s lastnimi testnimi primeri.

Seznam rešenih vaj:
----------
- V01 -> V02

Testiranje s programom `Marjan.sh` (Current version == 1.1):
---------
S programom `Marjan.sh` lahko testirate svoj program s testnimi primeri.
```shell
./Marjan.sh {ime_vasega_programa_brez_koncnice} {st_testov_ki_so_na_voljo} {imate test.out file? NE - 0, DA - 1}
```

Torej za program `Resitev.cpp`, z 50 testnimi primeri in z rešitvami (testXX.out file) se požene tako:
```shell
./Marjan.sh Resitev 50 1
```

Prevajanje in poganjanje posameznih programov:
----------
Prevajanje:
```shell
g++ -std=c++20 {Ime programa}
```
Poganjanje:
```shell
./a.out < {test01.in} > {test01.res}
```
Torej program `Resitev.cpp` se prevede in požene (izhod se zapiše v datoteko `test01.res`) tako:
```shell
g++ -std=c++20 Osvetlitev.cpp
./a.out < test01.in > test01.res
```

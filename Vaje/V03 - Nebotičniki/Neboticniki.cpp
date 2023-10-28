#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Glavna ideja je, da shranjujemo velikosti nebotičnikov (urejene po velikosti) v arr v2 in hkrati za vsak nabotičnik preverimo, koliko jih je manjših.
// Če ni noben manjši, v njega dodamo trenutni nebotičnik na 0. mesto. Če pa je manjši pa za bisekcijo najdemo točno mesto kam bi ga vstavili.
// Najprej povečamo SUM za št. nebotičnikov, ki so večji ali enaki njemu, nato ga vstavimo na to mesto.Na koncu še enkrat ponovimo postopek, 
// samo da gremo od zadaj naprej.

int main(){
    int N, x, velikost=1, min, max;
    long long SUM = 0;
    cin >> N;
    int *v = (int*)malloc(N*sizeof(int));
    int *v2 = (int*)malloc(N*sizeof(int));
    cin >> x;
    v[0] = x;
    v2[0] = x;
    for(int i = 1; i < N; i++){
        cin >> x;
        min = velikost - 1;
        max = 0;
        v[i] = x;
        if (x > v2[0]){
            v2[0] = x;
            velikost = 1;
            continue;
        }
        if (x <= v2[min]){
            SUM += velikost;
            v2[velikost] = x;
            velikost++;
            continue;
        }
        int polovica = (max + min) / 2;
        while (min - max > 1){
            if (v2[polovica] < x){
                min = polovica;
            }else if (v2[polovica] > x){
                max = polovica;
            }else{
                while (v2[min] < x){
                    min--;
                }
                min++;
                break;
            }
            polovica = (max + min) / 2;
        }
        SUM += min;
        v2[min] = x;
        velikost = min + 1;
    }
    v2[0] = v[N-1];
    velikost = 1;
    for(int i = N-2; i >= 0; i--){
        x = v[i];
        min = velikost - 1;
        max = 0;
        if (x > v2[0]){
            v2[0] = x;
            velikost = 1;
            continue;
        }
        if (x <= v2[min]){
            SUM += velikost;
            v2[velikost] = x;
            velikost++;
            continue;
        }
        int polovica = (max + min) / 2;
        while (min - max > 1){
            if (v2[polovica] < x){
                min = polovica;
            }else if (v2[polovica] > x){
                max = polovica;
            }else{
                while (v2[min] < x){
                    min--;
                }
                min++;
                break;
            }
            polovica = (max + min) / 2;
        }
        SUM += min;
        v2[min] = x;
        velikost = min + 1;
    }
    
    cout << SUM << "\n";

    return 0;
}
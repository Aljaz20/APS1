#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Najprej preberemo vsa vhodna števila in jih zapišemo v 2D array, kjer je vsaka četa v svoji "vrstici".
// Nato naredimo K arrayev in jih zlijemo v enega z uporabo funkcije "zlij".Nato ta novi array vstavimo nazaj v prvotnega (v array1, ki se potem prepiše v array).
// To ponovimo za vse čete. Če je array urejen (dolžina 1), prenehamo. Če je A = 0, prenehamo.
// Če ni urejen in je A > 0, A-- in na novo določimo meje med četami in ponovimo postopek.

vector<int> zlij(vector<vector<int>> novi, int sum, vector<int> poz1){
    vector<int> novi_array;
    vector<int> pozicije;
    for (int i = 0; i < (int)poz1.size(); i++){
        pozicije.push_back(0);
    }

    while(sum > 0){
        long min = 10000000000;
        int index = 0;
        for(int i = 0; i < (int)pozicije.size(); i++){
            if(pozicije[i] == poz1[i]){
                continue;
            }
            if(novi[i][pozicije[i]] < min){
                min = novi[i][pozicije[i]];
                index = i;
            }
        }
        pozicije[index]++;
        novi_array.push_back(min);
        
        sum--;
    }
    return novi_array;
}

int main(){
    int N, K, A;
    cin >> N >> K >> A;
    vector<vector<int>> array;
    int cete = 0;
    int prejsno = 0;
    array.push_back(vector<int>());
    for(int i = 0; i < N; i++){
        int stevilo;
        cin >> stevilo;
        if (stevilo < prejsno){
            cete++;
            array.push_back(vector<int>());
        }
        array[cete].push_back(stevilo);
        prejsno = stevilo;
    }

    while((int)array.size() > 1 && A > 0){
        vector<vector<int>> array2;
        for (int i = 0; i < (int)array.size(); i+= K){
            int l = K;
            if(i + K > (int)array.size()){
                l = array.size() - i;
            }
            vector<vector<int>> novi;
            vector<int> pozicije;
            int sum = 0;
            for(int j = 0; j < l; j++){
                novi.push_back(array[i+j]);
                pozicije.push_back((int)array[i+j].size());
                sum += (int)array[i+j].size();
            }

            vector<int> novi_array;
            novi_array = zlij(novi, sum, pozicije);
            array2.push_back(novi_array);

        }
        array = array2;
        A--;
    }

    for(int i = 0; i < (int)array.size(); i++){
        for(int j = 0; j < (int)array[i].size(); j++){
            cout << array[i][j] << endl;
        }
    }
    
    return 0;
}

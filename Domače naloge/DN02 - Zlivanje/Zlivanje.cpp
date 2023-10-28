#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Najprej preberemo vsa vhodna števila in jih zapišemo v 2D array, kjer je vsaka četa v svoji "vrstici".
// Nato naredimo K arrayev in jih zlijemo v enega z uporabo funkcije "zlij".Nato ta novi array vstavimo nazaj v prvotnega (v array1, ki se potem prepiše v array).
// To ponovimo za vse čete. Če je array urejen (dolžina 1), prenehamo. Če je A = 0, prenehamo.
// Če ni urejen in je A > 0, A-- in na novo določimo meje med četami in ponovimo postopek.

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
    vector<int> pozicije2(K);
    
    while(cete > 0 && A > 0){
        vector<vector<int>> array2;
        
        int size = cete + 1;
        
        for (int i = 0; i < size; i+= K){
            
            cete = i / K;
            int l = K;
            if(i + K > size){
                l = size - i;
            }
            
            int sum = 0;
            for(int j = 0; j < l; j++){
                int a = (int)array[i+j].size();
                sum += a;
                pozicije2[j] = a;
            }
            array2.push_back(vector<int>(sum));
            

            while(sum > 0){
                int max = 0;
                int index = 0;
                for(int k = 0; k < l; k++){
                    if(0 == pozicije2[k]){
                        continue;
                    }
                    if(array[k+i][pozicije2[k]-1] > max){
                        max = array[k+i][pozicije2[k]-1];
                        index = k;
                    }
                }
                pozicije2[index]--;
                array2[cete][sum-1] = max;
                
                sum--;
            }
        }
        array = array2;
        A--;
    }

    for(int i = 0; i <= cete; i++){
        for(int j = 0; j < (int)array[i].size(); j++){
            cout << array[i][j] << "\n";
        }
    }
    
    return 0;
}

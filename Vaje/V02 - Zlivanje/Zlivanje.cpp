#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Najprej preberemo vsa vhodna števila in jih zapišemo v array, medtem pa tudi prestejemo koliko čet je in zapišemo meje med četami.
// Nato naredimo K arrayev in jih zlijemo v enega z uporabo funkcije "zlij".Nato ta novi array vstavimo nazaj v prvotnega. To ponovimo za vse čete.
// Če je array urejen, prenehamo. Če je A = 0, prenehamo. Če ni urejen in je A > 0, A-- in na novo določimo meje med četami in ponovimo postopek.

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
    vector<int> array;
    vector<int> cete;
    for(int i = 0; i < N; i++){
        int stevilo;
        cin >> stevilo;
        if(i == 0 || stevilo < array[i-1]){
           cete.push_back(i);
        }
        array.push_back(stevilo);
    }

    while((int)cete.size() > 1 && is_sorted(array.begin(), array.end()) == false && A > 0){
        for(int i = 0; i < (int)cete.size(); i += K){
            int l = K;
            if(i + K > (int)cete.size()){
                l = cete.size() - i;
            }
            if ((l + i == (int)cete.size() && is_sorted(array.begin() + cete[i], array.end()) == true) || (l + i != (int)cete.size() && is_sorted(array.begin() + cete[i], array.begin() + cete[i+l]) == true)){
                continue;
            }
            vector<vector<int>> novi(l);
            vector<int> pozicije;
            int sum = 0;
            
            for(int j = 0; j < l; j++){
                if (i+j == (int) cete.size() - 1){
                    for(int k = cete[i+j]; k < N; k++){
                        novi[j].push_back(array[k]);
                    }
                    pozicije.push_back(N - cete[i+j]);
                    sum += N - cete[i+j];
                }else{
                    for(int k = cete[i+j]; k < cete[i+j+1]; k++){
                        novi[j].push_back(array[k]);
                    }
                    pozicije.push_back(cete[i+j+1] - cete[i+j]);
                    sum += cete[i+j+1] - cete[i+j];
                }
                
            }

            vector<int> novi_array;
            novi_array = zlij(novi, sum, pozicije);
            
            if (l + i == (int)cete.size()){
                array.erase(array.begin() + cete[i], array.end());
            }else{
                array.erase(array.begin() + cete[i], array.begin() + cete[i+l]);
            }
            for(int j = novi_array.size() -1 ; j >= 0; j--){
                array.insert(array.begin() + cete[i], novi_array[j]);
            }

        }
        vector <int> cete2;
        for (int i = 0; i < (int)cete.size(); i++){
            if (i % K == 0){
                cete2.push_back(cete[i]);
            }
        }
        cete = cete2;
        A--;
    }

    for(int i = 0; i < (int)array.size(); i++){
        cout << array[i] << endl;
    }
    
    return 0;
}

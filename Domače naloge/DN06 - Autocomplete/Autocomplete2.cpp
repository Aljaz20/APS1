#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

// za dodajanje uporabimo binary search, enako iskanje.

class Slovar {
private:
    vector<int> t;
    vector<string> besede;
    vector<int> pozicije;
public:
    void push(string s, int x, int poz) {
        int min = 0;
        int dolzina1 = (int)s.length();
        //int dolzina2, dolzina;
        int pozic = 0;

        if (t.size() == 0){
            t.push_back(x);
            besede.push_back(s);
            pozicije.push_back(poz);
            return;
        }
        if (primerjaj(s, t.size()-1, dolzina1) == 1){
            t.push_back(x);
            besede.push_back(s);
            pozicije.push_back(poz);
            pozic = t.size() - 1;
            return;
        }else{
            if (primerjaj(s, 0, dolzina1) == 1){
                int mid;
                int max = t.size() - 1;
                while (min < max){
                    mid = (min + max) / 2;
                    int rez = primerjaj(s, mid, dolzina1);
                    if (rez == -1){
                        max = mid;
                    }
                    else if (rez == 1){
                        min = mid + 1;
                    }else{
                        if (t[mid] < x){
                            t[mid]= x;
                            pozicije[mid]= poz;
                        }
                        return;
                    }
                }
                
            }
            
            pozic = min;
        }

        t.insert(t.begin() + pozic, x);
        besede.insert(besede.begin() + pozic, s);
        pozicije.insert(pozicije.begin() + pozic, poz);
        return;
    }

    int primerjaj (string s, int poz, int dolzina1) {
        int dolzina2 = (int)besede[poz].length();
        int dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
        for (int i = 0; i < dolzina; i++){
            if (s[i] < besede[poz][i]){
                return -1;
            }
            else if (s[i] > besede[poz][i]){
                return 1;
            }
        }
        if (dolzina1 < dolzina2){
            return -1;
        }else if (dolzina1 == dolzina2){
            return 0;
        }
        return 1;
    }

    void izpisi(){
        for (int i = 0; i < (int)t.size(); i++){
            cout << besede[i] << " " << t[i] << " " << pozicije[i] << endl;
        }
    }

    int poisci(string s){
        int min = 0;
        int dolzina1 = (int)s.length();
        int dolzina2, dolzina;
        if (primerjaj(s, t.size()-1, dolzina1) == 1){
            return 0;
        }else if(primerjaj(s, 0, dolzina1) != -1){
            int mid;
            int max = t.size() - 1;
            while (min < max){
                mid = (min + max) / 2;
                int rez = primerjaj(s, mid, dolzina1);
                if (rez != 1){
                    max = mid;
                }
                else{
                    min = mid + 1;
                }
            }
        }
        dolzina2 = (int)besede[min].length();
        dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
        for (int i = 0; i < dolzina; i++){
            if (s[i] < besede[min][i]){
                return 0;
            }
            else if (s[i] > besede[min][i]){
                return 0;
            }
        }
        
        int mid;
        int min1 = min;
        int max = t.size() - 1;
        while (min1 < max){
            int rez = 0;
            mid = (min1 + max) / 2;
            dolzina2 = (int)besede[min].length();
            dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
            for (int i = 0; i < dolzina; i++){
                if (s[i] < besede[mid][i]){
                    rez = -1;
                    break;
                }
                else if (s[i] > besede[mid][i]){
                    rez = 1;
                    break;
                }
            }
            if (rez != -1){
                min1 = mid + 1;
            }
            else{
                max = mid;
            }
        }
        min1 = max;
        dolzina2 = (int)besede[min1].length();
        dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
        for (int i = 0; i < dolzina; i++){
            if (s[i] < besede[min1][i]){
                min1--;
                break;
            }
            else if (s[i] > besede[min1][i]){
                min1--;
                break;
            }
        }
        min1++;
        /*
        if (s == "z"){
            cout << "min: " << min << " beseda " << besede[min] << " " << t[min] <<endl;
            cout << "max: " << min1 << " beseda " << besede[min1] << " " << t[min1] <<endl;
        }*/        
        
        max = t[min];
        int poz = pozicije[min];
        
        while (min < min1){
            if (t[min] > max){
                max = t[min];
                poz = pozicije[min];
            }
            min++;
        }
        return poz;      
    }

};

int main(){
    int N, x;
    string s;
    cin >> N;
    Slovar v;
    for (int i = 1; i <= N; i++){
        cin >> s >> x;
        v.push(s, x, i);
    }
    
    cin >> N;
    int *izpis = new int[N];
    for (int i = 0; i < N; i++){
        cin >> s;
        izpis[i] = v.poisci(s);
    }
    //v.izpisi();
    for (int i = 0; i < N; i++){
        cout << izpis[i] << endl;
    }
    return 0;
}

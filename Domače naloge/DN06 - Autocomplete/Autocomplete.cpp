#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
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
        int dolzina2, dolzina;
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
            
            int velikost = (int)t.size();
            while (min < velikost){
                dolzina2 = (int)besede[min].length();
                dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
                int rez = 0;
                for (int i = 0; i < dolzina; i++){                    
                    if (s[i] < besede[min][i]){
                        rez = -1;
                        
                        t.insert(t.begin() + pozic, x);
                        besede.insert(besede.begin() + pozic, s);
                        pozicije.insert(pozicije.begin() + pozic, poz);
                        break;
                    }
                }
                if (rez != -1){
                    if (t[min] >= x){
                        return;
                    }
                    if (min == velikost - 1){
                        t.insert(t.begin() + pozic, x);
                        besede.insert(besede.begin() + pozic, s);
                        pozicije.insert(pozicije.begin() + pozic, poz);
                    }
                }else{
                    break;
                }
                min++;
            }
        }
        
        min = pozic;
        while (min > 0){
            min--;
            dolzina2 = (int)besede[min].length();
            dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
            if (s[0] > besede[min][0]){
                return;
            }
            int pr = 0;
            for (int i = 0; i < dolzina; i++){
                if (s[i] != besede[min][i]){
                    pr = 1;
                    break;;
                }
            }
            if (pr == 1){
                continue;
            }
            if (t[min] < x){
                t.erase(t.begin() + min);
                besede.erase(besede.begin() + min);
                pozicije.erase(pozicije.begin() + min);
            }else{
                return;
            }
        }
        /*
        t.insert(t.begin() + pozic, temp);
        besede.insert(besede.begin() + pozic, s);
        */
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
                if (rez == -1){
                    max = mid;
                }
                else if (rez == 1){
                    min = mid + 1;
                }else{
                    min = mid;
                    break;
                }
            }
        }
        int max = 0;
        int poz = 0;
        while (min < (int)t.size()){
            dolzina2 = (int)besede[min].length();
            dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
            int rez = 0;
            for (int i = 0; i < dolzina; i++){
                if (s[i] < besede[min][i]){
                    rez = -1;
                    break;
                }
            }
            if (rez != -1){
                if (t[min] > max){
                    max = t[min];
                    poz = pozicije[min];
                }
            }else{
                break;
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

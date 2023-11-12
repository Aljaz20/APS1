#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// za dodajanje uporabimo binary search, enako iskanje.

int main(){
    int N, x;
    string s;
    cin >> N;
    //Slovar v;
    vector<int> t;
    vector<string> besede;
    vector<int> pozicije;
    cin >> s >> x;
    t.push_back(x);
    besede.push_back(s);
    pozicije.push_back(1);
    for (int i = 2; i <= N; i++){
        cin >> s >> x;
        int poz = i;
        int min = 0;
        int dolzina1 = (int)s.length();
        int dolzina2, dolzina;
        int pozic = 0;
        int bb = 0;
        int temp;

        int rez = 0;
        temp = t.size() - 1;
        dolzina2 = (int)besede[temp].length();
        dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
        for (int i = 0; i < dolzina; i++){
            if (s[i] < besede[temp][i]){
                rez = -1;
                break;
            }
            else if (s[i] > besede[temp][i]){
                rez = 1;
                break;
            }
        }
        if (rez == 0){
            if (dolzina1 < dolzina2){
                rez = -1;
            }else if (dolzina1 == dolzina2){
                rez = 0;
            }else{
                rez = 1;
            }
        }
        
        if (rez == 1){
            t.push_back(x);
            besede.push_back(s);
            pozicije.push_back(poz);
            pozic = t.size() - 1;
        }else{
            rez = 0;
            temp = 0;
            dolzina2 = (int)besede[temp].length();
            dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
            for (int i = 0; i < dolzina; i++){
                if (s[i] < besede[temp][i]){
                    rez = -1;
                    break;
                }
                else if (s[i] > besede[temp][i]){
                    rez = 1;
                    break;
                }
            }
            if (rez == 0){
                if (dolzina1 < dolzina2){
                    rez = -1;
                }else if (dolzina1 == dolzina2){
                    rez = 0;
                }else{
                    rez = 1;
                }
            }
            if (rez == 1){
                int mid;
                int max = t.size() - 1;
                while (min < max){
                    mid = (min + max) / 2;
                    rez = 0;
                    temp = mid;
                    dolzina2 = (int)besede[temp].length();
                    dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
                    for (int i = 0; i < dolzina; i++){
                        if (s[i] < besede[temp][i]){
                            rez = -1;
                            break;
                        }
                        else if (s[i] > besede[temp][i]){
                            rez = 1;
                            break;
                        }
                    }
                    if (rez == 0){
                        if (dolzina1 < dolzina2){
                            rez = -1;
                        }else if (dolzina1 == dolzina2){
                            rez = 0;
                        }else{
                            rez = 1;
                        }
                    }

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
                        bb = 1;
                        break;
                    }
                }
                
            }
            if (bb == 1){
                continue;
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
                        break;
                    }
                    if (min == velikost - 1){
                        t.insert(t.begin() + pozic, x);
                        besede.insert(besede.begin() + pozic, s);
                        pozicije.insert(pozicije.begin() + pozic, poz);
                    }
                }else{
                    bb = 1;
                    break;
                }
                min++;
            }
        }
        if (bb == 1){
            continue;
        }
        min = pozic;
        while (min > 0){
            min--;
            dolzina2 = (int)besede[min].length();
            dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
            if (s[0] > besede[min][0]){
                break;
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
                break;
            }
        }
        /*
        t.insert(t.begin() + pozic, temp);
        besede.insert(besede.begin() + pozic, s);
        */
    }
    /*
    for (int i = 0; i < (int)t.size(); i++){
        cout << besede[i] << " " << t[i] << " " << pozicije[i] << endl;
    }*/
    
    cin >> N;
    int *izpis = new int[N];

    for (int i = 0; i < N; i++){
        cin >> s;
        int min = 0;
        int dolzina1 = (int)s.length();
        int dolzina2, dolzina;
        int rez,temp;
        rez = 0;
        temp = t.size() - 1;
        dolzina2 = (int)besede[temp].length();
        dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
        for (int i = 0; i < dolzina; i++){
            if (s[i] < besede[temp][i]){
                rez = -1;
                break;
            }
            else if (s[i] > besede[temp][i]){
                rez = 1;
                break;
            }
        }
        if (rez == 0){
            if (dolzina1 < dolzina2){
                rez = -1;
            }else if (dolzina1 == dolzina2){
                rez = 0;
            }else{
                rez = 1;
            }
        }
        if (rez == 1){
            izpis[i] = 0;
            continue;
        }else{
            rez = 0;
            temp = 0;
            dolzina2 = (int)besede[temp].length();
            dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
            for (int i = 0; i < dolzina; i++){
                if (s[i] < besede[temp][i]){
                    rez = -1;
                    break;
                }
                else if (s[i] > besede[temp][i]){
                    rez = 1;
                    break;
                }
            }
            if (rez == 0){
                if (dolzina1 < dolzina2){
                    rez = -1;
                }else if (dolzina1 == dolzina2){
                    rez = 0;
                }else{
                    rez = 1;
                }
            }
            if(rez != -1){
                int mid;
                int max = t.size() - 1;
                while (min < max){
                    mid = (min + max) / 2;
                    rez = 0;
                    temp = mid;
                    dolzina2 = (int)besede[temp].length();
                    dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
                    for (int i = 0; i < dolzina; i++){
                        if (s[i] < besede[temp][i]){
                            rez = -1;
                            break;
                        }
                        else if (s[i] > besede[temp][i]){
                            rez = 1;
                            break;
                        }
                    }
                    if (rez == 0){
                        if (dolzina1 < dolzina2){
                            rez = -1;
                        }else if (dolzina1 == dolzina2){
                            rez = 0;
                        }else{
                            rez = 1;
                        }
                    }
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
        izpis[i] = poz;
    }
    //v.izpisi();
    for (int i = 0; i < N; i++){
        cout << izpis[i] << endl;
    }
    return 0;
}

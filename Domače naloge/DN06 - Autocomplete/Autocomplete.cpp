#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// najprej array z pozicijami glede na abecedni vrstni red, nato pa binary search

/*
class Slovar{
private:
    vector<pair<string, int>> t;
    int N;
public:
    Slovar(int n){
        N = n;
    }
    void dodaj(int poz, string beseda){
        t.push_back(make_pair(beseda, poz));
    }

    void sortiraj(){
        sort(t.begin(), t.end());
    }

    void izpisi(vector<int> stevila){
        for (int i = 0; i < N; i++){
            cout << t[i].first << " " << stevila[t[i].second - 1] << " " << t[i].second << endl;
        }
    }

    pair<string, int> operator[](int i){
        return t[i];
    }

    int poisci(string s, vector<int> stevila){
        int min = 0;
        int dolzina1 = (int)s.length();
        int dolzina2, dolzina;
        if (t[N-1].first.compare(s) < 0){
            return 0;
        }else if(t[0].first.compare(s) <= 0){
            int mid;
            int max = N - 1;
            while (min < max){
                mid = (min + max) / 2;
                int rez = t[mid].first.compare(s);
                if (rez > 0){
                    max = mid;
                }
                else if (rez < 0){
                    min = mid + 1;
                }else{
                    min = mid;
                    break;
                }
            }
        }
        int max = 0;
        int poz = 0;
        while (min < N){
            dolzina2 = (int)t[min].first.length();
            dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
            for (int i = 0; i < dolzina; i++){
                if (s[i] != t[min].first[i]){
                    return poz;
                }
            }
            if (stevila[t[min].second - 1] > max){
                max = stevila[t[min].second - 1];
                poz = t[min].second;
            }
            min++;
        }
        return poz;            
    }
};
*/


int main(){
    int N, x, M;
    string s;
    cin >> N;
    vector<int> stevila;
    vector <string> besede;
    vector <int> pozicije;
    for (int i = 0; i < N; i++){
        cin >> s >> x;
        stevila.push_back(x);
        besede.push_back(s);
        pozicije.push_back(i);
    }
    sort(pozicije.begin(), pozicije.end(), [&besede](int i1, int i2) {return besede[i1] < besede[i2];});
    /*
    for(int i = 0; i < N; i++){
        cout << besede[pozicije[i]] << " " << stevila[pozicije[i]] << " " << pozicije[i] + 1 << endl;
    }
    */
    cin >> M;
    int *rezultati = new int[M];
    for (int j = 0; j < M; j++){
        cin >> s;
        //rezultati[i] = v.poisci(s, stevila);
        int min = 0;
        int dolzina1 = (int)s.length();
        int dolzina2, dolzina;
        if (besede[pozicije[N-1]].compare(s) < 0){
            rezultati[j] = 0;
            continue;
        }else if(besede[pozicije[0]].compare(s) <= 0){
            int mid;
            int max = N - 1;
            while (min < max){
                mid = (min + max) / 2;
                int rez = besede[pozicije[mid]].compare(s);
                if (rez > 0){
                    max = mid;
                }
                else if (rez < 0){
                    min = mid + 1;
                }else{
                    min = mid;
                    break;
                }
            }
        }
        int max = 0;
        int poz = 0;
        while (min < N){
            dolzina2 = (int)besede[pozicije[min]].length();
            dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
            int preveri = 0;
            for (int i = 0; i < dolzina; i++){
                if (s[i] != besede[pozicije[min]][i]){
                    preveri = 1;
                    break;
                }
            }
            if (preveri == 0){
                if (stevila[pozicije[min]] > max){
                    max = stevila[pozicije[min]];
                    poz = pozicije[min] + 1;
                }
            }else{
                break;
            }
            
            min++;
        }
        rezultati[j] = poz;
    }

    for (int i = 0; i < M; i++){
        cout << rezultati[i] << "\n";
    }
    
    return 0;
}

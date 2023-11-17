#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// najprej sortiramo, nato pa binary search

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
        dolzina2 = (int)t[min].first.length();
        dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
        for (int i = 0; i < dolzina; i++){
            if (s[i] != t[min].first[i]){
                return 0;
            }
        }
        
        int mid;
        int min1 = min;
        int max = N - 1;
        while (min1 < max){
            int rez = 0;
            mid = (min1 + max) / 2;
            dolzina2 = (int)t[min].first.length();
            dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
            for (int i = 0; i < dolzina; i++){
                if (s[i] < t[mid].first[i]){
                    rez = -1;
                    break;
                }
                else if (s[i] > t[mid].first[i]){
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
        dolzina2 = (int)t[min1].first.length();
        dolzina = dolzina1 <= dolzina2 ? dolzina1 : dolzina2;
        for (int i = 0; i < dolzina; i++){
            if (s[i] < t[min1].first[i]){
                min1--;
                break;
            }
            else if (s[i] > t[min1].first[i]){
                min1--;
                break;
            }
        }
        min1++;    
        max = stevila[t[min].second - 1];
        int poz = t[min].second;
        
        while (min < min1){
            if (stevila[t[min].second - 1] > max){
                max = stevila[t[min].second - 1];
                poz = t[min].second;
            }
            min++;
        }
        return poz;             
    }
};



int main(){
    int N, x, M;
    string s;
    cin >> N;
    Slovar v(N);
    vector<int> stevila;
    for (int i = 1; i <=N; i++){
        cin >> s >> x;
        v.dodaj(i, s);
        stevila.push_back(x);
    }
    v.sortiraj();
    //v.izpisi(stevila);

    cin >> M;
    vector<int> rezultati;
    for (int i = 0; i < M; i++){
        cin >> s;
        rezultati.push_back(v.poisci(s, stevila));
        
    }
    for (int i = 0; i < (int)rezultati.size(); i++){
        cout << rezultati[i] << endl;
    }

    return 0;
}

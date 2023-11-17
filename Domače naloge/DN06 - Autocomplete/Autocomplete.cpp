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
    int *rezultati = new int[M];
    for (int i = 0; i < M; i++){
        cin >> s;
        rezultati[i] = v.poisci(s, stevila);
    }

    for (int i = 0; i < M; i++){
        cout << rezultati[i] << "\n";
    }
    
    return 0;
}

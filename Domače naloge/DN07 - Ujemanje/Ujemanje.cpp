#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// 

pair <int, int> ujemanje(string s, string t){
    int s_dolzina = s.length();
    int t_dolzina = t.length();
    int prvi = -1;
    if (s_dolzina - count(s.begin(), s.end(), '*') > t_dolzina) {
        return make_pair(-1, -1);
    }
    int zadnji_znakt = 0;
    int zadnji_znaks = 0;
    size_t found = s.find('*', zadnji_znaks +1);
    if (found == string::npos){
        found = s_dolzina;
    }
    if(s[0] == '*'){
        prvi = 0;
    }else{
        
        string podniz = s.substr(0, found);
        for (int i = 0; i < (int)t_dolzina; i++){
            int preveri = 0;
            for(int j = 0; j < (int)found; j++){
                if (i + j >= t_dolzina){
                    return make_pair(-1, -1);
                }
                if (podniz[j] != t[i + j]){
                    if (podniz[j] == '?'){
                        continue;
                    }
                    preveri = 1;
                    break;
                }
            }
            if (preveri == 0){
                prvi = i;
                break;
            }
        }
        if (prvi == -1){
            return make_pair(-1, -1);
        }
        zadnji_znakt = found + prvi - 1;
        zadnji_znaks = found;
        if ((int)found == s_dolzina){
            return make_pair(prvi, zadnji_znakt);
        }
    }
    //cout << "prvi: " << prvi << endl;
    //cout << "zadnji_znakt: " << zadnji_znakt << endl;
    while (zadnji_znaks != s_dolzina - 1){
        size_t found = s.find('*', zadnji_znaks + 1);

        if (found == string::npos){
            found = s_dolzina;
        }
        
        string podniz = s.substr(zadnji_znaks + 1, found - zadnji_znaks - 1);
        //cout << "podniz: " << podniz << endl;
        if (podniz.length() != 0){
            int preveri = 0;
            for (int i = zadnji_znakt; i < t_dolzina; i++){
                preveri = 0;
                for(int j = 0; j < (int)podniz.length(); j++){
                    if (podniz[j] != t[i + j]){
                        if (i + j >= t_dolzina){
                            return make_pair(-1, -1);
                        }
                        if (podniz[j] == '?'){
                            continue;
                        }
                        preveri = 1;
                        break;
                    }
                }
                if (preveri == 0){
                    zadnji_znakt = i + podniz.length() - 1;
                    break;
                }
            }
            if (preveri == 1){
                return make_pair(-1, -1);
            }
        }else{
            zadnji_znaks += 1;
        }
        zadnji_znaks += podniz.length();
        //cout << "zadnji_znaks: " << zadnji_znaks << endl;
        //cout << "zadnji_znakt: " << zadnji_znakt << endl;
        if (zadnji_znakt >= t_dolzina){
            cout << "TUKAJ" << endl;
            return make_pair(-1, -1);
        }
    }

    return make_pair(prvi, zadnji_znakt);

    
}

int main(){
    int N;
    cin >> N;
    string s;
    string t;
    
    for (int i = 0; i < N; i++){
        cin >> s >> t;
        pair <int, int> rezultat = ujemanje(s, t);
        if (rezultat.first == -1){
            cout << -1 << endl;
        }else{
            cout << rezultat.first << " " << rezultat.second << endl;
        }
    }
    
    
    return 0;
}

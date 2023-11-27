#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// najprej preverimo ali je dolzina sploh v pravilnem območju. Besedo S razdelimo na manjše besede, ki so ločene s *. 

int main(){
    int N;
    cin >> N;
    string s;
    string t;
    
    for (int i = 0; i < N; i++){
        cin >> s >> t;
        int s_dolzina = s.length();
        int t_dolzina = t.length();
        int prvi = -1;
        int naprej = 0;
        if (s_dolzina - count(s.begin(), s.end(), '*') > t_dolzina) {
            cout << -1 << endl;
            continue;
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
                        naprej = 1;
                        break;
                    }                
                    if (podniz[j] != t[i + j] && podniz[j] != '?'){
                        preveri = 1;
                        break;
                    }
                }
                if (preveri == 0 || naprej == 1){
                    prvi = i;
                    break;
                }
            }
            if (prvi == -1 || naprej == 1){
                cout << -1 << endl;
                continue;
            }
            zadnji_znakt = found + prvi - 1;
            zadnji_znaks = found;
            if ((int)found == s_dolzina){
                cout << prvi << " " << zadnji_znakt << endl;
                continue;
            }
        }
        
        
        while (zadnji_znaks != s_dolzina - 1){
            size_t found = s.find('*', zadnji_znaks + 1);

            if (found == string::npos){
                found = s_dolzina;
            }
            
            string podniz = s.substr(zadnji_znaks + 1, found - zadnji_znaks - 1);
           
            if (podniz.length() > 0){
                int preveri = 0;
                for (int i = zadnji_znakt + 1; i < t_dolzina; i++){
                    preveri = 0;
                    for(int j = 0; j < (int)podniz.length(); j++){
                        if (i + j >= t_dolzina){
                            naprej = 1;
                            break;
                        }
                        if (podniz[j] != t[i + j] && podniz[j] != '?'){
                            preveri = 1;
                            break;
                        }
                    }
                    if (preveri == 0 || naprej == 1){
                        zadnji_znakt = i + podniz.length() - 1;
                        break;
                    }
                }
                if (preveri == 1 || naprej == 1){
                    naprej = 1;
                    break;
                }
            }else{
                zadnji_znaks += 1;
            }
            zadnji_znaks += podniz.length();
            //cout << "zadnji_znaks: " << zadnji_znaks << endl;
            //cout << "zadnji_znakt: " << zadnji_znakt << endl;
            if (zadnji_znakt >= t_dolzina || naprej == 1){
                naprej = 1;
                break;
            }
        }
        if (naprej != 1){
            cout << prvi << " " << zadnji_znakt << endl;
        }else{
            cout << -1 << endl;
        }
    }
    
    
    return 0;
}

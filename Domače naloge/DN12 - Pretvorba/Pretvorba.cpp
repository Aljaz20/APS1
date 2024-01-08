#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string.h>
using namespace std;

// Najprej naredimo tabelo in v njej izracunamo najcenejso pot/pretvorbo in nato rekonstruiramo pot/pretvorbo.

string S_x;
string T_y;
int cena_zamenjave;
int cena_dodajanja;
int cena_brisanja;

/*
string LCS(string s, string t, int &lcs_len) {
    int n=s.size(), m=t.size();
    int lcs[n+1][m+1]; // dodatna vrstica in stolpec nicel
    memset(lcs,0,sizeof(lcs));
    for (int i=n-1;i>=0;i--) {
        for (int j=m-1;j>=0;j--) {
            lcs[i][j]=max(lcs[i+1][j], lcs[i][j+1]);
            if (s[i]==t[j]) lcs[i][j]=max(lcs[i][j], 1+lcs[i+1][j+1]);
        }
    }
    lcs_len= lcs[0][0];
    // izpis izracunane tabele
    
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            cout << lcs[i][j] << '\t';
        }
        cout << endl;
    }
    // rekonstrukcija vseh najdaljsih podzaporedij

    string l="";
    int i=0, j=0;
    while (i<n && j<m) {
        if (lcs[i][j]==lcs[i+1][j]) i++;
        else if (lcs[i][j]==lcs[i][j+1]) j++;
        else { l+=s[i]; i++; j++; }
    }
    return l;
    
}
*/

// REKURZIJA - počasna
/*
void najkrajsa(int x, int y, int **cene){
    // po y brises; po x dodajas; po diagonali zamenjas
    if (cene[y][x] > cene[0][0] && cene[0][0] != -1){
        return;
    }
    if (x == 0){
        if (y == 0){
            return;
        }
        else{
            int temp = cene[y][x] + cena_dodajanja;
            if ((cene[y-1][x] > temp) || (cene[y-1][x] == -1)){
                cene[y-1][x] = temp;
                najkrajsa(x, y-1, cene);
            }
            
        }
    }else if (y == 0){
        int temp = cene[y][x] + cena_brisanja;
        if ((cene[y][x-1] > temp) || (cene[y][x-1] == -1)){
            cene[y][x-1] = temp;
            najkrajsa(x-1, y, cene);
        }
    }else{
        int temp = cene[y][x];
        if (S_x[x-1] == T_y[y-1]){
            if (temp < cene[y-1][x-1] || cene[y-1][x-1] == -1){
                cene[y-1][x-1] = temp;
                najkrajsa(x-1, y-1, cene);
                return;
            }
        }else{
            temp += cena_zamenjave;
            if (temp < cene[y-1][x-1] || cene[y-1][x-1] == -1){
                cene[y-1][x-1] = temp;
                najkrajsa(x-1, y-1, cene);
            }
        }
        
        temp = cene[y][x] + cena_brisanja;
        if (temp < cene[y][x-1] || cene[y][x-1] == -1){
            cene[y][x-1] = temp;
            najkrajsa(x-1, y, cene);
        }
        temp = cene[y][x] + cena_dodajanja;
        if (temp < cene[y-1][x] || cene[y-1][x] == -1){
            cene[y-1][x] = temp;
            najkrajsa(x, y-1, cene);
        }
    }
}
*/


int main(){
    cin >> cena_dodajanja >> cena_brisanja >> cena_zamenjave;
    cin >> S_x >> T_y;

    int x = S_x.size();
    int y = T_y.size();

    int zam = 0;
    int dod = 0;
    int bris = 0;
    int enaki = 0;

    int cene[1100][1100];
    cene[0][0] = 0;

    // napolnimo prvo vrstico in prvi stolpec
    for (int i = 1; i < y+1; i++){
        cene[i][0] = cene[i-1][0] + cena_dodajanja;
    }

    for(int j = 1; j < x+1; j++){
        cene[0][j] = cene[0][j-1] + cena_brisanja;
    }
    
    // napolnimo ostalo tabelo
    for (int i = 1; i < y+1; i++){
        for (int j = 1; j < x+1; j++){
            cene[i][j] = 0;
        }
    }

    for (int i = 1; i < y+1; i++){
        for (int j = 1; j < x+1; j++){
            if (S_x[j-1] == T_y[i-1]){
                cene[i][j] = cene[i-1][j-1];
            }else{
                int min = cene[i-1][j] + cena_dodajanja;
                if (min > cene[i][j-1] + cena_brisanja){
                    min = cene[i][j-1] + cena_brisanja;
                }
                if (min > cene[i-1][j-1] + cena_zamenjave){
                    min = cene[i-1][j-1] + cena_zamenjave;
                }
                cene[i][j] = min;
            }
        }
    }

    int xx = x;
    int yy = y;

    while (true){
        if (xx == 0){
            while(yy != 0){
                cene[yy][xx] = -1;
                yy--;
                dod++;
            }
            break;
        }
        else if (yy == 0){
            while(xx != 0){
                cene[yy][xx] = -1;
                xx--;
                bris++;
            }
            break;
        }else{
            if (S_x[xx-1] == T_y[yy-1]){
                cene[yy][xx] = -1;
                xx--;
                yy--;
                enaki++;
            }else{
                if (cene[yy][xx] == cene[yy-1][xx-1] + cena_zamenjave){
                    cene[yy][xx] = -1;
                    xx--;
                    yy--;
                    zam++;
                }else if (cene[yy][xx] == cene[yy][xx-1] + cena_brisanja){
                    cene[yy][xx] = -1;
                    xx--;
                    bris++;
                }else{
                    cene[yy][xx] = -1;
                    yy--;
                    dod++;
                }
            }
        }
    }
    /*
    for(int i = 0; i < y+1; i++){
        for(int j = 0; j < x+1; j++){
            cout << cene[i][j] << " ";
        }
        cout << endl;
    }
    */
    int skupaj = zam * cena_zamenjave + dod * cena_dodajanja + bris * cena_brisanja;
    cout << skupaj << endl;

    int i = 0;
    int j = 0;
    bool naprej = true;
    
    while(naprej){
        if (cene[j+1][i] == -1){
            // dodajanje
            cout << "+" << T_y[j] << " ";
            j++;
            continue;
        }else if(cene[j][i+1] == -1){
            // brisanje
            cout << "-" << S_x[i] << " ";
            i++;
            continue;
        }else if(cene[j+1][i+1] == -1){
            if (S_x[i] == T_y[j]){
                cout << S_x[i] << " ";
                i++;
                j++;
                continue;
            }else{
                // zamenjava
                cout << S_x[i] << ">" << T_y[j] << " ";
                i++;
                j++;
                continue;
            }
        }else{
            // naprej
            naprej = false;
        }
    }


    
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int M, N;
    cin >> M >> N;
    if (N == 0){
        cout << M << endl;
        return 0;
    }
    vector<pair<int, int>> luc(N);
    int stevec = 0;

    for (int i = 0; i < N; i++){
        int x, d;
        cin >> x >> d;
        if (d == 0){
            luc[i].first = 0;
            luc[i].second = 0;
            continue;
        }
        int levo = x-d;
        long desno = x+d;
        if (levo < 0){
            levo = 0;
        }
        if (desno > M){
            desno = M;
        }
        luc[i].first = levo;
        luc[i].second = (int) desno;
    }

    sort(luc.begin(), luc.end());
    int X_desno = 0;

    for (int i = 0; i < N; i++){
        if (luc[i].first == 0 && luc[i].second == 0){
            continue;
        }
        if (X_desno < luc[i].first){
            stevec += luc[i].first - X_desno;            
        }
        if (X_desno < luc[i].second){
            X_desno = luc[i].second;
        }

    }
    
    if (X_desno < M){
        stevec += M - X_desno;
    }
    cout << stevec << endl;
    // Maximalna časovna zahtevnost algoritma je O(N + N*log(N) + N) = O(N*log(N) + 2*N)
    return 0;
}

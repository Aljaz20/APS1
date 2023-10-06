#include <iostream>
using namespace std;

int main(){
    int M, N;
    cin >> M >> N;
    int osvetlitev[M];
    int stevec = 0;
    for(int i = 0; i < M; i++){
        osvetlitev[i] = 0;
    }
    for(int i = 0; i < N; i++){
        int x, d, j;
        cin >> x >> d;
        if (x == 0){
            continue;
        }
        if (x - d < 0){
            j = 0;
        }else{
            j = x-d;
        }
        for(j; j < x+d && j < M; j++){
            if(osvetlitev[j] == 1){
                continue;
            }else{
                stevec++;
                osvetlitev[j] = 1;
            }
        }
    }
    
    stevec = M - stevec;
    cout << stevec << endl;
    // Maximalna časovna zahtevnost algoritma je O((N+1)*M)
    return 0;
}
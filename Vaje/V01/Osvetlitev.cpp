#include <iostream>
using namespace std;

int main(){
    int M, N;
    cin >> M >> N;
    bool *osvetlitev;
    osvetlitev = (bool*)calloc(M,sizeof(bool));
    int stevec = 0;
    
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
            if(osvetlitev[j] == true){
                continue;
            }else{
                stevec++;
                osvetlitev[j] = true;
            }
        }
    }
    
    stevec = M - stevec;
    cout << stevec << endl;
    // Maximalna časovna zahtevnost algoritma je O((N+1)*M)
    return 0;
}
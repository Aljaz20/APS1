#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// 

int main(){
    short N;
    long k;
    cin >> N >> k;
    vector<long> seznam;
    
    int a, b;
    for (short i = 1; i <=N; i++){
        cin >> a >> b;
        float kvocient = (float)i / N;
        for (int j = a; j <= b; j++){
            double x = pow(log2(j), kvocient);
            long y = j * x;
            seznam.push_back(y);
        }
    }
    nth_element(seznam.begin(), seznam.begin()+k-1, seznam.end());
    cout << seznam[k-1] << endl;
    
    
    return 0;
}

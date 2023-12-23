#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// 

int main(){
    short N;
    long k, temp = 0, min, temp2 = -1;
    cin >> N >> k;
    vector<long> seznam;
    int a, b;
    float kv = (float)1 / N;
    if (N == 1){
        cin >> a >> b;
        a += k-1;
        double x = log(log2(a));
        x = exp(x);
        long y = a * x;
        cout << y << endl;
        return 0;
    }
    vector<pair<pair<pair<int, int>, int>, long>> meje;
    for (short i = 1; i <=N; i++){
        cin >> a >> b;
        float kvocient = (float)i / N;
        double x = log(log2(a)) * kvocient;
        x = exp(x);
        long y = a * x;
        meje.push_back(make_pair(make_pair(make_pair(a, b), i), y));
    }
    sort(meje.begin(), meje.end(), [](const pair<pair<pair<int, int>, int>, long> &a, const pair<pair<pair<int, int>, int>, long> &b){
        return a.second < b.second;
    });
    min = meje[0].second;
    long max = 0;
    for (int i = 0; i < N; i++){
        temp += meje[i].first.first.second - meje[i].first.first.first + 1;
        double x = log(log2(meje[i].first.first.second)) * kv * meje[i].first.second;
        x = exp(x);
        long t = meje[i].first.first.second * x;
        if (t > max){
            max = t;
        }
        if (temp >= k){          
            break;
        }
    }
    //cout << min << " " << max << endl;
    seznam.resize(max-min+1, 0);
    temp = 0;



    for (int i = 0; i < N; i++){
        int a = meje[i].first.first.first;
        int b = meje[i].first.first.second;
        int j = meje[i].first.second;
        seznam[meje[i].second-min] += 1;
        float kvocient = kv * j;
        long y;
        if (temp2 == -1){
            for (int j = a+1; j <= b; j++){
                double x = pow(log2(j), kvocient);
                y = j * x;
                //cout << y << " " << temp << endl;
                seznam[y-min] += 1;
            }
        }else{
            for (int j = a+1; j <= b; j++){
                double x = pow(log2(j), kvocient);
                y = j * x;
                if (y <= temp2){
                    seznam[y-min] += 1;
                }else{
                    break;
                }
            }
        }
        
        temp += b-a+1;
        if (i == N-1){
            y = 0;
            for (int j = 0; j < (int)seznam.size(); j++){
                y += seznam[j];
                if (y >= k){
                    temp2 = j+min;
                    break;
                }
            }
            cout << temp2 << endl;
            return 0;
        }
        if (temp >= k){
            y = 0;
            //cout << "temp: " << temp << endl;
            for (int j = 0; j < (int)seznam.size(); j++){
                y += seznam[j];
                //cout << min + j << " " << y << endl;
                if (y >= k){
                    temp2 = j+min;
                    break;
                }
            }
            if (temp2 <= meje[i+1].second){
                cout << temp2 << endl;
                return 0;
            }
        }
    }
    
    
    return 0;
}

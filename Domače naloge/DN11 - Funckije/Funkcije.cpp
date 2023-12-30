#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// 

int main(){
    int N;
    long k, temp, temp1;
    cin >> N >> k;
    vector<vector<long>> v(N+1);
    int a, b;
    long min = 1e12;
    long max = 1;
    long mid;

    int tt = 0;

    for(int i = 1; i <= N; i++){
        cin >> a >> b;
        v[i].push_back(a);
        v[i].push_back(b);
        v[i].push_back(0);
        float kvocient = (float)i / N;
        double x = log(log2(a)) * kvocient;
        x = exp(x);
        mid = a * x;
        if (mid < min){
            min = mid;
        }
        x = log(log2(b)) * kvocient;
        x = exp(x);
        mid = b * x;
        if (mid > max){
            max = mid;
        }
        v[i].push_back(mid);
    }
    temp = 0;
    temp1 = 0;
    
    while (min <= max){
        temp1 = 0;
        tt = 0;
        mid = (min + max) / 2;
        
        for (int i = 1; i <= N; i++){
            float kvocient = (float)i / N;
            int min1 = v[i][0];
            int max1 = v[i][1];
            int mid1;
            while (max1 > min1){
                mid1 = (min1 + max1) / 2;
                double x = log(log2(mid1)) * kvocient;
                x = exp(x);
                long y = mid1 * x;
                if (y < mid){
                    min1 = mid1 + 1;
                }
                else if (y > mid){
                    max1 = mid1 - 1;
                }
                else{
                    min1 = mid1;
                    break;
                }
            }
            double x = log(log2(min1)) * kvocient;
            x = exp(x);
            long y = min1 * x;
            if (y > mid || y > v[i][3]){
                min1--;
            }else if (y == mid){
                tt++;
                temp1--;
            }
            if (mid == 5467847135){
                //cout << y << " " << min1 << " " << v[i][0] << " " << v[i][1] << "-------" << endl;
            }
            //cout << y << endl;
            v[i][2] = min1;
            temp1 += min1 - v[i][0] + 1;

        }
        //cout << min << " " << mid << " " << max << " " << temp << " " << temp1 << " " << tt << endl;
        if (k > temp + temp1 && k <= temp + temp1 + tt){
            //cout << temp + temp1 << endl;
            break;
        }
        else if (k <= temp+ temp1){
            max = mid - 1;
            for(int i = 1; i <= N; i++){
                v[i][1] = v[i][2];
            }
        }
        else{
            min = mid + 1;
            temp += temp1 + tt;
            for(int i = 1; i <= N; i++){
                //v[i][3] += v[i][2] - v[i][0];
                if (v[i][0] <= v[i][2]){
                    v[i][0] = v[i][2] + 1;
                }
            }
        }
    }

    cout << mid << endl;
    
    
    return 0;
}

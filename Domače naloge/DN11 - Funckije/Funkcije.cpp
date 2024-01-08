#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// 

int main(){
    int N;
    long k, sum, isti;
    cin >> N >> k;
    vector<vector<int>> v(N+1);
    long a, b;
    long min = 0;
    long max = 1e15;
    long mid;

    for(int i = 1; i <= N; i++){
        cin >> a >> b;
        v[i].push_back(a);
        v[i].push_back(b);
    }
    mid = (min + max) / 2;
    
    while (min <= max){
        sum = 0;
        isti = 0;
        for (int i = 1; i <= N; i++){
            float kvocient = (float)i / N;
            long min1 = v[i][0];
            long max1 = v[i][1];
            long mid1;
            while (min1 < max1){
                mid1 = (min1 + max1) / 2;
                double x = log2(mid1);
                x = pow(x, kvocient);
                long y = mid1 * x;
                if (y < mid){
                    min1 = mid1 + 1;
                }
                else if (y > mid){
                    max1 = mid1;
                }
                else{
                    max1 = mid1;
                    break;
                }
            }
            
            double x = log2(max1);
            x = pow(x, kvocient);
            long y = max1 * x;
            if (y < mid){
                max1++;
            }else if (y == mid){
                isti++;
            }
            sum += max1 - v[i][0];
            

        }
        //cout << min << " " << mid << " " << max << " " << " " << sum << " " << isti << endl;
        if (k > sum && k <= sum + isti){
            break;
        }
        else if (k <= sum){
            max = mid;
        }
        else{
            min = mid + 1;
        }
        mid = (min + max) / 2;
    }

    cout << mid << endl;
    
    
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// za dodajanje v vreco uporabimo binary search, enako za odstranjevanje. Za prestej uporabimo binary search za min in max, nato pa odstejemo indeksa
// in pristejemo 1

class Vreca {
private:
    vector<int> t;
public:
    void push(int x) {
        if (t.size() == 0 || t[t.size() - 1] <= x){
            t.push_back(x);
            return;
        }
        int mid;
        int min = 0;
        int max = t.size() - 1;
        while (min < max){
            mid = (min + max) / 2;
            if (t[mid] > x){
                max = mid;
            }
            else if (t[mid] < x){
                min = mid + 1;
            }
            else{
                t.insert(t.begin() + mid, x);
                return;
            }
        }
        t.insert(t.begin() + min, x);
        
    }

    void remove(int x) {
        if (t.size() == 0 || t[t.size() - 1] < x){
            return;
        }
        int mid;
        int min = 0;
        int max = t.size() - 1;
        while (min < max){
            mid = (min + max) / 2;
            if (t[mid] > x){
                max = mid;
            }
            else if (t[mid] < x){
                min = mid + 1;
            }
            else{
                t.erase(t.begin() + mid);
                return;
            }
        }
        if (t[min] == x){
            t.erase(t.begin() + min);
        }
        
    }

    int size(){
        return (int)t.size();
    }

    void izpisi(){
        for (int i = 0; i < (int)t.size(); i++){
            cout << t[i] << " ";
        }
        cout << endl;
    }

    int prestej(int min, int max){
        int velikost = (int)t.size();
        if (max < min){
            int temp = min;
            min = max;
            max = temp;
        }
        if (velikost == 0 || max < t[0] || min > t[velikost - 1]){
            return 0;
        }
        int mid;
        int min1 = 0;
        int max1 = velikost - 1;
        if (min <= t[0]){
            min = 0;
        }
        else{
            while (min1 < max1){
                mid = (min1 + max1) / 2;
                if (t[mid] >= min){
                    max1 = mid;
                }
                else{
                    min1 = mid+1;
                }
            }
            if (t[min1] < min){
                min1++;
            }
            min = min1;
        }
        if (max >= t[velikost - 1]){
            max = velikost- 1;
        }
        else{
            max1 = velikost- 1;
            while (min1 < max1){
                mid = (min1 + max1) / 2;
                if (t[mid] <= max){
                    min1 = mid + 1;
                }
                else{
                    max1 = mid;
                }
            }
            if (t[max1] > max){
                max1--;
            }
            max = max1;
        }    
        return max - min + 1;
    }
};

int main(){
    int N, x, s;
    long long sum = 0;
    cin >> N;
    Vreca v;
    for (int i = 0; i < N; i++){
        cin >> s >> x;
        if (s < 0){
            v.push(x);
        }else if (s == 0){
            v.remove(x);
        }else{
            sum += v.prestej(x, s);
        }
    }
    cout << sum << endl;
    return 0;
}

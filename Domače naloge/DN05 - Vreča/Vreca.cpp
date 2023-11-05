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
        /*
        vector<int>::iterator it = upper_bound(t.begin(), t.end(), x);
        t.insert(it, x);
        */
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
        /*
        vector<int>::iterator it = lower_bound(t.begin(), t.end(), x);
        if (it != t.end() && *it == x){
            t.erase(it);
        }
        */
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
        /*
        vector<int>::iterator it1 = lower_bound(t.begin(), t.end(), min);
        vector<int>::iterator it2 = upper_bound(it1 , t.end(), max);
        return (int)(it2 - it1);
        */
        if (velikost == 0){
            return 0;
        }
        int mid;
        if (min <= t[0]){
            min = 0;
        }
        else if (min > t[velikost - 1]){
            min = velikost;
        }
        else{
            int min1 = 0;
            int max1 = velikost - 1;
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
        else if (max < t[0]){
            max = -1;
        }
        else{
            int min2 = min;
            int max2 = velikost- 1;
            while (min2 < max2){
                mid = (min2 + max2) / 2;
                if (t[mid] <= max){
                    min2 = mid + 1;
                }
                else{
                    max2 = mid;
                }
            }
            if (t[max2] > max){
                max2--;
            }
            max = max2;
        }
        if (min > max){
            return 0;
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

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Mediana je vedno na sredini. Elementi manjši od nje so v max-kopici, elementi večji od nje pa v min-kopici. Glede na to kakšno je naslednje število pa
// program izbira v katero kopico jo bo dal in če je potrebno mediano popravi.

class BinaryHeap_min {
private:
    vector<int> t={-1};
public:
    void push(int x) {
        t.push_back(x);
        int i=(int)t.size()-1;
        while (i>1 && t[i]<t[i/2]) {  // lift
            swap(t[i],t[i/2]);
            i/=2;
        }
    }

    int pull() {
        int x=t[1], i=1;
        t[1]=t.back(); t.pop_back();
        while (1) {  // sink
            int j=i;
            if (2*i<(int)t.size() && t[2*i]<t[j]) j=2*i;
            if (2*i+1<(int)t.size() && t[2*i+1]<t[j]) j=2*i+1;
            if (i==j) break;
            swap(t[i],t[j]);
            i=j;
        }
        return x;
    }

    int size(){
        return (int)t.size();
    }
};

class BinaryHeap_max {
private:
    vector<int> t={-1};
public:
    void push(int x) {
        t.push_back(x);
        int i=(int)t.size()-1;
        while (i>1 && t[i]>t[i/2]) {  // lift
            swap(t[i],t[i/2]);
            i/=2;
        }
    }

    int pull() {
        int x=t[1], i=1;
        t[1]=t.back(); t.pop_back();
        while (1) {  // sink
            int j=i;
            if (2*i<(int)t.size() && t[2*i]>t[j]) j=2*i;
            if (2*i+1<(int)t.size() && t[2*i+1]>t[j]) j=2*i+1;
            if (i==j) break;
            swap(t[i],t[j]);
            i=j;
        }
        return x;
    }

    int size(){
        return (int)t.size();
    }
};

int main(){
    int N, x, mediana;
    BinaryHeap_max min;
    BinaryHeap_min max;
    cin >> N;
    cin >> x;
    mediana = x;
    cout << mediana << "\n";
    for (int i = 1; i < N; i++){
        cin >> x;
        if (x >= mediana){
            max.push(x);
        }
        else{
            min.push(x);
        }

        if (min.size() > max.size()){
            max.push(mediana);
            mediana = min.pull();
        }
        else if (max.size() > min.size() + 1){
            min.push(mediana);
            mediana = max.pull();
        }
        
        cout << mediana << "\n";
    }    

    return 0;
}
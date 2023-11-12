#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Uporabimo statično drevo(SUM), ki ga zgradimo na začetku. V njega shranjujemo število elementov na intervalu.

class Vreca {
private:
    vector<int> t;
    int n=1048576; // 2^20
    struct Node { long sum, begin, end; };
    vector<Node> tree;
public:
    Vreca () {
        t.resize(n);
        tree.resize(2*n);
        build();
    }

    void push(int x){
        int id = x + n;
        tree[id] = {tree[id].sum+1, id-n, id-n+1};
        while (id > 1) {
            id /= 2;
            tree[id] = {tree[2*id].sum + tree[2*id+1].sum, tree[2*id].begin, tree[2*id+1].end};
        }
    }

    void pop(int x){
        int id = x + n;
        int temp = tree[id].sum > 0 ? tree[id].sum - 1 : 0;
        tree[id] = {temp, id-n, id-n+1};
        while (id > 1) {
            id /= 2;
            tree[id] = {tree[2*id].sum + tree[2*id+1].sum, tree[2*id].begin, tree[2*id+1].end};
        }
    }

    void build(int id=1) {
        if (id>=n) { tree[id] = {t[id-n], id-n, id-n+1}; return; }  // list
        int left=2*id, right=2*id+1;
        build(left); build(right);
        tree[id] = {tree[left].sum + tree[right].sum, tree[left].begin, tree[right].end};
    }

    long query(int l, int r, int id=1) {
        if (l<=tree[id].begin && tree[id].end<=r) return tree[id].sum;  // znotraj
        if (r<=tree[id].begin || tree[id].end<=l) return 0;           // zunaj
        return (query(l,r,2*id) + query(l,r,2*id+1));
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
            v.pop(x);
        }else{
            int temp;
            if (x > s){
                temp = x;
                x = s;
                s = temp;
            }
            sum += v.query(x, s+1);
        }
    }
    cout << sum << endl;
    return 0;
}

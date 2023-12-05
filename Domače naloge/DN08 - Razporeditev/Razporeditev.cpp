#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

// searchamo z uporabo DFS. nato pregledamo, če smo obiskali vsa vozlišča. Če smo - izpišemo, če nismo potem gremo na tisto oglišče. ki še ni bilo obiskano


template<typename T>
void print(vector<T> sez) {
    for (T x : sez) cout << x << " ";
    cout << endl;
}

int stevec = 1;
vector<short> skupine;
vector<vector<int>> sosedi;

void BFS(int n, int zacetek, vector<short> &skupine, vector<vector<int>> &sosedi) {
    stevec++;
    queue<int> q;
    q.push(zacetek); skupine[zacetek] = 1;
    while (!q.empty()) {
        int x=q.front(); q.pop();
        //seq.push_back(x);
        for (int y : sosedi[x]) {
            if (skupine[y] == 0) {
                q.push(y);
                stevec++;
                if (skupine[x] == 1) {
                    skupine[y] = 2;
                } else {
                    skupine[y] = 1;
                }
            }else{
                if (skupine[x] == skupine[y]) {
                    cout << -1 << endl;
                    exit(0);
                }
            }
        }
    }
    
    if (stevec != n) {
        while (skupine[zacetek] != 0) {
            zacetek++;
        }
        //cout << "zacetek: " << zacetek << " count: " << count << endl;
        BFS(n, zacetek, skupine, sosedi);
    }else{
        for (int i=1;i <=n ;i++) {
            cout << skupine[i] << "\n";
        }
        exit(0);
    }
}

void DFS(int n, int zacetek) {
    
    //cout << "zacetek: " << zacetek << endl;
    //cout << "count: " << count << endl;
    //cout << "n: " << n << endl;
    /*
    if (count == n) {
        for (int i=1;i <=n ;i++) {
            cout << skupine[i] << "\n";
        }
        cout << "count: " << count << endl;
        exit(0);
    }*/
    for (int y : sosedi[zacetek]) {
        if (skupine[y] == 0) {
            if (skupine[zacetek] == 1) {
                skupine[y] = 2;
            } else {
                skupine[y] = 1;
            }
            stevec++;
            //cout << "y: " << y << " stevec: " << stevec << endl;
            DFS(n, y);
        }else{
            if (skupine[zacetek] == skupine[y]) {
                cout << -1 << endl;
                exit(0);
            }
        }
    }
    if (zacetek == 1) {
        while (stevec < n) {
            while (skupine[zacetek] != 0) {
                zacetek++;
            }
            skupine[zacetek] = 1;
            stevec++;
            DFS(n, zacetek);
        }

    }
}

int main(){
    int n,m;
    cin >> n >> m;
    sosedi.resize(n+1);
    skupine.resize(n+1);
    int a,b;
    for (int i=0;i<m;i++) {
        cin >> a >> b;
        sosedi[a].push_back(b);
        sosedi[b].push_back(a);
    }
    /*
    for (int x=0;x<=n;x++) {
        cout << x << ": ";
        print(sosedi[x]);
    }*/
    skupine[1] = 1;
    //BFS(n, 1);
    DFS(n, 1);
    for (int i=1;i <=n ;i++) {
        cout << skupine[i] << "\n";
    }
    
    
    return 0;
}

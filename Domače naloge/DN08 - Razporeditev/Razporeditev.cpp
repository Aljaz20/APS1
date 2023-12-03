#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

// searchamo z uporabo BFS. nato pregledamo, če smo obiskali vsa vozlišča. Če smo - izpišemo, če nismo potem gremo na tisto oglišče. ki še ni bilo obiskano

typedef pair<int,int> PII;
typedef vector<pair<int,int>> VII;

template<typename T>
void print(vector<T> sez) {
    for (T x : sez) cout << x << " ";
    cout << endl;
}

void BFS(int n, vector<vector<int>> &sosedi, vector<int> &skupine, int count, int zacetek) {
    count++;
    queue<int> q;
    q.push(zacetek); skupine[zacetek] = 1;
    while (!q.empty()) {
        int x=q.front(); q.pop();
        //seq.push_back(x);
        for (int y : sosedi[x]) {
            if (skupine[y] == 0) {
                q.push(y);
                count++;
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
    
    if (count != n) {
        while (skupine[zacetek] != 0) {
            zacetek++;
        }
        //cout << "zacetek: " << zacetek << " count: " << count << endl;
        BFS(n, sosedi, skupine, count, zacetek);
    }else{
        for (int i=1;i <=n ;i++) {
            cout << skupine[i] << "\n";
        }
        exit(0);
    }
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> sosedi(n+1);
    for (int i=0;i<m;i++) {
        int a,b;
        cin >> a >> b;
        sosedi[a].push_back(b);
        sosedi[b].push_back(a);
    }
    /*
    for (int x=0;x<=n;x++) {
        cout << x << ": ";
        print(sosedi[x]);
    }*/

    vector<int> skupine(n+1);
    BFS(n,sosedi,skupine, 0, 1);
    
    
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

// 2 counterja, ki hranita najkrajso in 2. najkrajso pot pot do vozlisca N-1

int najkrajsa = 1000000000;
int druga = 1000000000;
short obiskani[2001];
vector<vector<pair<int, int>>> povezave;

void poti(int trenutno, int dolzina, int n){
    if (trenutno == n){
        if (dolzina < najkrajsa){
            druga = najkrajsa;
            najkrajsa = dolzina;
        }
        else if (dolzina < druga){
            druga = dolzina;
        }
        return;
    }

    for (int i = 0; i < (int)povezave[trenutno].size(); i++){
        if (obiskani[povezave[trenutno][i].first] == 0){
            obiskani[povezave[trenutno][i].first] = 1;
            poti(povezave[trenutno][i].first, dolzina + povezave[trenutno][i].second, n);
            obiskani[povezave[trenutno][i].first] = 0;
        }
    }

}

void Dijkstra_BQ(vector<vector<pair<int,int>>> &adjw, int start, vector<int> &dist, vector<int> &dist2) {
    int n=adjw.size();
    dist=vector<int>(n,-1); 
    dist2=vector<int>(n,-1);
    int c=0;  // maximum weight
    for (int x=0;x<n;x++) for (auto [y,w] : adjw[x]) c=max(c, w);
    int maxd=(n-1)*c;
    vector<vector<int>> bq(maxd+1);  // bucket queue
    dist[start]=0; bq[0].push_back(start);
    dist2[start]=-1;
    for (int d=0;d<=maxd;d++) {
        for (int x : bq[d]) {
            if (dist[x]!=d) continue;  // ignore old values

            for (auto [y,w] : adjw[x]) {  // update neighbors
                
                int d=dist[x]+w;
                int d2= dist2[x] == -1 ? 100000000 : dist2[x] + w;
                //cout << "x: " << x << " y: " << y << " w: " << w << " d[x]: " << dist[x] << " d2[x]: " << dist2[x] << " d[y]: " << dist[y] << " d2[y]: " << dist2[y] << endl;

                if (dist[y]==-1) {  // new node
                    dist[y]=d;
                    if (dist2[y]==-1) dist2[y]=d2;
                    bq[d].push_back(y);
                } else if (d<dist[y]) {  // better path
                    if (d2 < dist[y]){
                        dist2[y] = dist[y];
                        dist[y] = d;
                    }
                    else{
                        dist2[y] = dist[y];
                    }
                    dist[y]=d;
                    bq[d].push_back(y);
                } else if (d<dist2[y] || dist2[y] == -1){  // better 2nd path
                    dist2[y]=d;
                    bq[d].push_back(y);
                }
                if (dist2[y] == 100000000) dist2[y] = -1;
                //cout << "x: " << x << " y: " << y << " w: " << w << " d[x]: " << dist[x] << " d2[x]: " << dist2[x] << " d[y]: " << dist[y] << " d2[y]: " << dist2[y] << endl;

            }
        }
    }

}


int main(){
    int N, M;
    cin >> N >> M;
    povezave.resize(N+1);
    int a, b, x;
    for(int i = 0; i < M; i++){
        cin >> a >> b >> x;
        povezave[a].push_back({b, x});
        povezave[b].push_back({a, x});
    }

    obiskani[0] = 1;
    /*
    poti(0, 0, N-1);

    if (druga == 1000000000){
        cout << -1 << endl;
    }
    else{
        cout << druga << endl;
    }
    */
    vector<int> dist, dist2;
    Dijkstra_BQ(povezave, 0, dist, dist2);
    /*
    for (int i = 0; i < N; i++){
        cout << dist[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < N; i++){
        cout << dist2[i] << " ";
    }*/
    cout << dist2[N-1] << endl;
    
    
    
    return 0;
}

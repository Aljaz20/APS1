#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

// Z uporabo funckije Dijkstra_BQ iz predavanj naredimo 2 seznama razdalj od zacetka do vsakega vozlisca (dist in dist2)


/*
int najkrajsa = 1000000000;
int druga = 1000000000;
short obiskani[2001];


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

}*/
vector<vector<pair<int, int>>> adjw;
vector<int> obiskani;

void Dijkstra(vector<int> &dist, vector<int> &prev) {
    int n=adjw.size();
    dist=vector<int>(n,-1);
    prev = vector<int>(n,-1);
    vector<int> p(n,-1);  // provisional distance (-1=unvisited, -2=done)
    p[0]=0;
    while (1) {
        int x=-1;  // smallest provisional
        for (int i=0;i<n;i++) if (p[i]>=0) {
            if (x==-1 || p[i]<p[x]) x=i;
        }
        if (x==-1) break;
        dist[x]=p[x]; p[x]=-2;
        for (auto [y,w] : adjw[x]) {  // update neighbors
            int d=dist[x]+w;
            if (p[y]==-1 || (p[y]>=0 && d<p[y])) { 
                p[y]=d; prev[y] = x;
            }
        }
    }
}

void Dijkstra2(vector<int> &dist, vector<int> &dist2) {
    int n=adjw.size();
    dist=vector<int>(n,-1);
    vector<int> p(n,-1);  // provisional distance (-1=unvisited, -2=done)
    p[0]=0;
    while (1) {
        int x=-1;  // smallest provisional
        for (int i=0;i<n;i++) if (p[i]>=0) {
            if (x==-1 || p[i]<p[x]) x=i;
        }
        if (x==-1) break;
        dist[x]=p[x]; p[x]=-2;
        for (auto [y,w] : adjw[x]) {  // update neighbors
            int d=dist[x]+w;
            if (p[y]==-1 || (p[y]>=0 && d<p[y])) { 
                p[y]=d;
            }
        }
    }
}

void Dijkstra_BQ(vector<int> &dist, vector<int> &dist2) {
    int n=adjw.size();
    int start = 0;
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
                if (y == 0) continue;
                
                int d=dist[x]+w;
                int d2= dist2[x] == -1 ? 100000000 : dist2[x] + w;
                cout << "x: " << x << " y: " << y << " w: " << w << " d[x]: " << dist[x] << " d2[x]: " << dist2[x] << " d[y]: " << dist[y] << " d2[y]: " << dist2[y] << endl;

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
                cout << "x: " << x << " y: " << y << " w: " << w << " d[x]: " << dist[x] << " d2[x]: " << dist2[x] << " d[y]: " << dist[y] << " d2[y]: " << dist2[y] << endl;
                
            }
            obiskani[x] = 1;
        }
    }

}


int main(){
    int N, M;
    cin >> N >> M;
    adjw.resize(N+1);
    obiskani.resize(N+1);
    int a, b, x;
    for(int i = 0; i < M; i++){
        cin >> a >> b >> x;
        adjw[a].push_back({b, x});
        adjw[b].push_back({a, x});
    }
    /*
    obiskani[0] = 1;
    poti(0, 0, N-1);

    if (druga == 1000000000){
        cout << -1 << endl;
    }
    else{
        cout << druga << endl;
    }
    */
    vector<int> dist, dist2, prev;
    obiskani[0] = 1;
    //Dijkstra_BQ(dist, dist2);
    Dijkstra(dist, prev);
    if (dist[N-1] == -1){
        cout << -1 << endl;
        return 0;
    }
    int trenutno = N-1;
    int min = 100000000;
    int temp0 = 0;
    while (prev[trenutno] != -1){
        for (int i = 0; i < (int)adjw[prev[trenutno]].size(); i++){
            if (adjw[prev[trenutno]][i].first == trenutno){
                x = adjw[prev[trenutno]][i].second;
                //cout << "x: " << prev[trenutno] << " y: " << trenutno << " w: " << adjw[prev[trenutno]][i].second << endl;
                adjw[prev[trenutno]][i].second = 100000000;
                temp0 = i;
                break;
            }
        }
        vector<int> temp1, temp2;
        Dijkstra2(temp1, temp2);
        //cout << "temp1[N-1]: " << temp1[N-1] << endl;
        if (temp1[N-1] < min){
            min = temp1[N-1];
        }
        adjw[prev[trenutno]][temp0].second = x;
        trenutno = prev[trenutno];
    }
    /*
    for (int i = 0; i < N; i++){
        cout << i << ": " << dist[i] << " ";
    }
    cout << endl;*/
    /*
    for (int i = 0; i < N; i++){
        cout << i << ": " << dist2[i] << " ";
    }
    cout << dist[N-1] << endl;
    cout << dist2[N-1] << endl;*/
    if (min == 100000000){
        cout << -1 << endl;
    }
    else{
        cout << min << endl;
    }
    
    
    return 0;
}

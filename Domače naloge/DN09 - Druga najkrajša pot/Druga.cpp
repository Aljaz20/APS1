#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

// Uporabimo Dijkstrov algoritem iz predavanj. Nato pa za vsako povezavo, ki je na najkrajši poti, 
// spreminjamo njeno težo v 100000000, nato pa ponovno uporabimo Dijkstrov algoritem. 
// Tako dobimo najkrajšo pot, ki ne vsebuje vseh povezavav, ki so na najkrajši poti.


vector<vector<pair<int, int>>> adjw;

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

int main(){
    int N, M;
    cin >> N >> M;
    adjw.resize(N+1);
    
    int a, b, x;
    for(int i = 0; i < M; i++){
        cin >> a >> b >> x;
        adjw[a].push_back({b, x});
        adjw[b].push_back({a, x});
    }
    
    
    vector<int> dist, dist2, prev;
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
        Dijkstra(temp1, temp2);
        //cout << "temp1[N-1]: " << temp1[N-1] << endl;
        if (temp1[N-1] < min){
            min = temp1[N-1];
        }
        adjw[prev[trenutno]][temp0].second = x;
        trenutno = prev[trenutno];
    }
    if (min == 100000000){
        cout << -1 << endl;
    }
    else{
        cout << min << endl;
    }
    
    
    return 0;
}

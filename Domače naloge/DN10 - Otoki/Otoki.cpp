#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Hkrati zapisujemo vrednosti v graf in v vector<vector<int>> visine, ki nam pove, kje se nahajajo določene višine.
// Nato gremo od najvišje višine proti nižjim in za vsako višino preverimo, če se lahko povežemo z sosednjimi polji.
// Če se lahko, se povežemo in odštejemo en otok (najprej smo prišteli št. otokov na tej višini). Če se ne moremo povezati, gremo naprej.

vector<int> otoki;

class DisjointSet {  // Union-Find
public:
    vector<int> parent, size;
    DisjointSet(int n) {
        parent = vector<int>(n);
        size = vector<int>(n);
        for (int i=0;i<n;i++) {  // individual sets
            parent[i] = i;
            size[i] = 1;
        }
    }
    
    int root(int x) {  // find
        if (parent[x]==x) return x;  // reached the root        
        int r = root(parent[x]);
        parent[x] = r;  // path compression
        return r;
    }

    void join(int x, int y) {  // union by size
        //x=root(x); y=root(y);  // replace by roots
        if (x==y) return;
        if (size[x]>size[y]) swap(x,y);  // make x smaller
        parent[x] = y;  // attach to larger root
        size[y] += size[x];
    }
};

void morje(vector<int> graf, int V, int S, int max, vector<vector<int>> visine){
    DisjointSet ds(V*S);
    int dolzina = V*S;
    int x_root, y_root;
    int otok = 0;
    otoki[max] = 0;
    for (int i = max; i > 0; i--){
        for (int j = 0; j < (int)visine[i].size(); j++){
            int x = visine[i][j];
            otok += 1;
            
            if (x % S != 0 && graf[x-1] >= i){
                x_root = ds.root(x);
                y_root = ds.root(x-1);
                if (x_root != y_root){
                    ds.join(x_root, y_root);
                    otok--;
                }
            }
            if (x % S != S-1 && graf[x+1] >= i){
                x_root = ds.root(x);
                y_root = ds.root(x+1);
                if (x_root != y_root){
                    ds.join(x_root, y_root);
                    otok--;
                }
            }
            if (x >= S && graf[x-S] >= i){
                x_root = ds.root(x);
                y_root = ds.root(x-S);
                if (x_root != y_root){
                    ds.join(x_root, y_root);
                    otok--;
                }
            }
            if (x < dolzina-S && graf[x+S] >= i){
                x_root = ds.root(x);
                y_root = ds.root(x+S);
                if (x_root != y_root){
                    ds.join(x_root, y_root);
                    otok--;
                }
            }
        }
        otoki[i-1] = otok;
    }
}


int main(){
    int V, S;
    cin >> V >> S;
    vector<int> graf;
    vector<vector<int>> visine(100001);
    int max = 0;

    for (int i = 0; i < V; i++){
        for (int j = 0; j < S; j++){
            int x;
            cin >> x;
            graf.push_back(x);
            visine[x].push_back(i*S+j);
            if (x > max) max = x;
        }
    }

    otoki.resize(max+1);
    morje(graf, V, S, max, visine);

    for (int i = 0; i <= max; i++){
        cout << otoki[i] << endl;
    }
    
    
    return 0;
}

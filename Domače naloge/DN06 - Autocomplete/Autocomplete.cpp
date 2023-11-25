#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

// Ustvarimo trie node in potem še trie strukturo, del kode za trie je iz spleta

struct TrieNode {
    unordered_map<char, TrieNode*> naslednji;
    int moc;
    int pozicija;
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(char *beseda, int moc, int poz) {
        TrieNode* trenutni = root;
        bool vecje = false;
        for (int i = 0; beseda[i] != '\0'; i++) {
            char c = beseda[i];
            if (trenutni->naslednji.contains(c) != 1) {
                trenutni->naslednji[c] = new TrieNode();
                trenutni->naslednji[c]->moc = moc;
                trenutni->naslednji[c]->pozicija = poz;
            }
            trenutni = trenutni->naslednji[c];
            if (vecje){
                trenutni->moc = moc;
                trenutni->pozicija = poz;
            }else{
                if(trenutni->moc < moc) {
                    trenutni->moc = moc;
                    trenutni->pozicija = poz;
                    vecje = true;
                }
            }   
        }
    }

    int search(char *beseda) {
        TrieNode* trenutni = root;

        for (int i = 0; beseda[i] != '\0'; i++) {
            char c = beseda[i];
            if (trenutni->naslednji.contains(c) != 1) {
                return 0;
            }
            trenutni = trenutni->naslednji[c];
        }
        return trenutni->pozicija;
    }


    void izpisi1(TrieNode* trenutni, string beseda) {
        cout << beseda << " " << trenutni->moc << " " << trenutni->pozicija << endl;

        for (char c='a'; c <= 'z'; c++) {
            if (trenutni->naslednji.find(c) != trenutni->naslednji.end()) {
                //izpisi1(trenutni->naslednji[c], beseda + c);
                cout << c << " " << trenutni->naslednji[c]->moc << " " << trenutni->naslednji[c]->pozicija << endl;
            }
        }
    }

    void izpisi() {
        izpisi1(root, "");
    }
};

int main(){
    int N, x, M;
    string s;
    cin >> N;
    Trie trie;
    for (int i = 1; i <= N; i++) {
        cin >> s >> x;
        trie.insert(&s[0], x, i);
    }
    //trie.izpisi();

    cin >> M;
    vector <int> pozicije;
    for (int i = 1; i <= M; i++) {
        cin >> s;
        pozicije.push_back(trie.search(&s[0]));
    }

    for (int i = 0; i < M; i++) {
        cout << pozicije[i] << endl;
    }
    
    
    return 0;
}

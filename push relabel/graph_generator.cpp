#include <bits/stdc++.h>
using namespace std;

void runDFS(int u, const vector<vector<pair<int,int>>>& adj, vector<int>& used) {
    used[u] = 1;

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first;
        int w = adj[u][i].second; 
        if (!used[v]) {
            runDFS(v, adj, used);
        }
    }
}

bool connected(const vector<vector<pair<int,int>>>& adj) {
    if (adj.empty()) return false;

    vector<int> used(adj.size(), 0);
    runDFS(0, adj, used);

    for (int i = 0; i < used.size(); i++) {
        if (!used[i]) return false;
    }
    return true;
}

int main() {
    srand(time(nullptr));

    int n = rand() % 50;
    vector<vector<pair<int,int>>> adj(n);
    unordered_set<string> edges;


    for (int i = 0; i + 1 < n; i++) {
        int nxt = i + 1;
        int w = (rand() % 206) - 5;

        string key = to_string(i) + "-" + to_string(nxt);
        edges.insert(key);
        adj[i].push_back(make_pair(nxt, w));
    }

    for (int u = 0; u < n; u++) {
        int extra = 1 + rand() % ( (n > 1) ? (n - 1) : 1 );

        for (int k = 0; k < extra; k++) {
            int v = rand() % n;
            while (v == u) v = rand() % n;

            string key1 = to_string(u) + "-" + to_string(v);
            string key2 = to_string(v) + "-" + to_string(u);

            if (edges.count(key1) == 0 && edges.count(key2) == 0) {
                edges.insert(key1);
                int w = (rand() % 206) - 5;
                adj[u].push_back(make_pair(v, w));
            }
        }
    }

    if (!connected(adj))
        cout << "Nepovrzan graf\n";
    else
        cout << "Povrzan graf\n";

 
    int E = 0;
    for (int i = 0; i < adj.size(); i++) {
        E += adj[i].size();
    }

    
    cout << n << " " << E << "\n";

    for (int u = 0; u < adj.size(); u++) {
        for (int i = 0; i < adj[u].size(); i++) {
            cout << u << " "
                 << adj[u][i].first << " "
                 << adj[u][i].second << "\n";
        }
    }

    return 0;
}

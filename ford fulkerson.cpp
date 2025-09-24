#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long INF = (long long)4e18;

struct Edge {
    int to;
    long long cap;
    int rev;
};

struct FordFulkerson {
    int n;
    vector<vector<Edge>> G;
    vector<char> vis;

    FordFulkerson(int n) : n(n), G(n), vis(n) {}

    void addEdge(int u, int v, long long c) {
        Edge a = {v, c, (int)G[v].size()};
        Edge b = {u, 0, (int)G[u].size()};
        G[u].push_back(a);
        G[v].push_back(b);
    }

    long long dfs(int v, int t, long long f) {
        if (v == t) return f;
        vis[v] = 1;
        for (auto &e : G[v]) {
            if (e.cap > 0 && !vis[e.to]) {
                long long pushed = dfs(e.to, t, min(f, e.cap));
                if (pushed > 0) {
                    e.cap -= pushed;
                    G[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (true) {
            fill(vis.begin(), vis.end(), 0);
            long long pushed = dfs(s, t, INF);
            if (pushed == 0) break;
            flow += pushed;
        }
        return flow;
    }
};

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;
    FordFulkerson ff(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        ff.addEdge(u, v, c);
    }
    int s, t;
    cin >> s >> t;

    cout << ff.maxFlow(s, t) << "\n";
    return 0;
}

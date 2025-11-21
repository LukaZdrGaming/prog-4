#include <bits/stdc++.h>
using namespace std;

void applyPush(int x, int y,
               vector<int>& height,
               vector<int>& excess,
               vector<vector<int>>& cap,
               vector<vector<int>>& flow,
               queue<int>& active)
{
    int available = cap[x][y] - flow[x][y];
    int send = excess[x] < available ? excess[x] : available;

    flow[x][y] += send;
    flow[y][x] -= send;

    excess[x] -= send;
    excess[y] += send;


    if (send > 0 && excess[y] == send) {
        active.push(y);
    }
}

void applyRelabel(int u, int N,
                  vector<int>& height,
                  vector<int>& excess,
                  vector<vector<int>>& cap,
                  vector<vector<int>>& flow)
{
    int best = INT_MAX;

    for (int v = 0; v < N; v++) {
        int residual = cap[u][v] - flow[u][v];
        if (residual > 0) {
            if (height[v] < best) {
                best = height[v];
            }
        }
    }

    if (best != INT_MAX) {
        height[u] = best + 1;
    }
}

void processNode(int u, int N,
                 vector<int>& ptr,
                 vector<int>& height,
                 vector<int>& excess,
                 vector<vector<int>>& cap,
                 vector<vector<int>>& flow,
                 queue<int>& active)
{
    while (excess[u] > 0) {
        if (ptr[u] < N) {
            int v = ptr[u];

            if (cap[u][v] - flow[u][v] > 0 &&
                height[u] > height[v])
            {
                applyPush(u, v, height, excess, cap, flow, active);
            }
            else {
                ptr[u]++;
            }
        }
        else {
            applyRelabel(u, N, height, excess, cap, flow);
            ptr[u] = 0;
        }
    }
}

int computeMaxFlow(int s, int t, int N,
                   vector<int>& ptr,
                   vector<int>& height,
                   vector<int>& excess,
                   vector<vector<int>>& cap,
                   vector<vector<int>>& flow,
                   queue<int>& active)
{
    height.resize(N, 0);
    height[s] = N;

    flow.assign(N, vector<int>(N, 0));
    excess.assign(N, 0);
    excess[s] = INT_MAX;

 
    for (int i = 0; i < N; i++) {
        if (i != s) {
            applyPush(s, i, height, excess, cap, flow, active);
        }
    }

    ptr.assign(N, 0);

    while (!active.empty()) {
        int u = active.front();
        active.pop();

        if (u != s && u != t) {
            processNode(u, N, ptr, height, excess, cap, flow, active);
        }
    }

    int result = 0;

    for (int i = 0; i < N; i++) {
        result += flow[i][t];
    }

    return result;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> capacity;
    vector<vector<int>> flow;

    capacity.assign(n, vector<int>(n, 0));

    // read edges
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        capacity[a][b] = w;
    }

    int s, t;
    cin >> s >> t;

    vector<int> height;
    vector<int> excess;
    vector<int> ptr;

    queue<int> active;

    int result = computeMaxFlow(
        s, t, n,
        ptr, height, excess,
        capacity, flow,
        active
    );

    cout << result;
    return 0;
}

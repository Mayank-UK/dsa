#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// DFS for bridges: edge (u,v) is a bridge when v cannot reach u or above
// through any back edge, i.e. low[v] > tin[u].
void dfs(int u, int p, const vector<vector<int>>& adj,
         vector<int>& tin, vector<int>& low, vector<bool>& vis,
         int& timer, vector<pair<int, int>>& bridges) {
    vis[u] = true;
    tin[u] = low[u] = ++timer;

    for (int v : adj[u]) {
        if (v == p) continue;
        if (vis[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, u, adj, tin, low, vis, timer, bridges);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) bridges.push_back({u, v});
        }
    }
}

vector<pair<int, int>> findBridges(int n, const vector<vector<int>>& adj) {
    vector<int> tin(n + 1, -1), low(n + 1, -1);
    vector<bool> vis(n + 1, false);
    vector<pair<int, int>> bridges;
    int timer = 0;

    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs(i, -1, adj, tin, low, vis, timer, bridges);

    return bridges;
}

int main() {
    cout << "===================== Bridges =====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V + E)\n";
    cout << "  Space : O(V)\n";
    cout << "  Note  : undirected; an edge whose removal disconnects the graph\n\n";

    cout << "[Demo]\n";
    int n = 5;
    vector<vector<int>> adj(n + 1);
    auto addEdge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    // 1-2, 2-3, 1-3 (triangle), 3-4 (bridge), 4-5 (bridge)
    addEdge(1, 2); addEdge(2, 3); addEdge(1, 3); addEdge(3, 4); addEdge(4, 5);
    cout << "  graph : 1-2, 2-3, 1-3, 3-4, 4-5\n";
    cout << "  bridges : ";
    for (auto& b : findBridges(n, adj)) cout << "(" << b.first << "-" << b.second << ") ";
    cout << "(expected 3-4, 4-5)\n\n";

    cout << "[Cases]\n";
    cout << "  cycle 1-2-3-1 (no bridges) : ";
    vector<vector<int>> cyc(3 + 1);
    auto ce = [&](int u, int v) { cyc[u].push_back(v); cyc[v].push_back(u); };
    ce(1,2); ce(2,3); ce(3,1);
    for (auto& b : findBridges(3, cyc)) cout << "(" << b.first << "-" << b.second << ") ";
    cout << "(expected none)\n";
    cout << "  chain 1-2-3-4 : ";
    vector<vector<int>> chain(4 + 1);
    for (int i = 1; i < 4; i++) { chain[i].push_back(i+1); chain[i+1].push_back(i); }
    for (auto& b : findBridges(4, chain)) cout << "(" << b.first << "-" << b.second << ") ";
    cout << "(expected all 3 edges)\n\n";

    cout << "[Edge Cases]\n";
    cout << "  single node : ";
    for (auto& b : findBridges(1, vector<vector<int>>(1 + 1))) cout << "(" << b.first << "-" << b.second << ") ";
    cout << "(none)\n";
    cout << "  single edge 1-2 : ";
    vector<vector<int>> se(2 + 1);
    se[1].push_back(2); se[2].push_back(1);
    for (auto& b : findBridges(2, se)) cout << "(" << b.first << "-" << b.second << ") ";
    cout << "(expected 1-2)\n\n";

    return 0;
}

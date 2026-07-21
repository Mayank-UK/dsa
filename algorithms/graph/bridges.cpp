#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int u, int p, const vector<vector<int>>& adj, vector<int>& tin, vector<int>& low, vector<bool>& vis, int& timer, vector<pair<int, int>>& bridges) {
    vis[u] = true;
    tin[u] = low[u] = ++timer;

    for (int v : adj[u]) {
        if (v == p) continue;
        if (vis[v]) {
            // Back-edge found: update low of current vertex
            low[u] = min(low[u], tin[v]);
        } else {
            // Forward edge (tree edge)
            dfs(v, u, adj, tin, low, vis, timer, bridges);
            low[u] = min(low[u], low[v]);

            // Condition for a bridge
            if (low[v] > tin[u]) {
                bridges.push_back({u, v});
            }
        }
    }
}

void findBridges(int n, const vector<vector<int>>& adj) {
    vector<int> tin(n + 1, -1);
    vector<int> low(n + 1, -1);
    vector<bool> vis(n + 1, false);
    vector<pair<int, int>> bridges;
    int timer = 0;

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, -1, adj, tin, low, vis, timer, bridges);
        }
    }

    cout << "Bridges in the graph:\n";
    for (const auto& bridge : bridges) {
        cout << "Edge (" << bridge.first << " - " << bridge.second << ")\n";
    }
}

int main() {
    int n = 5; // Number of vertices (1-indexed)
    vector<vector<int>> adj(n + 1);

    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    // Graph structure with a bridge between 3 and 4
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(1, 3);
    addEdge(3, 4);
    addEdge(4, 5);

    findBridges(n, adj);

    return 0;
}
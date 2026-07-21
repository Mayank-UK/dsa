#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Updated dfs signature: adj passed as const reference
void dfs(int u, int p, const vector<vector<int>>& adj, vector<int>& tin, vector<int>& low, vector<bool>& vis, vector<bool>& isArticulation, int& timer) {
    vis[u] = true;
    tin[u] = low[u] = ++timer;
    int children = 0;

    for (int v : adj[u]) {
        if (v == p) continue;
        if (vis[v]) {
            // Back-edge found: update low of current vertex
            low[u] = min(low[u], tin[v]);
        } else {
            // Forward edge (tree edge)
            dfs(v, u, adj, tin, low, vis, isArticulation, timer);
            low[u] = min(low[u], low[v]);
            
            // Condition for non-root nodes
            if (low[v] >= tin[u] && p != -1) {
                isArticulation[u] = true;
            }
            children++;
        }
    }

    // Condition for root node
    if (p == -1 && children > 1) {
        isArticulation[u] = true;
    }
}

void findArticulationPoints(int n, const vector<vector<int>>& adj) {
    vector<int> tin(n + 1, -1);
    vector<int> low(n + 1, -1);
    vector<bool> vis(n + 1, false);
    vector<bool> isArticulation(n + 1, false);
    int timer = 0;

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, -1, adj, tin, low, vis, isArticulation, timer);
        }
    }

    cout << "Articulation points in the graph:\n";
    for (int i = 1; i <= n; i++) {
        if (isArticulation[i]) {
            cout << "Vertex " << i << "\n";
        }
    }
}

int main() {
    int n = 5; // Number of vertices (1-indexed)
    vector<vector<int>> adj(n + 1);

    // Graph edges: (1-2), (2-3), (1-3), (3-4), (4-5)
    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(1, 3);
    addEdge(3, 4);
    addEdge(4, 5);

    findArticulationPoints(n, adj);

    return 0;
}
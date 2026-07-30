#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// DFS computing discovery (tin) and low-link times. A non-root vertex u is
// articulation if some child v cannot reach above u (low[v] >= tin[u]); the
// root is articulation if it has more than one DFS child.
void dfs(int u, int p, const vector<vector<int>>& adj,
         vector<int>& tin, vector<int>& low, vector<bool>& vis,
         vector<bool>& isArt, int& timer) {
    vis[u] = true;
    tin[u] = low[u] = ++timer;
    int children = 0;

    for (int v : adj[u]) {
        if (v == p) continue;
        if (vis[v]) {
            low[u] = min(low[u], tin[v]);        // back edge
        } else {
            dfs(v, u, adj, tin, low, vis, isArt, timer);
            low[u] = min(low[u], low[v]);
            if (p != -1 && low[v] >= tin[u]) isArt[u] = true;  // non-root rule
            children++;
        }
    }
    if (p == -1 && children > 1) isArt[u] = true;  // root rule
}

vector<int> findArticulationPoints(int n, const vector<vector<int>>& adj) {
    vector<int> tin(n + 1, -1), low(n + 1, -1);
    vector<bool> vis(n + 1, false), isArt(n + 1, false);
    int timer = 0;

    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs(i, -1, adj, tin, low, vis, isArt, timer);

    vector<int> result;
    for (int i = 1; i <= n; i++) if (isArt[i]) result.push_back(i);
    return result;
}

int main() {
    cout << "============= Articulation Points =============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V + E)\n";
    cout << "  Space : O(V)\n";
    cout << "  Note  : undirected; a vertex whose removal disconnects the graph\n\n";

    cout << "[Demo]\n";
    int n = 5;
    vector<vector<int>> adj(n + 1);
    auto addEdge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    // 1-2, 2-3, 1-3, 3-4, 4-5  -> articulation points: 3 and 4
    addEdge(1, 2); addEdge(2, 3); addEdge(1, 3); addEdge(3, 4); addEdge(4, 5);
    cout << "  graph : 1-2, 2-3, 1-3, 3-4, 4-5\n";
    cout << "  articulation points : ";
    for (int x : findArticulationPoints(n, adj)) cout << x << " ";
    cout << "(expected 3, 4)\n\n";

    cout << "[Cases]\n";
    cout << "  simple chain 1-2-3-4-5 : ";
    vector<vector<int>> chain(5 + 1);
    for (int i = 1; i < 5; i++) { chain[i].push_back(i+1); chain[i+1].push_back(i); }
    for (int x : findArticulationPoints(5, chain)) cout << x << " ";
    cout << "(expected 2,3,4)\n";
    cout << "  complete graph K4 (none): ";
    vector<vector<int>> k4(4 + 1);
    auto ke = [&](int u, int v) { k4[u].push_back(v); k4[v].push_back(u); };
    ke(1,2); ke(1,3); ke(1,4); ke(2,3); ke(2,4); ke(3,4);
    for (int x : findArticulationPoints(4, k4)) cout << x << " ";
    cout << "(expected none)\n\n";

    cout << "[Edge Cases]\n";
    cout << "  single node : ";
    for (int x : findArticulationPoints(1, vector<vector<int>>(1 + 1))) cout << x << " ";
    cout << "(none)\n";
    cout << "  single edge 1-2 : ";
    vector<vector<int>> se(2 + 1);
    se[1].push_back(2); se[2].push_back(1);
    for (int x : findArticulationPoints(2, se)) cout << x << " ";
    cout << "(none)\n\n";

    return 0;
}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// DFS that collects every node reachable from u (one connected component).
void dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& comp) {
    visited[u] = true;
    comp.push_back(u);
    for (int v : adj[u]) {
        if (!visited[v]) dfs(v, adj, visited, comp);
    }
}

// All connected components of an undirected graph.
vector<vector<int>> findConnectedComponents(int n, const vector<vector<int>>& adj) {
    vector<bool> visited(n + 1, false);
    vector<vector<int>> components;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            vector<int> comp;
            dfs(i, adj, visited, comp);
            components.push_back(comp);
        }
    }
    return components;
}

static void printComponents(const vector<vector<int>>& comps) {
    cout << "  " << comps.size() << " component(s):\n";
    for (size_t i = 0; i < comps.size(); i++) {
        cout << "    C" << i + 1 << " : ";
        for (int x : comps[i]) cout << x << " ";
        cout << "\n";
    }
}

int main() {
    cout << "============= Connected Components =============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V + E)\n";
    cout << "  Space : O(V)\n";
    cout << "  Note  : undirected graph; DFS/BFS flood fill per component\n\n";

    cout << "[Demo]\n";
    int n = 7;
    vector<vector<int>> adj(n + 1);
    auto addEdge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    addEdge(1, 2); addEdge(2, 3); addEdge(4, 5);  // {1,2,3}, {4,5}, {6}, {7}
    cout << "  graph : 1-2, 2-3, 4-5; nodes 6,7 isolated\n";
    printComponents(findConnectedComponents(n, adj));
    cout << "\n";

    cout << "[Cases]\n";
    cout << "  fully connected chain:\n";
    vector<vector<int>> chain(5 + 1);
    for (int i = 1; i < 5; i++) { chain[i].push_back(i+1); chain[i+1].push_back(i); }
    printComponents(findConnectedComponents(5, chain));
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  no edges (n=4) : all isolated\n";
    printComponents(findConnectedComponents(4, vector<vector<int>>(4 + 1)));
    cout << "  single node    : ";
    printComponents(findConnectedComponents(1, vector<vector<int>>(1 + 1)));
    cout << "\n";

    return 0;
}

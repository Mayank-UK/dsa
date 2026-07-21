#include <iostream>
#include <vector>

using namespace std;

// DFS utility to traverse and collect all nodes in the current component
void dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& currentComponent) {
    visited[u] = true;
    currentComponent.push_back(u);

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited, currentComponent);
        }
    }
}

// Function to find all connected components in an undirected graph
void findConnectedComponents(int n, const vector<vector<int>>& adj) {
    vector<bool> visited(n + 1, false);
    vector<vector<int>> components;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            vector<int> currentComponent;
            dfs(i, adj, visited, currentComponent);
            components.push_back(currentComponent);
        }
    }

    cout << "Total Connected Components: " << components.size() << "\n";
    for (size_t i = 0; i < components.size(); i++) {
        cout << "Component " << i + 1 << ": ";
        for (int node : components[i]) {
            cout << node << " ";
        }
        cout << "\n";
    }
}

int main() {
    int n = 7; // Number of vertices (1-indexed)
    vector<vector<int>> adj(n + 1);

    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    // Graph with 2 separate components:
    // Component 1: 1-2-3
    // Component 2: 4-5, 6 (with 7 isolated)
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(4, 5);
    // Vertex 6 and 7 have no edges (or vertex 7 is isolated)

    findConnectedComponents(n, adj);

    return 0;
}
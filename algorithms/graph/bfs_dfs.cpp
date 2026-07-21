#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Breadth-First Search (BFS) implementation
void bfs(int start, int n, const vector<vector<int>>& adj) {
    vector<bool> visited(n + 1, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << "\n";
}

// Helper function for Depth-First Search (DFS)
void dfsUtil(int u, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfsUtil(v, adj, visited);
        }
    }
}

// Depth-First Search (DFS) implementation
void dfs(int start, int n, const vector<vector<int>>& adj) {
    vector<bool> visited(n + 1, false);
    cout << "DFS Traversal: ";
    dfsUtil(start, adj, visited);
    cout << "\n";
}

int main() {
    int n = 5; // Number of vertices (1-indexed)
    vector<vector<int>> adj(n + 1);

    // Helper lambda to add undirected edges
    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    // Constructing a sample graph:
    // 1 -- 2 -- 4
    // |    |
    // 3 -- 5
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(2, 5);
    addEdge(3, 5);

    int startNode = 1;

    cout << "Starting traversals from node " << startNode << ":\n";
    bfs(startNode, n, adj);
    dfs(startNode, n, adj);

    return 0;
}
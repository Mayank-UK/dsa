#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// First DFS to fill the stack with finishing times
void dfs1(int u, const vector<vector<int>>& adj, vector<bool>& vis, stack<int>& st) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs1(v, adj, vis, st);
        }
    }
    st.push(u);
}

// Second DFS on the transposed graph to collect nodes in an SCC
void dfs2(int u, const vector<vector<int>>& transposeAdj, vector<bool>& vis, vector<int>& component) {
    vis[u] = true;
    component.push_back(u);
    for (int v : transposeAdj[u]) {
        if (!vis[v]) {
            dfs2(v, transposeAdj, vis, component);
        }
    }
}

// Function to find all Strongly Connected Components using Kosaraju's Algorithm
void findStronglyConnectedComponents(int n, const vector<vector<int>>& adj) {
    vector<bool> vis(n + 1, false);
    stack<int> st;

    // Step 1: Fill vertices in stack according to their finishing times
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs1(i, adj, vis, st);
        }
    }

    // Step 2: Create the transpose graph (reverse all edges)
    vector<vector<int>> transposeAdj(n + 1);
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            transposeAdj[v].push_back(u);
        }
    }

    // Step 3: Process all vertices in the order defined by the stack
    fill(vis.begin(), vis.end(), false);
    vector<vector<int>> sccs;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (!vis[u]) {
            vector<int> component;
            dfs2(u, transposeAdj, vis, component);
            sccs.push_back(component);
        }
    }

    // Print the SCCs
    cout << "Strongly Connected Components (SCCs):\n";
    for (size_t i = 0; i < sccs.size(); i++) {
        cout << "SCC " << i + 1 << ": ";
        for (int node : sccs[i]) {
            cout << node << " ";
        }
        cout << "\n";
    }
}

int main() {
    int n = 5; // Number of vertices (1-indexed)
    vector<vector<int>> adj(n + 1);

    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v); // Directed edge
    };

    // Constructing a directed graph with multiple SCCs
    // SCC 1: 1 -> 3 -> 4 -> 1
    // SCC 2: 2 -> 1
    // SCC 3: 5 -> 4 (or isolated/directional)
    addEdge(1, 3);
    addEdge(3, 4);
    addEdge(4, 1);
    addEdge(2, 1);
    addEdge(4, 5);

    findStronglyConnectedComponents(n, adj);

    return 0;
}
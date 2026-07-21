#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// DFS helper function for Tarjan's SCC algorithm
void tarjanDFS(int u, const vector<vector<int>>& adj, vector<int>& tin, vector<int>& low, vector<bool>& onStack, stack<int>& st, int& timer, vector<vector<int>>& sccs) {
    tin[u] = low[u] = ++timer;
    st.push(u);
    onStack[u] = true;

    for (int v : adj[u]) {
        if (tin[v] == -1) {
            // If v is not visited, recurse on it
            tarjanDFS(v, adj, tin, low, onStack, st, timer, sccs);
            low[u] = min(low[u], low[v]);
        } else if (onStack[v]) {
            // If v is in the current recursion stack, update low of u (back-edge or cross-edge)
            low[u] = min(low[u], tin[v]);
        }
    }

    // If u is the root of an SCC, pop all nodes from the stack until u
    if (low[u] == tin[u]) {
        vector<int> currentComponent;
        while (true) {
            int v = st.top();
            st.pop();
            onStack[v] = false;
            currentComponent.push_back(v);
            if (v == u) break;
        }
        sccs.push_back(currentComponent);
    }
}

// Function to find all Strongly Connected Components using Tarjan's Algorithm
void findTarjanSCCs(int n, const vector<vector<int>>& adj) {
    vector<int> tin(n + 1, -1);
    vector<int> low(n + 1, -1);
    vector<bool> onStack(n + 1, false);
    stack<int> st;
    vector<vector<int>> sccs;
    int timer = 0;

    for (int i = 1; i <= n; i++) {
        if (tin[i] == -1) {
            tarjanDFS(i, adj, tin, low, onStack, st, timer, sccs);
        }
    }

    // Print the SCCs
    cout << "Strongly Connected Components (Tarjan's):\n";
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
    // SCC 3: 4 -> 5
    addEdge(1, 3);
    addEdge(3, 4);
    addEdge(4, 1);
    addEdge(2, 1);
    addEdge(4, 5);

    findTarjanSCCs(n, adj);

    return 0;
}
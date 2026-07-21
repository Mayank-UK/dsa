#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// DFS helper function for topological sort with cycle detection
bool dfsTopo(int u, const vector<vector<int>>& adj, vector<int>& visited, stack<int>& st) {
    visited[u] = 1; // Mark as currently visiting (recursion stack)

    for (int v : adj[u]) {
        if (visited[v] == 0) {
            if (!dfsTopo(v, adj, visited, st)) return false;
        } else if (visited[v] == 1) {
            // Cycle detected
            return false;
        }
    }

    visited[u] = 2; // Mark as fully processed
    st.push(u);     // Push to stack after all descendants are visited
    return true;
}

// Function to perform topological sorting using DFS
vector<int> topologicalSortDFS(int n, const vector<vector<int>>& adj) {
    // 0 = unvisited, 1 = visiting, 2 = visited
    vector<int> visited(n + 1, 0);
    stack<int> st;

    for (int i = 1; i <= n; i++) {
        if (visited[i] == 0) {
            if (!dfsTopo(i, adj, visited, st)) {
                cout << "Graph contains a cycle! Topological sort not possible.\n";
                return {};
            }
        }
    }

    // Extract elements from stack to form the topological order
    vector<int> topoOrder;
    while (!st.empty()) {
        topoOrder.push_back(st.top());
        st.pop();
    }

    return topoOrder;
}

int main() {
    int n = 6; // Number of vertices (1-indexed)
    vector<vector<int>> adj(n + 1);

    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v); // Directed edge from u to v
    };

    // Constructing a DAG (Directed Acyclic Graph)
    addEdge(6, 3);
    addEdge(6, 1);
    addEdge(5, 1);
    addEdge(5, 2);
    addEdge(3, 4);
    addEdge(4, 2);

    vector<int> result = topologicalSortDFS(n, adj);

    if (!result.empty()) {
        cout << "Topological Order (DFS): ";
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i] << (i == result.size() - 1 ? "" : " -> ");
        }
        cout << "\n";
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function to find topological ordering using Kahn's Algorithm
vector<int> topologicalSort(int n, const vector<vector<int>>& adj) {
    vector<int> inDegree(n + 1, 0);

    // Step 1: Compute in-degrees for all vertices
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            inDegree[v]++;
        }
    }

    // Step 2: Push all nodes with in-degree 0 into the queue
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topoOrder;

    // Step 3: Process the queue
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        // Reduce in-degree of adjacent vertices
        for (int v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Step 4: Check for cycles (if topoOrder doesn't contain all vertices)
    if (topoOrder.size() != n) {
        cout << "Graph contains a cycle! Topological sort not possible.\n";
        return {};
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
    // 5 -> 2, 5 -> 0 (let's use 1 to 6)
    // 6 -> 3, 6 -> 1, 5 -> 2, 5 -> 0(not valid here, 1 to 6)
    addEdge(6, 3);
    addEdge(6, 1);
    addEdge(5, 1);
    addEdge(5, 2);
    addEdge(3, 4);
    addEdge(4, 2);

    vector<int> result = topologicalSort(n, adj);

    if (!result.empty()) {
        cout << "Topological Order: ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i == result.size() - 1 ? "" : " -> ");
        }
        cout << "\n";
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// BFS to find if there is a path from source to sink in the residual graph
bool bfs(int s, int t, int n, const vector<vector<int>>& capacity, vector<vector<int>>& adj, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        auto [u, flow] = q.front();
        q.pop();

        for (int v : adj[u]) {
            // If v is not visited and there is available capacity
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                int new_flow = min(flow, capacity[u][v]);
                if (v == t)
                    return true;
                q.push({v, new_flow});
            }
        }
    }
    return false;
}

// Edmonds-Karp algorithm for Maximum Flow
int fordFulkerson(int s, int t, int n, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    int max_flow = 0;
    vector<int> parent(n + 1);
    int new_flow;

    // While there is an augmenting path using BFS
    while (bfs(s, t, n, capacity, adj, parent)) {
        int current_flow = INT_MAX;
        
        // Find the minimum residual capacity along the path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            current_flow = min(current_flow, capacity[u][v]);
        }

        // Update residual capacities of the edges and reverse edges
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= current_flow;
            capacity[v][u] += current_flow;
        }

        max_flow += current_flow;
    }

    return max_flow;
}

int main() {
    int n = 6; // Number of vertices (1-indexed)
    int source = 1, sink = 6;

    vector<vector<int>> capacity(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> adj(n + 1);

    auto addEdge = [&](int u, int v, int cap) {
        capacity[u][v] += cap; // Handle parallel edges if any
        adj[u].push_back(v);
        adj[v].push_back(u); // Add reverse edge for residual graph
    };

    // Constructing a flow network
    addEdge(1, 2, 16);
    addEdge(1, 3, 13);
    addEdge(2, 3, 10);
    addEdge(2, 4, 12);
    addEdge(3, 2, 4);
    addEdge(3, 5, 14);
    addEdge(4, 3, 9);
    addEdge(4, 6, 20);
    addEdge(5, 4, 7);
    addEdge(5, 6, 4);

    int maxFlow = fordFulkerson(source, sink, n, capacity, adj);
    cout << "Maximum Flow = " << maxFlow << "\n";

    return 0;
}
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Structure to represent a weighted edge for printing MST results
struct Edge {
    int u, v, weight;
};

// Function to run Prim's algorithm using a min-priority queue
void primMST(int n, const vector<vector<pair<int, int>>>& adj) {
    vector<bool> visited(n + 1, false);
    // Min-priority queue stores pairs of {weight, vertex}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    long long mstTotalWeight = 0;
    vector<Edge> mstEdges;

    // Start from vertex 1 with weight 0 (and parent 0)
    // We store {weight, current_vertex, parent_vertex}
    // Using a tuple or custom tracking struct for clean edge recording:
    // Let's store {weight, u, parent} in priority queue: {0, 1, 0}
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pqEdges;
    pqEdges.push({0, 1, 0}); // {weight, node, parent}

    while (!pqEdges.empty()) {
        auto [weight, u, parent] = pqEdges.top();
        pqEdges.pop();

        if (visited[u]) continue;

        visited[u] = true;
        if (parent != 0) {
            mstTotalWeight += weight;
            mstEdges.push_back({parent, u, weight});
        }

        // Iterate through all neighbors of u
        for (const auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int edgeWeight = neighbor.second;

            if (!visited[v]) {
                pqEdges.push({edgeWeight, v, u});
            }
        }
    }

    // Print the results
    cout << "Minimum Spanning Tree Total Weight (Prim's): " << mstTotalWeight << "\n";
    cout << "Edges in the MST:\n";
    for (const auto& edge : mstEdges) {
        cout << "(" << edge.u << " - " << edge.v << ") : weight " << edge.weight << "\n";
    }
}

int main() {
    int n = 4; // Number of vertices (1-indexed)
    vector<vector<pair<int, int>>> adj(n + 1);

    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Undirected graph
    };

    // Constructing a weighted undirected graph
    addEdge(1, 2, 1);
    addEdge(1, 3, 3);
    addEdge(2, 3, 1);
    addEdge(2, 4, 4);
    addEdge(3, 4, 2);

    primMST(n, adj);

    return 0;
}
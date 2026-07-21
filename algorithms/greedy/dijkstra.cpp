#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Function to compute shortest paths using Dijkstra's algorithm
void dijkstra(int n, int src, const vector<vector<pair<int, int>>>& adj) {
    // dist[i] stores the shortest distance from src to i
    vector<long long> dist(n + 1, LLONG_MAX);

    // Min-priority queue to store pairs of {distance, vertex}
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // If a shorter path to u has already been processed, skip
        if (d > dist[u]) continue;

        // Iterate through all neighbors of u
        for (const auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            // Relaxation step
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print shortest distances from source
    cout << "Shortest distances from source (" << src << "):\n";
    for (int i = 1; i <= n; i++) {
        cout << "Vertex " << i << " : ";
        if (dist[i] == LLONG_MAX)
            cout << "Unreachable\n";
        else
            cout << dist[i] << "\n";
    }
}

int main() {
    int n = 5; // Number of vertices (1-indexed)
    vector<vector<pair<int, int>>> adj(n + 1);

    // Adjacency list: {neighbor, weight}
    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Undirected graph
    };

    addEdge(1, 2, 4);
    addEdge(1, 3, 2);
    addEdge(2, 3, 1);
    addEdge(2, 4, 5);
    addEdge(3, 4, 8);
    addEdge(3, 5, 10);
    addEdge(4, 5, 2);

    int source = 1;
    dijkstra(source, n, adj);

    return 0;
}
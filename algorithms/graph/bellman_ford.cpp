#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Structure to represent a weighted edge
struct Edge {
    int u, v, weight;
};

// Function to run Bellman-Ford algorithm
void bellmanFord(int n, int src, const vector<Edge>& edges) {
    vector<long long> dist(n + 1, LLONG_MAX);
    dist[src] = 0;

    // Relax all edges V - 1 times
    for (int i = 1; i <= n - 1; i++) {
        for (const auto& edge : edges) {
            if (dist[edge.u] != LLONG_MAX && dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

    // Check for negative weight cycles
    for (const auto& edge : edges) {
        if (dist[edge.u] != LLONG_MAX && dist[edge.u] + edge.weight < dist[edge.v]) {
            cout << "Graph contains a negative weight cycle!\n";
            return;
        }
    }

    // Print shortest distances from source
    cout << "Vertex Distance from Source (" << src << "):\n";
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
    vector<Edge> edges = {
        {1, 2, -1},
        {1, 3, 4},
        {2, 3, 3},
        {2, 4, 2},
        {2, 5, 2},
        {4, 3, 5},
        {4, 1, 1},
        {5, 4, -3}
    };

    int source = 1;
    bellmanFord(n, source, edges);

    return 0;
}
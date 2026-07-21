#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to run Floyd-Warshall all-pairs shortest path algorithm
void floydWarshall(int n, const vector<vector<long long>>& graph) {
    // dist matrix initialized with the input graph weights
    vector<vector<long long>> dist = graph;

    // Main DP loops: Intermediate vertex k, Source i, Destination j
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // Check if paths through k are valid before updating
                if (dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int i = 1; i <= n; i++) {
        if (dist[i][i] < 0) {
            cout << "Graph contains a negative weight cycle!\n";
            return;
        }
    }

    // Print all-pairs shortest distances matrix
    cout << "All-Pairs Shortest Paths Matrix:\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] == LLONG_MAX)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << "\n";
    }
}

int main() {
    int n = 4; // Number of vertices (1-indexed)
    long long INF = LLONG_MAX;

    // Initialize adjacency matrix with INF
    vector<vector<long long>> graph(n + 1, vector<long long>(n + 1, INF));

    for (int i = 1; i <= n; i++) {
        graph[i][i] = 0; // Distance to self is 0
    }

    // Add weighted directed edges
    graph[1][3] = -2;
    graph[1][2] = 3;
    graph[2][4] = 1;
    graph[3][4] = 4;
    graph[3][2] = 5;

    floydWarshall(n, graph);

    return 0;
}
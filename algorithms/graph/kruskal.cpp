#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a weighted edge
struct Edge {
    int u, v, weight;
    
    // Comparator to sort edges by weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Disjoint Set Union (DSU) structure for cycle detection
struct DSU {
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }
};

// Function to run Kruskal's algorithm and find MST weight and edges
void kruskalMST(int n, vector<Edge>& edges) {
    // Step 1: Sort all edges in increasing order of weight
    sort(edges.begin(), edges.end());

    DSU dsu(n);
    vector<Edge> mstEdges;
    long long mstTotalWeight = 0;

    // Step 2: Iterate through sorted edges
    for (const auto& edge : edges) {
        // If including this edge does not cause a cycle
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mstEdges.push_back(edge);
            mstTotalWeight += edge.weight;
        }
    }

    // Print the results
    cout << "Minimum Spanning Tree Total Weight: " << mstTotalWeight << "\n";
    cout << "Edges in the MST:\n";
    for (const auto& edge : mstEdges) {
        cout << "(" << edge.u << " - " << edge.v << ") : weight " << edge.weight << "\n";
    }
}

int main() {
    int n = 4; // Number of vertices (1-indexed)
    vector<Edge> edges = {
        {1, 2, 1},
        {1, 3, 3},
        {2, 3, 1},
        {2, 4, 4},
        {3, 4, 2}
    };

    kruskalMST(n, edges);

    return 0;
}
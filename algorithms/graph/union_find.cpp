#include <iostream>
#include <vector>

using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
    int numComponents;

public:
    // Constructor to initialize DSU for n elements (1-indexed)
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        numComponents = n;
        for (int i = 1; i <= n; i++) {
            parent[i] = i; // Every element is its own parent initially
        }
    }

    // Find function with Path Compression
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression flattens the tree
    }

    // Union function by Rank
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            // Attach smaller rank tree under root of high rank tree
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
            numComponents--; // Merging two components reduces total count by 1
        }
    }

    // Check if two elements belong to the same set
    bool connected(int i, int j) {
        return find(i) == find(j);
    }

    // Return current number of disjoint components
    int getComponentCount() {
        return numComponents;
    }
};

int main() {
    int n = 5; // Number of elements (1-indexed)
    DSU dsu(n);

    // Perform union operations
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    dsu.unite(2, 4); // Connects {1, 2} and {3, 4} into a single component {1, 2, 3, 4}

    cout << "Are 1 and 3 connected? " << (dsu.connected(1, 3) ? "Yes" : "No") << "\n";
    cout << "Are 1 and 5 connected? " << (dsu.connected(1, 5) ? "Yes" : "No") << "\n";
    cout << "Total Disjoint Components: " << dsu.getComponentCount() << "\n";

    return 0;
}
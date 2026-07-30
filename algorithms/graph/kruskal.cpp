#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& o) const { return weight < o.weight; }
};

// DSU for cycle checks during MST construction.
struct DSU {
    vector<int> parent, rank_;
    DSU(int n) : parent(n + 1), rank_(n + 1, 0) {
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int i) { return parent[i] == i ? i : parent[i] = find(parent[i]); }
    void unite(int i, int j) {
        int ri = find(i), rj = find(j);
        if (ri == rj) return;
        if (rank_[ri] < rank_[rj]) parent[ri] = rj;
        else if (rank_[ri] > rank_[rj]) parent[rj] = ri;
        else { parent[rj] = ri; rank_[ri]++; }
    }
};

struct MST { long long totalWeight; vector<Edge> edges; };

// Kruskal: sort edges by weight, add each if it joins two different components.
MST kruskalMST(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());

    DSU dsu(n);
    long long total = 0;
    vector<Edge> taken;

    for (const auto& e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            taken.push_back(e);
            total += e.weight;
        }
    }
    return {total, taken};
}

int main() {
    cout << "==================== Kruskal MST ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(E log E)     dominated by the edge sort\n";
    cout << "  Space : O(V + E)\n";
    cout << "  Note  : greedy; picks the cheapest edge that doesn't form a cycle\n\n";

    cout << "[Demo]\n";
    int n = 4;
    vector<Edge> edges = {
        {1, 2, 1}, {1, 3, 3}, {2, 3, 1}, {2, 4, 4}, {3, 4, 2}
    };
    MST m = kruskalMST(n, edges);
    cout << "  total MST weight = " << m.totalWeight << "\n";
    cout << "  edges:\n";
    for (const auto& e : m.edges)
        cout << "    (" << e.u << " - " << e.v << ") w=" << e.weight << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  disconnected graph (no spanning tree):\n";
    vector<Edge> disc = {{1, 2, 5}};  // 4 nodes, only one edge
    MST md = kruskalMST(4, disc);
    cout << "    weight=" << md.totalWeight << ", edges taken=" << md.edges.size()
         << " (< " << 4 - 1 << " => forest, not a single tree)\n";
    cout << "  single node : weight=";
    {
        vector<Edge> none;
        cout << kruskalMST(1, none).totalWeight << "\n";
    }
    cout << "\n";

    return 0;
}

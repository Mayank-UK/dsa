#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <string>

using namespace std;

struct Edge { int u, v, weight; };

struct MST { long long totalWeight; vector<Edge> edges; };

// Greedy view of Prim: start with one vertex and grow a single tree by always
// adding the cheapest edge that crosses the cut (tree vs. rest). The cut
// property guarantees the cheapest crossing edge belongs to some MST, so the
// greedy choice is safe at every step.
MST primMST(int n, const vector<vector<pair<int, int>>>& adj) {
    vector<bool> inTree(n + 1, false);
    // {weight, vertex, parent}
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
                   greater<tuple<int, int, int>>> pq;

    long long total = 0;
    vector<Edge> edges;

    pq.push({0, 1, 0});
    while (!pq.empty()) {
        auto [w, u, parent] = pq.top(); pq.pop();
        if (inTree[u]) continue;
        inTree[u] = true;
        if (parent != 0) { total += w; edges.push_back({parent, u, w}); }
        for (const auto& [v, ew] : adj[u]) {
            if (!inTree[v]) pq.push({ew, v, u});
        }
    }
    return {total, edges};
}

int main() {
    cout << "================ Prim MST (Greedy) ================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(E log V)   binary-heap adjacency list\n";
    cout << "  Space : O(V + E)\n";
    cout << "  Note  : greedy cut-property; grows one tree by the cheapest crossing edge\n";
    cout << "          (see graph/prim.cpp for the same algorithm)\n\n";

    cout << "[Demo]\n";
    int n = 4;
    vector<vector<pair<int, int>>> adj(n + 1);
    auto addEdge = [&](int u, int v, int w) { adj[u].push_back({v, w}); adj[v].push_back({u, w}); };
    addEdge(1, 2, 1); addEdge(1, 3, 3); addEdge(2, 3, 1); addEdge(2, 4, 4); addEdge(3, 4, 2);
    MST m = primMST(n, adj);
    cout << "  total MST weight = " << m.totalWeight << "\n";
    cout << "  edges:\n";
    for (const auto& e : m.edges)
        cout << "    (" << e.u << " - " << e.v << ") w=" << e.weight << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  disconnected (4 nodes, one edge 1-2):\n";
    vector<vector<pair<int, int>>> disc(4 + 1);
    disc[1].push_back({2, 5}); disc[2].push_back({1, 5});
    MST md = primMST(4, disc);
    cout << "    weight=" << md.totalWeight << ", edges=" << md.edges.size()
         << " (< " << 4 - 1 << " => forest)\n";
    cout << "  single node : weight=" << primMST(1, vector<vector<pair<int,int>>>(1 + 1)).totalWeight << "\n";
    cout << "\n";

    return 0;
}

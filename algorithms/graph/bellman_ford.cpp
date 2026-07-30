#include <iostream>
#include <vector>
#include <climits>
#include <string>

using namespace std;

const long long INF = LLONG_MAX;

struct Edge { int u, v, weight; };

struct BFResult {
    vector<long long> dist;
    bool hasNegativeCycle;
};

// Bellman-Ford: relax every edge V-1 times, then one extra pass to detect a
// negative cycle. Handles negative edge weights (unlike Dijkstra).
BFResult bellmanFord(int n, int src, const vector<Edge>& edges) {
    vector<long long> dist(n + 1, INF);
    dist[src] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (const auto& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.weight;
            }
        }
    }

    // If anything still relaxes, a negative cycle is reachable.
    bool neg = false;
    for (const auto& e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v]) {
            neg = true; break;
        }
    }
    return {dist, neg};
}

static void printDist(const vector<long long>& dist, int src) {
    for (int i = 1; i < (int)dist.size(); i++) {
        cout << "    " << src << " -> " << i << " : ";
        if (dist[i] == INF) cout << "Unreachable\n"; else cout << dist[i] << "\n";
    }
}

int main() {
    cout << "==================== Bellman-Ford ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V * E)\n";
    cout << "  Space : O(V)\n";
    cout << "  Note  : single-source; handles NEGATIVE weights; detects negative cycles\n\n";

    cout << "[Demo]\n";
    int n = 5;
    // Canonical Bellman-Ford example (negative edges, NO negative cycle).
    vector<Edge> edges = {
        {1, 2, -1}, {1, 3, 4}, {2, 3, 3}, {2, 4, 2},
        {2, 5, 2}, {4, 3, 5}, {4, 2, 1}, {5, 4, -3}
    };
    auto r = bellmanFord(n, 1, edges);
    cout << "  directed graph with negative edges, source = 1\n";
    cout << "  negative cycle? " << (r.hasNegativeCycle ? "Yes" : "No") << "\n";
    cout << "  distances:\n";
    printDist(r.dist, 1);
    cout << "\n";

    cout << "[Cases]  (graph with a negative cycle: 1->2->3->1)\n";
    vector<Edge> cyc = {{1, 2, 1}, {2, 3, -3}, {3, 1, 1}};
    auto rc = bellmanFord(3, 1, cyc);
    cout << "  negative cycle? " << (rc.hasNegativeCycle ? "Yes (detected)" : "No") << "\n\n";

    cout << "[Edge Cases]\n";
    cout << "  single node   : dist(1->1) = " << bellmanFord(1, 1, {}).dist[1] << "\n";
    cout << "  no edges (n=3): ";
    auto d = bellmanFord(3, 1, {}).dist;
    cout << "1->3 = " << (d[3] == INF ? "Unreachable" : to_string(d[3])) << "\n";
    cout << "\n";

    return 0;
}

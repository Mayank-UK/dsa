#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>

using namespace std;

const long long INF = LLONG_MAX;

// Greedy view of Dijkstra: maintain a frontier of "settled" vertices whose
// shortest distance is final. Each step greedily finalizes the closest unsettled
// vertex, then relaxes its edges. Correctness rests on non-negative weights: a
// closer vertex can never be improved by routing through a farther one.
vector<long long> dijkstra(int n, int src, const vector<vector<pair<int, int>>>& adj) {
    vector<long long> dist(n + 1, INF);
    vector<bool> settled(n + 1, false);
    // Min-heap of {tentative distance, vertex}.
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (settled[u]) continue;     // stale heap entry; already finalized
        settled[u] = true;            // greedy choice: this is final

        for (const auto& [v, w] : adj[u]) {
            if (!settled[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

static void printDist(const vector<long long>& dist, int src) {
    for (int i = 1; i < (int)dist.size(); i++) {
        cout << "    " << src << " -> " << i << " : ";
        if (dist[i] == INF) cout << "Unreachable\n"; else cout << dist[i] << "\n";
    }
}

int main() {
    cout << "=============== Dijkstra (Greedy) ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O((V + E) log V)   binary-heap adjacency list\n";
    cout << "  Space : O(V)\n";
    cout << "  Note  : greedy finalize-closest-unsettled; NON-NEGATIVE weights only\n";
    cout << "          (see graph/dijkstra.cpp for the same algorithm framed as a graph traversal)\n\n";

    cout << "[Demo]\n";
    int n = 5;
    vector<vector<pair<int, int>>> adj(n + 1);
    auto addEdge = [&](int u, int v, int w) { adj[u].push_back({v, w}); adj[v].push_back({u, w}); };
    addEdge(1, 2, 4); addEdge(1, 3, 2); addEdge(2, 3, 1);
    addEdge(2, 4, 5); addEdge(3, 4, 8); addEdge(3, 5, 10); addEdge(4, 5, 2);
    cout << "  weighted undirected graph, source = 1\n";
    cout << "  shortest distances:\n";
    printDist(dijkstra(n, 1, adj), 1);
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  single node  : dist(1->1) = "
         << dijkstra(1, 1, vector<vector<pair<int,int>>>(1 + 1))[1] << "\n";
    vector<vector<pair<int, int>>> disc(3 + 1);
    disc[1].push_back({2, 5}); disc[2].push_back({1, 5});
    auto d = dijkstra(3, 1, disc);
    cout << "  disconnected : 1->3 = " << (d[3] == INF ? "Unreachable" : to_string(d[3])) << "\n";
    cout << "  greedy finalization is wrong on negative edges "
         << "(see graph/bellman_ford.cpp instead)\n";
    cout << "\n";

    return 0;
}

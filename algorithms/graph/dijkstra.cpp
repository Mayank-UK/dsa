#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>

using namespace std;

const long long INF = LLONG_MAX;

// Dijkstra: shortest distances from src over non-negative weighted edges.
// Returns dist[i] = INF for unreachable vertices.
vector<long long> dijkstra(int n, int src, const vector<vector<pair<int, int>>>& adj) {
    vector<long long> dist(n + 1, INF);

    // Min-heap of {distance, vertex}.
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;  // stale heap entry

        for (const auto& [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;  // relax
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
    cout << "====================== Dijkstra ======================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O((V + E) log V)   binary-heap adjacency list\n";
    cout << "  Space : O(V)\n";
    cout << "  Note  : single-source; NON-NEGATIVE weights only\n\n";

    cout << "[Demo]\n";
    int n = 5;
    vector<vector<pair<int, int>>> adj(n + 1);
    auto addEdge = [&](int u, int v, int w) { adj[u].push_back({v, w}); adj[v].push_back({u, w}); };
    addEdge(1, 2, 4); addEdge(1, 3, 2); addEdge(2, 3, 1);
    addEdge(2, 4, 5); addEdge(3, 4, 8); addEdge(3, 5, 10); addEdge(4, 5, 2);
    cout << "  weighted undirected graph, source = 1\n";
    cout << "  distances:\n";
    printDist(dijkstra(n, 1, adj), 1);
    cout << "\n";

    cout << "[Cases]  (source = 4)\n";
    cout << "  distances:\n";
    printDist(dijkstra(n, 4, adj), 4);
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  single node  : dist(1->1) = "
         << dijkstra(1, 1, vector<vector<pair<int,int>>>(1 + 1))[1] << "\n";
    // Disconnected: node 3 unreachable from 1
    vector<vector<pair<int, int>>> disc(3 + 1);
    disc[1].push_back({2, 5}); disc[2].push_back({1, 5});
    auto d = dijkstra(3, 1, disc);
    cout << "  disconnected : 1->3 = " << (d[3] == INF ? "Unreachable" : to_string(d[3])) << "\n";
    cout << "\n";

    return 0;
}

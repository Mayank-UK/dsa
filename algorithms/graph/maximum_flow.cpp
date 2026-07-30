#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

// BFS that finds an augmenting path in the residual graph and records parents.
// Returns true if s can reach t with positive residual capacity.
bool bfs(int s, int t, int n, const vector<vector<int>>& capacity,
         const vector<vector<int>>& adj, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        auto [u, flow] = q.front(); q.pop();
        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                int nf = min(flow, capacity[u][v]);
                if (v == t) return true;
                q.push({v, nf});
            }
        }
    }
    return false;
}

// Edmonds-Karp (Ford-Fulkerson with BFS). Returns the max flow s -> t.
int maxFlow(int s, int t, int n, vector<vector<int>>& capacity, const vector<vector<int>>& adj) {
    int flow = 0;
    vector<int> parent(n + 1);

    while (bfs(s, t, n, capacity, adj, parent)) {
        // bottleneck along the found path
        int push = INT_MAX;
        for (int v = t; v != s; v = parent[v])
            push = min(push, capacity[parent[v]][v]);

        // update residual capacities (forward -= push, reverse += push)
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= push;
            capacity[v][u] += push;
        }
        flow += push;
    }
    return flow;
}

int main() {
    cout << "=============== Maximum Flow (Edmonds-Karp) ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V * E^2)   Edmonds-Karp (BFS augmenting paths)\n";
    cout << "  Space : O(V^2)       capacity matrix\n";
    cout << "  Note  : Ford-Fulkerson with BFS; finds max s-t flow\n\n";

    cout << "[Demo]\n";
    int n = 6, source = 1, sink = 6;
    vector<vector<int>> capacity(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> adj(n + 1);
    auto addEdge = [&](int u, int v, int cap) {
        capacity[u][v] += cap;
        adj[u].push_back(v);
        adj[v].push_back(u);  // reverse edge for the residual graph
    };
    addEdge(1,2,16); addEdge(1,3,13); addEdge(2,3,10); addEdge(2,4,12);
    addEdge(3,2,4);  addEdge(3,5,14); addEdge(4,3,9);  addEdge(4,6,20);
    addEdge(5,4,7);  addEdge(5,6,4);
    cout << "  network : source=1, sink=6\n";
    cout << "  max flow = " << maxFlow(source, sink, n, capacity, adj) << "  (classic CLRS example = 23)\n\n";

    cout << "[Cases]\n";
    cout << "  simple 1->2->3 (bottleneck 5):\n";
    {
        vector<vector<int>> c(3 + 1, vector<int>(3 + 1, 0));
        vector<vector<int>> a(3 + 1);
        auto ae = [&](int u, int v, int cap) { c[u][v] += cap; a[u].push_back(v); a[v].push_back(u); };
        ae(1,2,10); ae(2,3,5);
        cout << "    max flow = " << maxFlow(1, 3, 3, c, a) << "\n";
    }
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  source == sink       : " << [&] {
        vector<vector<int>> c(2 + 1, vector<int>(2 + 1, 0)); vector<vector<int>> a(2 + 1);
        return maxFlow(1, 1, 2, c, a);
    }() << "\n";
    cout << "  no path s->t         : ";
    {
        vector<vector<int>> c(3 + 1, vector<int>(3 + 1, 0)); vector<vector<int>> a(3 + 1);
        a[1].push_back(2); a[2].push_back(1);  // no edge toward 3
        cout << maxFlow(1, 3, 3, c, a) << "  (0 flow)\n";
    }
    cout << "\n";

    return 0;
}

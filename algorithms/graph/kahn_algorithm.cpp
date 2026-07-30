#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Kahn's algorithm: repeatedly remove a 0-in-degree vertex, decrement its
// neighbors' in-degrees, and enqueue new zeros. If not all vertices come out,
// the graph has a cycle.
vector<int> topologicalSort(int n, const vector<vector<int>>& adj) {
    vector<int> inDegree(n + 1, 0);

    for (int u = 1; u <= n; u++)
        for (int v : adj[u]) inDegree[v]++;

    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (inDegree[i] == 0) q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u])
            if (--inDegree[v] == 0) q.push(v);
    }

    if ((int)order.size() != n) return {};  // cycle
    return order;
}

static void printOrder(const vector<int>& o) {
    if (o.empty()) { cout << "  (none — cycle present)\n"; return; }
    cout << "  ";
    for (size_t i = 0; i < o.size(); i++) cout << o[i] << (i + 1 == o.size() ? "" : " -> ");
    cout << "\n";
}

int main() {
    cout << "============= Topological Sort (Kahn) =============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V + E)\n";
    cout << "  Space : O(V)\n";
    cout << "  Note  : BFS on in-degrees; cycle => fewer than V vertices emitted\n\n";

    cout << "[Demo]\n";
    int n = 6;
    vector<vector<int>> adj(n + 1);
    auto addEdge = [&](int u, int v) { adj[u].push_back(v); };
    addEdge(6, 3); addEdge(6, 1); addEdge(5, 1); addEdge(5, 2);
    addEdge(3, 4); addEdge(4, 2);
    cout << "  DAG edges : 6->3,6->1,5->1,5->2,3->4,4->2\n";
    cout << "  topo order: ";
    printOrder(topologicalSort(n, adj));
    cout << "\n";

    cout << "[Cases]  (cyclic graph -> rejected)\n";
    vector<vector<int>> cyc(3 + 1);
    auto ce = [&](int u, int v) { cyc[u].push_back(v); };
    ce(1, 2); ce(2, 3); ce(3, 1);
    cout << "  cycle 1->2->3->1 : ";
    printOrder(topologicalSort(3, cyc));
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  single node     : "; printOrder(topologicalSort(1, vector<vector<int>>(1 + 1)));
    cout << "  no edges (n=4) : "; printOrder(topologicalSort(4, vector<vector<int>>(4 + 1)));
    cout << "\n";

    return 0;
}

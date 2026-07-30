#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

// Hierholzer's algorithm. Mutates adj (consumes edges). Returns the circuit
// vertices in order, or empty if no Eulerian circuit exists.
vector<int> findEulerianCircuit(int n, vector<vector<int>>& adj) {
    // Precondition: every vertex that has edges must have even degree.
    for (int i = 1; i <= n; i++)
        if ((int)adj[i].size() % 2 != 0) return {};

    vector<int> circuit;
    vector<int> path;
    path.push_back(1);  // start anywhere that has edges

    while (!path.empty()) {
        int u = path.back();
        if (!adj[u].empty()) {
            int v = adj[u].back();
            adj[u].pop_back();
            // remove the reverse edge too (undirected)
            auto it = find(adj[v].begin(), adj[v].end(), u);
            if (it != adj[v].end()) adj[v].erase(it);
            path.push_back(v);
        } else {
            circuit.push_back(u);
            path.pop_back();
        }
    }
    return circuit;
}

static void printCircuit(const vector<int>& c) {
    if (c.empty()) { cout << "  (no Eulerian circuit — odd-degree vertex present)\n"; return; }
    cout << "  ";
    for (size_t i = 0; i < c.size(); i++) cout << c[i] << (i + 1 == c.size() ? "" : " -> ");
    cout << "\n";
}

int main() {
    cout << "=============== Euler Circuit ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(E)     Hierholzer (undirected, adjacency list)\n";
    cout << "  Space : O(V + E)\n";
    cout << "  Note  : exists iff connected (ignoring isolates) AND every degree is EVEN\n\n";

    cout << "[Demo]\n";
    int n = 3;
    vector<vector<int>> adj(n + 1);
    auto addEdge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    // triangle 1-2-3-1: every vertex degree 2 (even) -> circuit exists
    addEdge(1, 2); addEdge(2, 3); addEdge(3, 1);
    cout << "  graph : triangle 1-2-3-1 (all degrees even)\n";
    cout << "  circuit: ";
    printCircuit(findEulerianCircuit(n, adj));
    cout << "\n";

    cout << "[Cases]\n";
    cout << "  square + diagonal (degrees 3/3/3/3 ... need even):\n";
    cout << "  two triangles sharing a vertex: 1-2,2-3,3-1,1-4,4-5,5-1\n";
    {
        vector<vector<int>> g(5 + 1);
        auto ae = [&](int u, int v) { g[u].push_back(v); g[v].push_back(u); };
        ae(1,2); ae(2,3); ae(3,1); ae(1,4); ae(4,5); ae(5,1);
        cout << "    circuit: "; printCircuit(findEulerianCircuit(5, g));
    }
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  no circuit (path graph 1-2-3, odd degrees):\n";
    {
        vector<vector<int>> g(3 + 1);
        g[1].push_back(2); g[2].push_back(1);
        g[2].push_back(3); g[3].push_back(2);
        cout << "    "; printCircuit(findEulerianCircuit(3, g));
    }
    cout << "  single node : ";
    {
        vector<vector<int>> g(1 + 1);
        printCircuit(findEulerianCircuit(1, g));
    }
    cout << "\n";

    return 0;
}

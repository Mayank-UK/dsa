#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Hierholzer adapted for an Eulerian PATH. Start at an odd-degree vertex if one
// exists; otherwise the graph has an Eulerian circuit (start anywhere).
// Returns the path vertices in order, or empty if none exists.
vector<int> findEulerianPath(int n, vector<vector<int>>& adj) {
    int oddCount = 0;
    int start = 1;
    for (int i = 1; i <= n; i++) {
        if ((int)adj[i].size() % 2 != 0) {
            oddCount++;
            start = i;  // an Eulerian path must start at an odd-degree vertex
        }
    }
    if (oddCount != 0 && oddCount != 2) return {};  // 0 = circuit, 2 = path

    vector<int> path, circuit;
    path.push_back(start);

    while (!path.empty()) {
        int u = path.back();
        if (!adj[u].empty()) {
            int v = adj[u].back();
            adj[u].pop_back();
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

static void printPath(const vector<int>& p) {
    if (p.empty()) { cout << "  (no Eulerian path — odd-degree count not 0 or 2)\n"; return; }
    cout << "  ";
    for (size_t i = 0; i < p.size(); i++) cout << p[i] << (i + 1 == p.size() ? "" : " -> ");
    cout << "\n";
}

int main() {
    cout << "=============== Euler Path ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(E)\n";
    cout << "  Space : O(V + E)\n";
    cout << "  Note  : exists iff connected (ignoring isolates) AND exactly 0 or 2 odd-degree vertices\n\n";

    cout << "[Demo]\n";
    int n = 4;
    vector<vector<int>> adj(n + 1);
    auto addEdge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    // 1-2, 2-3, 3-1, 3-4 -> degrees 2,2,3,1 -> odd vertices {3,4}
    addEdge(1, 2); addEdge(2, 3); addEdge(3, 1); addEdge(3, 4);
    cout << "  graph : 1-2, 2-3, 3-1, 3-4 (odd vertices 3 and 4)\n";
    cout << "  path  : ";
    printPath(findEulerianPath(n, adj));
    cout << "\n";

    cout << "[Cases]\n";
    cout << "  pure circuit case (triangle, 0 odd):\n";
    {
        vector<vector<int>> g(3 + 1);
        auto ae = [&](int u, int v) { g[u].push_back(v); g[v].push_back(u); };
        ae(1,2); ae(2,3); ae(3,1);
        cout << "    "; printPath(findEulerianPath(3, g));
    }
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  no path (4 odd vertices): 1-2, 3-4\n";
    {
        vector<vector<int>> g(4 + 1);
        auto ae = [&](int u, int v) { g[u].push_back(v); g[v].push_back(u); };
        ae(1,2); ae(3,4);
        cout << "    "; printPath(findEulerianPath(4, g));
    }
    cout << "  single node : ";
    {
        vector<vector<int>> g(1 + 1);
        printPath(findEulerianPath(1, g));
    }
    cout << "\n";

    return 0;
}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Cycle detection in a DIRECTED graph via 3-color DFS.
//  0 = unvisited, 1 = visiting (on recursion stack), 2 = done.
bool dfsCycle(int u, const vector<vector<int>>& adj, vector<int>& state) {
    state[u] = 1;
    for (int v : adj[u]) {
        if (state[v] == 0) {
            if (dfsCycle(v, adj, state)) return true;
        } else if (state[v] == 1) {
            return true;  // back edge into the current path -> cycle
        }
    }
    state[u] = 2;
    return false;
}

bool hasCycle(int n, const vector<vector<int>>& adj) {
    vector<int> state(n + 1, 0);
    for (int i = 1; i <= n; i++)
        if (state[i] == 0 && dfsCycle(i, adj, state)) return true;
    return false;
}

static string yesNo(bool b) { return b ? "Cycle detected" : "No cycle"; }

int main() {
    cout << "================= Cycle Detection =================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V + E)\n";
    cout << "  Space : O(V)\n";
    cout << "  Note  : DIRECTED graph, 3-color DFS (a back edge = a cycle)\n\n";

    cout << "[Demo]\n";
    int n = 4;
    vector<vector<int>> adj(n + 1);
    auto addEdge = [&](int u, int v) { adj[u].push_back(v); };
    // 1 -> 2 -> 3 -> 2 (cycle), 3 -> 4
    addEdge(1, 2); addEdge(2, 3); addEdge(3, 2); addEdge(3, 4);
    cout << "  graph : 1->2, 2->3, 3->2, 3->4\n";
    cout << "  result: " << yesNo(hasCycle(n, adj)) << "\n\n";

    cout << "[Cases]\n";
    vector<vector<int>> dag(n + 1);
    auto de = [&](int u, int v) { dag[u].push_back(v); };
    de(1, 2); de(2, 3); de(3, 4);  // pure DAG, no cycle
    cout << "  DAG (1->2->3->4) : " << yesNo(hasCycle(n, dag)) << "\n";
    cout << "  self-loop (1->1) : " << yesNo(hasCycle(2, [&] {
        vector<vector<int>> a(2 + 1); a[1].push_back(1); return a; }())) << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  empty graph (n=3) : " << yesNo(hasCycle(3, vector<vector<int>>(3 + 1))) << "\n";
    cout << "  single node       : " << yesNo(hasCycle(1, vector<vector<int>>(1 + 1))) << "\n";
    cout << "\n";

    return 0;
}

#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

// DFS topological sort with cycle detection. Push a vertex onto the stack
// only after all its descendants are processed; popping yields a valid order.
bool dfsTopo(int u, const vector<vector<int>>& adj, vector<int>& state, stack<int>& st) {
    state[u] = 1;  // visiting
    for (int v : adj[u]) {
        if (state[v] == 0) {
            if (!dfsTopo(v, adj, state, st)) return false;
        } else if (state[v] == 1) {
            return false;  // cycle
        }
    }
    state[u] = 2;
    st.push(u);
    return true;
}

// Returns a topological order, or empty if the graph has a cycle.
vector<int> topologicalSortDFS(int n, const vector<vector<int>>& adj) {
    vector<int> state(n + 1, 0);
    stack<int> st;

    for (int i = 1; i <= n; i++)
        if (state[i] == 0 && !dfsTopo(i, adj, state, st))
            return {};  // cycle -> no valid order

    vector<int> order;
    while (!st.empty()) { order.push_back(st.top()); st.pop(); }
    return order;
}

static void printOrder(const vector<int>& o) {
    if (o.empty()) { cout << "  (none — cycle present)\n"; return; }
    cout << "  ";
    for (size_t i = 0; i < o.size(); i++) cout << o[i] << (i + 1 == o.size() ? "" : " -> ");
    cout << "\n";
}

int main() {
    cout << "=============== Topological Sort (DFS) ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V + E)\n";
    cout << "  Space : O(V)\n";
    cout << "  Note  : directed ACYCLIC graph (DAG); rejects cyclic graphs\n\n";

    cout << "[Demo]\n";
    int n = 6;
    vector<vector<int>> adj(n + 1);
    auto addEdge = [&](int u, int v) { adj[u].push_back(v); };
    addEdge(6, 3); addEdge(6, 1); addEdge(5, 1); addEdge(5, 2);
    addEdge(3, 4); addEdge(4, 2);
    cout << "  DAG edges : 6->3,6->1,5->1,5->2,3->4,4->2\n";
    cout << "  topo order: ";
    printOrder(topologicalSortDFS(n, adj));
    cout << "\n";

    cout << "[Cases]  (cyclic graph -> rejected)\n";
    vector<vector<int>> cyc(3 + 1);
    auto ce = [&](int u, int v) { cyc[u].push_back(v); };
    ce(1, 2); ce(2, 3); ce(3, 1);
    cout << "  cycle 1->2->3->1 : ";
    printOrder(topologicalSortDFS(3, cyc));
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  single node       : "; printOrder(topologicalSortDFS(1, vector<vector<int>>(1 + 1)));
    cout << "  no edges (n=4)   : "; printOrder(topologicalSortDFS(4, vector<vector<int>>(4 + 1)));
    cout << "\n";

    return 0;
}

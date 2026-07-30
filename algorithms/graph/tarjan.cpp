#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

// Tarjan's SCC: one DFS using discovery time (tin) and low-link. A vertex is
// the root of an SCC when low[u] == tin[u]; pop the stack down to it.
void tarjanDFS(int u, const vector<vector<int>>& adj,
               vector<int>& tin, vector<int>& low, vector<bool>& onStack,
               stack<int>& st, int& timer, vector<vector<int>>& sccs) {
    tin[u] = low[u] = ++timer;
    st.push(u); onStack[u] = true;

    for (int v : adj[u]) {
        if (tin[v] == -1) {
            tarjanDFS(v, adj, tin, low, onStack, st, timer, sccs);
            low[u] = min(low[u], low[v]);
        } else if (onStack[v]) {
            low[u] = min(low[u], tin[v]);  // back/cross edge within the stack
        }
    }

    if (low[u] == tin[u]) {  // root of an SCC
        vector<int> comp;
        while (true) {
            int v = st.top(); st.pop();
            onStack[v] = false;
            comp.push_back(v);
            if (v == u) break;
        }
        sccs.push_back(comp);
    }
}

vector<vector<int>> findTarjanSCCs(int n, const vector<vector<int>>& adj) {
    vector<int> tin(n + 1, -1), low(n + 1, -1);
    vector<bool> onStack(n + 1, false);
    stack<int> st;
    vector<vector<int>> sccs;
    int timer = 0;

    for (int i = 1; i <= n; i++)
        if (tin[i] == -1) tarjanDFS(i, adj, tin, low, onStack, st, timer, sccs);

    return sccs;
}

static void printSCCs(const vector<vector<int>>& sccs) {
    cout << "  " << sccs.size() << " SCC(s):\n";
    for (size_t i = 0; i < sccs.size(); i++) {
        cout << "    SCC " << i + 1 << " : ";
        for (int x : sccs[i]) cout << x << " ";
        cout << "\n";
    }
}

int main() {
    cout << "================= Tarjan SCC =================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V + E)     single DFS (vs Kosaraju's two)\n";
    cout << "  Space : O(V)\n";
    cout << "  Note  : directed graph; one pass with low-link + explicit stack\n\n";

    cout << "[Demo]\n";
    int n = 5;
    vector<vector<int>> adj(n + 1);
    auto addEdge = [&](int u, int v) { adj[u].push_back(v); };
    addEdge(1, 3); addEdge(3, 4); addEdge(4, 1); addEdge(2, 1); addEdge(4, 5);
    cout << "  graph : 1->3,3->4,4->1 (SCC), 2->1, 4->5\n";
    printSCCs(findTarjanSCCs(n, adj));
    cout << "\n";

    cout << "[Cases]\n";
    cout << "  single big cycle (1->2->3->1):\n";
    vector<vector<int>> cyc(3 + 1);
    auto ce = [&](int u, int v) { cyc[u].push_back(v); };
    ce(1, 2); ce(2, 3); ce(3, 1);
    printSCCs(findTarjanSCCs(3, cyc));
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  DAG (each node its own SCC) : 1->2, 2->3\n";
    vector<vector<int>> dag(3 + 1);
    dag[1].push_back(2); dag[2].push_back(3);
    printSCCs(findTarjanSCCs(3, dag));
    cout << "  single node : ";
    printSCCs(findTarjanSCCs(1, vector<vector<int>>(1 + 1)));
    cout << "\n";

    return 0;
}

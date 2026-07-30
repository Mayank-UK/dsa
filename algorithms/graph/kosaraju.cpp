#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

// First pass: DFS the original graph, push vertices onto a stack by finishing time.
void dfs1(int u, const vector<vector<int>>& adj, vector<bool>& vis, stack<int>& st) {
    vis[u] = true;
    for (int v : adj[u]) if (!vis[v]) dfs1(v, adj, vis, st);
    st.push(u);
}

// Second pass: DFS the transposed graph; everything reachable is one SCC.
void dfs2(int u, const vector<vector<int>>& radj, vector<bool>& vis, vector<int>& comp) {
    vis[u] = true;
    comp.push_back(u);
    for (int v : radj[u]) if (!vis[v]) dfs2(v, radj, vis, comp);
}

// Kosaraju: order by finishing time on G, then collect SCCs on G^T.
vector<vector<int>> findSCCs(int n, const vector<vector<int>>& adj) {
    vector<bool> vis(n + 1, false);
    stack<int> st;

    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs1(i, adj, vis, st);

    // Build the transpose.
    vector<vector<int>> radj(n + 1);
    for (int u = 1; u <= n; u++)
        for (int v : adj[u]) radj[v].push_back(u);

    fill(vis.begin(), vis.end(), false);
    vector<vector<int>> sccs;

    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (!vis[u]) {
            vector<int> comp;
            dfs2(u, radj, vis, comp);
            sccs.push_back(comp);
        }
    }
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
    cout << "=============== Kosaraju SCC ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V + E)     two DFS passes + one transpose\n";
    cout << "  Space : O(V + E)\n";
    cout << "  Note  : directed graph; finds strongly connected components\n\n";

    cout << "[Demo]\n";
    int n = 5;
    vector<vector<int>> adj(n + 1);
    auto addEdge = [&](int u, int v) { adj[u].push_back(v); };
    // SCC {1,3,4}, singletons {2}, {5}
    addEdge(1, 3); addEdge(3, 4); addEdge(4, 1); addEdge(2, 1); addEdge(4, 5);
    cout << "  graph : 1->3,3->4,4->1 (SCC), 2->1, 4->5\n";
    printSCCs(findSCCs(n, adj));
    cout << "\n";

    cout << "[Cases]\n";
    cout << "  single big cycle (1->2->3->1):\n";
    vector<vector<int>> cyc(3 + 1);
    auto ce = [&](int u, int v) { cyc[u].push_back(v); };
    ce(1, 2); ce(2, 3); ce(3, 1);
    printSCCs(findSCCs(3, cyc));
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  DAG (no SCCs > 1) : 1->2, 2->3\n";
    vector<vector<int>> dag(3 + 1);
    dag[1].push_back(2); dag[2].push_back(3);
    printSCCs(findSCCs(3, dag));
    cout << "  single node : ";
    printSCCs(findSCCs(1, vector<vector<int>>(1 + 1)));
    cout << "\n";

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Breadth-First Search from `start`. Returns vertices in visit order.
vector<int> bfs(int start, int n, const vector<vector<int>>& adj) {
    vector<bool> visited(n + 1, false);
    vector<int> order;
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return order;
}

// Recursive DFS helper.
void dfsUtil(int u, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& order) {
    visited[u] = true;
    order.push_back(u);

    for (int v : adj[u]) {
        if (!visited[v]) dfsUtil(v, adj, visited, order);
    }
}

// Depth-First Search from `start`. Returns vertices in visit order.
vector<int> dfs(int start, int n, const vector<vector<int>>& adj) {
    vector<bool> visited(n + 1, false);
    vector<int> order;
    dfsUtil(start, adj, visited, order);
    return order;
}

static void printVec(const vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++)
        cout << v[i] << (i + 1 == v.size() ? "" : " -> ");
    cout << "\n";
}

int main() {
    cout << "====================== BFS / DFS ======================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V + E)     using adjacency lists\n";
    cout << "  Space : O(V)\n";
    cout << "  Note  : BFS = shortest hops on unweighted graphs; DFS goes deep first\n\n";

    cout << "[Demo]\n";
    int n = 5;
    vector<vector<int>> adj(n + 1);
    auto addEdge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    //   1 -- 2 -- 4
    //   |    |
    //   3 -- 5
    addEdge(1, 2); addEdge(1, 3); addEdge(2, 4); addEdge(2, 5); addEdge(3, 5);

    cout << "  graph : 1-2, 1-3, 2-4, 2-5, 3-5  (undirected)\n";
    cout << "  BFS from 1 : "; printVec(bfs(1, n, adj));
    cout << "  DFS from 1 : "; printVec(dfs(1, n, adj));
    cout << "\n";

    cout << "[Cases]  (start from a different node)\n";
    cout << "  BFS from 3 : "; printVec(bfs(3, n, adj));
    cout << "  DFS from 4 : "; printVec(dfs(4, n, adj));
    cout << "\n";

    cout << "[Edge Cases]\n";
    vector<vector<int>> empty(n + 1);              // no edges
    cout << "  isolated graph BFS from 1 : "; printVec(bfs(1, n, empty));
    cout << "  single node  (n=1)        : "; printVec(bfs(1, 1, {{}, {}}));
    cout << "\n";

    return 0;
}

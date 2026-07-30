#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Hamiltonian Path via backtracking over an adjacency matrix.
// A path visiting every vertex exactly once. From the current vertex we recurse
// onto each unvisited neighbor; reaching count == V means success. Any vertex
// can be the start, so the search tries each.
class HamiltonianPath {
    int V;
    vector<vector<int>> adj;
    bool backtrack(int u, int count, vector<bool>& visited, vector<int>& path) {
        if (count == V) return true;          // every vertex visited -> found
        for (int v = 0; v < V; ++v) {
            if (adj[u][v] && !visited[v]) {
                visited[v] = true;            // choose
                path.push_back(v);
                if (backtrack(v, count + 1, visited, path)) return true;
                path.pop_back();              // un-choose
                visited[v] = false;
            }
        }
        return false;
    }
public:
    HamiltonianPath(int vertices) : V(vertices), adj(vertices, vector<int>(vertices, 0)) {}
    void addEdge(int u, int v) { adj[u][v] = adj[v][u] = 1; }

    // Returns the path (vertex sequence), or empty if none exists.
    vector<int> findPath() {
        vector<bool> visited(V, false);
        vector<int> path;
        for (int i = 0; i < V; ++i) {        // try every start vertex
            visited[i] = true;
            path.push_back(i);
            if (backtrack(i, 1, visited, path)) return path;
            path.pop_back();
            visited[i] = false;
        }
        return {};                            // no Hamiltonian path
    }
};

int main() {
    cout << "============== Hamiltonian Path ==============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V!) worst case   (factorial branching, lightly pruned)\n";
    cout << "  Space : O(V) recursion + visited/path arrays\n";
    cout << "  Note  : visit each vertex once; every vertex is a candidate start\n\n";

    cout << "[Demo]\n";
    //   (0)---(1)---(2)
    //    |   / \     |
    //   (3)-------(4)
    HamiltonianPath hp(5);
    hp.addEdge(0, 1); hp.addEdge(0, 3); hp.addEdge(1, 2);
    hp.addEdge(1, 3); hp.addEdge(1, 4); hp.addEdge(2, 4); hp.addEdge(3, 4);
    vector<int> path = hp.findPath();
    if (path.empty()) {
        cout << "  No Hamiltonian Path exists.\n";
    } else {
        cout << "  path (" << path.size() << " vertices): ";
        for (size_t i = 0; i < path.size(); i++)
            cout << path[i] << (i + 1 == path.size() ? "" : " -> ");
        cout << "\n";
    }
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  single vertex : ";
    {
        auto p = HamiltonianPath(1).findPath();
        cout << (p.empty() ? "none" : to_string(p[0])) << "\n";
    }
    cout << "  disconnected (3 nodes, one edge): ";
    {
        HamiltonianPath d(3); d.addEdge(0, 1);   // node 2 isolated
        auto p = d.findPath();
        cout << (p.empty() ? "No Hamiltonian Path\n" : "found (unexpected)\n");
    }
    cout << "  simple chain 0-1-2-3: ";
    {
        HamiltonianPath c(4);
        c.addEdge(0,1); c.addEdge(1,2); c.addEdge(2,3);
        auto p = c.findPath();
        for (size_t i = 0; i < p.size(); i++)
            cout << p[i] << (i + 1 == p.size() ? "\n" : " -> ");
    }
    cout << "\n";

    return 0;
}

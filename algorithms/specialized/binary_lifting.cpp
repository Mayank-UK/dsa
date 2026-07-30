#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// ============================================================
// Binary Lifting — answer k-th-ancestor and LCA queries on a rooted tree in
// O(log n), after an O(n log n) precompute. up[node][j] is the 2^j-th ancestor
// of node. Any k is the sum of powers of two (its bits), so a k-th ancestor is
// a sequence of O(log n) jumps. LCA lifts the deeper node to equal depth, then
// lifts both until their ancestors coincide. Vector-backed → RAII, no destructor.
// ============================================================
class BinaryLifting {
private:
    int n;
    int LOG;
    vector<vector<int>> up;     // up[node][j] = 2^j-th ancestor, -1 if none
    vector<int> depth;
    vector<vector<int>> graph;

public:
    BinaryLifting(int vertices) {
        n = vertices;
        LOG = (int)ceil(log2(n)) + 1;

        graph.resize(n);
        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);
    }

    // ─── Add an undirected tree edge ───
    void addEdge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // ─── DFS: fill depth + the 2^j ancestor table ───  Time: O(n log n)
    void dfs(int node, int parent) {
        up[node][0] = parent;
        for (int j = 1; j < LOG; j++)
            if (up[node][j - 1] != -1)
                up[node][j] = up[up[node][j - 1]][j - 1];

        for (int child : graph[node]) {
            if (child == parent) continue;
            depth[child] = depth[node] + 1;
            dfs(child, node);
        }
    }

    void build(int root = 0) { dfs(root, -1); }

    // ─── k-th ancestor of node (-1 if it walks above the root) ───  Time: O(log n)
    int kthAncestor(int node, int k) {
        for (int j = 0; j < LOG; j++) {
            if (node == -1) break;
            if (k & (1 << j))
                node = up[node][j];
        }
        return node;
    }

    // ─── Lowest Common Ancestor of u and v ───  Time: O(log n)
    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        u = kthAncestor(u, depth[u] - depth[v]);   // equalize depths
        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {        // lift together past the LCA
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }

    int depthOf(int node) const { return depth[node]; }

    void printTable() {
        cout << "  node | 2^j-th ancestors (j = 0 .. " << LOG - 1 << ")" << endl;
        for (int i = 0; i < n; i++) {
            cout << "    " << i << " (depth " << depth[i] << ") | ";
            for (int j = 0; j < LOG; j++) cout << up[i][j] << " ";
            cout << endl;
        }
    }
};

// ============================================================
int main() {

    cout << "==================== Binary Lifting (LCA) ====================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  build        : O(n log n)   (DFS + fill the 2^j table)" << endl;
    cout << "  kth ancestor : O(log n)     (one jump per set bit of k)" << endl;
    cout << "  LCA          : O(log n)     (equalize depth, then lift together)" << endl;
    cout << "  space        : O(n log n)" << endl;

    BinaryLifting tree(9);
    /*
              0
            /   \
           1     2
          / \   / \
         3  4  5   6
               |
               7
               |
               8
    */
    tree.addEdge(0, 1); tree.addEdge(0, 2);
    tree.addEdge(1, 3); tree.addEdge(1, 4);
    tree.addEdge(2, 5); tree.addEdge(2, 6);
    tree.addEdge(5, 7); tree.addEdge(7, 8);
    tree.build(0);

    cout << endl;
    cout << "[Build]  rooted tree on 9 nodes (see ASCII in source)" << endl;
    tree.printTable();

    cout << endl;
    cout << "[Queries]" << endl;
    cout << "  2nd ancestor of 8 : " << tree.kthAncestor(8, 2) << "  (8->7->5)" << endl;
    cout << "  3rd ancestor of 8 : " << tree.kthAncestor(8, 3) << "  (8->7->5->2)" << endl;
    cout << "  6th ancestor of 8 : " << tree.kthAncestor(8, 6) << "  (-1 = above root)" << endl;
    cout << "  LCA(3,4) : " << tree.lca(3, 4) << "  (siblings under 1)" << endl;
    cout << "  LCA(3,8) : " << tree.lca(3, 8) << "  (root 0)" << endl;
    cout << "  LCA(6,8) : " << tree.lca(6, 8) << "  (node 2)" << endl;
    cout << "  LCA(7,8) : " << tree.lca(7, 8) << "  (7 is an ancestor of 8)" << endl;

    // Invariant check: the LCA is an ancestor of both endpoints.
    cout << endl;
    cout << "[Verify]  LCA is an ancestor of both u and v";
    auto isAncestor = [&](int maybeAnc, int node) {
        return tree.kthAncestor(node, tree.depthOf(node) - tree.depthOf(maybeAnc)) == maybeAnc;
    };
    int tests[][2] = {{3, 4}, {3, 8}, {6, 8}, {7, 8}, {0, 5}};
    bool ok = true;
    for (auto& t : tests) {
        int l = tree.lca(t[0], t[1]);
        if (!isAncestor(l, t[0]) || !isAncestor(l, t[1])) { ok = false; break; }
    }
    cout << " : " << (ok ? "Holds for all sample pairs" : "FAILED") << endl;

    cout << endl;
    cout << "[Edge Cases]" << endl;
    cout << "  LCA of a node with itself LCA(4,4) = " << tree.lca(4, 4) << endl;
    cout << "  LCA with the root LCA(8,0) = " << tree.lca(8, 0) << endl;
    cout << "  0-th ancestor (the node itself) of 5 = " << tree.kthAncestor(5, 0) << endl;

    cout << endl;
    cout << "[Note]  This is the static-tree LCA. For an evolving tree (online" << endl;
    cout << "       link/cut), use a Link-Cut Tree. lowest_common_ancestor.cpp in" << endl;
    cout << "       algorithms/tree/ covers the same idea with a different demo." << endl;

    return 0;
}

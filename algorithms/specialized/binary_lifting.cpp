#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class BinaryLifting {
private:
    int n;
    int LOG;

    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> graph;

public:
    BinaryLifting(int vertices) {
        n = vertices;
        LOG = ceil(log2(n)) + 1;

        graph.resize(n);
        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);
    }

    // ----------------------------------------------------------
    // Add Edge (Undirected Tree)
    // ----------------------------------------------------------
    void addEdge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // ----------------------------------------------------------
    // DFS to Build Parent Table
    // Time: O(n log n)
    // ----------------------------------------------------------
    void dfs(int node, int parent) {

        up[node][0] = parent;

        for (int j = 1; j < LOG; j++) {
            if (up[node][j - 1] != -1)
                up[node][j] =
                    up[up[node][j - 1]][j - 1];
        }

        for (int child : graph[node]) {

            if (child == parent)
                continue;

            depth[child] = depth[node] + 1;

            dfs(child, node);
        }
    }

    void build(int root = 0) {
        dfs(root, -1);
    }

    // ----------------------------------------------------------
    // Find kth Ancestor
    // Time: O(log n)
    // ----------------------------------------------------------
    int kthAncestor(int node, int k) {

        for (int j = 0; j < LOG; j++) {

            if (node == -1)
                break;

            if (k & (1 << j))
                node = up[node][j];
        }

        return node;
    }

    // ----------------------------------------------------------
    // Lowest Common Ancestor (LCA)
    // Time: O(log n)
    // ----------------------------------------------------------
    int lca(int u, int v) {

        if (depth[u] < depth[v])
            swap(u, v);

        // Bring u to same depth
        int diff = depth[u] - depth[v];

        u = kthAncestor(u, diff);

        if (u == v)
            return u;

        // Lift both nodes
        for (int j = LOG - 1; j >= 0; j--) {

            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }

    void printTable() {

        cout << "\nBinary Lifting Table\n";

        for (int i = 0; i < n; i++) {

            cout << "Node " << i << ": ";

            for (int j = 0; j < LOG; j++)
                cout << up[i][j] << " ";

            cout << endl;
        }
    }
};

int main() {

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

    tree.addEdge(0,1);
    tree.addEdge(0,2);

    tree.addEdge(1,3);
    tree.addEdge(1,4);

    tree.addEdge(2,5);
    tree.addEdge(2,6);

    tree.addEdge(5,7);
    tree.addEdge(7,8);

    tree.build();

    tree.printTable();

    cout << "\nQueries\n";

    cout << "2nd Ancestor of 8 : "
         << tree.kthAncestor(8,2)
         << endl;

    cout << "3rd Ancestor of 8 : "
         << tree.kthAncestor(8,3)
         << endl;

    cout << "LCA(3,4) : "
         << tree.lca(3,4)
         << endl;

    cout << "LCA(3,8) : "
         << tree.lca(3,8)
         << endl;

    cout << "LCA(6,8) : "
         << tree.lca(6,8)
         << endl;

    return 0;
}
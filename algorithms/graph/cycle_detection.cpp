#include <iostream>
#include <vector>

using namespace std;

// DFS helper function to detect cycle using recursion stack states
bool dfsCycleCheck(int u, const vector<vector<int>>& adj, vector<int>& visited) {
    visited[u] = 1; // Mark as currently visiting (in recursion stack)

    for (int v : adj[u]) {
        if (visited[v] == 0) {
            if (dfsCycleCheck(v, adj, visited)) return true;
        } else if (visited[v] == 1) {
            // If the neighbor is already in the current recursion stack, a cycle exists
            return true;
        }
    }

    visited[u] = 2; // Mark as fully processed
    return false;
}

// Function to check if a directed graph contains a cycle
bool hasCycle(int n, const vector<vector<int>>& adj) {
    // 0 = unvisited, 1 = visiting (recursion stack), 2 = visited
    vector<int> visited(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        if (visited[i] == 0) {
            if (dfsCycleCheck(i, adj, visited)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int n = 4; // Number of vertices (1-indexed)
    vector<vector<int>> adj(n + 1);

    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
    };

    // Graph with a cycle: 1 -> 2 -> 3 -> 2 (cycle between 2 and 3)
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 2);
    addEdge(3, 4);

    if (hasCycle(n, adj)) {
        cout << "Cycle detected in the directed graph!\n";
    } else {
        cout << "No cycle found in the directed graph.\n";
    }

    return 0;
}
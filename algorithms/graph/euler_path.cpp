#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Hierholzer's Algorithm adapted to find an Eulerian Path in an undirected graph
void findEulerianPath(int n, vector<vector<int>>& adj) {
    // Count odd degree vertices and find a potential start node
    int oddCount = 0;
    int startNode = 1;

    vector<int> degrees(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        degrees[i] = adj[i].size();
        if (degrees[i] % 2 != 0) {
            oddCount++;
            startNode = i; // Start at an odd-degree vertex if available
        }
    }

    // An Eulerian path only exists if odd degree vertices count is 0 or 2
    if (oddCount != 0 && oddCount != 2) {
        cout << "Eulerian Path does not exist.\n";
        return;
    }

    vector<int> path;
    vector<int> curr_path;
    curr_path.push_back(startNode);

    while (!curr_path.empty()) {
        int u = curr_path.back();

        if (!adj[u].empty()) {
            int v = adj[u].back();
            
            // Remove edge from graph (undirected)
            adj[u].pop_back();
            auto it = find(adj[v].begin(), adj[v].end(), u);
            if (it != adj[v].end()) adj[v].erase(it);

            curr_path.push_back(v);
        } else {
            path.push_back(u);
            curr_path.pop_back();
        }
    }

    // Print the path
    cout << "Eulerian Path: ";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i] << (i == 0 ? "" : " -> ");
    }
    cout << "\n";
}

int main() {
    int n = 4; // Number of vertices (1-indexed)
    vector<vector<int>> adj(n + 1);

    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    // Graph configuration with an Eulerian path (nodes 1 and 4 have odd degrees: 1 and 3)
    // 1-2, 2-3, 3-1, 3-4 -> Degrees: 1(2), 2(2), 3(3), 4(1) -> Odd nodes: 3 and 4
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 1);
    addEdge(3, 4);

    findEulerianPath(n, adj);

    return 0;
}
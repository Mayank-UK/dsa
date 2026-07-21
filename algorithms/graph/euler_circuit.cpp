#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// Hierholzer's Algorithm for finding an Eulerian Circuit in an undirected graph
void findEulerianCircuit(int n, vector<vector<int>>& adj) {
    // Check if all vertices with edges have even degrees
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() % 2 != 0) {
            cout << "Eulerian Circuit does not exist (odd degree vertex found).\n";
            return;
        }
    }

    vector<int> circuit;
    vector<int> curr_path;
    
    // Using a stack to keep track of the current path
    curr_path.push_back(1); // Start from vertex 1 (assuming it has edges)

    while (!curr_path.empty()) {
        int u = curr_path.back();

        if (!adj[u].empty()) {
            // Pick a neighbor, remove the edge, and move to it
            int v = adj[u].back();
            
            // Remove edge from both u and v (since it's undirected)
            adj[u].pop_back();
            auto it = find(adj[v].begin(), adj[v].end(), u);
            if (it != adj[v].end()) adj[v].erase(it);

            curr_path.push_back(v);
        } else {
            // If no more adjacent edges, add vertex to circuit and backtrack
            circuit.push_back(u);
            curr_path.pop_back();
        }
    }

    // Print the circuit path
    cout << "Eulerian Circuit: ";
    for (int i = circuit.size() - 1; i >= 0; i--) {
        cout << circuit[i] << (i == 0 ? "" : " -> ");
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

    // Constructing a graph forming a square cycle (1-2-3-4-1) with a diagonal or loop
    // Let's make a complete-ish graph where all degrees are even:
    // 1-2, 2-3, 3-4, 4-1, 1-3, 3-1 (or similar valid setup)
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 1);
    addEdge(1, 4);
    addEdge(4, 3);

    // Degrees check: 1(3 - wait, let's fix to ensure even degrees)
    // Let's use a standard square with a cross: 1-2, 2-3, 3-4, 4-1, 1-3, 3-1 -> degrees: 1(4), 2(2), 3(4), 4(2)
    // Let's clear and re-add properly for an Eulerian circuit:
    adj.assign(n + 1, vector<int>());
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 4);
    addEdge(4, 1);
    addEdge(1, 3);
    addEdge(3, 1); // multigraph edge or just alternative graph structure

    findEulerianCircuit(n, adj);

    return 0;
}
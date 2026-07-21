#include <iostream>
#include <vector>

using namespace std;

class HamiltonianPath {
private:
    int V;                   // Number of vertices
    vector<vector<int>> adj; // Adjacency matrix

    // Core backtracking function
    bool backtrack(int current_vertex, int count, vector<bool>& visited, vector<int>& path) {
        // Base case: If the number of visited vertices equals the total number of vertices,
        // a Hamiltonian Path has been successfully formed.
        if (count == V) {
            return true;
        }

        // Try all possible next vertices
        for (int v = 0; v < V; ++v) {
            // Check if there is an edge to vertex 'v' and it hasn't been visited yet
            if (adj[current_vertex][v] && !visited[v]) {
                
                // 1. Choose: Mark as visited and add to path
                visited[v] = true;
                path.push_back(v);

                // 2. Explore: Move forward recursively
                if (backtrack(v, count + 1, visited, path)) {
                    return true;
                }

                // 3. Un-choose (Backtrack): Remove from path and unmark to explore other branches
                visited[v] = false;
                path.pop_back();
            }
        }

        return false;
    }

public:
    // Constructor initializes the adjacency matrix with 0s
    HamiltonianPath(int vertices) {
        V = vertices;
        adj.assign(V, vector<int>(V, 0));
    }

    // Adds an undirected edge to the graph
    void addEdge(int u, int v) {
        // Bounds checking is omitted for brevity, assuming valid inputs
        adj[u][v] = 1;
        adj[v][u] = 1; 
    }

    // Initiates the search for a Hamiltonian Path
    void findPath() {
        vector<bool> visited(V, false);
        vector<int> path;

        cout << "--- Search Results ---\n";

        // A Hamiltonian Path can start at any vertex, so we must try them all
        for (int i = 0; i < V; ++i) {
            // Setup the initial vertex
            visited[i] = true;
            path.push_back(i);

            // Launch the backtracking process
            if (backtrack(i, 1, visited, path)) {
                cout << "Hamiltonian Path Found:\n";
                for (int j = 0; j < path.size(); ++j) {
                    cout << path[j] << (j == path.size() - 1 ? "" : " -> ");
                }
                cout << "\n----------------------\n";
                return; // Stop after finding the first valid path
            }

            // Backtrack if starting from vertex 'i' yielded no paths
            visited[i] = false;
            path.pop_back();
        }

        cout << "No Hamiltonian Path exists in this graph.\n";
        cout << "----------------------\n";
    }
};

int main() {
    /*
        Let's create the following graph:
           (0)---(1)---(2)
            |   / \     |
            |  /   \    |
           (3)-------(4)
    */
    int vertices = 5;
    HamiltonianPath hp(vertices);

    hp.addEdge(0, 1);
    hp.addEdge(0, 3);
    hp.addEdge(1, 2);
    hp.addEdge(1, 3);
    hp.addEdge(1, 4);
    hp.addEdge(2, 4);
    hp.addEdge(3, 4);

    cout << "Graph contains " << vertices << " vertices.\n\n";

    // Perform the search
    hp.findPath();

    return 0;
}
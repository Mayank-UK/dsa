#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <optional>
#include <stdexcept>

using namespace std;

class DirectedGraph {

private:
    // ─────────────────── Graph Representation ───────────────────
    
    // Adjacency List: Maps a vertex ID to a set of its outgoing destination vertex IDs.
    unordered_map<int, unordered_set<int>> adj;

    // ─────────────────── Internal Helpers ───────────────────

    void dfsHelper(int vertex, unordered_set<int>& visited, vector<int>& traversal) const {
        visited.insert(vertex);
        traversal.push_back(vertex);

        for (int neighbor : adj.at(vertex)) {
            if (visited.find(neighbor) == visited.end()) {
                dfsHelper(neighbor, visited, traversal);
            }
        }
    }

    // Cycle detection for Directed Graphs requires tracking the "Recursion Stack" (the current path).
    // A back-edge pointing to a node currently on the recursion stack indicates a cycle.
    bool checkCycle(int vertex, unordered_set<int>& visited, unordered_set<int>& recStack) const {
        visited.insert(vertex);
        recStack.insert(vertex); // Add to current path

        for (int neighbor : adj.at(vertex)) {
            if (visited.find(neighbor) == visited.end()) {
                if (checkCycle(neighbor, visited, recStack)) {
                    return true;
                }
            } 
            else if (recStack.find(neighbor) != recStack.end()) {
                // If the neighbor is already visited AND in the current path stack, it's a cycle!
                return true;
            }
        }

        recStack.erase(vertex); // Remove from current path before backtracking
        return false;
    }

public:
    DirectedGraph() = default;
    ~DirectedGraph() = default;

    DirectedGraph(const DirectedGraph&) = delete;
    DirectedGraph& operator=(const DirectedGraph&) = delete;

    // ─────────────────── Mutators ───────────────────

    void addVertex(int vertex) {
        if (adj.find(vertex) == adj.end()) {
            adj[vertex] = unordered_set<int>();
        }
    }

    // Adds a directed edge strictly from u to v
    void addEdge(int u, int v) {
        addVertex(u);
        addVertex(v);
        
        adj[u].insert(v);
    }

    void removeEdge(int u, int v) {
        if (adj.find(u) != adj.end()) {
            adj[u].erase(v);
        }
    }

    // Completely removes a vertex and all of its incoming and outgoing edges.
    void removeVertex(int vertex) {
        if (adj.find(vertex) == adj.end()) return;

        // O(V + E) operation: We must iterate through all other vertices 
        // to remove any incoming edges pointing to the target vertex.
        for (auto& pair : adj) {
            pair.second.erase(vertex);
        }

        // Remove the vertex and its outgoing edges
        adj.erase(vertex);
    }

    void clear() {
        adj.clear();
    }

    // ─────────────────── Queries ───────────────────

    [[nodiscard]] bool hasVertex(int vertex) const {
        return adj.find(vertex) != adj.end();
    }

    [[nodiscard]] bool hasEdge(int u, int v) const {
        if (adj.find(u) == adj.end()) return false;
        return adj.at(u).find(v) != adj.at(u).end();
    }

    [[nodiscard]] int getVertexCount() const {
        return adj.size();
    }

    [[nodiscard]] int getEdgeCount() const {
        int count = 0;
        for (const auto& pair : adj) {
            count += pair.second.size();
        }
        return count; // Directed edges are counted exactly once
    }

    // Out-Degree: Number of edges leaving the vertex
    [[nodiscard]] optional<int> getOutDegree(int vertex) const {
        if (!hasVertex(vertex)) return nullopt;
        return adj.at(vertex).size();
    }

    // In-Degree: Number of edges entering the vertex
    [[nodiscard]] optional<int> getInDegree(int vertex) const {
        if (!hasVertex(vertex)) return nullopt;
        
        int inDegree = 0;
        for (const auto& pair : adj) {
            if (pair.second.find(vertex) != pair.second.end()) {
                inDegree++;
            }
        }
        return inDegree;
    }

    // ─────────────────── Traversals ───────────────────

    vector<int> bfs(int startVertex) const {
        vector<int> traversal;
        if (!hasVertex(startVertex)) return traversal;

        unordered_set<int> visited;
        queue<int> q;

        q.push(startVertex);
        visited.insert(startVertex);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            traversal.push_back(current);

            for (int neighbor : adj.at(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        return traversal;
    }

    vector<int> dfs(int startVertex) const {
        vector<int> traversal;
        if (!hasVertex(startVertex)) return traversal;

        unordered_set<int> visited;
        dfsHelper(startVertex, visited, traversal);
        return traversal;
    }

    // ─────────────────── Algorithms ───────────────────

    [[nodiscard]] bool hasCycle() const {
        unordered_set<int> visited;
        unordered_set<int> recStack; // Tracks the current active path

        for (const auto& pair : adj) {
            int vertex = pair.first;
            if (visited.find(vertex) == visited.end()) {
                if (checkCycle(vertex, visited, recStack)) {
                    return true;
                }
            }
        }
        return false;
    }

    // Kahn's Algorithm for Topological Sorting (BFS based)
    // Valid only for Directed Acyclic Graphs (DAGs).
    // Returns an empty vector if a cycle is detected (sort impossible).
    vector<int> topologicalSort() const {
        unordered_map<int, int> inDegreeMap;
        
        // 1. Initialize all in-degrees to 0
        for (const auto& pair : adj) {
            inDegreeMap[pair.first] = 0;
        }

        // 2. Compute actual in-degrees
        for (const auto& pair : adj) {
            for (int neighbor : pair.second) {
                inDegreeMap[neighbor]++;
            }
        }

        // 3. Queue all vertices with an in-degree of 0 (no dependencies)
        queue<int> q;
        for (const auto& pair : inDegreeMap) {
            if (pair.second == 0) {
                q.push(pair.first);
            }
        }

        vector<int> topoOrder;

        // 4. Process the queue
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            topoOrder.push_back(current);

            // Decrease the in-degree of all neighbors (dependencies met)
            for (int neighbor : adj.at(current)) {
                inDegreeMap[neighbor]--;
                if (inDegreeMap[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // 5. If the topological order doesn't include all vertices, there's a cycle.
        if (topoOrder.size() != adj.size()) {
            return vector<int>(); // Graph is not a DAG
        }

        return topoOrder;
    }

    // ─────────────────── Printing ───────────────────

    void printGraph() const {
        if (adj.empty()) {
            cout << "Graph is empty.\n";
            return;
        }

        for (const auto& pair : adj) {
            cout << "[" << pair.first << "] -> { ";
            for (int neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << "}\n";
        }
    }
};

// ─────────────────── Main Function / Testing ───────────────────

int main() {
    DirectedGraph dag;

    // Build a Directed Acyclic Graph (DAG) for tasks/dependencies
    // Example: Getting dressed (Shirt must precede Jacket, etc.)
    // Let's use numbers: 1 (Socks), 2 (Shoes), 3 (Shirt), 4 (Belt), 5 (Pants), 6 (Jacket)
    
    // Dependencies:
    dag.addEdge(1, 2); // Socks before Shoes
    dag.addEdge(5, 2); // Pants before Shoes
    dag.addEdge(5, 4); // Pants before Belt
    dag.addEdge(3, 4); // Shirt before Belt
    dag.addEdge(3, 6); // Shirt before Jacket
    dag.addEdge(4, 6); // Belt before Jacket

    cout << "Initial Directed Graph:\n";
    dag.printGraph();

    cout << "\nGraph Stats:\n";
    cout << "Vertices:       " << dag.getVertexCount() << "\n";
    cout << "Edges:          " << dag.getEdgeCount() << "\n";
    cout << "Node 4 (Belt) - In-Degree: " << dag.getInDegree(4).value_or(-1)  << ", Out-Degree: " << dag.getOutDegree(4).value_or(-1) << "\n";
    
    cout << "\nAlgorithms:\n";
    cout << "Has Cycle?      " << (dag.hasCycle() ? "Yes" : "No") << "\n";

    cout << "\nTopological Sort (Valid Dependency Resolution / Build Order):\n";
    vector<int> topo = dag.topologicalSort();
    for (int v : topo) cout << v << " ";
    cout << "\n";

    cout << "\nTraversals (starting at 5 / Pants):\n";
    cout << "BFS: ";
    for (int v : dag.bfs(5)) cout << v << " ";
    cout << "\nDFS: ";
    for (int v : dag.dfs(5)) cout << v << " ";
    cout << "\n";

    cout << "\n--- Modifying Graph to create a Cycle ---\n";
    cout << "Adding edge (6, 5) -> Jacket before Pants (Impossible!)\n";
    dag.addEdge(6, 5);
    
    cout << "Has Cycle?      " << (dag.hasCycle() ? "Yes" : "No") << "\n";
    
    cout << "Attempting Topological Sort: ";
    topo = dag.topologicalSort();
    if (topo.empty()) {
        cout << "Failed (Cycle Detected!)\n";
    }

    cout << "\n--- Removing Vertex 4 (Belt) ---\n";
    dag.removeVertex(4);
    dag.printGraph();

    return 0;
}
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <optional>

using namespace std;

class UndirectedGraph {

private:
    // ─────────────────── Graph Representation ───────────────────
    
    // Adjacency List: Maps a vertex ID to a set of its neighboring vertex IDs.
    // Using unordered_set ensures O(1) edge insertion/deletion and prevents duplicate edges.
    unordered_map<int, unordered_set<int>> adj;

    // ─────────────────── Internal Helpers ───────────────────

    // Helper for recursive DFS
    void dfsHelper(int vertex, unordered_set<int>& visited, vector<int>& traversal) const {
        visited.insert(vertex);
        traversal.push_back(vertex);

        for (int neighbor : adj.at(vertex)) {
            if (visited.find(neighbor) == visited.end()) {
                dfsHelper(neighbor, visited, traversal);
            }
        }
    }

    // Helper for Cycle Detection
    // In an undirected graph, a visited neighbor is a cycle ONLY IF it is not the node we just came from (parent).
    bool checkCycle(int vertex, int parent, unordered_set<int>& visited) const {
        visited.insert(vertex);

        for (int neighbor : adj.at(vertex)) {
            if (visited.find(neighbor) == visited.end()) {
                if (checkCycle(neighbor, vertex, visited)) {
                    return true;
                }
            } else if (neighbor != parent) {
                // If the neighbor is already visited and isn't the parent, we found a back-edge (cycle)
                return true;
            }
        }
        return false;
    }

public:
    UndirectedGraph() = default;
    ~UndirectedGraph() = default;

    // Prevent accidental copying if dealing with massive graphs
    UndirectedGraph(const UndirectedGraph&) = delete;
    UndirectedGraph& operator=(const UndirectedGraph&) = delete;

    // ─────────────────── Mutators ───────────────────

    // Adds a disconnected vertex to the graph. 
    // If the vertex already exists, this does nothing.
    void addVertex(int vertex) {
        if (adj.find(vertex) == adj.end()) {
            adj[vertex] = unordered_set<int>();
        }
    }

    // Adds an undirected edge between u and v.
    // Automatically creates the vertices if they do not exist.
    void addEdge(int u, int v) {
        addVertex(u);
        addVertex(v);
        
        // Self-loops can be allowed or ignored depending on requirements. 
        // Here, we'll allow them, but an undirected self loop only counts once.
        adj[u].insert(v);
        if (u != v) {
            adj[v].insert(u);
        }
    }

    // Removes an edge between u and v.
    void removeEdge(int u, int v) {
        if (adj.find(u) != adj.end()) adj[u].erase(v);
        if (adj.find(v) != adj.end()) adj[v].erase(u);
    }

    // Completely removes a vertex and all of its connected edges.
    void removeVertex(int vertex) {
        if (adj.find(vertex) == adj.end()) return;

        // First, go to all neighbors and remove the edge pointing back to this vertex
        for (int neighbor : adj[vertex]) {
            adj[neighbor].erase(vertex);
        }

        // Finally, remove the vertex itself from the map
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
        // Since each undirected edge is stored twice (once in u, once in v), we divide by 2.
        // Self-loops are only stored once per node in our insert logic, so we must account for them if present.
        return count / 2; 
    }

    // The degree is the number of edges connected to a vertex.
    [[nodiscard]] optional<int> getDegree(int vertex) const {
        if (!hasVertex(vertex)) return nullopt;
        return adj.at(vertex).size();
    }

    // ─────────────────── Traversals ───────────────────

    // Standard Breadth-First Search from a starting node.
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

    // Standard Depth-First Search from a starting node.
    vector<int> dfs(int startVertex) const {
        vector<int> traversal;
        if (!hasVertex(startVertex)) return traversal;

        unordered_set<int> visited;
        dfsHelper(startVertex, visited, traversal);
        return traversal;
    }

    // ─────────────────── Algorithms ───────────────────

    // Checks if the graph contains at least one cycle.
    [[nodiscard]] bool hasCycle() const {
        unordered_set<int> visited;

        // We must loop over all vertices in case the graph is disconnected
        for (const auto& pair : adj) {
            int vertex = pair.first;
            if (visited.find(vertex) == visited.end()) {
                // Pass -1 (or any dummy value) as the parent for the starting node
                if (checkCycle(vertex, -1, visited)) {
                    return true;
                }
            }
        }
        return false;
    }

    // Returns a list of all connected components in the graph.
    // Each component is a vector of vertex IDs.
    vector<vector<int>> getConnectedComponents() const {
        vector<vector<int>> components;
        unordered_set<int> visited;

        for (const auto& pair : adj) {
            int vertex = pair.first;
            if (visited.find(vertex) == visited.end()) {
                vector<int> component;
                dfsHelper(vertex, visited, component);
                components.push_back(component);
            }
        }
        return components;
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
    UndirectedGraph graph;

    // Build a graph with two separate components
    // Component 1: 1 - 2 - 3 (Triangle) and 3 - 4
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);
    graph.addEdge(3, 4);

    // Component 2: 5 - 6
    graph.addEdge(5, 6);

    // Isolated Node
    graph.addVertex(99);

    cout << "Initial Graph Structure:\n";
    graph.printGraph();

    cout << "\nGraph Stats:\n";
    cout << "Vertices:     " << graph.getVertexCount() << "\n";
    cout << "Edges:        " << graph.getEdgeCount() << "\n";
    cout << "Degree of 3:  " << graph.getDegree(3).value_or(-1) << "\n";
    
    cout << "\nAlgorithms:\n";
    cout << "Has Cycle?    " << (graph.hasCycle() ? "Yes" : "No") << "\n";

    cout << "\nTraversals (starting at 1):\n";
    cout << "BFS: ";
    for (int v : graph.bfs(1)) cout << v << " ";
    
    cout << "\nDFS: ";
    for (int v : graph.dfs(1)) cout << v << " ";
    cout << "\n";

    cout << "\nConnected Components:\n";
    auto components = graph.getConnectedComponents();
    for (size_t i = 0; i < components.size(); ++i) {
        cout << "  Component " << i + 1 << ": ";
        for (int v : components[i]) {
            cout << v << " ";
        }
        cout << "\n";
    }

    cout << "\n--- Modifying Graph ---\n";
    
    cout << "\nRemoving edge (1, 3) to break the cycle...\n";
    graph.removeEdge(1, 3);
    cout << "Has Cycle?    " << (graph.hasCycle() ? "Yes" : "No") << "\n";

    cout << "\nRemoving vertex 3 (should sever connections to 2 and 4)...\n";
    graph.removeVertex(3);
    graph.printGraph();

    cout << "\nFinal Connected Components:\n";
    components = graph.getConnectedComponents();
    for (size_t i = 0; i < components.size(); ++i) {
        cout << "  Component " << i + 1 << ": ";
        for (int v : components[i]) {
            cout << v << " ";
        }
        cout << "\n";
    }

    return 0;
}
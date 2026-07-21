#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <optional>

using namespace std;

class MultiGraph {

private:
    // ─────────────────── Graph Representation ───────────────────
    
    // Adjacency List using unordered_multiset.
    // This allows multiple identical destination vertices (duplicate edges).
    unordered_map<int, unordered_multiset<int>> adj;
    
    bool isDirected;

public:
    explicit MultiGraph(bool directed = false) : isDirected(directed) {}
    ~MultiGraph() = default;

    MultiGraph(const MultiGraph&) = delete;
    MultiGraph& operator=(const MultiGraph&) = delete;

    // ─────────────────── Mutators ───────────────────

    void addVertex(int vertex) {
        if (adj.find(vertex) == adj.end()) {
            adj[vertex] = unordered_multiset<int>();
        }
    }

    // Adds a single edge between u and v. 
    // If called multiple times with the same u and v, it creates multiple edges.
    void addEdge(int u, int v) {
        addVertex(u);
        addVertex(v);
        
        adj[u].insert(v);
        if (!isDirected && u != v) {
            adj[v].insert(u);
        }
    }

    // Removes exactly ONE instance of an edge between u and v.
    void removeSingleEdge(int u, int v) {
        if (adj.find(u) != adj.end()) {
            auto it = adj[u].find(v);
            if (it != adj[u].end()) {
                adj[u].erase(it); // Erases only the element pointed to by the iterator
            }
        }

        if (!isDirected && u != v) {
            if (adj.find(v) != adj.end()) {
                auto it = adj[v].find(u);
                if (it != adj[v].end()) {
                    adj[v].erase(it);
                }
            }
        }
    }

    // Removes ALL edges existing between u and v.
    void removeAllEdgesBetween(int u, int v) {
        if (adj.find(u) != adj.end()) {
            adj[u].erase(v); // Passing the value to erase() removes ALL instances
        }
        
        if (!isDirected && u != v) {
            if (adj.find(v) != adj.end()) {
                adj[v].erase(u);
            }
        }
    }

    // Completely removes a vertex and all of its connected edges.
    void removeVertex(int vertex) {
        if (adj.find(vertex) == adj.end()) return;

        if (isDirected) {
            // Scan all vertices to remove incoming edges
            for (auto& pair : adj) {
                pair.second.erase(vertex);
            }
        } else {
            // Remove the reverse edges from all neighbors
            for (int neighbor : adj[vertex]) {
                adj[neighbor].erase(vertex);
            }
        }

        adj.erase(vertex);
    }

    void clear() {
        adj.clear();
    }

    // ─────────────────── Queries ───────────────────

    [[nodiscard]] bool hasVertex(int vertex) const {
        return adj.find(vertex) != adj.end();
    }

    // Returns true if AT LEAST one edge exists between u and v.
    [[nodiscard]] bool hasEdge(int u, int v) const {
        if (adj.find(u) == adj.end()) return false;
        return adj.at(u).find(v) != adj.at(u).end();
    }

    // Returns the exact number of edges between u and v.
    [[nodiscard]] int getMultiplicity(int u, int v) const {
        if (adj.find(u) == adj.end()) return 0;
        return adj.at(u).count(v);
    }

    [[nodiscard]] int getVertexCount() const {
        return adj.size();
    }

    [[nodiscard]] int getEdgeCount() const {
        int count = 0;
        for (const auto& pair : adj) {
            count += pair.second.size(); // size() counts all duplicates
        }
        return isDirected ? count : count / 2;
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
    cout << "=== Directed Multigraph (e.g., Network Packets between Servers) ===\n";
    MultiGraph network(true);

    // Send 3 distinct data packets from Server 1 to Server 2
    network.addEdge(1, 2);
    network.addEdge(1, 2);
    network.addEdge(1, 2);
    
    // Send 1 packet from Server 2 to Server 3
    network.addEdge(2, 3);

    // Send 2 packets from Server 1 to Server 3
    network.addEdge(1, 3);
    network.addEdge(1, 3);

    network.printGraph();

    cout << "\nStats:\n";
    cout << "Total Edges: " << network.getEdgeCount() << "\n";
    cout << "Multiplicity (1 -> 2): " << network.getMultiplicity(1, 2) << " edges\n";
    cout << "Multiplicity (1 -> 3): " << network.getMultiplicity(1, 3) << " edges\n";

    cout << "\nRemoving ONE edge from 1 to 2...\n";
    network.removeSingleEdge(1, 2);
    cout << "New Multiplicity (1 -> 2): " << network.getMultiplicity(1, 2) << " edges\n";

    cout << "\nRemoving ALL edges from 1 to 3...\n";
    network.removeAllEdgesBetween(1, 3);
    cout << "New Multiplicity (1 -> 3): " << network.getMultiplicity(1, 3) << " edges\n";

    cout << "\nFinal Graph Structure:\n";
    network.printGraph();

    return 0;
}
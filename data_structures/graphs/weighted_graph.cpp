#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <optional>
#include <algorithm>

using namespace std;

class WeightedGraph {

private:
    // ─────────────────── Graph Representation ───────────────────
    
    // Adjacency List: Maps a vertex ID to a map of its neighbors and edge weights.
    // u -> { v -> weight }
    // Using a nested unordered_map allows O(1) edge lookups, updates, and deletions.
    unordered_map<int, unordered_map<int, int>> adj;
    
    bool isDirected;

public:
    // By default, the graph is undirected unless specified otherwise.
    explicit WeightedGraph(bool directed = false) : isDirected(directed) {}
    ~WeightedGraph() = default;

    WeightedGraph(const WeightedGraph&) = delete;
    WeightedGraph& operator=(const WeightedGraph&) = delete;

    // ─────────────────── Mutators ───────────────────

    void addVertex(int vertex) {
        if (adj.find(vertex) == adj.end()) {
            adj[vertex] = unordered_map<int, int>();
        }
    }

    // Adds a weighted edge between u and v.
    // If the edge already exists, this updates the weight.
    void addEdge(int u, int v, int weight) {
        addVertex(u);
        addVertex(v);
        
        adj[u][v] = weight;
        
        if (!isDirected && u != v) {
            adj[v][u] = weight;
        }
    }

    void removeEdge(int u, int v) {
        if (adj.find(u) != adj.end()) {
            adj[u].erase(v);
        }
        if (!isDirected && adj.find(v) != adj.end()) {
            adj[v].erase(u);
        }
    }

    void removeVertex(int vertex) {
        if (adj.find(vertex) == adj.end()) return;

        // If the graph is directed, we must scan all vertices to remove incoming edges
        if (isDirected) {
            for (auto& pair : adj) {
                pair.second.erase(vertex);
            }
        } else {
            // For undirected, we just visit the neighbors and remove the reverse edge
            for (const auto& neighborPair : adj[vertex]) {
                int neighbor = neighborPair.first;
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

    [[nodiscard]] bool hasEdge(int u, int v) const {
        if (adj.find(u) == adj.end()) return false;
        return adj.at(u).find(v) != adj.at(u).end();
    }

    [[nodiscard]] optional<int> getWeight(int u, int v) const {
        if (hasEdge(u, v)) {
            return adj.at(u).at(v);
        }
        return nullopt;
    }

    [[nodiscard]] int getVertexCount() const {
        return adj.size();
    }

    // ─────────────────── Algorithms ───────────────────

    // Dijkstra's Algorithm: Single-Source Shortest Path (for non-negative weights).
    // Returns a map of destination vertices to their shortest distance from the startVertex.
    unordered_map<int, int> dijkstra(int startVertex) const {
        unordered_map<int, int> distances;
        const int INF = numeric_limits<int>::max();

        // Initialize all distances to Infinity
        for (const auto& pair : adj) {
            distances[pair.first] = INF;
        }

        if (!hasVertex(startVertex)) return distances;

        // Min-Heap priority queue stores pairs of {distance, vertex}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        distances[startVertex] = 0;
        pq.push({0, startVertex});

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int currentVertex = pq.top().second;
            pq.pop();

            // Optimization: Skip if we've already found a shorter path to this vertex
            if (currentDist > distances[currentVertex]) continue;

            // Relax all neighboring edges
            for (const auto& neighborPair : adj.at(currentVertex)) {
                int neighbor = neighborPair.first;
                int weight = neighborPair.second;

                int newDist = currentDist + weight;

                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    pq.push({newDist, neighbor});
                }
            }
        }

        return distances;
    }

    // Prim's Algorithm: Minimum Spanning Tree (MST).
    // Valid for connected, undirected graphs.
    // Returns the total weight of the MST and prints the edges included.
    optional<int> primsMST() const {
        if (isDirected || adj.empty()) return nullopt;

        unordered_map<int, bool> inMST;
        for (const auto& pair : adj) inMST[pair.first] = false;

        // Min-Heap stores {weight, {u, v}}
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;

        int startVertex = adj.begin()->first;
        inMST[startVertex] = true;
        int mstWeight = 0;
        int edgesIncluded = 0;

        // Add all edges from the starting vertex to the PQ
        for (const auto& neighborPair : adj.at(startVertex)) {
            pq.push({neighborPair.second, {startVertex, neighborPair.first}});
        }

        cout << "MST Edges:\n";

        while (!pq.empty() && edgesIncluded < adj.size() - 1) {
            int weight = pq.top().first;
            int u = pq.top().second.first;
            int v = pq.top().second.second;
            pq.pop();

            // If the destination is already in the MST, skip it (prevents cycles)
            if (inMST[v]) continue;

            // Include edge in MST
            inMST[v] = true;
            mstWeight += weight;
            edgesIncluded++;
            
            cout << "  (" << u << " - " << v << ") : weight " << weight << "\n";

            // Add all edges from the newly added vertex to the PQ
            for (const auto& neighborPair : adj.at(v)) {
                if (!inMST[neighborPair.first]) {
                    pq.push({neighborPair.second, {v, neighborPair.first}});
                }
            }
        }

        // Check if the graph is disconnected
        if (edgesIncluded != adj.size() - 1) {
            cout << "Graph is disconnected! Spanning forest created instead.\n";
        }

        return mstWeight;
    }

    // ─────────────────── Printing ───────────────────

    void printGraph() const {
        if (adj.empty()) {
            cout << "Graph is empty.\n";
            return;
        }

        for (const auto& pair : adj) {
            cout << "[" << pair.first << "] -> { ";
            for (const auto& neighborPair : pair.second) {
                cout << "(" << neighborPair.first << ", w:" << neighborPair.second << ") ";
            }
            cout << "}\n";
        }
    }
};

// ─────────────────── Main Function / Testing ───────────────────

int main() {
    // 1. Test Undirected Weighted Graph (Useful for Routing / Spanning Trees)
    cout << "=== Undirected Weighted Graph ===\n";
    WeightedGraph uGraph(false); 

    // Add edges to create a network
    uGraph.addEdge(0, 1, 4);
    uGraph.addEdge(0, 7, 8);
    uGraph.addEdge(1, 2, 8);
    uGraph.addEdge(1, 7, 11);
    uGraph.addEdge(2, 3, 7);
    uGraph.addEdge(2, 8, 2);
    uGraph.addEdge(2, 5, 4);
    uGraph.addEdge(3, 4, 9);
    uGraph.addEdge(3, 5, 14);
    uGraph.addEdge(4, 5, 10);
    uGraph.addEdge(5, 6, 2);
    uGraph.addEdge(6, 7, 1);
    uGraph.addEdge(6, 8, 6);
    uGraph.addEdge(7, 8, 7);

    uGraph.printGraph();

    cout << "\nRunning Prim's Algorithm (Minimum Spanning Tree):\n";
    int mstWeight = uGraph.primsMST().value_or(-1);
    cout << "Total MST Weight: " << mstWeight << "\n";

    cout << "\nRunning Dijkstra's Algorithm (Shortest Paths from Node 0):\n";
    auto distances = uGraph.dijkstra(0);
    for (int i = 0; i < uGraph.getVertexCount(); ++i) {
        cout << "  Distance 0 -> " << i << " = " << distances[i] << "\n";
    }

    // 2. Test Directed Weighted Graph (Useful for Flights / Asymmetric costs)
    cout << "\n=== Directed Weighted Graph ===\n";
    WeightedGraph dGraph(true); 

    dGraph.addEdge(1, 2, 10); // Flight 1 -> 2 costs $10
    dGraph.addEdge(1, 3, 15);
    dGraph.addEdge(2, 4, 12);
    dGraph.addEdge(3, 4, 50);
    dGraph.addEdge(2, 3, 2);  // Flight 2 -> 3 exists, but not 3 -> 2

    dGraph.printGraph();

    cout << "\nRunning Dijkstra's Algorithm (Shortest Flights from Node 1):\n";
    auto flightCosts = dGraph.dijkstra(1);
    for (int i = 1; i <= dGraph.getVertexCount(); ++i) {
        cout << "  Cost 1 -> " << i << " = $" << flightCosts[i] << "\n";
    }

    return 0;
}
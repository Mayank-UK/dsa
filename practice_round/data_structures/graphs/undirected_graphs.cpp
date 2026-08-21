/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <climits>
#include <vector>

using std::cout;
using std::queue;
using std::unordered_map;
using std::unordered_set;
using std::vector;

class UndirectedGraph
{
private:
    unordered_map<int, unordered_set<int>> adj;

    void dfsRecursive(int currentVertex, unordered_set<int> &visitedVertices, vector<int> &traversal)
    {
        visitedVertices.insert(currentVertex);
        traversal.push_back(currentVertex);

        for (auto neighbour : adj[currentVertex])
        {
            if (visitedVertices.find(neighbour) == visitedVertices.end())
            {
                dfsRecursive(neighbour, visitedVertices, traversal);
            }
        }
    }

    bool hasCycleRecursive(unordered_set<int> &visitedVertices, int currentVertex, int parentVertex)
    {
        visitedVertices.insert(currentVertex);

        for (int neighbour : adj[currentVertex])
        {
            // if node is visited and it's parent is not the neighbour, then cycle is detected
            if ((visitedVertices.find(neighbour) != visitedVertices.end()) && (neighbour != parentVertex))
            {
                return true;
            }

            // if node is not visited
            if (visitedVertices.find(neighbour) == visitedVertices.end())
            {

                if (hasCycleRecursive(visitedVertices, neighbour, currentVertex))
                {
                    return true;
                }
            }
        }

        return false;
    }

public:
    UndirectedGraph() {}

    // Prevent accidental copying if dealing with massive graphs
    UndirectedGraph(const UndirectedGraph &) = delete;
    UndirectedGraph &operator=(const UndirectedGraph &) = delete;

    ~UndirectedGraph() {}

    void addVertex(int v)
    {
        if (adj.find(v) == adj.end())
        {
            adj[v] = {};
        }
    }

    void addEdge(int v1, int v2)
    {
        if (adj.find(v1) == adj.end() || adj.find(v2) == adj.end())
        {
            return;
        }

        if (v1 != v2)
        {
            adj[v1].insert(v2);
            adj[v2].insert(v1);
        }
    }

    bool hasVertex(int v)
    {
        return (adj.find(v) != adj.end());
    }

    bool hasEdge(int v1, int v2)
    {
        if (adj.find(v1) == adj.end() || adj.find(v2) == adj.end())
        {
            return false;
        }

        return (adj[v1].find(v2) != adj[v1].end());
    }

    int getVertexCount()
    {
        return adj.size();
    }

    int getEdgeCount()
    {
        int count = 0;

        for (auto item : adj)
        {
            for (int vertex : adj[item.first])
            {
                count++;
            }
        }

        return count / 2;
    }

    int getDegree(int v)
    {
        if (adj.find(v) == adj.end())
        {
            return INT_MIN;
        }

        int degree = 0;

        for (int i : adj[v])
        {
            degree++;
        }

        return degree;
    }

    void bfs(int startingVertex)
    {
        if (!hasVertex(startingVertex))
        {
            return;
        }

        queue<int> q;
        unordered_set<int> visitedVertices;
        vector<int> traversal;

        q.push(startingVertex);
        visitedVertices.insert(startingVertex);
        traversal.push_back(startingVertex);

        while (!q.empty())
        {
            int vertex = q.front();
            q.pop();

            for (int neighbour : adj[vertex])
            {
                if (visitedVertices.find(neighbour) == visitedVertices.end())
                {
                    visitedVertices.insert(neighbour);
                    traversal.push_back(neighbour);
                    q.push(neighbour);
                }
            }
        }

        for (int item : traversal)
        {
            cout << item << " ";
        }

        cout << "\n";
    }

    void bfsComplete()
    {
        unordered_set<int> visitedVertices;
        queue<int> q;
        vector<int> traversal;

        for (auto adjItem : adj)
        {
            int startingVertex = adjItem.first;

            if (visitedVertices.find(startingVertex) != visitedVertices.end())
            {
                continue;
            }

            q.push(startingVertex);
            visitedVertices.insert(startingVertex);
            traversal.push_back(startingVertex);

            while (!q.empty())
            {
                int front = q.front();
                q.pop();

                for (int vertex : adj[front])
                {
                    if (visitedVertices.find(vertex) == visitedVertices.end())
                    {
                        visitedVertices.insert(vertex);
                        traversal.push_back(vertex);
                        q.push(vertex);
                    }
                }
            }
        }

        for (int item : traversal)
        {
            cout << item << " ";
        }

        cout << "\n";
    }

    void dfs(int startingVertex)
    {
        if (!hasVertex(startingVertex))
        {
            return;
        }

        unordered_set<int> visitedVertices;
        vector<int> traversal;

        dfsRecursive(startingVertex, visitedVertices, traversal);

        for (int item : traversal)
        {
            cout << item << " ";
        }

        cout << "\n";
    }

    void dfsComplete()
    {
        unordered_set<int> visitedVertices;
        vector<int> traversal;

        for (auto adjItem : adj)
        {
            int startingVertex = adjItem.first;

            if (visitedVertices.find(startingVertex) != visitedVertices.end())
            {
                continue;
            }

            dfsRecursive(startingVertex, visitedVertices, traversal);
        }

        for (int item : traversal)
        {
            cout << item << " ";
        }

        cout << "\n";
    }

    void removeVertex(int v)
    {
        if (adj.find(v) == adj.end())
        {
            return;
        }

        adj.erase(v);

        for (auto &item : adj)
        {
            item.second.erase(v);
        }
    }

    void removeEdge(int v1, int v2)
    {
        if (adj.find(v1) == adj.end() || adj.find(v2) == adj.end())
        {
            return;
        }

        adj[v1].erase(v2);
        adj[v2].erase(v1);
    }

    bool hasCycle()
    {
        unordered_set<int> visitedVertices;
        bool hasCycle = false;

        for (auto item : adj)
        {
            auto startingVertex = item.first;

            if (visitedVertices.find(startingVertex) != visitedVertices.end())
            {
                continue;
            }

            hasCycle = hasCycleRecursive(visitedVertices, startingVertex, -1);

            if (hasCycle)
            {
                break;
            }
        }

        return hasCycle;
    }

    void clear()
    {
        adj.clear();
    }

    void printGraph()
    {
        if (adj.empty())
        {
            return;
        }

        for (auto item : adj)
        {
            cout << item.first << ": ";

            for (int vertex : item.second)
            {
                cout << vertex << " ";
            }

            cout << "\n";
        }
    }
};

int main()
{
    UndirectedGraph graph;

    // ============================================================
    // Add vertices
    // ============================================================

    for (int i = 1; i <= 8; i++)
    {
        graph.addVertex(i);
    }

    // ============================================================
    // Create graph
    //
    // Component 1:
    //
    //       1
    //      / \
    //     2---3
    //     |
    //     4
    //
    // Component 2:
    //
    //     5 --- 6
    //      \   /
    //        7
    //
    // Component 3:
    //
    //     8
    //
    // Component 1 and 2 contain cycles.
    // ============================================================

    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);

    graph.addEdge(5, 6);
    graph.addEdge(6, 7);
    graph.addEdge(7, 5);

    // 8 remains isolated.

    // ============================================================
    // Print graph
    // ============================================================

    cout << "========== GRAPH ==========\n";
    graph.printGraph();

    // ============================================================
    // Vertex / edge count
    // ============================================================

    cout << "\n========== COUNTS ==========\n";

    cout << "Vertex count: "
         << graph.getVertexCount() << "\n";

    cout << "Edge count: "
         << graph.getEdgeCount() << "\n";

    // ============================================================
    // Vertex existence
    // ============================================================

    cout << "\n========== VERTEX CHECK ==========\n";

    cout << "Has vertex 4: "
         << graph.hasVertex(4) << "\n";

    cout << "Has vertex 10: "
         << graph.hasVertex(10) << "\n";

    // ============================================================
    // Edge existence
    // ============================================================

    cout << "\n========== EDGE CHECK ==========\n";

    cout << "Has edge 1-2: "
         << graph.hasEdge(1, 2) << "\n";

    cout << "Has edge 1-4: "
         << graph.hasEdge(1, 4) << "\n";

    // ============================================================
    // Degree
    // ============================================================

    cout << "\n========== DEGREE ==========\n";

    cout << "Degree of 1: "
         << graph.getDegree(1) << "\n";

    cout << "Degree of 2: "
         << graph.getDegree(2) << "\n";

    cout << "Degree of 8: "
         << graph.getDegree(8) << "\n";

    // ============================================================
    // BFS on individual components
    // ============================================================

    cout << "\n========== BFS ==========\n";

    cout << "BFS from 1: ";
    graph.bfs(1);

    cout << "BFS from 5: ";
    graph.bfs(5);

    cout << "BFS from 8: ";
    graph.bfs(8);

    // ============================================================
    // DFS on individual components
    // ============================================================

    cout << "\n========== DFS ==========\n";

    cout << "DFS from 1: ";
    graph.dfs(1);

    cout << "DFS from 5: ";
    graph.dfs(5);

    cout << "DFS from 8: ";
    graph.dfs(8);

    // ============================================================
    // Complete BFS / DFS
    // Traverses every connected component.
    // ============================================================

    cout << "\n========== COMPLETE BFS ==========\n";

    graph.bfsComplete();

    cout << "\n========== COMPLETE DFS ==========\n";

    graph.dfsComplete();

    // ============================================================
    // Cycle detection
    // ============================================================

    cout << "\n========== CYCLE CHECK ==========\n";

    cout << "Has cycle: "
         << graph.hasCycle() << "\n";

    // ============================================================
    // Remove an edge from component 1.
    //
    // 1
    // |
    // 2---3
    // |
    // 4
    //
    // No cycle in component 1 anymore.
    // But component 2 still contains a cycle.
    // ============================================================

    graph.removeEdge(1, 3);

    cout << "\nAfter removing edge 1-3:\n";
    graph.printGraph();

    cout << "Has cycle: "
         << graph.hasCycle() << "\n";

    // ============================================================
    // Remove another edge from component 2.
    //
    // 5 --- 6 --- 7
    //
    // No cycles remain.
    // ============================================================

    graph.removeEdge(5, 7);

    cout << "\nAfter removing edge 5-7:\n";
    graph.printGraph();

    cout << "Has cycle: "
         << graph.hasCycle() << "\n";

    // ============================================================
    // Remove vertex
    // ============================================================

    graph.removeVertex(2);

    cout << "\nAfter removing vertex 2:\n";
    graph.printGraph();

    cout << "Vertex count: "
         << graph.getVertexCount() << "\n";

    cout << "Edge count: "
         << graph.getEdgeCount() << "\n";

    // ============================================================
    // Final complete traversals
    // ============================================================

    cout << "\n========== FINAL BFS ==========\n";
    graph.bfsComplete();

    cout << "\n========== FINAL DFS ==========\n";
    graph.dfsComplete();

    // ============================================================
    // Clear graph
    // ============================================================

    graph.clear();

    cout << "\n========== AFTER CLEAR ==========\n";

    cout << "Vertex count: "
         << graph.getVertexCount() << "\n";

    cout << "Edge count: "
         << graph.getEdgeCount() << "\n";

    cout << "Has cycle: "
         << graph.hasCycle() << "\n";

    return 0;
}
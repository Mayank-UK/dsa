/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using std::cout;
using std::queue;
using std::unordered_map;
using std::unordered_set;
using std::vector;

class DirectedGraph
{
private:
    unordered_map<int, unordered_set<int>> adj;

    void dfsRecursive(unordered_set<int> &visitedVertices, vector<int> &traversal, int currentVertex)
    {
        visitedVertices.insert(currentVertex);
        traversal.push_back(currentVertex);

        for (auto neighbour : adj[currentVertex])
        {
            if (visitedVertices.find(neighbour) != visitedVertices.end())
            {
                continue;
            }

            dfsRecursive(visitedVertices, traversal, neighbour);
        }
    }

    bool hasCycleRecursive(unordered_set<int> &visitedVertices, unordered_set<int> &currentPath, int currentVertex)
    {
        visitedVertices.insert(currentVertex);
        currentPath.insert(currentVertex);

        for (int neighbour : adj[currentVertex])
        {
            if (currentPath.find(neighbour) != currentPath.end())
            {
                return true;
            }

            if (visitedVertices.find(neighbour) == visitedVertices.end())
            {
                if (hasCycleRecursive(visitedVertices, currentPath, neighbour))
                {
                    return true;
                }
            }
        }

        // recursion function should maintain this itself, rather than doing ultimate clear() in public loopCheck method
        currentPath.erase(currentVertex);
        return false;
    }

    // void connectedComponentsRecursive(unordered_set<int> &visitedVertices, ) {}

public:
    DirectedGraph() {}

    ~DirectedGraph() {}

    void addVertex(int vertex)
    {
        if (adj.find(vertex) != adj.end())
        {
            return;
        }

        adj[vertex] = {};
    }

    void addEdge(int v1, int v2)
    {
        if (adj.find(v1) == adj.end() || adj.find(v2) == adj.end())
        {
            return;
        }

        adj[v1].insert(v2);
    }

    bool hasVertex(int vertex)
    {
        return !(adj.find(vertex) == adj.end());
    }

    bool hasEdge(int v1, int v2)
    {
        if (adj.find(v1) == adj.end() || adj.find(v2) == adj.end())
        {
            return false;
        }

        return !(adj[v1].find(v2) == adj[v1].end());
    }

    int getVertexCount()
    {
        return adj.size();
    }

    int getEdgeCount()
    {
        int count = 0;

        for (auto adjItem : adj)
        {
            for (int item : adjItem.second)
            {
                count++;
            }
        }

        return count;
    }

    void bfsComplete()
    {
        unordered_set<int> visitedVertices;
        vector<int> traversal;
        queue<int> q;

        for (auto adjItem : adj)
        {

            int startingVertex = adjItem.first;

            if (visitedVertices.find(startingVertex) != visitedVertices.end())
            {
                continue;
            }

            visitedVertices.insert(startingVertex);
            traversal.push_back(startingVertex);
            q.push(startingVertex);

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

        for (int vertex : traversal)
        {
            cout << vertex;
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

            dfsRecursive(visitedVertices, traversal, startingVertex);
        }

        for (int vertex : traversal)
        {
            cout << vertex;
        }

        cout << "\n";
    }

    bool hasCycle()
    {
        unordered_set<int> visitedVertices;
        unordered_set<int> currentPath;
        bool hasCycle = false;

        for (auto adjItem : adj)
        {
            int startingVertex = adjItem.first;

            if (visitedVertices.find(startingVertex) != visitedVertices.end())
            {
                continue;
            }

            hasCycle = hasCycleRecursive(visitedVertices, currentPath, startingVertex);

            if (hasCycle)
            {
                break;
            }
        }

        return hasCycle;
    }

    void showWeaklyConnectedComponents()
    {
        unordered_set<int> visitedVertices;
        unordered_map<int, unordered_set<int>> connectedComponents;
        queue<int> q;

        for (auto adjItem : adj)
        {
            int startingVertex = adjItem.first;

            if (visitedVertices.find(startingVertex) != visitedVertices.end())
            {
                continue;
            }

            visitedVertices.insert(startingVertex);
            connectedComponents[startingVertex] = {};
            connectedComponents[startingVertex].insert(startingVertex);
            q.push(startingVertex);

            while (!q.empty())
            {
                int front = q.front();
                q.pop();

                // traverse outgoing edges
                for (int vertex : adj[front])
                {
                    if (visitedVertices.find(vertex) == visitedVertices.end())
                    {
                        visitedVertices.insert(vertex);
                        connectedComponents[startingVertex].insert(vertex);
                        q.push(vertex);
                    }
                }

                // traverse incoming edges
                for (auto adjItem : adj)
                {
                    for (int neighbour : adjItem.second)
                    {
                        if (neighbour == front)
                        {
                            int incomingVertex = adjItem.first;

                            if (visitedVertices.find(incomingVertex) == visitedVertices.end())
                            {
                                visitedVertices.insert(incomingVertex);
                                connectedComponents[startingVertex].insert(incomingVertex);
                                q.push(incomingVertex);
                            }
                        }
                    }
                }
            }
        }

        for (auto component : connectedComponents)
        {
            cout << component.first << ": ";

            for (int vertex : component.second)
            {
                cout << vertex;
            }

            cout << "\n";
        }
    }

    void showStronglyConnectedComponents() {}

    void showDegree(int vertex)
    {
        if (adj.find(vertex) == adj.end())
        {
            cout << "Vertex not found\n";
            return;
        }

        cout << "Out degree: " << adj[vertex].size() << "\n";

        cout << "In degree: ";
        int count = 0;

        for (auto adjItem : adj)
        {
            if (adjItem.second.find(vertex) != adjItem.second.end())
            {
                count++;
            }
        }

        cout << count << "\n";
    }

    void removeVertex(int vertex)
    {
        if (adj.find(vertex) == adj.end())
        {
            return;
        }

        adj.erase(vertex);

        for (auto &adjItem : adj)
        {
            adjItem.second.erase(vertex);
        }
    }

    void removeEdge(int v1, int v2)
    {
        if (adj.find(v1) == adj.end() || adj.find(v2) == adj.end())
        {
            return;
        }

        adj[v1].erase(v2);
    }

    void printGraph()
    {
        for (auto adjItem : adj)
        {
            cout << adjItem.first << ": ";

            for (int vertex : adjItem.second)
            {
                cout << vertex;
            }

            cout << "\n";
        }
    }

    void clear()
    {
        adj.clear();
    }
};
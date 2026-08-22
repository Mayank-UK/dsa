/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using std::cout;
using std::hash;
using std::queue;
using std::size_t;
using std::unordered_map;
using std::unordered_set;
using std::vector;

struct Edge
{
    int source;
    int destination;
    int weight;

    Edge(int sour, int dest, int w)
    {
        source = sour;
        destination = dest;
        weight = w;
    }

    /*
        This is operator overloading, normally C++ doesn't know how to compare two Edge objects
        This tells unordered_set<Edge> that two Edge objects are equal if both their destination and weight are equal.
    */
    bool operator==(const Edge &other) const
    {
        return source == other.source && destination == other.destination && weight == other.weight;
    }
};

/*
    Generates a hash value for an Edge so it can be stored in an unordered_set.
    The destination and weight are combined to produce the hash.
*/
struct EdgeHash
{
    size_t operator()(const Edge &edge) const
    {
        /*
            ^ is the bitwise XOR (exclusive OR) operator in C++. You're using XOR to combine the two hash values.
            0 ^ 0 = 0
            0 ^ 1 = 1
            1 ^ 0 = 1
            1 ^ 1 = 0
        */
        return hash<int>{}(edge.source) ^ hash<int>{}(edge.destination) ^ (hash<int>{}(edge.weight) << 1);
    }
};

class DirectedGraph
{
private:
    /*
        EdgeHash tells the unordered_set how to calculate the hash of an Edge
        The second template parameter of unordered_set is the hash function, and it has a default hash function for simple types like int, char, etc, but needs to be provided separately for custom ones like Edge
    */
    unordered_map<int, unordered_set<Edge, EdgeHash>> adj;

    void dfsRecursive(int currentVertex, unordered_set<int> &visitedVertices, vector<int> &traversal)
    {
        visitedVertices.insert(currentVertex);
        traversal.push_back(currentVertex);

        for (auto neighbour : adj[currentVertex])
        {
            if (visitedVertices.find(neighbour.destination) != visitedVertices.end())
            {
                continue;
            }

            dfsRecursive(neighbour.destination, visitedVertices, traversal);
        }
    }

    bool hasCycleRecursive(int currentVertex, unordered_set<int> &visitedVertices, unordered_set<int> &currentPath)
    {
        visitedVertices.insert(currentVertex);
        currentPath.insert(currentVertex);

        for (auto neighbour : adj[currentVertex])
        {
            if (visitedVertices.find(neighbour.destination) != visitedVertices.end())
            {
                if (currentPath.find(neighbour.destination) != currentPath.end())
                {
                    return true;
                }

                continue;
            }

            if (hasCycleRecursive(neighbour.destination, visitedVertices, currentPath))
            {
                return true;
            }
        }

        currentPath.erase(currentVertex);

        return false;
    }

public:
    void addVertex(int vertex)
    {
        if (adj.find(vertex) != adj.end())
        {
            return;
        }

        adj[vertex] = {};
    }

    void addEdge(int v1, int v2, int weight)
    {
        if ((adj.find(v1) == adj.end()) || (adj.find(v2) == adj.end()))
        {
            return;
        }

        Edge newEdge(v1, v2, weight);

        adj[v1].insert(newEdge);
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

                for (auto neighbour : adj[front])
                {
                    if (visitedVertices.find(neighbour.destination) == visitedVertices.end())
                    {
                        visitedVertices.insert(neighbour.destination);
                        traversal.push_back(neighbour.destination);
                        q.push(neighbour.destination);
                    }
                }
            }
        }

        cout << "BFS: ";

        for (int vertex : traversal)
        {
            cout << vertex << " ";
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

        cout << "DFS: ";

        for (int vertex : traversal)
        {
            cout << vertex << " ";
        }

        cout << "\n";
    }

    bool hasCycle()
    {
        unordered_set<int> visitedVertices;
        unordered_set<int> currentPath;
        bool loopDetected = false;

        for (auto adjItem : adj)
        {
            int startingVertex = adjItem.first;

            if (visitedVertices.find(startingVertex) != visitedVertices.end())
            {
                continue;
            }

            loopDetected = hasCycleRecursive(startingVertex, visitedVertices, currentPath);

            if (loopDetected)
            {
                break;
            }
        }

        return loopDetected;
    }

    bool hasVertex(int vertex)
    {
        return !(adj.find(vertex) == adj.end());
    }

    bool hasEdge(int v1, int v2)
    {
        if ((adj.find(v1) == adj.end()) || (adj.find(v2) == adj.end()))
        {
            return false;
        }

        for (auto neighbour : adj[v1])
        {
            if (neighbour.destination == v2)
            {
                return true;
            }
        }

        return false;
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
            for (auto neighbour : adjItem.second)
            {
                count++;
            }
        }

        return count;
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

                // traverse outgoing edges: front -> neighbour
                for (auto neighbour : adj[front])
                {
                    if (visitedVertices.find(neighbour.destination) == visitedVertices.end())
                    {
                        visitedVertices.insert(neighbour.destination);
                        connectedComponents[startingVertex].insert(neighbour.destination);
                        q.push(neighbour.destination);
                    }
                }

                // traverse incoming edges: neighbour -> front
                for (auto adjItem : adj)
                {
                    for (auto edge : adjItem.second)
                    {
                        if (edge.destination == front)
                        {
                            int incomingVertex = adjItem.first;

                            if (visitedVertices.find(incomingVertex) == visitedVertices.end())
                            {
                                // if not marked visited, it will be treated as starting of a separate component
                                visitedVertices.insert(incomingVertex);
                                connectedComponents[startingVertex].insert(incomingVertex);
                                // if not pushed in the queue it won't be traversed
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
            for (auto neighbour : component.second)
            {
                cout << neighbour;
            }

            cout << "\n";
        }
    }

    void showStronglyConnectedComponents() {}

    void showDegree(int vertex)
    {
        if (adj.find(vertex) == adj.end())
        {
            return;
        }

        cout << "Outward degree: " << adj[vertex].size() << "\n";

        int count = 0;
        cout << "Inward degree: ";

        for (auto adjItem : adj)
        {
            for (auto neighbour : adjItem.second)
            {
                if (neighbour.destination == vertex)
                {
                    count++;
                }
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
            for (auto it = adjItem.second.begin(); it != adjItem.second.end();)
            {
                if (it->destination == vertex)
                {
                    // after removing the vertex, iterator is assigned back pointing to the next element, else we increment it in the else block
                    it = adjItem.second.erase(it);
                    // there can be multiple edges between two vertices so continue without breaking
                }
                // if nothing was erased, then increment the iterator
                else
                {
                    ++it;
                }
            }
        }
    }

    void removeEdge(int v1, int v2, int weight)
    {
        if ((adj.find(v1) == adj.end()) || (adj.find(v2) == adj.end()))
        {
            return;
        }

        for (auto it = adj[v1].begin(); it != adj[v1].end(); ++it)
        {
            if (it->destination == v2 && it->weight == weight)
            {
                adj[v1].erase(it);
                return;
            }
        }
    }

    void printGraph()
    {
        for (auto adjItem : adj)
        {
            cout << adjItem.first << ": ";
            for (auto neighbour : adjItem.second)
            {
                cout << "[" << neighbour.destination << "," << neighbour.weight << "]";
            }
            cout << "\n";
        }
    }

    void clear()
    {
        adj.clear();
    }
};
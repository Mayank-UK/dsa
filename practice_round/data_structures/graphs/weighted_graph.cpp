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

struct Edge
{
    int destination;
    int weight;

    Edge(int dest, int w)
    {
        destination = dest;
        weight = w;
    }
};

class DirectedGraph
{
private:
    unordered_map<int, unordered_set<Edge>> adj;

    void dfsRecursive() {}

    void hasCycleRecursive() {}

public:
    void addVertex() {}

    void addEdge() {}

    void bfsComplete() {}

    void dfsComplete() {}

    bool hasCycle() {}

    bool hasEdge() {}

    bool hasEdge() {}

    int getVertexCount() {}

    int getEdgeCount() {}

    void showConnectedComponents() {}

    void showDegree() {}

    void removeVertex() {}

    void removeEdge() {}

    void printGraph() {}

    void clear() {}
};
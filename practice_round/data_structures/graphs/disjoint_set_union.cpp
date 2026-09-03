/*
            ############################################# Practice round 1 #############################################
*/

// #include <iostream>
// #include <unordered_map>
// #include <unordered_set>

// using std::cout;
// using std::unordered_map;
// using std::unordered_set;

// class DisjointSetUnion
// {
// private:
//     unordered_map<int, int> size;
//     unordered_map<int, int> parent;

// public:
//     DisjointSetUnion(unordered_map<int, unordered_set<int>> adjList)
//     {
//         for (auto adjItem : adjList)
//         {
//             size[adjItem.first] = 1;
//             parent[adjItem.first] = adjItem.first;
//         }
//     }

//     int findParent(int node)
//     {
//         // base case, node is parent of itself
//         if (node == parent[node])
//         {
//             return node;
//         }

//         // recursive step
//         return parent[node] = findParent(parent[node]);
//     }

//     void unionBySize(int node1, int node2)
//     {
//         int rootParentNode1 = findParent(node1);
//         int rootParentNode2 = findParent(node2);

//         // they already belong to the same component
//         if (rootParentNode1 == rootParentNode2)
//         {
//             return;
//         }

//         // size of rootParentNode1 is greater than rootParentNode2, then attach N1 to N2
//         if (size[rootParentNode1] > size[rootParentNode2])
//         {
//             parent[rootParentNode2] = rootParentNode1;
//             size[rootParentNode1] += size[rootParentNode2];
//         }
//         else if (size[rootParentNode1] < size[rootParentNode2])
//         {
//             parent[rootParentNode1] = rootParentNode2;
//             size[rootParentNode2] += size[rootParentNode1];
//         }
//         // sizes are equal
//         else
//         {
//             parent[rootParentNode2] = rootParentNode1;
//             size[rootParentNode1] += size[rootParentNode2];
//         }
//     }

//     bool isConnected(int node1, int node2)
//     {
//         int rootParentNode1 = findParent(node1);
//         int rootParentNode2 = findParent(node2);

//         if (rootParentNode1 == rootParentNode2)
//         {
//             return true;
//         }

//         return false;
//     }
// };

// int main()
// {
//     unordered_map<int, unordered_set<int>> adjList = {
//         {1, {2}},
//         {2, {1, 3}},
//         {3, {2}},
//         {4, {5}},
//         {5, {4, 6}},
//         {6, {5}},
//         {7, {}}};

//     DisjointSetUnion dsu(adjList);

//     // Initially:
//     // Component 1: {1}
//     // Component 2: {2}
//     // ...
//     // Component 7: {7}

//     dsu.unionBySize(1, 2);
//     dsu.unionBySize(2, 3);

//     dsu.unionBySize(4, 5);
//     dsu.unionBySize(5, 6);

//     cout << std::boolalpha;

//     cout << "1 and 3 connected: " << dsu.isConnected(1, 3) << '\n';

//     cout << "1 and 4 connected: " << dsu.isConnected(1, 4) << '\n';

//     cout << "4 and 6 connected: " << dsu.isConnected(4, 6) << '\n';

//     cout << "1 and 7 connected: " << dsu.isConnected(1, 7) << '\n';

//     // Merge the two components
//     dsu.unionBySize(3, 6);

//     cout << "\nAfter merging components:\n";

//     cout << "1 and 6 connected: " << dsu.isConnected(1, 6) << '\n';

//     cout << "2 and 5 connected: " << dsu.isConnected(2, 5) << '\n';

//     cout << "1 and 7 connected: " << dsu.isConnected(1, 7) << '\n';

//     return 0;
// }

/*
            ############################################# Practice round 2 #############################################
*/

// #include <iostream>
// #include <unordered_map>
// #include <unordered_set>

// using std::cout;
// using std::unordered_map;
// using std::unordered_set;

// class DisjointSetUnion
// {
// private:
//     unordered_map<int, int> size;
//     unordered_map<int, int> parent;

// public:
//     DisjointSetUnion(unordered_map<int, unordered_set<int>> adjList)
//     {
//         for (auto adjItem : adjList)
//         {
//             size[adjItem.first] = 1;
//             parent[adjItem.first] = adjItem.first;
//         }
//     }

//     int findParent(int node)
//     {
//         // base case
//         if (node == parent[node])
//         {
//             return node;
//         }

//         return parent[node] = findParent(parent[node]);
//     }

//     void unionBySize(int node1, int node2)
//     {
//         int rootNode1 = findParent(node1);
//         int rootNode2 = findParent(node2);

//         if (rootNode1 == rootNode2)
//         {
//             return;
//         }

//         // size of N1 < N2, then attach N1 to N2
//         if (size[rootNode1] < size[rootNode2])
//         {
//             parent[rootNode1] = rootNode2;
//             size[rootNode2] += size[rootNode1];
//         }
//         else if (size[rootNode1] >= size[rootNode2])
//         {
//             parent[rootNode2] = rootNode1;
//             size[rootNode1] += size[rootNode2];
//         }
//     }

//     bool isConnected(int node1, int node2)
//     {
//         int rootNode1 = findParent(node1);
//         int rootNode2 = findParent(node2);

//         if (rootNode1 == rootNode2)
//         {
//             return true;
//         }

//         return false;
//     }
// };

/*
            ############################################# Practice round 3 #############################################
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>

using std::cout;
using std::unordered_map;
using std::unordered_set;

class DisjointSetUnion
{
private:
    unordered_map<int, int> size;
    unordered_map<int, int> parent;

public:
    DisjointSetUnion(unordered_map<int, unordered_set<int>> adjList)
    {
        for (auto adjItem : adjList)
        {
            size[adjItem.first] = 1;
            parent[adjItem.first] = adjItem.first;
        }
    }

    int findParent(int node)
    {
        // base case
        if (node == parent[node])
        {
            return node;
        }

        // doing path compression alongside finding root
        return parent[node] = findParent(parent[node]);
    }

    void unionBySize(int node1, int node2)
    {
        int rootNode1 = findParent(node1);
        int rootNode2 = findParent(node2);

        // already part of the same component, no need to do union
        if (rootNode1 == rootNode2)
        {
            return;
        }

        // size n1 > n2, then attach n2 to n1
        if (size[rootNode1] >= size[rootNode2])
        {
            parent[rootNode2] = rootNode1;
            size[rootNode1] += size[rootNode2];
        }
        else
        {
            parent[rootNode1] = rootNode2;
            size[rootNode2] += size[rootNode1];
        }
    }

    bool isConnected(int node1, int node2)
    {
        int rootNode1 = findParent(node1);
        int rootNode2 = findParent(node2);

        if (rootNode1 == rootNode2)
        {
            return true;
        }

        return false;
    }
};

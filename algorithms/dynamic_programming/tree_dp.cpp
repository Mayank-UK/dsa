#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Adjacency list representation of the tree
int n;
vector<vector<int>> adj;
vector<int> weight;

// dp[u][0] = max weight sum for subtree u if u is NOT included
// dp[u][1] = max weight sum for subtree u if u IS included
vector<vector<int>> dp;

void dfs(int u, int parent) {
    // Initialize base states
    dp[u][0] = 0;              // If u is not included, its weight contributes 0
    dp[u][1] = weight[u - 1];  // If u is included, add its weight

    for (int v : adj[u]) {
        if (v == parent) continue; // Avoid going back to parent

        // Recurse down to children first (Post-order behavior)
        dfs(v, u);

        // Transition 1: If u is NOT included, its children can either be included or excluded
        dp[u][0] += max(dp[v][0], dp[v][1]);

        // Transition 2: If u IS included, its children MUST be excluded
        dp[u][1] += dp[v][0];
    }
}

int main() {
    n = 5;
    // 1-indexed weights for nodes 1 to 5
    weight = {10, 20, 30, 40, 50}; 
    
    adj.resize(n + 1);
    dp.assign(n + 1, vector<int>(2, 0));

    // Tree edges (undirected)
    // 1-2, 1-3, 2-4, 2-5
    adj[1].push_back(2); adj[2].push_back(1);
    adj[1].push_back(3); adj[3].push_back(1);
    adj[2].push_back(4); adj[4].push_back(2);
    adj[2].push_back(5); adj[5].push_back(2);

    // Run DFS starting from root (node 1)
    dfs(1, 0);

    // The answer is the maximum of including or excluding the root node
    int maxWeightSum = max(dp[1][0], dp[1][1]);
    cout << "Maximum Weight Independent Set Sum = " << maxWeightSum << "\n";

    return 0;
}
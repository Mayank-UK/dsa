#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Maximum-Weight Independent Set on a tree (re-rooted DFS DP).
// dp[u][0] = best sum for subtree u if u is EXCLUDED.
// dp[u][1] = best sum for subtree u if u is INCLUDED.
int n;
vector<vector<int>> adj;
vector<int> weight;
vector<vector<int>> dp;

void dfs(int u, int parent) {
    dp[u][0] = 0;             // u excluded -> contributes 0
    dp[u][1] = weight[u - 1]; // u included -> add its weight (1-indexed)

    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);

        // u excluded: each child may be included or not -> take the better.
        dp[u][0] += max(dp[v][0], dp[v][1]);
        // u included: children MUST be excluded.
        dp[u][1] += dp[v][0];
    }
}

int main() {
    cout << "=========== Tree DP (Max-Wt Indep. Set) ===========\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n)     one DFS\n";
    cout << "  Space : O(n)\n";
    cout << "  Note  : on a tree, MWIS is solvable in linear time\n\n";

    cout << "[Demo]\n";
    n = 5;
    weight = {10, 20, 30, 40, 50};  // 1-indexed: node 1..5
    adj.assign(n + 1, {});
    dp.assign(n + 1, vector<int>(2, 0));

    // Edges: 1-2, 1-3, 2-4, 2-5
    adj[1].push_back(2); adj[2].push_back(1);
    adj[1].push_back(3); adj[3].push_back(1);
    adj[2].push_back(4); adj[4].push_back(2);
    adj[2].push_back(5); adj[5].push_back(2);

    cout << "  weights: node 1..5 = ";
    for (int w : weight) cout << w << " ";
    cout << "\n  edges  : 1-2, 1-3, 2-4, 2-5\n";

    dfs(1, 0);
    int ans = max(dp[1][0], dp[1][1]);
    cout << "  -> Max weight independent set = " << ans
         << "  (e.g. nodes 1,4,5 = 10+40+50)\n\n";

    cout << "[Cases]\n";
    // A path graph 1-2-3 with weights 3,2,2 -> MWIS = max(3+2, 2) = 5
    {
        n = 3; weight = {3, 2, 2};
        adj.assign(n + 1, {}); dp.assign(n + 1, vector<int>(2, 0));
        adj[1].push_back(2); adj[2].push_back(1);
        adj[2].push_back(3); adj[3].push_back(2);
        dfs(1, 0);
        cout << "  path 1-2-3 (3,2,2) : " << max(dp[1][0], dp[1][1]) << "  (nodes 1,3)\n";
    }
    cout << "\n";

    cout << "[Edge Cases]\n";
    // Single node
    {
        n = 1; weight = {7};
        adj.assign(n + 1, {}); dp.assign(n + 1, vector<int>(2, 0));
        dfs(1, 0);
        cout << "  single node (7)    : " << max(dp[1][0], dp[1][1]) << "\n";
    }
    cout << "\n";

    return 0;
}

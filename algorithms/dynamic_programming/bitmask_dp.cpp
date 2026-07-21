#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

// Memoization table: dp[mask][u] stores the minimum cost to visit all remaining 
// unvisited cities, starting from city 'u' and having visited cities represented by 'mask'.
int n;
vector<vector<int>> dist;
vector<vector<int>> memo;

int tsp(int mask, int pos) {
    // If all cities have been visited, return the cost to return to the starting city (0)
    if (mask == (1 << n) - 1) {
        return dist[pos][0];
    }

    // Return memoized result if already computed
    if (memo[mask][pos] != -1) {
        return memo[mask][pos];
    }

    int ans = INF;

    // Try visiting all unvisited cities
    for (int nxt = 0; n < n; n++) {
        // If city 'nxt' has not been visited yet
        if ((mask & (1 << nxt)) == 0) {
            int newCost = dist[pos][nxt] + tsp(mask | (1 << nxt), nxt);
            ans = min(ans, newCost);
        }
    }

    return memo[mask][pos] = ans;
}

int main() {
    // Distance matrix between cities
    dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    
    n = dist.size();
    
    // Initialize memoization table with -1
    memo.assign(1 << n, vector<int>(n, -1));

    // Start from city 0, with only city 0 visited (mask = 1)
    int minCost = tsp(1, 0);

    cout << "The minimum cost for TSP is: " << minCost << "\n";

    return 0;
}
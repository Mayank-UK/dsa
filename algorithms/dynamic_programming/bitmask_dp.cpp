#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

// Held-Karp TSP via bitmask DP. Globals keep the recursion small for the demo.
// dp(mask, pos) = min cost to visit every remaining unvisited city and return
// to city 0, given the visited set `mask` and current city `pos`.
int n;
vector<vector<int>> dist;
vector<vector<int>> memo;

int tsp(int mask, int pos) {
    // All cities visited: close the tour by returning to city 0.
    if (mask == (1 << n) - 1) {
        return dist[pos][0];
    }

    if (memo[mask][pos] != -1) return memo[mask][pos];

    int ans = INF;
    for (int nxt = 0; nxt < n; nxt++) {            // was "n < n; n++" (dead loop)
        if ((mask & (1 << nxt)) == 0) {            // city nxt unvisited
            int newCost = dist[pos][nxt] + tsp(mask | (1 << nxt), nxt);
            ans = min(ans, newCost);
        }
    }
    return memo[mask][pos] = ans;
}

static int runTSP(const vector<vector<int>>& matrix) {
    dist = matrix;
    n = (int)dist.size();
    memo.assign(1 << n, vector<int>(n, -1));
    return tsp(1, 0);  // start at city 0, only city 0 visited
}

int main() {
    cout << "=========== Bitmask DP (TSP, Held-Karp) ===========\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(2^n * n^2)\n";
    cout << "  Space : O(2^n * n)\n";
    cout << "  Note  : exact TSP; feasible only for small n (<= ~20)\n\n";

    cout << "[Demo]\n";
    vector<vector<int>> matrix = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    cout << "  cities : " << matrix.size() << "\n";
    cout << "  -> Min tour cost = " << runTSP(matrix) << "  (0->1->3->2->0)\n\n";

    cout << "[Cases]\n";
    cout << "  2 cities : " << runTSP({{0, 5}, {5, 0}}) << "  (round trip)\n";
    cout << "  3 cities : " << runTSP({{0, 1, 2}, {1, 0, 3}, {2, 3, 0}}) << "\n";
    cout << "  4 cities : " << runTSP({{0, 10, 15, 20}, {10, 0, 35, 25},
                                      {15, 35, 0, 30}, {20, 25, 30, 0}}) << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  1 city   : " << runTSP({{0}}) << "  (stay in place)\n";
    cout << "\n";

    return 0;
}

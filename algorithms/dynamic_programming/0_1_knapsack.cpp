#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// 0/1 Knapsack (bottom-up). dp[i][w] = max value using the first i items
// under capacity w. Each item is taken at most once.
int knapsack01(int W, const vector<int>& weights, const vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                // Best of taking item i-1 or skipping it.
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]],
                               dp[i - 1][w]);
            } else {
                // Item too heavy for this capacity -> must skip.
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}

int main() {
    cout << "=================== 0/1 Knapsack ===================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n * W)\n";
    cout << "  Space : O(n * W)     (O(W) with the rolling-array variant)\n";
    cout << "  Note  : pseudo-polynomial in W; each item used 0 or 1 time\n\n";

    cout << "[Demo]\n";
    vector<int> values  = {60, 100, 120};
    vector<int> weights = {10, 20, 30};
    int W = 50;
    cout << "  values  : ";
    for (int v : values) cout << v << " ";
    cout << "\n  weights : ";
    for (int w : weights) cout << w << " ";
    cout << "\n  capacity: " << W << "\n";
    cout << "  -> Max value = " << knapsack01(W, weights, values, (int)values.size()) << "\n\n";

    cout << "[Cases]  (same items, varying capacity)\n";
    for (int cap : {0, 10, 25, 50, 100}) {
        cout << "  W=" << cap << " -> " << knapsack01(cap, weights, values, (int)values.size()) << "\n";
    }
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  empty items       : " << knapsack01(50, {}, {}, 0) << "\n";
    cout << "  zero capacity     : " << knapsack01(0, weights, values, (int)values.size()) << "\n";
    cout << "  one item, fits    : " << knapsack01(10, {10}, {60}, 1) << "\n";
    cout << "  one item, no fit  : " << knapsack01(5, {10}, {60}, 1) << "\n";
    cout << "\n";

    return 0;
}

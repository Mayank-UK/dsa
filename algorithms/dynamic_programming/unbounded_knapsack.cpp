#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Unbounded Knapsack (1D DP). dp[w] = max value attainable with capacity w.
// Items may be reused any number of times, so the transition looks at
// dp[w - weights[i]] in the SAME row.
int unboundedKnapsack(int W, const vector<int>& weights, const vector<int>& values, int n) {
    vector<int> dp(W + 1, 0);

    for (int w = 1; w <= W; w++) {
        for (int i = 0; i < n; i++) {
            if (weights[i] <= w) {
                dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
            }
        }
    }
    return dp[W];
}

int main() {
    cout << "=============== Unbounded Knapsack ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n * W)\n";
    cout << "  Space : O(W)\n";
    cout << "  Note  : items can be picked unlimited times (contrast 0/1)\n\n";

    cout << "[Demo]\n";
    vector<int> values  = {10, 40, 50, 70};
    vector<int> weights = {1, 3, 4, 5};
    int W = 8;
    cout << "  values  : ";
    for (int v : values) cout << v << " ";
    cout << "\n  weights : ";
    for (int w : weights) cout << w << " ";
    cout << "\n  capacity: " << W << "\n";
    cout << "  -> Max value = " << unboundedKnapsack(W, weights, values, (int)values.size()) << "\n\n";

    cout << "[Cases]  (same items, varying capacity)\n";
    for (int cap : {0, 3, 5, 8, 15}) {
        cout << "  W=" << cap << " -> " << unboundedKnapsack(cap, weights, values, (int)values.size()) << "\n";
    }
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  empty items       : " << unboundedKnapsack(50, {}, {}, 0) << "\n";
    cout << "  zero capacity     : " << unboundedKnapsack(0, weights, values, (int)values.size()) << "\n";
    cout << "  single item reused: " << unboundedKnapsack(7, {3}, {40}, 1) << "  (take weight-3 twice = 80)\n";
    cout << "\n";

    return 0;
}

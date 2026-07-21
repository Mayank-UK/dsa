#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the maximum value for an unbounded knapsack of capacity W
int unboundedKnapsack(int W, const vector<int>& weights, const vector<int>& values, int n) {
    // dp[w] stores the maximum value that can be attained with weight capacity w
    vector<int> dp(W + 1, 0);

    // Fill dp array from capacity 1 to W
    for (int w = 1; w <= W; w++) {
        for (int i = 0; i < n; i++) {
            if (weights[i] <= w) {
                // Since items can be picked multiple times, we look at dp[w - weights[i]]
                dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
            }
        }
    }

    return dp[W];
}

int main() {
    vector<int> values = {10, 40, 50, 70};
    vector<int> weights = {1, 3, 4, 5};
    int W = 8;
    int n = values.size();

    int maxVal = unboundedKnapsack(W, weights, values, n);
    cout << "Maximum value in Unbounded Knapsack = " << maxVal << "\n";

    return 0;
}
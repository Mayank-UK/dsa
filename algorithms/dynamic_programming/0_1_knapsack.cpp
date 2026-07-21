#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Returns the maximum value that can be put in a knapsack of capacity W
int knapsack01(int W, const vector<int>& weights, const vector<int>& values, int n) {
    // Create a 2D DP table where dp[i][w] stores the max value 
    // considering the first i items and a maximum weight w.
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Build the table bottom-up
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                // Max of including the item or excluding it
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                // Item exceeds current weight capacity, exclude it
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main() {
    vector<int> values = {60, 100, 120};
    vector<int> weights = {10, 20, 30};
    int W = 50;
    int n = values.size();

    int maxVal = knapsack01(W, weights, values, n);
    cout << "Maximum value in Knapsack = " << maxVal << "\n";

    return 0;
}
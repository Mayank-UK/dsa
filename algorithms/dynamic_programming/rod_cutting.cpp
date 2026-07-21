#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the maximum revenue obtainable by cutting up the rod
int cutRod(const vector<int>& prices, int n) {
    // dp[i] stores the maximum revenue for a rod of length i
    vector<int> dp(n + 1, 0);

    // Build the dp table bottom-up
    for (int i = 1; i <= n; i++) {
        int max_val = -1;
        for (int j = 1; j <= i; j++) {
            // price[j - 1] represents the price of a piece of length j
            max_val = max(max_val, prices[j - 1] + dp[i - j]);
        }
        dp[i] = max_val;
    }

    return dp[n];
}

int main() {
    // Prices for rod lengths 1 to 8
    vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20};
    int n = prices.size();

    int maxRevenue = cutRod(prices, n);
    cout << "Maximum Obtainable Value = " << maxRevenue << "\n";

    return 0;
}
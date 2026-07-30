#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Rod cutting: dp[i] = max revenue for a rod of length i. For each length i,
// try every first cut of size j and add the best of the remaining i-j.
int cutRod(const vector<int>& prices, int n) {
    vector<int> dp(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        int best = -1;
        for (int j = 1; j <= i; j++) {
            // prices[j-1] = price of a piece of length j.
            best = max(best, prices[j - 1] + dp[i - j]);
        }
        dp[i] = best;
    }
    return dp[n];
}

int main() {
    cout << "=================== Rod Cutting ===================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n^2)\n";
    cout << "  Space : O(n)\n";
    cout << "  Note  : maximize revenue; pieces may be reused (unbounded)\n\n";

    cout << "[Demo]\n";
    vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20};  // price[length-1], length 1..8
    int n = (int)prices.size();
    cout << "  prices (length 1.." << n << "): ";
    for (int p : prices) cout << p << " ";
    cout << "\n  rod length: " << n << "\n";
    cout << "  -> Max revenue = " << cutRod(prices, n) << "\n\n";

    cout << "[Cases]  (best revenue per rod length 1.." << n << ")\n";
    for (int len = 1; len <= n; len++) {
        cout << "  length " << len << " -> " << cutRod(prices, len) << "\n";
    }
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  length 0       : " << cutRod(prices, 0) << "\n";
    cout << "  length 1       : " << cutRod(prices, 1) << "\n";
    cout << "  single price   : " << cutRod({7}, 3) << "  (only length-1 piece known -> 21)\n";
    cout << "\n";

    return 0;
}

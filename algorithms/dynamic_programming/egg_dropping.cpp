#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to find the minimum number of attempts needed for k eggs and n floors
int superEggDrop(int k, int n) {
    // dp[i][j] represents min trials with i eggs and j floors
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

    // Base cases:
    // 0 floors need 0 drops, 1 floor needs 1 drop
    for (int i = 1; i <= k; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }

    // 1 egg needs j drops for j floors
    for (int j = 1; j <= n; j++) {
        dp[1][j] = j;
    }

    // Fill the rest of the table using bottom-up DP
    for (int i = 2; i <= k; i++) {
        for (int j = 2; j <= n; j++) {
            dp[i][j] = INT_MAX;
            // Linear search for the optimal floor to drop from (can be optimized with binary search)
            for (int x = 1; x <= j; x++) {
                int res = 1 + max(dp[i - 1][x - 1], dp[i][j - x]);
                dp[i][j] = min(dp[i][j], res);
            }
        }
    }

    return dp[k][n];
}

int main() {
    int k = 2; // Number of eggs
    int n = 10; // Number of floors

    int minAttempts = superEggDrop(k, n);
    cout << "Minimum number of trials in worst case = " << minAttempts << "\n";

    return 0;
}
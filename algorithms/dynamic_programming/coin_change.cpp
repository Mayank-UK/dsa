#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to find the minimum number of coins needed to make the target amount
int coinChange(const vector<int>& coins, int amount) {
    // Initialize DP table with amount + 1 (which acts as infinity)
    vector<int> dp(amount + 1, amount + 1);
    
    // Base case: 0 coins needed for amount 0
    dp[0] = 0;

    for (int i = 1; i <= amount; ++i) {
        for (int coin : coins) {
            if (i - coin >= 0) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    // If dp[amount] is still amount + 1, it means the amount cannot be made
    return (dp[amount] > amount) ? -1 : dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    int minCoins = coinChange(coins, amount);
    
    if (minCoins != -1) {
        cout << "Minimum coins required = " << minCoins << "\n";
    } else {
        cout << "It is not possible to make the target amount.\n";
    }

    return 0;
}
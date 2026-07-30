#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Minimum coins to make `amount` (unlimited supply of each coin).
// dp[i] = fewest coins summing to i; amount+1 acts as "infinity".
int coinChange(const vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);

    dp[0] = 0;  // zero coins to make amount 0

    for (int i = 1; i <= amount; ++i) {
        for (int coin : coins) {
            if (i - coin >= 0) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    // Unreachable amounts keep the sentinel value -> report -1.
    return (dp[amount] > amount) ? -1 : dp[amount];
}

int main() {
    cout << "=================== Coin Change ===================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(amount * |coins|)\n";
    cout << "  Space : O(amount)\n";
    cout << "  Note  : minimizes coin COUNT (unlimited supply of each)\n\n";

    cout << "[Demo]\n";
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    cout << "  coins  : ";
    for (int c : coins) cout << c << " ";
    cout << "\n  amount : " << amount << "\n";
    cout << "  -> Min coins = " << coinChange(coins, amount) << "\n\n";

    cout << "[Cases]  (same coins, varying amount)\n";
    for (int a : {0, 1, 3, 11, 30}) {
        int r = coinChange(coins, a);
        cout << "  amount=" << a << " -> " << (r == -1 ? "impossible" : to_string(r)) << "\n";
    }
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  amount 0            : " << coinChange({1, 2, 5}, 0) << "\n";
    cout << "  impossible (3, {2}) : " << coinChange({2}, 3) << "  (-1 = impossible)\n";
    cout << "  exact single coin   : " << coinChange({5}, 5) << "\n";
    cout << "  empty coin set      : " << coinChange({}, 7) << "  (-1)\n";
    cout << "\n";

    return 0;
}

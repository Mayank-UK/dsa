#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Egg drop: minimum number of drops needed in the WORST case to find the
// critical floor with k eggs and n floors. dp[i][j] = answer for i eggs,
// j floors. For a trial at floor x: if the egg breaks we have i-1 eggs and
// x-1 floors below; if it survives we have i eggs and j-x floors above.
// We must plan for the worse of the two (hence max) and minimize over x.
int superEggDrop(int k, int n) {
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

    // Base cases: 0 floors -> 0 drops; 1 floor -> 1 drop.
    for (int i = 1; i <= k; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }
    // With 1 egg we must test every floor bottom-up.
    for (int j = 1; j <= n; j++) dp[1][j] = j;

    for (int i = 2; i <= k; i++) {
        for (int j = 2; j <= n; j++) {
            dp[i][j] = INT_MAX;
            // Linear scan over the trial floor (binary search can speed this up).
            for (int x = 1; x <= j; x++) {
                int res = 1 + max(dp[i - 1][x - 1], dp[i][j - x]);
                dp[i][j] = min(dp[i][j], res);
            }
        }
    }
    return dp[k][n];
}

int main() {
    cout << "================== Egg Dropping ==================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(k * n^2)   (O(k*n log n) with the binary-search variant)\n";
    cout << "  Space : O(k * n)\n";
    cout << "  Note  : worst-case min drops to find the critical floor\n\n";

    cout << "[Demo]\n";
    int k = 2, n = 10;
    cout << "  eggs    : " << k << "\n";
    cout << "  floors  : " << n << "\n";
    cout << "  -> Min drops (worst case) = " << superEggDrop(k, n) << "\n\n";

    cout << "[Cases]  (2 eggs, varying floors)\n";
    for (int floors : {1, 6, 10, 36, 100}) {
        cout << "  n=" << floors << " -> " << superEggDrop(2, floors) << " drops\n";
    }
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  0 floors      : " << superEggDrop(2, 0) << "\n";
    cout << "  1 floor       : " << superEggDrop(2, 1) << "\n";
    cout << "  1 egg, n flrs : " << superEggDrop(1, 10) << "  (must test linearly)\n";
    cout << "  many eggs     : " << superEggDrop(10, 10) << "  (binary-search-like)\n";
    cout << "\n";

    return 0;
}

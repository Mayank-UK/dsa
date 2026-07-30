#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Subset sum (decision): is there a subset of arr that sums to targetSum?
// dp[i][j] = true if some subset of the first i items sums to j.
bool isSubsetSum(const vector<int>& arr, int targetSum) {
    int n = (int)arr.size();

    vector<vector<bool>> dp(n + 1, vector<bool>(targetSum + 1, false));

    // Sum 0 is always reachable (take nothing).
    for (int i = 0; i <= n; i++) dp[i][0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= targetSum; j++) {
            if (arr[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][targetSum];
}

static string yesNo(bool b) { return b ? "Yes" : "No"; }

int main() {
    cout << "=================== Subset Sum ===================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n * targetSum)\n";
    cout << "  Space : O(n * targetSum)     (O(targetSum) with 1D DP)\n";
    cout << "  Note  : decision problem (Yes/No); pseudo-polynomial\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {3, 34, 4, 12, 5, 2};
    int targetSum = 9;
    cout << "  arr    : ";
    for (int x : arr) cout << x << " ";
    cout << "\n  target : " << targetSum << "\n";
    cout << "  -> Subset exists? " << yesNo(isSubsetSum(arr, targetSum)) << "  (4+5)\n\n";

    cout << "[Cases]\n";
    cout << "  target 0  -> " << yesNo(isSubsetSum(arr, 0)) << "   (empty subset)\n";
    cout << "  target 9  -> " << yesNo(isSubsetSum(arr, 9)) << "   (4+5)\n";
    cout << "  target 40 -> " << yesNo(isSubsetSum(arr, 40)) << "  (34+4+2)\n";
    cout << "  target 49 -> " << yesNo(isSubsetSum(arr, 49)) << "  (34+12+3)\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  empty arr, target 0 : " << yesNo(isSubsetSum({}, 0)) << "\n";
    cout << "  empty arr, target 5 : " << yesNo(isSubsetSum({}, 5)) << "\n";
    cout << "  single == target    : " << yesNo(isSubsetSum({9}, 9)) << "\n";
    cout << "  single != target    : " << yesNo(isSubsetSum({9}, 8)) << "\n";
    cout << "\n";

    return 0;
}

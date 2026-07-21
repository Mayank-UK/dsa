#include <iostream>
#include <vector>

using namespace std;

// Function to check if there is a subset with the given sum
bool isSubsetSum(const vector<int>& arr, int targetSum) {
    int n = arr.size();

    // Create a 2D boolean dp table
    vector<vector<bool>> dp(n + 1, vector<bool>(targetSum + 1, false));

    // If sum is 0, answer is true (empty subset)
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    // Fill the dp table bottom-up
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

int main() {
    vector<int> arr = {3, 34, 4, 12, 5, 2};
    int targetSum = 9;

    if (isSubsetSum(arr, targetSum)) {
        cout << "Found a subset with the given sum.\n";
    } else {
        cout << "No subset with the given sum exists.\n";
    }

    return 0;
}
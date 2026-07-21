#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the length of the Longest Common Subsequence
int longestCommonSubsequence(const string& text1, const string& text2) {
    int m = text1.length();
    int n = text2.length();

    // Create a 2D DP table with dimensions (m + 1) x (n + 1) initialized to 0
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Build the DP table bottom-up
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}

int main() {
    string text1 = "ABCBDAB";
    string text2 = "BDCABA";

    int lcsLength = longestCommonSubsequence(text1, text2);
    cout << "Length of Longest Common Subsequence = " << lcsLength << "\n";

    return 0;
}
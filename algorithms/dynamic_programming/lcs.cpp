#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Longest Common Subsequence (length only). dp[i][j] = LCS length of
// text1[0..i-1] and text2[0..j-1].
int longestCommonSubsequence(const string& text1, const string& text2) {
    int m = (int)text1.length();
    int n = (int)text2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

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
    cout << "============ Longest Common Subsequence ============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(m * n)\n";
    cout << "  Space : O(m * n)     (O(min(m,n)) with the rolling variant)\n";
    cout << "  Note  : subsequence need NOT be contiguous\n\n";

    cout << "[Demo]\n";
    string text1 = "ABCBDAB";
    string text2 = "BDCABA";
    cout << "  text1 : " << text1 << "\n";
    cout << "  text2 : " << text2 << "\n";
    cout << "  -> LCS length = " << longestCommonSubsequence(text1, text2) << "  (e.g. BCBA / BDAB)\n\n";

    cout << "[Cases]\n";
    cout << "  identical       : " << longestCommonSubsequence("ABC", "ABC") << "\n";
    cout << "  disjoint        : " << longestCommonSubsequence("ABC", "XYZ") << "\n";
    cout << "  prefix vs full  : " << longestCommonSubsequence("ACE", "ABCDE") << "\n";
    cout << "  one is substring: " << longestCommonSubsequence("AB", "XABY") << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  both empty      : " << longestCommonSubsequence("", "") << "\n";
    cout << "  one empty       : " << longestCommonSubsequence("ABC", "") << "\n";
    cout << "  single chars    : " << longestCommonSubsequence("A", "A") << " / "
         << longestCommonSubsequence("A", "B") << "\n";
    cout << "\n";

    return 0;
}

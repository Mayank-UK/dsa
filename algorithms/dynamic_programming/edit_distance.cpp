#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Levenshtein edit distance: min insertions/deletions/substitutions to turn
// str1 into str2. dp[i][j] = distance between str1[0..i-1] and str2[0..j-1].
int editDistance(const string& str1, const string& str2) {
    int m = (int)str1.length();
    int n = (int)str2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;                      // insert all of str2
            } else if (j == 0) {
                dp[i][j] = i;                      // delete all of str1
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];       // chars match, free
            } else {
                dp[i][j] = 1 + min({
                    dp[i - 1][j],                  // delete
                    dp[i][j - 1],                  // insert
                    dp[i - 1][j - 1]               // substitute
                });
            }
        }
    }
    return dp[m][n];
}

int main() {
    cout << "=================== Edit Distance ===================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(m * n)\n";
    cout << "  Space : O(m * n)     (O(min(m,n)) with the rolling variant)\n";
    cout << "  Note  : Levenshtein — insert / delete / substitute each cost 1\n\n";

    cout << "[Demo]\n";
    string s1 = "kitten";
    string s2 = "sitting";
    cout << "  str1 : " << s1 << "\n";
    cout << "  str2 : " << s2 << "\n";
    cout << "  -> Edit distance = " << editDistance(s1, s2) << "  (k->s, e->i, +g)\n\n";

    cout << "[Cases]\n";
    cout << "  identical   : " << editDistance("abc", "abc") << "\n";
    cout << "  one extra   : " << editDistance("abc", "abcd") << "\n";
    cout << "  anagram-ish : " << editDistance("flaw", "lawn") << "\n";
    cout << "  full replace: " << editDistance("abc", "xyz") << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  both empty : " << editDistance("", "") << "\n";
    cout << "  one empty  : " << editDistance("abc", "") << " / " << editDistance("", "abc") << "\n";
    cout << "  single char: " << editDistance("a", "b") << " / " << editDistance("a", "a") << "\n";
    cout << "\n";

    return 0;
}

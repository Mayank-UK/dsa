#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to compute the edit distance between two strings
int editDistance(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();

    // Create a 2D DP table with dimensions (m + 1) x (n + 1)
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Initialize base cases
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // If first string is empty, insert all characters of second string
            if (i == 0) {
                dp[i][j] = j;
            }
            // If second string is empty, remove all characters of first string
            else if (j == 0) {
                dp[i][j] = i;
            }
            // If characters match, no operation is needed
            else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            // If characters don't match, consider all options and take minimum
            else {
                dp[i][j] = 1 + min({
                    dp[i - 1][j],    // Deletion
                    dp[i][j - 1],    // Insertion
                    dp[i - 1][j - 1] // Substitution
                });
            }
        }
    }

    return dp[m][n];
}

int main() {
    string str1 = "kitten";
    string str2 = "sitting";

    int distance = editDistance(str1, str2);
    cout << "The edit distance between \"" << str1 << "\" and \"" << str2 << "\" is: " << distance << "\n";

    return 0;
}
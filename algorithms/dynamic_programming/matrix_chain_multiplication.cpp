#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to find the most efficient multiplication order
int matrixChainOrder(const vector<int>& p) {
    int n = p.size() - 1; // Number of matrices

    // dp[i][j] stores the minimum number of scalar multiplications needed 
    // to compute the matrix A[i]...A[j]
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // l is chain length
    for (int l = 2; l <= n; l++) {
        for (int i = 0; i < n - l + 1; i++) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++) {
                // cost = cost of multiplying left subchain + cost of right subchain + cost of multiplying their results
                int q = dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < dp[i][j]) {
                    dp[i][j] = q;
                }
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    // Dimensions of matrices: A1(10x30), A2(30x5), A3(5x60)
    vector<int> p = {10, 30, 5, 60};

    int minOperations = matrixChainOrder(p);
    cout << "Minimum number of multiplications is = " << minOperations << "\n";

    return 0;
}
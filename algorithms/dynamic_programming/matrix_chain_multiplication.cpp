#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Matrix Chain Order: min scalar multiplications to multiply the chain
// A[0..n-1] with dimensions p (A[i] is p[i] x p[i+1]). dp[i][j] = min cost
// to multiply A[i..j]; try every split point k between them.
int matrixChainOrder(const vector<int>& p) {
    int n = (int)p.size() - 1;  // number of matrices

    vector<vector<int>> dp(n, vector<int>(n, 0));

    // l = chain length being considered.
    for (int l = 2; l <= n; l++) {
        for (int i = 0; i < n - l + 1; i++) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++) {
                // left cost + right cost + cost to multiply the two results.
                int q = dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < dp[i][j]) dp[i][j] = q;
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    cout << "============ Matrix Chain Multiplication ============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n^3)\n";
    cout << "  Space : O(n^2)\n";
    cout << "  Note  : n = number of matrices; finds min scalar multiplications\n\n";

    cout << "[Demo]\n";
    vector<int> p = {10, 30, 5, 60};  // A1:10x30, A2:30x5, A3:5x60
    cout << "  dims : ";
    for (int x : p) cout << x << " ";
    cout << " -> " << (int)p.size() - 1 << " matrices\n";
    cout << "  -> Min multiplications = " << matrixChainOrder(p) << "\n\n";

    cout << "[Cases]\n";
    cout << "  {40,20,30,10,30} : " << matrixChainOrder({40, 20, 30, 10, 30}) << "\n";
    cout << "  {10,20,30,40,30} : " << matrixChainOrder({10, 20, 30, 40, 30}) << "\n";
    cout << "  {1,2,3,4}        : " << matrixChainOrder({1, 2, 3, 4}) << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  one matrix {10,20} : " << matrixChainOrder({10, 20}) << "  (no multiplication)\n";
    cout << "  two matrices       : " << matrixChainOrder({10, 30, 5}) << "  (10*30*5)\n";
    cout << "\n";

    return 0;
}

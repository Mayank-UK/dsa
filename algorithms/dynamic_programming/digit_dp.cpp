#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

// Digit DP: count numbers in [0, n] whose decimal digit sum == targetSum.
// state = (idx, sum_left, tight). `tight` means the prefix so far equals n's
// prefix, so the next digit is capped by the corresponding digit of n.
string s;
long long memo[20][180][2];  // [index][sum_left][tight]

long long countValid(int idx, int sum_left, bool tight) {
    if (idx == (int)s.length()) {
        return (sum_left == 0) ? 1 : 0;  // exact sum matched
    }
    if (sum_left < 0) return 0;

    // Only memoize the non-tight states (tight states depend on the prefix).
    if (!tight && memo[idx][sum_left][tight] != -1) {
        return memo[idx][sum_left][tight];
    }

    long long total = 0;
    int limit = tight ? (s[idx] - '0') : 9;

    for (int dig = 0; dig <= limit; ++dig) {
        bool next_tight = tight && (dig == limit);
        total += countValid(idx + 1, sum_left - dig, next_tight);
    }

    if (!tight) memo[idx][sum_left][tight] = total;
    return total;
}

// Count of x in [0, n] with digit sum == targetSum.
long long solve(long long n, int target_sum) {
    if (n < 0) return 0;
    s = to_string(n);
    memset(memo, -1, sizeof(memo));
    return countValid(0, target_sum, true);
}

int main() {
    cout << "=================== Digit DP ===================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(digits * targetSum * 2 * 10)\n";
    cout << "  Space : O(digits * targetSum * 2)\n";
    cout << "  Note  : counts numbers in [0, n] with a given digit sum\n\n";

    cout << "[Demo]\n";
    long long n = 50;
    int target_sum = 5;
    cout << "  range       : [0, " << n << "]\n";
    cout << "  target sum  : " << target_sum << "\n";
    cout << "  -> Count = " << solve(n, target_sum)
         << "  (5,14,23,32,41,50)\n\n";

    cout << "[Cases]\n";
    cout << "  [0,100]  sum=5  : " << solve(100, 5) << "\n";
    cout << "  [0,100]  sum=10 : " << solve(100, 10) << "\n";
    cout << "  [0,1000] sum=1  : " << solve(1000, 1) << "  (1,10,100,1000)\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  n=0, sum=0      : " << solve(0, 0) << "  (the number 0)\n";
    cout << "  n=0, sum=5      : " << solve(0, 5) << "\n";
    cout << "  sum unreachable : " << solve(50, 100) << "\n";
    cout << "\n";

    return 0;
}

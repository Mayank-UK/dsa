#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

string s;
long long memo[20][180][2]; // [index][sum][tight]

// Recursive function for Digit DP
long long countValid(int idx, int sum_left, bool tight) {
    // Base case: if we have processed all digits
    if (idx == s.length()) {
        return (sum_left == 0) ? 1 : 0;
    }

    if (sum_left < 0) return 0;

    // Return memoized result if available (only when not tight)
    if (!tight && memo[idx][sum_left][tight] != -1) {
        return memo[idx][sum_left][tight];
    }

    long long total_ways = 0;
    // Determine the upper limit for the current digit
    int limit = tight ? (s[idx] - '0') : 9;

    for (int dig = 0; dig <= limit; ++dig) {
        bool next_tight = tight && (dig == limit);
        total_ways += countValid(idx + 1, sum_left - dig, next_tight);
    }

    // Save to memoization table if not tight
    if (!tight) {
        memo[idx][sum_left][tight] = total_ways;
    }

    return total_ways;
}

long long solve(long long n, int target_sum) {
    if (n < 0) return 0;
    s = to_string(n);
    memset(memo, -1, sizeof(memo));
    return countValid(0, target_sum, true);
}

int main() {
    long long n = 50;
    int target_sum = 5;

    long long result = solve(n, target_sum);
    cout << "Count of numbers from 0 to " << n << " with digit sum equal to " << target_sum << " is: " << result << "\n";

    return 0;
}
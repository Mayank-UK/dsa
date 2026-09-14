#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ─── Dynamic programming, mechanism only ───
// f(n) = f(n-1) + f(n-2), f(0)=0, f(1)=1. The same relation shown four ways:
// watch the repeated subproblems appear, then disappear once answers are stored.

static string showMemo(const vector<int>& memo) {
    string s;
    for (size_t i = 0; i < memo.size(); i++) {
        s += (memo[i] == -1) ? "-" : to_string(memo[i]);
        if (i + 1 < memo.size()) s += " ";
    }
    return s;
}

// (a) naive recursion — every call re-derives everything below it
static int naive(vector<int>& calls, int n, int depth) {
    calls[n]++;
    string again = (calls[n] > 1) ? "  <- computed AGAIN (call #" + to_string(calls[n]) + ")" : "";
    cout << string(depth * 2, ' ') << "f(" << n << ")" << again << "\n";
    if (n <= 1) return n;
    return naive(calls, n - 1, depth + 1) + naive(calls, n - 2, depth + 1);
}

// (b) memoized recursion — each subproblem computed once, then reused
static int memoized(vector<int>& memo, int n, int depth) {
    if (n <= 1) {
        cout << string(depth * 2, ' ') << "f(" << n << "): base -> " << n << "\n";
        return n;
    }
    if (memo[n] != -1) {
        cout << string(depth * 2, ' ') << "f(" << n << "): HIT -> reuse memo[" << n << "] = " << memo[n] << "\n";
        return memo[n];
    }
    cout << string(depth * 2, ' ') << "f(" << n << "): miss -> compute\n";
    memo[n] = memoized(memo, n - 1, depth + 1) + memoized(memo, n - 2, depth + 1);
    cout << string(depth * 2, ' ') << "stored memo[" << n << "] = " << memo[n]
         << "   memo = [" << showMemo(memo) << "]\n";
    return memo[n];
}

int main() {
    cout << "=============== DP Fundamentals — store once, reuse ===============\n\n";

    cout << "[Data]\n";
    cout << "  f(0)=0  f(1)=1  f(n)=f(n-1)+f(n-2)   — watching f(5)\n\n";

    cout << "[1] Naive recursion: subproblems repeat\n";
    vector<int> calls(6, 0);
    int r1 = naive(calls, 5, 0);
    cout << "  result: f(5) = " << r1
         << "   (15 calls for only 6 distinct subproblems)\n\n";

    cout << "[2] Memoization: fill the table as answers land\n";
    vector<int> memo(6, -1);
    int r2 = memoized(memo, 5, 0);
    cout << "  result: f(5) = " << r2
         << "   (every HIT is a subtree never walked)\n\n";

    cout << "[3] Tabulation: fill left to right, reuse earlier cells\n";
    vector<int> dp = {0, 1};
    dp.resize(6);
    cout << "  dp[0] = 0 (base)\n  dp[1] = 1 (base)\n";
    for (int i = 2; i <= 5; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
        cout << "  dp[" << i << "] = dp[" << i - 1 << "] + dp[" << i - 2 << "] = "
             << dp[i - 1] << " + " << dp[i - 2] << " = " << dp[i] << "\n";
    }
    cout << "  table = [" << dp[0];
    for (int i = 1; i <= 5; i++) cout << " " << dp[i];
    cout << "]\n\n";

    cout << "[4] Rolling variables: keep only the two reused cells\n";
    int a = 0, b = 1;                       // f(0), f(1)
    for (int n = 2; n <= 5; n++) {
        int next = a + b;
        cout << "  f(" << n << ") = " << a << " + " << b << " = " << next
             << "   keep {" << b << ", " << next << "}, drop f(" << n - 2 << ")\n";
        a = b;
        b = next;
    }

    cout << "\n[Note] Repeated subproblems -> store -> reuse; that is the whole trick.\n";
    return 0;
}

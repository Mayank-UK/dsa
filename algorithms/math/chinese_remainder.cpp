#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Chinese Remainder Theorem (CRT). Given pairwise-coprime moduli n[i] and
// remainders r[i], finds the unique X (mod product) with X ≡ r[i] (mod n[i]).
// Formula: X = Σ r[i] * (P/n[i]) * inv(P/n[i] mod n[i]),  where P = Π n[i].
// (For non-coprime moduli the general algorithm merges congruences pairwise;
//  this implementation assumes the coprime case, the standard CRT form.)

static long long extGCD(long long a, long long b, long long& x, long long& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long x1, y1;
    long long g = extGCD(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1;
    return g;
}

// Modular inverse of a mod m (assumes gcd(a,m)=1).
static long long modInverse(long long a, long long m) {
    long long x, y;
    extGCD((a % m + m) % m, m, x, y);
    return (x % m + m) % m;
}

// Returns the smallest nonnegative X satisfying all congruences, or -1 on
// inconsistent input. Assumes moduli are pairwise coprime.
long long solveCRT(const vector<int>& moduli, const vector<int>& remainders) {
    int k = (int)moduli.size();
    long long P = 1;
    for (int i = 0; i < k; ++i) P *= moduli[i];

    long long X = 0;
    for (int i = 0; i < k; ++i) {
        long long pp = P / moduli[i];
        long long inv = modInverse(pp % moduli[i], moduli[i]);   // (P/n[i])^-1 mod n[i]
        X += (long long)remainders[i] * inv % moduli[i] * pp;     // accumulate the term
        X %= P;
    }
    return X;
}

// Check that X actually satisfies every congruence — the demo's truth source.
static bool verify(const vector<int>& moduli, const vector<int>& remainders, long long X) {
    for (int i = 0; i < (int)moduli.size(); ++i)
        if (X % moduli[i] != remainders[i]) return false;
    return true;
}

static void runCase(const string& label, const vector<int>& moduli, const vector<int>& rem) {
    long long X = solveCRT(moduli, rem);
    long long P = 1; for (int m : moduli) P *= m;
    cout << "  " << label << "  X mod " << P << " = " << X
         << "   (satisfies all : " << (verify(moduli, rem, X) ? "Yes" : "No") << ")\n";
}

int main() {
    cout << "==================== Chinese Remainder Theorem ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time   : O(k * log P)   k congruences, each needs one modular inverse\n";
    cout << "  Space  : O(k)\n";
    cout << "  Notes  : requires pairwise-coprime moduli; solution is unique mod P.\n\n";

    cout << "[Demo]\n";
    vector<int> moduli = {3, 4, 5};
    vector<int> rem    = {2, 3, 1};
    long long X = solveCRT(moduli, rem);
    cout << "  congruences: X%3=2, X%4=3, X%5=1\n";
    cout << "  X = " << X << "   (satisfies all : " << (verify(moduli, rem, X) ? "Yes" : "No") << ")\n\n";

    cout << "[Edge Cases]\n";
    runCase("single congruence", {7}, {4});
    runCase("two moduli      ", {5, 7}, {1, 3});
    runCase("classic sun-tzu ", {3, 5, 7}, {2, 3, 2});   // → 23

    return 0;
}

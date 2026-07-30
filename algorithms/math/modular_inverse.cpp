#include <iostream>

using namespace std;

// Two ways to compute the modular inverse of a mod m (defined iff gcd(a,m)=1):
//   (1) Fermat's little theorem: a^(-1) ≡ a^(m-2) mod m   — REQUIRES m prime.
//   (2) Extended Euclidean: solve a*x + m*y = 1, then x mod m — works for ANY m
//       as long as gcd(a,m)=1. Returns -1 when no inverse exists.

static long long modPow(long long base, long long exp, long long mod) {
    long long res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return res;
}

static long long extGCD(long long a, long long b, long long& x, long long& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long x1, y1;
    long long g = extGCD(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1;
    return g;
}

// Fermat: inverse of a mod m, valid only when m is prime and gcd(a,m)=1.
long long modInverseFermat(long long a, long long m) {
    return modPow(a, m - 2, m);
}

// Extended-Euclid: inverse of a mod m for ANY m; returns -1 if none (gcd≠1).
long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = extGCD((a % m + m) % m, m, x, y);
    if (g != 1) return -1;                  // a and m not coprime → no inverse
    return (x % m + m) % m;
}

static void runInverse(const char* label, long long a, long long m) {
    long long inv = modInverse(a, m);
    cout << "  " << label << "  a=" << a << ", m=" << m << " -> ";
    if (inv == -1) { cout << "no inverse (gcd(a,m) != 1)\n"; return; }
    bool ok = (((__int128)a * inv) % m == 1);
    cout << "inverse = " << inv << "   (a*inv % m == 1 : " << (ok ? "Yes" : "No") << ")\n";
}

int main() {
    cout << "======================= Modular Inverse =======================\n\n";

    cout << "[Complexity]\n";
    cout << "  Fermat's : O(log m)        one modular exponentiation (m MUST be prime)\n";
    cout << "  Ext-Euclid: O(log m)       works for any m with gcd(a,m)=1\n";
    cout << "  Notes  : inverse exists iff gcd(a,m) == 1; verifies a*inv ≡ 1 (mod m).\n\n";

    cout << "[Demo] Fermat vs Extended-Euclid agree on a prime modulus:\n";
    long long a = 3, m = 11;
    cout << "  a=" << a << ", m=" << m << " (prime)\n";
    cout << "    Fermat      : " << modInverseFermat(a, m) << "\n";
    cout << "    Ext-Euclid  : " << modInverse(a, m) << "\n\n";

    cout << "[Edge Cases]\n";
    runInverse("inverse of 1   ", 1, 11);
    runInverse("non-prime mod  ", 3, 26);          // gcd(3,26)=1 → inverse exists
    runInverse("no inverse     ", 4, 8);           // gcd(4,8)=4 → none
    runInverse("larger coprime ", 10, 17);
    runInverse("a > m          ", 25, 7);

    return 0;
}

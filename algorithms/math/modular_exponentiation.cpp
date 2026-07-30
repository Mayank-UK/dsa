#include <iostream>

using namespace std;

// Modular exponentiation by repeated squaring: (base^exp) mod m.
// Square-and-multiply: walk the exponent's bits; for each bit, square the base,
// and when the bit is 1 fold it into the result. O(log exp) multiplications.
// __int128 absorbs the intermediate product so a*b mod m is exact for 64-bit m.

long long modPow(long long base, long long exp, long long mod) {
    if (mod == 1) return 0;                 // everything is 0 mod 1
    long long res = 1;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = (__int128)res * base % mod;   // odd bit → multiply
        base = (__int128)base * base % mod;              // square
        exp >>= 1;
    }
    return res;
}

// Naive loop for cross-checking on small exponents only.
static long long modPowNaive(long long base, long long exp, long long mod) {
    long long r = 1 % mod;
    for (long long i = 0; i < exp; ++i) r = (__int128)r * base % mod;
    return r;
}

int main() {
    cout << "==================== Modular Exponentiation ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time   : O(log exp) multiplications\n";
    cout << "  Space  : O(1)\n";
    cout << "  Notes  : square-and-multiply; __int128 keeps a*b mod m exact for 64-bit m.\n\n";

    cout << "[Demo]\n";
    long long base = 3, exp = 200, mod = 10007;
    cout << "  (" << base << "^" << exp << ") % " << mod << " = " << modPow(base, exp, mod)
         << "   (naive check on small exp: "
         << (modPow(3, 13, mod) == modPowNaive(3, 13, mod) ? "match" : "MISMATCH") << ")\n\n";

    cout << "[Edge Cases]\n";
    cout << "  exp = 0          : 5^0 % 7 = " << modPow(5, 0, 7) << " (expect 1)\n";
    cout << "  base = 0         : 0^10 % 7 = " << modPow(0, 10, 7) << " (expect 0)\n";
    cout << "  mod = 1          : 9^9 % 1 = " << modPow(9, 9, 1) << " (expect 0)\n";
    cout << "  base >= mod      : 15^3 % 7 = " << modPow(15, 3, 7)
         << " (= 1^3 % 7 = " << modPow(1, 3, 7) << ")\n";
    cout << "  large exponent   : 2^62 % 1000000007 = " << modPow(2, 62, 1000000007LL) << "\n";
    cout << "  big modulus      : 7^256 % 1000000007 = " << modPow(7, 256, 1000000007LL) << "\n";

    return 0;
}

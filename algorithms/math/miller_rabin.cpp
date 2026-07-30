#include <iostream>

using namespace std;

// Miller-Rabin primality test. Write n-1 = 2^s * d (d odd). For a witness a,
// either a^d ≡ 1 (mod n), or some a^(d·2^r) ≡ -1 (mod n) for 0 ≤ r < s; if
// neither holds, n is composite. Testing the 12 bases below is DETERMINISTIC
// for all n < 3.3·10^24, so this is exact (not probabilistic) in practice.

static long long modPow(long long base, long long exp, long long mod) {
    long long res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return res;
}

// True if `a` is a witness for n's primality (i.e. passes the MR check).
static bool passesWitness(long long a, long long d, long long n) {
    long long x = modPow(a, d, n);
    if (x == 1 || x == n - 1) return true;
    while (d != n - 1) {                       // square up through the 2^s factors
        x = (__int128)x * x % n;
        d *= 2;
        if (x == n - 1) return true;
    }
    return false;
}

bool isPrime(long long n) {
    if (n < 2) return false;
    if (n < 4) return true;                    // 2, 3
    if (n % 2 == 0) return false;

    long long d = n - 1;                        // factor out powers of 2: n-1 = 2^s * d
    while (d % 2 == 0) d /= 2;

    static const long long bases[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (long long a : bases) {
        if (a >= n) continue;                   // skip bases not smaller than n
        if (!passesWitness(a, d, n)) return false;
    }
    return true;
}

static void runTest(const char* label, long long n) {
    cout << "  " << label << "  isPrime(" << n << ") = "
         << (isPrime(n) ? "prime" : "composite") << "\n";
}

int main() {
    cout << "======================= Miller-Rabin Primality =======================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time   : O(k * log n)     k=12 witnesses, each one modular exponentiation\n";
    cout << "  Space  : O(1)\n";
    cout << "  Notes  : deterministic for n < 3.3e24 with these 12 bases — not a guess.\n\n";

    cout << "[Demo]\n";
    runTest("10,000th prime", 104729);
    runTest("Mersenne M31  ", 2147483647LL);
    cout << "\n";

    cout << "[Edge Cases]\n";
    runTest("0 / 1         ", 1);
    runTest("smallest prime", 2);
    runTest("odd composite ", 9);
    runTest("even > 2      ", 1000);
    runTest("Carmichael 561", 561);               // composite but fools Fermat tests
    runTest("Carmichael 1105", 1105);
    runTest("product of big primes", 1000000007LL * 1000000009LL);   // composite
    runTest("big prime     ", 999999937LL);

    return 0;
}

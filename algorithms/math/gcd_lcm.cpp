#include <iostream>

using namespace std;

// GCD via the Euclidean algorithm: gcd(a, b) = gcd(b, a mod b), terminating at
// gcd(a, 0) = a. The remainder strictly decreases each step, so it always ends.

// Recursive form.
long long gcd(long long a, long long b) {
    while (b != 0) {                  // iterative tail call — no stack growth
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// LCM from GCD. Divide BEFORE multiplying so the intermediate cannot overflow a
// naive a*b/gcd (and a*b alone could overflow 64-bit for large inputs).
long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

static void runPair(const char* label, long long a, long long b) {
    long long g = gcd(a, b);
    long long l = lcm(a, b);
    cout << "  " << label << "  gcd(" << a << ", " << b << ") = " << g;
    cout << "   lcm = " << l;
    // lcm * gcd == |a * b| when both nonzero — a cheap sanity check.
    if (a != 0 && b != 0) {
        bool ok = (l * g == a * b);
        cout << "   (lcm*gcd == a*b : " << (ok ? "Yes" : "No") << ")";
    }
    cout << "\n";
}

int main() {
    cout << "============================ GCD & LCM ============================\n\n";

    cout << "[Complexity]\n";
    cout << "  GCD : O(log min(a,b))   Euclidean algorithm (Lamé's bound)\n";
    cout << "  LCM : O(log min(a,b))   one GCD call\n";
    cout << "  Notes: gcd(a,b)*lcm(a,b) == |a*b|; divide-first LCM avoids overflow.\n\n";

    cout << "[Demo]\n";
    runPair("typical   ", 54, 24);
    runPair("coprime   ", 17, 13);
    cout << "\n";

    cout << "[Edge Cases]\n";
    runPair("equal     ", 12, 12);
    runPair("one divides", 100, 25);
    runPair("with zero ", 0, 9);
    runPair("both zero ", 0, 0);
    runPair("primes    ", 97, 89);
    runPair("large     ", 1000000000LL, 999999937LL);

    return 0;
}

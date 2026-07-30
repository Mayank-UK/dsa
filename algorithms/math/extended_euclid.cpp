#include <iostream>

using namespace std;

// Extended Euclidean Algorithm. Runs the Euclidean algorithm and additionally
// produces Bézout coefficients (x, y) satisfying  a*x + b*y = gcd(a, b).
// This identity is the foundation of modular inverses and of CRT.

// Returns gcd(a, b); sets x, y so that a*x + b*y == gcd.
long long extendedGCD(long long a, long long b, long long& x, long long& y) {
    if (b == 0) { x = 1; y = 0; return a; }   // a*1 + 0*0 = a
    long long x1, y1;
    long long g = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;                      // unwind one level of the recursion
    return g;
}

static void runPair(const char* label, long long a, long long b) {
    long long x, y;
    long long g = extendedGCD(a, b, x, y);
    cout << "  " << label << "  gcd(" << a << ", " << b << ") = " << g
         << "   Bézout: x=" << x << ", y=" << y;
    // Verify the identity holds (overflow-safe via __int128).
    long long check = (long long)((__int128)a * x + (__int128)b * y);
    cout << "   (a*x+b*y = " << check << " == gcd : "
         << (check == g ? "Yes" : "No") << ")\n";
}

int main() {
    cout << "==================== Extended Euclidean Algorithm ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time   : O(log min(a,b))\n";
    cout << "  Space  : O(log min(a,b)) recursion\n";
    cout << "  Notes  : yields Bézout coefficients  a*x + b*y = gcd(a,b).\n\n";

    cout << "[Demo]\n";
    runPair("typical ", 30, 20);
    runPair("coprime ", 35, 15);
    cout << "\n";

    cout << "[Edge Cases]\n";
    runPair("a multiple of b", 100, 25);
    runPair("coprime primes  ", 17, 13);
    runPair("one is zero     ", 9, 0);
    runPair("with negatives  ", -30, 20);
    runPair("large coprime   ", 999999937LL, 1000000007LL);

    return 0;
}

#include <iostream>

using namespace std;

// Binary exponentiation (exponentiation by squaring). To compute base^exp, walk
// the bits of exp: square the base each step, and whenever the current bit is 1
// fold it into the result. Only O(log exp) multiplications instead of exp-1.
// The same idea underlies modular exponentiation — see math/modular_exponentiation.cpp
// (this file shows the un-modded form plus a plain-overflow guarded modular variant).

class FastMath {
public:
    // base^exp (exact, but overflows for large results — keep exp modest).
    static long long power(long long base, long long exp) {
        long long result = 1;
        while (exp > 0) {
            if (exp & 1) result *= base;   // odd bit → multiply
            base *= base;                   // square for the next bit
            exp >>= 1;
        }
        return result;
    }

    // (base^exp) % mod — uses __int128 so a*b mod m is exact for 64-bit m.
    static long long modularPower(long long base, long long exp, long long mod) {
        if (mod == 1) return 0;
        long long result = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) result = (__int128)result * base % mod;
            base = (__int128)base * base % mod;
            exp >>= 1;
        }
        return result;
    }
};

int main() {
    cout << "===================== Fast Exponentiation =====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(log exp) multiplications\n";
    cout << "  Space : O(1)\n";
    cout << "  Notes : square-and-multiply; the modular form (math/modular_exponentiation.cpp)\n";
    cout << "          is the same loop with % after every multiply to bound magnitude.\n\n";

    cout << "[Demo]\n";
    cout << "  3^13      = " << FastMath::power(3, 13) << "   (expect 1594323)\n";
    cout << "  2^10      = " << FastMath::power(2, 10) << "   (expect 1024)\n";
    cout << "  2^1000000000 % 1000000007 = " << FastMath::modularPower(2, 1000000000LL, 1000000007LL)
         << "\n\n";

    cout << "[Edge Cases]\n";
    cout << "  exp = 0   : 5^0 = " << FastMath::power(5, 0) << " (anything^0 = 1)\n";
    cout << "  base = 1  : 1^99 = " << FastMath::power(1, 99) << "\n";
    cout << "  base = 0  : 0^5 = " << FastMath::power(0, 5) << "\n";
    cout << "  mod = 1   : 7^9 % 1 = " << FastMath::modularPower(7, 9, 1) << " (always 0)\n";

    return 0;
}

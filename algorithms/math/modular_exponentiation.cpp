#include <iostream>

using namespace std;

// Function to compute (base^exp) % mod efficiently
long long modularExponentiation(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod; // Handle cases where base >= mod

    if (base == 0) return 0; // Edge case: base is 0

    while (exp > 0) {
        // If exp is odd, multiply base with result
        if (exp & 1) {
            res = (__int128)res * base % mod; // Use __int128 to prevent overflow during multiplication
        }

        // exp must be even now, square the base and halve the exponent
        base = (__int128)base * base % mod;
        exp >>= 1; // Divide by 2
    }

    return res;
}

int main() {
    long long base = 3;
    long long exp = 200;
    long long mod = 10007;

    long long result = modularExponentiation(base, exp, mod);

    cout << "(" << base << "^" << exp << ") % " << mod << " = " << result << "\n";

    return 0;
}
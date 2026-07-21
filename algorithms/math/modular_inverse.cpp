#include <iostream>

using namespace std;

// Binary exponentiation helper: (base^exp) % mod
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Function to find modular inverse using Fermat's Little Theorem (requires prime m)
long long modInverseFermat(long long a, long long m) {
    return power(a, m - 2, m);
}

int main() {
    long long a = 3, m = 11; // 11 is prime

    long long inverse = modInverseFermat(a, m);
    cout << "Modular inverse of " << a << " modulo " << m << " (Fermat's) is: " << inverse << "\n";

    return 0;
}
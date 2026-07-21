#include <iostream>

using namespace std;

// Function to calculate (base^exp) % mod using modular exponentiation
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp /= 2;
    }
    return res;
}

// Miller-Rabin primality test for a single base 'a'
bool millerTest(long long d, long long n, long long a) {
    long long x = power(a, d, n);
    if (x == 1 || x == n - 1)
        return true;

    // Square x while d does not reach n - 1
    while (d != n - 1) {
        x = (__int128)x * x % n;
        d *= 2;

        if (x == n - 1) return true;
    }
    return false;
}

// Main Miller-Rabin function with multiple rounds (k iterations)
bool isPrime(long long n, int k = 5) {
    // Corner cases
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    // Find d such that n-1 = 2^s * d
    long long d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // Check against k random bases (using deterministic small bases for deterministic guarantees up to 2^64 if needed)
    // Here we use standard small test bases for demonstration
    long long bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int i = 0; i < k && i < 12; i++) {
        if (n <= bases[i]) break;
        if (!millerTest(d, n, bases[i]))
            return false;
    }

    return true;
}

int main() {
    long long n = 104729; // 10,472th prime number

    if (isPrime(n)) {
        cout << n << " is probably prime.\n";
    } else {
        cout << n << " is composite.\n";
    }

    return 0;
}
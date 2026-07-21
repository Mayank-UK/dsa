#include <iostream>

using namespace std;

// Recursive implementation of the Euclidean algorithm for GCD
long long gcd(long long a, long long b) {
    // Base case: if b is 0, the gcd is a
    if (b == 0) {
        return a;
    }
    // Recursive step: gcd(b, remainder of a divided by b)
    return gcd(b, a % b);
}

// Function to find the Least Common Multiple (LCM) using GCD
long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b; // Divide first to avoid integer overflow
}

int main() {
    long long a = 54, b = 24;

    cout << "GCD(" << a << ", " << b << ") = " << gcd(a, b) << "\n";
    cout << "LCM(" << a << ", " << b << ") = " << lcm(a, b) << "\n";

    return 0;
}
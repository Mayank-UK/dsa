#include <iostream>

using namespace std;

// Extended Euclidean Algorithm function
// Returns gcd(a, b) and updates x and y such that ax + by = gcd(a, b)
long long extendedGCD(long long a, long long b, long long& x, long long& y) {
    // Base Case: if b is 0, gcd is a, and ax + 0y = a implies x = 1, y = 0
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;
    long long gcd = extendedGCD(b, a % b, x1, y1);

    // Update x and y using results from the recursive step
    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

int main() {
    long long a = 30, b = 20;
    long long x, y;

    long long gcd = extendedGCD(a, b, x, y);

    cout << "GCD(" << a << ", " << b << ") = " << gcd << "\n";
    cout << "Bézout coefficients: x = " << x << ", y = " << y << "\n";
    cout << "Verification: " << a << "*(" << x << ") + " << b << "*(" << y << ") = " << (a * x + b * y) << "\n";

    return 0;
}
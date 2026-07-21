#include <iostream>
#include <vector>

using namespace std;

// Extended Euclidean Algorithm to find modular inverse
// Solves ax + by = gcd(a, b) and returns gcd(a, b)
int extendedGCD(int a, int b, int& x, int& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    
    int x1, y1;
    int gcd = extendedGCD(b % a, a, x1, y1);
    
    // Update x and y using results of recursive call
    x = y1 - (b / a) * x1;
    y = x1;
    
    return gcd;
}

// Function to find the modulo inverse of 'A' with respect to 'M'
int modInverse(int A, int M) {
    int x, y;
    extendedGCD(A, M, x, y);
    
    // Handle negative x by adding M
    return (x % M + M) % M;
}

// Function to find the smallest x satisfying the system of congruences
long long findMinX(const vector<int>& num, const vector<int>& rem) {
    int k = num.size();
    long long prod = 1;
    
    // Step 1: Calculate the product of all moduli
    for (int i = 0; i < k; i++) {
        prod *= num[i];
    }
    
    long long result = 0;
    
    // Step 2-4: Apply the CRT formula
    for (int i = 0; i < k; i++) {
        long long pp = prod / num[i];
        
        // Find modular inverse of pp (modulo num[i])
        // We pass (pp % num[i]) to prevent integer overflow in extendedGCD
        long long inv = modInverse(pp % num[i], num[i]);
        
        result += rem[i] * inv * pp;
    }
    
    // Return the smallest valid positive integer
    return result % prod;
}

int main() {
    // Example: 
    // x = 2 (mod 3)
    // x = 3 (mod 4)
    // x = 1 (mod 5)
    vector<int> num = {3, 4, 5};
    vector<int> rem = {2, 3, 1};

    cout << "Smallest x satisfying the congruences is: " << findMinX(num, rem) << "\n";

    return 0;
}
#include <iostream>

using namespace std;

class FastMath {
public:
    // Standard Binary Exponentiation
    // Computes base^exp in O(log N) time
    long long power(long long base, long long exp) {
        long long result = 1;
        
        while (exp > 0) {
            // If the current lowest bit of the exponent is 1 (odd)
            // Multiply the current base value into our result
            if (exp & 1) { 
                result *= base;
            }
            
            // Square the base for the next bit position
            base *= base;
            
            // Shift the exponent right by 1 (equivalent to exp / 2)
            exp >>= 1; 
        }
        
        return result;
    }

    // Modular Exponentiation
    // Computes (base^exp) % mod to prevent overflow
    long long modularPower(long long base, long long exp, long long mod) {
        long long result = 1;
        
        // Handle cases where the initial base is larger than the mod
        base = base % mod; 
        
        while (exp > 0) {
            // If exp is odd, multiply and immediately take modulo
            if (exp & 1) {
                result = (result * base) % mod;
            }
            
            // Square the base and take modulo
            base = (base * base) % mod;
            
            exp >>= 1;
        }
        
        return result;
    }
};

int main() {
    FastMath math;

    cout << "--- Standard Fast Exponentiation ---\n";
    long long b1 = 3, e1 = 13;
    cout << b1 << "^" << e1 << " = " << math.power(b1, e1) << "\n\n";

    cout << "--- Modular Exponentiation ---\n";
    // In competitive programming, 10^9 + 7 is a standard large prime modulo
    long long b2 = 2, e2 = 1000000000; // 2^1 billion
    long long mod = 1000000007; 
    
    cout << b2 << "^" << e2 << " % " << mod << " = " 
         << math.modularPower(b2, e2, mod) << "\n";
    cout << "------------------------------------\n";

    return 0;
}
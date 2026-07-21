#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

class PowerOfTwo {
public:
    // Approach 1: Bitwise AND (The most optimal approach)
    // Uses the property that x & (x - 1) clears the lowest set bit.
    // If a number is a power of 2, it only has ONE set bit, so clearing it results in 0.
    bool isPowerOfTwoBitwise(long long n) {
        // n > 0 is crucial because 0 and negative numbers are not powers of 2
        return (n > 0) && ((n & (n - 1)) == 0);
    }

    // Approach 2: Popcount (Using built-in compiler functions)
    // A power of two must have exactly 1 set bit.
    bool isPowerOfTwoPopcount(long long n) {
        if (n <= 0) return false;
        return __builtin_popcountll(n) == 1;
    }

    // Approach 3: Iterative Division
    // The standard mathematical way without bit manipulation.
    bool isPowerOfTwoIterative(long long n) {
        if (n <= 0) return false;
        while (n % 2 == 0) {
            n /= 2;
        }
        return n == 1;
    }
};

int main() {
    PowerOfTwo checker;
    
    // Test cases covering standard powers, non-powers, and edge cases (0, negatives)
    vector<long long> test_cases = {0, 1, 2, 8, 14, 1024, -8};

    cout << "--- Power of Two Checker ---\n";
    for (long long n : test_cases) {
        // Display the binary string for positive numbers up to 16 bits for visual proof
        string binaryStr = "N/A (Negative or Zero)";
        if (n > 0 && n <= 65535) {
            binaryStr = bitset<16>(n).to_string();
            binaryStr.erase(0, binaryStr.find_first_not_of('0')); // Strip leading zeros
            if (binaryStr.empty()) binaryStr = "0";
        }

        cout << "Number: " << n << "\t (Binary: " << binaryStr << ")\n";
        cout << "  -> Bitwise:   " << (checker.isPowerOfTwoBitwise(n) ? "True" : "False") << "\n";
        cout << "  -> Popcount:  " << (checker.isPowerOfTwoPopcount(n) ? "True" : "False") << "\n";
        cout << "  -> Iterative: " << (checker.isPowerOfTwoIterative(n) ? "True" : "False") << "\n\n";
    }
    cout << "----------------------------\n";

    return 0;
}
#include <iostream>
#include <bitset>

using namespace std;

class SetBitsCounter {
public:
    // Approach 1: Simple Shift and AND
    // Checks every single bit from right to left.
    int countSimple(int n) {
        int count = 0;
        while (n > 0) {
            // Check if the least significant bit is 1
            count += (n & 1);
            // Shift right by 1 to process the next bit
            n >>= 1;
        }
        return count;
    }

    // Approach 2: Brian Kernighan's Algorithm
    // Skips the 0 bits and only processes the 1 bits.
    int countKernighan(int n) {
        int count = 0;
        while (n > 0) {
            // n & (n - 1) always drops the lowest set bit of n
            n = n & (n - 1); 
            count++;
        }
        return count;
    }

    // Approach 3: Compiler Built-in (GCC/Clang)
    // The most efficient method for competitive programming.
    int countBuiltin(int n) {
        // Returns the number of 1-bits in an integer.
        // For long long, use __builtin_popcountll(n)
        return __builtin_popcount(n); 
    }
};

int main() {
    int numbers[] = {9, 15, 128, 9999};
    SetBitsCounter counter;

    cout << "--- Counting Set Bits ---\n";
    for (int n : numbers) {
        // Using std::bitset just to display the binary string for visual proof
        string binaryStr = bitset<16>(n).to_string();
        // Strip leading zeros for a cleaner output
        binaryStr.erase(0, binaryStr.find_first_not_of('0')); 

        cout << "Number: " << n << "\t (Binary: " << binaryStr << ")\n";
        cout << "  -> Simple:    " << counter.countSimple(n) << "\n";
        cout << "  -> Kernighan: " << counter.countKernighan(n) << "\n";
        cout << "  -> Built-in:  " << counter.countBuiltin(n) << "\n\n";
    }
    cout << "-------------------------\n";

    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

class XorTricks {
public:
    // Trick 1: In-Place Swap
    // Swaps two variables without using a temporary variable.
    void swapInPlace(int& a, int& b) {
        // Warning: This will zero out the value if 'a' and 'b' 
        // point to the exact same memory address.
        if (&a != &b) {
            a ^= b;
            b ^= a;
            a ^= b;
        }
    }

    // Trick 2: Find the Single Non-Repeating Element
    // In an array where every element appears exactly twice except for one,
    // XORing all elements together will cancel out the pairs, leaving only the unique element.
    int findSingleNumber(const vector<int>& nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result;
    }

    // Trick 3: Find the Missing Number in a Sequence
    // Given an array of N distinct numbers in the range [0, N], find the missing one.
    int findMissingNumber(const vector<int>& nums) {
        int n = nums.size();
        int missing_num = 0;
        
        // XOR all expected indices and actual values together.
        // The numbers that are present will cancel out their corresponding index.
        for (int i = 0; i <= n; ++i) {
            missing_num ^= i;
        }
        for (int num : nums) {
            missing_num ^= num;
        }
        
        return missing_num;
    }
};

int main() {
    XorTricks tricks;

    cout << "--- Trick 1: In-Place Swap ---\n";
    int x = 10, y = 25;
    cout << "Before: x = " << x << ", y = " << y << "\n";
    tricks.swapInPlace(x, y);
    cout << "After:  x = " << x << ", y = " << y << "\n\n";

    cout << "--- Trick 2: Single Non-Repeating Element ---\n";
    vector<int> duplicates = {4, 1, 2, 1, 2};
    cout << "Array: [4, 1, 2, 1, 2]\n";
    cout << "Unique Number: " << tricks.findSingleNumber(duplicates) << "\n\n";

    cout << "--- Trick 3: Missing Number in Sequence ---\n";
    vector<int> sequence = {3, 0, 1}; // Missing 2
    cout << "Array (Expected [0..3]): [3, 0, 1]\n";
    cout << "Missing Number: " << tricks.findMissingNumber(sequence) << "\n";
    cout << "--------------------------------\n";

    return 0;
}
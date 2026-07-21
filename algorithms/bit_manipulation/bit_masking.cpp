#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class BitMasking {
public:
    // Generates all possible subsets using binary representation
    vector<vector<int>> generateSubsets(const vector<int>& elements) {
        int n = elements.size();
        
        // The total number of subsets for a set of size N is 2^N.
        // We can efficiently calculate 2^N using the left shift operator: (1 << n)
        int total_subsets = 1 << n; 
        
        vector<vector<int>> all_subsets;

        // Iterate from 0 up to (2^N) - 1. 
        // Each number represents a unique bit pattern for subset inclusion.
        for (int mask = 0; mask < total_subsets; mask++) {
            vector<int> current_subset;
            
            // Check every bit position from 0 to N-1
            for (int i = 0; i < n; i++) {
                
                // (1 << i) creates a number with only the i-th bit set to 1.
                // The bitwise AND (&) checks if the i-th bit in 'mask' is also 1.
                if ((mask & (1 << i)) != 0) {
                    current_subset.push_back(elements[i]);
                }
            }
            all_subsets.push_back(current_subset);
        }
        
        return all_subsets;
    }
    
    // Demonstrates common Bit Masking operations
    void bitwiseCheatSheet() {
        cout << "--- Common Bitmask Operations ---\n";
        cout << "Set the i-th bit:        mask | (1 << i)\n";
        cout << "Unset the i-th bit:      mask & ~(1 << i)\n";
        cout << "Toggle the i-th bit:     mask ^ (1 << i)\n";
        cout << "Check the i-th bit:      (mask & (1 << i)) != 0\n";
        cout << "Multiply by 2^N:         x << N\n";
        cout << "Divide by 2^N:           x >> N\n";
        cout << "Check if even/odd:       (x & 1) == 0 ? Even : Odd\n";
        cout << "Check if power of 2:     (x & (x - 1)) == 0 (and x > 0)\n";
        cout << "---------------------------------\n\n";
    }
};

int main() {
    // A distinct set of elements
    vector<int> elements = {1, 2, 3};
    int n = elements.size();
    
    BitMasking bm;
    bm.bitwiseCheatSheet();
    
    cout << "Original Set: { ";
    for (int num : elements) cout << num << " ";
    cout << "}\n\n";

    // Generate all subsets using bit manipulation
    vector<vector<int>> result = bm.generateSubsets(elements);

    // Print the results
    cout << "--- Generated Subsets (Power Set) ---\n";
    int count = 1;
    for (int i = 0; i < result.size(); i++) {
        cout << "Mask " << i << " (Bin: ";
        
        // Print the binary representation for clarity
        for(int b = n - 1; b >= 0; b--) {
            cout << (((1 << b) & i) != 0 ? "1" : "0");
        }
        
        cout << ") -> [ ";
        for (int num : result[i]) {
            cout << num << " ";
        }
        cout << "]\n";
    }
    cout << "-------------------------------------\n";
    cout << "Total subsets found: " << result.size() << "\n";

    return 0;
}
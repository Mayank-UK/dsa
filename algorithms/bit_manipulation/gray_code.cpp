#include <iostream>
#include <vector>

using namespace std;

class GrayCode {
public:
    // Generates the sequence of Gray codes for n bits
    vector<int> generate(int n) {
        vector<int> result;
        
        // The total number of codes for n bits is 2^n
        int num_codes = 1 << n;
        
        for (int i = 0; i < num_codes; ++i) {
            // Standard formula to convert a binary number 'i' to its Gray code:
            // Right shift 'i' by 1 and XOR it with the original 'i'
            int gray = i ^ (i >> 1);
            result.push_back(gray);
        }
        
        return result;
    }
    
    // Helper function to print the integer in a padded binary format
    void printBinary(int val, int bits) {
        for (int i = bits - 1; i >= 0; --i) {
            cout << (((1 << i) & val) != 0 ? "1" : "0");
        }
    }
};

int main() {
    GrayCode gc;
    
    // Test for a 3-bit Gray Code sequence
    int n = 3;
    vector<int> sequence = gc.generate(n);
    
    cout << "--- " << n << "-Bit Gray Code Sequence ---\n";
    cout << "Index\tBinary\tGray Code (Binary)\tGray Code (Int)\n";
    cout << "-------------------------------------------------------\n";
    
    for (int i = 0; i < sequence.size(); ++i) {
        cout << i << "\t";
        gc.printBinary(i, n);
        cout << "\t";
        gc.printBinary(sequence[i], n);
        cout << "\t\t\t" << sequence[i] << "\n";
    }
    cout << "-------------------------------------------------------\n";

    return 0;
}
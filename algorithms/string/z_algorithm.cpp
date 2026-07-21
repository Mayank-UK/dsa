#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ZAlgorithm {
private:
    // Core function to build the Z-array in O(N) time
    vector<int> buildZArray(const string& str) {
        int n = str.length();
        vector<int> Z(n, 0);
        
        // L and R represent the boundaries of the rightmost matched window
        int L = 0, R = 0; 
        
        // Note: Z[0] is typically not well-defined or used, so we start at i = 1
        for (int i = 1; i < n; i++) {
            // Case 1: i is outside the current window. 
            // We must calculate the Z-value naively by comparing characters.
            if (i > R) {
                L = R = i;
                while (R < n && str[R - L] == str[R]) {
                    R++;
                }
                Z[i] = R - L;
                R--; // R is now the index of the last matching character
            } 
            // Case 2: i is inside the current window [L, R]
            else {
                // k is the corresponding index in the prefix
                int k = i - L; 
                
                // If the previously computed Z-value at k does not stretch 
                // beyond the right boundary R, we can safely copy it.
                if (Z[k] < R - i + 1) {
                    Z[i] = Z[k];
                } 
                // If it touches or crosses the right boundary R, we must 
                // extend the window to the right starting from R.
                else {
                    L = i;
                    while (R < n && str[R - L] == str[R]) {
                        R++;
                    }
                    Z[i] = R - L;
                    R--;
                }
            }
        }
        return Z;
    }

public:
    // Searches for the pattern in the text in O(N + M) time
    void search(const string& pattern, const string& text) {
        if (pattern.empty() || text.empty()) {
            cout << "Pattern or text is empty.\n";
            return;
        }

        // Create the concatenated string: Pattern + Sentinel + Text
        // The sentinel ensures the Z-value never exceeds the pattern's length
        string concat = pattern + "$" + text;
        
        // Compute the Z-array for the concatenated string
        vector<int> Z = buildZArray(concat);
        
        cout << "--- Search Results ---\n";
        bool found = false;
        int m = pattern.length();
        
        // Iterate through the Z-array looking for matches
        for (int i = 0; i < Z.size(); i++) {
            // If the Z-value equals the pattern length, we found a match
            if (Z[i] == m) {
                found = true;
                
                // Calculate the original index in the text:
                // i is the current index in the concatenated string.
                // Subtracting m (pattern length) and 1 (the '$' symbol) gives the real index.
                int text_index = i - m - 1; 
                cout << "Pattern '" << pattern << "' found starting at index " << text_index << "\n";
            }
        }
        
        if (!found) {
            cout << "No patterns found in the text.\n";
        }
        cout << "----------------------\n";
    }
};

int main() {
    // Text to search within
    string text = "aabaacaadaabaaba";
    
    // Pattern to find
    string pattern = "aaba";
    
    cout << "Text:    " << text << "\n";
    cout << "Pattern: " << pattern << "\n\n";

    // Initialize the Z-Algorithm
    ZAlgorithm z_algo;

    // Perform the search
    z_algo.search(pattern, text);

    return 0;
}
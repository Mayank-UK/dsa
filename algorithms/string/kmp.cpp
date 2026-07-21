#include <iostream>
#include <vector>
#include <string>

using namespace std;

class KMP {
private:
    string pattern;
    vector<int> lps;

    // Preprocess the pattern to calculate the Longest Prefix Suffix (LPS) array
    void computeLPSArray() {
        int m = pattern.length();
        lps.assign(m, 0);
        
        int len = 0; // Length of the previous longest prefix suffix
        int i = 1;
        
        // Loop calculates lps[i] for i = 1 to m-1
        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                // Mismatch after len matches
                if (len != 0) {
                    // Fall back to the previous longest prefix suffix
                    len = lps[len - 1];
                } else {
                    // No prefix suffix match found
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

public:
    // Constructor initializes the pattern and builds the LPS array
    KMP(const string& input_pattern) {
        pattern = input_pattern;
        computeLPSArray();
    }

    // Search the text using the preprocessed LPS array
    void search(const string& text) {
        int n = text.length();
        int m = pattern.length();
        
        if (m == 0 || m > n) {
            cout << "Pattern is empty or longer than the text.\n";
            return;
        }

        cout << "--- Search Results ---\n";
        bool found = false;
        
        int i = 0; // Index for text
        int j = 0; // Index for pattern
        
        // Loop while there is enough text left to potentially match the pattern
        while ((n - i) >= (m - j)) {
            if (pattern[j] == text[i]) {
                j++;
                i++;
            }
            
            if (j == m) {
                // Match found!
                found = true;
                cout << "Pattern '" << pattern << "' found starting at index " << i - j << "\n";
                
                // Use the LPS array to find the next potential match alignment
                j = lps[j - 1];
            } 
            else if (i < n && pattern[j] != text[i]) {
                // Mismatch after j matches
                if (j != 0) {
                    // Do not match lps[j-1] characters, they will match anyway
                    j = lps[j - 1];
                } else {
                    // If j == 0, move to the next character in the text
                    i++;
                }
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
    string text = "ABABDABACDABABCABAB";
    
    // Pattern to find
    string pattern = "ABABCABAB";
    
    cout << "Text:    " << text << "\n";
    cout << "Pattern: " << pattern << "\n\n";

    // Initialize the KMP algorithm
    KMP kmp(pattern);

    // Perform the search
    kmp.search(text);

    return 0;
}
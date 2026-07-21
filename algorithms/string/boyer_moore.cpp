#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Using 256 to cover all extended ASCII characters
const int ALPHABET_SIZE = 256;

class BoyerMoore {
private:
    string pattern;
    vector<int> bad_char;

    // Preprocess the pattern to build the Bad Character Table
    void buildBadCharTable() {
        // Initialize all occurrences as -1
        bad_char.assign(ALPHABET_SIZE, -1);

        // Fill the actual value of the last occurrence of each character in the pattern
        for (int i = 0; i < pattern.length(); i++) {
            bad_char[(unsigned char)pattern[i]] = i;
        }
    }

public:
    // Constructor initializes the pattern and builds the preprocessing table
    BoyerMoore(const string& input_pattern) {
        pattern = input_pattern;
        buildBadCharTable();
    }

    // Search the text using the preprocessed Bad Character table
    void search(const string& text) {
        int m = pattern.length();
        int n = text.length();

        if (m == 0 || m > n) {
            cout << "Pattern is empty or longer than the text.\n";
            return;
        }

        cout << "--- Search Results ---\n";
        bool found = false;

        // 's' represents the shift of the pattern with respect to the text
        int s = 0; 
        
        while (s <= (n - m)) {
            int j = m - 1;

            // Keep reducing index j of the pattern while characters of 
            // the pattern and text match at this shift 's'
            while (j >= 0 && pattern[j] == text[s + j]) {
                j--;
            }

            // If the pattern is present at the current shift
            if (j < 0) {
                found = true;
                cout << "Pattern '" << pattern << "' found starting at index " << s << "\n";

                // Shift the pattern so that the next character in the text
                // aligns with its last occurrence in the pattern.
                // The condition s + m < n is necessary for when the pattern 
                // occurs exactly at the end of the text.
                s += (s + m < n) ? m - bad_char[(unsigned char)text[s + m]] : 1;
            } else {
                // Mismatch occurred. 
                // Shift the pattern so that the bad character in the text
                // aligns with its last occurrence in the pattern.
                // The max() function ensures we always get a positive shift 
                // (avoiding moving backwards if the last occurrence is to the right of j).
                s += max(1, j - bad_char[(unsigned char)text[s + j]]);
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
    string text = "abacaabadcabacabaabb";
    
    // Pattern to find
    string pattern = "abacab";
    
    cout << "Text:    " << text << "\n";
    cout << "Pattern: " << pattern << "\n\n";

    // Initialize the Boyer-Moore algorithm
    BoyerMoore bm(pattern);

    // Perform the search
    bm.search(text);

    return 0;
}
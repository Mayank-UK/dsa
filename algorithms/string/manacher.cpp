#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Manacher {
private:
    // Helper to transform the string to handle even and odd lengths uniformly
    // Example: "aba" -> "^#a#b#a#$"
    // Example: "bb"  -> "^#b#b#$"
    string preprocess(const string& s) {
        if (s.empty()) return "^$";
        
        string ret = "^";
        for (char c : s) {
            ret += "#" + string(1, c);
        }
        ret += "#$";
        return ret;
    }

public:
    // Finds and prints the longest palindromic substring
    void findLongestPalindrome(const string& text) {
        if (text.empty()) {
            cout << "Empty string provided.\n";
            return;
        }

        // T is the preprocessed string with boundaries and separators
        string T = preprocess(text);
        int n = T.length();
        
        // P[i] stores the radius of the longest palindrome centered at i
        vector<int> P(n, 0);
        
        int center = 0; // Center of the palindrome that reaches furthest to the right
        int right = 0;  // Rightmost boundary of that palindrome
        
        int max_len = 0;      // Length of the absolute longest palindrome found
        int center_index = 0; // Center index of the absolute longest palindrome

        // We iterate from 1 to n-2 because 0 is '^' and n-1 is '$'
        for (int i = 1; i < n - 1; i++) {
            // Find the mirror of i around the current 'center'
            int mirror = 2 * center - i;

            // If i is within the right boundary of the current furthest palindrome,
            // we can copy the previously computed radius from its mirror.
            // However, it cannot exceed the distance to the 'right' boundary.
            if (i < right) {
                P[i] = min(right - i, P[mirror]);
            }

            // Attempt to expand the palindrome centered at i
            // The sentinels '^' and '$' guarantee we won't go out of bounds here
            while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                P[i]++;
            }

            // If the palindrome centered at i expands past 'right',
            // adjust 'center' and 'right' to the new furthest-reaching palindrome.
            if (i + P[i] > right) {
                center = i;
                right = i + P[i];
            }

            // Track the absolute longest palindrome seen so far
            if (P[i] > max_len) {
                max_len = P[i];
                center_index = i;
            }
        }

        // Extract the longest palindrome from the original string.
        // The math maps the index from the preprocessed string T back to text.
        int start_idx = (center_index - 1 - max_len) / 2;
        string longest_palindrome = text.substr(start_idx, max_len);

        cout << "--- Search Results ---\n";
        cout << "Longest Palindromic Substring: '" << longest_palindrome << "'\n";
        cout << "Length: " << max_len << "\n";
        cout << "Starts at index: " << start_idx << " in the original string\n";
        cout << "----------------------\n";
    }
};

int main() {
    // String to search within
    string text = "forgeeksskeegfor";
    
    cout << "Original Text: " << text << "\n\n";

    // Initialize the Manacher algorithm class
    Manacher manacher;

    // Find the longest palindrome
    manacher.findLongestPalindrome(text);

    return 0;
}
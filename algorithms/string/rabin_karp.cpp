#include <iostream>
#include <vector>
#include <string>

using namespace std;

class RabinKarp {
private:
    // d is the number of characters in the input alphabet (256 for extended ASCII)
    const int d = 256; 
    
    // A large prime number to prevent integer overflow and minimize hash collisions
    long long q;       

public:
    // Constructor allows passing a custom prime, defaults to a large prime (10^9 + 7)
    RabinKarp(long long prime = 1000000007) {
        q = prime;
    }

    // Searches for the pattern in the given text
    void search(const string& pattern, const string& text) {
        int m = pattern.length();
        int n = text.length();
        bool found = false;

        if (m == 0 || m > n) {
            cout << "Pattern is empty or longer than the text.\n";
            return;
        }

        cout << "--- Search Results ---\n";

        long long p = 0; // Hash value for the pattern
        long long t = 0; // Hash value for the current window of the text
        long long h = 1; // The multiplier for the most significant digit

        // Calculate h = pow(d, m-1) % q
        for (int i = 0; i < m - 1; i++) {
            h = (h * d) % q;
        }

        // Precompute the hash value for the pattern and the first window of the text
        for (int i = 0; i < m; i++) {
            p = (d * p + pattern[i]) % q;
            t = (d * t + text[i]) % q;
        }

        // Slide the pattern over the text one character at a time
        for (int i = 0; i <= n - m; i++) {
            
            // Check if the current hash values match
            if (p == t) {
                bool match = true;
                
                // Hashes match, so we must verify character by character 
                // to ensure it's not a hash collision
                for (int j = 0; j < m; j++) {
                    if (text[i + j] != pattern[j]) {
                        match = false;
                        break;
                    }
                }

                if (match) {
                    found = true;
                    cout << "Pattern '" << pattern << "' found starting at index " << i << "\n";
                }
            }

            // Calculate the hash value for the next window of text:
            // Remove the leading character, shift, and add the trailing character
            if (i < n - m) {
                t = (d * (t - text[i] * h) + text[i + m]) % q;

                // Modulo arithmetic can result in negative values in C++,
                // so we convert it to a positive equivalent
                if (t < 0) {
                    t = (t + q);
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
    string text = "AABAACAADAABAABA";
    
    // Pattern to find
    string pattern = "AABA";
    
    cout << "Text:    " << text << "\n";
    cout << "Pattern: " << pattern << "\n\n";

    // Initialize the Rabin-Karp algorithm
    RabinKarp rk;

    // Perform the search
    rk.search(pattern, text);

    return 0;
}
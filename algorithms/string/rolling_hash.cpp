#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class RollingHash {
private:
    // Prime base (31 is common for lowercase English, 256 for all ASCII)
    const long long p = 256; 
    
    // Large prime modulus to prevent overflow and minimize collisions
    const long long m = 1e9 + 9; 
    
    // Arrays to store precomputed prefix hashes and powers of p
    vector<long long> hash_prefix;
    vector<long long> p_pow;

public:
    // Constructor precomputes hashes and powers in O(N) time
    RollingHash(const string& s) {
        int n = s.length();
        
        // hash_prefix[i] will store the hash of the prefix of length i
        hash_prefix.assign(n + 1, 0);
        
        // p_pow[i] will store p^i modulo m
        p_pow.assign(n + 1, 1);

        for (int i = 0; i < n; ++i) {
            // Build the prefix hash
            hash_prefix[i + 1] = (hash_prefix[i] * p + s[i]) % m;
            
            // Precompute the powers of the base prime
            p_pow[i + 1] = (p_pow[i] * p) % m;
        }
    }

    // Returns the hash of the substring s[l...r] (inclusive) in O(1) time
    long long get_substring_hash(int l, int r) {
        assert(l >= 0 && r >= l && r < hash_prefix.size() - 1);
        
        // Mathematically: H(l, r) = (H[r+1] - H[l] * p^(r - l + 1)) % m
        long long hash_val = (hash_prefix[r + 1] - (hash_prefix[l] * p_pow[r - l + 1]) % m) % m;
        
        // C++ modulo operator can return negative results, so we ensure it's positive
        if (hash_val < 0) {
            hash_val += m;
        }
        
        return hash_val;
    }
};

int main() {
    // Example string
    string text = "abacaba";
    cout << "Original Text: " << text << "\n\n";

    // Precompute hashes for the text
    RollingHash rh(text);

    // Let's compare some substrings using their O(1) hashes
    
    // Substring 1: "aba" from index 0 to 2
    long long hash1 = rh.get_substring_hash(0, 2);
    
    // Substring 2: "aba" from index 4 to 6
    long long hash2 = rh.get_substring_hash(4, 6);
    
    // Substring 3: "cab" from index 3 to 5
    long long hash3 = rh.get_substring_hash(3, 5);

    cout << "--- Hash Comparisons ---\n";
    cout << "Hash of text[0..2] ('aba'): " << hash1 << "\n";
    cout << "Hash of text[4..6] ('aba'): " << hash2 << "\n";
    cout << "Hash of text[3..5] ('cab'): " << hash3 << "\n\n";

    if (hash1 == hash2) {
        cout << "Match found: text[0..2] is identical to text[4..6]\n";
    }

    if (hash1 != hash3) {
        cout << "Mismatch: text[0..2] is different from text[3..5]\n";
    }
    cout << "----------------------\n";

    return 0;
}
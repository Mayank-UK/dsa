#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Manacher's algorithm. Finds the longest palindromic substring in O(n) by
// reusing previously computed radii: keep the palindrome [center, right] that
// reaches furthest right, and when a new center i falls inside it, seed P[i]
// from its mirror (clamped to the boundary) before expanding. Sentinels '^'
// and '$' let the expansion stop itself without bounds checks.

struct Palindrome {
    string text;    // the palindrome substring
    int    length;
    int    start;   // start index in the ORIGINAL string
};

class Manacher {
private:
    // "aba" -> "^#a#b#a#$" : interleave with '#' so even- and odd-length
    // palindromes are handled uniformly, and add sentinels at both ends.
    static string preprocess(const string& s) {
        string t = "^";
        for (char c : s) { t += '#'; t += c; }
        t += "#$";
        return t;
    }

public:
    // Returns the longest palindromic substring of `s` (empty string → length 0).
    static Palindrome longestPalindrome(const string& s) {
        if (s.empty()) return {"", 0, -1};

        string T = preprocess(s);
        int n = (int)T.length();
        vector<int> P(n, 0);                 // P[i] = radius of palindrome centered at i

        int center = 0, right = 0;           // furthest-reaching palindrome so far
        int maxLen = 0, maxCenter = 0;

        for (int i = 1; i < n - 1; ++i) {
            int mirror = 2 * center - i;
            if (i < right) P[i] = min(right - i, P[mirror]);   // seed from mirror

            while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) ++P[i]; // expand (sentinels stop it)

            if (i + P[i] > right) { center = i; right = i + P[i]; }
            if (P[i] > maxLen)   { maxLen = P[i]; maxCenter = i; }
        }

        int start = (maxCenter - 1 - maxLen) / 2;             // map back to original
        return { s.substr(start, maxLen), maxLen, start };
    }
};

// ─── Demo helpers ───
static void runCase(const string& label, const string& s) {
    Palindrome p = Manacher::longestPalindrome(s);
    cout << "  " << label << " \"" << s << "\"\n";
    if (p.length == 0) cout << "    -> (empty)\n\n";
    else cout << "    -> \"" << p.text << "\"  length=" << p.length
              << "  start=" << p.start << "\n\n";
}

int main() {
    cout << "====================== Manacher (Longest Palindrome) ======================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time   : O(n)        each center's expansion is amortized constant\n";
    cout << "  Space  : O(n)        radius array + transformed string\n";
    cout << "  Notes  : the '^'/'$' sentinels and '#' spacers unify odd/even cases.\n\n";

    cout << "[Demo]\n";
    runCase("classic even", "forgeeksskeegfor");   // "geeksskeeg"
    runCase("classic odd ", "babad");               // "bab" or "aba"

    cout << "[Edge Cases]\n";
    runCase("empty          ", "");
    runCase("single char    ", "a");
    runCase("all same       ", "aaaa");
    runCase("no repeat > 1  ", "abcdef");
    runCase("palindrome at end", "xyzracecar");

    return 0;
}

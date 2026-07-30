#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Rabin-Karp. Hash the pattern and each text window of length m; only when the
// hashes match do we verify character-by-character (to rule out collisions).
// The window hash rolls in O(1): drop the leading char, multiply by the base,
// add the trailing char — all mod a large prime. Multiple patterns are found by
// hashing each and comparing, which is RK's strength.

class RabinKarp {
private:
    static constexpr int BASE = 256;            // alphabet size (extended ASCII)
    long long prime;                            // large prime modulus

public:
    RabinKarp(long long q = 1000000007) : prime(q) {}

    // Returns every start index in `text` where `pattern` occurs.
    vector<int> search(const string& pattern, const string& text) const {
        vector<int> matches;
        int m = (int)pattern.length();
        int n = (int)text.length();
        if (m == 0 || m > n) return matches;

        long long h = 1;                        // h = BASE^(m-1) mod prime
        for (int i = 0; i < m - 1; ++i) h = (h * BASE) % prime;

        long long ph = 0, th = 0;               // pattern hash, current window hash
        for (int i = 0; i < m; ++i) {
            ph = (BASE * ph + (unsigned char)pattern[i]) % prime;
            th = (BASE * th + (unsigned char)text[i])     % prime;
        }

        for (int i = 0; i <= n - m; ++i) {
            if (ph == th) {                     // hash hit — verify to reject collisions
                bool match = true;
                for (int j = 0; j < m; ++j)
                    if (text[i + j] != pattern[j]) { match = false; break; }
                if (match) matches.push_back(i);
            }
            if (i < n - m) {                    // roll the window hash forward
                th = (BASE * (th - (unsigned char)text[i] * h) + (unsigned char)text[i + m]) % prime;
                if (th < 0) th += prime;        // C++ % can be negative
            }
        }
        return matches;
    }
};

// ─── Demo helpers ───
static void printMatches(const string& pattern, const string& text, const vector<int>& m) {
    cout << "  text    : " << text << "\n";
    cout << "  pattern : " << pattern << "\n";
    if (m.empty()) { cout << "  result  : Not Found\n"; return; }
    cout << "  found at: ";
    for (size_t k = 0; k < m.size(); ++k) cout << m[k] << (k + 1 < m.size() ? ", " : "");
    cout << "  (" << m.size() << " occurrence" << (m.size() == 1 ? "" : "s") << ")\n";
}

static void runCase(const string& label, const string& pattern, const string& text) {
    cout << "[" << label << "]\n";
    printMatches(pattern, text, RabinKarp().search(pattern, text));
    cout << "\n";
}

int main() {
    cout << "======================== Rabin-Karp String Search ========================\n\n";

    cout << "[Complexity]\n";
    cout << "  Average : O(n + m)     one rolling-hash pass, O(1) verify per hash hit\n";
    cout << "  Worst   : O(n * m)     spurious collisions everywhere (pathological)\n";
    cout << "  Space   : O(1)\n";
    cout << "  Notes   : hash match MUST be verified char-by-char — collisions exist.\n\n";

    cout << "[Demo]\n";
    string pattern = "AABA";
    printMatches(pattern, "AABAACAADAABAABA", RabinKarp().search(pattern, "AABAACAADAABAABA"));
    cout << "\n";

    cout << "[Edge Cases]\n";
    runCase("overlapping    ", "AA",   "AAAAA");
    runCase("absent         ", "XYZ",  "ABCDEFG");
    runCase("pattern > text ", "ABCDEF", "ABC");
    runCase("empty pattern  ", "",     "ABC");
    runCase("single chars   ", "A",    "BANANA");

    return 0;
}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Knuth–Morris–Pratt string matching. The key idea: when a mismatch happens
// after j matched characters, the LPS (longest proper prefix which is also a
// suffix) array tells us how far to fall back in the pattern WITHOUT moving the
// text pointer back. That avoids re-checking characters and gives linear time.

class KMP {
private:
    string pattern;
    vector<int> lps;

    // Build the LPS array: lps[i] = length of the longest proper prefix of
    // pattern[0..i] that is also a suffix of pattern[0..i].
    void computeLPSArray() {
        int m = (int)pattern.length();
        lps.assign(m, 0);

        int len = 0;   // length of the current matching prefix
        int i = 1;
        while (i < m) {
            if (pattern[i] == pattern[len]) {
                lps[i++] = ++len;
            } else if (len != 0) {
                len = lps[len - 1];   // fall back, do NOT advance i
            } else {
                lps[i++] = 0;
            }
        }
    }

public:
    KMP(const string& p) : pattern(p) {
        computeLPSArray();
    }

    const vector<int>& getLPS() const { return lps; }

    // Returns every start index in `text` where `pattern` occurs.
    vector<int> search(const string& text) const {
        vector<int> matches;
        int n = (int)text.length();
        int m = (int)pattern.length();
        if (m == 0 || m > n) return matches;

        int i = 0, j = 0;          // i -> text, j -> pattern
        while (i < n) {
            if (text[i] == pattern[j]) { ++i; ++j; }
            if (j == m) {                          // full match
                matches.push_back(i - j);
                j = lps[j - 1];                    // continue without backing up i
            } else if (i < n && text[i] != pattern[j]) {
                if (j != 0) j = lps[j - 1];   // fall back, retry same text char
                else        ++i;              // no progress possible, advance text
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
    printMatches(pattern, text, KMP(pattern).search(text));
    cout << "\n";
}

int main() {
    cout << "=========================== KMP String Search ===========================\n\n";

    cout << "[Complexity]\n";
    cout << "  Preprocess : O(m)         build the LPS array\n";
    cout << "  Search     : O(n + m)     text pointer never moves backward\n";
    cout << "  Space      : O(m)         LPS array\n";
    cout << "  Notes      : LPS fallback is the whole trick — no re-scanning of text.\n\n";

    cout << "[Demo] the LPS array is what KMP is teaching:\n";
    string pattern = "ABABCABAB";
    KMP kmp(pattern);
    cout << "  pattern : " << pattern << "\n  LPS     : ";
    for (int v : kmp.getLPS()) cout << v << " ";
    cout << "\n";
    string text = "ABABDABACDABABCABAB";
    printMatches(pattern, text, kmp.search(text));
    cout << "\n";

    cout << "[Edge Cases]\n";
    runCase("overlapping    ", "AA",   "AAAAA");          // 0,1,2,3
    runCase("multiple       ", "AABA", "AABAACAADAABAABA");
    runCase("absent         ", "XYZ",  "ABCDEFG");
    runCase("pattern > text ", "ABCDEF", "ABC");
    runCase("empty pattern  ", "",     "ABC");
    runCase("single chars   ", "A",    "BANANA");

    return 0;
}

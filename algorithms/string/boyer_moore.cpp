#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Boyer-Moore (bad-character heuristic). Match the pattern against the text from
// RIGHT to LEFT. On a mismatch, slide the pattern so the mismatched text char
// aligns with its rightmost occurrence in the pattern — often skipping large
// chunks of text. Sublinear in practice on large alphabets. (This implements the
// bad-character rule only; the full algorithm also adds the good-suffix rule.)

const int ALPHABET_SIZE = 256;   // extended ASCII

class BoyerMoore {
private:
    string pattern;
    vector<int> bad_char;        // rightmost index of each char in the pattern, else -1

    void buildBadCharTable() {
        bad_char.assign(ALPHABET_SIZE, -1);
        for (int i = 0; i < (int)pattern.length(); ++i)
            bad_char[(unsigned char)pattern[i]] = i;
    }

public:
    BoyerMoore(const string& p) : pattern(p) { buildBadCharTable(); }

    // Returns every start index in `text` where `pattern` occurs.
    vector<int> search(const string& text) const {
        vector<int> matches;
        int m = (int)pattern.length();
        int n = (int)text.length();
        if (m == 0 || m > n) return matches;

        for (int s = 0; s <= n - m;) {
            int j = m - 1;
            while (j >= 0 && pattern[j] == text[s + j]) --j;   // match right→left

            if (j < 0) {                                       // full match
                matches.push_back(s);
                // Slide past: align the char after the match with its rightmost spot.
                int next = bad_char[(unsigned char)text[s + m]];
                s += (s + m < n) ? max(1, m - next) : 1;
            } else {
                // Mismatch at j: shift so text[s+j] aligns with its rightmost spot
                // in the pattern (clamped to ≥1 so we never slide backward).
                s += max(1, j - bad_char[(unsigned char)text[s + j]]);
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
    printMatches(pattern, text, BoyerMoore(pattern).search(text));
    cout << "\n";
}

int main() {
    cout << "==================== Boyer-Moore (Bad-Character) ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(n / m)     sublinear — skips text on each mismatch\n";
    cout << "  Worst   : O(n * m)     bad-char rule alone (good-suffix rule fixes this)\n";
    cout << "  Space   : O(alphabet)  bad-character table (256 here)\n";
    cout << "  Notes   : right-to-left compare; shines on large alphabets / long patterns.\n\n";

    cout << "[Demo]\n";
    string pattern = "abacab";
    printMatches(pattern, "abacaabadcabacabaabb", BoyerMoore(pattern).search("abacaabadcabacabaabb"));
    cout << "\n";

    cout << "[Edge Cases]\n";
    runCase("multiple       ", "AABA", "AABAACAADAABAABA");
    runCase("overlapping    ", "AA",   "AAAAA");
    runCase("absent         ", "XYZ",  "ABCDEFG");
    runCase("pattern > text ", "ABCDEF", "ABC");
    runCase("empty pattern  ", "",     "ABC");
    runCase("single chars   ", "A",    "BANANA");

    return 0;
}

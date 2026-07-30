#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Z-algorithm. Z[i] = length of the longest substring starting at i that is also
// a prefix of the whole string. Computed in O(n) by maintaining the rightmost
// matched segment [L, R] and reusing the mirrored prefix value. Pattern search
// is just running Z over pattern + "$" + text and reporting where Z[i] == |pattern|.

class ZAlgorithm {
private:
    static vector<int> buildZArray(const string& str) {
        int n = (int)str.length();
        vector<int> Z(n, 0);
        int L = 0, R = 0;                  // rightmost matched window [L, R)
        for (int i = 1; i < n; ++i) {
            if (i < R) {                   // inside the window: reuse mirror
                Z[i] = min(R - i, Z[i - L]);
            }
            while (R < n && i + Z[i] < n && str[Z[i]] == str[i + Z[i]]) {
                ++Z[i];                    // extend past the window if it matches
            }
            if (i + Z[i] > R) {            // window extended → update [L, R]
                L = i;
                R = i + Z[i];
            }
        }
        return Z;
    }

public:
    // The Z-array of any string (Z[0] is conventionally the full length).
    static vector<int> getZArray(const string& s) {
        vector<int> Z = buildZArray(s);
        if (!Z.empty()) Z[0] = (int)s.length();
        return Z;
    }

    // Returns every start index in `text` where `pattern` occurs.
    static vector<int> search(const string& pattern, const string& text) {
        vector<int> matches;
        if (pattern.empty() || text.empty()) return matches;

        string concat = pattern + "$" + text;   // '$' is a sentinel not in the alphabet
        vector<int> Z = buildZArray(concat);
        int m = (int)pattern.length();
        for (int i = m + 1; i < (int)Z.size(); ++i) {
            if (Z[i] == m) matches.push_back(i - m - 1);   // map back into text
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
    printMatches(pattern, text, ZAlgorithm::search(pattern, text));
    cout << "\n";
}

int main() {
    cout << "======================== Z-Algorithm String Search ========================\n\n";

    cout << "[Complexity]\n";
    cout << "  Z-array   : O(n)         each character is matched at most once\n";
    cout << "  Search    : O(n + m)     one Z pass over pattern+text\n";
    cout << "  Space     : O(n + m)\n";
    cout << "  Notes     : Z[i] = longest prefix of the string that restarts at i.\n\n";

    cout << "[Demo] the Z-array itself is the lesson:\n";
    string demo = "aabxaabxaab";
    vector<int> Z = ZAlgorithm::getZArray(demo);
    cout << "  string : " << demo << "\n  Z      : ";
    for (int v : Z) cout << v << " ";
    cout << "\n\n";

    cout << "[Search]\n";
    printMatches("aaba", "aabaacaadaabaaba", ZAlgorithm::search("aaba", "aabaacaadaabaaba"));
    cout << "\n";

    cout << "[Edge Cases]\n";
    runCase("overlapping    ", "AA",   "AAAAA");
    runCase("absent         ", "XYZ",  "ABCDEFG");
    runCase("pattern > text ", "ABCDEF", "ABC");
    runCase("empty pattern  ", "",     "ABC");
    runCase("single chars   ", "A",    "BANANA");

    return 0;
}

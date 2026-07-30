#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

// Rolling hash (Rabin fingerprint via prefix hashes). Precompute prefix hashes
// and powers of the base so that the hash of ANY substring s[l..r] is answered
// in O(1):  H(l,r) = (H[r+1] - H[l] * BASE^(r-l+1)) mod M.
// That turns "are two substrings equal?" into an O(1) integer comparison.

class RollingHash {
private:
    static constexpr long long BASE = 256;      // base (256 for arbitrary ASCII)
    static constexpr long long MOD  = 1000000009; // large prime modulus
    vector<long long> prefix;                   // prefix[i] = hash of s[0..i-1]
    vector<long long> powb;                      // powb[i] = BASE^i mod MOD

public:
    explicit RollingHash(const string& s) {
        int n = (int)s.length();
        prefix.assign(n + 1, 0);
        powb.assign(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = (prefix[i] * BASE + (unsigned char)s[i]) % MOD;
            powb[i + 1]   = (powb[i]   * BASE) % MOD;
        }
    }

    // Hash of substring s[l..r] inclusive, in O(1).
    long long substringHash(int l, int r) const {
        assert(l >= 0 && l <= r && r < (int)prefix.size() - 1);
        long long h = (prefix[r + 1] - prefix[l] * powb[r - l + 1]) % MOD;
        if (h < 0) h += MOD;                     // C++ % can be negative
        return h;
    }

    // True iff s[l1..r1] equals s[l2..r2] — by hash equality (probabilistic).
    bool substringsEqual(int l1, int r1, int l2, int r2) const {
        if (r1 - l1 != r2 - l2) return false;    // different lengths can't be equal
        return substringHash(l1, r1) == substringHash(l2, r2);
    }
};

// ─── Demo helpers ───
static void runSub(const string& s, int l, int r) {
    RollingHash rh(s);
    cout << "  s[" << l << ".." << r << "] = \"" << s.substr(l, r - l + 1)
         << "\"   hash = " << rh.substringHash(l, r) << "\n";
}

int main() {
    cout << "=========================== Rolling Hash ===========================\n\n";

    cout << "[Complexity]\n";
    cout << "  Preprocess : O(n)        prefix hashes + powers of BASE\n";
    cout << "  Per query  : O(1)        substring hash / equality\n";
    cout << "  Space      : O(n)\n";
    cout << "  Notes      : equality is PROBABILISTIC — collisions possible but rare\n";
    cout << "               with a large prime; double-hash to make it negligible.\n\n";

    cout << "[Demo] O(1) substring hashing on \"abacaba\":\n";
    string s = "abacaba";
    cout << "  string : " << s << "\n";
    RollingHash rh(s);
    cout << "  s[0..2] (\"aba\") hash = " << rh.substringHash(0, 2) << "\n";
    cout << "  s[4..6] (\"aba\") hash = " << rh.substringHash(4, 6) << "\n";
    cout << "  s[3..5] (\"cab\") hash = " << rh.substringHash(3, 5) << "\n";
    cout << "  s[0..2] == s[4..6]? " << (rh.substringsEqual(0, 2, 4, 6) ? "Yes (equal)" : "No") << "\n";
    cout << "  s[0..2] == s[3..5]? " << (rh.substringsEqual(0, 2, 3, 5) ? "Yes" : "No (different)") << "\n\n";

    cout << "[Edge Cases]\n";
    runSub("abcde", 2, 2);        // single character
    runSub("abcde", 0, 4);        // whole string
    runSub("hello", 1, 3);        // interior window
    {
        RollingHash single("z");
        cout << "  single-char string \"z\" -> hash = " << single.substringHash(0, 0) << "\n";
    }
    cout << "\n";

    return 0;
}

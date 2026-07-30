#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Gray code. A Gray code of n bits lists all 2^n values so that CONSECUTIVE
// values differ in exactly one bit (and the last wraps to the first). The
// reflected binary formula  gray(i) = i ^ (i >> 1)  builds the canonical one in
// index order — used in K-maps, rotary encoders, and error-minimizing search.

class GrayCode {
public:
    // The 2^n Gray-code values, in order, for n bits.
    static vector<int> generate(int n) {
        int total = 1 << n;
        vector<int> codes;
        codes.reserve(total);
        for (int i = 0; i < total; ++i)
            codes.push_back(i ^ (i >> 1));    // binary → Gray
        return codes;
    }
};

// ─── Demo helpers ───
static string binStr(int val, int bits) {
    string s;
    for (int b = bits - 1; b >= 0; --b) s += ((val >> b) & 1 ? '1' : '0');
    return s;
}

// Verify the defining property: each adjacent pair (and the wrap-around) differs
// in exactly one bit. Returns true iff the sequence is a valid cyclic Gray code.
static bool verifyProperty(const vector<int>& codes) {
    int n = (int)codes.size();
    for (int i = 0; i < n; ++i) {
        int diff = codes[i] ^ codes[(i + 1) % n];   // XOR = bits that differ
        if (diff == 0 || (diff & (diff - 1)) != 0)  // not exactly one set bit
            return false;
    }
    return true;
}

int main() {
    cout << "============================ Gray Code ============================\n\n";

    cout << "[Complexity]\n";
    cout << "  Generate 2^n codes : O(2^n) time and space\n";
    cout << "  Notes  : gray(i) = i ^ (i >> 1); consecutive codes differ in ONE bit.\n\n";

    int n = 3;
    vector<int> codes = GrayCode::generate(n);
    cout << "[Demo] " << n << "-bit Gray code:\n";
    cout << "  i   binary   gray\n";
    for (int i = 0; i < (int)codes.size(); ++i)
        cout << "  " << i << "   " << binStr(i, n) << "     " << binStr(codes[i], n) << "\n";
    cout << "  Adjacent differ by exactly one bit : "
         << (verifyProperty(codes) ? "Yes" : "No") << "\n\n";

    cout << "[Edge Cases]\n";
    cout << "  n = 0 -> { " ;
    { vector<int> z = GrayCode::generate(0); for (int v : z) cout << v << " "; cout << "} (single value)\n"; }
    cout << "  n = 1 -> { ";
    { vector<int> o = GrayCode::generate(1); for (int v : o) cout << v << " "; cout << "} (0,1)\n"; }
    cout << "  n = 4 still valid : "
         << (verifyProperty(GrayCode::generate(4)) ? "Yes" : "No") << "\n";

    return 0;
}

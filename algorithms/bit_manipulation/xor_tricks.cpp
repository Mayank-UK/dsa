#include <iostream>
#include <vector>
#include <string>

using namespace std;

// XOR (⊕) tricks powered by two facts: x ⊕ x = 0 (anything XORs with itself away)
// and x ⊕ 0 = x. That self-cancelling property turns a stream of duplicates into
// noise and leaves only the un-paired value. This file collects three classic uses.

class XorTricks {
public:
    // Swap two ints with no temp variable: a^=b; b^=a; a^=b. NOT safe if both
    // references alias the same variable (would zero it) — guarded here.
    static void swapInPlace(int& a, int& b) {
        if (&a == &b) return;     // aliasing guard
        a ^= b; b ^= a; a ^= b;
    }

    // In an array where every value appears twice except one, XORing all values
    // cancels the pairs and leaves the singleton.
    static int findSingleNumber(const vector<int>& nums) {
        int r = 0;
        for (int x : nums) r ^= x;
        return r;
    }

    // Find the missing number in a permutation of [0..n] (one missing): XOR all
    // indices [0..n] with all values — present pairs cancel, the missing one survives.
    static int findMissingNumber(const vector<int>& nums) {
        int n = (int)nums.size();
        int missing = 0;
        for (int i = 0; i <= n; ++i) missing ^= i;     // expected full range
        for (int x : nums) missing ^= x;                // actual values
        return missing;
    }
};

int main() {
    cout << "============================ XOR Tricks ============================\n\n";

    cout << "[Complexity]\n";
    cout << "  All tricks : O(n) time, O(1) space\n";
    cout << "  Notes : x ^ x = 0 and x ^ 0 = x — pairs cancel, the lone survivor remains.\n\n";

    cout << "[Trick 1] in-place swap:\n";
    int x = 10, y = 25;
    cout << "  before: x=" << x << ", y=" << y << "\n";
    XorTricks::swapInPlace(x, y);
    cout << "  after : x=" << x << ", y=" << y << "   (swapped : " << (x==25 && y==10 ? "Yes" : "No") << ")\n\n";

    cout << "[Trick 2] single non-repeating element:\n";
    vector<int> dup = {4, 1, 2, 1, 2};
    cout << "  [4,1,2,1,2] -> " << XorTricks::findSingleNumber(dup) << " (expect 4)\n\n";

    cout << "[Trick 3] missing number in [0..n]:\n";
    vector<int> seq = {3, 0, 1};
    cout << "  [3,0,1] (range [0..3]) -> " << XorTricks::findMissingNumber(seq) << " (expect 2)\n\n";

    cout << "[Edge Cases]\n";
    cout << "  single-element array -> " << XorTricks::findSingleNumber({7}) << " (expect 7)\n";
    cout << "  missing first (0)    -> " << XorTricks::findMissingNumber({1, 2, 3}) << " (expect 0)\n";
    cout << "  missing last (n)     -> " << XorTricks::findMissingNumber({0, 1, 2}) << " (expect 3)\n";
    cout << "  swap alias guarded   -> ";
    { int v = 5; XorTricks::swapInPlace(v, v); cout << "v=" << v << " (unchanged)\n"; }

    return 0;
}

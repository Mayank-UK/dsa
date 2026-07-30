#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Bit masking. An integer's bits are a compact set membership / flags array:
// bit i set ⇔ element i is "in". One 32/64-bit int encodes a subset of up to
// 32/64 items, and set algebra becomes single instructions (AND=∩, OR=∪,
// XOR=symmetric difference). This file shows the core operations and the
// canonical application — enumerating a power set by walking all 2^n masks.
// (For a deeper subset-enumeration treatment incl. backtracking, see
//  subset_enumeration.cpp.)

class BitMasking {
public:
    // Every subset of `elements` ↔ one integer in [0, 2^n). Bit i of the mask
    // selects elements[i]. Returns subsets ordered by mask value.
    static vector<vector<int>> generateSubsets(const vector<int>& elements) {
        int n = (int)elements.size();
        int total = 1 << n;                         // 2^n
        vector<vector<int>> all;
        all.reserve(total);
        for (int mask = 0; mask < total; ++mask) {
            vector<int> subset;
            for (int i = 0; i < n; ++i)
                if (mask & (1 << i)) subset.push_back(elements[i]);
            all.push_back(subset);
        }
        return all;
    }
};

// ─── Demo helpers ───
static bool mask_on(int val, int b) { return (val & (1 << b)) != 0; }   // is bit b set?

static string binStr(int val, int bits) {
    string s;
    for (int b = bits - 1; b >= 0; --b) s += (mask_on(val, b) ? '1' : '0');
    return s;
}

static void printSubsets(const vector<int>& elements, const vector<vector<int>>& subsets) {
    int n = (int)elements.size();
    for (int i = 0; i < (int)subsets.size(); ++i) {
        cout << "  mask " << binStr(i, n) << " -> [ ";
        for (int x : subsets[i]) cout << x << " ";
        cout << "]\n";
    }
}

int main() {
    cout << "============================ Bit Masking ============================\n\n";

    cout << "[Complexity]\n";
    cout << "  Single op (set/check/toggle bit i) : O(1)\n";
    cout << "  Power set of n items               : O(n * 2^n) time, O(2^n) output\n";
    cout << "  Notes  : AND=intersection, OR=union, XOR=symmetric difference.\n\n";

    cout << "[Operations] the bitmask cheat-sheet:\n";
    cout << "  set i-th bit    :  mask | (1 << i)\n";
    cout << "  clear i-th bit  :  mask & ~(1 << i)\n";
    cout << "  toggle i-th bit :  mask ^ (1 << i)\n";
    cout << "  test i-th bit   :  (mask & (1 << i)) != 0\n";
    cout << "  is power of two :  n > 0 && (n & (n - 1)) == 0\n";
    cout << "  even/odd        :  (x & 1) == 0 ? even : odd\n\n";

    cout << "[Demo] power set of {1, 2, 3} via masks:\n";
    vector<int> elements = {1, 2, 3};
    printSubsets(elements, BitMasking::generateSubsets(elements));
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  empty set   -> " << BitMasking::generateSubsets({}).size() << " subset(s)  (just {})\n";
    cout << "  single item -> ";
    printSubsets({42}, BitMasking::generateSubsets({42}));

    return 0;
}

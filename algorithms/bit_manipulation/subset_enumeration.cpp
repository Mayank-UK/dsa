#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Subset enumeration (the power set). Two ways to list all 2^n subsets of an
// n-element set: (1) bit masks — mask m in [0, 2^n) IS a subset, bit i selects
// element i; (2) recursion/backtracking — at each element, branch on include vs
// exclude. Both produce 2^n subsets; this file shows both sides by side.
// (For the bitmask-operations angle, see bit_masking.cpp.)

class SubsetGenerator {
public:
    // Bit-mask iteration over [0, 2^n).
    static vector<vector<int>> generateBitwise(const vector<int>& nums) {
        int n = (int)nums.size();
        vector<vector<int>> powerSet;
        powerSet.reserve(1 << n);
        for (int mask = 0; mask < (1 << n); ++mask) {
            vector<int> sub;
            for (int i = 0; i < n; ++i)
                if (mask & (1 << i)) sub.push_back(nums[i]);
            powerSet.push_back(sub);
        }
        return powerSet;
    }

    // Recursion: choose exclude/include at each index (classic include/exclude tree).
    static vector<vector<int>> generateBacktracking(const vector<int>& nums) {
        vector<vector<int>> powerSet;
        vector<int> cur;
        backtrack(0, cur, nums, powerSet);
        return powerSet;
    }

private:
    static void backtrack(int idx, vector<int>& cur, const vector<int>& nums,
                          vector<vector<int>>& out) {
        if (idx == (int)nums.size()) { out.push_back(cur); return; }
        backtrack(idx + 1, cur, nums, out);     // exclude nums[idx]
        cur.push_back(nums[idx]);
        backtrack(idx + 1, cur, nums, out);     // include nums[idx]
        cur.pop_back();                          // un-choose
    }
};

// ─── Demo helpers ───
static void printSubsets(const vector<vector<int>>& subsets) {
    cout << "  { ";
    for (size_t i = 0; i < subsets.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < subsets[i].size(); ++j)
            cout << subsets[i][j] << (j + 1 < subsets[i].size() ? "," : "");
        cout << "]" << (i + 1 < subsets.size() ? " " : "");
    }
    cout << " }  (" << subsets.size() << " subsets)\n";
}

int main() {
    cout << "====================== Subset Enumeration ======================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n * 2^n)   must emit 2^n subsets, each up to size n\n";
    cout << "  Space : O(n) recursion (backtracking) · O(2^n) to store output\n";
    cout << "  Notes : bitmask form maps each subset to an int in [0, 2^n).\n\n";

    vector<int> set = {1, 2, 3};
    auto bw = SubsetGenerator::generateBitwise(set);
    auto bt = SubsetGenerator::generateBacktracking(set);
    cout << "[Demo] power set of {1,2,3}:\n";
    cout << "  bitwise     : "; printSubsets(bw);
    cout << "  backtracking: "; printSubsets(bt);
    cout << "  both emit 2^" << set.size() << " = " << bw.size() << " subsets : "
         << (bw.size() == bt.size() && bw.size() == (size_t)(1 << set.size()) ? "Yes" : "No")
         << " (same members, different visit order)\n\n";

    cout << "[Edge Cases]\n";
    cout << "  empty set    : "; printSubsets(SubsetGenerator::generateBitwise({}));
    cout << "  single item  : "; printSubsets(SubsetGenerator::generateBitwise({7}));

    return 0;
}

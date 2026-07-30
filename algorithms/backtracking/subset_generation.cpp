#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Power set via backtracking. Unlike combinations/permutations there is no
// target-size base case: EVERY node on the recursion path is a valid subset, so
// we record the current subset at entry, then branch on include/exclude of each
// remaining element. Forward-only index avoids listing {1,2} and {2,1}.
class Subsets {
    void backtrack(int start, const vector<int>& elements,
                   vector<int>& cur, vector<vector<int>>& result) {
        result.push_back(cur);   // every prefix is a subset (incl. the empty one)
        for (int i = start; i < (int)elements.size(); ++i) {
            cur.push_back(elements[i]);              // choose
            backtrack(i + 1, elements, cur, result); // explore forward
            cur.pop_back();                           // un-choose
        }
    }
public:
    vector<vector<int>> generate(const vector<int>& elements) {
        vector<vector<int>> result;
        vector<int> cur;
        backtrack(0, elements, cur, result);
        return result;
    }
};

static void printSubsets(const vector<vector<int>>& subs) {
    int n = 1;
    for (const auto& s : subs) {
        cout << "    " << n++ << ": { ";
        for (int x : s) cout << x << " ";
        cout << "}\n";
    }
}

int main() {
    cout << "============= Subset Generation (Power Set) =============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n * 2^n)   2^n subsets, each copied in O(n)\n";
    cout << "  Space : O(n) recursion depth + O(n*2^n) to store results\n";
    cout << "  Note  : every path prefix is a subset; includes the empty set\n\n";

    cout << "[Demo]\n";
    vector<int> elements = {1, 2, 3};
    cout << "  set = { ";
    for (int x : elements) cout << x << " ";
    cout << "}\n";
    auto result = Subsets().generate(elements);
    printSubsets(result);
    cout << "  total = " << result.size() << "  (= 2^" << elements.size()
         << " = " << result.size() << ")\n\n";

    cout << "[Edge Cases]\n";
    cout << "  empty set -> only the empty subset:\n";
    printSubsets(Subsets().generate({}));
    cout << "  single element:\n";
    printSubsets(Subsets().generate({5}));
    cout << "\n";

    return 0;
}

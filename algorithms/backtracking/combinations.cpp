#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Combinations of size k chosen from `elements`, via classic backtracking.
// At each position we either include elements[i] and recurse forward, or skip it.
// The `start` index forces forward progress so each subset is listed once.
class Combinations {
    void backtrack(const vector<int>& elements, int k, int start,
                   vector<int>& cur, vector<vector<int>>& result) {
        if ((int)cur.size() == k) { result.push_back(cur); return; }
        for (int i = start; i < (int)elements.size(); ++i) {
            cur.push_back(elements[i]);        // choose
            backtrack(elements, k, i + 1, cur, result);  // explore forward
            cur.pop_back();                    // un-choose
        }
    }
public:
    vector<vector<int>> generate(const vector<int>& elements, int k) {
        vector<vector<int>> result;
        vector<int> cur;
        if (k < 0 || k > (int)elements.size()) return result;  // invalid -> empty
        backtrack(elements, k, 0, cur, result);
        return result;
    }
};

static void printCombos(const vector<vector<int>>& combos) {
    int n = 1;
    for (const auto& c : combos) {
        cout << "    " << n++ << ": [ ";
        for (int x : c) cout << x << " ";
        cout << "]\n";
    }
}

int main() {
    cout << "================ Combinations ================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(C(n,k) * k)   C(n,k) outputs, each copied in O(k)\n";
    cout << "  Space : O(k) recursion depth + O(C(n,k)*k) to store results\n";
    cout << "  Note  : choose/explore/un-choose; forward-only index prevents duplicates\n\n";

    cout << "[Demo]\n";
    vector<int> elements = {1, 2, 3, 4, 5};
    int k = 3;
    cout << "  set = { ";
    for (int x : elements) cout << x << " ";
    cout << "},  k = " << k << "\n";
    auto result = Combinations().generate(elements, k);
    printCombos(result);
    cout << "  total = " << result.size() << "  (C(" << elements.size()
         << "," << k << ") = " << result.size() << ")\n\n";

    cout << "[Edge Cases]\n";
    cout << "  k = 0 (empty combination): count = "
         << Combinations().generate({1, 2, 3}, 0).size() << "\n";
    cout << "  k > n (impossible): count = "
         << Combinations().generate({1, 2}, 5).size() << "\n";
    cout << "  k = n (one combination, all elements):\n";
    printCombos(Combinations().generate({1, 2, 3}, 3));
    cout << "  empty set, k = 0: count = "
         << Combinations().generate({}, 0).size() << "\n";
    cout << "\n";

    return 0;
}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// All permutations via in-place swapping (Heap's-style recursion).
// Fix elements[start] by swapping each j >= start into that slot, recurse to
// fix the next position, then swap back (un-choose) to restore order.
class Permutations {
    void backtrack(int start, vector<int>& elements, vector<vector<int>>& result) {
        if (start == (int)elements.size()) { result.push_back(elements); return; }
        for (int i = start; i < (int)elements.size(); ++i) {
            swap(elements[start], elements[i]);              // choose
            backtrack(start + 1, elements, result);          // explore
            swap(elements[start], elements[i]);              // un-choose
        }
    }
public:
    vector<vector<int>> generate(vector<int> elements) {  // by value: swap in a copy
        vector<vector<int>> result;
        if (elements.empty()) return result;
        backtrack(0, elements, result);
        return result;
    }
};

static void printPerms(const vector<vector<int>>& perms) {
    int n = 1;
    for (const auto& p : perms) {
        cout << "    " << n++ << ": [ ";
        for (int x : p) cout << x << " ";
        cout << "]\n";
    }
}

int main() {
    cout << "================ Permutations ================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n * n!)   n! permutations, each copied in O(n)\n";
    cout << "  Space : O(n) recursion depth + O(n*n!) to store results\n";
    cout << "  Note  : in-place swap; backtracking restores order after each branch\n\n";

    cout << "[Demo]\n";
    vector<int> elements = {1, 2, 3};
    cout << "  set = { ";
    for (int x : elements) cout << x << " ";
    cout << "}\n";
    auto result = Permutations().generate(elements);
    printPerms(result);
    cout << "  total = " << result.size() << "  (= " << elements.size() << "! = "
         << result.size() << ")\n\n";

    cout << "[Edge Cases]\n";
    cout << "  empty set: count = " << Permutations().generate({}).size() << "\n";
    cout << "  single element:\n";
    printPerms(Permutations().generate({7}));
    cout << "  two elements:\n";
    printPerms(Permutations().generate({4, 9}));
    cout << "\n";

    return 0;
}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Linear search: scan every element in order, return the first match.
// Works on ANY array (sorted or not).
int linearSearch(const vector<int>& arr, int target) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;  // not present
}

// ─── Demo helpers ───
static void printArray(const vector<int>& arr) {
    cout << "  array : ";
    if (arr.empty()) { cout << "(empty)\n"; return; }
    for (int x : arr) cout << x << " ";
    cout << "\n";
}

static void report(int target, int idx) {
    if (idx != -1)
        cout << "  target " << target << " -> Found at index " << idx << "\n";
    else
        cout << "  target " << target << " -> Not Found\n";
}

static void runSearch(const vector<int>& arr, int target) {
    report(target, linearSearch(arr, target));
}

int main() {
    cout << "==================== Linear Search ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(1)     target is the first element\n";
    cout << "  Average : O(n)\n";
    cout << "  Worst   : O(n)     target at the end, or absent\n";
    cout << "  Space   : O(1)\n";
    cout << "  Input   : any array (sorted or unsorted)\n\n";

    cout << "[Demo]  (unsorted array — no precondition needed)\n";
    vector<int> arr = {35, 12, 49, 8, 22, 60, 15};
    printArray(arr);
    runSearch(arr, 22);
    cout << "\n";

    cout << "[Searches]\n";
    runSearch(arr, 35);   // first element
    runSearch(arr, 15);   // last element
    runSearch(arr, 49);   // middle
    runSearch(arr, 99);   // absent
    cout << "\n";

    cout << "[Edge Cases]\n";
    runSearch({}, 5);                 // empty
    runSearch({42}, 42);              // single, present
    runSearch({42}, 7);               // single, absent
    runSearch({7, 7, 7, 7}, 7);       // all duplicates -> first index
    cout << "\n";

    return 0;
}

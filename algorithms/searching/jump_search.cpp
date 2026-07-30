#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

// Jump search on a SORTED array: jump forward by sqrt(n) steps until the
// block that could hold target is found, then linear-scan that block.
int jumpSearch(const vector<int>& arr, int target) {
    int n = (int)arr.size();
    if (n == 0) return -1;

    int step = (int)sqrt(n);
    int prev = 0;

    // Jump forward while the end of the current block is still < target.
    while (prev < n && arr[min(step, n) - 1] < target) {
        prev = step;
        step += (int)sqrt(n);
        if (prev >= n) return -1;  // target larger than every element
    }

    // Linear scan within the candidate block.
    while (prev < min(step, n)) {
        if (arr[prev] == target) return prev;
        prev++;
    }
    return -1;
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
    report(target, jumpSearch(arr, target));
}

int main() {
    cout << "==================== Jump Search ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(1)     target in the first block\n";
    cout << "  Average : O(sqrt(n))\n";
    cout << "  Worst   : O(sqrt(n))\n";
    cout << "  Space   : O(1)\n";
    cout << "  Input   : MUST be sorted\n\n";

    cout << "[Demo]  (sorted array, step = sqrt(n))\n";
    vector<int> arr = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610};
    printArray(arr);
    runSearch(arr, 55);
    cout << "\n";

    cout << "[Searches]\n";
    runSearch(arr, 0);     // first element
    runSearch(arr, 610);   // last element
    runSearch(arr, 21);    // mid
    runSearch(arr, 100);   // absent
    cout << "\n";

    cout << "[Edge Cases]\n";
    runSearch({}, 5);                  // empty
    runSearch({42}, 42);               // single, present
    runSearch({42}, 7);                // single, absent
    runSearch({1, 2, 3}, 0);           // below range
    runSearch({1, 2, 3}, 9);           // above range
    cout << "\n";

    return 0;
}

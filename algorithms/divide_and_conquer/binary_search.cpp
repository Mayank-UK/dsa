#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Divide-and-conquer applied to search: each step cuts the search space in half
// and keeps only the half that could contain the target. The "divide" is the
// mid split, the "conquer" is one recursive call on a single half, and there is
// no combine step — a binary decision collapses to one answer.
// (For the search-framed twin, see searching/binary_search.cpp.)

// Recursive D&C form. Returns the index of target in arr[low..high], or -1.
int binarySearchRec(const vector<int>& arr, int target, int low, int high) {
    if (low > high) return -1;                       // empty subproblem → miss

    int mid = low + (high - low) / 2;                // avoids overflow vs (low+high)/2
    if (arr[mid] == target) return mid;
    if (arr[mid] > target)
        return binarySearchRec(arr, target, low, mid - 1);   // keep left half
    return binarySearchRec(arr, target, mid + 1, high);      // keep right half
}

// Iterative equivalent — same D&C, constant stack (no recursion overhead).
int binarySearch(const vector<int>& arr, int target) {
    int low = 0, high = (int)arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else                   high = mid - 1;
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

// Human-readable lookup result against a sorted array.
static void runSearch(const string& label, const vector<int>& arr, int target) {
    int idx = binarySearch(arr, target);
    cout << "  " << label << " target=" << target << " : ";
    if (idx == -1) cout << "Not Found\n";
    else           cout << "Found at index " << idx << "\n";
}

int main() {
    cout << "=================== Binary Search (Divide & Conquer) ===================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(1)        target is the middle element\n";
    cout << "  Average : O(log n)    halves the search space each step\n";
    cout << "  Worst   : O(log n)\n";
    cout << "  Space   : O(1) iterative · O(log n) recursive (call stack)\n";
    cout << "  Notes   : REQUIRES a sorted array · divide step = mid split, no combine\n\n";

    cout << "[Precondition] array must be sorted ascending — the demo array is.\n";
    vector<int> arr = {2, 3, 4, 10, 40, 75, 100};
    printArray(arr);
    cout << "\n";

    cout << "[Demo] recursive form == iterative form (both D&C):\n";
    int target = 10;
    cout << "  recursive : target=" << target << " -> index "
         << binarySearchRec(arr, target, 0, (int)arr.size() - 1) << "\n";
    cout << "  iterative : target=" << target << " -> index "
         << binarySearch(arr, target) << "\n\n";

    cout << "[Searches]\n";
    runSearch("middle  ", arr, 10);
    runSearch("first   ", arr, 2);
    runSearch("last    ", arr, 100);
    runSearch("absent  ", arr, 50);
    cout << "\n";

    cout << "[Edge Cases]\n";
    runSearch("empty arr       ", {}, 5);
    runSearch("single present  ", {42}, 42);
    runSearch("single absent   ", {42}, 7);
    runSearch("below range     ", arr, 1);
    runSearch("above range     ", arr, 999);
    runSearch("duplicates      ", {1, 3, 3, 3, 5}, 3);  // some valid index, not guaranteed first
    cout << "\n";

    return 0;
}

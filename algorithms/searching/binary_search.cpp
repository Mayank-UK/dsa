#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Iterative binary search on a SORTED array. Returns the index of target,
// or -1 if absent. mid = low + (high-low)/2 avoids overflow vs (low+high)/2.
int binarySearch(const vector<int>& arr, int target) {
    int low = 0;
    int high = (int)arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            low = mid + 1;   // target is in the right half
        } else {
            high = mid - 1;  // target is in the left half
        }
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
    report(target, binarySearch(arr, target));
}

int main() {
    cout << "==================== Binary Search ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(1)     target is the middle element\n";
    cout << "  Average : O(log n)\n";
    cout << "  Worst   : O(log n)\n";
    cout << "  Space   : O(1)     iterative version\n";
    cout << "  Input   : MUST be sorted\n\n";

    cout << "[Demo]  (sorted array)\n";
    vector<int> arr = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    printArray(arr);
    runSearch(arr, 23);
    cout << "\n";

    cout << "[Searches]\n";
    runSearch(arr, 2);    // first element
    runSearch(arr, 91);   // last element
    runSearch(arr, 38);   // exact middle
    runSearch(arr, 50);   // absent, between values
    cout << "\n";

    cout << "[Edge Cases]\n";
    runSearch({}, 5);                 // empty
    runSearch({42}, 42);              // single, present
    runSearch({42}, 7);               // single, absent
    runSearch({1, 2, 3}, 0);          // below range
    runSearch({1, 2, 3}, 9);          // above range
    cout << "\n";

    return 0;
}

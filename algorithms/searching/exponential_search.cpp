#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Standard binary search over arr[low..high].
int binarySearch(const vector<int>& arr, int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Exponential (galloping) search on a SORTED array: double the index until
// passing the target, then binary-search the discovered range. Shines when
// the target is near the front, or in unbounded/infinite-size arrays.
int exponentialSearch(const vector<int>& arr, int target) {
    int n = (int)arr.size();
    if (n == 0) return -1;

    if (arr[0] == target) return 0;

    // Find the range [i/2, min(i, n-1)] that brackets target.
    int i = 1;
    while (i < n && arr[i] <= target) {
        i *= 2;
    }

    return binarySearch(arr, i / 2, min(i, n - 1), target);
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
    report(target, exponentialSearch(arr, target));
}

int main() {
    cout << "=============== Exponential Search ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(1)      target at index 0\n";
    cout << "  Average : O(log i)  i = index where target lives\n";
    cout << "  Worst   : O(log n)\n";
    cout << "  Space   : O(1)\n";
    cout << "  Input   : MUST be sorted\n";
    cout << "  Note    : ideal for unbounded streams / target near the front\n\n";

    cout << "[Demo]  (sorted array)\n";
    vector<int> arr = {2, 3, 4, 10, 40, 50, 75, 100, 150, 200};
    printArray(arr);
    runSearch(arr, 75);
    cout << "\n";

    cout << "[Searches]\n";
    runSearch(arr, 2);     // first element (fast path)
    runSearch(arr, 200);   // last element (gallops to the end)
    runSearch(arr, 10);    // near front
    runSearch(arr, 99);    // absent
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

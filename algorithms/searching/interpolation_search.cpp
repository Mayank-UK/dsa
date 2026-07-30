#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Interpolation search on a SORTED, roughly UNIFORM array. Instead of the
// midpoint, it estimates the probe position by linear interpolation, so on
// uniform data it homes in in ~O(log log n). Degrades to O(n) on clustered
// data (e.g. {1,2,3,1000}).
int interpolationSearch(const vector<int>& arr, int target) {
    int low = 0;
    int high = (int)arr.size() - 1;

    // Stay in range and only probe while target is within [arr[low], arr[high]].
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target) return low;
            return -1;
        }

        // Estimate where target likely sits, assuming uniform spacing.
        int pos = low + (int)(((double)(high - low) / (arr[high] - arr[low])) *
                              (target - arr[low]));

        if (arr[pos] == target) {
            return pos;
        }
        if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
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
    report(target, interpolationSearch(arr, target));
}

int main() {
    cout << "=============== Interpolation Search ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(1)\n";
    cout << "  Average : O(log log n)   uniformly distributed keys\n";
    cout << "  Worst   : O(n)           highly clustered / non-uniform keys\n";
    cout << "  Space   : O(1)\n";
    cout << "  Input   : MUST be sorted; performs best on uniform spacing\n\n";

    cout << "[Demo]  (uniformly spaced array)\n";
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    printArray(arr);
    runSearch(arr, 70);
    cout << "\n";

    cout << "[Searches]\n";
    runSearch(arr, 10);    // first element
    runSearch(arr, 100);   // last element
    runSearch(arr, 45);    // absent, mid-range
    runSearch(arr, 5);     // below range
    cout << "\n";

    cout << "[Edge Cases]\n";
    runSearch({}, 5);                  // empty
    runSearch({42}, 42);               // single, present
    runSearch({42}, 7);                // single, absent
    cout << "\n";

    cout << "[Degradation]\n";
    cout << "  Non-uniform input degrades toward O(n):\n";
    vector<int> clustered = {1, 2, 3, 1000, 2000, 3000};
    printArray(clustered);
    runSearch(clustered, 2000);
    cout << "\n";

    return 0;
}

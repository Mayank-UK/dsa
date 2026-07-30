#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Selection sort: repeatedly select the minimum of the unsorted tail
// and swap it into the next front position.
void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        // Find the minimum element in the unsorted suffix arr[i..n-1].
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the found minimum into position i (skip if already there).
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// ─── Demo helpers ───
static void printArray(const vector<int>& arr, const string& label) {
    cout << "  " << label << " : ";
    if (arr.empty()) { cout << "(empty)\n"; return; }
    for (int x : arr) cout << x << " ";
    cout << "\n";
}

static bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++)
        if (arr[i] < arr[i - 1]) return false;
    return true;
}

static void runCase(const string& name, vector<int> arr) {
    printArray(arr, name + " before");
    selectionSort(arr);
    printArray(arr, name + " after ");
}

int main() {
    cout << "==================== Selection Sort ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(n^2)   always scans the full unsorted tail\n";
    cout << "  Average : O(n^2)\n";
    cout << "  Worst   : O(n^2)\n";
    cout << "  Space   : O(1)     in-place\n";
    cout << "  Stable  : No       the long-distance swap can reorder equals\n";
    cout << "  Note    : minimizes swaps (at most n-1)\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {64, 25, 12, 22, 11};
    printArray(arr, "before");
    selectionSort(arr);
    printArray(arr, "after ");
    cout << "  Sorted correctly : " << (isSorted(arr) ? "Yes" : "No") << "\n\n";

    cout << "[Edge Cases]\n";
    runCase("empty       ", {});
    runCase("single      ", {42});
    runCase("duplicates  ", {5, 1, 5, 2, 1, 5});
    runCase("already sort", {1, 2, 3, 4, 5});
    runCase("reverse     ", {5, 4, 3, 2, 1});
    runCase("negatives   ", {0, -3, 8, -1, 4, -7});
    cout << "\n";

    return 0;
}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Optimized bubble sort: stops early once a full pass makes no swaps,
// proving the array is already sorted.
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;

        // Last i elements are already in their final positions.
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // No swaps means the array is sorted — nothing more to do.
        if (!swapped) {
            break;
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
    bubbleSort(arr);
    printArray(arr, name + " after ");
}

int main() {
    cout << "====================== Bubble Sort ======================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(n)     already sorted (early exit via swapped flag)\n";
    cout << "  Average : O(n^2)\n";
    cout << "  Worst   : O(n^2)   reverse-sorted input\n";
    cout << "  Space   : O(1)     in-place\n";
    cout << "  Stable  : Yes      equal keys keep their relative order\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    printArray(arr, "before");
    bubbleSort(arr);
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

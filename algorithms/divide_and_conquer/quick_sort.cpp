#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Divide-and-conquer quicksort. Divide = partition around a pivot so everything
// ≤ pivot is on its left and everything > pivot on its right; Conquer = recurse
// on the two partitions; Combine = nothing (the array is sorted once the
// partitions are — pivot lands in its final spot during partition).
// This is the "divide does the work, combine is free" counterpart to merge sort.
// (Sort-framed twin lives in sorting/quick_sort.cpp.)

// Lomuto partition: pivot = arr[high], returns pivot's final index.
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;                          // boundary of the ≤ pivot region
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);              // move pivot to its final spot
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);   // divide
        quickSort(arr, low, pi - 1);          // conquer left
        quickSort(arr, pi + 1, high);         // conquer right
        // no combine step
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
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i] < arr[i - 1]) return false;
    return true;
}

static void runCase(const string& name, vector<int> arr) {
    printArray(arr, name + " before");
    if (!arr.empty()) quickSort(arr, 0, (int)arr.size() - 1);
    printArray(arr, name + " after ");
    cout << "  Sorted correctly : " << (isSorted(arr) ? "Yes" : "No") << "\n";
}

int main() {
    cout << "=================== Quick Sort (Divide & Conquer) ===================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best / Average : O(n log n)   balanced partitions split the work evenly\n";
    cout << "  Worst          : O(n^2)       already-sorted input + last-element pivot\n";
    cout << "  Space          : O(log n) avg / O(n) worst  (recursion stack)\n";
    cout << "  Stable         : No           (Lomuto swaps can reorder equal keys)\n\n";

    cout << "[Demo] partition does the work, combine is a no-op:\n";
    vector<int> arr = {10, 7, 8, 9, 1, 5};
    printArray(arr, "before");
    quickSort(arr, 0, (int)arr.size() - 1);
    printArray(arr, "after ");
    cout << "  Sorted correctly : " << (isSorted(arr) ? "Yes" : "No") << "\n\n";

    cout << "[Edge Cases]\n";
    runCase("empty       ", {});
    runCase("single      ", {42});
    runCase("duplicates  ", {5, 1, 5, 2, 1, 5});
    runCase("already sort", {1, 2, 3, 4, 5});   // worst-case shape for last-elt pivot
    runCase("reverse     ", {5, 4, 3, 2, 1});
    runCase("negatives   ", {0, -3, 8, -1, 4, -7});
    cout << "\n";

    return 0;
}

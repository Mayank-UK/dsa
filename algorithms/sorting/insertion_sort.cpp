#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Insertion sort: grow a sorted prefix by inserting each next element
// into its correct position among those already sorted.
void insertionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Shift elements of the sorted prefix that are greater than key
        // one position to the right.
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Drop the key into the gap that opened up.
        arr[j + 1] = key;
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
    insertionSort(arr);
    printArray(arr, name + " after ");
}

int main() {
    cout << "==================== Insertion Sort ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(n)     already sorted (each key shifts zero)\n";
    cout << "  Average : O(n^2)\n";
    cout << "  Worst   : O(n^2)   reverse-sorted input\n";
    cout << "  Space   : O(1)     in-place\n";
    cout << "  Stable  : Yes\n";
    cout << "  Note    : excellent on small / nearly-sorted data\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {12, 11, 13, 5, 6};
    printArray(arr, "before");
    insertionSort(arr);
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

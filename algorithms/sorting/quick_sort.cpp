#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Lomuto partition: pick the last element as pivot, then move everything
// smaller to its left. Returns the pivot's final index.
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;  // right edge of the "smaller than pivot" region

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick sort over arr[low..high].
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // pivot is now in final place

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
    if (!arr.empty()) quickSort(arr, 0, (int)arr.size() - 1);
    printArray(arr, name + " after ");
}

int main() {
    cout << "===================== Quick Sort =====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(n log n)\n";
    cout << "  Average : O(n log n)\n";
    cout << "  Worst   : O(n^2)     already/reverse sorted with last-elem pivot\n";
    cout << "  Space   : O(log n)   recursion stack (O(n) in the worst case)\n";
    cout << "  Stable  : No         Lomuto partition swaps over long distances\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {10, 7, 8, 9, 1, 5};
    printArray(arr, "before");
    quickSort(arr, 0, (int)arr.size() - 1);
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

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Sift-down heapify: push arr[i] down within a max-heap of size n
// until the heap property (parent >= children) is restored.
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);  // keep sifting into the affected subtree
    }
}

// Heap sort: build a max-heap, then repeatedly swap the root (max) to the
// tail and re-heapify the shrinking prefix.
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build max-heap bottom-up from the last internal node.
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract maxima one by one into the sorted tail.
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
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
    heapSort(arr);
    printArray(arr, name + " after ");
}

int main() {
    cout << "===================== Heap Sort =====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(n log n)\n";
    cout << "  Average : O(n log n)\n";
    cout << "  Worst   : O(n log n)\n";
    cout << "  Space   : O(1)     in-place (O(log n) recursion stack)\n";
    cout << "  Stable  : No       heap swaps can reorder equal keys\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    printArray(arr, "before");
    heapSort(arr);
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

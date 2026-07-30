#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Merge two sorted sub-arrays arr[left..mid] and arr[mid+1..right] into one.
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temp buffers for the two halves.
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Interleave the two halves back into arr, smallest first.
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    // Drain whichever half still has elements.
    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

// Top-down merge sort over arr[left..right].
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // avoids overflow vs (l+r)/2

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
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
    if (!arr.empty()) mergeSort(arr, 0, (int)arr.size() - 1);
    printArray(arr, name + " after ");
}

int main() {
    cout << "===================== Merge Sort =====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(n log n)\n";
    cout << "  Average : O(n log n)\n";
    cout << "  Worst   : O(n log n)\n";
    cout << "  Space   : O(n)     temp buffers for each merge\n";
    cout << "  Stable  : Yes      (<= keeps left element first on ties)\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    printArray(arr, "before");
    mergeSort(arr, 0, (int)arr.size() - 1);
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

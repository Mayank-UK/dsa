#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int MIN_RUN = 32;

// Insertion sort over the slice arr[left..right] (used on small runs).
void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Merge two sorted runs arr[l..m] and arr[m+1..r].
void merge(vector<int>& arr, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    vector<int> leftArr(len1), rightArr(len2);

    for (int i = 0; i < len1; i++) leftArr[i] = arr[l + i];
    for (int i = 0; i < len2; i++) rightArr[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else                            arr[k++] = rightArr[j++];
    }
    while (i < len1) arr[k++] = leftArr[i++];
    while (j < len2) arr[k++] = rightArr[j++];
}

// Timsort (simplified): insertion-sort MIN_RUN-sized chunks, then bottom-up
// merge them with doubling merge width. (Real Timsort also stacks runs in a
// galloping merge stack; this is the common textbook core.)
void timSort(vector<int>& arr) {
    int n = arr.size();

    // Phase 1: insertion-sort every MIN_RUN-sized slice.
    for (int i = 0; i < n; i += MIN_RUN)
        insertionSort(arr, i, min(i + MIN_RUN - 1, n - 1));

    // Phase 2: merge runs of growing width (MIN_RUN, 2*MIN_RUN, ...).
    for (int size = MIN_RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);

            if (mid < right)
                merge(arr, left, mid, right);
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
    timSort(arr);
    printArray(arr, name + " after ");
}

int main() {
    cout << "===================== Tim Sort =====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(n)       already sorted (runs detected, merge skipped)\n";
    cout << "  Average : O(n log n)\n";
    cout << "  Worst   : O(n log n)\n";
    cout << "  Space   : O(n)       temp buffers for each merge\n";
    cout << "  Stable  : Yes\n";
    cout << "  Note    : hybrid of insertion sort (small runs) + merge sort\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {5, 21, 7, 23, 19, 3, 1, 35, 12, 18};
    printArray(arr, "before");
    timSort(arr);
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

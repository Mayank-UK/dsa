#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Divide-and-conquer merge sort. Divide = split at the midpoint into two halves;
// Conquer = recursively sort each half; Combine = linear merge of the two sorted
// halves. The combine step is what makes this the canonical "divide THEN merge"
// example (and where its O(n) temp buffers come from).
// (Sort-framed twin with the same logic lives in sorting/merge_sort.cpp.)

// Merge two sorted sub-arrays arr[left..mid] and arr[mid+1..right] into one.
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);                       // temp buffers for the two halves
    vector<int> R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {               // interleave, smallest first
        if (L[i] <= R[j]) arr[k++] = L[i++]; // <= keeps left first on ties → stable
        else              arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];        // drain leftovers
    while (j < n2) arr[k++] = R[j++];
}

// Top-down divide-and-conquer over arr[left..right].
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;               // base case: 0 or 1 element

    int mid = left + (right - left) / 2;     // avoids overflow vs (l+r)/2
    mergeSort(arr, left, mid);               // conquer left
    mergeSort(arr, mid + 1, right);          // conquer right
    merge(arr, left, mid, right);            // combine
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
    if (!arr.empty()) mergeSort(arr, 0, (int)arr.size() - 1);
    printArray(arr, name + " after ");
    cout << "  Sorted correctly : " << (isSorted(arr) ? "Yes" : "No") << "\n";
}

int main() {
    cout << "=================== Merge Sort (Divide & Conquer) ===================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best / Average / Worst : O(n log n)   divides log n deep, merges O(n) each\n";
    cout << "  Space                  : O(n)         temp buffers per merge\n";
    cout << "  Stable                 : Yes          (<= keeps left element first on ties)\n\n";

    cout << "[Demo] the combine (merge) step is the lesson:\n";
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

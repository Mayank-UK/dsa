#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Shell sort: gapped insertion sort with a shrinking gap (n/2, n/4, ..., 1).
// Large gaps pre-sort far-apart elements so the final gap=1 pass is cheap.
void shellSort(vector<int>& arr) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Gapped insertion sort for this gap size.
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;

            // Shift earlier gap-sorted elements right until temp's slot opens.
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = temp;
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
    shellSort(arr);
    printArray(arr, name + " after ");
}

int main() {
    cout << "===================== Shell Sort =====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(n log n)   with good gap sequences\n";
    cout << "  Average : depends on gap sequence (here: n/2, n/4, ...)\n";
    cout << "  Worst   : O(n^2)       for the simple halving gap sequence\n";
    cout << "  Space   : O(1)         in-place\n";
    cout << "  Stable  : No           gapped inserts cross equal keys\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {12, 34, 54, 2, 3};
    printArray(arr, "before");
    shellSort(arr);
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

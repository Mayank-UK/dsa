#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Counting sort for NON-NEGATIVE integers. Counts frequencies, turns them
// into prefix sums (final positions), then scatters backward for stability.
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());

    vector<int> count(maxVal + 1, 0);

    // Frequency of each value.
    for (int x : arr) count[x]++;

    // Prefix sums: count[v] is now the count of values <= v.
    for (int v = 1; v <= maxVal; v++)
        count[v] += count[v - 1];

    // Build output by walking the input backward (keeps it stable).
    vector<int> output(arr.size());
    for (int i = (int)arr.size() - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    arr = output;
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
    countingSort(arr);
    printArray(arr, name + " after ");
}

int main() {
    cout << "==================== Counting Sort ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(n + k)   k = max value\n";
    cout << "  Average : O(n + k)\n";
    cout << "  Worst   : O(n + k)\n";
    cout << "  Space   : O(n + k)   count array + output\n";
    cout << "  Stable  : Yes        (backward scatter preserves order)\n";
    cout << "  Note    : keys must be non-negative integers in a small range\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};
    printArray(arr, "before");
    countingSort(arr);
    printArray(arr, "after ");
    cout << "  Sorted correctly : " << (isSorted(arr) ? "Yes" : "No") << "\n\n";

    cout << "[Edge Cases]\n";
    runCase("empty       ", {});
    runCase("single      ", {42});
    runCase("duplicates  ", {5, 1, 5, 2, 1, 5});
    runCase("already sort", {1, 2, 3, 4, 5});
    runCase("reverse     ", {9, 7, 5, 3, 1});
    runCase("all same    ", {4, 4, 4, 4});
    cout << "\n";

    cout << "[Limitation]\n";
    cout << "  This implementation handles only non-negative integers.\n";
    cout << "  Negative keys need an offset by -min before counting.\n\n";

    return 0;
}

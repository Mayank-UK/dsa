#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Stable counting sort of arr by the digit at place exp (1, 10, 100, ...).
void countingSortByDigit(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    // Frequency of each digit 0..9 at this place.
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Prefix sums -> final positions.
    for (int d = 1; d < 10; d++)
        count[d] += count[d - 1];

    // Scatter backward to keep the previous (lower) digit ordering intact.
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// Radix sort: stable sort each decimal digit, least significant first.
// Handles non-negative integers only.
void radixSort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());  // drives digit count

    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortByDigit(arr, exp);
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
    radixSort(arr);
    printArray(arr, name + " after ");
}

int main() {
    cout << "===================== Radix Sort =====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(d * (n + k))   d = digits, k = base (10)\n";
    cout << "  Average : O(d * n)\n";
    cout << "  Worst   : O(d * n)\n";
    cout << "  Space   : O(n + k)\n";
    cout << "  Stable  : Yes              each pass is a stable counting sort\n";
    cout << "  Note    : keys must be non-negative integers\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    printArray(arr, "before");
    radixSort(arr);
    printArray(arr, "after ");
    cout << "  Sorted correctly : " << (isSorted(arr) ? "Yes" : "No") << "\n\n";

    cout << "[Edge Cases]\n";
    runCase("empty       ", {});
    runCase("single      ", {42});
    runCase("duplicates  ", {7, 7, 3, 7, 3});
    runCase("already sort", {1, 2, 300, 4000});
    runCase("reverse     ", {900, 80, 7, 3, 1});
    runCase("vary width  ", {1, 100, 22, 9, 3050});
    cout << "\n";

    cout << "[Limitation]\n";
    cout << "  Handles only non-negative integers.\n";
    cout << "  Negative keys need a sign split or an offset.\n\n";

    return 0;
}

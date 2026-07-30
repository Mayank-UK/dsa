#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;

// Quickselect (randomized) — find the k-th smallest element in EXPECTED O(n),
// faster than sorting (O(n log n)) when you only need one order statistic. Same
// random-pivot partition as randomized_quick_sort.cpp, but it recurses into
// ONLY the side that contains k — so it discards ~half each step: n + n/2 +
// n/4 + ... = 2n. The random pivot again kills the O(n^2) killer-input case.

// Partition arr[low..high] around a random pivot; returns its final index.
static int partition(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// k-th smallest (1-indexed) within arr[low..high]. Reorders arr.
static int randomizedSelect(vector<int>& arr, int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        int pi = partition(arr, low, high);

        if (pi - low == k - 1)            // pivot IS the k-th smallest
            return arr[pi];

        if (pi - low > k - 1)             // k-th is in the left part
            return randomizedSelect(arr, low, pi - 1, k);

        return randomizedSelect(arr, pi + 1, high, k - (pi - low + 1));  // right part
    }
    return -1;  // k out of range
}

static void runCase(const string& label, const vector<int>& original, int k) {
    vector<int> arr = original;
    int got = (arr.empty() || k < 1 || k > (int)arr.size())
              ? -1
              : randomizedSelect(arr, 0, (int)arr.size() - 1, k);

    // Independent check: sort a copy and read index k-1.
    vector<int> sorted = original;
    sort(sorted.begin(), sorted.end());
    int expect = (arr.empty() || k < 1 || k > (int)arr.size())
                 ? -1 : sorted[k - 1];

    cout << "  " << label << ", k=" << k << " -> " << got
         << "  [sort-check " << expect << ": "
         << (got == expect ? "agree" : "DISAGREE") << "]\n";
}

int main() {
    srand((unsigned)time(nullptr));

    cout << "=============== Randomized Select (Quickselect) ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Average : O(n)       n + n/2 + n/4 + ... = 2n (recurses into one side only)\n";
    cout << "  Worst   : O(n^2)     astronomically unlikely with a random pivot\n";
    cout << "  Space   : O(log n)   recursion stack\n";
    cout << "  Notes   : partial-order; faster than a full sort for a single statistic.\n\n";

    cout << "[Demo]  arr = {10,4,5,8,6,11,26}\n";
    vector<int> arr = {10, 4, 5, 8, 6, 11, 26};
    runCase("3rd smallest",   arr, 3);   // 6
    runCase("minimum (k=1)",  arr, 1);   // 4
    runCase("maximum (k=7)",  arr, 7);   // 26
    runCase("median (k=4)",   arr, 4);   // 8

    cout << "\n[Edge Cases]\n";
    runCase("single element {42}",       {42}, 1);
    runCase("k out of range",            arr, 0);
    runCase("k out of range",            arr, 99);
    runCase("duplicates {7,7,7,7}",      {7, 7, 7, 7}, 2);

    cout << "\n[Note]\n";
    cout << "  Same random-pivot partition as randomized_quick_sort.cpp, but only one\n";
    cout << "  branch is taken per level. The deterministic median-of-medians variant\n";
    cout << "  guarantees O(n) WORST case at the cost of a larger constant.\n";

    return 0;
}

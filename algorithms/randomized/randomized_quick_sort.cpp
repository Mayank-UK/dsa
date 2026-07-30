#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;

// Lomuto partition, but the pivot is chosen at RANDOM (not always the last
// element). Randomizing the pivot makes the O(n^2) worst case (already/reverse
// sorted input, or a killer sequence crafted against deterministic quicksort)
// vanish in expectation: E[time] = O(n log n) on ANY input, and the bad case
// becomes a measure-zero event rather than a reliable attack.

// Partition arr[low..high] around a random pivot; returns its final index.
static int partition(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);   // random pivot
    swap(arr[randomIndex], arr[high]);                    // move it to the end

    int pivot = arr[high];
    int i = low - 1;                                      // right edge of "<= pivot"

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Randomized quicksort over arr[low..high].
static void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

// ─── Demo helpers ───
static void printArray(const vector<int>& arr, const string& label) {
    cout << "  " << label << " : ";
    if (arr.empty()) { cout << "(empty)"; }
    for (int x : arr) cout << x << " ";
    cout << "\n";
}

static bool isSorted(const vector<int>& arr) {
    for (int i = 1; i < (int)arr.size(); i++)
        if (arr[i] < arr[i - 1]) return false;
    return true;
}

static void runCase(const string& name, vector<int> arr) {
    printArray(arr, name + " before");
    if (!arr.empty()) randomizedQuickSort(arr, 0, (int)arr.size() - 1);
    printArray(arr, name + " after ");
    cout << "  Sorted correctly: " << (isSorted(arr) ? "Yes" : "No") << "\n\n";
}

int main() {
    srand((unsigned)time(nullptr));

    cout << "=============== Randomized Quick Sort ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(n log n)\n";
    cout << "  Average : O(n log n)   expected, on ANY input (random pivot)\n";
    cout << "  Worst   : O(n^2)        astronomically unlikely — no killer input\n";
    cout << "  Space   : O(log n)      recursion stack (O(n) worst case)\n";
    cout << "  Stable  : No            (Lomuto swap can reorder equal keys)\n\n";

    cout << "[Demo]\n";
    runCase("mixed",          {10, 7, 8, 9, 1, 5, 3, 2, 6, 4});

    cout << "[Edge Cases]\n";
    runCase("empty",          {});
    runCase("single",         {42});
    runCase("duplicates",     {5, 5, 5, 5, 5});
    runCase("already sorted", {1, 2, 3, 4, 5});   // deterministic quicksort's nemesis
    runCase("reverse sorted", {5, 4, 3, 2, 1});   // ditto
    runCase("negatives",      {-3, 7, -1, 0, 4, -8});

    cout << "[Note]\n";
    cout << "  The deterministic version (deterministic last-element pivot) hits O(n^2)\n";
    cout << "  on sorted/reverse input; the random pivot removes that attack surface.\n";
    cout << "  See sorting/quick_sort.cpp for the base algorithm and divide_and_conquer/\n";
    cout << "  quick_sort.cpp for the D&C framing.\n";

    return 0;
}

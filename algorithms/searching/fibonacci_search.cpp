#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Fibonacci search on a SORTED array. Uses Fibonacci numbers to split the
// range instead of computing mid, so it only needs +/- comparisons (no
// division) — historically useful on older hardware.
int fibonacciSearch(const vector<int>& arr, int target) {
    int n = (int)arr.size();
    if (n == 0) return -1;

    // fib2 = F(k-2), fib1 = F(k-1), fibK = F(k)
    int fib2 = 0;
    int fib1 = 1;
    int fibK = fib2 + fib1;

    // Smallest Fibonacci number >= n.
    while (fibK < n) {
        fib2 = fib1;
        fib1 = fibK;
        fibK = fib2 + fib1;
    }

    int offset = -1;  // eliminated range from the front

    while (fibK > 1) {
        int i = min(offset + fib2, n - 1);

        if (arr[i] < target) {
            // Drop the range below i: move one step down the Fibonacci ladder.
            fibK = fib1;
            fib1 = fib2;
            fib2 = fibK - fib1;
            offset = i;
        } else if (arr[i] > target) {
            // Drop the range above i: move two steps down.
            fibK = fib2;
            fib1 = fib1 - fib2;
            fib2 = fibK - fib1;
        } else {
            return i;
        }
    }

    // One last element to compare.
    if (fib1 && offset + 1 < n && arr[offset + 1] == target) {
        return offset + 1;
    }
    return -1;
}

// ─── Demo helpers ───
static void printArray(const vector<int>& arr) {
    cout << "  array : ";
    if (arr.empty()) { cout << "(empty)\n"; return; }
    for (int x : arr) cout << x << " ";
    cout << "\n";
}

static void report(int target, int idx) {
    if (idx != -1)
        cout << "  target " << target << " -> Found at index " << idx << "\n";
    else
        cout << "  target " << target << " -> Not Found\n";
}

static void runSearch(const vector<int>& arr, int target) {
    report(target, fibonacciSearch(arr, target));
}

int main() {
    cout << "================= Fibonacci Search =================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(1)\n";
    cout << "  Average : O(log n)\n";
    cout << "  Worst   : O(log n)\n";
    cout << "  Space   : O(1)\n";
    cout << "  Input   : MUST be sorted\n";
    cout << "  Note    : splits via Fibonacci numbers — no division needed\n\n";

    cout << "[Demo]  (sorted array)\n";
    vector<int> arr = {10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100};
    printArray(arr);
    runSearch(arr, 85);
    cout << "\n";

    cout << "[Searches]\n";
    runSearch(arr, 10);    // first element
    runSearch(arr, 100);   // last element
    runSearch(arr, 45);    // mid
    runSearch(arr, 60);    // absent
    cout << "\n";

    cout << "[Edge Cases]\n";
    runSearch({}, 5);                  // empty
    runSearch({42}, 42);               // single, present
    runSearch({42}, 7);                // single, absent
    runSearch({1, 2, 3}, 0);           // below range
    runSearch({1, 2, 3}, 9);           // above range
    cout << "\n";

    return 0;
}

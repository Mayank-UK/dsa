#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Ternary search for the MAXIMUM of a unimodal array (strictly increasing
// then strictly decreasing). Split [low, high] into thirds at m1 < m2 and
// keep the half that must contain the peak. Returns the peak value.
double ternarySearchPeak(const vector<double>& arr) {
    int low = 0;
    int high = (int)arr.size() - 1;

    // Narrow until at most 3 candidates remain. Guard is > 2 (not > 1):
    // at span 2 the two third-points collapse to the endpoints and the loop
    // would not narrow — an infinite loop on monotonic input.
    while (high - low > 2) {
        int m1 = low + (high - low) / 3;
        int m2 = high - (high - low) / 3;

        if (arr[m1] < arr[m2]) {
            low = m1;   // peak lies to the right of m1
        } else {
            high = m2;  // peak lies to the left of m2
        }
    }

    // Scan the small remainder (at most 3 elements) for the true peak.
    double peak = arr[low];
    for (int i = low + 1; i <= high; i++) {
        if (arr[i] > peak) peak = arr[i];
    }
    return peak;
}

// ─── Demo helpers ───
static void printArray(const vector<double>& arr) {
    cout << "  array : ";
    if (arr.empty()) { cout << "(empty)\n"; return; }
    for (double x : arr) cout << x << " ";
    cout << "\n";
}

static void runPeak(const vector<double>& arr) {
    if (arr.empty()) { cout << "  peak  -> (empty array)\n"; return; }
    cout << "  peak  -> " << ternarySearchPeak(arr) << "\n";
}

int main() {
    cout << "=================== Ternary Search ===================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(1)\n";
    cout << "  Average : O(log base 3 of n)\n";
    cout << "  Worst   : O(log base 3 of n)   fewer iterations than binary,\n";
    cout << "                                    but more comparisons per step\n";
    cout << "  Space   : O(1)\n";
    cout << "  Input   : unimodal (increasing then decreasing)\n\n";

    cout << "[Demo]  (unimodal array — peak = maximum)\n";
    vector<double> arr = {1.2, 3.4, 5.6, 8.9, 12.1, 10.5, 7.2, 4.1};
    printArray(arr);
    runPeak(arr);
    cout << "\n";

    cout << "[Searches]\n";
    runPeak({0, 1, 5, 9, 4, 2});             // peak in middle
    runPeak({9, 7, 5, 3, 1});                // strictly decreasing -> first
    runPeak({1, 2, 3, 4, 5});                // strictly increasing -> last
    cout << "\n";

    cout << "[Edge Cases]\n";
    runPeak({});                             // empty
    runPeak({42.0});                         // single element
    runPeak({5.0, 5.0});                     // two equal elements
    runPeak({-3.0, -1.0, -8.0});             // negative unimodal
    cout << "\n";

    return 0;
}

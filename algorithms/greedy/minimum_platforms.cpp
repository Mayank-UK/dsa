#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Greedy: sort arrivals and departures independently, then sweep events in time
// order. Each arrival (+1 platform) and departure (-1 platform) is consumed in
// chronological order; the running max is the answer.
int findMinPlatforms(vector<int> arr, vector<int> dep) {
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());

    int n = (int)arr.size();
    int platforms = 0, maxPlatforms = 0;
    int i = 0, j = 0;
    while (i < n && j < n) {
        // <= : a train arriving exactly when another departs still needs its own
        // platform until the departure completes (same-minute overlap).
        if (arr[i] <= dep[j]) {
            platforms++;
            i++;
        } else {
            platforms--;
            j++;
        }
        maxPlatforms = max(maxPlatforms, platforms);
    }
    return maxPlatforms;
}

int main() {
    cout << "=============== Minimum Platforms ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n log n)   sorting both arrays\n";
    cout << "  Space : O(1) extra  (in-place sort of copies)\n";
    cout << "  Note  : greedy chronological event sweep; max concurrent trains\n\n";

    cout << "[Demo]\n";
    vector<int> arrival   = {900, 940, 950, 1100, 1500, 1800};
    vector<int> departure = {910, 1200, 1120, 1130, 1900, 2000};
    cout << "  arrivals   = ";
    for (int a : arrival)   cout << a << " ";
    cout << "\n  departures = ";
    for (int d : departure) cout << d << " ";
    cout << "\n";
    cout << "  minimum platforms = " << findMinPlatforms(arrival, departure) << "\n\n";

    cout << "[Edge Cases]\n";
    cout << "  no trains      : " << findMinPlatforms({}, {}) << "\n";
    cout << "  one train      : " << findMinPlatforms({100}, {200}) << "\n";
    cout << "  all at once    : " << findMinPlatforms({100, 100, 100}, {200, 200, 200}) << "\n";
    cout << "  no overlap (1) : " << findMinPlatforms({100, 300, 500}, {200, 400, 600}) << "\n";
    cout << "  back-to-back (1): "
         << findMinPlatforms({100, 200, 300}, {200, 300, 400}) << "  (arr <= dep ties)\n";
    cout << "\n";

    return 0;
}

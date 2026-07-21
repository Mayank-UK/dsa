#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the minimum number of platforms required
int findMinPlatforms(vector<int>& arr, vector<int>& dep) {
    int n = arr.size();

    // Step 1: Sort arrival and departure arrays independently
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());

    int platformsNeeded = 0;
    int maxPlatforms = 0;
    int i = 0; // Pointer for arrivals
    int j = 0; // Pointer for departures

    // Step 2: Traverse through all events using two pointers
    while (i < n && j < n) {
        // If arrival time is less than or equal to departure, a new platform is needed
        if (arr[i] <= dep[j]) {
            platformsNeeded++;
            i++;
        } else {
            // A train has departed, free up a platform
            platformsNeeded--;
            j++;
        }

        // Track the maximum platforms needed at any given time
        maxPlatforms = max(maxPlatforms, platformsNeeded);
    }

    return maxPlatforms;
}

int main() {
    // Arrival and departure times (represented in 24-hour format, e.g., 900 = 09:00 AM)
    vector<int> arrival = {900, 940, 950, 1100, 1500, 1800};
    vector<int> departure = {910, 1200, 1120, 1130, 1900, 2000};

    int minPlatforms = findMinPlatforms(arrival, departure);
    cout << "Minimum number of platforms required: " << minPlatforms << "\n";

    return 0;
}
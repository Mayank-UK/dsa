#include <iostream>
#include <vector>

using namespace std;

// Function to perform interpolation search on a uniformly distributed sorted array
int interpolationSearch(const vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    // Check if array is non-empty and target is within range
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // If low and high boundaries point to the same element
        if (low == high) {
            if (arr[low] == target) return low;
            return -1;
        }

        // Probing the position using interpolation formula
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]));

        // Check if target is found at estimated position
        if (arr[pos] == target) {
            return pos;
        }

        // If target is larger, target is in the upper part
        if (arr[pos] < target) {
            low = pos + 1;
        }
        // If target is smaller, target is in the lower part
        else {
            high = pos - 1;
        }
    }

    return -1; // Target not found
}

int main() {
    // Uniformly distributed sorted array
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int target = 70;

    int resultIndex = interpolationSearch(arr, target);

    if (resultIndex != -1) {
        cout << "Element " << target << " found at index " << resultIndex << ".\n";
    } else {
        cout << "Element " << target << " not found in the array.\n";
    }

    return 0;
}
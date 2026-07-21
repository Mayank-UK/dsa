#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Standard binary search helper function
int binarySearch(const vector<int>& arr, int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Exponential search function for sorted arrays
int exponentialSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    if (n == 0) return -1;

    // If target is present at the first index itself
    if (arr[0] == target) return 0;

    // Find range for binary search by repeated doubling
    int i = 1;
    while (i < n && arr[i] <= target) {
        i *= 2;
    }

    // Call binary search for the found subarray range
    return binarySearch(arr, i / 2, min(i, n - 1), target);
}

int main() {
    vector<int> arr = {2, 3, 4, 10, 40, 50, 75, 100, 150, 200};
    int target = 75;

    int resultIndex = exponentialSearch(arr, target);

    if (resultIndex != -1) {
        cout << "Element " << target << " found at index " << resultIndex << ".\n";
    } else {
        cout << "Element " << target << " not found in the array.\n";
    }

    return 0;
}
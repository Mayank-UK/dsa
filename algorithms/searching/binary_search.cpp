#include <iostream>
#include <vector>

using namespace std;

// Function to perform binary search on a sorted array
int binarySearch(const vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        // Prevent potential integer overflow for large indices
        int mid = low + (high - low) / 2;

        // Check if target is present at mid
        if (arr[mid] == target) {
            return mid;
        }

        // If target is greater, ignore left half
        if (arr[mid] < target) {
            low = mid + 1;
        }
        // If target is smaller, ignore right half
        else {
            high = mid - 1;
        }
    }

    // Target was not present in the array
    return -1;
}

int main() {
    vector<int> arr = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int target = 23;

    int resultIndex = binarySearch(arr, target);

    if (resultIndex != -1) {
        cout << "Element " << target << " found at index " << resultIndex << ".\n";
    } else {
        cout << "Element " << target << " not found in the array.\n";
    }

    return 0;
}
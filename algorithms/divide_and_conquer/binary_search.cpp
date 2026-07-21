#include <iostream>
#include <vector>

using namespace std;

// Iterative binary search function
// Returns the index of the target if found, otherwise returns -1
int binarySearch(const vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        // Prevent potential integer overflow for extremely large arrays
        int mid = low + (high - low) / 2;

        // Check if target is present at mid
        if (arr[mid] == target) {
            return mid;
        }

        // If target is greater, ignore the left half
        if (arr[mid] < target) {
            low = mid + 1;
        }
        // If target is smaller, ignore the right half
        else {
            high = mid - 1;
        }
    }

    // Element was not present in the array
    return -1;
}

int main() {
    vector<int> arr = {2, 3, 4, 10, 40, 75, 100};
    int target = 10;

    int result = binarySearch(arr, target);

    if (result != -1) {
        cout << "Element found at index " << result << "\n";
    } else {
        cout << "Element not found in the array.\n";
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Function to perform jump search on a sorted array
int jumpSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    if (n == 0) return -1;

    // Finding optimal block size to jump (sqrt(n))
    int step = sqrt(n);

    // Finding the block where element is present (if it exists)
    int prev = 0;
    while (prev < n && arr[min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1; // Element is outside the array range
    }

    // Doing a linear search for target in the identified block
    while (prev < min(step, n)) {
        if (arr[prev] == target) {
            return prev;
        }
        prev++;
    }

    return -1; // Element not found
}

int main() {
    vector<int> arr = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610};
    int target = 55;

    int resultIndex = jumpSearch(arr, target);

    if (resultIndex != -1) {
        cout << "Element " << target << " found at index " << resultIndex << ".\n";
    } else {
        cout << "Element " << target << " not found in the array.\n";
    }

    return 0;
}
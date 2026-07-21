#include <iostream>
#include <vector>

using namespace std;

// Function to perform linear search on an array
int linearSearch(const vector<int>& arr, int target) {
    int n = arr.size();

    // Sequentially check every element in the array
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i; // Return the index where target is found
        }
    }

    // Element not present in the array
    return -1;
}

int main() {
    vector<int> arr = {35, 12, 49, 8, 22, 60, 15};
    int target = 22;

    int resultIndex = linearSearch(arr, target);

    if (resultIndex != -1) {
        cout << "Element " << target << " found at index " << resultIndex << ".\n";
    } else {
        cout << "Element " << target << " not found in the array.\n";
    }

    return 0;
}
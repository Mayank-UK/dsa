#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to perform counting sort on non-negative integers
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    // Find the maximum element to determine the range K
    int maxVal = *max_element(arr.begin(), arr.end());

    // Create a count array to store the frequencies of each element
    vector<int> count(maxVal + 1, 0);

    // Store the count of each element
    for (int i = 0; i < arr.size(); i++) {
        count[arr[i]]++;
    }

    // Change count[i] so that count[i] contains the actual position of this element in output array
    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }

    // Create the output array
    vector<int> output(arr.size());

    // Build the output array (traverse backward to maintain stability)
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy the sorted elements back into the original array
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

int main() {
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};

    cout << "Original array:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    countingSort(arr);

    cout << "Sorted array using Counting Sort:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}
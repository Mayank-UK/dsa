#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Partition function (same as in Randomized QuickSort)
int partition(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Randomized Select function to find the k-th smallest element (1-indexed k)
int randomizedSelect(vector<int>& arr, int low, int high, int k) {
    // If k is smaller than number of elements in current subarray
    if (k > 0 && k <= high - low + 1) {
        // Partition the array around a random pivot
        int pi = partition(arr, low, high);

        // If position matches k-1 (0-indexed pivot position)
        if (pi - low == k - 1) {
            return arr[pi];
        }

        // If position is greater than k-1, recurse on the left subarray
        if (pi - low > k - 1) {
            return randomizedSelect(arr, low, pi - 1, k);
        }

        // Otherwise, recurse on the right subarray (adjusting k)
        return randomizedSelect(arr, pi + 1, high, k - (pi - low + 1));
    }

    return -1; // Out of bounds
}

int main() {
    srand(time(nullptr));

    vector<int> arr = {10, 4, 5, 8, 6, 11, 26};
    int n = arr.size();
    int k = 3; // Find the 3rd smallest element

    // Copy array since randomizedSelect modifies order
    vector<int> tempArr = arr;
    int kthSmallest = randomizedSelect(tempArr, 0, n - 1, k);

    cout << "Array elements: ";
    for (int num : arr) cout << num << " ";
    cout << "\n";

    cout << "The " << k << "-rd smallest element is: " << kthSmallest << "\n";

    return 0;
}
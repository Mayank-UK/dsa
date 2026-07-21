#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Function to partition the array around a random pivot
int partition(vector<int>& arr, int low, int high) {
    // Select a random index between low and high
    int randomIndex = low + rand() % (high - low + 1);
    
    // Swap the randomly chosen pivot with the last element
    swap(arr[randomIndex], arr[high]);
    
    int pivot = arr[high];
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Randomized QuickSort helper function
void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partition the array around a random pivot
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

int main() {
    // Seed the random number generator
    srand(time(nullptr));

    vector<int> arr = {10, 7, 8, 9, 1, 5, 3, 2, 6, 4};
    int n = arr.size();

    cout << "Original array:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    randomizedQuickSort(arr, 0, n - 1);

    cout << "Sorted array using Randomized QuickSort:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}
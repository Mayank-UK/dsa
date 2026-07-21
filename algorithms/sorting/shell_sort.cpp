#include <iostream>
#include <vector>

using namespace std;

// Function to perform shell sort using the classic shell gap sequence (n/2)
void shellSort(vector<int>& arr) {
    int n = arr.size();

    // Start with a large gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements arr[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is gap-sorted
        for (int i = gap; i < n; i++) {
            // Add arr[i] to the elements that have been gap sorted
            // save arr[i] in a variable and make a hole at position i
            int temp = arr[i];
            int j;

            // Shift earlier gap-sorted elements up until the correct location for arr[i] is found
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            // Put temp (the original arr[i]) in its correct location
            arr[j] = temp;
        }
    }
}

int main() {
    vector<int> arr = {12, 34, 54, 2, 3};

    cout << "Original array:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    shellSort(arr);

    cout << "Sorted array using Shell Sort:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}
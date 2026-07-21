#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MIN_RUN = 32;

// Insertion sort for small runs
void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Merge function to combine two sorted runs
void merge(vector<int>& arr, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    vector<int> leftArr(len1), rightArr(len2);

    for (int i = 0; i < len1; i++) leftArr[i] = arr[l + i];
    for (int i = 0; i < len2; i++) rightArr[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < len1) arr[k++] = leftArr[i++];
    while (j < len2) arr[k++] = rightArr[j++];
}

// Main Timsort function
void timSort(vector<int>& arr) {
    int n = arr.size();

    // Sort individual subarrays of size MIN_RUN
    for (int i = 0; i < n; i += MIN_RUN) {
        insertionSort(arr, i, min(i + MIN_RUN - 1, n - 1));
    }

    // Start merging from size MIN_RUN up to full size n
    for (int size = MIN_RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

int main() {
    vector<int> arr = {5, 21, 7, 23, 19, 3, 1, 35, 12, 18};

    cout << "Original array:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    timSort(arr);

    cout << "Sorted array using Timsort:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}
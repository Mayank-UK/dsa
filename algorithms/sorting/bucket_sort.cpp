#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to perform bucket sort on floating-point numbers in range [0, 1)
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    // 1. Create n empty buckets
    vector<vector<float>> buckets(n);

    // 2. Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i]; // Index in bucket
        if (bi >= n) bi = n - 1; // Safety check for upper bound
        buckets[bi].push_back(arr[i]);
    }

    // 3. Sort individual buckets
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }

    // 4. Concatenate all buckets back into arr
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (float val : buckets[i]) {
            arr[index++] = val;
        }
    }
}

int main() {
    vector<float> arr = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};

    cout << "Original array:\n";
    for (float num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    bucketSort(arr);

    cout << "Sorted array using Bucket Sort:\n";
    for (float num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}
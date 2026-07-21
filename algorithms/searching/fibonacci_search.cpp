#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to perform Fibonacci search on a sorted array
int fibonacciSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    if (n == 0) return -1;

    // Initialize Fibonacci numbers
    int fib2 = 0; // (k-2)'th Fibonacci number
    int fib1 = 1; // (k-1)'th Fibonacci number
    int fibK = fib2 + fib1; // k'th Fibonacci number

    // Find the smallest Fibonacci number greater than or equal to n
    while (fibK < n) {
        fib2 = fib1;
        fib1 = fibK;
        fibK = fib2 + fib1;
    }

    // Marks the eliminated range from the front
    int offset = -1;

    // While there are elements to inspect (fibK > 1, meaning fib2 > 0)
    while (fibK > 1) {
        // Check valid index
        int i = min(offset + fib2, n - 1);

        // If target is greater than the value at index i, cut the subarray from offset to i
        if (arr[i] < target) {
            fibK = fib1;
            fib1 = fib2;
            fib2 = fibK - fib1;
            offset = i;
        }
        // If target is less than the value at index i, cut the subarray after i
        else if (arr[i] > target) {
            fibK = fib2;
            fib1 = fib1 - fib2;
            fib2 = fibK - fib1;
        }
        // Element found
        else {
            return i;
        }
    }

    // Comparing the last element with target
    if (fib1 && offset + 1 < n && arr[offset + 1] == target) {
        return offset + 1;
    }

    // Element not found
    return -1;
}

int main() {
    vector<int> arr = {10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100};
    int target = 85;

    int resultIndex = fibonacciSearch(arr, target);

    if (resultIndex != -1) {
        cout << "Element " << target << " found at index " << resultIndex << ".\n";
    } else {
        cout << "Element " << target << " not found in the array.\n";
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to find the maximum contiguous subarray sum using Kadane's Algorithm
long long maxSubArraySum(const vector<int>& arr) {
    if (arr.empty()) return 0;

    long long current_max = arr[0];
    long long global_max = arr[0];

    for (size_t i = 1; i < arr.size(); ++i) {
        // Decide whether to add to the existing subarray or start a new one
        current_max = max(static_cast<long long>(arr[i]), current_max + arr[i]);
        // Update the global maximum if current_max is larger
        global_max = max(global_max, current_max);
    }

    return global_max;
}

int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    
    long long maxSum = maxSubArraySum(arr);
    cout << "The maximum contiguous subarray sum is: " << maxSum << "\n";

    return 0;
}
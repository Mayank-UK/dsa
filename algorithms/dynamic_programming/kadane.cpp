#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Kadane's algorithm: maximum sum of a contiguous subarray in one pass.
// current_max = best subarray ending here; global_max = best overall.
long long maxSubArraySum(const vector<int>& arr) {
    if (arr.empty()) return 0;

    long long current_max = arr[0];
    long long global_max = arr[0];

    for (size_t i = 1; i < arr.size(); ++i) {
        // Extend the running subarray, or start fresh at arr[i].
        current_max = max(static_cast<long long>(arr[i]), current_max + arr[i]);
        global_max = max(global_max, current_max);
    }
    return global_max;
}

int main() {
    cout << "================== Kadane's Algorithm ==================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n)\n";
    cout << "  Space : O(1)\n";
    cout << "  Note  : max sum of a CONTIGUOUS subarray (long long avoids overflow)\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "  array : ";
    for (int x : arr) cout << x << " ";
    cout << "\n  -> Max subarray sum = " << maxSubArraySum(arr) << "  ([4,-1,2,1])\n\n";

    cout << "[Cases]\n";
    cout << "  all positive : " << maxSubArraySum({1, 2, 3, 4}) << "\n";
    cout << "  all negative : " << maxSubArraySum({-8, -3, -6, -1, -2}) << "  (picks the largest single)\n";
    cout << "  mixed        : " << maxSubArraySum({-2, 1, -3, 4, -1, 2, 1, -5, 4}) << "\n";
    cout << "  with zero    : " << maxSubArraySum({-2, -3, 0, -1}) << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  empty        : " << maxSubArraySum({}) << "  (defined as 0)\n";
    cout << "  single pos   : " << maxSubArraySum({7}) << "\n";
    cout << "  single neg   : " << maxSubArraySum({-7}) << "\n";
    cout << "\n";

    return 0;
}

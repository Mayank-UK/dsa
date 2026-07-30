#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Longest (strictly) Increasing Subsequence in O(n log n).
// tails[i] = smallest possible tail value of an increasing subsequence of
// length i+1. For each number, binary-search its slot and extend or improve.
int lengthOfLIS(const vector<int>& nums) {
    if (nums.empty()) return 0;

    vector<int> tails;

    for (int x : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) {
            tails.push_back(x);   // x extends the longest subsequence so far
        } else {
            *it = x;              // lower the tail for that length
        }
    }
    return (int)tails.size();
}

int main() {
    cout << "======== Longest Increasing Subsequence ========\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n log n)   (lower_bound per element)\n";
    cout << "  Space : O(n)\n";
    cout << "  Note  : strictly increasing; returns LENGTH only\n\n";

    cout << "[Demo]\n";
    vector<int> nums = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    cout << "  array : ";
    for (int x : nums) cout << x << " ";
    cout << "\n  -> LIS length = " << lengthOfLIS(nums) << "  (e.g. 10,22,33,50,60,80)\n\n";

    cout << "[Cases]\n";
    cout << "  strictly increasing : " << lengthOfLIS({1, 2, 3, 4, 5}) << "\n";
    cout << "  strictly decreasing : " << lengthOfLIS({5, 4, 3, 2, 1}) << "\n";
    cout << "  with duplicates     : " << lengthOfLIS({2, 2, 2, 2}) << "  (strict -> 1)\n";
    cout << "  mixed               : " << lengthOfLIS({0, 8, 4, 12, 2, 10, 6, 14, 1, 9}) << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  empty        : " << lengthOfLIS({}) << "\n";
    cout << "  single       : " << lengthOfLIS({7}) << "\n";
    cout << "  two ascending: " << lengthOfLIS({1, 2}) << "\n";
    cout << "  two equal    : " << lengthOfLIS({3, 3}) << "\n";
    cout << "\n";

    return 0;
}

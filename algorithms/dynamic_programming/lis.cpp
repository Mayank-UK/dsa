#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the length of the Longest Increasing Subsequence in O(n log n) time
int lengthOfLIS(const vector<int>& nums) {
    if (nums.empty()) return 0;

    // tails[i] stores the smallest tail of all increasing subsequences of length i+1
    vector<int> tails;

    for (int x : nums) {
        // Find the index of the first element in tails that is >= x
        auto it = lower_bound(tails.begin(), tails.end(), x);

        // If x is larger than all elements in tails, extend the tail
        if (it == tails.end()) {
            tails.push_back(x);
        } 
        // Otherwise, find the smallest element >= x and replace it
        else {
            *it = x;
        }
    }

    // The size of tails represents the length of the longest increasing subsequence
    return tails.size();
}

int main() {
    vector<int> nums = {10, 22, 9, 33, 21, 50, 41, 60, 80};

    int lisLength = lengthOfLIS(nums);
    cout << "Length of Longest Increasing Subsequence = " << lisLength << "\n";

    return 0;
}
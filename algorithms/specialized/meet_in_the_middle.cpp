#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to generate all possible subset sums for a given vector
void generateSums(const vector<int>& arr, int i, int endIndex, long long currentSum, vector<long long>& sums) {
    if (i > endIndex) {
        sums.push_back(currentSum);
        return;
    }
    // Exclude current element
    generateSums(arr, i + 1, endIndex, currentSum, sums);
    // Include current element
    generateSums(arr, i + 1, endIndex, currentSum + arr[i], sums);
}

// Function to check if a subset sum equals target using Meet-in-the-Middle
bool meetInTheMiddle(const vector<int>& arr, long long target) {
    int n = arr.size();
    vector<int> leftHalf(arr.begin(), arr.begin() + n / 2);
    vector<int> rightHalf(arr.begin() + n / 2, arr.end());

    vector<long long> leftSums, rightSums;

    // Generate all sums for both halves
    generateSums(leftHalf, 0, leftHalf.size() - 1, 0, leftSums);
    generateSums(rightHalf, 0, rightHalf.size() - 1, 0, rightSums);

    // Sort the left sums to enable binary search
    sort(leftSums.begin(), leftSums.end());

    // Check each right sum against left sums
    for (long long rightSum : rightSums) {
        long long remaining = target - rightSum;
        // Binary search for 'remaining' in leftSums
        if (binary_search(leftSums.begin(), leftSums.end(), remaining)) {
            return true;
        }
    }

    return false;
}

int main() {
    vector<int> arr = {3, 34, 4, 12, 5, 2};
    long long target = 9;

    if (meetInTheMiddle(arr, target)) {
        cout << "Subset with target sum " << target << " found!\n";
    } else {
        cout << "No subset with target sum " << target << " exists.\n";
    }

    return 0;
}
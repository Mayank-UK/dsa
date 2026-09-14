#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================
// Meet-in-the-Middle — split a subset-sum search in half.
// A brute-force subset sum is O(2^n). Splitting the array into two halves,
// enumerating each half's 2^(n/2) subset sums, sorting one half, and binary-
// searching the complement in it for each sum of the other half gives
// O(2^(n/2) * n) — exponential speedup. Classic use: n ~ 40 where 2^40 is
// hopeless but 2^20 is trivial.
// ============================================================

// Enumerate every subset sum of arr[start..end] into `sums`.
static void generateSums(const vector<int>& arr, int i, int endIndex,
                         long long currentSum, vector<long long>& sums) {
    if (i > endIndex) {
        sums.push_back(currentSum);
        return;
    }
    generateSums(arr, i + 1, endIndex, currentSum, sums);            // exclude arr[i]
    generateSums(arr, i + 1, endIndex, currentSum + arr[i], sums);   // include arr[i]
}

// True iff some subset of arr sums to target.
static bool meetInTheMiddle(const vector<int>& arr, long long target) {
    int n = (int)arr.size();
    vector<int> leftHalf(arr.begin(), arr.begin() + n / 2);
    vector<int> rightHalf(arr.begin() + n / 2, arr.end());

    vector<long long> leftSums, rightSums;
    generateSums(leftHalf,  0, (int)leftHalf.size()  - 1, 0, leftSums);
    generateSums(rightHalf, 0, (int)rightHalf.size() - 1, 0, rightSums);

    sort(leftSums.begin(), leftSums.end());   // enables binary_search

    for (long long rightSum : rightSums) {
        long long remaining = target - rightSum;
        if (binary_search(leftSums.begin(), leftSums.end(), remaining))
            return true;
    }
    return false;
}

// Brute-force subset sum — used only to verify the optimized search.
static bool bruteSubsetSum(const vector<int>& arr, long long target) {
    int n = (int)arr.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        long long s = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) s += arr[i];
        if (s == target) return true;
    }
    return false;
}

static void runCase(const string& label, const vector<int>& arr, long long target) {
    bool found = meetInTheMiddle(arr, target);
    bool check = bruteSubsetSum(arr, target);
    cout << "  " << label << " -> "
         << (found ? "FOUND" : "no subset") << "   [brute: "
         << (check ? "FOUND" : "no subset") << ", "
         << (found == check ? "agree]" : "DISAGREE]") << endl;
}

// ============================================================
int main() {

    cout << "=================== Meet-in-the-Middle ===================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  time  : O(2^(n/2) * n)   (vs O(2^n) brute force)" << endl;
    cout << "  space : O(2^(n/2))       (store one half's sums)" << endl;
    cout << "  Notes : split + enumerate halves + sort one + binary-search the other." << endl;

    vector<int> arr = {3, 34, 4, 12, 5, 2};

    cout << endl;
    cout << "[Demo]  arr = {3, 34, 4, 12, 5, 2}" << endl;
    runCase("target = 9  (4 + 5)",         arr, 9);
    runCase("target = 30 (no subset)",      arr, 30);
    runCase("target = 11 (4 + 5 + 2)",      arr, 11);
    runCase("target = 13 (no subset)",       arr, 13);

    cout << endl;
    cout << "[Edge Cases]" << endl;
    runCase("target = 0  (the empty subset always works)", arr, 0);
    runCase("target = whole-array sum 60",                 arr, 60);
    runCase("target = 61 (one more than the sum)",         arr, 61);

    vector<int> one = {7};
    runCase("single element {7}, target = 7",  one, 7);
    runCase("single element {7}, target = 8",  one, 8);
    runCase("empty {}, target = 0",            {},   0);

    cout << endl;
    cout << "[Note]  This solves subset-sum exactly. For the optimization/counting" << endl;
    cout << "       variants see dynamic_programming/subset_sum.cpp (pseudo-poly O(n*sum))." << endl;

    return 0;
}

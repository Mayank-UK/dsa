#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// Divide-and-conquer maximum subarray (the CLRS form). The max subarray of
// arr[low..high] is ONE of three things:
//   (1) entirely in the left  half,
//   (2) entirely in the right half,
//   (3) crossing the midpoint (straddles mid).
// Recurse for (1) and (2); compute (3) directly by expanding outward from mid.
// The "combine" is the max of those three candidates.
// NOTE: an earlier revision of this file used Kadane's algorithm — that is a
// DP solution, not divide-and-conquer, so it mislabeled the category. Kadane
// lives in dynamic_programming/kadane.cpp; this file now teaches the genuine D&C.

struct Subarray {
    long long sum;   // sum of the chosen subarray
    int lo;          // inclusive start index
    int hi;          // inclusive end index
};

// Max subarray that MUST cross the midpoint: grow leftward from mid and
// rightward from mid+1, tracking the best suffix/prefix independently.
static Subarray maxCrossing(const vector<int>& arr, int low, int mid, int high) {
    long long leftSum = LLONG_MIN, sum = 0;
    int lo = mid;
    for (int i = mid; i >= low; --i) {
        sum += arr[i];
        if (sum > leftSum) { leftSum = sum; lo = i; }
    }
    long long rightSum = LLONG_MIN; sum = 0;
    int hi = mid + 1;
    for (int i = mid + 1; i <= high; ++i) {
        sum += arr[i];
        if (sum > rightSum) { rightSum = sum; hi = i; }
    }
    return {leftSum + rightSum, lo, hi};
}

// Recursive D&C: returns the best subarray within arr[low..high].
static Subarray maxSubArrayRec(const vector<int>& arr, int low, int high) {
    if (low == high) return {arr[low], low, high};   // base case: single element

    int mid = low + (high - low) / 2;
    Subarray left  = maxSubArrayRec(arr, low, mid);
    Subarray right = maxSubArrayRec(arr, mid + 1, high);
    Subarray cross = maxCrossing(arr, low, mid, high);

    if (left.sum >= right.sum && left.sum >= cross.sum) return left;
    if (right.sum >= left.sum && right.sum >= cross.sum) return right;
    return cross;
}

// Public entry — returns the max-sum contiguous subarray (empty array → {0,-1,-1}).
Subarray maxSubArray(const vector<int>& arr) {
    if (arr.empty()) return {0, -1, -1};
    return maxSubArrayRec(arr, 0, (int)arr.size() - 1);
}

// ─── Demo helpers ───
static void printArray(const vector<int>& arr) {
    cout << "  array : ";
    if (arr.empty()) { cout << "(empty)\n"; return; }
    for (int x : arr) cout << x << " ";
    cout << "\n";
}

// Naive O(n^2) check used only to verify the D&C answer in the demo.
static long long naiveMaxSum(const vector<int>& arr) {
    long long best = LLONG_MIN;
    for (size_t i = 0; i < arr.size(); ++i) {
        long long s = 0;
        for (size_t j = i; j < arr.size(); ++j) {
            s += arr[j];
            best = max(best, s);
        }
    }
    return best;
}

static void runCase(const string& name, const vector<int>& arr) {
    printArray(arr);
    Subarray s = maxSubArray(arr);
    if (s.lo == -1) {
        cout << "  " << name << " max sum : (empty array) -> 0\n\n";
        return;
    }
    cout << "  " << name << " subarray : [";
    for (int i = s.lo; i <= s.hi; ++i) cout << arr[i] << (i < s.hi ? ", " : "");
    cout << "]  sum = " << s.sum
         << "  (naive check: " << naiveMaxSum(arr) << ")\n\n";
}

int main() {
    cout << "=============== Maximum Subarray (Divide & Conquer) ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Best / Average / Worst : O(n log n)   (T(n) = 2T(n/2) + O(n))\n";
    cout << "  Space                  : O(log n) recursion\n";
    cout << "  Notes                  : Kadane's DP (dynamic_programming/kadane.cpp)\n";
    cout << "                            beats this at O(n); kept here for the D&C lesson.\n\n";

    cout << "[Demo]\n";
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};   // classic: [4,-1,2,1] = 6
    Subarray s = maxSubArray(arr);
    printArray(arr);
    cout << "  subarray : [";
    for (int i = s.lo; i <= s.hi; ++i) cout << arr[i] << (i < s.hi ? ", " : "");
    cout << "]  sum = " << s.sum
         << "  (naive check: " << naiveMaxSum(arr) << ")\n\n";

    cout << "[Edge Cases]\n";
    runCase("all negative ", {-8, -3, -6, -2, -5, -4});   // picks the single max element
    runCase("single element", {42});
    runCase("empty array  ", {});
    runCase("all positive ", {1, 2, 3, 4});
    runCase("mixed        ", {-1, 2, 3, -4, 5});

    return 0;
}

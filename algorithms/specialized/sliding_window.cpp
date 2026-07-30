#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <climits>

using namespace std;

// ============================================================
// Sliding Window — maintain a window [left..right] and expand/contract it one
// step at a time, recomputing the answer incrementally instead of rescanning.
// Two shapes: FIXED size (slide a length-k window) and VARIABLE size (grow
// right, shrink left while a constraint is violated). Either way O(n) because
// each element enters and leaves the window once.
// ============================================================
class SlidingWindow {
public:

    // ─── Fixed window: max sum of any length-k subarray ───  Time: O(n)
    static int maxSumSubarray(const vector<int>& arr, int k) {
        if (arr.empty() || k > (int)arr.size())
            return -1;

        int windowSum = 0;
        for (int i = 0; i < k; i++)            // seed the first window
            windowSum += arr[i];

        int maxSum = windowSum;
        for (int i = k; i < (int)arr.size(); i++) {   // slide: add new, drop old
            windowSum += arr[i];
            windowSum -= arr[i - k];
            maxSum = max(maxSum, windowSum);
        }
        return maxSum;
    }

    // ─── Variable window: smallest length with sum >= target ───  Time: O(n)
    static int minSubarrayLength(const vector<int>& arr, int target) {
        int left = 0, sum = 0, ans = INT_MAX;

        for (int right = 0; right < (int)arr.size(); right++) {
            sum += arr[right];
            while (sum >= target) {                       // shrink while still valid
                ans = min(ans, right - left + 1);
                sum -= arr[left++];
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }

    // ─── Longest substring with all unique chars ───  Time: O(n)
    static int longestUniqueSubstring(const string& s) {
        unordered_map<char, int> lastIndex;
        int left = 0, answer = 0;

        for (int right = 0; right < (int)s.length(); right++) {
            if (lastIndex.count(s[right]) && lastIndex[s[right]] >= left)
                left = lastIndex[s[right]] + 1;          // jump past the duplicate

            lastIndex[s[right]] = right;
            answer = max(answer, right - left + 1);
        }
        return answer;
    }

    // ─── Longest substring with at most k distinct chars ───  Time: O(n)
    static int longestKDistinct(const string& s, int k) {
        unordered_map<char, int> freq;
        int left = 0, answer = 0;

        for (int right = 0; right < (int)s.length(); right++) {
            freq[s[right]]++;
            while ((int)freq.size() > k) {               // too many distinct -> shrink
                freq[s[left]]--;
                if (freq[s[left]] == 0) freq.erase(s[left]);
                left++;
            }
            answer = max(answer, right - left + 1);
        }
        return answer;
    }

    // ─── Fixed window: max of every length-k window ───  Time: O(n)  (see also max_sliding_window.cpp)
    static vector<int> slidingWindowMaximum(const vector<int>& nums, int k) {
        deque<int> dq;   // indices, values decreasing
        vector<int> result;

        for (int i = 0; i < (int)nums.size(); i++) {
            while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
            while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
            dq.push_back(i);
            if (i >= k - 1) result.push_back(nums[dq.front()]);
        }
        return result;
    }

    // ─── Count subarrays with sum <= target (NON-NEGATIVE numbers) ───  Time: O(n)
    static long long countSubarraysLessEqual(const vector<int>& arr, int target) {
        int left = 0;
        long long answer = 0;
        int sum = 0;

        for (int right = 0; right < (int)arr.size(); right++) {
            sum += arr[right];
            while (sum > target)
                sum -= arr[left++];
            answer += (right - left + 1);                // all subarrays ending at right
        }
        return answer;
    }

    // ─── Longest subarray with at most 2 distinct values (Fruit Into Baskets) ───  Time: O(n)
    static int totalFruit(const vector<int>& fruits) {
        unordered_map<int, int> freq;
        int left = 0, answer = 0;

        for (int right = 0; right < (int)fruits.size(); right++) {
            freq[fruits[right]]++;
            while ((int)freq.size() > 2) {
                freq[fruits[left]]--;
                if (freq[fruits[left]] == 0) freq.erase(fruits[left]);
                left++;
            }
            answer = max(answer, right - left + 1);
        }
        return answer;
    }
};

static void printVec(const string& label, const vector<int>& v) {
    cout << "    " << label << ": ";
    for (int x : v) cout << x << " ";
    cout << endl;
}

// ============================================================
int main() {

    cout << "===================== Sliding Window =====================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  All shapes : O(n)   (each element enters and leaves the window once)" << endl;
    cout << "  space      : O(k) to O(alphabet) for the auxiliary map/deque" << endl;
    cout << "  Notes : FIXED size slides a length-k window; VARIABLE grows right," << endl;
    cout << "          shrinks left while the constraint is violated." << endl;

    cout << endl;
    cout << "[Demo]" << endl;

    // Fixed-window max sum.
    {
        vector<int> nums = {2, 1, 5, 1, 3, 2};
        cout << "  Max Sum of any length-3 subarray" << endl;
        printVec("nums", nums);
        cout << "    max sum = " << SlidingWindow::maxSumSubarray(nums, 3)
             << "  (5+1+3 = 9)" << endl;
    }

    // Smallest subarray with sum >= target.
    {
        vector<int> nums = {2, 1, 5, 1, 3, 2};
        cout << endl << "  Smallest subarray with sum >= 7" << endl;
        printVec("nums", nums);
        cout << "    min length = " << SlidingWindow::minSubarrayLength(nums, 7)
             << "  ({5,1,1} no, {5,1,3} = 9 -> length 3)" << endl;
    }

    // Longest unique substring.
    cout << endl << "  Longest Substring Without Repeating Characters" << endl;
    cout << "    \"abcabcbb\" -> " << SlidingWindow::longestUniqueSubstring("abcabcbb") << "  (\"abc\")" << endl;
    cout << "    \"bbbbbbb\"  -> " << SlidingWindow::longestUniqueSubstring("bbbbbbb")  << "  (\"b\")" << endl;

    // Longest k-distinct substring.
    cout << endl << "  Longest Substring with At Most 2 Distinct Chars" << endl;
    cout << "    \"eceba\", k=2 -> " << SlidingWindow::longestKDistinct("eceba", 2) << "  (\"ece\")" << endl;

    // Sliding window maximum.
    {
        vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
        cout << endl << "  Max of Every length-3 Window" << endl;
        printVec("nums", arr);
        cout << "    maxes  = ";
        for (int x : SlidingWindow::slidingWindowMaximum(arr, 3)) cout << x << " ";
        cout << endl;
    }

    // Count subarrays with sum <= target.
    {
        vector<int> positive = {1, 2, 1, 1, 3};
        cout << endl << "  Count Subarrays with sum <= 4 (non-negative only)" << endl;
        printVec("nums", positive);
        cout << "    count = " << SlidingWindow::countSubarraysLessEqual(positive, 4) << endl;
    }

    // Fruit into baskets.
    {
        vector<int> fruits = {1, 2, 1, 2, 3, 2, 2};
        cout << endl << "  Fruit Into Baskets (longest subarray, <= 2 distinct values)" << endl;
        printVec("fruits", fruits);
        cout << "    max length = " << SlidingWindow::totalFruit(fruits) << "  ({1,2,1,2} or {2,3,2,2})" << endl;
    }

    cout << endl;
    cout << "[Edge Cases]" << endl;
    cout << "  Max sum, k larger than array {1,2,3}, k=5 -> "
         << SlidingWindow::maxSumSubarray({1, 2, 3}, 5) << "  (-1 = no full window)" << endl;
    cout << "  Smallest subarray, no window reaches target {1,1,1}, target=10 -> "
         << SlidingWindow::minSubarrayLength({1, 1, 1}, 10) << "  (0 = impossible)" << endl;
    cout << "  Longest unique substring \"\" -> "
         << SlidingWindow::longestUniqueSubstring("") << endl;
    cout << "  Longest k-distinct, k=0 \"abc\", k=0 -> "
         << SlidingWindow::longestKDistinct("abc", 0) << "  (0 = no chars allowed)" << endl;

    cout << endl;
    cout << "[Note]  Variable-window subarray-sum tricks need NON-NEGATIVE numbers so the" << endl;
    cout << "       sum is monotone in window size (the count/length invariants break on" << endl;
    cout << "       negatives). The fixed-window MAX is independent of sign — see" << endl;
    cout << "       max_sliding_window.cpp for the deque version." << endl;

    return 0;
}

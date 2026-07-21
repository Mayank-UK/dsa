#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <climits>
using namespace std;

class SlidingWindow {
public:

    // ==========================================================
    // Fixed Size Sliding Window
    // Time: O(n)
    // ==========================================================
    static int maxSumSubarray(const vector<int>& arr, int k) {
        if (arr.empty() || k > arr.size())
            return -1;

        int windowSum = 0;

        // First window
        for (int i = 0; i < k; i++)
            windowSum += arr[i];

        int maxSum = windowSum;

        // Slide the window
        for (int i = k; i < arr.size(); i++) {
            windowSum += arr[i];
            windowSum -= arr[i - k];
            maxSum = max(maxSum, windowSum);
        }

        return maxSum;
    }

    // ==========================================================
    // Smallest Subarray with Sum >= Target
    // Time: O(n)
    // ==========================================================
    static int minSubarrayLength(const vector<int>& arr, int target) {
        int left = 0;
        int sum = 0;
        int ans = INT_MAX;

        for (int right = 0; right < arr.size(); right++) {
            sum += arr[right];

            while (sum >= target) {
                ans = min(ans, right - left + 1);
                sum -= arr[left++];
            }
        }

        return ans == INT_MAX ? 0 : ans;
    }

    // ==========================================================
    // Longest Substring Without Repeating Characters
    // Time: O(n)
    // ==========================================================
    static int longestUniqueSubstring(const string& s) {
        unordered_map<char, int> lastIndex;

        int left = 0;
        int answer = 0;

        for (int right = 0; right < s.length(); right++) {

            if (lastIndex.count(s[right]) &&
                lastIndex[s[right]] >= left)
                left = lastIndex[s[right]] + 1;

            lastIndex[s[right]] = right;

            answer = max(answer, right - left + 1);
        }

        return answer;
    }

    // ==========================================================
    // Longest Substring with At Most K Distinct Characters
    // Time: O(n)
    // ==========================================================
    static int longestKDistinct(const string& s, int k) {

        unordered_map<char, int> freq;

        int left = 0;
        int answer = 0;

        for (int right = 0; right < s.length(); right++) {

            freq[s[right]]++;

            while (freq.size() > k) {

                freq[s[left]]--;

                if (freq[s[left]] == 0)
                    freq.erase(s[left]);

                left++;
            }

            answer = max(answer, right - left + 1);
        }

        return answer;
    }

    // ==========================================================
    // Maximum in Every Window of Size K
    // Time: O(n)
    // ==========================================================
    static vector<int> slidingWindowMaximum(
            const vector<int>& nums, int k) {

        deque<int> dq;
        vector<int> result;

        for (int i = 0; i < nums.size(); i++) {

            // Remove indices outside current window
            while (!dq.empty() && dq.front() <= i - k)
                dq.pop_front();

            // Remove smaller values
            while (!dq.empty() &&
                   nums[dq.back()] <= nums[i])
                dq.pop_back();

            dq.push_back(i);

            if (i >= k - 1)
                result.push_back(nums[dq.front()]);
        }

        return result;
    }

    // ==========================================================
    // Count Subarrays with Sum <= Target (Positive Numbers)
    // Time: O(n)
    // ==========================================================
    static long long countSubarraysLessEqual(
            const vector<int>& arr,
            int target) {

        int left = 0;
        long long answer = 0;
        int sum = 0;

        for (int right = 0; right < arr.size(); right++) {

            sum += arr[right];

            while (sum > target)
                sum -= arr[left++];

            answer += (right - left + 1);
        }

        return answer;
    }

    // ==========================================================
    // Fruit Into Baskets
    // Longest subarray with at most 2 distinct values
    // ==========================================================
    static int totalFruit(const vector<int>& fruits) {

        unordered_map<int, int> freq;

        int left = 0;
        int answer = 0;

        for (int right = 0; right < fruits.size(); right++) {

            freq[fruits[right]]++;

            while (freq.size() > 2) {

                freq[fruits[left]]--;

                if (freq[fruits[left]] == 0)
                    freq.erase(fruits[left]);

                left++;
            }

            answer = max(answer, right - left + 1);
        }

        return answer;
    }
};

int main() {

    vector<int> nums = {2, 1, 5, 1, 3, 2};

    cout << "Maximum Sum of Window Size 3: "
         << SlidingWindow::maxSumSubarray(nums, 3)
         << endl;

    cout << "Minimum Length Subarray with Sum >= 7: "
         << SlidingWindow::minSubarrayLength(nums, 7)
         << endl;

    string s = "abcabcbb";

    cout << "Longest Unique Substring: "
         << SlidingWindow::longestUniqueSubstring(s)
         << endl;

    cout << "Longest Substring with At Most 2 Distinct: "
         << SlidingWindow::longestKDistinct("eceba", 2)
         << endl;

    vector<int> arr = {1,3,-1,-3,5,3,6,7};

    vector<int> mx =
        SlidingWindow::slidingWindowMaximum(arr, 3);

    cout << "Sliding Window Maximum: ";

    for (int x : mx)
        cout << x << " ";

    cout << endl;

    vector<int> positive = {1,2,1,1,3};

    cout << "Count of Subarrays Sum <= 4: "
         << SlidingWindow::countSubarraysLessEqual(
                positive, 4)
         << endl;

    vector<int> fruits = {1,2,1,2,3,2,2};

    cout << "Fruit Into Baskets: "
         << SlidingWindow::totalFruit(fruits)
         << endl;

    return 0;
}
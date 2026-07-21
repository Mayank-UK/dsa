#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class TwoPointers {
public:

    // ==========================================================
    // Two Sum in Sorted Array
    // Time: O(n)
    // ==========================================================
    static pair<int, int> twoSumSorted(const vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int sum = nums[left] + nums[right];

            if (sum == target)
                return {left, right};

            if (sum < target)
                left++;
            else
                right--;
        }

        return {-1, -1};
    }

    // ==========================================================
    // Reverse Array
    // Time: O(n)
    // ==========================================================
    static void reverseArray(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            swap(nums[left], nums[right]);
            left++;
            right--;
        }
    }

    // ==========================================================
    // Remove Duplicates from Sorted Array
    // Time: O(n)
    // ==========================================================
    static int removeDuplicates(vector<int>& nums) {
        if (nums.empty())
            return 0;

        int slow = 0;

        for (int fast = 1; fast < nums.size(); fast++) {
            if (nums[fast] != nums[slow]) {
                slow++;
                nums[slow] = nums[fast];
            }
        }

        return slow + 1;
    }

    // ==========================================================
    // Move Zeroes to End
    // Time: O(n)
    // ==========================================================
    static void moveZeroes(vector<int>& nums) {
        int slow = 0;

        for (int fast = 0; fast < nums.size(); fast++) {
            if (nums[fast] != 0) {
                swap(nums[slow], nums[fast]);
                slow++;
            }
        }
    }

    // ==========================================================
    // Valid Palindrome
    // Time: O(n)
    // ==========================================================
    static bool isPalindrome(const string& s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            if (s[left] != s[right])
                return false;

            left++;
            right--;
        }

        return true;
    }

    // ==========================================================
    // Container With Most Water
    // Time: O(n)
    // ==========================================================
    static int maxArea(const vector<int>& height) {

        int left = 0;
        int right = height.size() - 1;

        int answer = 0;

        while (left < right) {

            int width = right - left;
            int h = min(height[left], height[right]);

            answer = max(answer, width * h);

            if (height[left] < height[right])
                left++;
            else
                right--;
        }

        return answer;
    }

    // ==========================================================
    // Squares of Sorted Array
    // Time: O(n)
    // ==========================================================
    static vector<int> sortedSquares(const vector<int>& nums) {

        int left = 0;
        int right = nums.size() - 1;

        vector<int> answer(nums.size());

        int index = nums.size() - 1;

        while (left <= right) {

            int leftSquare = nums[left] * nums[left];
            int rightSquare = nums[right] * nums[right];

            if (leftSquare > rightSquare) {
                answer[index--] = leftSquare;
                left++;
            } else {
                answer[index--] = rightSquare;
                right--;
            }
        }

        return answer;
    }

    // ==========================================================
    // 3 Sum
    // Time: O(n²)
    // ==========================================================
    static vector<vector<int>> threeSum(vector<int> nums) {

        sort(nums.begin(), nums.end());

        vector<vector<int>> answer;

        for (int i = 0; i < nums.size(); i++) {

            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int left = i + 1;
            int right = nums.size() - 1;

            while (left < right) {

                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {

                    answer.push_back(
                        {nums[i], nums[left], nums[right]}
                    );

                    while (left < right &&
                           nums[left] == nums[left + 1])
                        left++;

                    while (left < right &&
                           nums[right] == nums[right - 1])
                        right--;

                    left++;
                    right--;
                }
                else if (sum < 0)
                    left++;
                else
                    right--;
            }
        }

        return answer;
    }
};

int main() {

    vector<int> nums = {1,2,3,4,6,8};

    auto p = TwoPointers::twoSumSorted(nums, 10);

    cout << "Two Sum Indices: "
         << p.first << " "
         << p.second << endl;

    vector<int> rev = {1,2,3,4,5};
    TwoPointers::reverseArray(rev);

    cout << "Reversed: ";
    for (int x : rev)
        cout << x << " ";
    cout << endl;

    vector<int> dup = {1,1,2,2,3,3,4};
    int len = TwoPointers::removeDuplicates(dup);

    cout << "After Removing Duplicates: ";
    for (int i = 0; i < len; i++)
        cout << dup[i] << " ";
    cout << endl;

    vector<int> zeroes = {0,1,0,3,12};
    TwoPointers::moveZeroes(zeroes);

    cout << "Move Zeroes: ";
    for (int x : zeroes)
        cout << x << " ";
    cout << endl;

    cout << "Palindrome (racecar): "
         << TwoPointers::isPalindrome("racecar")
         << endl;

    vector<int> height = {1,8,6,2,5,4,8,3,7};

    cout << "Max Area: "
         << TwoPointers::maxArea(height)
         << endl;

    vector<int> sq = {-7,-3,2,3,11};

    auto result = TwoPointers::sortedSquares(sq);

    cout << "Sorted Squares: ";

    for (int x : result)
        cout << x << " ";

    cout << endl;

    vector<int> arr = {-1,0,1,2,-1,-4};

    auto triplets = TwoPointers::threeSum(arr);

    cout << "3 Sum:\n";

    for (auto &v : triplets) {
        for (int x : v)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}
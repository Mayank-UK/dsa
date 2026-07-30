#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================
// Two Pointers — drive two indices toward each other (or a fast/slow pair) to
// scan in O(n) what nested loops would do in O(n^2). The shared idea: every
// step makes a monotone decision (move left, move right, or copy forward), so
// each element is visited O(1) times. Several classic shapes below.
// ============================================================
class TwoPointers {
public:

    // ─── Two Sum in a SORTED array ───  Time: O(n)
    static pair<int, int> twoSumSorted(const vector<int>& nums, int target) {
        int left = 0;
        int right = (int)nums.size() - 1;

        while (left < right) {
            int sum = nums[left] + nums[right];

            if (sum == target)
                return {left, right};

            if (sum < target) left++;
            else              right--;
        }
        return {-1, -1};
    }

    // ─── Reverse in place ───  Time: O(n)
    static void reverseArray(vector<int>& nums) {
        int left = 0;
        int right = (int)nums.size() - 1;

        while (left < right) {
            swap(nums[left], nums[right]);
            left++;
            right--;
        }
    }

    // ─── Remove duplicates from a SORTED array (return new length) ───  Time: O(n)
    static int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;

        int slow = 0;
        for (int fast = 1; fast < (int)nums.size(); fast++) {
            if (nums[fast] != nums[slow]) {
                slow++;
                nums[slow] = nums[fast];
            }
        }
        return slow + 1;
    }

    // ─── Move all zeroes to the end, keeping order ───  Time: O(n)
    static void moveZeroes(vector<int>& nums) {
        int slow = 0;
        for (int fast = 0; fast < (int)nums.size(); fast++) {
            if (nums[fast] != 0) {
                swap(nums[slow], nums[fast]);
                slow++;
            }
        }
    }

    // ─── Is palindrome? ───  Time: O(n)
    static bool isPalindrome(const string& s) {
        int left = 0;
        int right = (int)s.size() - 1;

        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }

    // ─── Container With Most Water ───  Time: O(n)
    static int maxArea(const vector<int>& height) {
        int left = 0;
        int right = (int)height.size() - 1;
        int answer = 0;

        while (left < right) {
            int width = right - left;
            int h = min(height[left], height[right]);
            answer = max(answer, width * h);

            if (height[left] < height[right]) left++;
            else                              right--;
        }
        return answer;
    }

    // ─── Squares of a sorted array (may have negatives) ───  Time: O(n)
    static vector<int> sortedSquares(const vector<int>& nums) {
        int left = 0;
        int right = (int)nums.size() - 1;
        vector<int> answer(nums.size());
        int index = (int)nums.size() - 1;

        while (left <= right) {
            int leftSquare  = nums[left]  * nums[left];
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

    // ─── 3 Sum (all unique triplets summing to 0) ───  Time: O(n^2)
    static vector<vector<int>> threeSum(vector<int> nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> answer;

        for (int i = 0; i < (int)nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;   // skip duplicate first element

            int left = i + 1;
            int right = (int)nums.size() - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    answer.push_back({nums[i], nums[left], nums[right]});

                    while (left < right && nums[left]  == nums[left + 1])  left++;   // dedupe
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                } else if (sum < 0) left++;
                else                right--;
            }
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

    cout << "====================== Two Pointers ======================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  All linear-pointer shapes : O(n)   (each element visited O(1) times)" << endl;
    cout << "  3 Sum                     : O(n^2) (fix one, two-pointers the rest)" << endl;
    cout << "  Notes : the pointer(s) move monotonically; never revisit a decision." << endl;

    cout << endl;
    cout << "[Demo]" << endl;

    // Two sum — requires a sorted input.
    {
        vector<int> nums = {1, 2, 3, 4, 6, 8};
        auto p = TwoPointers::twoSumSorted(nums, 10);
        cout << "  Two Sum (sorted {1,2,3,4,6,8}, target 10): indices "
             << p.first << "," << p.second
             << "  (values " << nums[p.first] << "+" << nums[p.second] << ")" << endl;
    }

    // Reverse.
    {
        vector<int> rev = {1, 2, 3, 4, 5};
        cout << endl << "  Reverse Array" << endl;
        printVec("before", rev);
        TwoPointers::reverseArray(rev);
        printVec("after ", rev);
    }

    // Remove duplicates.
    {
        vector<int> dup = {1, 1, 2, 2, 3, 3, 4};
        cout << endl << "  Remove Duplicates (sorted)" << endl;
        printVec("before", dup);
        int len = TwoPointers::removeDuplicates(dup);
        cout << "    after (len " << len << "): ";
        for (int i = 0; i < len; i++) cout << dup[i] << " ";
        cout << endl;
    }

    // Move zeroes.
    {
        vector<int> z = {0, 1, 0, 3, 12};
        cout << endl << "  Move Zeroes to End" << endl;
        printVec("before", z);
        TwoPointers::moveZeroes(z);
        printVec("after ", z);
    }

    // Palindrome.
    cout << endl << "  Palindrome Check" << endl;
    cout << "    \"racecar\" -> " << (TwoPointers::isPalindrome("racecar") ? "Yes" : "No") << endl;
    cout << "    \"hello\"   -> " << (TwoPointers::isPalindrome("hello")   ? "Yes" : "No") << endl;

    // Container with most water.
    {
        vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        cout << endl << "  Container With Most Water" << endl;
        printVec("height", height);
        cout << "    max area = " << TwoPointers::maxArea(height) << endl;
    }

    // Sorted squares.
    {
        vector<int> sq = {-7, -3, 2, 3, 11};
        cout << endl << "  Sorted Squares (input may have negatives)" << endl;
        printVec("before", sq);
        printVec("after ", TwoPointers::sortedSquares(sq));
    }

    // 3 Sum.
    {
        vector<int> arr = {-1, 0, 1, 2, -1, -4};
        cout << endl << "  3 Sum (unique triplets summing to 0)" << endl;
        printVec("input", arr);
        auto triplets = TwoPointers::threeSum(arr);
        cout << "    triplets:" << endl;
        for (auto& v : triplets) {
            cout << "      ";
            for (int x : v) cout << x << " ";
            cout << endl;
        }
    }

    cout << endl;
    cout << "[Edge Cases]" << endl;
    cout << "  Two Sum no pair in {1,2,3}, target 50 -> indices "
         << TwoPointers::twoSumSorted({1, 2, 3}, 50).first << ","
         << TwoPointers::twoSumSorted({1, 2, 3}, 50).second << "  (-1,-1 = not found)" << endl;
    vector<int> emptyDup;
    cout << "  Remove Duplicates on {} -> length "
         << TwoPointers::removeDuplicates(emptyDup) << endl;
    cout << "  Palindrome \"\" (empty) -> " << (TwoPointers::isPalindrome("") ? "Yes" : "No") << endl;
    cout << "  Palindrome \"a\" (single) -> " << (TwoPointers::isPalindrome("a") ? "Yes" : "No") << endl;

    cout << endl;
    cout << "[Note]  Two pointers needs the input to be SORTED when the decision is" << endl;
    cout << "       \"sum too small/large\" (two sum, 3 sum, water). The fast/slow" << endl;
    cout << "       variants (dedupe, move-zeroes) work on any array. Variable-window" << endl;
    cout << "       problems are in sliding_window.cpp." << endl;

    return 0;
}

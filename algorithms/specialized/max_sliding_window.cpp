#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class SlidingWindowMaximum {
public:

    // ----------------------------------------------------------
    // Maximum in Every Window of Size K
    // Time: O(n)
    // Space: O(k)
    // ----------------------------------------------------------
    static vector<int> maxSlidingWindow(const vector<int>& nums, int k) {

        deque<int> dq;          // Stores indices
        vector<int> result;

        for (int i = 0; i < nums.size(); i++) {

            // Remove indices outside current window
            while (!dq.empty() && dq.front() <= i - k)
                dq.pop_front();

            // Remove all smaller elements
            while (!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();

            // Insert current index
            dq.push_back(i);

            // Window is complete
            if (i >= k - 1)
                result.push_back(nums[dq.front()]);
        }

        return result;
    }
};

int main() {

    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;

    vector<int> answer =
        SlidingWindowMaximum::maxSlidingWindow(nums, k);

    cout << "Sliding Window Maximum:\n";

    for (int x : answer)
        cout << x << " ";

    cout << endl;

    return 0;
}
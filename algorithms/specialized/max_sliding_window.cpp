#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// ============================================================
// Sliding Window Maximum — a deque of INDICES keeps candidates in decreasing
// value order. For each new element: drop indices that fell out of the window
// from the front, pop smaller values from the back (they can never be the max
// while the new element is in the window), then push the new index. The front
// of the deque is always the current window's maximum. Each index enters and
// leaves the deque once → O(n).
// ============================================================
class SlidingWindowMaximum {
public:
    // ─── Max of every window of size k ───  Time: O(n)   Space: O(k)
    static vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
        deque<int> dq;          // indices; values monotonically decreasing
        vector<int> result;

        for (int i = 0; i < (int)nums.size(); i++) {
            // Drop indices that left the window.
            while (!dq.empty() && dq.front() <= i - k)
                dq.pop_front();

            // Drop smaller values — they cannot be the max now.
            while (!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();

            dq.push_back(i);

            // Start emitting once the first full window has formed.
            if (i >= k - 1)
                result.push_back(nums[dq.front()]);
        }
        return result;
    }
};

static void runCase(const string& label, const vector<int>& nums, int k) {
    vector<int> ans = SlidingWindowMaximum::maxSlidingWindow(nums, k);
    cout << "  " << label << "\n    nums: ";
    for (int x : nums) cout << x << " ";
    cout << "\n    max (k=" << k << "): ";
    for (int x : ans) cout << x << " ";
    cout << "\n";
}

// ============================================================
int main() {

    cout << "=============== Maximum in Sliding Window ===============" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  time  : O(n)   (each index pushed once, popped once)" << endl;
    cout << "  space : O(k)   (deque holds at most one window of indices)" << endl;
    cout << "  Notes : monotonic DECREASING deque of indices; front = window max." << endl;

    cout << endl;
    cout << "[Demo]" << endl;
    runCase("classic {1,3,-1,-3,5,3,6,7}, k=3",
            {1, 3, -1, -3, 5, 3, 6, 7}, 3);

    cout << endl;
    cout << "[Edge Cases]" << endl;
    runCase("window = 1 -> every element is its own max",
            {4, 2, 9, 1}, 1);
    runCase("window = n -> the single global max",
            {4, 2, 9, 1}, 4);
    runCase("window larger than array -> no full window, empty result",
            {1, 2, 3}, 5);
    runCase("single element, k = 1",
            {7}, 1);
    runCase("non-increasing -> max equals leftmost each time",
            {9, 7, 5, 3}, 2);

    cout << endl;
    cout << "[Note]  This is the fixed-window max; the variable-size cousin" << endl;
    cout << "       (longest/shortest subarray with a property) lives in sliding_window.cpp." << endl;

    return 0;
}

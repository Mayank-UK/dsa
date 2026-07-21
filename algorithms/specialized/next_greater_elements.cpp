#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Function to find the next greater element for each array item
vector<int> nextGreaterElements(const vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st; // Monotonically decreasing stack storing indices

    for (int i = 0; i < n; i++) {
        // While stack is not empty and current element is greater than 
        // the element corresponding to the index at the top of the stack
        while (!st.empty() && nums[st.top()] < nums[i]) {
            result[st.top()] = nums[i]; // Next greater element found
            st.pop();
        }
        st.push(i);
    }

    return result;
}

int main() {
    vector<int> nums = {2, 1, 2, 4, 3};

    vector<int> nge = nextGreaterElements(nums);

    cout << "Next greater elements:\n";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " -> " << nge[i] << "\n";
    }

    return 0;
}
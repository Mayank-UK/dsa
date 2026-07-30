#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// ============================================================
// Next Greater Element (NGE) — monotonic decreasing stack, one pass.
// For each index, pop while the stack top's value is smaller than nums[i]:
// those elements have just found their next greater. Each index is pushed and
// popped at most once → O(n) despite the nested while. Indices not popped by
// the end have no greater element to their right (stay -1).
// ============================================================

// Returns, for each index, the next greater element to its right (-1 if none).
static vector<int> nextGreaterElements(const vector<int>& nums) {
    int n = (int)nums.size();
    vector<int> result(n, -1);
    stack<int> st;  // indices; values on the stack are monotonically decreasing

    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] < nums[i]) {
            result[st.top()] = nums[i];   // nums[i] is the next greater for st.top()
            st.pop();
        }
        st.push(i);
    }
    return result;
}

// Print nums[i] -> nge[i] for a labeled case.
static void runCase(const string& label, const vector<int>& nums) {
    vector<int> nge = nextGreaterElements(nums);
    cout << "  " << label << "\n    nums: ";
    for (int x : nums) cout << x << " ";
    cout << "\n    nge : ";
    for (int x : nge) cout << x << " ";
    cout << "\n";
}

// ============================================================
int main() {

    cout << "=============== Next Greater Element ===============" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  time  : O(n)   (each index pushed once, popped once)" << endl;
    cout << "  space : O(n)   (the stack)" << endl;
    cout << "  Notes : monotonic DECREASING stack; remaining indices get -1." << endl;

    cout << endl;
    cout << "[Demo]" << endl;
    runCase("classic {2,1,2,4,3}",              {2, 1, 2, 4, 3});

    cout << endl;
    cout << "[Edge Cases]" << endl;
    runCase("ascending {1,2,3,4}  -> each finds the next", {1, 2, 3, 4});
    runCase("descending {4,3,2,1} -> none has a greater",  {4, 3, 2, 1});
    runCase("duplicates {5,5,5}   -> strict <, so all -1", {5, 5, 5});
    runCase("single {7}",                                  {7});
    runCase("empty {}",                                   {});

    cout << endl;
    cout << "[Note]  Variant: a CIRCULAR NGE scans i in [0,2n) modulo n. To get the" << endl;
    cout << "       next SMALLER element instead, flip the comparison to '>' and use" << endl;
    cout << "       a monotonically INCREASING stack." << endl;

    return 0;
}

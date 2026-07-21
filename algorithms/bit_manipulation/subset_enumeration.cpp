#include <iostream>
#include <vector>

using namespace std;

class SubsetGenerator {
public:
    // Approach 1: Bit Masking (Iterative)
    // Uses integers from 0 to (2^N - 1) to represent all possible subsets.
    vector<vector<int>> generateBitwise(const vector<int>& nums) {
        vector<vector<int>> power_set;
        int n = nums.size();
        int total_subsets = 1 << n; // 2^n
        
        for (int mask = 0; mask < total_subsets; ++mask) {
            vector<int> current_subset;
            for (int i = 0; i < n; ++i) {
                // If the i-th bit in the mask is set to 1, include nums[i]
                if (mask & (1 << i)) {
                    current_subset.push_back(nums[i]);
                }
            }
            power_set.push_back(current_subset);
        }
        
        return power_set;
    }

    // Approach 2: Backtracking (Recursive)
    // Explores the inclusion/exclusion of each element in a depth-first manner.
    vector<vector<int>> generateBacktracking(const vector<int>& nums) {
        vector<vector<int>> power_set;
        vector<int> current_subset;
        backtrack(0, current_subset, nums, power_set);
        return power_set;
    }

private:
    void backtrack(int index, vector<int>& current_subset, const vector<int>& nums, vector<vector<int>>& power_set) {
        // Base case: If we have considered all elements, add the current subset
        if (index == nums.size()) {
            power_set.push_back(current_subset);
            return;
        }
        
        // Choice 1: Exclude the current element and move forward
        backtrack(index + 1, current_subset, nums, power_set);
        
        // Choice 2: Include the current element and move forward
        current_subset.push_back(nums[index]);
        backtrack(index + 1, current_subset, nums, power_set);
        
        // Backtrack: Remove the element to explore other branches (clean up state)
        current_subset.pop_back();
    }
};

// Helper function to print subsets clearly
void printSubsets(const vector<vector<int>>& subsets) {
    cout << "{ ";
    for (size_t i = 0; i < subsets.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < subsets[i].size(); ++j) {
            cout << subsets[i][j] << (j < subsets[i].size() - 1 ? ", " : "");
        }
        cout << "]" << (i < subsets.size() - 1 ? ", " : "");
    }
    cout << " }\n";
}

int main() {
    SubsetGenerator generator;
    vector<int> set = {1, 2, 3};
    
    cout << "--- Subset Enumeration (Power Set) ---\n";
    cout << "Original Set: [1, 2, 3]\n\n";
    
    cout << "1. Bitwise Generation:\n";
    vector<vector<int>> bitwise_subsets = generator.generateBitwise(set);
    printSubsets(bitwise_subsets);
    
    cout << "\n2. Backtracking Generation:\n";
    vector<vector<int>> backtrack_subsets = generator.generateBacktracking(set);
    printSubsets(backtrack_subsets);
    
    cout << "--------------------------------------\n";

    return 0;
}
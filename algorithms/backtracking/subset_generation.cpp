#include <iostream>
#include <vector>

using namespace std;

class Subsets {
private:
    // Core backtracking function
    void backtrack(int start_index, const vector<int>& elements, vector<int>& current_subset, vector<vector<int>>& result) {
        // Unlike N-Queens or Permutations, we don't wait for a base case to record the state.
        // Every valid 'current_subset' formed along the path is a valid subset of the power set.
        result.push_back(current_subset);

        // Iterate through the remaining elements starting from 'start_index'
        for (int i = start_index; i < elements.size(); ++i) {
            // 1. Choose: Include the current element in the subset
            current_subset.push_back(elements[i]);

            // 2. Explore: Move to the next element
            // We pass 'i + 1' to ensure we only move forward, preventing duplicate sets like {1,2} and {2,1}
            backtrack(i + 1, elements, current_subset, result);

            // 3. Un-choose (Backtrack): Remove the element to explore subsets without it
            current_subset.pop_back();
        }
    }

public:
    // Public interface to generate all subsets
    vector<vector<int>> generate(const vector<int>& elements) {
        vector<vector<int>> result;
        vector<int> current_subset;
        
        // Start backtracking from index 0
        backtrack(0, elements, current_subset, result);
        
        return result;
    }
};

int main() {
    // A distinct set of elements
    vector<int> elements = {1, 2, 3};
    
    cout << "Original Set: { ";
    for (int num : elements) cout << num << " ";
    cout << "}\n\n";

    // Initialize the Subsets algorithm
    Subsets sub;

    // Generate all subsets
    vector<vector<int>> result = sub.generate(elements);

    // Print the results
    cout << "--- Generated Subsets (Power Set) ---\n";
    int count = 1;
    for (const auto& subset : result) {
        cout << count++ << ": [ ";
        for (int num : subset) {
            cout << num << " ";
        }
        cout << "]\n";
    }
    cout << "-------------------------------------\n";
    cout << "Total subsets found: " << result.size() << "\n";

    return 0;
}
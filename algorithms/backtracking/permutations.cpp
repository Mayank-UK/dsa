#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Permutations {
private:
    // Core backtracking function
    void backtrack(int start, vector<int>& elements, vector<vector<int>>& result) {
        // Base case: If the starting index reaches the end of the array,
        // we have formed a complete permutation.
        if (start == elements.size()) {
            result.push_back(elements);
            return;
        }

        // Iterate through the array starting from the 'start' index
        for (int i = start; i < elements.size(); ++i) {
            // 1. Choose: Swap the current element with the 'start' element
            // This locks elements[start] in place for this recursive branch.
            swap(elements[start], elements[i]);

            // 2. Explore: Recursively generate permutations for the remaining elements
            backtrack(start + 1, elements, result);

            // 3. Un-choose (Backtrack): Swap the elements back to restore the 
            // original array state before moving to the next iteration.
            swap(elements[start], elements[i]);
        }
    }

public:
    // Public interface to generate permutations
    vector<vector<int>> generate(vector<int> elements) {
        vector<vector<int>> result;
        
        if (elements.empty()) {
            return result;
        }

        // Start the backtracking process from index 0
        backtrack(0, elements, result);
        
        return result;
    }
};

int main() {
    // Set of distinct elements
    vector<int> elements = {1, 2, 3};
    
    cout << "Elements: { ";
    for (int num : elements) cout << num << " ";
    cout << "}\n\n";

    // Initialize the Permutations algorithm
    Permutations perm;

    // Generate all permutations
    vector<vector<int>> result = perm.generate(elements);

    // Print the results
    cout << "--- Generated Permutations ---\n";
    int count = 1;
    for (const auto& permutation : result) {
        cout << count++ << ": [ ";
        for (int num : permutation) {
            cout << num << " ";
        }
        cout << "]\n";
    }
    cout << "------------------------------\n";
    cout << "Total permutations found: " << result.size() << "\n";

    return 0;
}
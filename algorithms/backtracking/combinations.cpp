#include <iostream>
#include <vector>

using namespace std;

class Combinations {
private:
    // Core backtracking function
    void backtrack(const vector<int>& elements, int k, int start, vector<int>& current_combo, vector<vector<int>>& result) {
        // Base case: If the current combination has reached the desired size k
        if (current_combo.size() == k) {
            result.push_back(current_combo);
            return;
        }

        // Iterate through the remaining elements starting from 'start'
        for (int i = start; i < elements.size(); ++i) {
            // 1. Choose: Add the current element to the combination
            current_combo.push_back(elements[i]);

            // 2. Explore: Move forward to the next elements (i + 1)
            backtrack(elements, k, i + 1, current_combo, result);

            // 3. Un-choose (Backtrack): Remove the last element to try the next one in the loop
            current_combo.pop_back();
        }
    }

public:
    // Public interface to generate combinations
    vector<vector<int>> generate(const vector<int>& elements, int k) {
        vector<vector<int>> result;
        vector<int> current_combo;
        
        if (k <= 0 || k > elements.size()) {
            cout << "Invalid combination size k.\n";
            return result;
        }

        // Start the backtracking process from index 0
        backtrack(elements, k, 0, current_combo, result);
        
        return result;
    }
};

int main() {
    // Set of elements to choose from
    vector<int> elements = {1, 2, 3, 4, 5};
    
    // Number of elements to pick (k)
    int k = 3;
    
    cout << "Elements: { ";
    for (int num : elements) cout << num << " ";
    cout << "}\n";
    cout << "Choosing " << k << " elements:\n\n";

    // Initialize the Combinations algorithm
    Combinations combo;

    // Generate all combinations
    vector<vector<int>> result = combo.generate(elements, k);

    // Print the results
    cout << "--- Generated Combinations ---\n";
    int count = 1;
    for (const auto& combination : result) {
        cout << count++ << ": [ ";
        for (int num : combination) {
            cout << num << " ";
        }
        cout << "]\n";
    }
    cout << "------------------------------\n";
    cout << "Total combinations found: " << result.size() << "\n";

    return 0;
}
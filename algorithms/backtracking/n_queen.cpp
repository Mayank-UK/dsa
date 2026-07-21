#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class NQueens {
private:
    int n;
    vector<vector<string>> solutions;

    // Core backtracking function
    void backtrack(int row, vector<int>& queens, vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2) {
        // Base case: If all N queens have been placed successfully
        if (row == n) {
            // Translate the column positions into a visual string board
            vector<string> board(n, string(n, '.'));
            for (int i = 0; i < n; i++) {
                board[i][queens[i]] = 'Q';
            }
            solutions.push_back(board);
            return;
        }

        // Try placing a queen in each column of the current row
        for (int col = 0; col < n; col++) {
            // Calculate the unique indices for the main and anti-diagonals
            int d1 = row - col + n - 1; // Top-left to bottom-right diagonal
            int d2 = row + col;         // Top-right to bottom-left diagonal

            // Check if the column or either diagonal is already under attack
            if (!cols[col] && !diag1[d1] && !diag2[d2]) {
                
                // 1. Choose: Place the queen and mark the attack lines
                cols[col] = diag1[d1] = diag2[d2] = true;
                queens.push_back(col);

                // 2. Explore: Move to the next row
                backtrack(row + 1, queens, cols, diag1, diag2);

                // 3. Un-choose (Backtrack): Remove the queen and unmark the attack lines
                queens.pop_back();
                cols[col] = diag1[d1] = diag2[d2] = false;
            }
        }
    }

public:
    // Constructor
    NQueens(int size) {
        n = size;
    }

    // Initiates the search
    void solve() {
        vector<int> queens; // Stores the column index of the queen for each row
        
        // Boolean arrays for O(1) attack checks
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n, false); 
        vector<bool> diag2(2 * n, false);

        // Start backtracking from row 0
        backtrack(0, queens, cols, diag1, diag2);

        cout << "--- Search Results ---\n";
        cout << "Found " << solutions.size() << " valid configurations for " << n << " Queens.\n\n";

        // Print up to the first 3 solutions to avoid flooding the console
        int display_limit = min((int)solutions.size(), 3);
        for (int i = 0; i < display_limit; i++) {
            cout << "Solution " << i + 1 << ":\n";
            for (const string& board_row : solutions[i]) {
                cout << board_row << "\n";
            }
            cout << "\n";
        }

        if (solutions.size() > display_limit) {
            cout << "... and " << solutions.size() - display_limit << " more solutions.\n";
        }
        cout << "----------------------\n";
    }
};

int main() {
    // Standard chessboard size
    int n = 8; 
    
    cout << "Calculating N-Queens for N = " << n << "...\n\n";

    // Initialize the N-Queens algorithm
    NQueens nq(n);

    // Perform the search
    nq.solve();

    return 0;
}
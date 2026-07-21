#include <iostream>
#include <vector>

using namespace std;

class SudokuSolver {
private:
    const int N = 9; // Size of the Sudoku grid

    // Utility function to check if placing 'num' at grid[row][col] is valid
    bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
        // 1. Check the current row and column
        for (int x = 0; x < N; x++) {
            if (grid[row][x] == num || grid[x][col] == num) {
                return false;
            }
        }

        // 2. Check the 3x3 subgrid
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i + startRow][j + startCol] == num) {
                    return false;
                }
            }
        }

        return true;
    }

public:
    // Core backtracking function
    bool solve(vector<vector<int>>& grid) {
        int row = -1;
        int col = -1;
        bool isEmpty = false;

        // Find the first empty cell (represented by 0)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) {
                    row = i;
                    col = j;
                    isEmpty = true;
                    break;
                }
            }
            if (isEmpty) {
                break;
            }
        }

        // Base case: If no empty cell is found, the puzzle is solved
        if (!isEmpty) {
            return true;
        }

        // Try placing digits 1 through 9 in the empty cell
        for (int num = 1; num <= 9; num++) {
            if (isSafe(grid, row, col, num)) {
                // 1. Choose: Temporarily assign the number
                grid[row][col] = num;

                // 2. Explore: Recursively attempt to fill the rest of the board
                if (solve(grid)) {
                    // Early Exit: If the recursive call returns true, a valid 
                    // configuration was found. Bubble up immediately.
                    return true;
                }

                // 3. Un-choose (Backtrack): Undo the assignment if it led to a dead end
                grid[row][col] = 0;
            }
        }

        // Trigger backtracking if no digit 1-9 works in this cell
        return false;
    }

    // Utility to format and print the Sudoku grid
    void printGrid(const vector<vector<int>>& grid) {
        for (int i = 0; i < N; i++) {
            if (i % 3 == 0 && i != 0) {
                cout << "---------------------\n";
            }
            for (int j = 0; j < N; j++) {
                if (j % 3 == 0 && j != 0) {
                    cout << "| ";
                }
                if (grid[i][j] == 0) {
                    cout << ". ";
                } else {
                    cout << grid[i][j] << " ";
                }
            }
            cout << "\n";
        }
    }
};

int main() {
    /*
        Sudoku board definition:
        0 represents an empty cell
    */
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    SudokuSolver solver;

    cout << "--- Original Puzzle ---\n";
    solver.printGrid(grid);
    cout << "\nSolving...\n\n";

    if (solver.solve(grid)) {
        cout << "--- Solved Puzzle ---\n";
        solver.printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku board.\n";
    }

    return 0;
}
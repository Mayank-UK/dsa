#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Sudoku solver via backtracking. Find the first empty cell (0), try digits
// 1..9 that satisfy the row, column, and 3x3 box constraints, then recurse.
// If no digit works, the partial assignment is wrong and we backtrack.
class SudokuSolver {
    static bool isSafe(const vector<vector<int>>& g, int row, int col, int num) {
        for (int x = 0; x < 9; x++)
            if (g[row][x] == num || g[x][col] == num) return false;
        int sr = row - row % 3, sc = col - col % 3;   // top-left of the 3x3 box
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (g[sr + i][sc + j] == num) return false;
        return true;
    }
public:
    // Mutates `grid` in place. Returns true if solved, false if unsolvable.
    bool solve(vector<vector<int>>& grid) {
        int row = -1, col = -1;
        bool empty = false;
        for (int i = 0; i < 9 && !empty; i++)
            for (int j = 0; j < 9; j++)
                if (grid[i][j] == 0) { row = i; col = j; empty = true; break; }

        if (!empty) return true;                 // no empty cell -> solved
        for (int num = 1; num <= 9; num++) {
            if (isSafe(grid, row, col, num)) {
                grid[row][col] = num;            // choose
                if (solve(grid)) return true;
                grid[row][col] = 0;              // un-choose
            }
        }
        return false;                            // no digit fits -> trigger backtrack
    }
};

static void printGrid(const vector<vector<int>>& g) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) cout << "    ---------------------\n";
        cout << "    ";
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) cout << "| ";
            cout << (g[i][j] == 0 ? '.' : char('0' + g[i][j])) << " ";
        }
        cout << "\n";
    }
}

int main() {
    cout << "================= Sudoku Solver =================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(9^(n)) worst case   n = empty cells (heavily pruned by constraints)\n";
    cout << "  Space : O(n) recursion depth\n";
    cout << "  Note  : try 1..9 at first empty cell; row/col/box check prunes the tree\n\n";

    cout << "[Demo]\n";
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
    cout << "  puzzle:\n";
    printGrid(grid);
    bool ok = SudokuSolver().solve(grid);
    cout << "  -> " << (ok ? "Solved:" : "No solution exists.") << "\n";
    if (ok) printGrid(grid);
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  already solved board:\n";
    {
        vector<vector<int>> full = {
            {5,3,4,6,7,8,9,1,2},{6,7,2,1,9,5,3,4,8},{1,9,8,3,4,2,5,6,7},
            {8,5,9,7,6,1,4,2,3},{4,2,6,8,5,3,7,9,1},{7,1,3,9,2,4,8,5,6},
            {9,6,1,5,3,7,2,8,4},{2,8,7,4,1,9,6,3,5},{3,4,5,2,8,6,1,7,9}
        };
        cout << "    solved on entry? " << (SudokuSolver().solve(full) ? "Yes" : "No") << "\n";
    }
    cout << "  unsolvable (cell (0,0) has no legal digit):\n";
    {
        vector<vector<int>> bad(9, vector<int>(9, 0));
        // row 0 holds 2..9; cell (0,0) therefore needs 1, but col 0 already has a 1.
        bad[0] = {0, 2, 3, 4, 5, 6, 7, 8, 9};
        bad[1][0] = 1;
        cout << "    solvable? " << (SudokuSolver().solve(bad) ? "Yes" : "No") << "\n";
    }
    cout << "\n";

    return 0;
}

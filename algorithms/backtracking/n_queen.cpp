#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// N-Queens via backtracking. Place one queen per row; for the current row try
// each column and prune with three boolean arrays (column, and the two diagonal
// families) so attack checks are O(1). The diagonal index is what lets a single
// array cover a whole diagonal: diag1 = row - col (+offset), diag2 = row + col.
class NQueens {
    int n;
    void backtrack(int row, vector<int>& queens, vector<bool>& cols,
                   vector<bool>& diag1, vector<bool>& diag2,
                   vector<vector<string>>& solutions) {
        if (row == n) {                       // all rows placed -> record board
            vector<string> board(n, string(n, '.'));
            for (int i = 0; i < n; i++) board[i][queens[i]] = 'Q';
            solutions.push_back(board);
            return;
        }
        for (int col = 0; col < n; col++) {
            int d1 = row - col + n - 1;       // main diagonal index
            int d2 = row + col;               // anti-diagonal index
            if (!cols[col] && !diag1[d1] && !diag2[d2]) {
                cols[col] = diag1[d1] = diag2[d2] = true;   // choose
                queens.push_back(col);
                backtrack(row + 1, queens, cols, diag1, diag2, solutions);
                queens.pop_back();                          // un-choose
                cols[col] = diag1[d1] = diag2[d2] = false;
            }
        }
    }
public:
    vector<vector<string>> solve(int size) {
        n = size;
        vector<vector<string>> solutions;
        if (n <= 0) return solutions;
        vector<int> queens;
        vector<bool> cols(n, false), diag1(2 * n, false), diag2(2 * n, false);
        backtrack(0, queens, cols, diag1, diag2, solutions);
        return solutions;
    }
};

static void printBoard(const vector<string>& board) {
    for (const string& row : board) cout << "      " << row << "\n";
}

int main() {
    cout << "================= N-Queens =================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(N!)        pruned by O(1) column/diagonal attack checks\n";
    cout << "  Space : O(N) recursion + O(N^2) per stored board\n";
    cout << "  Note  : one queen per row; three boolean arrays make attack tests O(1)\n\n";

    cout << "[Demo]\n";
    int n = 4;
    auto solutions = NQueens().solve(n);
    cout << "  N = " << n << " -> " << solutions.size() << " solution(s)\n";
    for (size_t i = 0; i < solutions.size(); i++) {
        cout << "  solution " << (i + 1) << ":\n";
        printBoard(solutions[i]);
    }
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  N = 1 : " << NQueens().solve(1).size() << " solution (the trivial board)\n";
    cout << "  N = 2 : " << NQueens().solve(2).size() << " (no solution)\n";
    cout << "  N = 3 : " << NQueens().solve(3).size() << " (no solution)\n";
    cout << "  N = 8 : " << NQueens().solve(8).size() << " solutions  (the classic count)\n";
    cout << "\n";

    return 0;
}

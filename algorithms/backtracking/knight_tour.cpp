#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Knight's Tour via backtracking. From the current square try each of the 8
// knight moves; recurse until all N*N squares are numbered. A square is safe if
// it is on the board and unvisited. Plain backtracking (no Warnsdorff heuristic).
class KnightTour {
    int N;
    vector<vector<int>> board;
    // The 8 L-shaped moves, paired (dx[i], dy[i]).
    int dx[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
    int dy[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

    bool isSafe(int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1;
    }
    bool solve(int x, int y, int moveCount) {
        if (moveCount == N * N) return true;     // every square visited
        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (isSafe(nx, ny)) {
                board[nx][ny] = moveCount;       // choose
                if (solve(nx, ny, moveCount + 1)) return true;
                board[nx][ny] = -1;              // un-choose
            }
        }
        return false;
    }
public:
    // Returns the move-numbered board, or empty if no tour from (0,0).
    vector<vector<int>> solveFrom(int size, int startX, int startY) {
        N = size;
        board.assign(N, vector<int>(N, -1));     // -1 == unvisited
        if (N <= 0) return board;
        board[startX][startY] = 0;               // start at step 0
        if (!solve(startX, startY, 1)) return {};  // no complete tour
        return board;
    }
};

static void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        cout << "    ";
        for (int v : row) cout << setw(3) << v << " ";
        cout << "\n";
    }
}

int main() {
    cout << "================= Knight's Tour =================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(8^(N^2)) worst case   (8 moves per square)\n";
    cout << "  Space : O(N^2) board + recursion depth O(N^2)\n";
    cout << "  Note  : plain backtracking (no Warnsdorff); feasible for small N\n\n";

    cout << "[Demo]\n";
    int n = 5;
    cout << "  " << n << "x" << n << " board, start = (0,0)\n";
    auto board = KnightTour().solveFrom(n, 0, 0);
    if (board.empty()) {
        cout << "  No complete tour exists.\n";
    } else {
        cout << "  move numbers (0 = start, " << (n * n - 1) << " = last):\n";
        printBoard(board);
    }
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  N = 1 (single square, trivial tour):\n";
    printBoard(KnightTour().solveFrom(1, 0, 0));
    cout << "  N = 3 (no closed-or-open tour from corner): "
         << (KnightTour().solveFrom(3, 0, 0).empty() ? "No tour\n" : "found\n");
    cout << "\n";

    return 0;
}

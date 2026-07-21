#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Size of the chessboard. 
// Set to 5 for instant backtracking execution.
const int N = 5; 

class KnightTour {
private:
    int board[N][N];

    // These arrays define the 8 possible movements for a knight in chess.
    // Pairing xMove[i] and yMove[i] gives one valid directional jump.
    int xMove[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
    int yMove[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

    // Utility function to check if i,j are valid indexes for an N*N chessboard
    bool isSafe(int x, int y) {
        return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
    }

    // A recursive utility function to solve the Knight Tour problem
    bool solveKTUtil(int x, int y, int move_count) {
        // Base case: If all squares are visited, the tour is complete
        if (move_count == N * N) {
            return true;
        }

        // Try all 8 possible next moves for the knight from the current coordinate
        for (int k = 0; k < 8; k++) {
            int next_x = x + xMove[k];
            int next_y = y + yMove[k];

            if (isSafe(next_x, next_y)) {
                // 1. Choose: Record the move sequence number on the board
                board[next_x][next_y] = move_count;

                // 2. Explore: Recurse to see if this choice leads to a solution
                if (solveKTUtil(next_x, next_y, move_count + 1)) {
                    return true;
                }

                // 3. Un-choose (Backtrack): The previous choice resulted in a dead end.
                // Reset the square and try the next move in the loop.
                board[next_x][next_y] = -1;
            }
        }

        // If no move from this square leads to a solution, return false
        return false;
    }

public:
    // Initializes the board and begins the tour
    void solve() {
        // Initialize all squares as unvisited (-1)
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < N; y++) {
                board[x][y] = -1;
            }
        }

        // Place the Knight at the starting position (0, 0)
        // Step 0 is the starting point
        board[0][0] = 0; 

        cout << "--- Search Results ---\n";
        cout << "Calculating Knight's Tour for a " << N << "x" << N << " board...\n\n";

        // Start the recursive backtracking from step 1
        if (!solveKTUtil(0, 0, 1)) {
            cout << "Solution does not exist for this board size and starting position.\n";
        } else {
            printSolution();
        }
        cout << "----------------------\n";
    }

    // Prints the final visited sequence matrix
    void printSolution() {
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < N; y++) {
                // Using setw to align the grid neatly
                cout << setw(3) << board[x][y] << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    // Initialize the Knight Tour algorithm
    KnightTour kt;

    // Perform the search
    kt.solve();

    return 0;
}
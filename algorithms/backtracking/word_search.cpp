#include <iostream>
#include <vector>
#include <string>

using namespace std;

class WordSearch {
private:
    int rows;
    int cols;

    // Core backtracking DFS function
    bool dfs(vector<vector<char>>& board, const string& word, int i, int j, int index) {
        // Base case: If we have matched all characters in the word
        if (index == word.length()) {
            return true;
        }

        // Boundary checks and character match check
        if (i < 0 || i >= rows || j < 0 || j >= cols || board[i][j] != word[index]) {
            return false;
        }

        // 1. Choose: Mark the current cell as visited
        // We temporarily replace the character with a special symbol to avoid reusing it
        char temp = board[i][j];
        board[i][j] = '#';

        // 2. Explore: Recursively check all 4 adjacent directions (Down, Up, Right, Left)
        bool found = dfs(board, word, i + 1, j, index + 1) ||
                     dfs(board, word, i - 1, j, index + 1) ||
                     dfs(board, word, i, j + 1, index + 1) ||
                     dfs(board, word, i, j - 1, index + 1);

        // 3. Un-choose (Backtrack): Restore the original character
        // This frees the cell up for other potential paths
        board[i][j] = temp;

        return found;
    }

public:
    // Public interface to search for the word
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || board[0].empty() || word.empty()) {
            return false;
        }

        rows = board.size();
        cols = board[0].size();

        // Iterate through every cell to find a valid starting point
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // If the first character matches, initiate DFS
                if (board[i][j] == word[0] && dfs(board, word, i, j, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};

int main() {
    // Define the character grid
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };

    WordSearch ws;

    // Test cases
    vector<string> words_to_test = {"ABCCED", "SEE", "ABCB"};

    cout << "--- Word Search Results ---\n";
    for (const string& word : words_to_test) {
        cout << "Word: '" << word << "' -> ";
        if (ws.exist(board, word)) {
            cout << "Found\n";
        } else {
            cout << "Not Found\n";
        }
    }
    cout << "---------------------------\n";

    return 0;
}
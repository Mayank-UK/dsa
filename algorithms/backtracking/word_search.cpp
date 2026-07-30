#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Word Search: does `word` exist as a path in the grid (adjacent cells, no reuse)?
// DFS from every cell whose char matches word[0]; mark the current cell with '#'
// so it can't be reused on this path, then restore it on backtrack.
class WordSearch {
    int rows, cols;
    bool dfs(vector<vector<char>>& board, const string& word, int i, int j, int idx) {
        if (idx == (int)word.length()) return true;          // whole word matched
        if (i < 0 || i >= rows || j < 0 || j >= cols || board[i][j] != word[idx])
            return false;                                    // off-board or mismatch

        char saved = board[i][j];
        board[i][j] = '#';                                   // choose: mark visited
        bool found = dfs(board, word, i + 1, j, idx + 1) ||
                     dfs(board, word, i - 1, j, idx + 1) ||
                     dfs(board, word, i, j + 1, idx + 1) ||
                     dfs(board, word, i, j - 1, idx + 1);
        board[i][j] = saved;                                 // un-choose: restore
        return found;
    }
public:
    bool exist(vector<vector<char>>& board, const string& word) {
        if (board.empty() || board[0].empty() || word.empty()) return false;
        rows = (int)board.size();
        cols = (int)board[0].size();
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (board[i][j] == word[0] && dfs(board, word, i, j, 0))
                    return true;
        return false;
    }
};

int main() {
    cout << "================= Word Search =================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(N * M * 4^L)   N*M start cells, 4 dirs over word length L\n";
    cout << "  Space : O(L) recursion depth\n";
    cout << "  Note  : '#' sentinel marks a cell in-use; restored on backtrack\n\n";

    cout << "[Demo]\n";
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    cout << "  board:\n";
    for (const auto& row : board) {
        cout << "    ";
        for (char c : row) cout << c << " ";
        cout << "\n";
    }
    WordSearch ws;
    vector<string> words = {"ABCCED", "SEE", "ABCB"};
    cout << "  searches:\n";
    for (const string& w : words)
        cout << "    \"" << w << "\" -> " << (ws.exist(board, w) ? "Found" : "Not Found") << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  empty word          : " << (ws.exist(board, "") ? "Found" : "Not Found") << "\n";
    cout << "  single-cell match   : ";
    {
        vector<vector<char>> one = {{'A'}};
        cout << (ws.exist(one, "A") ? "Found" : "Not Found") << "\n";
    }
    cout << "  char not on board   : " << (ws.exist(board, "XYZ") ? "Found" : "Not Found") << "\n";
    cout << "  reuse forbidden     : " << (ws.exist(board, "ABA") ? "Found" : "Not Found")
         << "  (would need cell reuse)\n";
    cout << "\n";

    return 0;
}

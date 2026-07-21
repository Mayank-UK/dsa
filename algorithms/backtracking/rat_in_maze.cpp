#include <iostream>
#include <vector>
#include <string>

using namespace std;

class RatInAMaze {
private:
    int n;
    vector<string> all_paths;

    // Movement arrays for Down, Left, Right, Up (Lexicographical order)
    int dx[4] = {1, 0, 0, -1};
    int dy[4] = {0, -1, 1, 0};
    char dir[4] = {'D', 'L', 'R', 'U'};

    // Utility function to check if the next cell is valid and unvisited
    bool isSafe(int x, int y, const vector<vector<int>>& maze, const vector<vector<bool>>& visited) {
        return (x >= 0 && x < n && y >= 0 && y < n && maze[x][y] == 1 && !visited[x][y]);
    }

    // Core backtracking function
    void backtrack(int x, int y, const vector<vector<int>>& maze, vector<vector<bool>>& visited, string& current_path) {
        // Base case: If the rat reaches the bottom-right corner
        if (x == n - 1 && y == n - 1) {
            all_paths.push_back(current_path);
            return;
        }

        // Try all 4 possible directions from the current cell
        for (int i = 0; i < 4; i++) {
            int next_x = x + dx[i];
            int next_y = y + dy[i];

            if (isSafe(next_x, next_y, maze, visited)) {
                // 1. Choose: Mark the cell as visited and append the direction to the path
                visited[next_x][next_y] = true;
                current_path.push_back(dir[i]);

                // 2. Explore: Move to the next cell recursively
                backtrack(next_x, next_y, maze, visited, current_path);

                // 3. Un-choose (Backtrack): Unmark the cell and remove the direction to try another route
                current_path.pop_back();
                visited[next_x][next_y] = false;
            }
        }
    }

public:
    // Initiates the search for all paths
    void solve(const vector<vector<int>>& maze, int size) {
        n = size;
        all_paths.clear();

        // Edge case: If the start or end point is blocked (0), no path is possible
        if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0) {
            cout << "No path exists. Start or Destination is blocked.\n";
            return;
        }

        vector<vector<bool>> visited(n, vector<bool>(n, false));
        string current_path = "";

        // Mark the starting cell as visited
        visited[0][0] = true;

        // Start backtracking from (0, 0)
        backtrack(0, 0, maze, visited, current_path);

        cout << "--- Search Results ---\n";
        if (all_paths.empty()) {
            cout << "No valid paths found for the rat to reach the destination.\n";
        } else {
            cout << "Found " << all_paths.size() << " valid paths (in lexicographical order):\n";
            for (int i = 0; i < all_paths.size(); i++) {
                cout << i + 1 << ": " << all_paths[i] << "\n";
            }
        }
        cout << "----------------------\n";
    }
};

int main() {
    /*
        Maze matrix definition:
        1 = Open path
        0 = Blocked wall
    */
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    int n = maze.size();

    cout << "Calculating Rat in a Maze paths for a " << n << "x" << n << " grid...\n\n";

    // Initialize the algorithm
    RatInAMaze rat;

    // Perform the search
    rat.solve(maze, n);

    return 0;
}
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Rat in a Maze: all paths from (0,0) to (n-1,n-1) over open cells (1), printed
// in lexicographic order. From each cell try D,L,R,U (in that order so output is
// naturally sorted); recurse onto safe neighbors, marking visited to avoid cycles.
class RatInAMaze {
    int n;
    int dx[4] = {1, 0, 0, -1};   // D, L, R, U  -> lexicographic order
    int dy[4] = {0, -1, 1, 0};
    char dir[4] = {'D', 'L', 'R', 'U'};

    bool safe(int x, int y, const vector<vector<int>>& maze, const vector<vector<bool>>& vis) {
        return x >= 0 && x < n && y >= 0 && y < n && maze[x][y] == 1 && !vis[x][y];
    }
    void backtrack(int x, int y, const vector<vector<int>>& maze,
                   vector<vector<bool>>& vis, string& cur, vector<string>& paths) {
        if (x == n - 1 && y == n - 1) { paths.push_back(cur); return; }  // reached goal
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (safe(nx, ny, maze, vis)) {
                vis[nx][ny] = true;            // choose
                cur.push_back(dir[i]);
                backtrack(nx, ny, maze, vis, cur, paths);
                cur.pop_back();                // un-choose
                vis[nx][ny] = false;
            }
        }
    }
public:
    // Returns all direction-strings; empty vector if start/goal blocked or unreachable.
    vector<string> solve(const vector<vector<int>>& maze) {
        n = (int)maze.size();
        vector<string> paths;
        if (n == 0 || maze[0][0] == 0 || maze[n - 1][n - 1] == 0) return paths;
        vector<vector<bool>> vis(n, vector<bool>(n, false));
        vis[0][0] = true;
        string cur;
        backtrack(0, 0, maze, vis, cur, paths);
        return paths;
    }
};

int main() {
    cout << "================ Rat in a Maze =================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(4^(n^2)) worst case   (4 moves per cell)\n";
    cout << "  Space : O(n^2) visited grid + recursion depth O(n^2)\n";
    cout << "  Note  : D,L,R,U order yields lexicographically sorted paths\n\n";

    cout << "[Demo]\n";
    // 1 = open, 0 = wall
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    cout << "  maze (" << maze.size() << "x" << maze.size() << "):\n";
    for (const auto& row : maze) {
        cout << "    ";
        for (int c : row) cout << c << " ";
        cout << "\n";
    }
    auto paths = RatInAMaze().solve(maze);
    cout << "  " << paths.size() << " path(s) from (0,0) to (3,3):\n";
    for (size_t i = 0; i < paths.size(); i++)
        cout << "    " << (i + 1) << ": " << paths[i] << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  start blocked (maze[0][0]=0): "
         << RatInAMaze().solve({{0,1},{1,1}}).size() << " path(s)\n";
    cout << "  goal blocked (maze[n-1][n-1]=0): "
         << RatInAMaze().solve({{1,1},{1,0}}).size() << " path(s)\n";
    cout << "  no route (wall seals the goal): "
         << RatInAMaze().solve({{1,1,0},{0,1,0},{0,0,1}}).size() << " path(s)\n";
    cout << "  single open cell: "
         << RatInAMaze().solve({{1}}).size() << " path(s)  (empty string = already there)\n";
    cout << "\n";

    return 0;
}

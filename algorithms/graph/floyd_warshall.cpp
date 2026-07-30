#include <iostream>
#include <vector>
#include <climits>
#include <string>

using namespace std;

const long long INF = LLONG_MAX;

struct FWResult {
    vector<vector<long long>> dist;
    bool hasNegativeCycle;
};

// Floyd-Warshall: all-pairs shortest paths. Try every vertex k as an
// intermediate: dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]).
FWResult floydWarshall(int n, const vector<vector<long long>>& graph) {
    vector<vector<long long>> dist = graph;

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    // A negative value on the diagonal means a negative cycle through that node.
    bool neg = false;
    for (int i = 1; i <= n; i++)
        if (dist[i][i] < 0) { neg = true; break; }

    return {dist, neg};
}

static void printMatrix(const vector<vector<long long>>& dist) {
    for (int i = 1; i < (int)dist.size(); i++) {
        cout << "    ";
        for (int j = 1; j < (int)dist.size(); j++) {
            if (dist[i][j] == INF) cout << "INF\t"; else cout << dist[i][j] << "\t";
        }
        cout << "\n";
    }
}

int main() {
    cout << "=================== Floyd-Warshall ===================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(V^3)\n";
    cout << "  Space : O(V^2)\n";
    cout << "  Note  : ALL-PAIRS shortest paths; detects negative cycles\n\n";

    cout << "[Demo]\n";
    int n = 4;
    vector<vector<long long>> g(n + 1, vector<long long>(n + 1, INF));
    for (int i = 1; i <= n; i++) g[i][i] = 0;
    g[1][3] = -2; g[1][2] = 3; g[2][4] = 1; g[3][4] = 4; g[3][2] = 5;
    auto r = floydWarshall(n, g);
    cout << "  directed graph (adjacency matrix)\n";
    cout << "  negative cycle? " << (r.hasNegativeCycle ? "Yes" : "No") << "\n";
    cout << "  all-pairs distance matrix:\n";
    printMatrix(r.dist);
    cout << "\n";

    cout << "[Cases]  (graph with a negative cycle)\n";
    vector<vector<long long>> gc(3 + 1, vector<long long>(3 + 1, INF));
    for (int i = 1; i <= 3; i++) gc[i][i] = 0;
    gc[1][2] = 1; gc[2][3] = -3; gc[3][1] = 1;
    auto rc = floydWarshall(3, gc);
    cout << "  negative cycle? " << (rc.hasNegativeCycle ? "Yes (detected)" : "No") << "\n\n";

    cout << "[Edge Cases]\n";
    cout << "  single node : dist(1->1) = " << floydWarshall(1, {{0,0},{0,0}}).dist[1][1] << "\n";
    cout << "  two nodes, no path 1->2 : ";
    vector<vector<long long>> t(2 + 1, vector<long long>(2 + 1, INF));
    t[1][1] = t[2][2] = 0;
    auto d2 = floydWarshall(2, t).dist;
    cout << (d2[1][2] == INF ? "INF" : to_string(d2[1][2])) << "\n";
    cout << "\n";

    return 0;
}

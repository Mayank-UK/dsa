#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Disjoint Set Union with path compression + union by rank.
class DSU {
private:
    vector<int> parent;
    vector<int> rank_;
    int numComponents;

public:
    DSU(int n) {
        parent.resize(n + 1);
        rank_.resize(n + 1, 0);
        numComponents = n;
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    // Find with path compression (flattens the tree on the way up).
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    // Union by rank: smaller tree goes under the larger.
    void unite(int i, int j) {
        int ri = find(i), rj = find(j);
        if (ri == rj) return;

        if (rank_[ri] < rank_[rj]) parent[ri] = rj;
        else if (rank_[ri] > rank_[rj]) parent[rj] = ri;
        else { parent[rj] = ri; rank_[ri]++; }
        numComponents--;
    }

    bool connected(int i, int j) { return find(i) == find(j); }
    int getComponentCount() { return numComponents; }
};

static string yesNo(bool b) { return b ? "Yes" : "No"; }

int main() {
    cout << "=============== Union-Find (DSU) ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(alpha(n)) per op ~ amortized O(1)   (inverse Ackermann)\n";
    cout << "  Space : O(n)\n";
    cout << "  Note  : path compression + union by rank\n\n";

    cout << "[Demo]\n";
    DSU dsu(5);
    cout << "  initial components : " << dsu.getComponentCount() << "  (n=5)\n";
    dsu.unite(1, 2); cout << "  unite(1,2) -> " << dsu.getComponentCount() << "\n";
    dsu.unite(3, 4); cout << "  unite(3,4) -> " << dsu.getComponentCount() << "\n";
    dsu.unite(2, 4); cout << "  unite(2,4) -> " << dsu.getComponentCount() << "  ({1,2,3,4} merge)\n";
    cout << "  connected(1,3)? " << yesNo(dsu.connected(1, 3)) << "\n";
    cout << "  connected(1,5)? " << yesNo(dsu.connected(1, 5)) << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    DSU single(1);
    cout << "  single element    : find(1)=" << single.find(1)
         << ", components=" << single.getComponentCount() << "\n";
    DSU selfU(3);
    selfU.unite(2, 2);  // unite with itself
    cout << "  unite(x,x) no-op : components=" << selfU.getComponentCount() << "\n";
    cout << "\n";

    return 0;
}

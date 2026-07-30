#include <iostream>
#include <vector>

using namespace std;

// ============================================================
// Sparse Table — O(1) range queries on a STATIC array, for IDEMPOTENT ops
// (min, max, gcd). st[j][i] holds the result over the range of length 2^j
// starting at i. A query [L..R] takes two overlapping 2^k blocks (k = floor
// log2 of the length) — overlap is harmless for idempotent ops, hence the
// O(1). NOT suitable for sum/product (non-idempotent): overlap double-counts;
// use a Fenwick/segment tree there. Build O(n log n), no updates supported.
// ============================================================
class SparseTable {
private:
    vector<vector<int>> st;   // st[j][i] = op over [i, i + 2^j - 1]
    vector<int> logTable;
    int n;

public:
    // ─── Build ───  Time: O(n log n)   Space: O(n log n)
    void build(const vector<int>& arr) {
        n = (int)arr.size();

        // floor-log2 lookup table, 1-based.
        logTable.resize(n + 1);
        logTable[1] = 0;
        for (int i = 2; i <= n; i++)
            logTable[i] = logTable[i / 2] + 1;

        int maxLog = logTable[n];
        st.assign(maxLog + 1, vector<int>(n));

        for (int i = 0; i < n; i++)                // level 0: length 1
            st[0][i] = arr[i];

        for (int j = 1; j <= maxLog; j++) {        // level j: length 2^j
            int length = 1 << j;
            for (int i = 0; i + length <= n; i++)
                st[j][i] = min(st[j - 1][i],
                               st[j - 1][i + (length >> 1)]);
        }
    }

    SparseTable(const vector<int>& arr) { build(arr); }

    // ─── Range Minimum Query [left, right] ───  Time: O(1)
    int query(int left, int right) {
        int len = right - left + 1;
        int k = logTable[len];
        return min(st[k][left],
                   st[k][right - (1 << k) + 1]);    // two overlapping 2^k blocks
    }

    void printTable() {
        cout << "  level | values" << endl;
        for (int j = 0; j < (int)st.size(); j++) {
            cout << "    " << j << " (len " << (1 << j) << ") | ";
            for (int val : st[j]) cout << val << " ";
            cout << endl;
        }
    }
};

// ============================================================
int main() {

    cout << "==================== Sparse Table (RMQ) ====================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  build : O(n log n)   (one level per power of two)" << endl;
    cout << "  query : O(1)         (two overlapping blocks of size 2^k)" << endl;
    cout << "  space : O(n log n)" << endl;
    cout << "  Notes : IDEMPOTENT ops only (min/max/gcd). No updates — static array." << endl;

    vector<int> arr = {1, 3, 2, 7, 9, 11, 3, 5, 6, 8};
    SparseTable table(arr);

    cout << endl;
    cout << "[Build]  arr = {1,3,2,7,9,11,3,5,6,8}" << endl;
    table.printTable();

    cout << endl;
    cout << "[Queries]  RMQ(L,R) = min of two overlapping 2^k blocks" << endl;
    cout << "  RMQ(0,4) = " << table.query(0, 4) << "  (min of 1,3,2,7,9)" << endl;
    cout << "  RMQ(3,8) = " << table.query(3, 8) << "  (min of 7,9,11,3,5,6)" << endl;
    cout << "  RMQ(2,6) = " << table.query(2, 6) << "  (min of 2,7,9,11,3)" << endl;
    cout << "  RMQ(5,9) = " << table.query(5, 9) << "  (min of 11,3,5,6,8)" << endl;

    // Self-verify every range against a naive scan.
    cout << endl;
    cout << "[Verify]  cross-check every range vs naive min";
    bool ok = true;
    int n = (int)arr.size();
    for (int L = 0; L < n && ok; L++)
        for (int R = L; R < n; R++) {
            int naive = arr[L];
            for (int i = L; i <= R; i++) naive = min(naive, arr[i]);
            if (naive != table.query(L, R)) { ok = false; break; }
        }
    cout << " : " << (ok ? "All ranges match" : "MISMATCH") << endl;

    cout << endl;
    cout << "[Edge Cases]" << endl;
    SparseTable single({42});
    cout << "  Single-element {42}: RMQ(0,0) = " << single.query(0, 0) << endl;
    cout << "  Full range on main array RMQ(0,9) = " << table.query(0, 9)
         << "  (global min)" << endl;
    cout << "  Length-1 range RMQ(4,4) = " << table.query(4, 4) << "  (= arr[4] = 9)" << endl;

    cout << endl;
    cout << "[Note]  For range SUM use a Fenwick/segment tree instead — the two-block" << endl;
    cout << "       overlap here would double-count. For min/max with UPDATES, a segment" << endl;
    cout << "       tree is required. See tree/fenwick_operations.cpp," << endl;
    cout << "       tree/segment_tree_operations.cpp." << endl;

    return 0;
}

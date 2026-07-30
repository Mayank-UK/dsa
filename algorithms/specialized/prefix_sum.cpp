#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// ============================================================
// Prefix Sum — O(1) range-sum queries after an O(n) precompute.
// prefix[i] = arr[0] + ... + arr[i], so sum(L..R) = prefix[R] - prefix[L-1].
// The complement of difference_array.cpp: this is the read-heavy / write-light
// structure (build once, query many); difference array is write-heavy / read-light.
// ============================================================
class PrefixSum {
private:
    vector<long long> prefix;

public:
    // ─── Build ───  Time: O(n)   Space: O(n)
    PrefixSum(const vector<int>& arr) {
        int n = (int)arr.size();
        prefix.resize(n);
        if (n == 0) return;

        prefix[0] = arr[0];
        for (int i = 1; i < n; i++)
            prefix[i] = prefix[i - 1] + arr[i];
    }

    // ─── Range sum [L, R] inclusive ───  Time: O(1)
    long long query(int L, int R) {
        if (L == 0) return prefix[R];
        return prefix[R] - prefix[L - 1];
    }

    // ─── Expose prefix array for the demo ───
    const vector<long long>& table() const { return prefix; }
};

// ============================================================
int main() {

    cout << "==================== Prefix Sum ====================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  build : O(n)   (one running-sum pass)" << endl;
    cout << "  query : O(1)   (prefix[R] - prefix[L-1])" << endl;
    cout << "  space : O(n)   (one prefix value per element)" << endl;
    cout << "  Notes : static array — rebuild needed if arr changes." << endl;

    vector<int> arr = {2, 4, 0, 5, 1, 9};
    PrefixSum ps(arr);

    cout << endl;
    cout << "[Build]  arr = {2, 4, 0, 5, 1, 9}" << endl;
    cout << "  prefix = ";
    for (long long v : ps.table()) cout << v << " ";
    cout << endl;

    cout << endl;
    cout << "[Queries]  sum(L..R) = prefix[R] - prefix[L-1]" << endl;
    cout << "  sum(1,3) = 4+0+5            = " << ps.query(1, 3) << endl;
    cout << "  sum(0,5) = whole array      = " << ps.query(0, 5) << endl;
    cout << "  sum(2,4) = 0+5+1            = " << ps.query(2, 4) << endl;
    cout << "  sum(0,0) = single element   = " << ps.query(0, 0) << endl;
    cout << "  sum(4,5) = 1+9              = " << ps.query(4, 5) << endl;

    // Self-verify against a naive recompute of every range.
    cout << endl;
    cout << "[Verify]  cross-check every range vs naive O(n) sum";
    bool ok = true;
    int n = (int)arr.size();
    for (int L = 0; L < n && ok; L++)
        for (int R = L; R < n; R++) {
            long long naive = 0;
            for (int i = L; i <= R; i++) naive += arr[i];
            if (naive != ps.query(L, R)) { ok = false; break; }
        }
    cout << " : " << (ok ? "All ranges match" : "MISMATCH") << endl;

    cout << endl;
    cout << "[Edge Cases]" << endl;
    vector<int> one = {42};
    PrefixSum single(one);
    cout << "  Single-element {42}: sum(0,0) = " << single.query(0, 0) << endl;

    PrefixSum empty({});
    cout << "  Empty array: built cleanly, no queries issued (guarded)." << endl;

    cout << endl;
    cout << "[Note]  For a MUTATING array (point/range updates + range sums)," << endl;
    cout << "       use a Fenwick tree or segment tree instead — see" << endl;
    cout << "       tree/fenwick_operations.cpp and tree/segment_tree_operations.cpp." << endl;

    return 0;
}

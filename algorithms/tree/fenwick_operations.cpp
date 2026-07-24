#include <iostream>
#include <vector>
using namespace std;

// ============================================================
// Fenwick Tree (Binary Indexed Tree) — prefix/range-sum demo.
// Vector-backed: RAII manages all memory, no destructor needed.
// ============================================================
class FenwickTree {
private:
    vector<int> tree;
    int n;

public:

    // ─── Empty constructor ───
    FenwickTree(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }

    // ─── Build from Array ───  Time: O(n log n) via n updates
    FenwickTree(const vector<int>& arr) {
        n = (int)arr.size();
        tree.assign(n + 1, 0);
        for (int i = 0; i < n; i++)
            update(i, arr[i]);
    }

    // ─── Point Update: add delta at index ───  Time: O(log n)
    void update(int index, int value) {

        index++;    // Convert to 1-based indexing (BIT stores freq at i+1)

        while (index <= n) {
            tree[index] += value;
            index += index & (-index);   // next responsible range
        }
    }

    // ─── Prefix Sum [0...index] ───  Time: O(log n)
    int prefixSum(int index) {

        index++;

        int sum = 0;

        while (index > 0) {
            sum += tree[index];
            index -= index & (-index);   // strip lowest set bit
        }

        return sum;
    }

    // ─── Range Sum [left...right] ───  Time: O(log n)
    int rangeSum(int left, int right) {

        if (left > right)
            return 0;

        return prefixSum(right)
             - (left > 0 ? prefixSum(left - 1) : 0);
    }

    // ─── Set Value at Index (delta = new - current) ───  Time: O(log n)
    void setValue(int index, int newValue) {
        int currentValue = rangeSum(index, index);
        update(index, newValue - currentValue);
    }

    // ─── Get Value at Index ───  Time: O(log n)
    int getValue(int index) {
        return rangeSum(index, index);
    }

    // ─── Print internal Fenwick array (1-based) ───
    void printTree() {
        cout << "Fenwick internal tree (1-based): ";
        for (int i = 1; i <= n; i++)
            cout << tree[i] << " ";
        cout << endl;
    }
};

// ============================================================
int main() {

    cout << "================== Fenwick Tree Operations =================="
         << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  build       : O(n log n)  (n point-updates; O(n) linear build exists)" << endl;
    cout << "  update      : O(log n)    (add delta: climb the responsible ranges)" << endl;
    cout << "  prefixSum   : O(log n)    (strip lowest set bit each step)" << endl;
    cout << "  rangeSum    : O(log n)    (two prefix sums)" << endl;
    cout << "  space       : O(n)        (1-based array of size n+1)" << endl;

    cout << endl;
    cout << "[Demo]  build from {1,2,3,4,5,6,7,8}" << endl;
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8};
    FenwickTree ft(arr);
    ft.printTree();

    cout << endl;
    cout << "  Prefix / range sums (BEFORE any update):" << endl;
    cout << "    prefixSum(4) = 1+2+3+4+5 = " << ft.prefixSum(4) << endl;
    cout << "    rangeSum(2,6) = 3+4+5+6+7 = " << ft.rangeSum(2, 6) << endl;
    cout << "    rangeSum(0,7) = whole array = " << ft.rangeSum(0, 7) << endl;

    cout << endl;
    cout << "  Update by delta: update(3, +10)  (arr[3] was 4 -> 14)" << endl;
    ft.update(3, 10);
    cout << "    value at index 3 = " << ft.getValue(3)
         << "  (marked expected: 14)" << endl;
    cout << "  AFTER delta update:" << endl;
    cout << "    rangeSum(2,6) = 3+14+5+6+7 = " << ft.rangeSum(2, 6)
         << "  (was 25 -> now 35)" << endl;
    cout << "    rangeSum(0,3) = 1+2+3+14 = " << ft.rangeSum(0, 3)
         << "  (was 10 -> now 20)" << endl;

    cout << endl;
    cout << "  Set absolute value: setValue(5, 100)  (arr[5] was 6 -> 100)" << endl;
    cout << "    value at index 5 BEFORE = "
         << (ft.setValue(5, 6), ft.getValue(5)) << "  (reset to original 6)" << endl;
    ft.setValue(5, 100);
    cout << "    value at index 5 AFTER  = " << ft.getValue(5)
         << "  (marked expected: 100)" << endl;
    cout << "  AFTER setValue:" << endl;
    cout << "    rangeSum(0,7) = whole array = " << ft.rangeSum(0, 7)
         << "  (hand sum 1+2+3+14+5+100+7+8 = 140)" << endl;

    cout << endl;
    cout << "[Edge Cases]" << endl;
    FenwickTree single(vector<int>{42});
    cout << "  Single-element array {42}:" << endl;
    cout << "    prefixSum(0) = " << single.prefixSum(0) << endl;
    cout << "    rangeSum(0,0) = whole array = " << single.rangeSum(0, 0) << endl;
    single.update(0, 8);
    cout << "    after update(0, +8): prefixSum(0) = " << single.prefixSum(0)
         << "  (marked: 50)" << endl;

    cout << endl;
    cout << "  Whole-array range (0,7) recomputed = " << ft.rangeSum(0, 7) << endl;
    cout << "  Length-1 range(4,4) = " << ft.rangeSum(4, 4)
         << "  (marked expected: arr[4] = 5, unchanged)" << endl;

    cout << endl;
    cout << "[Note]  Fenwick/BIT supports ONLY invertible associative ops (sum here)," << endl;
    cout << "       but is simpler and faster than a segment tree for those ops. For" << endl;
    cout << "       non-invertible ops (min/max/gcd) use a segment tree instead —" << endl;
    cout << "       see segment_tree_operations.cpp." << endl;

    return 0;
}

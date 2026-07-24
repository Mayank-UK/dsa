#include <iostream>
#include <vector>
using namespace std;

// ============================================================
// Segment Tree — range-sum point-update demo (array-backed).
// Vector-backed: RAII manages all memory, no destructor needed.
// ============================================================
class SegmentTree {
private:
    vector<int> tree;
    vector<int> arr;
    int n;

    // ─── Build ───  Time: O(n)
    void build(int node, int start, int end) {

        if (start == end) {
            tree[node] = arr[start];
            return;
        }

        int mid = start + (end - start) / 2;

        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // ─── Point Update (recursive) ───  Time: O(log n)
    void update(int node,
                int start,
                int end,
                int index,
                int value) {

        if (start == end) {
            arr[index] = value;
            tree[node] = value;
            return;
        }

        int mid = start + (end - start) / 2;

        if (index <= mid)
            update(2 * node, start, mid, index, value);
        else
            update(2 * node + 1, mid + 1, end, index, value);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // ─── Range Sum Query ───  Time: O(log n)
    int query(int node,
              int start,
              int end,
              int left,
              int right) {

        // No overlap
        if (right < start || end < left)
            return 0;

        // Complete overlap
        if (left <= start && end <= right)
            return tree[node];

        // Partial overlap
        int mid = start + (end - start) / 2;

        return query(2 * node, start, mid, left, right)
             + query(2 * node + 1, mid + 1, end, left, right);
    }

    // ─── Print leaves ───
    void print(int node, int start, int end) {

        if (start == end) {
            cout << "[" << start << "] = " << tree[node] << endl;
            return;
        }

        int mid = start + (end - start) / 2;

        print(2 * node, start, mid);
        print(2 * node + 1, mid + 1, end);
    }

public:

    SegmentTree(const vector<int>& input) {
        arr = input;
        n = (int)arr.size();
        tree.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    // ─── Update wrapper ───
    void update(int index, int value) {
        update(1, 0, n - 1, index, value);
    }

    // ─── Query wrapper ───
    int rangeSum(int left, int right) {
        return query(1, 0, n - 1, left, right);
    }

    // ─── Single value (via range query of length 1) ───
    int getValue(int index) {
        return rangeSum(index, index);
    }

    // ─── Print current array ───
    void printArray() {
        cout << "Array: ";
        for (int value : arr)
            cout << value << " ";
        cout << endl;
    }

    // ─── Print segment-tree leaves (per-index values) ───
    void printTree() {
        cout << "Leaf Nodes:" << endl;
        print(1, 0, n - 1);
    }
};

// ============================================================
int main() {

    cout << "================== Segment Tree Operations =================="
         << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  build        : O(n)        (one pass over the leaves)" << endl;
    cout << "  point update : O(log n)    (descend one root-to-leaf path)" << endl;
    cout << "  range query  : O(log n)    (at most 4 nodes per level visited)" << endl;
    cout << "  space        : O(4n)       (tree sized for 1-based 2*node indexing)" << endl;

    cout << endl;
    cout << "[Demo]  build from {1,2,3,4,5,6,7,8}" << endl;
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8};
    SegmentTree tree(arr);
    tree.printArray();

    cout << endl;
    cout << "  Range sums (BEFORE update):" << endl;
    cout << "    rangeSum(0,3) = 1+2+3+4 = " << tree.rangeSum(0, 3) << endl;
    cout << "    rangeSum(2,6) = 3+4+5+6+7 = " << tree.rangeSum(2, 6) << endl;
    cout << "    rangeSum(0,7) = whole array = " << tree.rangeSum(0, 7) << endl;

    cout << endl;
    cout << "  Point update: arr[3] = 20  (was 4, delta +16)" << endl;
    tree.update(3, 20);
    tree.printArray();

    cout << endl;
    cout << "  Range sums (AFTER update):" << endl;
    cout << "    rangeSum(0,3) = 1+2+3+20 = " << tree.rangeSum(0, 3) << endl;
    cout << "    rangeSum(2,6) = 3+20+5+6+7 = " << tree.rangeSum(2, 6) << endl;
    cout << "    rangeSum(0,7) = whole array = " << tree.rangeSum(0, 7) << endl;
    cout << "  (rangeSum(0,3): 10 -> 26 ; rangeSum(2,6): 25 -> 41)" << endl;

    cout << endl;
    cout << "[Edge Cases]" << endl;
    vector<int> one = {42};
    SegmentTree single(one);
    cout << "  Single-element array {42}:" << endl;
    cout << "    rangeSum(0,0) = whole array = " << single.rangeSum(0, 0) << endl;
    cout << "    after update(0, 99): rangeSum(0,0) = " << (single.update(0, 99), single.rangeSum(0, 0)) << endl;

    cout << endl;
    cout << "  Length-1 range on 8-element tree:" << endl;
    cout << "    rangeSum(5,5) = " << tree.rangeSum(5, 5)
         << "  (marked value: arr[5] = 6)" << endl;

    cout << endl;
    cout << "  Whole-array range (0,7) recomputed = " << tree.rangeSum(0, 7)
         << "  (hand sum 1+2+3+20+5+6+7+8 = 52)" << endl;

    cout << endl;
    cout << "[Stats]  segment-tree leaves (one per array index):" << endl;
    tree.printTree();

    cout << endl;
    cout << "[Note]  Segment tree is the GENERAL range-query structure: it works" << endl;
    cout << "       for ANY associative op (sum / min / max / gcd ...). For prefix-sum" << endl;
    cout << "       queries specifically, a Fenwick/BIT is simpler and faster but only" << endl;
    cout << "       supports invertible ops — see fenwick_operations.cpp." << endl;

    return 0;
}

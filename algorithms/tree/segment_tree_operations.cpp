#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    vector<int> arr;
    int n;

    // ----------------------------------------------------------
    // Build Segment Tree
    // Time: O(n)
    // ----------------------------------------------------------
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

    // ----------------------------------------------------------
    // Point Update
    // Time: O(log n)
    // ----------------------------------------------------------
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

    // ----------------------------------------------------------
    // Range Sum Query
    // Time: O(log n)
    // ----------------------------------------------------------
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

        return query(2 * node,
                     start,
                     mid,
                     left,
                     right)
             +
               query(2 * node + 1,
                     mid + 1,
                     end,
                     left,
                     right);
    }

    // ----------------------------------------------------------
    // Print Tree
    // ----------------------------------------------------------
    void print(int node,
               int start,
               int end) {

        if (start == end) {

            cout << "[" << start << "] = "
                 << tree[node]
                 << endl;

            return;
        }

        int mid = start + (end - start) / 2;

        print(2 * node, start, mid);
        print(2 * node + 1, mid + 1, end);
    }

public:

    SegmentTree(const vector<int>& input) {

        arr = input;
        n = arr.size();

        tree.assign(4 * n, 0);

        build(1, 0, n - 1);
    }

    // ----------------------------------------------------------
    // Update Wrapper
    // ----------------------------------------------------------
    void update(int index, int value) {

        update(1,
               0,
               n - 1,
               index,
               value);
    }

    // ----------------------------------------------------------
    // Query Wrapper
    // ----------------------------------------------------------
    int rangeSum(int left, int right) {

        return query(1,
                     0,
                     n - 1,
                     left,
                     right);
    }

    // ----------------------------------------------------------
    // Get Single Value
    // ----------------------------------------------------------
    int getValue(int index) {

        return rangeSum(index, index);
    }

    // ----------------------------------------------------------
    // Print Original Array
    // ----------------------------------------------------------
    void printArray() {

        cout << "Array:\n";

        for (int value : arr)
            cout << value << " ";

        cout << endl;
    }

    // ----------------------------------------------------------
    // Print Segment Tree Leaves
    // ----------------------------------------------------------
    void printTree() {

        cout << "\nLeaf Nodes:\n";

        print(1, 0, n - 1);
    }
};

int main() {

    vector<int> arr = {
        1,2,3,4,5,6,7,8
    };

    SegmentTree tree(arr);

    tree.printArray();

    cout << "\nRange Sum (0,3): "
         << tree.rangeSum(0,3)
         << endl;

    cout << "Range Sum (2,6): "
         << tree.rangeSum(2,6)
         << endl;

    cout << "\nUpdate index 3 -> 20\n";

    tree.update(3,20);

    tree.printArray();

    cout << "\nValue at index 3: "
         << tree.getValue(3)
         << endl;

    cout << "\nRange Sum (0,3): "
         << tree.rangeSum(0,3)
         << endl;

    cout << "Range Sum (2,6): "
         << tree.rangeSum(2,6)
         << endl;

    tree.printTree();

    return 0;
}
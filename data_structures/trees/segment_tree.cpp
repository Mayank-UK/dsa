#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {

private:

    vector<int> tree;
    vector<int> arr;

    int n;

    // ---------------- Build ----------------

    void build(int node, int start, int end) {

        if (start == end) {

            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;

        build(2 * node, start, mid);

        build(2 * node + 1, mid + 1, end);

        tree[node] =
            tree[2 * node] +
            tree[2 * node + 1];
    }

    // ---------------- Range Query ----------------

    int query(int node, int start, int end, int left, int right) {

        // No overlap

        if (right < start ||
            left > end)
            return 0;

        // Complete overlap

        if (left <= start &&
            end <= right)
            return tree[node];

        // Partial overlap

        int mid = (start + end) / 2;

        int leftSum =
            query(2 * node, start, mid, left, right);

        int rightSum =
            query(2 * node + 1, mid + 1, end, left, right);

        return leftSum + rightSum;
    }

    // ---------------- Point Update ----------------

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

        int mid = (start + end) / 2;

        if (index <= mid)
            update(2 * node, start, mid, index, value);

        else
            update(2 * node + 1, mid + 1, end, index, value);

        tree[node] =
            tree[2 * node] +
            tree[2 * node + 1];
    }

public:

    SegmentTree(vector<int> values) {

        arr = values;

        n = arr.size();

        tree.resize(4 * n);

        build(1, 0, n - 1);
    }

    // ---------------- Range Sum ----------------

    int rangeSum(int left, int right) {

        return query(1, 0, n - 1, left, right);
    }

    // ---------------- Update ----------------

    void update(int index,
                int value) {

        update(1, 0, n - 1, index, value);
    }

    // ---------------- Display Original Array ----------------

    void displayArray() {

        for (int value : arr)
            cout << value << " ";

        cout << endl;
    }

    // ---------------- Display Tree ----------------

    void displayTree() {

        cout << "Segment Tree:\n";

        for (int i = 1; i < 2 * n; i++)
            cout << tree[i] << " ";

        cout << endl;
    }

        // ---------------- Size ----------------

    int size() {

        return n;
    }

    // ---------------- Value At Index ----------------

    int at(int index) {

        if (index < 0 || index >= n)
            return -1;

        return arr[index];
    }

    // ---------------- Total Sum ----------------

    int totalSum() {

        if (n == 0)
            return 0;

        return tree[1];
    }

    // ---------------- Minimum (Brute Force) ----------------

    int minimum() {

        if (n == 0)
            return -1;

        int minimum = arr[0];

        for (int value : arr)
            if (value < minimum)
                minimum = value;

        return minimum;
    }

    // ---------------- Maximum (Brute Force) ----------------

    int maximum() {

        if (n == 0)
            return -1;

        int maximum = arr[0];

        for (int value : arr)
            if (value > maximum)
                maximum = value;

        return maximum;
    }

};

int main() {

    vector<int> values = {
        2, 4, 5, 7,
        8, 9, 1, 6
    };

    SegmentTree tree(values);

    cout << "===== Original Array =====\n";
    tree.displayArray();

    cout << "\n===== Segment Tree =====\n";
    tree.displayTree();

    cout << "\n===== Range Sum Queries =====\n";

    cout << "Sum [0, 3] = " << tree.rangeSum(0, 3) << endl;

    cout << "Sum [2, 5] = " << tree.rangeSum(2, 5) << endl;

    cout << "Sum [0, 7] = " << tree.rangeSum(0, 7) << endl;

    cout << "Sum [4, 6] = " << tree.rangeSum(4, 6) << endl;

    cout << "\n===== Update =====\n";

    cout << "Update index 3 -> 20\n";

    tree.update(3, 20);

    tree.displayArray();

    cout << "\nNew Segment Tree\n";
    tree.displayTree();

    cout << "\n===== Queries After Update =====\n";

    cout << "Sum [0, 3] = " << tree.rangeSum(0, 3) << endl;

    cout << "Sum [2, 5] = " << tree.rangeSum(2, 5) << endl;

    cout << "Sum [0, 7] = " << tree.rangeSum(0, 7) << endl;

    cout << "\n===== Statistics =====\n";

    cout << "Size      : " << tree.size() << endl;

    cout << "Total Sum : " << tree.totalSum() << endl;

    cout << "Minimum   : " << tree.minimum() << endl;

    cout << "Maximum   : " << tree.maximum() << endl;

    cout << "\nValue at index 5 : " << tree.at(5) << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class SegmentTree
{

private:
    // ---------------- Node ----------------

    struct Node
    {

        int sum;
        int minimum;
        int maximum;
    };

    vector<Node> tree;
    vector<int> arr;

    int n;

    // ---------------- Merge ----------------

    Node merge(Node left, Node right)
    {

        Node result;

        result.sum =
            left.sum +
            right.sum;

        result.minimum =
            min(left.minimum,
                right.minimum);

        result.maximum =
            max(left.maximum,
                right.maximum);

        return result;
    }

    // ---------------- Build ----------------

    void build(int node, int start, int end)
    {

        if (start == end)
        {

            tree[node].sum = arr[start];

            tree[node].minimum = arr[start];

            tree[node].maximum = arr[start];

            return;
        }

        int mid = (start + end) / 2;

        build(2 * node,
              start,
              mid);

        build(2 * node + 1,
              mid + 1,
              end);

        tree[node] =
            merge(tree[2 * node],
                  tree[2 * node + 1]);
    }

    // ---------------- Range Query ----------------

    Node query(int node,
               int start,
               int end,
               int left,
               int right)
    {

        // No overlap

        if (right < start ||
            left > end)
        {

            return {
                0,
                INT_MAX,
                INT_MIN};
        }

        // Complete overlap

        if (left <= start &&
            end <= right)
        {

            return tree[node];
        }

        // Partial overlap

        int mid = (start + end) / 2;

        Node leftResult =
            query(2 * node,
                  start,
                  mid,
                  left,
                  right);

        Node rightResult =
            query(2 * node + 1,
                  mid + 1,
                  end,
                  left,
                  right);

        return merge(leftResult,
                     rightResult);
    }

    // ---------------- Point Update ----------------

    void update(int node,
                int start,
                int end,
                int index,
                int value)
    {

        if (start == end)
        {

            arr[index] = value;

            tree[node].sum = value;

            tree[node].minimum = value;

            tree[node].maximum = value;

            return;
        }

        int mid = (start + end) / 2;

        if (index <= mid)
        {

            update(2 * node,
                   start,
                   mid,
                   index,
                   value);
        }

        else
        {

            update(2 * node + 1,
                   mid + 1,
                   end,
                   index,
                   value);
        }

        tree[node] =
            merge(tree[2 * node],
                  tree[2 * node + 1]);
    }

public:
    // ---------------- Constructor ----------------

    SegmentTree(vector<int> values)
    {

        arr = values;

        n = arr.size();

        tree.resize(4 * n);

        if (n > 0)
            build(1, 0, n - 1);
    }

    // ---------------- Range Query ----------------

    Node rangeQuery(int left, int right)
    {

        if (n == 0)
            return {0, INT_MAX, INT_MIN};

        if (left < 0 ||
            right >= n ||
            left > right)
            return {0, INT_MAX, INT_MIN};

        return query(1,
                     0,
                     n - 1,
                     left,
                     right);
    }

    // ---------------- Range Sum ----------------

    int rangeSum(int left, int right)
    {

        return rangeQuery(left, right).sum;
    }

    // ---------------- Range Minimum ----------------

    int rangeMinimum(int left, int right)
    {

        return rangeQuery(left, right).minimum;
    }

    // ---------------- Range Maximum ----------------

    int rangeMaximum(int left, int right)
    {

        return rangeQuery(left, right).maximum;
    }

    // ---------------- Update ----------------

    void update(int index,
                int value)
    {

        if (n == 0)
            return;

        if (index < 0 ||
            index >= n)
            return;

        update(1,
               0,
               n - 1,
               index,
               value);
    }

    // ---------------- Display Array ----------------

    void displayArray()
    {

        for (int value : arr)
            cout << value << " ";

        cout << endl;
    }

    // ---------------- Display Tree ----------------

    void displayTree()
    {

        cout << "Segment Tree:\n";

        for (int i = 1; i < 2 * n; i++)
        {

            cout << "["
                 << tree[i].sum
                 << ", min="
                 << tree[i].minimum
                 << ", max="
                 << tree[i].maximum
                 << "] ";
        }

        cout << endl;
    }

    // ---------------- Size ----------------

    int size()
    {

        return n;
    }

    // ---------------- Value At Index ----------------

    int at(int index)
    {

        if (index < 0 ||
            index >= n)
            return -1;

        return arr[index];
    }

    // ---------------- Total Sum ----------------

    int totalSum()
    {

        if (n == 0)
            return 0;

        return tree[1].sum;
    }

    // ---------------- Minimum ----------------

    int minimum()
    {

        if (n == 0)
            return -1;

        return tree[1].minimum;
    }

    // ---------------- Maximum ----------------

    int maximum()
    {

        if (n == 0)
            return -1;

        return tree[1].maximum;
    }
};

int main()
{

    vector<int> values = {
        2, 4, 5, 7,
        8, 9, 1, 6};

    SegmentTree tree(values);

    cout << "============= Segment Tree =============\n";

    cout << "\n===== Original Array =====\n";
    tree.displayArray();

    cout << "\n===== Segment Tree =====\n";
    tree.displayTree();

    cout << "\n===== Range Queries =====\n";

    cout << "Range [0, 3]\n";
    cout << "Sum     = " << tree.rangeSum(0, 3) << endl;
    cout << "Minimum = " << tree.rangeMinimum(0, 3) << endl;
    cout << "Maximum = " << tree.rangeMaximum(0, 3) << endl;

    cout << "\nRange [2, 5]\n";
    cout << "Sum     = " << tree.rangeSum(2, 5) << endl;
    cout << "Minimum = " << tree.rangeMinimum(2, 5) << endl;
    cout << "Maximum = " << tree.rangeMaximum(2, 5) << endl;

    cout << "\nRange [0, 7]\n";
    cout << "Sum     = " << tree.rangeSum(0, 7) << endl;
    cout << "Minimum = " << tree.rangeMinimum(0, 7) << endl;
    cout << "Maximum = " << tree.rangeMaximum(0, 7) << endl;

    cout << "\nRange [4, 6]\n";
    cout << "Sum     = " << tree.rangeSum(4, 6) << endl;
    cout << "Minimum = " << tree.rangeMinimum(4, 6) << endl;
    cout << "Maximum = " << tree.rangeMaximum(4, 6) << endl;

    cout << "\n===== Update =====\n";

    cout << "Update index 3 -> 20\n";

    tree.update(3, 20);

    tree.displayArray();

    cout << "\nNew Segment Tree\n";
    tree.displayTree();

    cout << "\n===== Queries After Update =====\n";

    cout << "Range [0, 3]\n";
    cout << "Sum     = " << tree.rangeSum(0, 3) << endl;
    cout << "Minimum = " << tree.rangeMinimum(0, 3) << endl;
    cout << "Maximum = " << tree.rangeMaximum(0, 3) << endl;

    cout << "\nRange [2, 5]\n";
    cout << "Sum     = " << tree.rangeSum(2, 5) << endl;
    cout << "Minimum = " << tree.rangeMinimum(2, 5) << endl;
    cout << "Maximum = " << tree.rangeMaximum(2, 5) << endl;

    cout << "\nRange [0, 7]\n";
    cout << "Sum     = " << tree.rangeSum(0, 7) << endl;
    cout << "Minimum = " << tree.rangeMinimum(0, 7) << endl;
    cout << "Maximum = " << tree.rangeMaximum(0, 7) << endl;

    cout << "\n===== Statistics =====\n";

    cout << "Size      : " << tree.size() << endl;

    cout << "Total Sum : " << tree.totalSum() << endl;

    cout << "Minimum   : " << tree.minimum() << endl;

    cout << "Maximum   : " << tree.maximum() << endl;

    cout << "\nValue at index 5 : "
         << tree.at(5)
         << endl;

    cout << "\n========================================\n";

    return 0;
}
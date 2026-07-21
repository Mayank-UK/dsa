#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<int> tree;
    int n;

public:

    // ----------------------------------------------------------
    // Constructor
    // ----------------------------------------------------------
    FenwickTree(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }

    // ----------------------------------------------------------
    // Build from Array
    // Time: O(n log n)
    // ----------------------------------------------------------
    FenwickTree(const vector<int>& arr) {
        n = arr.size();
        tree.assign(n + 1, 0);

        for (int i = 0; i < n; i++)
            update(i, arr[i]);
    }

    // ----------------------------------------------------------
    // Point Update
    // Add value at index
    // Time: O(log n)
    // ----------------------------------------------------------
    void update(int index, int value) {

        index++;    // Convert to 1-based indexing

        while (index <= n) {
            tree[index] += value;
            index += index & (-index);
        }
    }

    // ----------------------------------------------------------
    // Prefix Sum [0...index]
    // Time: O(log n)
    // ----------------------------------------------------------
    int prefixSum(int index) {

        index++;

        int sum = 0;

        while (index > 0) {
            sum += tree[index];
            index -= index & (-index);
        }

        return sum;
    }

    // ----------------------------------------------------------
    // Range Sum [left...right]
    // Time: O(log n)
    // ----------------------------------------------------------
    int rangeSum(int left, int right) {

        if (left > right)
            return 0;

        return prefixSum(right) -
               (left > 0 ? prefixSum(left - 1) : 0);
    }

    // ----------------------------------------------------------
    // Set Value at Index
    // Time: O(log n)
    // ----------------------------------------------------------
    void setValue(int index, int newValue) {

        int currentValue = rangeSum(index, index);

        update(index, newValue - currentValue);
    }

    // ----------------------------------------------------------
    // Get Value at Index
    // Time: O(log n)
    // ----------------------------------------------------------
    int getValue(int index) {
        return rangeSum(index, index);
    }

    // ----------------------------------------------------------
    // Print Internal Fenwick Tree
    // ----------------------------------------------------------
    void printTree() {

        cout << "Fenwick Tree:\n";

        for (int i = 1; i <= n; i++)
            cout << tree[i] << " ";

        cout << endl;
    }
};

int main() {

    vector<int> arr = {
        1,2,3,4,5,6,7,8
    };

    FenwickTree ft(arr);

    ft.printTree();

    cout << "\nPrefix Sum(4): "
         << ft.prefixSum(4)
         << endl;

    cout << "Range Sum(2,6): "
         << ft.rangeSum(2,6)
         << endl;

    cout << "\nUpdate index 3 by +10\n";

    ft.update(3,10);

    cout << "Range Sum(2,6): "
         << ft.rangeSum(2,6)
         << endl;

    cout << "\nValue at index 3: "
         << ft.getValue(3)
         << endl;

    cout << "\nSet index 5 = 100\n";

    ft.setValue(5,100);

    cout << "Value at index 5: "
         << ft.getValue(5)
         << endl;

    cout << "\nRange Sum(0,7): "
         << ft.rangeSum(0,7)
         << endl;

    return 0;
}
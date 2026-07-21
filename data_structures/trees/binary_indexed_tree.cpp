#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {

private:

    vector<int> bit;
    vector<int> arr;

    int n;

public:

    // ---------------- Constructor ----------------

    FenwickTree(vector<int> values) {

        arr = values;

        n = arr.size();

        bit.resize(n + 1, 0);

        for (int i = 0; i < n; i++)
            update(i, arr[i]);
    }

    // ---------------- Point Update ----------------

    void update(int index,
                int delta) {

        index++;

        while (index <= n) {

            bit[index] += delta;

            index += index & (-index);
        }
    }

    // ---------------- Prefix Sum ----------------

    int prefixSum(int index) {

        index++;

        int sum = 0;

        while (index > 0) {

            sum += bit[index];

            index -= index & (-index);
        }

        return sum;
    }

    // ---------------- Range Sum ----------------

    int rangeSum(int left, int right) {

        if (left == 0)
            return prefixSum(right);

        return prefixSum(right) - prefixSum(left - 1);
    }

    // ---------------- Set Value ----------------

    void setValue(int index, int value) {

        int delta = value - arr[index];

        arr[index] = value;

        update(index, delta);
    }

    // ---------------- Get Value ----------------

    int at(int index) {

        return arr[index];
    }

    // ---------------- Display Array ----------------

    void displayArray() {

        for (int value : arr)
            cout << value << " ";

        cout << endl;
    }

    // ---------------- Display BIT ----------------

    void displayBIT() {

        cout << "Binary Indexed Tree:\n";

        for (int i = 1; i <= n; i++)
            cout << bit[i] << " ";

        cout << endl;
    }

        // ---------------- Size ----------------

    int size() {

        return n;
    }

    // ---------------- Total Sum ----------------

    int totalSum() {

        if (n == 0)
            return 0;

        return prefixSum(n - 1);
    }

    // ---------------- Minimum ----------------

    int minimum() {

        if (n == 0)
            return -1;

        int minimum = arr[0];

        for (int value : arr)
            if (value < minimum)
                minimum = value;

        return minimum;
    }

    // ---------------- Maximum ----------------

    int maximum() {

        if (n == 0)
            return -1;

        int maximum = arr[0];

        for (int value : arr)
            if (value > maximum)
                maximum = value;

        return maximum;
    }

    // ---------------- Empty ----------------

    bool empty() {

        return n == 0;
    }

};

int main() {

    vector<int> values = {
        2, 4, 5, 7,
        8, 9, 1, 6
    };

    FenwickTree bit(values);

    cout << "===== Original Array =====\n";
    bit.displayArray();

    cout << "\n===== Binary Indexed Tree =====\n";
    bit.displayBIT();

    cout << "\n===== Prefix Sum Queries =====\n";

    cout << "Prefix Sum [0..0] = " << bit.prefixSum(0) << endl;

    cout << "Prefix Sum [0..3] = " << bit.prefixSum(3) << endl;

    cout << "Prefix Sum [0..7] = " << bit.prefixSum(7) << endl;

    cout << "\n===== Range Sum Queries =====\n";

    cout << "Range Sum [2..5] = " << bit.rangeSum(2, 5) << endl;

    cout << "Range Sum [1..6] = " << bit.rangeSum(1, 6) << endl;

    cout << "Range Sum [0..7] = " << bit.rangeSum(0, 7) << endl;

    cout << "\n===== Update =====\n";

    cout << "Set index 3 -> 20\n";

    bit.setValue(3, 20);

    bit.displayArray();

    cout << "\nUpdated Binary Indexed Tree\n";
    bit.displayBIT();

    cout << "\n===== Queries After Update =====\n";

    cout << "Prefix Sum [0..3] = " << bit.prefixSum(3) << endl;

    cout << "Range Sum [2..5] = " << bit.rangeSum(2, 5) << endl;

    cout << "Range Sum [0..7] = " << bit.rangeSum(0, 7) << endl;

    cout << "\n===== Statistics =====\n";

    cout << "Size      : " << bit.size() << endl;

    cout << "Total Sum : " << bit.totalSum() << endl;

    cout << "Minimum   : " << bit.minimum() << endl;

    cout << "Maximum   : " << bit.maximum() << endl;

    cout << "Value at index 5 : " << bit.at(5) << endl;

    cout << "\nEmpty : " << (bit.empty() ? "Yes" : "No") << endl;

    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

class DifferenceArray {
private:
    vector<int> diff;
    int n;

public:
    // ----------------------------------------------------------
    // Build Difference Array
    // Time: O(n)
    // ----------------------------------------------------------
    DifferenceArray(const vector<int>& arr) {
        n = arr.size();
        diff.resize(n);

        diff[0] = arr[0];

        for (int i = 1; i < n; i++)
            diff[i] = arr[i] - arr[i - 1];
    }

    // ----------------------------------------------------------
    // Range Update
    // Add 'value' to every element in [left, right]
    // Time: O(1)
    // ----------------------------------------------------------
    void rangeUpdate(int left, int right, int value) {

        diff[left] += value;

        if (right + 1 < n)
            diff[right + 1] -= value;
    }

    // ----------------------------------------------------------
    // Restore Original Array
    // Time: O(n)
    // ----------------------------------------------------------
    vector<int> getArray() {

        vector<int> result(n);

        result[0] = diff[0];

        for (int i = 1; i < n; i++)
            result[i] = result[i - 1] + diff[i];

        return result;
    }

    // ----------------------------------------------------------
    // Print Difference Array
    // ----------------------------------------------------------
    void printDifferenceArray() {

        cout << "Difference Array: ";

        for (int x : diff)
            cout << x << " ";

        cout << endl;
    }
};

int main() {

    vector<int> arr = {10, 20, 30, 40, 50};

    DifferenceArray da(arr);

    cout << "Initial\n";

    da.printDifferenceArray();

    // Add 5 to index [1...3]
    da.rangeUpdate(1, 3, 5);

    // Add 10 to index [2...4]
    da.rangeUpdate(2, 4, 10);

    // Add -3 to index [0...2]
    da.rangeUpdate(0, 2, -3);

    cout << "\nAfter Updates\n";

    da.printDifferenceArray();

    vector<int> result = da.getArray();

    cout << "\nFinal Array: ";

    for (int x : result)
        cout << x << " ";

    cout << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class SparseTable {
private:
    vector<vector<int>> st;
    vector<int> logTable;
    int n;

public:
    SparseTable(const vector<int>& arr) {
        build(arr);
    }

    // Build Sparse Table
    // Time: O(n log n)
    // Space: O(n log n)
    void build(const vector<int>& arr) {
        n = arr.size();

        // Precompute logarithms
        logTable.resize(n + 1);
        logTable[1] = 0;
        for (int i = 2; i <= n; i++)
            logTable[i] = logTable[i / 2] + 1;

        int maxLog = logTable[n];

        st.assign(maxLog + 1, vector<int>(n));

        // Level 0
        for (int i = 0; i < n; i++)
            st[0][i] = arr[i];

        // Build higher levels
        for (int j = 1; j <= maxLog; j++) {
            int length = 1 << j;

            for (int i = 0; i + length <= n; i++) {
                st[j][i] = min(
                    st[j - 1][i],
                    st[j - 1][i + (length >> 1)]
                );
            }
        }
    }

    // Range Minimum Query
    // Time: O(1)
    int query(int left, int right) {
        int len = right - left + 1;
        int k = logTable[len];

        return min(
            st[k][left],
            st[k][right - (1 << k) + 1]
        );
    }

    void printTable() {
        cout << "Sparse Table:\n";

        for (int j = 0; j < st.size(); j++) {
            cout << "Level " << j << ": ";

            for (int val : st[j])
                cout << val << " ";

            cout << endl;
        }
    }
};

int main() {

    vector<int> arr = {
        1, 3, 2, 7,
        9, 11, 3, 5,
        6, 8
    };

    SparseTable table(arr);

    table.printTable();

    cout << "\nRange Minimum Queries\n";

    cout << "RMQ(0,4): "
         << table.query(0,4) << endl;

    cout << "RMQ(3,8): "
         << table.query(3,8) << endl;

    cout << "RMQ(2,6): "
         << table.query(2,6) << endl;

    cout << "RMQ(5,9): "
         << table.query(5,9) << endl;

    return 0;
}
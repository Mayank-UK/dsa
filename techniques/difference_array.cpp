#include <iostream>
#include <vector>

using namespace std;

// ============================================================
// Difference Array — O(1) range-add updates, O(n) final restore.
// diff[i] = arr[i] - arr[i-1]. Adding v to [l..r] is just diff[l]+=v and
// diff[r+1]-=v (two points, not r-l+1). A running prefix-sum over diff then
// reconstructs the updated array. This is the write-heavy / read-light mirror
// of prefix_sum.cpp: many range updates, one read at the end.
// ============================================================
class DifferenceArray {
private:
    vector<long long> diff;
    int n;

public:
    // ─── Build ───  Time: O(n)
    DifferenceArray(const vector<int>& arr) {
        n = (int)arr.size();
        diff.resize(n);
        if (n == 0) return;

        diff[0] = arr[0];
        for (int i = 1; i < n; i++)
            diff[i] = arr[i] - arr[i - 1];
    }

    // ─── Range update: add value to every index in [left, right] ───  Time: O(1)
    void rangeUpdate(int left, int right, long long value) {
        diff[left] += value;
        if (right + 1 < n)
            diff[right + 1] -= value;
    }

    // ─── Restore the updated array ───  Time: O(n)
    vector<long long> getArray() {
        vector<long long> result(n);
        if (n == 0) return result;

        result[0] = diff[0];
        for (int i = 1; i < n; i++)
            result[i] = result[i - 1] + diff[i];

        return result;
    }

    void printDifferenceArray() {
        cout << "  diff = ";
        for (long long x : diff) cout << x << " ";
        cout << endl;
    }
};

// Pretty-print an array with a label.
static void printArray(const string& label, const vector<long long>& v) {
    cout << "  " << label << " = ";
    for (long long x : v) cout << x << " ";
    cout << endl;
}

// ============================================================
int main() {

    cout << "================== Difference Array ==================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  build        : O(n)  (store consecutive deltas)" << endl;
    cout << "  range update : O(1)  (touch diff[l] and diff[r+1] only)" << endl;
    cout << "  restore      : O(n)  (running sum of diff)" << endl;
    cout << "  space        : O(n)" << endl;
    cout << "  Notes : each range update is O(1) vs O(length) on a raw array." << endl;

    vector<int> arr = {10, 20, 30, 40, 50};
    DifferenceArray da(arr);

    cout << endl;
    cout << "[Build]  arr = {10, 20, 30, 40, 50}" << endl;
    da.printDifferenceArray();

    cout << endl;
    cout << "[Range Updates]" << endl;
    cout << "  add +5  to [1..3]" << endl;
    da.rangeUpdate(1, 3, 5);
    cout << "  add +10 to [2..4]" << endl;
    da.rangeUpdate(2, 4, 10);
    cout << "  add -3  to [0..2]" << endl;
    da.rangeUpdate(0, 2, -3);
    cout << "  after all updates:" << endl;
    da.printDifferenceArray();

    cout << endl;
    cout << "[Restore]  prefix-sum the diff array" << endl;
    vector<long long> result = da.getArray();
    printArray("final", result);

    // Self-verify against applying the same updates to a plain array.
    cout << endl;
    cout << "[Verify]  replay updates on a naive array and compare";
    vector<long long> naive(arr.begin(), arr.end());
    naive[1]+=5; naive[2]+=5; naive[3]+=5;
    naive[2]+=10; naive[3]+=10; naive[4]+=10;
    naive[0]+=-3; naive[1]+=-3; naive[2]+=-3;
    bool ok = (naive == result);
    cout << " : " << (ok ? "Match" : "MISMATCH") << endl;

    cout << endl;
    cout << "[Edge Cases]" << endl;
    DifferenceArray single({42});
    single.rangeUpdate(0, 0, 100);
    cout << "  Single-element {42}, add 100 to [0..0]: final = ";
    for (long long x : single.getArray()) cout << x << " ";
    cout << endl;

    DifferenceArray full({1, 2, 3, 4, 5});
    full.rangeUpdate(0, 4, 7);   // full-array update — diff[r+1] is out of range, skipped
    cout << "  Full-array update [0..4] += 7: final = ";
    for (long long x : full.getArray()) cout << x << " ";
    cout << endl;

    cout << endl;
    cout << "[Note]  Inverse of prefix_sum.cpp. Pair it with a Fenwick tree when you" << endl;
    cout << "       need the restored value AFTER EACH update rather than once at the end." << endl;

    return 0;
}

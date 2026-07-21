#include <iostream>
#include <vector>

using namespace std;

class PrefixSum {
private:
    vector<long long> prefix;

public:
    // Constructor to build the prefix sum array
    PrefixSum(const vector<int>& arr) {
        int n = arr.size();
        prefix.resize(n);
        if (n == 0) return;

        prefix[0] = arr[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + arr[i];
        }
    }

    // Function to get the sum of elements in range [L, R] in O(1) time
    long long query(int L, int R) {
        if (L == 0) {
            return prefix[R];
        }
        return prefix[R] - prefix[L - 1];
    }
};

int main() {
    vector<int> arr = {2, 4, 0, 5, 1, 9};

    PrefixSum ps(arr);

    // Query range sums
    cout << "Sum of elements from index 1 to 3: " << ps.query(1, 3) << "\n"; // 4 + 0 + 5 = 9
    cout << "Sum of elements from index 0 to 5: " << ps.query(0, 5) << "\n"; // 2+4+0+5+1+9 = 21
    cout << "Sum of elements from index 2 to 4: " << ps.query(2, 4) << "\n"; // 0 + 5 + 1 = 6

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

// Bucket sort for floats in [0, 1): scatter into n buckets by value,
// sort each bucket, then concatenate. Linear-ish when input is uniform.
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    vector<vector<float>> buckets(n);

    // Distribute element i into bucket floor(n * arr[i]).
    for (int i = 0; i < n; i++) {
        int bi = (int)(n * arr[i]);
        if (bi >= n) bi = n - 1;  // clamp arr[i] == 1.0 to the last bucket
        buckets[bi].push_back(arr[i]);
    }

    // Sort each bucket individually.
    for (int i = 0; i < n; i++)
        sort(buckets[i].begin(), buckets[i].end());

    // Concatenate buckets back into arr.
    int index = 0;
    for (int i = 0; i < n; i++)
        for (float val : buckets[i])
            arr[index++] = val;
}

// ─── Demo helpers ───
static void printArray(const vector<float>& arr, const string& label) {
    cout << "  " << label << " : ";
    if (arr.empty()) { cout << "(empty)\n"; return; }
    cout << fixed << setprecision(4);
    for (float x : arr) cout << x << " ";
    cout << "\n";
}

static bool isSorted(const vector<float>& arr) {
    for (size_t i = 1; i < arr.size(); i++)
        if (arr[i] < arr[i - 1]) return false;
    return true;
}

static void runCase(const string& name, vector<float> arr) {
    printArray(arr, name + " before");
    bucketSort(arr);
    printArray(arr, name + " after ");
}

int main() {
    cout << "==================== Bucket Sort ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Best    : O(n + k)     uniform input, k buckets\n";
    cout << "  Average : O(n)         when input is uniformly distributed\n";
    cout << "  Worst   : O(n^2)       all elements land in one bucket\n";
    cout << "  Space   : O(n + k)\n";
    cout << "  Stable  : Yes          (stable bucket sort + per-bucket sort)\n";
    cout << "  Note    : this version assumes keys in [0, 1)\n\n";

    cout << "[Demo]\n";
    vector<float> arr = {0.897f, 0.565f, 0.656f, 0.1234f, 0.665f, 0.3434f};
    printArray(arr, "before");
    bucketSort(arr);
    printArray(arr, "after ");
    cout << "  Sorted correctly : " << (isSorted(arr) ? "Yes" : "No") << "\n\n";

    cout << "[Edge Cases]\n";
    runCase("empty       ", {});
    runCase("single      ", {0.42f});
    runCase("duplicates  ", {0.5f, 0.1f, 0.5f, 0.2f, 0.1f});
    runCase("already sort", {0.1f, 0.2f, 0.3f, 0.4f});
    runCase("reverse     ", {0.9f, 0.7f, 0.5f, 0.3f, 0.1f});
    runCase("near zero   ", {0.001f, 0.999f, 0.5f, 0.25f, 0.75f});
    cout << "\n";

    return 0;
}

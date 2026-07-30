#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

using namespace std;

// Reservoir Sampling (Algorithm R) — pick a uniform random sample of size k
// from a stream of unknown length in ONE pass, O(n) time, O(k) space, without
// storing the whole stream. Fill the reservoir with the first k items; then for
// each later item i, replace a random reservoir slot with probability k/(i+1).
// The magic: every item ends up selected with exactly probability k/n, and the
// proof is a clean induction on i.

// Return k uniformly-sampled items from the stream.
static vector<int> reservoirSampling(const vector<int>& stream, int k) {
    if (k <= 0) return {};
    int n = (int)stream.size();
    if (k > n) k = n;

    vector<int> reservoir(k);
    for (int i = 0; i < k; i++)                    // seed with the first k
        reservoir[i] = stream[i];

    for (int i = k; i < n; i++) {
        int j = rand() % (i + 1);                  // random slot in [0..i]
        if (j < k)                                 // with probability k/(i+1)
            reservoir[j] = stream[i];
    }
    return reservoir;
}

int main() {
    srand((unsigned)time(nullptr));

    cout << "==================== Reservoir Sampling ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  time  : O(n)   one pass over the stream\n";
    cout << "  space : O(k)   only the reservoir is kept, never the whole stream\n";
    cout << "  Notes : every item selected with probability exactly k/n.\n\n";

    vector<int> stream = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int k = 3;

    cout << "[Demo]  stream of 10 items, k=" << k << "\n";
    cout << "  stream: ";
    for (int x : stream) cout << x << " ";
    cout << "\n";
    vector<int> sample = reservoirSampling(stream, k);
    cout << "  one sample: ";
    for (int x : sample) cout << x << " ";
    cout << "\n";

    // Validate a single draw: size, membership, distinctness.
    cout << "\n[Sanity]  the sample is a valid k-subset";
    bool sizeOk = ((int)sample.size() == min(k, (int)stream.size()));
    unordered_set<int> streamSet(stream.begin(), stream.end());
    bool memberOk = true, distinctOk = true;
    unordered_set<int> seen;
    for (int x : sample) {
        if (!streamSet.count(x)) memberOk = false;
        if (seen.count(x)) distinctOk = false;
        seen.insert(x);
    }
    cout << " : size " << (sizeOk ? "ok" : "BAD")
         << ", members " << (memberOk ? "ok" : "BAD")
         << ", distinct " << (distinctOk ? "ok" : "BAD") << "\n";

    // Empirical uniformity: sample many times, count how often each item is
    // chosen. With n=10, k=3 the expected hit rate is 3/10 = 30% each.
    cout << "\n[Uniformity]  empirical selection rate over 200,000 draws\n";
    cout << "             (expected = k/n = " << k << "/" << stream.size()
         << " = 0.30 for every item)\n";
    const int TRIALS = 200000;
    vector<long long> hits(stream.size(), 0);
    for (int t = 0; t < TRIALS; t++) {
        vector<int> s = reservoirSampling(stream, k);
        for (int x : s) {
            int idx = (x - 10) / 10;               // map value back to its index
            if (idx >= 0 && idx < (int)stream.size()) hits[idx]++;
        }
    }
    for (int i = 0; i < (int)stream.size(); i++)
        cout << "  item " << stream[i] << " : " << (double)hits[i] / TRIALS << "\n";

    cout << "\n[Edge Cases]\n";
    cout << "  k = 0 -> empty sample: size "
         << reservoirSampling(stream, 0).size() << "\n";
    cout << "  k > stream size -> returns whole stream: size "
         << reservoirSampling({1, 2, 3}, 10).size() << "\n";
    cout << "  k = 1 (uniform single draw)\n";
    vector<int> one = reservoirSampling(stream, 1);
    cout << "    sample: " << one[0] << "\n";

    cout << "\n[Note]\n";
    cout << "  Crucial for streams that don't fit in memory or arrive live (logs, IoT).\n";
    cout << "  Weighted reservoir sampling (A-Res / A-ExpJ) extends this to non-uniform\n";
    cout << "  distributions; distributed reservoir sampling merges per-shard reservoirs.\n";

    return 0;
}

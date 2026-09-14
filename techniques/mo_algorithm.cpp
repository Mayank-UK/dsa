#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// ============================================================
// Mo's Algorithm — answer MANY range queries on a STATIC array faster than
// doing each independently. Sort the queries offline by (L / block, R) so that
// consecutive queries overlap, then maintain [currL, currR] and ADD/REMOVE one
// endpoint at a time to reach the next query. Total pointer movement is
// O((n + q) * sqrt(n)) — a win when add/remove are O(1) and q is large.
// Shown here for range SUM (swap the lambda to count distinct, freq, etc.).
// ============================================================

struct Query { int L, R, id; };

static int BLOCK_SIZE;

// Hilbert-friendly order: same block by L, R alternating direction per block
// to cut the right-pointer's travel.
static bool compareQueries(const Query& x, const Query& y) {
    int blockX = x.L / BLOCK_SIZE;
    int blockY = y.L / BLOCK_SIZE;
    if (blockX != blockY) return blockX < blockY;
    return (blockX % 2 == 1) ? (x.R < y.R) : (x.R > y.R);
}

// Answer every query; result[i] is the answer for the query with id == i.
static vector<long long> mosAlgorithm(const vector<int>& arr, const vector<Query>& queries) {
    int q = (int)queries.size();
    vector<long long> answers(q);
    if (q == 0) return answers;

    BLOCK_SIZE = max(1, (int)sqrt((double)arr.size()));

    vector<Query> sortedQueries = queries;
    sort(sortedQueries.begin(), sortedQueries.end(), compareQueries);

    int currL = 0, currR = -1;
    long long currentSum = 0;

    auto add    = [&](int idx) { currentSum += arr[idx]; };
    auto remove = [&](int idx) { currentSum -= arr[idx]; };

    for (int i = 0; i < q; i++) {
        int L = sortedQueries[i].L;
        int R = sortedQueries[i].R;
        int id = sortedQueries[i].id;

        while (currL > L) { currL--; add(currL); }
        while (currL < L) { remove(currL); currL++; }
        while (currR < R) { currR++; add(currR); }
        while (currR > R) { remove(currR); currR--; }

        answers[id] = currentSum;
    }
    return answers;
}

// Naive per-query sum — only to verify the optimized answers.
static long long naiveSum(const vector<int>& arr, int L, int R) {
    long long s = 0;
    for (int i = L; i <= R; i++) s += arr[i];
    return s;
}

// ============================================================
int main() {

    cout << "==================== Mo's Algorithm ====================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  time  : O((n + q) * sqrt(n))   (total L/R pointer movement)" << endl;
    cout << "  space : O(q)                    (answer buffer)" << endl;
    cout << "  Notes : offline + reorder queries; needs O(1) add/remove." << endl;

    vector<int> arr = {1, 1, 2, 1, 3, 4, 5, 2, 8};
    vector<Query> queries = {
        {0, 4, 0},
        {1, 3, 1},
        {2, 4, 2},
        {0, 8, 3},
        {4, 4, 4},
    };

    cout << endl;
    cout << "[Demo]  arr = {1,1,2,1,3,4,5,2,8}, 5 range-sum queries" << endl;
    vector<long long> results = mosAlgorithm(arr, queries);

    cout << "  id | [L,R]      | Mo's sum | naive | match" << endl;
    bool ok = true;
    for (int i = 0; i < (int)queries.size(); i++) {
        long long naive = naiveSum(arr, queries[i].L, queries[i].R);
        bool agree = (naive == results[i]);
        if (!agree) ok = false;
        cout << "  " << queries[i].id << " | [" << queries[i].L << "," << queries[i].R
             << "]    | " << results[i]
             << "      | " << naive
             << "    | " << (agree ? "Yes" : "NO") << endl;
    }

    cout << endl;
    cout << "[Verify]  every query matches a naive O(length) scan : "
         << (ok ? "All agree" : "MISMATCH") << endl;

    cout << endl;
    cout << "[Edge Cases]" << endl;
    cout << "  Single-element query [4,4] above = " << results[4]
         << "  (= arr[4] = 3)" << endl;
    cout << "  Full-array query [0,8] above = " << results[3] << endl;

    vector<Query> none;
    vector<long long> empty = mosAlgorithm(arr, none);
    cout << "  Zero queries: returned " << empty.size() << " answers (guarded)." << endl;

    cout << endl;
    cout << "[Note]  Mo's shines when add/remove are O(1) but a prefix-sum/segment" << endl;
    cout << "       tree is NOT applicable — e.g. count DISTINCT values in a range," << endl;
    cout << "       or k-th smallest in a range. Swap the add/remove lambdas; the" << endl;
    cout << "       reordering machinery stays identical." << endl;

    return 0;
}

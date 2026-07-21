#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Structure to represent a query
struct Query {
    int L, R, id;
};

int BLOCK_SIZE;

// Comparator to sort queries for Mo's Algorithm
bool compareQueries(const Query& x, const Query& y) {
    int blockX = x.L / BLOCK_SIZE;
    int blockY = y.L / BLOCK_SIZE;

    if (blockX != blockY) {
        return blockX < blockY;
    }
    // Even blocks sort R ascending, odd blocks sort R descending (optimization)
    return (blockX % 2 == 1) ? (x.R < y.R) : (x.R > y.R);
}

// Function to process range sum queries using Mo's Algorithm
vector<long long> mosAlgorithm(const vector<int>& arr, const vector<Query>& queries) {
    int n = arr.size();
    int q = queries.size();
    vector<long long> answers(q);

    BLOCK_SIZE = sqrt(n);

    // Make a copy of queries to sort them offline
    vector<Query> sortedQueries = queries;
    sort(sortedQueries.begin(), sortedQueries.end(), compareQueries);

    int currL = 0, currR = -1;
    long long currentSum = 0;

    auto add = [&](int idx) {
        currentSum += arr[idx];
    };

    auto remove = [&](int idx) {
        currentSum -= arr[idx];
    };

    for (int i = 0; i < q; i++) {
        int L = sortedQueries[i].L;
        int R = sortedQueries[i].R;
        int id = sortedQueries[i].id;

        // Adjust currL
        while (currL > L) {
            currL--;
            add(currL);
        }
        while (currL < L) {
            remove(currL);
            currL++;
        }

        // Adjust currR
        while (currR < R) {
            currR++;
            add(currR);
        }
        while (currR > R) {
            remove(currR);
            currR--;
        }

        answers[id] = currentSum;
    }

    return answers;
}

int main() {
    vector<int> arr = {1, 1, 2, 1, 3, 4, 5, 2, 8};
    vector<Query> queries = {
        {0, 4, 0},
        {1, 3, 1},
        {2, 4, 2}
    };

    vector<long long> results = mosAlgorithm(arr, queries);

    cout << "Mo's Algorithm Query Results:\n";
    for (int i = 0; i < results.size(); i++) {
        cout << "Query " << i << " sum: " << results[i] << "\n";
    }

    return 0;
}
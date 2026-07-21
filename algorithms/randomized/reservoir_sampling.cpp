#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to select k items randomly from a stream of unknown size
vector<int> reservoirSampling(vector<int>& stream, int k) {
    vector<int> reservoir(k);

    // Step 1: Fill the reservoir with the first k items
    for (int i = 0; i < k; i++) {
        reservoir[i] = stream[i];
    }

    // Step 2: Process remaining elements from the stream
    for (int i = k; i < stream.size(); i++) {
        // Pick a random index from 0 to i (inclusive)
        int j = rand() % (i + 1);

        // If the randomly chosen index is within the reservoir capacity, replace it
        if (j < k) {
            reservoir[j] = stream[i];
        }
    }

    return reservoir;
}

int main() {
    srand(time(nullptr));

    // Simulated data stream of a large size
    vector<int> stream = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int k = 3; // Number of items to sample

    vector<int> sample = reservoirSampling(stream, k);

    cout << "Random sample of size " << k << " from stream:\n";
    for (int num : sample) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}
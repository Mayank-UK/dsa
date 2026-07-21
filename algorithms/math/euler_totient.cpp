#include <iostream>
#include <vector>

using namespace std;

// Function to compute totient values for all numbers up to n in O(n log log n)
vector<int> computeTotients(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++) {
        phi[i] = i;
    }

    for (int p = 2; p <= n; p++) {
        // If p is a prime
        if (phi[p] == p) {
            for (int i = p; i <= n; i += p) {
                phi[i] -= phi[i] / p;
            }
        }
    }

    return phi;
}

int main() {
    int maxLimit = 10;
    vector<int> totients = computeTotients(maxLimit);

    cout << "Euler's Totient values from 1 to " << maxLimit << ":\n";
    for (int i = 1; i <= maxLimit; i++) {
        cout << "Phi(" << i << ") = " << totients[i] << "\n";
    }

    return 0;
}
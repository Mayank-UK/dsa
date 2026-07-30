#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Euler's totient φ(n) = count of k in [1..n] with gcd(k,n)=1. This computes
// φ for EVERY number up to n in one sieve pass (a multiplicative refinement of
// the Sieve of Eratosthenes): start with φ[i]=i, then for each prime p subtract
// φ[i]/p from every multiple of p. Each prime factor of i divides φ down by the
// factor (1 - 1/p), giving the classic φ(n) = n · Π (1 - 1/p).

vector<int> computeTotients(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; ++i) phi[i] = i;

    for (int p = 2; p <= n; ++p) {
        if (phi[p] == p) {                       // p is prime (untouched so far)
            for (int i = p; i <= n; i += p) {
                phi[i] -= phi[i] / p;            // multiply in (1 - 1/p)
            }
        }
    }
    return phi;
}

int main() {
    cout << "====================== Euler's Totient (φ) ======================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time   : O(n log log n)   sieve-style refinement\n";
    cout << "  Space  : O(n)\n";
    cout << "  Notes  : φ(prime p) = p-1; φ(p^k) = p^k - p^(k-1); φ is multiplicative.\n\n";

    int maxLimit = 20;
    vector<int> phi = computeTotients(maxLimit);

    cout << "[Demo] φ for 1.." << maxLimit << ":\n";
    cout << "  n  : "; for (int i = 1; i <= maxLimit; ++i) cout << i << "\t";
    cout << "\n  φ  : "; for (int i = 1; i <= maxLimit; ++i) cout << phi[i] << "\t";
    cout << "\n\n";

    cout << "[Spot Checks]\n";
    cout << "  φ(1)  = " << phi[1]  << "   (expect 1)\n";
    cout << "  φ(7)  = " << phi[7]  << "   (prime  → expect 6)\n";
    cout << "  φ(9)  = " << phi[9]  << "   (3^2    → expect 6)\n";
    cout << "  φ(12) = " << phi[12] << "   (expect 4)\n";

    cout << "\n[Edge Cases]\n";
    vector<int> small = computeTotients(1);
    cout << "  n=1 → φ(1) = " << small[1] << "\n";

    return 0;
}

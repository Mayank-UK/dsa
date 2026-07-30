#include <iostream>
#include <vector>

using namespace std;

// Sieve of Eratosthenes (classic boolean form). Assume every number ≥ 2 is prime,
// then for each prime p still marked, strike out its multiples starting at p*p
// (smaller multiples were already struck by a smaller prime). What remains marked
// is prime. This lists ALL primes up to n.
// (For the smallest-prime-factor variant that also factorizes, see
//  seive_of_erastothenes.cpp.)

vector<int> sieveOfEratosthenes(int n) {
    if (n < 2) return {};
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int p = 2; (long long)p * p <= n; ++p) {   // only up to √n
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {     // mark from p*p onward
                isPrime[i] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; ++i)
        if (isPrime[i]) primes.push_back(i);
    return primes;
}

// π(n): count of primes ≤ n, for an at-a-glance stat.
static int countPrimes(int n) { return (int)sieveOfEratosthenes(n).size(); }

int main() {
    cout << "==================== Sieve of Eratosthenes (classic) ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time   : O(n log log n)   each composite struck once per prime factor\n";
    cout << "  Space  : O(n)             boolean table\n";
    cout << "  Notes  : mark multiples from p*p; iterate p only up to √n.\n\n";

    cout << "[Demo] primes up to 50:\n  ";
    vector<int> primes = sieveOfEratosthenes(50);
    for (int p : primes) cout << p << " ";
    cout << "\n  count = " << primes.size() << "\n\n";

    cout << "[Stats] π(n) for growing n:\n";
    int limits[] = {10, 100, 1000, 10000};
    for (int n : limits)
        cout << "  π(" << n << ") = " << countPrimes(n) << "\n";

    cout << "\n[Edge Cases]\n";
    cout << "  n = 0  -> count " << countPrimes(0) << "\n";
    cout << "  n = 1  -> count " << countPrimes(1) << "\n";
    cout << "  n = 2  -> count " << countPrimes(2) << " (just {2})\n";
    cout << "  n = 3  -> count " << countPrimes(3) << " ({2,3})\n";

    return 0;
}

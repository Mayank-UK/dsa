#include <iostream>
#include <vector>

using namespace std;

// Sieve of Eratosthenes — smallest-prime-factor (SPF) variant. Same Eratosthenes
// sweep, but instead of a boolean, each cell stores the SMALLEST prime dividing
// it. That one table answers two questions at once: "is n prime?" (spf[n]==n) and
// "factorize n" (repeatedly peel off spf[n]). So this file complements the
// classic boolean sieve in seive.cpp — same algorithm, different payload.
// (For the plain prime-listing sieve, see seive.cpp.)

// Returns spf[] where spf[i] = smallest prime factor of i (spf[0]=spf[1]=0).
vector<int> smallestPrimeFactor(int n) {
    vector<int> spf(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (spf[i] == 0) {                     // i is prime
            spf[i] = i;
            for (long long j = (long long)i * i; j <= n; j += i) {
                if (spf[(int)j] == 0) spf[(int)j] = i;   // first prime to reach j wins
            }
        }
    }
    return spf;
}

// Factorize m (m ≤ n) by peeling off its smallest prime factor each step: O(log m).
static vector<int> factorize(const vector<int>& spf, int m) {
    vector<int> factors;
    if (m < 2 || m >= (int)spf.size()) return factors;   // out of table range
    while (m > 1) {
        factors.push_back(spf[m]);
        m /= spf[m];
    }
    return factors;
}

int main() {
    cout << "=============== Sieve of Eratosthenes (SPF variant) ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Build      : O(n log log n)   same Eratosthenes sweep\n";
    cout << "  Factorize  : O(log m)         per query, by peeling off spf[]\n";
    cout << "  Space      : O(n)\n";
    cout << "  Notes  : spf[i]==i  ⇔ i is prime; one table → primality AND factorization.\n\n";

    int n = 120;
    vector<int> spf = smallestPrimeFactor(n);

    int displayUpTo = 50;
    cout << "[Demo] primes up to " << displayUpTo << " (cells where spf[i]==i):\n  ";
    for (int i = 2; i <= displayUpTo; ++i) if (spf[i] == i) cout << i << " ";
    cout << "\n\n";

    cout << "[Factorizations]\n";
    int samples[] = {12, 17, 60, 97, 100};
    for (int m : samples) {
        cout << "  " << m << " = ";
        vector<int> f = factorize(spf, m);
        if (f.empty()) { cout << "(none)\n"; continue; }
        for (size_t i = 0; i < f.size(); ++i) cout << f[i] << (i + 1 < f.size() ? " * " : "\n");
    }

    cout << "\n[Edge Cases]\n";
    cout << "  spf[1] = " << spf[1] << "  (1 has no prime factor)\n";
    cout << "  spf[2] = " << spf[2] << "  (prime)\n";
    cout << "  factor 2 = "; {
        vector<int> f = factorize(spf, 2);
        for (size_t i = 0; i < f.size(); ++i) cout << f[i] << (i + 1 < f.size() ? " * " : "\n");
    }

    return 0;
}

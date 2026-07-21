#include <iostream>
#include <vector>

using namespace std;

// Function to generate all primes up to n using Sieve of Eratosthenes
vector<int> sieveOfEratosthenes(int n) {
    // Initialize a boolean array "isPrime" and assume all numbers are prime
    vector<bool> isPrime(n + 1, true);
    
    isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime

    for (int p = 2; p * p <= n; p++) {
        // If isPrime[p] is true, then it is a prime number
        if (isPrime[p]) {
            // Mark all multiples of p (starting from p*p) as false
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }

    // Collect all prime numbers into a result vector
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

int main() {
    int n = 50; // Find all primes up to 50
    vector<int> primes = sieveOfEratosthenes(n);

    cout << "Prime numbers up to " << n << ":\n";
    for (int prime : primes) {
        cout << prime << " ";
    }
    cout << "\nTotal primes found: " << primes.size() << "\n";

    return 0;
}
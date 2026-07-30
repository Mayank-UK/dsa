#include <iostream>
#include <bitset>
#include <vector>
#include <string>

using namespace std;

// Is n a power of two? A power of two has exactly ONE set bit (1, 10, 100, ...),
// so clearing that lowest bit with n & (n-1) yields 0. Three ways to test it,
// all O(1) — the lesson is recognizing the "single set bit" shape.

class PowerOfTwo {
public:
    // n & (n-1) clears the lowest set bit; a power of two has only one, → 0.
    static bool isBitwise(long long n) { return n > 0 && (n & (n - 1)) == 0; }

    // A power of two has popcount exactly 1.
    static bool isPopcount(long long n) { return n > 0 && __builtin_popcountll(n) == 1; }

    // Divide by 2 until odd; a power of two reduces to 1.
    static bool isIterative(long long n) {
        if (n <= 0) return false;
        while (n % 2 == 0) n /= 2;
        return n == 1;
    }
};

static void runCase(long long n) {
    string bin = (n > 0 && n <= 65535) ? bitset<16>((unsigned long long)n).to_string() : "n/a";
    if (bin != "n/a") { bin.erase(0, bin.find_first_not_of('0')); if (bin.empty()) bin = "0"; }
    cout << "  n=" << n << "\t(bin " << bin << ")  bitwise=" << PowerOfTwo::isBitwise(n)
         << "  popcount=" << PowerOfTwo::isPopcount(n)
         << "  iterative=" << PowerOfTwo::isIterative(n) << "\n";
}

int main() {
    cout << "======================== Power of Two Check ========================\n\n";

    cout << "[Complexity]\n";
    cout << "  All three approaches : O(1)\n";
    cout << "  Notes : a power of two has exactly one set bit; n=0 and negatives are NOT.\n\n";

    cout << "[Demo]\n";
    runCase(1);       // 2^0
    runCase(2);
    runCase(8);
    runCase(1024);
    runCase(14);      // not a power
    cout << "\n";

    cout << "[Edge Cases]\n";
    runCase(0);       // not a power of two
    runCase(-8);      // negative — not a power of two
    runCase((1LL << 40));   // 2^40, a large power
    runCase((1LL << 40) + 1); // one past it — not

    return 0;
}

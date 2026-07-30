#include <iostream>
#include <bitset>
#include <string>

using namespace std;

// Population count (popcount): the number of 1-bits in an integer's binary
// representation. Three approaches of decreasing constant factor — the lesson is
// that Brian Kernighan's n & (n-1) trick clears the lowest SET bit, so the loop
// runs exactly popcount(n) times instead of all bit-width times.

class SetBitsCounter {
public:
    // Walk every bit position. O(bits) — visits 0-bits too.
    static int countSimple(unsigned n) {
        int count = 0;
        while (n > 0) { count += (n & 1); n >>= 1; }
        return count;
    }

    // Brian Kernighan: drop the lowest set bit each iteration. O(set bits).
    static int countKernighan(unsigned n) {
        int count = 0;
        while (n > 0) { n &= (n - 1); ++count; }
        return count;
    }

    // Hardware/Compiler intrinsic — usually a single POPCNT instruction.
    static int countBuiltin(unsigned n) { return __builtin_popcount(n); }
};

static void runNum(unsigned n) {
    string b = bitset<16>(n).to_string();
    b.erase(0, b.find_first_not_of('0'));          // strip leading zeros
    if (b.empty()) b = "0";
    cout << "  " << n << "\t(bin " << b << ")  simple=" << SetBitsCounter::countSimple(n)
         << "  kernighan=" << SetBitsCounter::countKernighan(n)
         << "  builtin=" << SetBitsCounter::countBuiltin(n) << "\n";
}

int main() {
    cout << "========================= Count Set Bits =========================\n\n";

    cout << "[Complexity]\n";
    cout << "  Simple      : O(bits)            visits every bit position\n";
    cout << "  Kernighan   : O(set bits)        n & (n-1) clears the lowest set bit\n";
    cout << "  __builtin   : O(1) / 1 instruction  (hardware POPCNT)\n\n";

    cout << "[Demo]\n";
    runNum(9);       // 1001 → 2
    runNum(15);      // 1111 → 4
    runNum(128);     // 10000000 → 1
    runNum(9999);

    cout << "\n[Edge Cases]\n";
    cout << "  0           -> " << SetBitsCounter::countBuiltin(0) << " (no bits set)\n";
    cout << "  1           -> " << SetBitsCounter::countBuiltin(1) << " (only LSB)\n";
    cout << "  65535       -> " << SetBitsCounter::countBuiltin(65535) << " (16 ones)\n";
    cout << "  UINT_MAX    -> " << SetBitsCounter::countBuiltin(~0u) << " (all 32 bits)\n";

    return 0;
}

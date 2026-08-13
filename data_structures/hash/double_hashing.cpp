#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Hash Map — Double Hashing (open addressing)
//
// Collision strategy: use a SECOND hash function to decide the step size:
//   index = (hash1(key) + i * hash2(key)) % capacity,  i = 0,1,2,...
//   • Eliminates BOTH primary and secondary clustering: every key gets its own
//     probe sequence, so even keys that share hash1 diverge immediately.
//   • hash2 must never return 0 (or probing stalls) and ideally has no common
//     factor with capacity — hence the classic  prime - (key % prime)  form.
//   • Tombstones keep probe chains intact after deletion.
// ─────────────────────────────────────────────────────────────────────────────

class HashMap {
private:
    enum SlotState { EMPTY, OCCUPIED, DELETED };

    struct Entry {
        int key;
        int value;
        SlotState state;
        Entry() : key(0), value(0), state(EMPTY) {}
    };

    vector<Entry> table;
    int capacity;
    int count;

    // Primary hash — the home bucket.
    int hash1(int key) const { return key % capacity; }

    // Secondary hash — the stride. 7 - (key % 7) is in [1..7], never 0.
    // (7 is chosen to be coprime with the default capacity 11.)
    int hash2(int key) const { return 7 - (key % 7); }

    int probe(int base, int step, int i) const {
        return (base + i * step) % capacity;
    }

public:
    HashMap(int size = 11) {
        capacity = size;
        count = 0;
        table.resize(capacity);
    }

    bool put(int key, int value, vector<int>* probePath = nullptr) {

        int base = hash1(key);
        int step = hash2(key);
        int firstTombstone = -1;

        for (int i = 0; i < capacity; i++) {
            int idx = probe(base, step, i);
            if (probePath) probePath->push_back(idx);

            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                table[idx].value = value;
                return false;
            }
            if (table[idx].state == EMPTY) {
                int target = (firstTombstone != -1) ? firstTombstone : idx;
                table[target].key = key;
                table[target].value = value;
                table[target].state = OCCUPIED;
                count++;
                return true;
            }
            if (table[idx].state == DELETED && firstTombstone == -1)
                firstTombstone = idx;
        }

        cout << "  (table full or probe exhausted — insert failed for key " << key << ")\n";
        return false;
    }

    bool get(int key, int& value, vector<int>* probePath = nullptr) const {

        int base = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < capacity; i++) {
            int idx = probe(base, step, i);
            if (probePath) probePath->push_back(idx);

            if (table[idx].state == EMPTY)
                return false;
            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                value = table[idx].value;
                return true;
            }
        }
        return false;
    }

    bool contains(int key) const {
        int dummy;
        return get(key, dummy);
    }

    bool remove(int key) {

        int base = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < capacity; i++) {
            int idx = probe(base, step, i);
            if (table[idx].state == EMPTY)
                return false;
            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                table[idx].state = DELETED;
                count--;
                return true;
            }
        }
        return false;
    }

    // Expose the two hashes so the demo can explain the stride.
    int showHash1(int key) const { return hash1(key); }
    int showHash2(int key) const { return hash2(key); }

    int size() const { return count; }
    int getCapacity() const { return capacity; }
    double loadFactor() const { return static_cast<double>(count) / capacity; }

    void clear() {
        for (int i = 0; i < capacity; i++) table[i].state = EMPTY;
        count = 0;
    }

    void display() const {
        for (int i = 0; i < capacity; i++) {
            cout << "  [" << setw(2) << i << "] -> ";
            if (table[i].state == OCCUPIED)
                cout << "(" << table[i].key << ", " << table[i].value << ")";
            else if (table[i].state == DELETED)
                cout << "<tombstone>";
            else
                cout << "EMPTY";
            cout << "\n";
        }
    }

    ~HashMap() = default;
};

ostream& printProbe(const vector<int>& path) {
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i + 1 < path.size()) cout << " -> ";
    }
    return cout;
}

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "============= Hash Map (Double Hashing) ==============\n";

    HashMap map(11);

    // ── [Build] — same hash1, but DIFFERENT strides → no clustering ──────────
    cout << "\n[Build] Inserting keys that share hash1(key)=0: 22, 33, 44, 55\n";
    vector<int> probe;

    cout << "  22: h1=" << map.showHash1(22) << ", stride h2=" << map.showHash2(22) << "\n";
    map.put(22, 100, &probe);
    cout << "  put(22): probe "; printProbe(probe); cout << "\n";

    cout << "  33: h1=" << map.showHash1(33) << ", stride h2=" << map.showHash2(33) << "\n";
    probe.clear(); map.put(33, 200, &probe);
    cout << "  put(33): probe "; printProbe(probe)
         << "  (same home, different stride than 22)\n";

    cout << "  44: h1=" << map.showHash1(44) << ", stride h2=" << map.showHash2(44) << "\n";
    probe.clear(); map.put(44, 300, &probe);
    cout << "  put(44): probe "; printProbe(probe) << "\n";

    cout << "  55: h1=" << map.showHash1(55) << ", stride h2=" << map.showHash2(55) << "\n";
    probe.clear(); map.put(55, 400, &probe);
    cout << "  put(55): probe "; printProbe(probe) << "\n";
    cout << "  -> All four share home bucket 0 yet spread to 4 distinct slots.\n";

    cout << "\nTable state:\n";
    map.display();

    cout << "\n[Stats]\n";
    cout << "  Size       : " << map.size() << "\n";
    cout << "  Capacity   : " << map.getCapacity() << "\n";
    cout << "  Load factor: " << map.loadFactor() << "\n";

    // ── [Lookup] ─────────────────────────────────────────────────────────────
    cout << "\n[Lookup]\n";
    int value;
    probe.clear();
    bool hit = map.get(44, value, &probe);
    cout << "  get(44): probe "; printProbe(probe)
         << " -> " << (hit ? to_string(value) : "miss") << "\n";

    probe.clear();
    cout << "  get(99): probe "; printProbe(probe)
         << " -> " << (map.get(99, value, &probe) ? to_string(value) : "miss") << "\n";

    // ── [Mutate] ─────────────────────────────────────────────────────────────
    cout << "\n[Mutate] Removing 33 (stride-based probe chain stays intact)\n";
    cout << "  remove(33) -> " << boolalpha << map.remove(33) << "\n";
    cout << "  remove(33) again -> " << map.remove(33) << "  (already gone)\n";

    // ── [Edge] ───────────────────────────────────────────────────────────────
    cout << "\n[Edge] Updating key 22 — no growth in size\n";
    cout << "  Size before: " << map.size() << "\n";
    map.put(22, 999);
    cout << "  Size after : " << map.size() << "\n";
    map.get(22, value);
    cout << "  get(22) now -> " << value << "\n";

    cout << "\n=====================================================\n";
    return 0;
}

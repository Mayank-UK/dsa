#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Hash Map — Quadratic Probing (open addressing)
//
// Collision strategy: step size grows quadratically:
//   index = (hash(key) + i*i) % capacity,  i = 0,1,2,...
//   • Avoids primary clustering (consecutive runs don't merge into one blob).
//   • Still suffers secondary clustering: keys with the same base hash follow
//     the IDENTICAL probe path.
//   • With a prime capacity and load factor < 0.5, every probe is guaranteed
//     to find a free slot (not guaranteed at higher load).
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

    int hash(int key) const { return key % capacity; }

    // Quadratic step: 0, 1, 4, 9, 16, ...
    int probe(int base, int i) const {
        return (base + i * i) % capacity;
    }

public:
    HashMap(int size = 11) {        // prime capacity
        capacity = size;
        count = 0;
        table.resize(capacity);
    }

    bool put(int key, int value, vector<int>* probePath = nullptr) {

        int base = hash(key);
        int firstTombstone = -1;

        for (int i = 0; i < capacity; i++) {
            int idx = probe(base, i);
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

        int base = hash(key);

        for (int i = 0; i < capacity; i++) {
            int idx = probe(base, i);
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

        int base = hash(key);

        for (int i = 0; i < capacity; i++) {
            int idx = probe(base, i);
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

    cout << "============ Hash Map (Quadratic Probing) ============\n";

    HashMap map(11);

    // ── [Build] — same base hash, but diverging probe paths ──────────────────
    cout << "\n[Build] Inserting keys that hash to slot 2: 13, 24, 35, 46\n";
    vector<int> probe;
    map.put(13, 100, &probe);
    cout << "  put(13): probe "; printProbe(probe); cout << "\n";

    probe.clear(); map.put(24, 200, &probe);
    cout << "  put(24): probe "; printProbe(probe) << "  (steps: 2 -> 3)\n";

    probe.clear(); map.put(35, 300, &probe);
    cout << "  put(35): probe "; printProbe(probe) << "  (steps: 2 -> 3 -> 6)\n";

    probe.clear(); map.put(46, 400, &probe);
    cout << "  put(46): probe "; printProbe(probe) << "  (steps: 2 -> 3 -> 6 -> 11%11=0... wraps)\n";
    // note: 2 + 9 = 11 % 11 = 0

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
    bool hit = map.get(35, value, &probe);
    cout << "  get(35): probe "; printProbe(probe)
         << " -> " << (hit ? to_string(value) : "miss") << "\n";

    probe.clear();
    cout << "  get(99): probe "; printProbe(probe)
         << " -> " << (map.get(99, value, &probe) ? to_string(value) : "miss") << "\n";

    // ── [Mutate] ─────────────────────────────────────────────────────────────
    cout << "\n[Mutate] Removing 24 (tombstone keeps the chain intact)\n";
    cout << "  remove(24) -> " << boolalpha << map.remove(24) << "\n";
    cout << "  remove(24) again -> " << map.remove(24) << "  (already gone)\n";

    // ── [Edge] duplicate update ──────────────────────────────────────────────
    cout << "\n[Edge] Updating key 13 — size stays the same\n";
    cout << "  Size before: " << map.size() << "\n";
    map.put(13, 999);
    cout << "  Size after : " << map.size() << "\n";
    map.get(13, value);
    cout << "  get(13) now -> " << value << "\n";

    cout << "\n=====================================================\n";
    return 0;
}

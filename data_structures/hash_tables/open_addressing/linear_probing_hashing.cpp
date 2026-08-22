#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Hash Map — Linear Probing (open addressing)
//
// Collision strategy: on collision, walk forward one slot at a time until an
// open slot is found:  index = (hash(key) + i) % capacity,  i = 0,1,2,...
//   • Primary clustering: contiguous runs of occupied slots grow and merge,
//     making average probe length grow quadratically with the load factor.
//   • Tombstones (DELETED) keep the probe chain intact after a removal.
//   • Performance collapses as α → 1; keep α < ~0.7.
// ─────────────────────────────────────────────────────────────────────────────

class HashMap
{
private:
    enum SlotState
    {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    struct Entry
    {
        int key;
        int value;
        SlotState state;

        Entry() : key(0), value(0), state(EMPTY) {}
    };

    vector<Entry> table;
    int capacity;
    int count; // occupied slots (excludes tombstones)

    int hash(int key) const
    {
        return key % capacity;
    }

    // The linear-probe step: i = 0,1,2,... → consecutive slots.
    int probe(int base, int i) const
    {
        return (base + i) % capacity;
    }

public:
    HashMap(int size = 11)
    { // prime size reduces clustering patterns
        capacity = size;
        count = 0;
        table.resize(capacity);
    }

    // Insert or update. Tracks the probe path so the caller can print it.
    bool put(int key, int value, vector<int> *probePath = nullptr)
    {

        int base = hash(key);
        int firstTombstone = -1;

        for (int i = 0; i < capacity; i++)
        {
            int idx = probe(base, i);
            if (probePath)
                probePath->push_back(idx);

            if (table[idx].state == OCCUPIED && table[idx].key == key)
            {
                table[idx].value = value; // update existing
                return false;
            }
            if (table[idx].state == EMPTY)
            {
                // Open slot (or reuse earliest tombstone if we saw one).
                int target = (firstTombstone != -1) ? firstTombstone : idx;
                table[target].key = key;
                table[target].value = value;
                table[target].state = OCCUPIED;
                count++;
                return true;
            }
            if (table[idx].state == DELETED && firstTombstone == -1)
            {
                firstTombstone = idx; // remember the first occurrence of deleted for later reuse
            }
        }

        cout << "  (table full — insert failed for key " << key << ")\n";
        return false;
    }

    bool get(int key, int &value, vector<int> *probePath = nullptr) const
    {

        int base = hash(key);

        for (int i = 0; i < capacity; i++)
        {
            int idx = probe(base, i);
            if (probePath)
                probePath->push_back(idx);

            if (table[idx].state == EMPTY)
                return false; // chain broken → miss
            if (table[idx].state == OCCUPIED && table[idx].key == key)
            {
                value = table[idx].value;
                return true;
            }
        }
        return false;
    }

    bool contains(int key) const
    {
        int dummy;
        return get(key, dummy);
    }

    // Soft delete — leaves a tombstone so later probes aren't broken.
    bool remove(int key)
    {

        int base = hash(key);

        for (int i = 0; i < capacity; i++)
        {
            int idx = probe(base, i);

            if (table[idx].state == EMPTY)
                return false;
            if (table[idx].state == OCCUPIED && table[idx].key == key)
            {
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

    void clear()
    {
        for (int i = 0; i < capacity; i++)
            table[i].state = EMPTY;
        count = 0;
    }

    void display() const
    {
        for (int i = 0; i < capacity; i++)
        {
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

    ~HashMap() = default; // vector manages memory
};

// Helper: render a recorded probe path like  3 -> 4 -> 5
ostream &printProbe(const vector<int> &path)
{
    for (size_t i = 0; i < path.size(); i++)
    {
        cout << path[i];
        if (i + 1 < path.size())
            cout << " -> ";
    }
    return cout;
}

// ─────────────────────────────── Demo ────────────────────────────────────────

int main()
{

    cout << "============= Hash Map (Linear Probing) =============\n";

    HashMap map(11);

    // ── [Build] with deliberate collisions ───────────────────────────────────
    // 13%11=2, 24%11=2  → 24 must probe to slot 3.
    cout << "\n[Build] Inserting 13, 24 (both hash to slot 2)\n";
    vector<int> probe;
    map.put(13, 100, &probe);
    cout << "  put(13): probe ";
    printProbe(probe);
    cout << "\n";
    probe.clear();
    map.put(24, 200, &probe);
    cout << "  put(24): probe ";
    printProbe(probe);
    cout << "  (collision at 2 → steps to 3)\n";

    cout << "\n  Inserting 35 (hash 2), 46 (hash 2) — cluster grows\n";
    probe.clear();
    map.put(35, 300, &probe);
    cout << "  put(35): probe ";
    printProbe(probe);
    cout << "\n";
    probe.clear();
    map.put(46, 400, &probe);
    cout << "  put(46): probe ";
    printProbe(probe);
    cout << "  (primary cluster: 2,3,4,5)\n";

    cout << "\nTable state:\n";
    map.display();

    cout << "\n[Stats]\n";
    cout << "  Size       : " << map.size() << "\n";
    cout << "  Capacity   : " << map.getCapacity() << "\n";
    cout << "  Load factor: " << map.loadFactor() << "\n";

    // ── [Lookup] with probe path ─────────────────────────────────────────────
    cout << "\n[Lookup]\n";
    int value;
    probe.clear();
    bool hit = map.get(46, value, &probe);
    cout << "  get(46): probe ";
    printProbe(probe);
    cout << " -> " << (hit ? to_string(value) : "miss") << "\n";

    probe.clear();
    cout << "  get(99): probe ";
    printProbe(probe);
    cout << " -> " << (map.get(99, value, &probe) ? to_string(value) : "miss") << "\n";

    // ── [Mutate] tombstone behavior ──────────────────────────────────────────
    cout << "\n[Mutate] Removing 24 (slot 3 becomes a tombstone, NOT EMPTY)\n";
    cout << "  remove(24) -> " << boolalpha << map.remove(24) << "\n";
    map.display();

    cout << "\n  Probing past a tombstone: get(46) must still traverse slot 3\n";
    probe.clear();
    map.get(46, value, &probe);
    cout << "  get(46): probe ";
    printProbe(probe) << " -> " << value << "\n";

    // ── [Edge] full table ────────────────────────────────────────────────────
    cout << "\n[Edge] Filling the table to demonstrate α → 1 degradation\n";
    HashMap full(5);
    for (int k = 1; k <= 5; k++)
        full.put(k, k * 10);
    cout << "  Load factor of a 5-slot full table: " << full.loadFactor() << "\n";
    cout << "  Inserting a 6th key:\n";
    full.put(6, 60);

    cout << "\n=====================================================\n";
    return 0;
}

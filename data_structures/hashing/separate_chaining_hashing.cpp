#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Hash Map — Separate Chaining
//
// Collision strategy: each bucket holds a singly linked list of all the
// (key, value) pairs that hash to that bucket. Lookups walk the chain.
//   • Average put/get/remove: O(1 + α)   where α = load factor = keys / capacity
//   • Worst case (all keys collide): O(n)
//   • Never fails on collision — only "full" when memory is exhausted.
// ─────────────────────────────────────────────────────────────────────────────

class HashMap {
private:
    struct Node {
        int key;
        int value;
        Node* next;

        Node(int k, int v) {
            key = k;
            value = v;
            next = nullptr;
        }
    };

    vector<Node*> table;
    int capacity;
    int count;          // total number of stored keys

    // Hash function: maps a key to a bucket index.
    int hash(int key) const {
        return key % capacity;
    }

public:
    HashMap(int size = 10) {
        capacity = size;
        count = 0;
        table.resize(capacity, nullptr);
    }

    // Insert or update. Returns true if a new key was added, false if updated.
    bool put(int key, int value) {

        int index = hash(key);
        Node* current = table[index];

        // Update existing key within the chain.
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return false;       // updated, not inserted
            }
            current = current->next;
        }

        // New node — insert at the head of the chain (O(1)).
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        count++;
        return true;
    }

    // Lookup. Returns true and fills `value` on hit; false on miss.
    bool get(int key, int& value) const {

        Node* current = table[hash(key)];

        while (current != nullptr) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Membership test without fetching the value.
    bool contains(int key) const {
        int dummy;
        return get(key, dummy);
    }

    // Remove a key. Returns true if something was removed.
    bool remove(int key) {

        int index = hash(key);
        Node* current = table[index];
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (previous == nullptr)
                    table[index] = current->next;   // removing chain head
                else
                    previous->next = current->next;

                delete current;
                count--;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    int size() const { return count; }
    int getCapacity() const { return capacity; }

    // α = keys / buckets. Chaining tolerates α > 1, but large α means long chains.
    double loadFactor() const {
        return static_cast<double>(count) / capacity;
    }

    // Length of the chain at a given bucket (useful to visualize clustering).
    int chainLength(int index) const {
        int len = 0;
        for (Node* c = table[index]; c != nullptr; c = c->next) len++;
        return len;
    }

    // Empty the whole map, freeing every node.
    void clear() {
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        count = 0;
    }

    // Pretty-print every bucket including empty ones.
    void display() const {

        for (int i = 0; i < capacity; i++) {
            cout << "  [" << setw(2) << i << "] -> ";

            Node* current = table[i];
            if (current == nullptr) {
                cout << "NULL";
            } else {
                while (current != nullptr) {
                    cout << "(" << current->key << "," << current->value << ")";
                    current = current->next;
                    if (current != nullptr) cout << " -> ";
                }
            }
            cout << "\n";
        }
    }

    ~HashMap() {
        clear();
    }
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "================ Hash Map (Separate Chaining) ================\n";

    HashMap map(7);     // small capacity on purpose → force collisions

    // ── [Build] ──────────────────────────────────────────────────────────────
    cout << "\n[Build] Inserting {11->100, 21->200, 31->300, 5->500, 18->180}\n";
    cout << "        (11, 21, 31 all hash to bucket 11%7 = 3 → chain forms)\n";
    map.put(11, 100);
    map.put(21, 200);
    map.put(31, 300);
    map.put(5, 500);
    map.put(18, 180);

    cout << "\nTable after build:\n";
    map.display();

    cout << "\n[Stats]\n";
    cout << "  Size (keys) : " << map.size() << "\n";
    cout << "  Capacity    : " << map.getCapacity() << "\n";
    cout << "  Load factor : " << map.loadFactor() << "\n";
    cout << "  Bucket-3 chain length: " << map.chainLength(3) << "  (collision cluster)\n";

    // ── [Lookup] ─────────────────────────────────────────────────────────────
    cout << "\n[Lookup]\n";
    int value;
    cout << "  get(21)  -> " << (map.get(21, value) ? to_string(value) + " (hit)"  : "miss") << "\n";
    cout << "  get(99)  -> " << (map.get(99, value) ? to_string(value) + " (hit)"  : "miss") << "\n";
    cout << "  contains(5)  -> " << (map.contains(5) ? "Yes" : "No") << "\n";
    cout << "  contains(7)  -> " << (map.contains(7) ? "Yes" : "No") << "\n";

    // ── [Mutate] before/after ────────────────────────────────────────────────
    cout << "\n[Mutate] Removing key 21 from bucket 3's chain\n";
    cout << "  Before — bucket 3 chain length: " << map.chainLength(3) << "\n";
    map.remove(21);
    cout << "  After  — bucket 3 chain length: " << map.chainLength(3) << "\n";
    cout << "  remove(21) returned: " << boolalpha << map.remove(21) << "  (already gone → false)\n";

    // ── [Edge] duplicate key update ──────────────────────────────────────────
    cout << "\n[Edge] Duplicate key 11 — value should update, size should NOT grow\n";
    cout << "  Size before: " << map.size() << "\n";
    map.put(11, 999);
    cout << "  Size after : " << map.size() << "\n";
    map.get(11, value);
    cout << "  get(11) now -> " << value << "\n";

    // ── [Clear] ──────────────────────────────────────────────────────────────
    cout << "\n[Clear] Emptying the map\n";
    map.clear();
    cout << "  Size after clear: " << map.size() << "\n";
    cout << "  Load factor     : " << map.loadFactor() << "\n";

    cout << "\n==============================================================\n";
    return 0;
}

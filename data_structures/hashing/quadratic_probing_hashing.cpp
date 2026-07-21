#include <iostream>
using namespace std;

class HashMap {
private:
    struct Entry {
        int key;
        int value;
        bool occupied;
        bool deleted;

        Entry() {
            key = 0;
            value = 0;
            occupied = false;
            deleted = false;
        }
    };

    Entry* table;
    int capacity;

    int hashFunction(int key) {
        return key % capacity;
    }

public:
    HashMap(int size = 11) {   // Prime size is preferred
        capacity = size;
        table = new Entry[capacity];
    }

    // Insert / Update
    void put(int key, int value) {

        int index = hashFunction(key);

        for (int i = 0; i < capacity; i++) {

            // Quadratic Probing
            int newIndex = (index + i * i) % capacity;

            if (table[newIndex].occupied &&
                table[newIndex].key == key) {

                table[newIndex].value = value;
                return;
            }

            if (!table[newIndex].occupied ||
                table[newIndex].deleted) {

                table[newIndex].key = key;
                table[newIndex].value = value;
                table[newIndex].occupied = true;
                table[newIndex].deleted = false;
                return;
            }
        }

        cout << "Hash Table is Full\n";
    }

    // Search
    bool get(int key, int& value) {

        int index = hashFunction(key);

        for (int i = 0; i < capacity; i++) {

            int newIndex = (index + i * i) % capacity;

            if (!table[newIndex].occupied &&
                !table[newIndex].deleted)
                return false;

            if (table[newIndex].occupied &&
                table[newIndex].key == key) {

                value = table[newIndex].value;
                return true;
            }
        }

        return false;
    }

    // Delete
    void remove(int key) {

        int index = hashFunction(key);

        for (int i = 0; i < capacity; i++) {

            int newIndex = (index + i * i) % capacity;

            if (!table[newIndex].occupied &&
                !table[newIndex].deleted)
                return;

            if (table[newIndex].occupied &&
                table[newIndex].key == key) {

                table[newIndex].occupied = false;
                table[newIndex].deleted = true;
                return;
            }
        }
    }

    void display() {

        cout << "\nHash Table\n\n";

        for (int i = 0; i < capacity; i++) {

            cout << i << " -> ";

            if (table[i].occupied)
                cout << "("
                     << table[i].key
                     << ", "
                     << table[i].value
                     << ")";
            else if (table[i].deleted)
                cout << "DELETED";
            else
                cout << "EMPTY";

            cout << endl;
        }
    }

    ~HashMap() {
        delete[] table;
    }
};

int main() {

    HashMap map;

    map.put(13, 100);
    map.put(24, 200);
    map.put(35, 300);
    map.put(46, 400);

    map.display();

    int value;

    if (map.get(35, value))
        cout << "\n35 => " << value << endl;

    map.remove(24);

    cout << "\nAfter removing 24\n";

    map.display();

    return 0;
}
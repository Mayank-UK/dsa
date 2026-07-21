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

    int hash1(int key) {
        return key % capacity;
    }

    int hash2(int key) {
        return 7 - (key % 7);
    }

public:
    HashMap(int size = 11) {
        capacity = size;
        table = new Entry[capacity];
    }

    void put(int key, int value) {

        int index = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < capacity; i++) {

            int newIndex = (index + i * step) % capacity;

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

        cout << "Hash Table Full\n";
    }

    bool get(int key, int &value) {

        int index = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < capacity; i++) {

            int newIndex = (index + i * step) % capacity;

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

    void remove(int key) {

        int index = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < capacity; i++) {

            int newIndex = (index + i * step) % capacity;

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
                cout << "(" << table[i].key
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

    map.put(22, 100);
    map.put(33, 200);
    map.put(44, 300);
    map.put(55, 400);

    map.display();

    int value;

    if (map.get(44, value))
        cout << "\n44 => " << value << endl;

    map.remove(33);

    cout << "\nAfter removing 33\n";

    map.display();

    return 0;
}
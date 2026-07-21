#include <iostream>
#include <vector>

using namespace std;

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

    int hash(int key) {
        return key % capacity;
    }

public:
    HashMap(int size = 10) {
        capacity = size;
        table.resize(capacity, nullptr);
    }

    // Insert
    void put(int key, int value) {

        int index = hash(key);

        Node* current = table[index];

        // Update existing key
        while (current != nullptr) {

            if (current->key == key) {
                current->value = value;
                return;
            }

            current = current->next;
        }

        // Insert at beginning
        Node* newNode = new Node(key, value);

        newNode->next = table[index];

        table[index] = newNode;
    }

    // Search
    bool get(int key, int& value) {

        int index = hash(key);

        Node* current = table[index];

        while (current != nullptr) {

            if (current->key == key) {
                value = current->value;
                return true;
            }

            current = current->next;
        }

        return false;
    }

    // Delete
    void remove(int key) {

        int index = hash(key);

        Node* current = table[index];
        Node* previous = nullptr;

        while (current != nullptr) {

            if (current->key == key) {

                if (previous == nullptr)
                    table[index] = current->next;
                else
                    previous->next = current->next;

                delete current;
                return;
            }

            previous = current;
            current = current->next;
        }
    }

    void display() {

        for (int i = 0; i < capacity; i++) {

            cout << i << " -> ";

            Node* current = table[i];

            while (current != nullptr) {

                cout << "("
                     << current->key
                     << ","
                     << current->value
                     << ") -> ";

                current = current->next;
            }

            cout << "nullptr\n";
        }
    }

    ~HashMap() {

        for (int i = 0; i < capacity; i++) {

            Node* current = table[i];

            while (current != nullptr) {

                Node* temp = current;

                current = current->next;

                delete temp;
            }
        }
    }
};

int main() {

    HashMap map;

    map.put(11, 100);
    map.put(21, 200);
    map.put(31, 300);
    map.put(5, 500);

    map.display();

    int value;

    if (map.get(21, value))
        cout << "\n21 => " << value << endl;

    map.remove(21);

    cout << "\nAfter removing 21\n\n";

    map.display();

    return 0;
}
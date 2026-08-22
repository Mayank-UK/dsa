/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
#include <array>
#include <climits>

using std::array;
using std::cout;

struct Node
{
    int key;
    int value;
    Node *next;

    Node(int k, int v)
    {
        key = k;
        value = v;
        next = nullptr;
    }
};

class HashTable
{
private:
    static const int tableSize = 10;
    int keyCount;
    array<Node *, tableSize> hashTable;

    int hash(int key)
    {
        // this is only for positive key values, use the below one for negative keys
        return (key % tableSize);
        // return (key % tableSize + tableSize) % tableSize;
    }

public:
    HashTable()
    {
        keyCount = 0;

        for (int i = 0; i < tableSize; i++)
        {
            hashTable[i] = nullptr;
        }
    }

    ~HashTable()
    {
        clear();
    }

    void put(int k, int v)
    {
        int index = hash(k);
        Node *current = hashTable[index];

        // key already exists, then update
        while (current != nullptr)
        {
            if (current->key == k)
            {
                current->value = v;
                return;
            }

            current = current->next;
        }

        // key don't exist, then create new Node
        Node *newNode = new Node(k, v);

        Node *temp = hashTable[index];
        hashTable[index] = newNode;
        newNode->next = temp;

        keyCount++;
    }

    int get(int k)
    {
        int index = hash(k);

        Node *current = hashTable[index];

        while (current != nullptr)
        {
            if (current->key == k)
            {
                return current->value;
            }

            current = current->next;
        }

        return INT_MIN;
    }

    bool contains(int k)
    {
        int index = hash(k);

        Node *current = hashTable[index];

        while (current != nullptr)
        {
            if (current->key == k)
            {
                return true;
            }

            current = current->next;
        }

        return false;
    }

    double loadFactor()
    {
        return static_cast<double>(keyCount) / tableSize;
    }

    bool remove(int k)
    {
        int index = hash(k);
        Node *current = hashTable[index];
        Node *parent = nullptr;

        while (current != nullptr)
        {
            if (current->key == k)
            {
                // if index is the first node itself
                if (parent == nullptr)
                {
                    hashTable[index] = current->next;
                    delete current;
                    keyCount--;
                    return true;
                }

                parent->next = current->next;
                delete current;
                keyCount--;
                return true;
            }

            parent = current;
            current = current->next;
        }

        return false;
    }

    void clear()
    {
        for (int i = 0; i < tableSize; i++)
        {
            Node *current = hashTable[i];

            while (current != nullptr)
            {
                Node *next = current->next;
                delete current;

                current = next;
            }

            hashTable[i] = nullptr;
        }

        keyCount = 0;
    }

    void display()
    {
        for (int i = 0; i < tableSize; i++)
        {
            Node *current = hashTable[i];

            cout << i << ": ";

            while (current != nullptr)
            {

                cout << "[" << current->key << " , " << current->value << "]";

                current = current->next;
            }

            cout << "\n";
        }
    }
};

int main()
{
    HashTable ht;

    // Insert
    ht.put(10, 100);
    ht.put(20, 200);
    ht.put(30, 300);
    ht.put(5, 500);

    cout << "After insertion:\n";
    ht.display();

    // Get
    cout << "\nGet 20: " << ht.get(20) << "\n";
    cout << "Get 99: " << ht.get(99) << "\n";

    // Contains
    cout << "\nContains 30: " << ht.contains(30) << "\n";
    cout << "Contains 99: " << ht.contains(99) << "\n";

    // Update existing key
    ht.put(20, 999);

    cout << "\nAfter updating key 20:\n";
    ht.display();

    cout << "\nGet 20: " << ht.get(20) << "\n";

    // Remove first node in a bucket
    cout << "\nRemove 30: " << ht.remove(30) << "\n";

    // Remove another node
    cout << "Remove 20: " << ht.remove(20) << "\n";

    // Try removing non-existent key
    cout << "Remove 99: " << ht.remove(99) << "\n";

    cout << "\nAfter removals:\n";
    ht.display();

    // Test collision handling
    // With tableSize = 10:
    // 1, 11, 21 all map to bucket 1
    ht.put(1, 1000);
    ht.put(11, 1100);
    ht.put(21, 2100);

    cout << "\nAfter inserting collision keys (1, 11, 21):\n";
    ht.display();

    cout << "\nGet 11: " << ht.get(11) << "\n";
    cout << "Get 21: " << ht.get(21) << "\n";

    // Remove middle node from collision chain
    cout << "\nRemove 11: " << ht.remove(11) << "\n";

    cout << "\nAfter removing 11:\n";
    ht.display();

    // Load factor
    cout << "\nLoad factor: " << ht.loadFactor() << "\n";

    // Clear
    ht.clear();

    cout << "\nAfter clear:\n";
    ht.display();

    cout << "\nLoad factor: " << ht.loadFactor() << "\n";

    return 0;
}
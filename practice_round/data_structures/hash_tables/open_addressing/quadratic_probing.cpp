/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
#include <array>
#include <climits>

using std::array;
using std::cout;

enum SlotState
{
    EMPTY,
    OCCUPIED,
    DELETED,
};

struct Node
{
    int key;
    int value;
    SlotState state;

    Node()
    {
        key = 0;
        value = 0;
        state = EMPTY;
    }
};

class HashTable
{
private:
    // use prime sizing to reduce clustering
    static const int tableSize = 11;
    int keyCount;
    array<Node, tableSize> hashTable;

    int hash(int k)
    {
        // this only handles positive numbers, for negative use the one below
        return (k % tableSize);
        // return ((k % tableSize) + tableSize) % tableSize
    }

    // quadratic probing is highly disliked because it does not guarantee visiting every slot
    int probe(int base, int i)
    {
        return (base + i * i) % tableSize;
    }

public:
    HashTable()
    {
        keyCount = 0;
    }

    ~HashTable()
    {
        clear();
    }

    void put(int k, int v)
    {
        int base = hash(k);
        int firstDeletedSlot = -1;

        for (int i = 0; i < tableSize; i++)
        {
            // for i = 0, probe() gives same value as hash(), so no need to handle the starting index separately
            int probeIndex = probe(base, i);
            Node &current = hashTable[probeIndex];

            // if key is found
            if (current.key == k && current.state == OCCUPIED)
            {
                current.value = v;
                return;
            }

            // if key is not found
            if (current.state == EMPTY)
            {
                int target = (firstDeletedSlot == -1) ? probeIndex : firstDeletedSlot;

                hashTable[target].key = k;
                hashTable[target].value = v;
                hashTable[target].state = OCCUPIED;

                keyCount++;
                return;
            }

            // is any DELETE position is encountered before EMPTY position
            if (current.state == DELETED && firstDeletedSlot == -1)
            {
                firstDeletedSlot = probeIndex;
            }
        }

        // if no empty slot was found, maybe because all were marked as DELETED
        if (firstDeletedSlot != -1)
        {
            hashTable[firstDeletedSlot].key = k;
            hashTable[firstDeletedSlot].value = v;
            hashTable[firstDeletedSlot].state = OCCUPIED;

            keyCount++;
        }
    }

    int get(int k)
    {
        int base = hash(k);

        for (int i = 0; i < tableSize; i++)
        {
            int probeIndex = probe(base, i);
            Node &current = hashTable[probeIndex];

            if (current.key == k && current.state == OCCUPIED)
            {
                return current.value;
            }

            if (current.state == EMPTY)
            {
                return INT_MIN;
            }
        }

        return INT_MIN;
    }

    bool contains(int k)
    {
        int base = hash(k);

        for (int i = 0; i < tableSize; i++)
        {
            int probeIndex = probe(base, i);
            Node &current = hashTable[probeIndex];

            if (current.key == k && current.state == OCCUPIED)
            {
                return true;
            }

            if (current.state == EMPTY)
            {
                return false;
            }
        }

        return false;
    }

    bool remove(int k)
    {
        int base = hash(k);

        for (int i = 0; i < tableSize; i++)
        {
            int probeIndex = probe(base, i);
            Node &current = hashTable[probeIndex];

            if (current.key == k && current.state == OCCUPIED)
            {
                current.key = 0;
                current.value = 0;
                current.state = DELETED;

                keyCount--;

                return true;
            }

            if (current.state == EMPTY)
            {
                return false;
            }
        }

        return false;
    }

    double loadFactor()
    {
        return static_cast<double>(keyCount) / tableSize;
    }

    void display()
    {
        for (int i = 0; i < tableSize; i++)
        {
            Node &current = hashTable[i];

            cout << "[" << current.key << "," << current.value << "]";
        }

        cout << "\n";
    }

    void clear()
    {
        for (int i = 0; i < tableSize; i++)
        {
            Node &current = hashTable[i];

            current.key = 0;
            current.value = 0;
            current.state = EMPTY;
        }

        keyCount = 0;
    }
};

int main()
{
    HashTable ht;

    // Insert
    ht.put(10, 100);
    ht.put(21, 200);
    ht.put(32, 300);
    ht.put(5, 500);

    cout << "After insertion:\n";
    ht.display();

    // Get
    cout << "\nGet 21: " << ht.get(21) << "\n";
    cout << "Get 99: " << ht.get(99) << "\n";

    // Contains
    cout << "\nContains 32: " << ht.contains(32) << "\n";
    cout << "Contains 99: " << ht.contains(99) << "\n";

    // Update existing key
    ht.put(21, 999);

    cout << "\nAfter updating key 21:\n";
    ht.display();

    cout << "Get 21: " << ht.get(21) << "\n";

    // Remove
    cout << "\nRemove 21: " << ht.remove(21) << "\n";
    cout << "Contains 21: " << ht.contains(21) << "\n";

    cout << "\nAfter removing 21:\n";
    ht.display();

    // Test reuse of DELETED slot
    ht.put(43, 4300);

    cout << "\nAfter inserting 43 (should reuse deleted slot):\n";
    ht.display();

    // Load factor
    cout << "\nLoad factor: " << ht.loadFactor() << "\n";

    // Clear
    ht.clear();

    cout << "\nAfter clear:\n";
    ht.display();

    cout << "Load factor: " << ht.loadFactor() << "\n";

    return 0;
}
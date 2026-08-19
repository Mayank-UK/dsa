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
    // prime size reduces clustering patterns
    static const int tableSize = 11;
    int keyCount;
    array<Node, tableSize> hashTable;

    int hash(int key)
    {
        // this only work for positive keys, for negative keys use the one below
        return (key % tableSize);
        // return ((key % tableSize) + tableSize) % tableSize;
    }

    int probe(int base, int i)
    {
        return (base + i) % tableSize;
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
        int firstDeletePosition = -1;

        for (int i = 0; i < tableSize; i++)
        {
            // for i = 0, the value of probeIndex is same as hash(k), so no need to separately start with hash(k)
            int probeIndex = probe(base, i);
            Node &current = hashTable[probeIndex];

            // if key already exists
            if (current.key == k && current.state == OCCUPIED)
            {
                current.value = v;
                return;
            }

            // if key don't exist, an EMPTY state simply means key don't exist
            if (current.state == EMPTY)
            {
                // before inserting in this EMPTY position, first check if any DELETED position was detected in past
                int target = (firstDeletePosition == -1) ? probeIndex : firstDeletePosition;

                hashTable[target].key = k;
                hashTable[target].value = v;
                hashTable[target].state = OCCUPIED;

                keyCount++;

                return;
            }

            // register first deleted node
            if (current.state == DELETED && firstDeletePosition == -1)
            {
                firstDeletePosition = probeIndex;
            }
        }

        // if EMPTY is never encountered, the loop may never insert anything, this can happen in case if all slots are marked as DELETED
        if (firstDeletePosition != -1)
        {
            hashTable[firstDeletePosition].key = k;
            hashTable[firstDeletePosition].value = v;
            hashTable[firstDeletePosition].state = OCCUPIED;
            keyCount++;
        }
    }

    int get(int k)
    {
        int base = hash(k);

        for (int i = 0; i < tableSize; i++)
        {
            // for i = 0, the value of probeIndex is same as hash(k), so no need to separately start with hash(k)
            int probeIndex = probe(base, i);
            Node &current = hashTable[probeIndex];

            if (current.key == k && current.state == OCCUPIED)
            {
                return current.value;
            }

            // if encountered EMPTY, key cannot exist
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
            // for i = 0, the value of probeIndex is same as hash(k), so no need to separately start with hash(k)
            int probeIndex = probe(base, i);

            Node &current = hashTable[probeIndex];

            if (current.key == k && current.state == OCCUPIED)
            {
                return true;
            }

            // if encountered EMPTY, key cannot exist in linear probing
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

    bool remove(int k)
    {
        int base = hash(k);

        for (int i = 0; i < tableSize; i++)
        {
            // for i = 0, the value of probeIndex is same as hash(k), so no need to separately start with hash(k)
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

            // if encountered EMPTY, key cannot exist in linear probing
            if (current.state == EMPTY)
            {
                return false;
            }
        }

        return false;
    }

    void display()
    {

        for (int i = 0; i < tableSize; i++)
        {
            Node &current = hashTable[i];
            if (current.state == OCCUPIED)
            {
                cout << "[" << current.key << " , " << current.value << "] ";
            }
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
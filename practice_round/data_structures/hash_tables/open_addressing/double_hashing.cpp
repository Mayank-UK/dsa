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

    int hash1(int k)
    {
        // this only handles positive numbers, for negative use the one below
        return (k % tableSize);
        // return ((k % tableSize) + tableSize) % tableSize
    }

    // using a separate hash for solving primary and secondary clustering
    int hash2(int k)
    {
        // use a number that is co-prime with tableSize
        return (7 - (k % 7));
    }

    int probe(int hash1, int hash2, int i)
    {
        return (hash1 + hash2 * i) % tableSize;
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
        int h1 = hash1(k);
        int h2 = hash2(k);
        int firstDeletedSlot = -1;

        for (int i = 0; i < tableSize; i++)
        {
            // for i = 0, probe() gives same value as hash(), so no need to handle the starting index separately
            int probeIndex = probe(h1, h2, i);
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
        int h1 = hash1(k);
        int h2 = hash2(k);

        for (int i = 0; i < tableSize; i++)
        {
            int probeIndex = probe(h1, h2, i);
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
        int h1 = hash1(k);
        int h2 = hash2(k);

        for (int i = 0; i < tableSize; i++)
        {
            int probeIndex = probe(h1, h2, i);
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
        int h1 = hash1(k);
        int h2 = hash2(k);

        for (int i = 0; i < tableSize; i++)
        {
            int probeIndex = probe(h1, h2, i);
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
    ht.put(43, 400);
    ht.put(54, 500);

    cout << "Initial table:\n";
    ht.display();

    // Get
    cout << "get(32): " << ht.get(32) << "\n";
    cout << "get(99): " << ht.get(99) << "\n";

    // Contains
    cout << "contains(43): " << ht.contains(43) << "\n";
    cout << "contains(99): " << ht.contains(99) << "\n";

    // Update existing key
    ht.put(32, 999);

    cout << "\nAfter updating key 32:\n";
    cout << "get(32): " << ht.get(32) << "\n";

    // Remove
    cout << "\nremove(21): " << ht.remove(21) << "\n";
    cout << "contains(21): " << ht.contains(21) << "\n";

    cout << "\nAfter removing 21:\n";
    ht.display();

    // Test insertion into a DELETED slot
    ht.put(65, 600);

    cout << "\nAfter inserting 65:\n";
    ht.display();

    // Clear
    ht.clear();

    cout << "\nAfter clear:\n";
    ht.display();

    return 0;
}
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

// Maximum levels allowed for the skip list
const int MAX_LEVEL = 4;
const float P_VAL = 0.5f;

// Node structure for Skip List
struct Node {
    int val;
    vector<Node*> forward;

    Node(int val, int level) {
        this->val = val;
        forward.resize(level + 1, nullptr);
    }
};

// Skip List class implementation
class SkipList {
    int maxLevel;
    int currentLevel;
    Node* header;

public:
    SkipList() {
        maxLevel = MAX_LEVEL;
        currentLevel = 0;
        header = new Node(INT_MIN, maxLevel);
    }

    // Random level generator using coin-flip probability
    int randomLevel() {
        int lvl = 0;
        while (((float)rand() / RAND_MAX) < P_VAL && lvl < maxLevel) {
            lvl++;
        }
        return lvl;
    }

    // Search for a target value
    bool search(int target) {
        Node* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->val < target) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        return (current != nullptr && current->val == target);
    }

    // Insert a value into the skip list
    void insert(int val) {
        vector<Node*> update(maxLevel + 1, nullptr);
        Node* current = header;

        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->val < val) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current == nullptr || current->val != val) {
            int rLevel = randomLevel();

            if (rLevel > currentLevel) {
                for (int i = currentLevel + 1; i <= rLevel; i++) {
                    update[i] = header;
                }
                currentLevel = rLevel;
            }

            Node* newNode = new Node(val, rLevel);
            for (int i = 0; i <= rLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
            cout << "Successfully inserted " << val << " with level tower height " << rLevel << "\n";
        }
    }

    // Display the skip list structure across all levels
    void displayList() {
        cout << "\n--- Skip List Structure ---\n";
        for (int i = currentLevel; i >= 0; i--) {
            Node* node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node != nullptr) {
                cout << node->val << " ";
                node = node->forward[i];
            }
            cout << "\n";
        }
        cout << "---------------------------\n";
    }
};

int main() {
    srand(time(nullptr));

    SkipList skipList;

    skipList.insert(3);
    skipList.insert(6);
    skipList.insert(7);
    skipList.insert(9);
    skipList.insert(12);
    skipList.insert(19);
    skipList.insert(17);
    skipList.insert(26);

    skipList.displayList();

    int target = 19;
    if (skipList.search(target)) {
        cout << "Found value " << target << " in the skip list.\n";
    } else {
        cout << "Value " << target << " not found.\n";
    }

    return 0;
}
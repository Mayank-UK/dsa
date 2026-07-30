#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <string>

using namespace std;

// ============================================================
// Skip List — a probabilistically balanced alternative to a self-balancing BST.
// A sorted linked list is stacked under several "express" lanes: each node is
// promoted to the next level up with probability P_VAL (a coin flip). Search
// drops in from the top level, scanning fast lanes and stepping down, visiting
// O(log n) nodes in expectation — like a BST but with no rotations. Insert /
// search are O(log n) expected; the height is bounded by MAX_LEVEL. The
// randomness replaces the rebalancing logic of an AVL / red-black tree.
// ============================================================

static const int MAX_LEVEL = 4;
static const float P_VAL   = 0.5f;

struct Node {
    int val;
    vector<Node*> forward;   // forward[i] = next node at level i

    Node(int val, int level) : val(val), forward(level + 1, nullptr) {}
};

class SkipList {
    int maxLevel;
    int currentLevel;
    Node* header;            // sentinel with INT_MIN, holds all levels

public:
    SkipList() : maxLevel(MAX_LEVEL), currentLevel(0) {
        header = new Node(INT_MIN, maxLevel);
    }

    // ─── Free every node (level-0 list owns them all) ───
    ~SkipList() {
        Node* cur = header;
        while (cur != nullptr) {
            Node* nxt = cur->forward[0];
            delete cur;
            cur = nxt;
        }
    }

    // Coin-flip level generator: keep promoting while heads, up to maxLevel.
    int randomLevel() {
        int lvl = 0;
        while (((double)rand() / RAND_MAX) < P_VAL && lvl < maxLevel)
            lvl++;
        return lvl;
    }

    // ─── Search ───  Time: O(log n) expected
    bool search(int target) const {
        const Node* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->val < target)
                current = current->forward[i];
        }
        current = current->forward[0];
        return (current != nullptr && current->val == target);
    }

    // ─── Insert (no duplicates) ───  Time: O(log n) expected
    // Returns the new node's tower height, or -1 if the value already exists.
    int insert(int val) {
        vector<Node*> update(maxLevel + 1, nullptr);
        Node* current = header;

        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->val < val)
                current = current->forward[i];
            update[i] = current;
        }
        current = current->forward[0];

        if (current != nullptr && current->val == val)
            return -1;                          // duplicate — leave as-is

        int rLevel = randomLevel();
        if (rLevel > currentLevel) {
            for (int i = currentLevel + 1; i <= rLevel; i++)
                update[i] = header;             // new top levels hang off the header
            currentLevel = rLevel;
        }

        Node* newNode = new Node(val, rLevel);
        for (int i = 0; i <= rLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
        return rLevel;
    }

    void displayList() const {
        for (int i = currentLevel; i >= 0; i--) {
            cout << "    Level " << i << ": ";
            Node* node = header->forward[i];
            while (node != nullptr) {
                cout << node->val << " ";
                node = node->forward[i];
            }
            cout << "\n";
        }
    }

    int level() const { return currentLevel; }
};

// ============================================================
int main() {
    srand((unsigned)time(nullptr));

    cout << "====================== Skip List ======================\n\n";

    cout << "[Complexity]\n";
    cout << "  search / insert : O(log n) expected   (O(n) worst case, prob. tiny)\n";
    cout << "  space           : O(n)                 (~2n nodes counting express lanes)\n";
    cout << "  Notes            : coin-flip promotion replaces tree rotations; max level "
         << MAX_LEVEL << ".\n\n";

    cout << "[Build]  insert 3,6,7,9,12,19,17,26\n";
    SkipList list;
    int vals[] = {3, 6, 7, 9, 12, 19, 17, 26};
    for (int v : vals) {
        int h = list.insert(v);
        cout << "    inserted " << v << "  (tower height " << h << ")\n";
    }

    cout << "\n[Structure]  top level = " << list.level() << "\n";
    list.displayList();

    cout << "\n[Searches]\n";
    auto check = [&](int target) {
        cout << "    " << target << " -> " << (list.search(target) ? "Found" : "Not Found") << "\n";
    };
    check(19);   // present
    check(17);   // present
    check(3);    // present (first)
    check(26);   // present (last)
    check(15);   // absent

    cout << "\n[Edge Cases]\n";
    cout << "    duplicate insert (re-insert 19) -> tower height "
         << list.insert(19) << "  (-1 = already present, no change)\n";
    SkipList empty;
    cout << "    search on empty list -> 19 is " << (empty.search(19) ? "Found" : "Not Found") << "\n";
    SkipList single;
    single.insert(50);
    cout << "    single-element list -> search 50 is " << (single.search(50) ? "Found" : "Not Found")
         << ", search 51 is " << (single.search(51) ? "Found" : "Not Found") << "\n";

    cout << "\n[Note]\n";
    cout << "  Skip lists give BST-like O(log n) ops with simpler concurrency than a\n";
    cout << "  rebalancing tree — used in Redis sorted sets and LevelDB/MemTable. P_VAL\n";
    cout << "  and MAX_LEVEL tune the height/time trade-off (p=1/2 is the classic choice).\n";

    return 0;
}

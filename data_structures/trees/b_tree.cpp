#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <algorithm>

using namespace std;

class BTree {

private:

    // ─────────────────── Node ───────────────────

    struct Node {
        vector<int> keys;         // Keys stored in increasing order
        vector<Node*> children;   // Child pointers
        bool isLeaf;              // True if node is a leaf

        Node(bool leaf) : isLeaf(leaf) {}
    };

    Node* root;
    int t; // Minimum degree. Every node (except root) must contain at least t-1 keys.

    // ─────────────────── Search ───────────────────

    Node* searchNode(Node* node, int value) const {
        if (node == nullptr) return nullptr;

        int i = 0;
        int n = node->keys.size();

        // Find the first key greater than or equal to value
        while (i < n && value > node->keys[i]) {
            i++;
        }

        // If the found key is equal to value, return this node
        if (i < n && node->keys[i] == value) {
            return node;
        }

        // If key is not found here and this is a leaf node
        if (node->isLeaf) {
            return nullptr;
        }

        // Go to the appropriate child
        return searchNode(node->children[i], value);
    }

    // ─────────────────── Split Child ───────────────────

    // Splits the child y of node x at index i. y must be full (2t-1 keys).
    void splitChild(Node* x, int i, Node* y) {
        Node* z = new Node(y->isLeaf);

        // z will store the last (t-1) keys of y
        for (int j = 0; j < t - 1; j++) {
            z->keys.push_back(y->keys[j + t]);
        }

        // If y is not a leaf, z also gets the last t children of y
        if (!y->isLeaf) {
            for (int j = 0; j < t; j++) {
                z->children.push_back(y->children[j + t]);
            }
        }

        // Reduce the number of keys/children in y
        y->keys.resize(t - 1);
        if (!y->isLeaf) y->children.resize(t);

        // Insert z as a child of x
        x->children.insert(x->children.begin() + i + 1, z);

        // Move the middle key of y up to x
        x->keys.insert(x->keys.begin() + i, y->keys[t - 1]);
        y->keys.pop_back(); // Remove the promoted key from y
    }

    // ─────────────────── Insert Non-Full ───────────────────

    void insertNonFull(Node* x, int value) {
        int i = x->keys.size() - 1;

        if (x->isLeaf) {
            // Find location to insert new key and shift existing keys
            x->keys.push_back(0); // Make space
            while (i >= 0 && x->keys[i] > value) {
                x->keys[i + 1] = x->keys[i];
                i--;
            }
            x->keys[i + 1] = value;
        } else {
            // Find the child which is going to have the new key
            while (i >= 0 && x->keys[i] > value) {
                i--;
            }
            i++; // The child index

            // If the child is full, split it
            if (x->children[i]->keys.size() == (size_t)(2 * t - 1)) {
                splitChild(x, i, x->children[i]);

                // After split, the middle key of x->children[i] goes up,
                // and x->children[i] is split into two. Decide which to descend.
                if (x->keys[i] < value) {
                    i++;
                }
            }
            insertNonFull(x->children[i], value);
        }
    }

    // ─────────────────── Deletion Helpers ───────────────────

    int findKey(Node* x, int value) const {
        int idx = 0;
        while (idx < x->keys.size() && x->keys[idx] < value)
            ++idx;
        return idx;
    }

    int getPred(Node* x, int idx) {
        Node* curr = x->children[idx];
        while (!curr->isLeaf)
            curr = curr->children.back();
        return curr->keys.back();
    }

    int getSucc(Node* x, int idx) {
        Node* curr = x->children[idx + 1];
        while (!curr->isLeaf)
            curr = curr->children.front();
        return curr->keys.front();
    }

    void borrowFromPrev(Node* x, int idx) {
        Node* child = x->children[idx];
        Node* sibling = x->children[idx - 1];

        // Shift all keys in child one step ahead
        child->keys.insert(child->keys.begin(), x->keys[idx - 1]);

        // If not a leaf, shift child pointers as well
        if (!child->isLeaf) {
            child->children.insert(child->children.begin(), sibling->children.back());
            sibling->children.pop_back();
        }

        // Move sibling's last key up to parent
        x->keys[idx - 1] = sibling->keys.back();
        sibling->keys.pop_back();
    }

    void borrowFromNext(Node* x, int idx) {
        Node* child = x->children[idx];
        Node* sibling = x->children[idx + 1];

        // child takes the parent's key
        child->keys.push_back(x->keys[idx]);

        // sibling's first key goes up to parent
        x->keys[idx] = sibling->keys.front();
        sibling->keys.erase(sibling->keys.begin());

        // sibling's first child moves to child's last child
        if (!child->isLeaf) {
            child->children.push_back(sibling->children.front());
            sibling->children.erase(sibling->children.begin());
        }
    }

    void merge(Node* x, int idx) {
        Node* child = x->children[idx];
        Node* sibling = x->children[idx + 1];

        // Pull down a key from the current node and insert it into child
        child->keys.push_back(x->keys[idx]);

        // Transfer all keys and children from sibling to child
        for (int i = 0; i < sibling->keys.size(); ++i)
            child->keys.push_back(sibling->keys[i]);

        if (!child->isLeaf) {
            for (int i = 0; i < sibling->children.size(); ++i)
                child->children.push_back(sibling->children[i]);
        }

        // Remove the pulled down key and sibling pointer from parent
        x->keys.erase(x->keys.begin() + idx);
        x->children.erase(x->children.begin() + idx + 1);

        delete sibling;
    }

    void fill(Node* x, int idx) {
        // If previous child has more than t-1 keys, borrow from it
        if (idx != 0 && x->children[idx - 1]->keys.size() >= t) {
            borrowFromPrev(x, idx);
        }
        // If next child has more than t-1 keys, borrow from it
        else if (idx != x->keys.size() && x->children[idx + 1]->keys.size() >= t) {
            borrowFromNext(x, idx);
        }
        // Otherwise, merge child with its sibling
        else {
            if (idx != x->keys.size()) {
                merge(x, idx);
            } else {
                merge(x, idx - 1);
            }
        }
    }

    void removeNode(Node* x, int value) {
        int idx = findKey(x, value);

        // The key to be removed is present in this node
        if (idx < x->keys.size() && x->keys[idx] == value) {
            if (x->isLeaf) {
                // Case 1: Key is in a leaf node
                x->keys.erase(x->keys.begin() + idx);
            } else {
                // Case 2: Key is in an internal node
                if (x->children[idx]->keys.size() >= t) {
                    // Predecessor child has enough keys
                    int pred = getPred(x, idx);
                    x->keys[idx] = pred;
                    removeNode(x->children[idx], pred);
                } else if (x->children[idx + 1]->keys.size() >= t) {
                    // Successor child has enough keys
                    int succ = getSucc(x, idx);
                    x->keys[idx] = succ;
                    removeNode(x->children[idx + 1], succ);
                } else {
                    // Both have t-1 keys, merge them
                    merge(x, idx);
                    removeNode(x->children[idx], value);
                }
            }
        } else {
            // Key is not present in this node
            if (x->isLeaf) {
                return; // Key does not exist in the tree
            }

            bool isLastChild = (idx == x->keys.size());

            // Ensure the child we're traversing to has at least t keys
            if (x->children[idx]->keys.size() < t) {
                fill(x, idx);
            }

            // If the last child was merged, we must traverse the previous child
            if (isLastChild && idx > x->keys.size()) {
                removeNode(x->children[idx - 1], value);
            } else {
                removeNode(x->children[idx], value);
            }
        }
    }

    // ─────────────────── Minimum / Maximum ───────────────────

    Node* findMin(Node* node) const {
        if (node == nullptr) return nullptr;
        while (!node->isLeaf)
            node = node->children.front();
        return node;
    }

    Node* findMax(Node* node) const {
        if (node == nullptr) return nullptr;
        while (!node->isLeaf)
            node = node->children.back();
        return node;
    }

    // ─────────────────── Count / Height ───────────────────

    int countKeys(Node* node) const {
        if (node == nullptr) return 0;
        int count = node->keys.size();
        if (!node->isLeaf) {
            for (Node* child : node->children) {
                count += countKeys(child);
            }
        }
        return count;
    }

    int getHeight(Node* node) const {
        if (node == nullptr) return 0;
        if (node->isLeaf) return 1;
        return 1 + getHeight(node->children[0]);
    }

    // ─────────────────── Destroy ───────────────────

    void destroy(Node* node) {
        if (node != nullptr) {
            if (!node->isLeaf) {
                for (Node* child : node->children) {
                    destroy(child);
                }
            }
            delete node;
        }
    }

    // ─────────────────── Traversals ───────────────────

    void inorder(Node* node) const {
        if (node != nullptr) {
            int i;
            for (i = 0; i < node->keys.size(); i++) {
                if (!node->isLeaf) inorder(node->children[i]);
                cout << node->keys[i] << " ";
            }
            if (!node->isLeaf) inorder(node->children[i]);
        }
    }

public:

    BTree(int _t = 2) : root(nullptr), t(_t) {
        if (t < 2) t = 2; // B-tree minimum degree must be at least 2
    }

    ~BTree() {
        destroy(root);
    }

    // Prevent accidental shallow copies
    BTree(const BTree&) = delete;
    BTree& operator=(const BTree&) = delete;

    // ─────────────────── Mutators ───────────────────

    void insert(int value) {
        // Drop duplicates silently to match RBT behavior
        if (search(value)) return;

        if (root == nullptr) {
            root = new Node(true);
            root->keys.push_back(value);
        } else {
            // If root is full, tree grows in height
            if (root->keys.size() == (size_t)(2 * t - 1)) {
                Node* s = new Node(false);
                s->children.push_back(root);
                splitChild(s, 0, root);
                
                int i = (s->keys[0] < value) ? 1 : 0;
                insertNonFull(s->children[i], value);
                root = s;
            } else {
                insertNonFull(root, value);
            }
        }
    }

    void remove(int value) {
        if (root == nullptr) return;

        removeNode(root, value);

        // If root becomes empty, make its first child the new root (if it has one)
        if (root->keys.size() == 0) {
            Node* tmp = root;
            if (root->isLeaf) {
                root = nullptr;
            } else {
                root = root->children[0];
            }
            delete tmp;
        }
    }

    void clear() {
        destroy(root);
        root = nullptr;
    }

    // ─────────────────── Queries ───────────────────

    [[nodiscard]] bool search(int value) const {
        return searchNode(root, value) != nullptr;
    }

    [[nodiscard]] optional<int> getMin() const {
        Node* minNode = findMin(root);
        return minNode ? optional<int>(minNode->keys.front()) : nullopt;
    }

    [[nodiscard]] optional<int> getMax() const {
        Node* maxNode = findMax(root);
        return maxNode ? optional<int>(maxNode->keys.back()) : nullopt;
    }

    [[nodiscard]] int height() const { return getHeight(root); }
    [[nodiscard]] int size()   const { return countKeys(root); }
    [[nodiscard]] bool isEmpty() const { return root == nullptr; }

    // ─────────────────── Traversals ───────────────────

    void inorder() const {
        inorder(root);
        cout << "\n";
    }

    void levelOrder() const {
        if (root == nullptr) return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            
            // Iterate over all nodes in the current level
            while (levelSize > 0) {
                Node* current = q.front();
                q.pop();

                cout << "[ ";
                for (int key : current->keys) {
                    cout << key << " ";
                }
                cout << "] ";

                if (!current->isLeaf) {
                    for (Node* child : current->children) {
                        q.push(child);
                    }
                }
                levelSize--;
            }
            cout << "\n"; // Newline after each tree level
        }
    }
};

int main() {
    // Initialize a B-Tree with minimum degree t=3
    // Nodes will have between 2 and 5 keys (except root)
    BTree btree(3);

    btree.insert(50);
    btree.insert(30);
    btree.insert(70);
    btree.insert(20);
    btree.insert(40);
    btree.insert(60);
    btree.insert(80);
    btree.insert(10);
    btree.insert(25);
    btree.insert(35);
    btree.insert(45);

    cout << "Inorder: \n";
    btree.inorder();

    cout << "\nLevel Order (Each line is a tree depth level): \n";
    btree.levelOrder();

    cout << "\nMinimum:      " << btree.getMin().value_or(-1) << "\n";
    cout << "Maximum:      " << btree.getMax().value_or(-1) << "\n";
    cout << "Height:       " << btree.height()       << "\n";
    cout << "Size (keys):  " << btree.size()         << "\n";

    cout << "\nSearch 60:  " << (btree.search(60)  ? "Found" : "Not Found") << "\n";
    cout << "Search 100: " << (btree.search(100) ? "Found" : "Not Found") << "\n";

    btree.remove(20);
    cout << "\nAfter deleting 20:\n";
    btree.levelOrder();

    btree.remove(30);
    cout << "\nAfter deleting 30:\n";
    btree.levelOrder();

    btree.remove(50);
    cout << "\nAfter deleting 50:\n";
    btree.levelOrder();

    cout << "\nFinal Inorder: \n";
    btree.inorder();
    cout << "Final Height:       " << btree.height()       << "\n";
    cout << "Final Size (keys):  " << btree.size()         << "\n";

    return 0;
}
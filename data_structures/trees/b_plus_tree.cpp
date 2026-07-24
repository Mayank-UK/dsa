#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <algorithm>

using namespace std;

class BPlusTree {

private:

    // ─────────────────── Node ───────────────────

    struct Node {
        bool isLeaf;
        vector<int> keys;
        vector<Node*> children; // Used only for internal nodes
        Node* next;             // Used only for leaf nodes (linked list)

        Node(bool leaf) : isLeaf(leaf), next(nullptr) {}
    };

    Node* root;
    int m; // Order of the B+ Tree (Maximum number of children). Max keys = m - 1.

    // Struct to handle upward propagation of keys during a split
    struct SplitResult {
        int promotedKey;
        Node* newNode;
        
        SplitResult() : promotedKey(0), newNode(nullptr) {}
        SplitResult(int key, Node* node) : promotedKey(key), newNode(node) {}
    };

    // ─────────────────── Search Helper ───────────────────

    Node* findLeaf(Node* node, int value) const {
        if (node == nullptr) return nullptr;

        while (!node->isLeaf) {
            int i = 0;
            // Find the first key greater than value
            while (i < (int)node->keys.size() && value >= node->keys[i]) {
                i++;
            }
            node = node->children[i];
        }
        return node;
    }

    // ─────────────────── Insert Recursive ───────────────────

    // Returns a valid SplitResult if the node was split, or an empty one if not.
    SplitResult insertInternal(Node* node, int value) {
        
        if (node->isLeaf) {
            // 1. Find position and insert in the leaf
            auto it = upper_bound(node->keys.begin(), node->keys.end(), value);
            
            // Ignore duplicate keys silently
            if (it != node->keys.begin() && *(it - 1) == value) {
                return SplitResult(); 
            }
            node->keys.insert(it, value);

            // 2. Check for overflow
            if ((int)node->keys.size() == m) {
                Node* sibling = new Node(true);
                int splitIndex = m / 2;

                // Move the right half of the keys to the new sibling
                sibling->keys.assign(node->keys.begin() + splitIndex, node->keys.end());
                node->keys.erase(node->keys.begin() + splitIndex, node->keys.end());

                // Maintain the linked list of leaves
                sibling->next = node->next;
                node->next = sibling;

                // For a leaf, we COPY the first key of the right node up
                return SplitResult(sibling->keys.front(), sibling);
            }
            return SplitResult();
        } 
        else {
            // 1. Find the correct child to route to
            int i = 0;
            while (i < (int)node->keys.size() && value >= node->keys[i]) {
                i++;
            }

            // 2. Recurse down
            SplitResult split = insertInternal(node->children[i], value);

            // 3. Handle child split (if any)
            if (split.newNode != nullptr) {
                node->keys.insert(node->keys.begin() + i, split.promotedKey);
                node->children.insert(node->children.begin() + i + 1, split.newNode);

                // 4. Check for internal node overflow
                if ((int)node->keys.size() == m) {
                    Node* sibling = new Node(false);
                    int splitIndex = m / 2;
                    int promoted = node->keys[splitIndex];

                    // Move the right half of keys AND children to the sibling
                    sibling->keys.assign(node->keys.begin() + splitIndex + 1, node->keys.end());
                    sibling->children.assign(node->children.begin() + splitIndex + 1, node->children.end());

                    // Erase moved elements from the current node
                    node->keys.erase(node->keys.begin() + splitIndex, node->keys.end());
                    node->children.erase(node->children.begin() + splitIndex + 1, node->children.end());

                    // For an internal node, we MOVE the middle key up (it is removed from both)
                    return SplitResult(promoted, sibling);
                }
            }
            return SplitResult();
        }
    }

    // ─────────────────── Height Helper ───────────────────

    int getHeight(Node* node) const {
        if (node == nullptr) return 0;
        if (node->isLeaf) return 1;
        return 1 + getHeight(node->children[0]); // B+ Trees are perfectly balanced
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

public:

    // Initialize with order m (e.g., m=4 means max 4 children, 3 keys per node)
    BPlusTree(int order = 4) : root(nullptr), m(order) {
        if (m < 3) m = 3; 
    }

    ~BPlusTree() {
        destroy(root);
    }

    BPlusTree(const BPlusTree&) = delete;
    BPlusTree& operator=(const BPlusTree&) = delete;

    // ─────────────────── Mutators ───────────────────

    void insert(int value) {
        if (root == nullptr) {
            root = new Node(true);
            root->keys.push_back(value);
            return;
        }

        SplitResult split = insertInternal(root, value);

        // If the root node split, we must grow the tree upwards
        if (split.newNode != nullptr) {
            Node* newRoot = new Node(false);
            newRoot->keys.push_back(split.promotedKey);
            newRoot->children.push_back(root);
            newRoot->children.push_back(split.newNode);
            root = newRoot;
        }
    }

    void remove(int value) {
        Node* leaf = findLeaf(root, value);
        if (leaf == nullptr) return;

        auto it = find(leaf->keys.begin(), leaf->keys.end(), value);
        if (it != leaf->keys.end()) {
            leaf->keys.erase(it);
            // Note: Implementing Lazy Deletion here.
            // In a strict academic implementation, we would check for underflow 
            // (< ceil(m/2)-1 keys) and execute complex borrow/merge logic. 
            // In practice, systems like InnoDB allow nodes to temporarily underflow 
            // to optimize write performance and prevent thrashing.
        }
    }

    void clear() {
        destroy(root);
        root = nullptr;
    }

    // ─────────────────── Queries ───────────────────

    [[nodiscard]] bool search(int value) const {
        Node* leaf = findLeaf(root, value);
        if (leaf == nullptr) return false;

        return find(leaf->keys.begin(), leaf->keys.end(), value) != leaf->keys.end();
    }

    [[nodiscard]] optional<int> getMin() const {
        if (root == nullptr) return nullopt;
        Node* curr = root;
        while (!curr->isLeaf) curr = curr->children.front();
        return curr->keys.front();
    }

    [[nodiscard]] optional<int> getMax() const {
        if (root == nullptr) return nullopt;
        Node* curr = root;
        while (!curr->isLeaf) curr = curr->children.back();
        return curr->keys.back();
    }

    [[nodiscard]] int height() const { return getHeight(root); }
    [[nodiscard]] bool isEmpty() const { return root == nullptr; }

    // ─────────────────── Traversals ───────────────────

    // The primary advantage of a B+ Tree: ultra-fast sequential iteration
    void printLeaves() const {
        if (root == nullptr) return;

        // 1. Traverse down the left-most spine to find the first leaf
        Node* curr = root;
        while (!curr->isLeaf) {
            curr = curr->children.front();
        }

        // 2. Iterate through the linked list
        cout << "Linked Leaves: ";
        while (curr != nullptr) {
            cout << "[ ";
            for (int key : curr->keys) {
                cout << key << " ";
            }
            cout << "] -> ";
            curr = curr->next;
        }
        cout << "NULL\n";
    }

    void levelOrder() const {
        if (root == nullptr) return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            
            while (levelSize > 0) {
                Node* current = q.front();
                q.pop();

                cout << (current->isLeaf ? "L:" : "I:");
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
            cout << "\n";
        }
    }
};

int main() {
    cout << "================= B+ Tree (order 4) =================\n";
    // Initialize a B+ Tree of order 4
    // Max 4 children per internal node, max 3 keys per node.
    BPlusTree bpt(4);

    bpt.insert(10);
    bpt.insert(20);
    bpt.insert(30);
    bpt.insert(40);
    bpt.insert(50);
    bpt.insert(60);
    bpt.insert(70);
    bpt.insert(80);
    bpt.insert(90);
    bpt.insert(100);

    cout << "Level Order Traversal (I=Internal, L=Leaf): \n";
    bpt.levelOrder();
    
    cout << "\nSequential Leaf Traversal:\n";
    bpt.printLeaves();

    cout << "\nMinimum:     " << bpt.getMin().value_or(-1) << "\n";
    cout << "Maximum:     " << bpt.getMax().value_or(-1) << "\n";
    cout << "Height:      " << bpt.height()       << "\n";

    cout << "\nSearch 60:   " << (bpt.search(60)  ? "Found" : "Not Found") << "\n";
    cout << "Search 150:  " << (bpt.search(150) ? "Found" : "Not Found") << "\n";

    bpt.remove(20);
    bpt.remove(70);
    cout << "\nAfter lazy-deleting 20 and 70 (Leaves updated, routing keys untouched):\n";
    bpt.printLeaves();
    bpt.levelOrder();

    cout << "\n=====================================================\n";
    return 0;
}
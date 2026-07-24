#include <iostream>
#include <queue>
#include <optional>
#include <algorithm>
#include <random>

using namespace std;

class Treap {

private:

    // ─────────────────── Node ───────────────────

    struct Node {
        int data;
        int priority;
        Node* left;
        Node* right;

        Node(int value, int prio) 
            : data(value), priority(prio), left(nullptr), right(nullptr) {}
    };

    Node* root;
    mt19937 rng; // Standard Mersenne Twister for generating priorities

    // ─────────────────── Rotations ───────────────────

    // Rotations in a Treap are remarkably simple when using pointer references.
    // By passing 'y' as Node*&, modifying 'y' directly updates the parent's 
    // left/right pointer or the root pointer, eliminating the need for 'parent' pointers.
    void rightRotate(Node*& y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        y = x; // x becomes the new root of this subtree
    }

    void leftRotate(Node*& x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        x = y; // y becomes the new root of this subtree
    }

    // ─────────────────── Insert ───────────────────

    void insertNode(Node*& node, int value, int priority) {
        if (node == nullptr) {
            node = new Node(value, priority);
            return;
        }

        // Standard BST Insertion
        if (value < node->data) {
            insertNode(node->left, value, priority);
            
            // Restore Max-Heap property for priority
            if (node->left->priority > node->priority) {
                rightRotate(node);
            }
        } 
        else if (value > node->data) {
            insertNode(node->right, value, priority);
            
            // Restore Max-Heap property for priority
            if (node->right->priority > node->priority) {
                leftRotate(node);
            }
        }
        // Duplicate keys are silently ignored
    }

    // ─────────────────── Delete ───────────────────

    void deleteNode(Node*& node, int value) {
        if (node == nullptr) return; // Key not found

        if (value < node->data) {
            deleteNode(node->left, value);
        } 
        else if (value > node->data) {
            deleteNode(node->right, value);
        } 
        else {
            // Node found
            
            // Case 1: Leaf node or single child
            if (node->left == nullptr) {
                Node* temp = node;
                node = node->right; // Automatically updates parent due to Node*&
                delete temp;
            } 
            else if (node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp;
            } 
            // Case 2: Node has two children
            else {
                // Rotate the child with the higher priority upwards, pushing 
                // the target node downwards until it becomes a single-child or leaf node.
                if (node->left->priority > node->right->priority) {
                    rightRotate(node);
                    deleteNode(node->right, value); // Node is now the right child
                } 
                else {
                    leftRotate(node);
                    deleteNode(node->left, value);  // Node is now the left child
                }
            }
        }
    }

    // ─────────────────── Search ───────────────────

    Node* searchNode(Node* node, int value) const {
        while (node != nullptr) {
            if (value == node->data) return node;
            if (value < node->data) node = node->left;
            else node = node->right;
        }
        return nullptr;
    }

    // ─────────────────── Minimum / Maximum ───────────────────

    Node* findMin(Node* node) const {
        if (!node) return nullptr;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* findMax(Node* node) const {
        if (!node) return nullptr;
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    // ─────────────────── Count / Height ───────────────────

    int getHeight(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int count(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + count(node->left) + count(node->right);
    }

    // ─────────────────── Validation ───────────────────

    bool verifyNode(Node* node) const {
        if (node == nullptr) return true;

        // Verify Max-Heap property
        if (node->left && node->left->priority > node->priority) return false;
        if (node->right && node->right->priority > node->priority) return false;

        // Verify BST property
        if (node->left && findMax(node->left)->data >= node->data) return false;
        if (node->right && findMin(node->right)->data <= node->data) return false;

        return verifyNode(node->left) && verifyNode(node->right);
    }

    // ─────────────────── Destroy ───────────────────

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    // ─────────────────── Traversals ───────────────────

    void inorder(Node* node) const {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:

    Treap() : root(nullptr) {
        // Initialize RNG with a random seed
        random_device rd;
        rng.seed(rd());
    }

    ~Treap() {
        destroy(root);
    }

    Treap(const Treap&) = delete;
    Treap& operator=(const Treap&) = delete;

    // ─────────────────── Mutators ───────────────────

    void insert(int value) {
        // Generate a random priority between 1 and 1,000,000
        uniform_int_distribution<int> dist(1, 1000000);
        insertNode(root, value, dist(rng));
    }

    void remove(int value) { 
        deleteNode(root, value); 
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
        return minNode ? optional<int>(minNode->data) : nullopt;
    }

    [[nodiscard]] optional<int> getMax() const {
        Node* maxNode = findMax(root);
        return maxNode ? optional<int>(maxNode->data) : nullopt;
    }

    [[nodiscard]] int height() const { return getHeight(root); }
    [[nodiscard]] int size()   const { return count(root); }
    [[nodiscard]] bool isEmpty() const { return root == nullptr; }

    [[nodiscard]] bool isValid() const { return verifyNode(root); }

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
            Node* current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
        cout << "\n";
    }

    // Displays both the BST Key and the Max-Heap Priority [Key:Priority]
    void levelOrderWithPriority() const {
        if (root == nullptr) return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            
            while (levelSize > 0) {
                Node* current = q.front();
                q.pop();

                cout << "[" << current->data << ":" << current->priority << "] ";

                if (current->left != nullptr) q.push(current->left);
                if (current->right != nullptr) q.push(current->right);
                levelSize--;
            }
            cout << "\n";
        }
    }
};

int main() {
    cout << "================ Treap (BST + Max-Heap) ================\n";

    Treap treap;

    treap.insert(50);
    treap.insert(30);
    treap.insert(70);
    treap.insert(20);
    treap.insert(40);
    treap.insert(60);
    treap.insert(80);
    treap.insert(10);
    treap.insert(25);
    treap.insert(35);
    treap.insert(45);

    cout << "Inorder (Keys must be sorted):      \n";
    treap.inorder();

    cout << "\nLevel Order (Keys only):            \n";
    treap.levelOrder();

    cout << "\nLevel Order [Key:Priority] (Verify Max-Heap layout):\n";
    treap.levelOrderWithPriority();

    cout << "\nMinimum:       " << treap.getMin().value_or(-1) << "\n";
    cout << "Maximum:       " << treap.getMax().value_or(-1) << "\n";
    cout << "Height:        " << treap.height()       << "\n";
    cout << "Size:          " << treap.size()         << "\n";
    cout << "Valid Treap:   " << (treap.isValid() ? "Yes" : "No") << "\n";

    cout << "\nSearch 60:   " << (treap.search(60)  ? "Found" : "Not Found") << "\n";
    cout << "Search 100:  " << (treap.search(100) ? "Found" : "Not Found") << "\n";

    treap.remove(20);
    cout << "\nAfter deleting 20:\n";
    treap.levelOrderWithPriority();
    cout << "Valid Treap: " << (treap.isValid() ? "Yes" : "No") << "\n";

    treap.remove(30);
    cout << "\nAfter deleting 30:\n";
    treap.levelOrderWithPriority();
    cout << "Valid Treap: " << (treap.isValid() ? "Yes" : "No") << "\n";

    treap.remove(50);
    cout << "\nAfter deleting 50 (Root/Internal shift):\n";
    treap.levelOrderWithPriority();
    cout << "Valid Treap: " << (treap.isValid() ? "Yes" : "No") << "\n";

    cout << "\nFinal Height:        " << treap.height()       << "\n";
    cout << "Final Size:          " << treap.size()         << "\n";

    cout << "\n=========================================================\n";
    return 0;
}
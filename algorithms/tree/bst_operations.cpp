#include <iostream>
#include <queue>
using namespace std;

class BST {
private:

    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int value) {
            data = value;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root = nullptr;

    // ----------------------------------------------------------
    // Insert
    // ----------------------------------------------------------
    Node* insert(Node* node, int value) {

        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);

        return node;
    }

    // ----------------------------------------------------------
    // Search
    // ----------------------------------------------------------
    bool search(Node* node, int value) {

        if (node == nullptr)
            return false;

        if (node->data == value)
            return true;

        if (value < node->data)
            return search(node->left, value);

        return search(node->right, value);
    }

    // ----------------------------------------------------------
    // Minimum Node
    // ----------------------------------------------------------
    Node* findMin(Node* node) {

        while (node && node->left)
            node = node->left;

        return node;
    }

    // ----------------------------------------------------------
    // Maximum Node
    // ----------------------------------------------------------
    Node* findMax(Node* node) {

        while (node && node->right)
            node = node->right;

        return node;
    }

    // ----------------------------------------------------------
    // Delete
    // ----------------------------------------------------------
    Node* remove(Node* node, int value) {

        if (node == nullptr)
            return nullptr;

        if (value < node->data)
            node->left = remove(node->left, value);

        else if (value > node->data)
            node->right = remove(node->right, value);

        else {

            // No child
            if (node->left == nullptr &&
                node->right == nullptr) {

                delete node;
                return nullptr;
            }

            // One child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Two children
            Node* successor = findMin(node->right);

            node->data = successor->data;

            node->right =
                remove(node->right, successor->data);
        }

        return node;
    }

    // ----------------------------------------------------------
    // Traversals
    // ----------------------------------------------------------
    void inorder(Node* node) {

        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {

        if (node == nullptr)
            return;

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {

        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    // ----------------------------------------------------------
    // Height
    // ----------------------------------------------------------
    int height(Node* node) {

        if (node == nullptr)
            return 0;

        return 1 + max(height(node->left),
                       height(node->right));
    }

    // ----------------------------------------------------------
    // Count Nodes
    // ----------------------------------------------------------
    int countNodes(Node* node) {

        if (node == nullptr)
            return 0;

        return 1 +
               countNodes(node->left) +
               countNodes(node->right);
    }

    // ----------------------------------------------------------
    // Free every node (post-order) — used by the destructor
    // so the demo never leaks.
    // ----------------------------------------------------------
    void freeTree(Node* node) {
        if (node == nullptr)
            return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

public:

    ~BST() { freeTree(root); }

    // ----------------------------------------------------------
    // Public APIs
    // ----------------------------------------------------------
    void insert(int value) {
        root = insert(root, value);
    }

    void remove(int value) {
        root = remove(root, value);
    }

    bool search(int value) {
        return search(root, value);
    }

    int minimum() {
        Node* node = findMin(root);
        return node ? node->data : -1;
    }

    int maximum() {
        Node* node = findMax(root);
        return node ? node->data : -1;
    }

    int height() {
        return height(root);
    }

    int size() {
        return countNodes(root);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    void preorder() {
        preorder(root);
        cout << endl;
    }

    void postorder() {
        postorder(root);
        cout << endl;
    }

    void levelOrder() {

        if (root == nullptr)
            return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {

            Node* current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left)
                q.push(current->left);

            if (current->right)
                q.push(current->right);
        }

        cout << endl;
    }
};

int main() {

    cout << "================ Binary Search Tree Operations ================\n";

    // ─── [Complexity] ───
    cout << "\n[Complexity]\n";
    cout << "Time:\n";
    cout << "  insert / search / remove : O(h) average, h = tree height\n";
    cout << "  balanced (random input)  : O(log n)\n";
    cout << "  worst (sorted input)     : O(n)  — degrades to a linked list\n";
    cout << "  traversals (in/pre/post) : O(n)\n";
    cout << "Space:\n";
    cout << "  O(n) for the nodes + O(h) recursion stack per operation\n";
    cout << "Notes:\n";
    cout << "  Maintains the BST invariant: left < node < right, so an inorder\n";
    cout << "  walk yields keys in ascending order. This BST does NOT self-balance;\n";
    cout << "  insertion order shapes the tree. For guaranteed O(log n), see\n";
    cout << "  avl_rotations.cpp and red_black_rotations.cpp.\n";

    // ─── [Build / Demo] ───
    BST tree;

    int values[] = {
        50, 30, 70, 20, 40,
        60, 80, 10, 25, 35, 45
    };
    int n = (int)(sizeof(values) / sizeof(values[0]));

    cout << "\n[Demo] Insert sequence: ";
    for (int i = 0; i < n; i++) cout << values[i] << " ";
    cout << "\n";

    for (int i = 0; i < n; i++)
        tree.insert(values[i]);

    cout << "\nInorder  (sorted ascending): ";
    tree.inorder();

    cout << "Preorder (root-first shape) : ";
    tree.preorder();

    cout << "Postorder                   : ";
    tree.postorder();

    cout << "Level order                 : ";
    tree.levelOrder();

    // ─── [Stats] ───
    cout << "[Stats]\n";
    cout << "  Size    : " << tree.size() << "\n";
    cout << "  Height  : " << tree.height() << "\n";
    cout << "  Minimum : " << tree.minimum() << "\n";
    cout << "  Maximum : " << tree.maximum() << "\n";

    // ─── [Searches] ───
    cout << "\n[Searches]\n";
    cout << "  search(60) : " << (tree.search(60) ? "Found" : "Not Found") << "\n";
    cout << "  search(100): " << (tree.search(100) ? "Found" : "Not Found")
         << "  (missing key)\n";

    // ─── [Delete] ───
    // 30 is an internal node with TWO children — exercises the
    // in-order successor splice path of remove().
    cout << "\n[Delete] Remove 30 (a node with two children).\n";
    cout << "  Before: ";
    tree.inorder();
    tree.remove(30);
    cout << "  After : ";
    tree.inorder();

    cout << "\n[Delete] Remove 50 (root, two children).\n";
    cout << "  Before: ";
    tree.inorder();
    tree.remove(50);
    cout << "  After : ";
    tree.inorder();

    // ─── [Edge Cases] ───
    cout << "\n[Edge Cases]\n";

    cout << "  Insert duplicate 70 (rejected — BST keeps unique keys):\n";
    cout << "    Before: ";
    tree.inorder();
    tree.insert(70);
    cout << "    After : ";
    tree.inorder();

    cout << "  Search missing key 999: "
         << (tree.search(999) ? "Found" : "Not Found") << "\n";

    cout << "  Remove a key not present (999) — tree unchanged:\n";
    cout << "    Before: ";
    tree.inorder();
    tree.remove(999);
    cout << "    After : ";
    tree.inorder();

    cout << "  Empty tree operations:\n";
    BST empty;
    cout << "    inorder of empty tree : "; empty.inorder();
    cout << "    search(1) on empty    : "
         << (empty.search(1) ? "Found" : "Not Found") << "\n";
    cout << "    minimum() on empty    : " << empty.minimum()
         << "  (-1 = sentinel for 'empty')\n";
    cout << "    size() on empty       : " << empty.size() << "\n";

    cout << "\nInorder still sorted ascending after all mutations.\n";

    return 0;
}
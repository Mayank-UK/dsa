#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

class AVLTree {
private:

    struct Node {
        int data;
        int height;
        Node* left;
        Node* right;

        Node(int value) {
            data = value;
            height = 1;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root = nullptr;

    // ----------------------------------------------------------
    // Height
    // ----------------------------------------------------------
    int height(Node* node) {
        return node ? node->height : 0;
    }

    // ----------------------------------------------------------
    // Balance Factor
    // ----------------------------------------------------------
    int balanceFactor(Node* node) {
        if (node == nullptr)
            return 0;

        return height(node->left) - height(node->right);
    }

    // ----------------------------------------------------------
    // Update Height
    // ----------------------------------------------------------
    void updateHeight(Node* node) {
        node->height = 1 +
            max(height(node->left), height(node->right));
    }

    // ----------------------------------------------------------
    // Right Rotation (LL Case)
    // ----------------------------------------------------------
    Node* rightRotate(Node* y) {

        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // ----------------------------------------------------------
    // Left Rotation (RR Case)
    // ----------------------------------------------------------
    Node* leftRotate(Node* x) {

        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // ----------------------------------------------------------
    // Insert
    // ----------------------------------------------------------
    Node* insert(Node* node, int key) {

        // Normal BST Insertion
        if (node == nullptr)
            return new Node(key);

        if (key < node->data)
            node->left = insert(node->left, key);

        else if (key > node->data)
            node->right = insert(node->right, key);

        else
            return node;    // Duplicate

        // Update height
        updateHeight(node);

        // Balance factor
        int balance = balanceFactor(node);

        // ---------------- LL ----------------
        if (balance > 1 &&
            key < node->left->data)
            return rightRotate(node);

        // ---------------- RR ----------------
        if (balance < -1 &&
            key > node->right->data)
            return leftRotate(node);

        // ---------------- LR ----------------
        if (balance > 1 &&
            key > node->left->data) {

            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // ---------------- RL ----------------
        if (balance < -1 &&
            key < node->right->data) {

            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // ----------------------------------------------------------
    // Find Minimum Node
    // ----------------------------------------------------------
    Node* minValueNode(Node* node) {

        Node* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    // ----------------------------------------------------------
    // Delete
    // ----------------------------------------------------------
    Node* deleteNode(Node* node, int key) {

        if (node == nullptr)
            return nullptr;

        // BST Delete
        if (key < node->data)
            node->left = deleteNode(node->left, key);

        else if (key > node->data)
            node->right = deleteNode(node->right, key);

        else {

            // One or Zero Child
            if (node->left == nullptr ||
                node->right == nullptr) {

                Node* temp =
                    node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;

                delete temp;
            }
            else {

                // Two Children
                Node* temp =
                    minValueNode(node->right);

                node->data = temp->data;

                node->right =
                    deleteNode(node->right,
                               temp->data);
            }
        }

        if (node == nullptr)
            return nullptr;

        updateHeight(node);

        int balance = balanceFactor(node);

        // LL
        if (balance > 1 &&
            balanceFactor(node->left) >= 0)
            return rightRotate(node);

        // LR
        if (balance > 1 &&
            balanceFactor(node->left) < 0) {

            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RR
        if (balance < -1 &&
            balanceFactor(node->right) <= 0)
            return leftRotate(node);

        // RL
        if (balance < -1 &&
            balanceFactor(node->right) > 0) {

            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // ----------------------------------------------------------
    // Search
    // ----------------------------------------------------------
    bool search(Node* node, int key) {

        if (node == nullptr)
            return false;

        if (node->data == key)
            return true;

        if (key < node->data)
            return search(node->left, key);

        return search(node->right, key);
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

    // Print inorder AND each node's balance factor, so the balancing
    // work the rotations do is visible rather than hidden in heights.
    void inorderWithBalance(Node* node) {
        if (node == nullptr)
            return;
        inorderWithBalance(node->left);
        cout << "    " << node->data
             << "  (h=" << node->height
             << ", bf=" << balanceFactor(node) << ")\n";
        inorderWithBalance(node->right);
    }

    // Pretty structural print (sideways) — sibling nodes share an indent.
    void printStructure(Node* node, const string& indent, bool isLeft) {
        if (node == nullptr)
            return;
        cout << indent;
        cout << (isLeft ? "L── " : "R── ") << node->data << "\n";
        printStructure(node->left, indent + "    ", true);
        printStructure(node->right, indent + "    ", false);
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

    ~AVLTree() { freeTree(root); }

    // ----------------------------------------------------------
    // Public APIs
    // ----------------------------------------------------------
    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    bool search(int key) {
        return search(root, key);
    }

    int height() {
        return height(root);
    }

    bool isBalanced() {
        return isBalanced(root);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    void inorderWithBalance() {
        inorderWithBalance(root);
    }

    void preorder() {
        preorder(root);
        cout << endl;
    }

    void postorder() {
        postorder(root);
        cout << endl;
    }

    void printStructure() {
        if (root == nullptr) {
            cout << "    (empty)\n";
            return;
        }
        cout << "    root: " << root->data << "\n";
        printStructure(root->left, "    ", true);
        printStructure(root->right, "    ", false);
    }

private:
    // Verify the AVL invariant holds at every node: |bf| <= 1.
    bool isBalanced(Node* node) {
        if (node == nullptr)
            return true;
        int bf = balanceFactor(node);
        if (bf < -1 || bf > 1)
            return false;
        return isBalanced(node->left) && isBalanced(node->right);
    }
};

int main() {

    cout << "========================= AVL Tree Rotations =========================\n";

    // ─── [Complexity] ───
    cout << "\n[Complexity]\n";
    cout << "Time:\n";
    cout << "  insert / search / remove : O(log n)  — height is kept at log n\n";
    cout << "  traversals               : O(n)\n";
    cout << "Space:\n";
    cout << "  O(n) for the nodes + O(log n) recursion stack per operation\n";
    cout << "Notes:\n";
    cout << "  AVL is a self-balancing BST: every node stores a height and must keep\n";
    cout << "  |balanceFactor| <= 1, where bf = height(left) - height(right).\n";
    cout << "  Insert/delete rebalance via four rotation cases:\n";
    cout << "    LL -> single right rotate | LR -> left-rotate left child, then right\n";
    cout << "    RR -> single left rotate  | RL -> right-rotate right child, then left\n";
    cout << "  AVL is STRICTER than Red-Black (see red_black_rotations.cpp): it keeps\n";
    cout << "  the tree tighter (|bf|<=1) so it does MORE rotations but gives slightly\n";
    cout << "  faster lookups. RB trades a looser balance for fewer rotations.\n";

    // ─── [Demo] ───
    // Classic sequence {10,20,30,40,50,25} exercises every rotation case:
    //   10,20,30  -> RR at 10  (left rotate)        : 20 becomes root
    //   ...40,50  -> RR on the right spine          : keeps right side balanced
    //   25        -> LR under 30                    : double rotation
    AVLTree tree;

    int values[] = {10, 20, 30, 40, 50, 25};
    int n = (int)(sizeof(values) / sizeof(values[0]));

    cout << "\n[Demo] Insert sequence: ";
    for (int i = 0; i < n; i++) cout << values[i] << " ";
    cout << "(triggers RR and LR rotation cases)\n";

    for (int i = 0; i < n; i++)
        tree.insert(values[i]);

    cout << "\nInorder (must be sorted ascending): ";
    tree.inorder();

    cout << "\nPer-node height and balance factor (|bf| <= 1 everywhere):\n";
    tree.inorderWithBalance();

    cout << "\nTree structure (sideways view):\n";
    tree.printStructure();

    cout << "\nPreorder (root-first — shows the balanced shape): ";
    tree.preorder();

    // ─── [Balance Check] ───
    cout << "[Balance Check]\n";
    cout << "  Height of tree        : " << tree.height() << "\n";
    cout << "  Nodes inserted        : " << n << "\n";
    cout << "  log2(n) ~             : " << (int)(log2((double)n)) << "\n";
    cout << "  AVL invariant holds   : "
         << (tree.isBalanced() ? "Yes" : "No") << "\n";

    // ─── [Searches] ───
    cout << "\n[Searches]\n";
    cout << "  search(25) : " << (tree.search(25) ? "Found" : "Not Found") << "\n";
    cout << "  search(100): " << (tree.search(100) ? "Found" : "Not Found")
         << "  (missing key)\n";

    // ─── [Delete] ───
    cout << "\n[Delete] Remove 30 (internal node, triggers rebalance back up).\n";
    cout << "  Before: ";
    tree.inorder();
    tree.remove(30);
    cout << "  After : ";
    tree.inorder();
    cout << "  Still balanced after delete: "
         << (tree.isBalanced() ? "Yes" : "No") << "\n";

    // ─── [Edge Cases] ───
    cout << "\n[Edge Cases]\n";

    cout << "  Insert duplicate 20 (rejected — AVL keeps unique keys):\n";
    cout << "    Before: ";
    tree.inorder();
    tree.insert(20);
    cout << "    After : ";
    tree.inorder();

    cout << "  Search missing key 999: "
         << (tree.search(999) ? "Found" : "Not Found") << "\n";

    cout << "  Empty tree:\n";
    AVLTree empty;
    cout << "    inorder on empty  : ";
    empty.inorder();
    cout << "    search(1) on empty : "
         << (empty.search(1) ? "Found" : "Not Found") << "\n";
    cout << "    height() on empty  : " << empty.height() << "\n";
    cout << "    balanced on empty  : "
         << (empty.isBalanced() ? "Yes" : "No") << "\n";

    cout << "\nAVL keeps inorder sorted AND height ~ log n after every op.\n";

    return 0;
}
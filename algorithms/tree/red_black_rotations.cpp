// Red-Black Tree Implementation in C++
// Focus: Rotations and Fixup

#include <iostream>
#include <iomanip>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Red-Black Tree Class
class RBTree {
private:
    Node* root;
    Node* NIL;  // Sentinel node (black)

    // Left Rotation
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != NIL) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == NIL) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    // Right Rotation
    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != NIL) {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == NIL) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }

        x->right = y;
        y->parent = x;
    }

    // Fix violations after insertion
    void fixInsert(Node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {  // Parent is left child
                Node* uncle = z->parent->parent->right;

                if (uncle->color == RED) {  // Case 1: Uncle is RED
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {  // Case 2: Triangle (LR)
                        z = z->parent;
                        leftRotate(z);
                    }
                    // Case 3: Line (LL)
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {  // Parent is right child (symmetric)
                Node* uncle = z->parent->parent->left;

                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {  // Case 2: Triangle (RL)
                        z = z->parent;
                        rightRotate(z);
                    }
                    // Case 3: Line (RR)
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

public:
    RBTree() {
        NIL = new Node(0);
        NIL->color = BLACK;
        root = NIL;
    }

    ~RBTree() {
        freeTree(root);
        delete NIL;
    }

private:
    // Free every real node (post-order), stopping at the NIL sentinel.
    void freeTree(Node* node) {
        if (node == NIL)
            return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

public:

    // Insert
    void insert(int key) {
        Node* z = new Node(key);
        z->left = NIL;
        z->right = NIL;

        Node* y = NIL;
        Node* x = root;

        while (x != NIL) {
            y = x;
            if (key < x->data) {
                x = x->left;
            } else if (key > x->data) {
                x = x->right;
            } else {
                delete z;  // Duplicate not allowed
                return;
            }
        }

        z->parent = y;

        if (y == NIL) {
            root = z;
        } else if (key < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }

        fixInsert(z);
    }

    // Inorder traversal
    void inorderHelper(Node* node) {
        if (node != NIL) {
            inorderHelper(node->left);
            cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
            inorderHelper(node->right);
        }
    }

    void inorder() {
        inorderHelper(root);
        cout << endl;
    }

    // Print tree structure
    void printHelper(Node* node, string indent, bool last) {
        if (node != NIL) {
            cout << indent;
            if (last) {
                cout << "└── ";
                indent += "    ";
            } else {
                cout << "├── ";
                indent += "│   ";
            }
            cout << node->data << "(" << (node->color == RED ? "R" : "B") << ")\n";
            printHelper(node->left, indent, false);
            printHelper(node->right, indent, true);
        }
    }

    void printTree() {
        cout << "Red-Black Tree Structure:\n";
        printHelper(root, "", true);
    }

    // Standard BST-style lookup (uses parent/binary search; NIL-safe).
    bool search(int key) {
        Node* x = root;
        while (x != NIL) {
            if (key < x->data) x = x->left;
            else if (key > x->data) x = x->right;
            else return true;
        }
        return false;
    }

    bool isEmpty() {
        return root == NIL;
    }
};

// Main
int main() {
    cout << "===================== Red-Black Tree Rotations =====================\n";

    // ─── [Complexity] ───
    cout << "\n[Complexity]\n";
    cout << "Time:\n";
    cout << "  insert / search / remove : O(log n)  — height <= 2*log2(n+1)\n";
    cout << "Space:\n";
    cout << "  O(n) for nodes + O(log n) recursion/loop stack per operation\n";
    cout << "Notes:\n";
    cout << "  Self-balancing BST maintained by color flips + rotations after\n";
    cout << "  each insert (this demo covers insert fixup; delete is omitted).\n";
    cout << "  The five Red-Black properties enforced by fixInsert():\n";
    cout << "    1. Every node is either RED or BLACK.\n";
    cout << "    2. The root is BLACK.\n";
    cout << "    3. Every NIL leaf (sentinel) is BLACK.\n";
    cout << "    4. If a node is RED, both its children are BLACK (no two reds in a row).\n";
    cout << "    5. Every path from a node down to its descendant NIL leaves passes\n";
    cout << "       through the same number of BLACK nodes (the black-height).\n";
    cout << "  Red-Black is LOOSER than AVL (see avl_rotations.cpp): it allows a wider\n";
    cout << "  imbalance but does FEWER rotations on update. That tradeoff is why\n";
    cout << "  std::map / std::set are typically implemented as Red-Black trees.\n";

    // ─── [Demo] ───
    RBTree rbt;

    int values[] = {10, 20, 30, 15, 25, 5, 40, 35, 50};
    int n = (int)(sizeof(values) / sizeof(values[0]));

    cout << "\n[Demo] Insert sequence: ";
    for (int i = 0; i < n; i++) cout << values[i] << " ";
    cout << "\n";

    for (int i = 0; i < n; i++)
        rbt.insert(values[i]);

    cout << "\nInorder with colors (must be sorted ascending; colors shown as R/B):\n  ";
    rbt.inorder();

    cout << "\nTree structure (indented tree drawing; R = red, B = black):\n";
    rbt.printTree();

    // ─── [Searches] ───
    cout << "\n[Searches]\n";
    cout << "  search(25) : " << (rbt.search(25) ? "Found" : "Not Found") << "\n";
    cout << "  search(100): " << (rbt.search(100) ? "Found" : "Not Found")
         << "  (missing key)\n";

    // ─── [Edge Cases] ───
    cout << "\n[Edge Cases]\n";

    cout << "  Insert duplicate 20 (rejected — RBTree keeps unique keys):\n";
    cout << "    Before: ";
    rbt.inorder();
    rbt.insert(20);
    cout << "    After : ";
    rbt.inorder();

    cout << "  Search missing key 999: "
         << (rbt.search(999) ? "Found" : "Not Found") << "\n";

    cout << "  Empty tree:\n";
    RBTree empty;
    cout << "    inorder on empty   : ";
    empty.inorder();
    cout << "    search(1) on empty : "
         << (empty.search(1) ? "Found" : "Not Found") << "\n";
    cout << "    isEmpty() on empty : "
         << (empty.isEmpty() ? "Yes" : "No") << "\n";

    cout << "\nRed-Black keeps inorder sorted AND height O(log n) via properties 1-5.\n";

    return 0;
}
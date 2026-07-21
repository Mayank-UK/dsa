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
};

// Main
int main() {
    RBTree rbt;

    cout << "Red-Black Tree Demonstration\n\n";

    int values[] = {10, 20, 30, 15, 25, 5, 40, 35, 50};

    cout << "Inserting: ";
    for (int val : values) {
        cout << val << " ";
        rbt.insert(val);
    }
    cout << "\n\n";

    cout << "Inorder Traversal: ";
    rbt.inorder();
    cout << "\n";

    rbt.printTree();

    cout << "\nNote: Red-Black trees use rotations + recoloring for balancing.\n";
    cout << "Rotations happen less frequently than in AVL but properties are stricter.\n";

    return 0;
}
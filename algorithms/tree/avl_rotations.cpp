#include <iostream>
#include <algorithm>
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

public:

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
};

int main() {

    AVLTree tree;

    int values[] = {
        10,20,30,40,50,25,
        5,35,45,15
    };

    cout << "Insertion\n";

    for (int x : values)
        tree.insert(x);

    cout << "\nInorder:\n";
    tree.inorder();

    cout << "\nPreorder:\n";
    tree.preorder();

    cout << "\nPostorder:\n";
    tree.postorder();

    cout << "\nSearch 35 : "
         << (tree.search(35) ? "Found" : "Not Found")
         << endl;

    cout << "Search 100 : "
         << (tree.search(100) ? "Found" : "Not Found")
         << endl;

    cout << "\nDeleting 40...\n";
    tree.remove(40);

    cout << "Deleting 20...\n";
    tree.remove(20);

    cout << "\nInorder After Deletion:\n";
    tree.inorder();

    return 0;
}
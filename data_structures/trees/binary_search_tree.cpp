#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

class BinarySearchTree {

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

    Node* root;

    // ---------------- Insert ----------------

    Node* insert(Node* node, int value) {

        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);

        return node;
    }

    // ---------------- Search ----------------

    bool search(Node* node, int value) {

        if (node == nullptr)
            return false;

        if (node->data == value)
            return true;

        if (value < node->data)
            return search(node->left, value);

        return search(node->right, value);
    }

    // ---------------- Find Minimum ----------------

    Node* findMin(Node* node) {

        while (node->left != nullptr)
            node = node->left;

        return node;
    }

    // ---------------- Find Maximum ----------------

    Node* findMax(Node* node) {

        while (node->right != nullptr)
            node = node->right;

        return node;
    }

    // ---------------- Delete ----------------

    Node* remove(Node* node, int value) {

        if (node == nullptr)
            return nullptr;

        if (value < node->data) {

            node->left = remove(node->left, value);

        } else if (value > node->data) {

            node->right = remove(node->right, value);

        } else {

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

            node->right = remove(node->right, successor->data);
        }

        return node;
    }

    // ---------------- Traversals ----------------

    void preorder(Node* node) {

        if (node == nullptr)
            return;

        cout << node->data << " ";

        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node* node) {

        if (node == nullptr)
            return;

        inorder(node->left);

        cout << node->data << " ";

        inorder(node->right);
    }

    void postorder(Node* node) {

        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);

        cout << node->data << " ";
    }

    // ---------------- Height ----------------

    int height(Node* node) {

        if (node == nullptr)
            return 0;

        return 1 + std::max(height(node->left), height(node->right));
    }

    // ---------------- Count ----------------

    int count(Node* node) {

        if (node == nullptr)
            return 0;

        return 1 + count(node->left) + count(node->right);
    }

    // ---------------- Destructor ----------------

    void destroy(Node* node) {

        if (node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);

        delete node;
    }

public:

    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int value) {
        root = insert(root, value);
    }

    bool search(int value) {
        return search(root, value);
    }

    void remove(int value) {
        root = remove(root, value);
    }

    void preorder() {
        preorder(root);
        cout << endl;
    }

    void inorder() {
        inorder(root);
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

    int getMin() {

        if (root == nullptr)
            return -1;

        return findMin(root)->data;
    }

    int getMax() {

        if (root == nullptr)
            return -1;

        return findMax(root)->data;
    }

    int height() {
        return height(root);
    }

    int size() {
        return count(root);
    }

    ~BinarySearchTree() {
        destroy(root);
    }
};

int main() {

    cout << "============= Binary Search Tree =============\n";

    BinarySearchTree bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    cout << "Inorder: ";
    bst.inorder();

    cout << "Preorder: ";
    bst.preorder();

    cout << "Postorder: ";
    bst.postorder();

    cout << "Level Order: ";
    bst.levelOrder();

    cout << "\nMinimum: " << bst.getMin() << endl;
    cout << "Maximum: " << bst.getMax() << endl;

    cout << "Height: " << bst.height() << endl;
    cout << "Size: " << bst.size() << endl;

    cout << "\nSearch 60: " << (bst.search(60) ? "Found" : "Not Found") << endl;
    cout << "Search 100: " << (bst.search(100) ? "Found" : "Not Found") << endl;

    bst.remove(20);

    cout << "\nAfter deleting 20\n";
    bst.inorder();

    bst.remove(30);

    cout << "\nAfter deleting 30\n";
    bst.inorder();

    bst.remove(50);

    cout << "\nAfter deleting 50\n";
    bst.inorder();

    cout << "\n==============================================\n";
    return 0;
}
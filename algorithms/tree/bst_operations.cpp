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

public:

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

    BST tree;

    int values[] = {
        50,30,70,20,40,
        60,80,10,25,35,45
    };

    for (int x : values)
        tree.insert(x);

    cout << "Inorder: ";
    tree.inorder();

    cout << "Preorder: ";
    tree.preorder();

    cout << "Postorder: ";
    tree.postorder();

    cout << "Level Order: ";
    tree.levelOrder();

    cout << "\nMinimum: "
         << tree.minimum() << endl;

    cout << "Maximum: "
         << tree.maximum() << endl;

    cout << "Height: "
         << tree.height() << endl;

    cout << "Size: "
         << tree.size() << endl;

    cout << "\nSearch 60: "
         << (tree.search(60) ? "Found" : "Not Found")
         << endl;

    cout << "Search 100: "
         << (tree.search(100) ? "Found" : "Not Found")
         << endl;

    cout << "\nDelete 20\n";
    tree.remove(20);

    cout << "Delete 30\n";
    tree.remove(30);

    cout << "Delete 50\n";
    tree.remove(50);

    cout << "\nInorder After Deletion:\n";
    tree.inorder();

    return 0;
}
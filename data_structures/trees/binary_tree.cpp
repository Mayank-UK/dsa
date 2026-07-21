#include <iostream>
#include <queue>

using namespace std;

class BinaryTree {
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

    // ---------------- Search ----------------

    bool search(Node* node, int value) {
        if (node == nullptr)
            return false;

        if (node->data == value)
            return true;

        return search(node->left, value) || search(node->right, value);
    }

    // ---------------- Count ----------------

    int countNodes(Node* node) {
        if (node == nullptr)
            return 0;

        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int countLeaves(Node* node) {
        if (node == nullptr)
            return 0;

        if (node->left == nullptr &&
            node->right == nullptr)
            return 1;

        return countLeaves(node->left) + countLeaves(node->right);
    }

    int countInternal(Node* node) {
        if (node == nullptr)
            return 0;

        if (node->left == nullptr &&
            node->right == nullptr)
            return 0;

        return 1 + countInternal(node->left) + countInternal(node->right);
    }

    // ---------------- Height ----------------

    int height(Node* node) {
        if (node == nullptr)
            return 0;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return 1 + max(leftHeight, rightHeight);
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
    BinaryTree() {
        root = nullptr;
    }

    // Build a sample tree
    void createTree() {

        root = new Node(10);

        root->left = new Node(20);
        root->right = new Node(30);

        root->left->left = new Node(40);
        root->left->right = new Node(50);

        root->right->left = new Node(60);
        root->right->right = new Node(70);
    }

    // ---------------- Public wrappers ----------------

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

    bool search(int value) {
        return search(root, value);
    }

    int countNodes() {
        return countNodes(root);
    }

    int countLeaves() {
        return countLeaves(root);
    }

    int countInternalNodes() {
        return countInternal(root);
    }

    int height() {
        return height(root);
    }

    ~BinaryTree() {
        destroy(root);
    }
};

int main() {

    BinaryTree tree;

    tree.createTree();

    cout << "Preorder: ";
    tree.preorder();

    cout << "Inorder: ";
    tree.inorder();

    cout << "Postorder: ";
    tree.postorder();

    cout << "Level Order: ";
    tree.levelOrder();

    cout << "\nTotal Nodes: " << tree.countNodes() << endl;

    cout << "Leaf Nodes: " << tree.countLeaves() << endl;

    cout << "Internal Nodes: " << tree.countInternalNodes() << endl;

    cout << "Height: " << tree.height() << endl;

    cout << "\nSearch 50: " << (tree.search(50) ? "Found" : "Not Found") << endl;

    cout << "Search 100: " << (tree.search(100) ? "Found" : "Not Found") << endl;

    return 0;
}
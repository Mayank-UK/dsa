#include <iostream>
#include <queue>
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

    Node* root;

    // ---------------- Height ----------------

    int getHeight(Node* node) {

        if (node == nullptr)
            return 0;

        return node->height;
    }

    // ---------------- Balance Factor ----------------

    int getBalance(Node* node) {

        if (node == nullptr)
            return 0;

        return getHeight(node->left) - getHeight(node->right);
    }

    // ---------------- Update Height ----------------

    void updateHeight(Node* node) {

        if (node == nullptr)
            return;

        node->height =
            1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    // ---------------- Right Rotation ----------------

    Node* rightRotate(Node* y) {

        Node* x = y->left;
        Node* t2 = x->right;

        x->right = y;
        y->left = t2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // ---------------- Left Rotation ----------------

    Node* leftRotate(Node* x) {

        Node* y = x->right;
        Node* t2 = y->left;

        y->left = x;
        x->right = t2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // ---------------- Insert ----------------

    Node* insert(Node* node, int value) {

        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);

        else if (value > node->data)
            node->right = insert(node->right, value);

        else
            return node;

        updateHeight(node);

        int balance = getBalance(node);

        // LL
        if (balance > 1 &&
            value < node->left->data)
            return rightRotate(node);

        // RR
        if (balance < -1 &&
            value > node->right->data)
            return leftRotate(node);

        // LR
        if (balance > 1 &&
            value > node->left->data) {

            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if (balance < -1 &&
            value < node->right->data) {

            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

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

    // ---------------- Minimum ----------------

    Node* findMin(Node* node) {

        while (node->left)
            node = node->left;

        return node;
    }

    // ---------------- Maximum ----------------

    Node* findMax(Node* node) {

        while (node->right)
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

            if (node->left == nullptr &&
                node->right == nullptr) {

                delete node;
                return nullptr;
            }

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

            Node* successor = findMin(node->right);

            node->data = successor->data;

            node->right =
                remove(node->right, successor->data);
        }

        updateHeight(node);

        int balance = getBalance(node);

        // LL

        if (balance > 1 &&
            getBalance(node->left) >= 0)
            return rightRotate(node);

        // LR

        if (balance > 1 &&
            getBalance(node->left) < 0) {

            node->left =
                leftRotate(node->left);

            return rightRotate(node);
        }

        // RR

        if (balance < -1 &&
            getBalance(node->right) <= 0)
            return leftRotate(node);

        // RL

        if (balance < -1 &&
            getBalance(node->right) > 0) {

            node->right =
                rightRotate(node->right);

            return leftRotate(node);
        }

        return node;
    }

    // ---------------- Traversals ----------------

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

    AVLTree() {
        root = nullptr;
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void remove(int value) {
        root = remove(root, value);
    }

    bool search(int value) {
        return search(root, value);
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
        return getHeight(root);
    }

    int size() {
        return count(root);
    }

    ~AVLTree() {
        destroy(root);
    }

};

int main() {

    AVLTree avl;

    avl.insert(50);
    avl.insert(30);
    avl.insert(70);
    avl.insert(20);
    avl.insert(40);
    avl.insert(60);
    avl.insert(80);
    avl.insert(10);
    avl.insert(25);
    avl.insert(35);
    avl.insert(45);

    cout << "Inorder: ";
    avl.inorder();

    cout << "Preorder: ";
    avl.preorder();

    cout << "Postorder: ";
    avl.postorder();

    cout << "Level Order: ";
    avl.levelOrder();

    cout << "\nMinimum: " << avl.getMin() << endl;
    cout << "Maximum: " << avl.getMax() << endl;

    cout << "Height: " << avl.height() << endl;
    cout << "Size: " << avl.size() << endl;

    cout << "\nSearch 60: " << (avl.search(60) ? "Found" : "Not Found") << endl;

    cout << "Search 100: " << (avl.search(100) ? "Found" : "Not Found") << endl;

    avl.remove(20);

    cout << "\nAfter deleting 20\n";
    avl.inorder();

    avl.remove(30);

    cout << "\nAfter deleting 30\n";
    avl.inorder();

    avl.remove(50);

    cout << "\nAfter deleting 50\n";
    avl.inorder();

    cout << "\nFinal Level Order: ";
    avl.levelOrder();

    cout << "Final Height: " << avl.height() << endl;

    cout << "Final Size: " << avl.size() << endl;

    return 0;
}
#include <iostream>
using namespace std;

class BinaryTree {
private:

    // ----------------------------------------------------------
    // Node
    // ----------------------------------------------------------
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

    // ----------------------------------------------------------
    // Lowest Common Ancestor
    // Time: O(n)
    // ----------------------------------------------------------
    Node* lowestCommonAncestor(Node* node,
                               int p,
                               int q) {

        if (node == nullptr)
            return nullptr;

        // One of the nodes found
        if (node->data == p || node->data == q)
            return node;

        Node* left =
            lowestCommonAncestor(node->left, p, q);

        Node* right =
            lowestCommonAncestor(node->right, p, q);

        // One node in each subtree
        if (left && right)
            return node;

        // Return whichever side found a node
        return left ? left : right;
    }

    // ----------------------------------------------------------
    // Inorder
    // ----------------------------------------------------------
    void inorder(Node* node) {

        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:

    BinaryTree() {

        /*
                    1
                  /   \
                 2     3
                / \   / \
               4   5 6   7
                  / \
                 8   9
        */

        root = new Node(1);

        root->left = new Node(2);
        root->right = new Node(3);

        root->left->left = new Node(4);
        root->left->right = new Node(5);

        root->right->left = new Node(6);
        root->right->right = new Node(7);

        root->left->right->left = new Node(8);
        root->left->right->right = new Node(9);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    void findLCA(int a, int b) {

        Node* answer =
            lowestCommonAncestor(root, a, b);

        if (answer)
            cout << "LCA("
                 << a << ", "
                 << b << ") = "
                 << answer->data
                 << endl;
        else
            cout << "LCA Not Found\n";
    }
};

int main() {

    BinaryTree tree;

    cout << "Inorder Traversal:\n";
    tree.inorder();

    cout << endl;

    tree.findLCA(4, 5);
    tree.findLCA(8, 9);
    tree.findLCA(4, 9);
    tree.findLCA(6, 7);
    tree.findLCA(6, 8);

    return 0;
}
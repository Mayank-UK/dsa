#include <iostream>
#include <algorithm>
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
    // Height
    // Returns height while updating diameter
    // Time: O(n)
    // ----------------------------------------------------------
    int height(Node* node, int& diameter) {

        if (node == nullptr)
            return 0;

        int leftHeight = height(node->left, diameter);
        int rightHeight = height(node->right, diameter);

        // Diameter passing through current node
        diameter = max(diameter,
                       leftHeight + rightHeight);

        return 1 + max(leftHeight, rightHeight);
    }

    // ----------------------------------------------------------
    // Inorder Traversal
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
                 / \     \
                4   5     6
               /
              7
        */

        root = new Node(1);

        root->left = new Node(2);
        root->right = new Node(3);

        root->left->left = new Node(4);
        root->left->right = new Node(5);

        root->right->right = new Node(6);

        root->left->left->left = new Node(7);
    }

    // ----------------------------------------------------------
    // Diameter
    // ----------------------------------------------------------
    int diameter() {

        int diameter = 0;

        height(root, diameter);

        return diameter;
    }

    void inorder() {

        inorder(root);
        cout << endl;
    }
};

int main() {

    BinaryTree tree;

    cout << "Inorder Traversal:\n";
    tree.inorder();

    cout << "\nDiameter of Tree = "
         << tree.diameter()
         << endl;

    return 0;
}
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
    // Recursive Inorder (For Verification)
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
        */

        root = new Node(1);

        root->left = new Node(2);
        root->right = new Node(3);

        root->left->left = new Node(4);
        root->left->right = new Node(5);

        root->right->left = new Node(6);
        root->right->right = new Node(7);
    }

    // ----------------------------------------------------------
    // Morris Inorder Traversal
    // Time : O(n)
    // Space: O(1)
    // ----------------------------------------------------------
    void morrisInorder() {

        Node* current = root;

        while (current != nullptr) {

            // No left child
            if (current->left == nullptr) {

                cout << current->data << " ";
                current = current->right;
            }
            else {

                // Find inorder predecessor
                Node* predecessor = current->left;

                while (predecessor->right != nullptr &&
                       predecessor->right != current)
                    predecessor = predecessor->right;

                // Create thread
                if (predecessor->right == nullptr) {

                    predecessor->right = current;
                    current = current->left;
                }
                // Thread already exists
                else {

                    predecessor->right = nullptr;

                    cout << current->data << " ";

                    current = current->right;
                }
            }
        }

        cout << endl;
    }

    // ----------------------------------------------------------
    // Morris Preorder Traversal
    // Time : O(n)
    // Space: O(1)
    // ----------------------------------------------------------
    void morrisPreorder() {

        Node* current = root;

        while (current != nullptr) {

            if (current->left == nullptr) {

                cout << current->data << " ";
                current = current->right;
            }
            else {

                Node* predecessor = current->left;

                while (predecessor->right != nullptr &&
                       predecessor->right != current)
                    predecessor = predecessor->right;

                if (predecessor->right == nullptr) {

                    cout << current->data << " ";

                    predecessor->right = current;

                    current = current->left;
                }
                else {

                    predecessor->right = nullptr;

                    current = current->right;
                }
            }
        }

        cout << endl;
    }

    // ----------------------------------------------------------
    // Recursive Inorder
    // ----------------------------------------------------------
    void inorder() {

        inorder(root);
        cout << endl;
    }
};

int main() {

    BinaryTree tree;

    cout << "Recursive Inorder:\n";
    tree.inorder();

    cout << "\nMorris Inorder:\n";
    tree.morrisInorder();

    cout << "\nMorris Preorder:\n";
    tree.morrisPreorder();

    return 0;
}
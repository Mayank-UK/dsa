#include <iostream>
#include <queue>
#include <sstream>
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
        */

        root = new Node(1);

        root->left = new Node(2);
        root->right = new Node(3);

        root->left->left = new Node(4);
        root->left->right = new Node(5);

        root->right->right = new Node(6);
    }

    // ----------------------------------------------------------
    // Serialize (Level Order)
    // Time : O(n)
    // Space: O(n)
    // ----------------------------------------------------------
    string serialize() {

        if (root == nullptr)
            return "";

        queue<Node*> q;
        q.push(root);

        stringstream ss;

        while (!q.empty()) {

            Node* current = q.front();
            q.pop();

            if (current == nullptr) {

                ss << "# ";
                continue;
            }

            ss << current->data << " ";

            q.push(current->left);
            q.push(current->right);
        }

        return ss.str();
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

    cout << "\nSerialized Tree:\n";
    cout << tree.serialize() << endl;

    return 0;
}
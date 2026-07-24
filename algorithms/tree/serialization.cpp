#include <iostream>
#include <queue>
#include <sstream>
using namespace std;

// ===== Serialization (Level-Order) =====
// Flatten a binary tree to a string using level-order traversal, emitting
// "#" for null children so the shape is recoverable. The matching rebuild
// (deserialize) lives in deserialization.cpp — this file serializes only.

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

    // Post-order free — every node is `new`-ed.
    void freeTree(Node* node) {
        if (node == nullptr)
            return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
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

    ~BinaryTree() { freeTree(root); }

    // ----------------------------------------------------------
    // Serialize (Level Order)
    // Time : O(n)  — every node (and null child) enqueued once
    // Space: O(n)  — queue + output string
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

    cout << "===== Serialization (Level-Order) =====\n";

    cout << "\n[Complexity]\n";
    cout << "Time : O(n) — every node and null child visited once\n";
    cout << "Space: O(n) — queue holds up to one level; output string is O(n)\n";
    cout << "Note : \"#\" marks null children so structure is preserved.\n";

    cout << "\n[Limitation]\n";
    cout << "This file SERIALIZES ONLY. The round-trip (rebuild the tree from "
            "this string) is implemented in deserialization.cpp — see that "
            "file for serialize → deserialize verification.\n";

    BinaryTree tree;

    cout << "\n[Demo]\n";
    cout << "Tree shape:\n";
    cout << "            1\n";
    cout << "          /   \\\n";
    cout << "         2     3\n";
    cout << "        / \\     \\\n";
    cout << "       4   5     6\n";

    cout << "\nInorder traversal: ";
    tree.inorder();

    cout << "\nSerialized string (level-order, '#' = null):\n";
    cout << tree.serialize() << endl;

    cout << "\n[Edge Cases]\n";
    cout << "- Empty tree serializes to \"\" (handled by the root==nullptr guard).\n";
    cout << "- Trailing nulls are emitted because every non-null node enqueues "
            "BOTH children; deserialization.cpp shows the matching reader.\n";

    return 0;
}

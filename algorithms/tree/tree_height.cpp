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
    // Recursive free (post-order delete — no leaks)
    // ----------------------------------------------------------
    void freeTree(Node* n) {
        if (!n) return;
        freeTree(n->left);
        freeTree(n->right);
        delete n;
    }

    // ----------------------------------------------------------
    // Height (Recursive)
    // Time : O(n)
    // Space: O(h) recursion stack
    // ----------------------------------------------------------
    int height(Node* node) {

        if (node == nullptr)
            return 0;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

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

    ~BinaryTree() {
        freeTree(root);
    }

    // ----------------------------------------------------------
    // Height Wrapper
    // ----------------------------------------------------------
    int height() {
        return height(root);
    }

    void inorder() {

        inorder(root);
        cout << endl;
    }
};

int main() {

    cout << "===================== Tree Height =====================" << endl;
    cout << endl;

    BinaryTree tree;

    cout << "[Complexity]" << endl;
    cout << "Time  : O(n) — every node visited once." << endl;
    cout << "Space : O(h) recursion stack (h = tree height)." << endl;
    cout << "Notes : Height is counted in nodes from root to deepest" << endl;
    cout << "        leaf; an empty tree has height 0." << endl;
    cout << endl;

    cout << "[Demo]" << endl;
    cout << "Tree shape:" << endl;
    cout << endl;
    cout << "             1" << endl;
    cout << "           /   \\" << endl;
    cout << "          2     3" << endl;
    cout << "         / \\     \\" << endl;
    cout << "        4   5     6" << endl;
    cout << "       /" << endl;
    cout << "      7" << endl;
    cout << endl;
    cout << "Inorder Traversal : ";
    tree.inorder();
    cout << "Height (nodes)    : " << tree.height() << endl;
    cout << "Deepest path      : 1 -> 2 -> 4 -> 7  (4 nodes)" << endl;
    cout << endl;

    cout << "[Edge Cases]" << endl;
    cout << "Empty tree -> height 0 (base case null returns 0)." << endl;
    cout << "Single-node tree -> height 1 (leaf returns 1)." << endl;

    return 0;
}

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
    // Height
    // Returns height while updating diameter (passed by ref).
    // Time: O(n)  Space: O(h)
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

    ~BinaryTree() {
        freeTree(root);
    }

    // ----------------------------------------------------------
    // Diameter (longest path in edges between any two nodes)
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

    cout << "===================== Tree Diameter =====================" << endl;
    cout << endl;

    BinaryTree tree;

    cout << "[Complexity]" << endl;
    cout << "Time  : O(n) — single post-order pass." << endl;
    cout << "Space : O(h) recursion stack." << endl;
    cout << "Notes : Diameter = longest path (in edges) between any" << endl;
    cout << "        two nodes; it may or may not pass through the" << endl;
    cout << "        root. Computed as max(leftH + rightH) over all" << endl;
    cout << "        nodes during the height recursion." << endl;
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
    cout << "Diameter (edges)  : " << tree.diameter() << endl;
    cout << "Longest path      : 7 -> 4 -> 2 -> 1 -> 3 -> 6" << endl;
    cout << "                    = 5 edges (6 nodes)" << endl;
    cout << "                    At root: leftH=3, rightH=2, sum=5." << endl;
    cout << endl;

    cout << "[Edge Cases]" << endl;
    cout << "Empty tree        -> diameter 0." << endl;
    cout << "Single-node tree  -> diameter 0 (no edges between nodes)." << endl;
    cout << "Two-node tree     -> diameter 1." << endl;

    return 0;
}

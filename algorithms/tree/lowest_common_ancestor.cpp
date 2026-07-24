#include <iostream>
using namespace std;

// ===== Lowest Common Ancestor =====
// Find the lowest node that has both p and q as descendants (a node is a
// descendant of itself). Classic recursion: return the node itself if it
// matches p or q; bubble up two non-null hits from different subtrees.

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
    // Time: O(n)  — visits each node once
    // Space: O(h) — recursion stack (h = height)
    // ----------------------------------------------------------
    Node* lowestCommonAncestor(Node* node,
                               int p,
                               int q) {

        if (node == nullptr)
            return nullptr;

        // One of the targets found — this node is a candidate LCA.
        if (node->data == p || node->data == q)
            return node;

        Node* left =
            lowestCommonAncestor(node->left, p, q);

        Node* right =
            lowestCommonAncestor(node->right, p, q);

        // One node in each subtree → this node is the LCA.
        if (left && right)
            return node;

        // Otherwise propagate whichever side found a target.
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

    // Post-order free — required because every node is `new`-ed.
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

    ~BinaryTree() { freeTree(root); }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    void findLCA(int a, int b) {

        Node* answer =
            lowestCommonAncestor(root, a, b);

        if (answer)
            cout << "LCA(" << a << ", " << b << ") = "
                 << answer->data << endl;
        else
            cout << "LCA(" << a << ", " << b
                 << ") = Not Found\n";
    }
};

int main() {

    cout << "===== Lowest Common Ancestor =====\n";

    cout << "\n[Complexity]\n";
    cout << "Time : O(n) — each node visited once\n";
    cout << "Space: O(h) — recursion stack (h = tree height)\n";
    cout << "Note : A node counts as a descendant of itself, so "
            "LCA(x, ancestor_of_x) = ancestor_of_x.\n";

    BinaryTree tree;

    cout << "\n[Demo]\n";
    cout << "Tree shape:\n";
    cout << "            1\n";
    cout << "          /   \\\n";
    cout << "         2     3\n";
    cout << "        / \\   / \\\n";
    cout << "       4   5 6   7\n";
    cout << "          / \\\n";
    cout << "         8   9\n";

    cout << "\nInorder traversal: ";
    tree.inorder();

    cout << "\nQueries (sibling pairs in different subtrees):\n";
    tree.findLCA(4, 5);   // different subtrees of 2 → 2
    tree.findLCA(6, 7);   // different subtrees of 3 → 3
    tree.findLCA(6, 8);   // 6 under 3, 8 under 2 → 1 (root)

    cout << "\nQueries (one node is an ancestor of the other):\n";
    tree.findLCA(2, 4);   // 2 is ancestor of 4 → 2
    tree.findLCA(5, 9);   // 5 is ancestor of 9 → 5
    tree.findLCA(1, 8);   // root is ancestor of everything → 1

    cout << "\nQueries (deep siblings):\n";
    tree.findLCA(8, 9);   // siblings under 5 → 5
    tree.findLCA(4, 9);   // both under 2 → 2

    cout << "\n[Edge Cases]\n";
    tree.findLCA(4, 4);   // same node → itself
    tree.findLCA(4, 99);  // one missing → the present node (it matches)
    tree.findLCA(42, 99); // both missing → Not Found

    return 0;
}

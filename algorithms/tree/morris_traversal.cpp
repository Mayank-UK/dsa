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
    // Recursive free (post-order delete — no leaks)
    // ----------------------------------------------------------
    void freeTree(Node* n) {
        if (!n) return;
        freeTree(n->left);
        freeTree(n->right);
        delete n;
    }

    // ----------------------------------------------------------
    // Recursive Inorder (for verification)
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

    ~BinaryTree() {
        freeTree(root);
    }

    // ----------------------------------------------------------
    // Morris Inorder Traversal
    // Time : O(n)
    // Space: O(1)  — trades structure mutation for constant space
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

    cout << "===================== Morris Traversal =====================" << endl;
    cout << endl;

    BinaryTree tree;

    cout << "[Complexity]" << endl;
    cout << "Time  : O(n) — amortized; each edge traversed a constant" << endl;
    cout << "        number of times via the threading." << endl;
    cout << "Space : O(1) — NO stack, NO recursion." << endl;
    cout << "Notes : Achieves constant space by temporarily threading" << endl;
    cout << "        each node's inorder predecessor back to it (mutates" << endl;
    cout << "        the tree), then un-threads on the way back. Trades" << endl;
    cout << "        structure mutation for the O(1) space bound; the" << endl;
    cout << "        tree is restored to its original shape at the end." << endl;
    cout << endl;

    cout << "[Demo]" << endl;
    cout << "Tree shape:" << endl;
    cout << endl;
    cout << "          1" << endl;
    cout << "        /   \\" << endl;
    cout << "       2     3" << endl;
    cout << "      / \\   / \\" << endl;
    cout << "     4   5 6   7" << endl;
    cout << endl;
    cout << "Recursive Inorder : ";
    tree.inorder();
    cout << "Morris Inorder    : ";
    tree.morrisInorder();
    cout << "Morris Preorder   : ";
    tree.morrisPreorder();
    cout << endl;

    cout << "[Verification]" << endl;
    cout << "Morris inorder output MUST match recursive inorder output" << endl;
    cout << "above (4 2 5 1 6 3 7) — if they differ, the threading is" << endl;
    cout << "broken." << endl;
    cout << endl;

    cout << "[Edge Cases]" << endl;
    cout << "Empty tree       -> nothing printed (loop never enters)." << endl;
    cout << "Single-node tree -> that node printed once, no predecessor" << endl;
    cout << "                    lookup needed." << endl;
    cout << "Right-skewed tree-> behaves like a linked-list walk; no" << endl;
    cout << "                    threading occurs." << endl;

    return 0;
}

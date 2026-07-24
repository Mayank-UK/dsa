#include <iostream>
#include <stack>
#include <queue>
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
    // Recursive Traversals
    // ----------------------------------------------------------
    void preorder(Node* node) {

        if (node == nullptr)
            return;

        cout << node->data << " ";

        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node* node) {

        if (node == nullptr)
            return;

        inorder(node->left);

        cout << node->data << " ";

        inorder(node->right);
    }

    void postorder(Node* node) {

        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);

        cout << node->data << " ";
    }

    // ----------------------------------------------------------
    // Height helper (for the stats block)
    // ----------------------------------------------------------
    int height(Node* node) {

        if (node == nullptr)
            return 0;

        return 1 + max(height(node->left), height(node->right));
    }

    int countNodes(Node* node) {

        if (node == nullptr)
            return 0;

        return 1 + countNodes(node->left) + countNodes(node->right);
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
    // Recursive Preorder  (Root Left Right)
    // ----------------------------------------------------------
    void preorder() {

        preorder(root);
        cout << endl;
    }

    // ----------------------------------------------------------
    // Recursive Inorder   (Left Root Right)
    // ----------------------------------------------------------
    void inorder() {

        inorder(root);
        cout << endl;
    }

    // ----------------------------------------------------------
    // Recursive Postorder (Left Right Root)
    // ----------------------------------------------------------
    void postorder() {

        postorder(root);
        cout << endl;
    }

    // ----------------------------------------------------------
    // Iterative Preorder (stack)
    // ----------------------------------------------------------
    void iterativePreorder() {

        if (root == nullptr)
            return;

        stack<Node*> st;
        st.push(root);

        while (!st.empty()) {

            Node* current = st.top();
            st.pop();

            cout << current->data << " ";

            if (current->right)
                st.push(current->right);

            if (current->left)
                st.push(current->left);
        }

        cout << endl;
    }

    // ----------------------------------------------------------
    // Iterative Inorder (stack)
    // ----------------------------------------------------------
    void iterativeInorder() {

        stack<Node*> st;
        Node* current = root;

        while (current != nullptr || !st.empty()) {

            while (current != nullptr) {
                st.push(current);
                current = current->left;
            }

            current = st.top();
            st.pop();

            cout << current->data << " ";

            current = current->right;
        }

        cout << endl;
    }

    // ----------------------------------------------------------
    // Iterative Postorder (two stacks)
    // ----------------------------------------------------------
    void iterativePostorder() {

        if (root == nullptr)
            return;

        stack<Node*> s1;
        stack<Node*> s2;

        s1.push(root);

        while (!s1.empty()) {

            Node* current = s1.top();
            s1.pop();

            s2.push(current);

            if (current->left)
                s1.push(current->left);

            if (current->right)
                s1.push(current->right);
        }

        while (!s2.empty()) {

            cout << s2.top()->data << " ";
            s2.pop();
        }

        cout << endl;
    }

    // ----------------------------------------------------------
    // Level Order Traversal (queue = BFS)
    // ----------------------------------------------------------
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

    // ----------------------------------------------------------
    // Stats helpers
    // ----------------------------------------------------------
    int height() { return height(root); }
    int size() { return countNodes(root); }
};

int main() {

    cout << "===================== Tree Traversals =====================" << endl;
    cout << endl;

    BinaryTree tree;

    cout << "[Complexity]" << endl;
    cout << "Time  : O(n) for every traversal (each node visited once)." << endl;
    cout << "Space : O(h) recursion/stack for depth-first variants," << endl;
    cout << "        O(w) for level order where w = max width;" << endl;
    cout << "        iterative forms use an explicit stack/queue." << endl;
    cout << "Notes : Pre/In/Post order differ only in WHEN the root is" << endl;
    cout << "        printed relative to its children." << endl;
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
    cout << "Nodes: " << tree.size() << "   Height: " << tree.height() << endl;
    cout << endl;

    cout << "[Recursive]" << endl;
    cout << "Preorder  (Root Left Right) : ";
    tree.preorder();
    cout << "Inorder   (Left Root Right) : ";
    tree.inorder();
    cout << "Postorder (Left Right Root) : ";
    tree.postorder();
    cout << endl;

    cout << "[Iterative]" << endl;
    cout << "Preorder  (stack)           : ";
    tree.iterativePreorder();
    cout << "Inorder   (stack)           : ";
    tree.iterativeInorder();
    cout << "Postorder (two stacks)      : ";
    tree.iterativePostorder();
    cout << endl;

    cout << "[BFS]" << endl;
    cout << "Level Order (queue)         : ";
    tree.levelOrder();
    cout << endl;

    cout << "[Edge Cases]" << endl;
    cout << "Recursive and iterative forms return empty output for an" << endl;
    cout << "empty tree (root == null guard); a single-node tree prints" << endl;
    cout << "just that node in every traversal." << endl;

    return 0;
}

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
    // Recursive Preorder
    // Root Left Right
    // ----------------------------------------------------------
    void preorder() {

        preorder(root);
        cout << endl;
    }

    // ----------------------------------------------------------
    // Recursive Inorder
    // Left Root Right
    // ----------------------------------------------------------
    void inorder() {

        inorder(root);
        cout << endl;
    }

    // ----------------------------------------------------------
    // Recursive Postorder
    // Left Right Root
    // ----------------------------------------------------------
    void postorder() {

        postorder(root);
        cout << endl;
    }

    // ----------------------------------------------------------
    // Iterative Preorder
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
    // Iterative Inorder
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
    // Iterative Postorder (Two Stacks)
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
    // Level Order Traversal
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
};

int main() {

    BinaryTree tree;

    cout << "Recursive Preorder:\n";
    tree.preorder();

    cout << "\nRecursive Inorder:\n";
    tree.inorder();

    cout << "\nRecursive Postorder:\n";
    tree.postorder();

    cout << "\nIterative Preorder:\n";
    tree.iterativePreorder();

    cout << "\nIterative Inorder:\n";
    tree.iterativeInorder();

    cout << "\nIterative Postorder:\n";
    tree.iterativePostorder();

    cout << "\nLevel Order:\n";
    tree.levelOrder();

    return 0;
}
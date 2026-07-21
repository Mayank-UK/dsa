#include <iostream>
#include <queue>
#include <sstream>
using namespace std;

class BinaryTree {
private:
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

public:

    // ----------------------------------------------------------
    // Serialize
    // Level Order Traversal
    // Time: O(n)
    // ----------------------------------------------------------
    static string serialize(Node* root) {

        if (root == nullptr)
            return "";

        queue<Node*> q;
        q.push(root);

        string result;

        while (!q.empty()) {

            Node* current = q.front();
            q.pop();

            if (current == nullptr) {
                result += "# ";
                continue;
            }

            result += to_string(current->data) + " ";

            q.push(current->left);
            q.push(current->right);
        }

        return result;
    }

    // ----------------------------------------------------------
    // Deserialize
    // Time: O(n)
    // ----------------------------------------------------------
    static Node* deserialize(const string& data) {

        if (data.empty())
            return nullptr;

        stringstream ss(data);

        string value;
        ss >> value;

        Node* root = new Node(stoi(value));

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {

            Node* current = q.front();
            q.pop();

            // Left Child
            if (!(ss >> value))
                break;

            if (value != "#") {
                current->left = new Node(stoi(value));
                q.push(current->left);
            }

            // Right Child
            if (!(ss >> value))
                break;

            if (value != "#") {
                current->right = new Node(stoi(value));
                q.push(current->right);
            }
        }

        return root;
    }

    // ----------------------------------------------------------
    // Inorder
    // ----------------------------------------------------------
    static void inorder(Node* root) {

        if (root == nullptr)
            return;

        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    // ----------------------------------------------------------
    // Sample Tree
    // ----------------------------------------------------------
    static Node* createTree() {

        /*
                 1
               /   \
              2     3
             / \   / \
            4  5  6   7
        */

        Node* root = new Node(1);

        root->left = new Node(2);
        root->right = new Node(3);

        root->left->left = new Node(4);
        root->left->right = new Node(5);

        root->right->left = new Node(6);
        root->right->right = new Node(7);

        return root;
    }
};

int main() {

    auto root = BinaryTree::createTree();

    string serialized =
        BinaryTree::serialize(root);

    cout << "Serialized Tree:\n";
    cout << serialized << endl;

    auto newRoot =
        BinaryTree::deserialize(serialized);

    cout << "\nInorder After Deserialization:\n";

    BinaryTree::inorder(newRoot);

    cout << endl;

    return 0;
}
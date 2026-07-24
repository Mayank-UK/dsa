#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

// ===== Deserialization (Level-Order Round-Trip) =====
// Serialize a tree to the level-order string format (with "#" for nulls) and
// rebuild an identical tree from it. The DEMO proves the round-trip is
// faithful: inorder(original) == inorder(rebuilt).

class BinaryTree {
public:
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

private:
    // Post-order free — every node is `new`-ed (including the rebuilt tree).
    static void freeTree(Node* node) {
        if (node == nullptr)
            return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

public:

    // ----------------------------------------------------------
    // Serialize
    // Level Order Traversal
    // Time: O(n)  Space: O(n)
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
    // Time: O(n)  Space: O(n)
    // Rebuilds the tree level by level, mirroring serialize()'s queue walk.
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
    // Inorder (collected into a vector, so we can compare round-trips)
    // ----------------------------------------------------------
    static void inorderCollect(Node* node, vector<int>& out) {

        if (node == nullptr)
            return;

        inorderCollect(node->left, out);
        out.push_back(node->data);
        inorderCollect(node->right, out);
    }

    static void inorderPrint(Node* root) {

        if (root == nullptr) {
            cout << "(empty)\n";
            return;
        }

        vector<int> vals;
        inorderCollect(root, vals);

        for (int v : vals)
            cout << v << " ";
        cout << endl;
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

    // Free a built tree (used for both the original and rebuilt trees).
    static void freeNodeTree(Node* root) { freeTree(root); }
};

int main() {

    cout << "===== Deserialization (Level-Order Round-Trip) =====\n";

    cout << "\n[Complexity]\n";
    cout << "Time : O(n) — serialize and deserialize each walk every node once\n";
    cout << "Space: O(n) — queue + serialized string + rebuilt nodes\n";
    cout << "Note : Paired with serialization.cpp (serialize-only); this file "
            "does both and verifies the round-trip.\n";

    cout << "\n[Demo]\n";
    cout << "Original tree shape:\n";
    cout << "         1\n";
    cout << "       /   \\\n";
    cout << "      2     3\n";
    cout << "     / \\   / \\\n";
    cout << "    4  5  6   7\n";

    auto original = BinaryTree::createTree();

    cout << "\nInorder (original):  ";
    BinaryTree::inorderPrint(original);

    // 1) Serialize the original tree to the level-order string.
    string serialized = BinaryTree::serialize(original);
    cout << "Serialized string:   " << serialized << endl;

    // 2) Rebuild a brand-new tree from that string.
    auto rebuilt = BinaryTree::deserialize(serialized);

    cout << "Inorder (rebuilt):   ";
    BinaryTree::inorderPrint(rebuilt);

    cout << "\n[Verify]\n";
    vector<int> a, b;
    BinaryTree::inorderCollect(original, a);
    BinaryTree::inorderCollect(rebuilt, b);

    bool faithful = (a == b);
    cout << "inorder(original) == inorder(rebuilt): "
         << (faithful ? "Yes — round-trip faithful" : "No — MISMATCH")
         << endl;

    cout << "\n[Edge Cases]\n";

    // Empty string → empty tree.
    auto emptyTree = BinaryTree::deserialize("");
    cout << "deserialize(\"\") → empty tree; inorder: ";
    BinaryTree::inorderPrint(emptyTree);

    // Single-node tree.
    auto singleOriginal = new BinaryTree::Node(42);
    string single = BinaryTree::serialize(singleOriginal);
    auto singleRoot = BinaryTree::deserialize(single);
    cout << "Single-node tree serialized: \"" << single << "\"\n";
    cout << "Single-node rebuilt inorder: ";
    BinaryTree::inorderPrint(singleRoot);

    // No leaks: free every tree we allocated.
    BinaryTree::freeNodeTree(original);
    BinaryTree::freeNodeTree(rebuilt);
    BinaryTree::freeNodeTree(singleOriginal);
    BinaryTree::freeNodeTree(singleRoot);
    // emptyTree is nullptr — nothing to free.

    return 0;
}

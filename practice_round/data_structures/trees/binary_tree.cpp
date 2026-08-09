/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
#include <algorithm>
#include <queue>
using std::cout;
using std::max;
using std::queue;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value)
    {
        data = value;
        left = right = nullptr;
    }
};

class BinaryTree
{
private:
    Node *root;

public:
    BinaryTree()
    {
        root = new Node(5);
        root->left = new Node(3);
        root->right = new Node(7);

        root->left->left = new Node(11);
        root->left->right = new Node(13);

        root->right->left = new Node(27);
        root->right->right = new Node(31);

        root->left->left->right = new Node(71);
    }

    BinaryTree(const BinaryTree &) = delete;
    BinaryTree &operator=(const BinaryTree &) = delete;

    ~BinaryTree()
    {
        destroy(root);
    }

    Node *getRoot()
    {
        return root;
    }

    void preOrder(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    void postOrder(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

    void levelOrder()
    {
        if (root == nullptr)
        {
            return;
        }

        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left)
            {
                q.push(current->left);
            }

            if (current->right)
            {
                q.push(current->right);
            }
        }
    }

    bool search(Node *node, int value)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (node->data == value)
        {
            return true;
        }

        return search(node->left, value) || search(node->right, value);
    }

    int countNodes(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int countLeaves(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        if (node->left == nullptr && node->right == nullptr)
        {
            return 1;
        }

        return countLeaves(node->left) + countLeaves(node->right);
    }

    int height(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return 1 + max(leftHeight, rightHeight);
    }

    void destroy(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        destroy(node->left);
        destroy(node->right);

        delete node;
    }
};

int main()
{
    BinaryTree binaryTree;

    cout << "preOrder: ";
    binaryTree.preOrder(binaryTree.getRoot());
    cout << "\n";

    cout << "inOrder: ";
    binaryTree.inOrder(binaryTree.getRoot());
    cout << "\n";

    cout << "postOrder: ";
    binaryTree.postOrder(binaryTree.getRoot());
    cout << "\n";

    cout << "levelOrder: ";
    binaryTree.levelOrder();
    cout << "\n";

    cout << "height: " << binaryTree.height(binaryTree.getRoot()) << "\n";

    cout << "nodes: " << binaryTree.countNodes(binaryTree.getRoot()) << "\n";

    cout << "leaves: " << binaryTree.countLeaves(binaryTree.getRoot()) << "\n";

    return 0;
}
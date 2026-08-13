/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
#include <queue>
#include <algorithm>

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

class BinarySearchTree
{
private:
    Node *root;

    Node *insert(Node *node, int value)
    {

        if (node == nullptr)
        {
            return new Node(value);
        }

        if (value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insert(node->right, value);
        }
        else
        {
            return node;
        }

        return node;
    }

    Node *remove(Node *node, int value)
    {

        if (node == nullptr)
        {
            return nullptr;
        }

        if (value < node->data)
        {
            node->left = remove(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = remove(node->right, value);
        }
        else
        {
            /*
                Found the node
                1. If node is a leaf node
                    Simply delete and return nullptr
                2. If node has 1 child
                    Delete the node and return it's child
                3. If node has 2 child
                    Find the smallest sub node in it's right sub tree, copy it's value
                    Delete the target node and replace it with the smallest sub node found to preserve BST property
            */

            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }
            else if (node->left != nullptr && node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            else if (node->left == nullptr && node->right != nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else
            {
                Node *temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        return node;
    }

public:
    BinarySearchTree()
    {
        root = nullptr;
    }

    BinarySearchTree(const BinarySearchTree &) = delete;
    BinarySearchTree &operator=(const BinarySearchTree &) = delete;

    ~BinarySearchTree()
    {
        destroy(root);
    }

    Node *getRoot()
    {
        return root;
    }

    void insert(int value)
    {
        root = insert(root, value);
    }

    Node *findMin(Node *node)
    {

        if (node == nullptr)
        {
            return nullptr;
        }

        // this is a BST, so lowest values lie on left side and at the last level

        while (node->left != nullptr)
        {
            node = node->left;
        }

        return node;
    }

    Node *findMax(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        // this is a BST, so hight values lie on right side and at the last level

        while (node->right != nullptr)
        {
            node = node->right;
        }

        return node;
    }

    bool search(Node *node, int value)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (value < node->data)
        {
            return search(node->left, value);
        }
        else if (value > node->data)
        {
            return search(node->right, value);
        }
        else
        {
            return true;
        }
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

        return;
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

        return;
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

        return;
    }

    void levelOrder(Node *node)
    {

        if (node == nullptr)
        {
            return;
        }

        queue<Node *> q;
        q.push(node);

        while (!q.empty())
        {
            Node *current = q.front();

            q.pop();
            cout << current->data << " ";

            if (current->left)
                q.push(current->left);

            if (current->right)
                q.push(current->right);
        }
    }

    void remove(int value)
    {
        root = remove(root, value);
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
    BinarySearchTree bst;

    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    bst.insert(5);
    bst.insert(6);
    bst.insert(7);
    bst.insert(8);

    cout << "preOrder: ";
    bst.preOrder(bst.getRoot());
    cout << "\n";

    cout << "inOrder: ";
    bst.inOrder(bst.getRoot());
    cout << "\n";

    cout << "postOrder: ";
    bst.postOrder(bst.getRoot());
    cout << "\n";

    cout << "levelOrder: ";
    bst.levelOrder(bst.getRoot());
    cout << "\n";

    cout << "height: " << bst.height(bst.getRoot()) << "\n";

    cout << "nodes: " << bst.countNodes(bst.getRoot()) << "\n";

    cout << "leaves: " << bst.countLeaves(bst.getRoot()) << "\n";

    bst.remove(7);
    bst.remove(1);

    cout << "levelOrder: ";
    bst.levelOrder(bst.getRoot());
    cout << "\n";

    cout << "minimum: " << bst.findMin(bst.getRoot())->data << "\n";

    cout << "maximum: " << bst.findMax(bst.getRoot())->data << "\n";

    return 0;
}

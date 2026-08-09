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
    int height;
    Node *left;
    Node *right;

    Node(int value)
    {
        data = value;
        left = right = nullptr;
        height = 0;
    }
};

class AvlTree
{
private:
    Node *root;

    Node *insert(Node *node, int value) {}

    bool search(Node *node, int value)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (value == node->data)
        {
            return true;
        }

        if (value < node->data)
        {
            return search(node->left, value);
        }

        if (value > node->data)
        {
            return search(node->right, value);
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

            if (current->left != nullptr)
                q.push(current->left);

            if (current->right != nullptr)
                q.push(current->right);
        }
    }

    Node *remove(Node *node, int value) {}

    int height(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        return node->height;
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

public:
    AvlTree()
    {
        root = nullptr;
    }

    ~AvlTree()
    {
        destroy(root);
    }

    AvlTree(const AvlTree &) = delete;
    AvlTree &operator=(const AvlTree &) = delete;

    void insert(int value)
    {
        root = insert(root, value);
    }

    Node *findMin()
    {
        if (root == nullptr)
            return nullptr;

        Node *current = root;

        while (current->left != nullptr)
        {
            current = current->left;
        }

        return current;
    }

    Node *findMax()
    {
        if (root == nullptr)
            return nullptr;

        Node *current = root;

        while (current->right != nullptr)
        {
            current = current->right;
        }

        return current;
    }

    bool search(int value)
    {
        return search(root, value);
    }

    void preOrder()
    {
        preOrder(root);
    }

    void inOrder()
    {
        inOrder(root);
    }

    void postOrder()
    {
        postOrder(root);
    }

    void levelOrder()
    {
        levelOrder(root);
    }

    void remove(int value)
    {
        root = remove(root, value);
    }

    int height()
    {
        return height(root);
    }

    int countNodes()
    {
        return countNodes(root);
    }

    int countLeaves()
    {
        return countLeaves(root);
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
    AvlTree avlTree;

    avlTree.insert(1);
    avlTree.insert(2);
    avlTree.insert(3);
    avlTree.insert(4);
    avlTree.insert(5);
    avlTree.insert(6);
    avlTree.insert(7);
    avlTree.insert(8);

    cout << "preOrder: ";
    avlTree.preOrder();
    cout << "\n";

    cout << "inOrder: ";
    avlTree.inOrder();
    cout << "\n";

    cout << "postOrder: ";
    avlTree.postOrder();
    cout << "\n";

    cout << "levelOrder: ";
    avlTree.levelOrder();
    cout << "\n";

    cout << "height: " << avlTree.height() << "\n";

    cout << "nodes: " << avlTree.countNodes() << "\n";

    cout << "leaves: " << avlTree.countLeaves() << "\n";

    avlTree.remove(7);
    avlTree.remove(1);

    cout << "levelOrder: ";
    avlTree.levelOrder();
    cout << "\n";

    cout << "minimum: " << avlTree.findMin()->data << "\n";

    cout << "maximum: " << avlTree.findMax()->data << "\n";

    return 0;
}

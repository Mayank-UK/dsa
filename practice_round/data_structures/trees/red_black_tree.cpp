/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
#include <algorithm>
#include <queue>

using std::cout;
using std::max;
using std::queue;

enum Color
{
    RED,
    BLACK
};

struct Node
{
    int data;
    Color color;
    Node *left;
    Node *right;
    Node *parent;

    Node(int value, Node *sentinelNode)
    {
        data = value;
        color = RED;
        left = right = parent = sentinelNode;
    }
};

class RedBlackTree
{
private:
    Node *root;
    Node *sentinelNode;

    void leftRotate(Node *node)
    {
        Node *x = node;
        Node *y = node->right;
        Node *y_left = y->left;

        if (x->parent == sentinelNode)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->left = x;
        x->right = y_left;

        y->parent = x->parent;
        x->parent = y;

        if (y_left != sentinelNode)
        {
            y_left->parent = x;
        }
    }

    void rightRotate(Node *node)
    {
        Node *x = node;
        Node *y = x->left;
        Node *y_right = y->right;

        if (x->parent == sentinelNode)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->right = x;
        x->left = y_right;

        y->parent = x->parent;
        x->parent = y;

        if (y_right != sentinelNode)
        {
            y_right->parent = x;
        }
    }

    void insertionFixup(Node *node)
    {
        while (node->parent->color == RED)
        {
            // storing the pointers separately to make recoloring simple even after rotation
            Node *grandParentBfrRotation = node->parent->parent;
            Node *parentBfrRotation = node->parent;
            Node *uncle;

            // parent is left child
            if (node->parent == node->parent->parent->left)
            {
                uncle = node->parent->parent->right;

                // uncle RED
                if (uncle->color == RED)
                {
                    parentBfrRotation->color = uncle->color = BLACK;
                    grandParentBfrRotation->color = RED;

                    // recoloring needs to be fixed iteratively
                    node = grandParentBfrRotation;
                }
                // uncle BLACK
                else
                {
                    // LL
                    if (node == node->parent->left)
                    {
                        rightRotate(grandParentBfrRotation);

                        grandParentBfrRotation->color = RED;
                        parentBfrRotation->color = BLACK;

                        break;
                    }

                    // LR
                    if (node == node->parent->right)
                    {
                        leftRotate(parentBfrRotation);
                        rightRotate(grandParentBfrRotation);

                        parentBfrRotation->color = grandParentBfrRotation->color = RED;
                        node->color = BLACK;

                        // rotation fixes the unword movement of violation, so break
                        break;
                    }
                }
            }
            // parent is right child
            else
            {
                uncle = node->parent->parent->left;

                // uncle RED
                if (uncle->color == RED)
                {
                    parentBfrRotation->color = uncle->color = BLACK;
                    grandParentBfrRotation->color = RED;

                    // recoloring needs to be fixed iteratively
                    node = grandParentBfrRotation;
                }
                // uncle BLACK
                else
                {
                    // RR
                    if (node == node->parent->right)
                    {
                        leftRotate(grandParentBfrRotation);

                        grandParentBfrRotation->color = RED;
                        parentBfrRotation->color = BLACK;

                        // rotation fixes the unword movement of violation, so break
                        break;
                    }

                    // RL
                    if (node == node->parent->left)
                    {
                        rightRotate(parentBfrRotation);
                        leftRotate(grandParentBfrRotation);

                        parentBfrRotation->color = grandParentBfrRotation->color = RED;
                        node->color = BLACK;

                        // rotation fixes the unword movement of violation, so break
                        break;
                    }
                }
            }
        }
    }

    Node *insert(Node *node, int value)
    {
        Node *current = node;
        Node *parent = sentinelNode;

        while (current != sentinelNode)
        {
            parent = current;

            if (value < current->data)
            {
                current = current->left;
            }
            else if (value > current->data)
            {
                current = current->right;
            }
            else
            {
                return nullptr;
            }
        }

        Node *newNode = new Node(value, sentinelNode);
        newNode->parent = parent;

        if (parent == sentinelNode)
        {
            root = newNode;
        }
        else if (value < parent->data)
        {
            parent->left = newNode;
        }
        else
        {
            parent->right = newNode;
        }

        return newNode;
    }

    bool search(Node *node, int value)
    {
        if (node == sentinelNode)
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

    Node *findMin(Node *node)
    {
        if (node == sentinelNode)
        {
            return nullptr;
        }

        Node *current = node;

        while (current->left != sentinelNode)
        {
            current = current->left;
        }

        return current;
    }

    Node *findMax(Node *node)
    {
        if (node == sentinelNode)
        {
            return nullptr;
        }

        Node *current = node;

        while (current->right != sentinelNode)
        {
            current = current->right;
        }

        return current;
    }

    void preOrder(Node *node)
    {
        if (node == sentinelNode)
        {
            return;
        }

        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(Node *node)
    {
        if (node == sentinelNode)
        {
            return;
        }

        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    void postOrder(Node *node)
    {
        if (node == sentinelNode)
        {
            return;
        }

        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

    void levelOrder(Node *node)
    {
        if (node == sentinelNode)
        {
            return;
        }

        queue<Node *> q;
        q.push(node);

        while (!q.empty())
        {
            Node *t = q.front();
            cout << t->data << " ";
            q.pop();

            if (t->left != sentinelNode)
            {
                q.push(t->left);
            }

            if (t->right != sentinelNode)
            {
                q.push(t->right);
            }
        }
    }

    int countNodes(Node *node)
    {
        if (node == sentinelNode)
        {
            return 0;
        }

        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int countLeaves(Node *node)
    {
        if (node == sentinelNode)
        {
            return 0;
        }

        if (node->left == sentinelNode && node->right == sentinelNode)
        {
            return 1;
        }

        return countLeaves(node->left) + countLeaves(node->right);
    }

    int getHeight(Node *node)
    {
        if (node == sentinelNode)
        {
            return 0;
        }

        return (1 + max(getHeight(node->left), getHeight(node->right)));
    }

    void transplant(Node *current, Node *successor)
    {
        if (current->parent == sentinelNode)
        {
            root = successor;
        }
        else if (current == current->parent->left)
        {
            current->parent->left = successor;
        }
        else
        {
            current->parent->right = successor;
        }

        successor->parent = current->parent;
    }

    void removalFixup(Node *replacement)
    {
        while (replacement != root && replacement->color == BLACK)
        {
            Node *parent = replacement->parent;

            if (replacement == replacement->parent->left)
            {
                Node *sibling = parent->right;

                // Case 1: sibling is RED
                if (sibling->color == RED)
                {
                    sibling->color = BLACK;
                    parent->color = RED;

                    leftRotate(parent);

                    sibling = parent->right;
                }

                // Case 2: sibling is BLACK and both children are BLACK
                if (sibling->left->color == BLACK &&
                    sibling->right->color == BLACK)
                {
                    sibling->color = RED;

                    replacement = parent;
                }
                else
                {
                    // Case 3: sibling is BLACK,
                    // near child is RED, far child is BLACK
                    if (sibling->right->color == BLACK)
                    {
                        sibling->left->color = BLACK;
                        sibling->color = RED;

                        rightRotate(sibling);

                        sibling = parent->right;
                    }

                    // Case 4: sibling is BLACK,
                    // far child is RED
                    sibling->color = parent->color;
                    parent->color = BLACK;
                    sibling->right->color = BLACK;

                    leftRotate(parent);

                    break;
                }
            }
            else
            {
                // Mirror cases
                Node *sibling = parent->left;

                // Case 1: sibling is RED
                if (sibling->color == RED)
                {
                    sibling->color = BLACK;
                    parent->color = RED;

                    rightRotate(parent);

                    sibling = parent->left;
                }

                // Case 2: sibling is BLACK and both children are BLACK
                if (sibling->right->color == BLACK &&
                    sibling->left->color == BLACK)
                {
                    sibling->color = RED;

                    replacement = parent;
                }
                else
                {
                    // Case 3: sibling is BLACK,
                    // near child is RED, far child is BLACK
                    if (sibling->left->color == BLACK)
                    {
                        sibling->right->color = BLACK;
                        sibling->color = RED;

                        leftRotate(sibling);

                        sibling = parent->left;
                    }

                    // Case 4: sibling is BLACK,
                    // far child is RED
                    sibling->color = parent->color;
                    parent->color = BLACK;
                    sibling->left->color = BLACK;

                    rightRotate(parent);

                    break;
                }
            }
        }

        replacement->color = BLACK;
    }

    void destroy(Node *node)
    {
        if (node == sentinelNode)
        {
            return;
        }

        destroy(node->left);
        destroy(node->right);

        delete node;
    }

public:
    RedBlackTree()
    {
        sentinelNode = new Node(0, nullptr);
        sentinelNode->color = BLACK;

        sentinelNode->left = sentinelNode->right = sentinelNode->parent = sentinelNode;

        root = sentinelNode;
    }

    RedBlackTree(const RedBlackTree &) = delete;
    RedBlackTree &operator=(const RedBlackTree &) = delete;

    ~RedBlackTree()
    {
        destroy(root);
        delete sentinelNode;
    }

    void insert(int value)
    {
        Node *newNode = insert(root, value);

        if (newNode == nullptr)
        {
            return;
        }

        insertionFixup(newNode);
        root->color = BLACK;
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

    bool search(int value)
    {
        return search(root, value);
    }

    Node *findMin()
    {
        return findMin(root);
    }

    Node *findMax()
    {
        return findMax(root);
    }

    int countNodes()
    {
        return countNodes(root);
    }

    int countLeaves()
    {
        return countLeaves(root);
    }

    int getHeight()
    {
        return getHeight(root);
    }

    void remove(int value)
    {
        // Find the node to delete
        Node *current = root;

        while (current != sentinelNode && current->data != value)
        {
            if (value < current->data)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        if (current == sentinelNode)
        {
            return;
        }

        /*
            removedColor represent the color of the node which is to be deleted, fixup is done only when a black node is deleted
            because deleting a RED node doesn't change the number of BLACK nodes on any root-to-leaf path
        */
        Color removedColor = current->color;
        // replacement represent the node which is used to replace the node which is deleted
        Node *replacement;

        // No left child
        if (current->left == sentinelNode)
        {
            replacement = current->right;

            transplant(current, current->right);
        }

        // No right child
        else if (current->right == sentinelNode)
        {
            replacement = current->left;

            transplant(current, current->left);
        }

        // Two children
        else
        {
            Node *successor = findMin(current->right);

            removedColor = successor->color;
            // since successor is the minimum node, it can't have the left child
            // since we want the fixup to start from where things have been changed, so we start from successor's right
            replacement = successor->right;

            if (successor->parent == current)
            {
                replacement->parent = successor;
            }
            else
            {
                transplant(successor, successor->right);

                successor->right = current->right;
                successor->right->parent = successor;
            }

            transplant(current, successor);

            successor->left = current->left;
            successor->left->parent = successor;
            successor->color = current->color;
        }

        delete current;

        if (removedColor == BLACK)
        {
            removalFixup(replacement);
        }
    }
};

int main()
{
    RedBlackTree redBlackTree;

    redBlackTree.insert(1);
    redBlackTree.insert(2);
    redBlackTree.insert(3);
    redBlackTree.insert(4);
    redBlackTree.insert(5);
    redBlackTree.insert(6);
    redBlackTree.insert(7);
    redBlackTree.insert(8);

    cout << "preOrder: ";
    redBlackTree.preOrder();
    cout << "\n";

    cout << "inOrder: ";
    redBlackTree.inOrder();
    cout << "\n";

    cout << "postOrder: ";
    redBlackTree.postOrder();
    cout << "\n";

    cout << "levelOrder: ";
    redBlackTree.levelOrder();
    cout << "\n";

    cout << "height: " << redBlackTree.getHeight() << "\n";

    cout << "nodes: " << redBlackTree.countNodes() << "\n";

    cout << "leaves: " << redBlackTree.countLeaves() << "\n";

    redBlackTree.remove(7);
    redBlackTree.remove(1);

    cout << "levelOrder: ";
    redBlackTree.levelOrder();
    cout << "\n";

    Node *min = redBlackTree.findMin();
    if (min != nullptr)
    {
        cout << "minimum: " << min->data << "\n";
    }

    Node *max = redBlackTree.findMax();
    if (max != nullptr)
    {

        cout << "maximum: " << max->data << "\n";
    }

    return 0;
}
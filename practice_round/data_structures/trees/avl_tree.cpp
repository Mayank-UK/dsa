/*
            ############################################# Practice round 1 #############################################
*/

// #include <iostream>
// #include <queue>
// #include <algorithm>
// #include <vector>

// using std::cout;
// using std::max;
// using std::queue;

// struct Node
// {
//     int data;
//     int height;
//     Node *left;
//     Node *right;

//     Node(int value)
//     {
//         data = value;
//         left = right = nullptr;
//         height = 1;
//     }
// };

// class AvlTree
// {
// private:
//     Node *root;

//     void updateHeight(Node *node)
//     {
//         if (node == nullptr)
//         {
//             return;
//         }

//         node->height = (1 + max(getHeight(node->left), getHeight(node->right)));
//     }

//     int getBalanceFactor(Node *node)
//     {
//         if (node == nullptr)
//         {
//             return 0;
//         }

//         return getHeight(node->left) - getHeight(node->right);
//     }

//     Node *leftRotate(Node *node)
//     {
//         Node *x = node;
//         Node *y = node->right;
//         Node *temp = y->left;

//         y->left = x;
//         x->right = temp;

//         updateHeight(x);
//         updateHeight(y);

//         return y;
//     }

//     Node *rightRotate(Node *node)
//     {
//         Node *x = node;
//         Node *y = node->left;
//         Node *temp = y->right;

//         y->right = x;
//         x->left = temp;

//         updateHeight(x);
//         updateHeight(y);

//         return y;
//     }

//     Node *insert(Node *node, int value)
//     {
//         if (node == nullptr)
//         {
//             return new Node(value);
//         }

//         if (value < node->data)
//         {
//             node->left = insert(node->left, value);
//         }
//         else if (value > node->data)
//         {
//             node->right = insert(node->right, value);
//         }
//         else
//         {
//             return node;
//         }

//         updateHeight(node);

//         int balanceFactor = getBalanceFactor(node);

//         // LL
//         if (balanceFactor > 1 && value < node->left->data)
//         {
//             return rightRotate(node);
//         }

//         // RR
//         if (balanceFactor < -1 && value > node->right->data)
//         {
//             return leftRotate(node);
//         }

//         // LR
//         if (balanceFactor > 1 && value > node->left->data)
//         {
//             node->left = leftRotate(node->left);
//             return rightRotate(node);
//         }

//         // Rl
//         if (balanceFactor < -1 && value < node->right->data)
//         {
//             node->right = rightRotate(node->right);
//             return leftRotate(node);
//         }

//         return node;
//     }

//     bool search(Node *node, int value)
//     {
//         if (node == nullptr)
//         {
//             return false;
//         }

//         if (value == node->data)
//         {
//             return true;
//         }

//         if (value < node->data)
//         {
//             return search(node->left, value);
//         }

//         if (value > node->data)
//         {
//             return search(node->right, value);
//         }
//     }

//     void preOrder(Node *node)
//     {
//         if (node == nullptr)
//         {
//             return;
//         }

//         cout << node->data << " ";
//         preOrder(node->left);
//         preOrder(node->right);
//     }

//     void inOrder(Node *node)
//     {
//         if (node == nullptr)
//         {
//             return;
//         }

//         inOrder(node->left);
//         cout << node->data << " ";
//         inOrder(node->right);
//     }

//     void postOrder(Node *node)
//     {
//         if (node == nullptr)
//         {
//             return;
//         }

//         postOrder(node->left);
//         postOrder(node->right);
//         cout << node->data << " ";
//     }

//     void levelOrder(Node *node)
//     {
//         if (node == nullptr)
//         {
//             return;
//         }

//         queue<Node *> q;
//         q.push(node);

//         while (!q.empty())
//         {
//             Node *current = q.front();
//             q.pop();

//             cout << current->data << " ";

//             if (current->left != nullptr)
//                 q.push(current->left);

//             if (current->right != nullptr)
//                 q.push(current->right);
//         }
//     }

//     Node *remove(Node *node, int value)
//     {
//         if (node == nullptr)
//         {
//             return nullptr;
//         }

//         if (value < node->data)
//         {
//             node->left = remove(node->left, value);
//         }
//         else if (value > node->data)
//         {
//             node->right = remove(node->right, value);
//         }
//         else
//         {
//             /*
//                 1. If node is a leaf node
//                     Simply delete and return nullptr
//                 2. If node has 1 child
//                     Simply delete node and return the child
//                 3. If node has 2 children
//                     Find the smallest from the node->right and replace with the node and then delete that smallest node
//             */

//             if (node->left == nullptr && node->right == nullptr)
//             {
//                 delete node;

//                 return nullptr;
//             }
//             else if (node->left != nullptr && node->right == nullptr)
//             {
//                 Node *temp = node->left;
//                 delete node;
//                 return temp;
//             }
//             else if (node->left == nullptr && node->right != nullptr)
//             {
//                 Node *temp = node->right;
//                 delete node;
//                 return temp;
//             }
//             else
//             {
//                 Node *temp = findMin(node->right);
//                 node->data = temp->data;
//                 node->right = remove(node->right, temp->data);
//             }
//         }

//         updateHeight(node);
//         int balanceFactor = getBalanceFactor(node);

//         // LL
//         if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
//         {
//             return rightRotate(node);
//         }

//         // RR
//         if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
//         {
//             return leftRotate(node);
//         }

//         // LR

//         if (balanceFactor > 1 && getBalanceFactor(node->left) <= 0)
//         {
//             node->left = leftRotate(node->left);
//             return rightRotate(node);
//         }

//         // RL
//         if (balanceFactor < -1 && getBalanceFactor(node->right) >= 0)
//         {
//             node->right = rightRotate(node->right);
//             return leftRotate(node);
//         }

//         return node;
//     }

//     int countNodes(Node *node)
//     {
//         if (node == nullptr)
//         {
//             return 0;
//         }

//         return 1 + countNodes(node->left) + countNodes(node->right);
//     }

//     int countLeaves(Node *node)
//     {
//         if (node == nullptr)
//         {
//             return 0;
//         }

//         if (node->left == nullptr && node->right == nullptr)
//         {
//             return 1;
//         }

//         return countLeaves(node->left) + countLeaves(node->right);
//     }

//     int getHeight(Node *node)
//     {
//         if (node == nullptr)
//         {
//             return 0;
//         }

//         return node->height;
//     }

//     Node *findMin(Node *node)
//     {
//         if (node == nullptr)
//             return nullptr;

//         Node *current = node;

//         while (current->left != nullptr)
//         {
//             current = current->left;
//         }

//         return current;
//     }

//     Node *findMax(Node *node)
//     {
//         if (node == nullptr)
//             return nullptr;

//         Node *current = node;

//         while (current->right != nullptr)
//         {
//             current = current->right;
//         }

//         return current;
//     }

// public:
//     AvlTree()
//     {
//         root = nullptr;
//     }

//     ~AvlTree()
//     {
//         destroy(root);
//     }

//     AvlTree(const AvlTree &) = delete;
//     AvlTree &operator=(const AvlTree &) = delete;

//     void insert(int value)
//     {
//         root = insert(root, value);
//     }

//     Node *findMin()
//     {
//         return findMin(root);
//     }

//     Node *findMax()
//     {
//         return findMax(root);
//     }

//     bool search(int value)
//     {
//         return search(root, value);
//     }

//     void preOrder()
//     {
//         preOrder(root);
//     }

//     void inOrder()
//     {
//         inOrder(root);
//     }

//     void postOrder()
//     {
//         postOrder(root);
//     }

//     void levelOrder()
//     {
//         levelOrder(root);
//     }

//     void remove(int value)
//     {
//         root = remove(root, value);
//     }

//     int height()
//     {
//         return getHeight(root);
//     }

//     int countNodes()
//     {
//         return countNodes(root);
//     }

//     int countLeaves()
//     {
//         return countLeaves(root);
//     }

//     void destroy(Node *node)
//     {
//         if (node == nullptr)
//         {
//             return;
//         }

//         destroy(node->left);
//         destroy(node->right);

//         delete node;
//     }

//     void display()
//     {
//         if (root == nullptr)
//         {
//             cout << "Tree is empty\n";
//             return;
//         }

//         std::vector<std::vector<Node *>> levels;
//         queue<Node *> q;
//         q.push(root);

//         int treeHeight = getHeight(root);

//         for (int level = 0; level < treeHeight; level++)
//         {
//             int nodesInLevel = 1 << level;
//             std::vector<Node *> currentLevel;

//             for (int i = 0; i < nodesInLevel; i++)
//             {
//                 Node *current = q.front();
//                 q.pop();

//                 currentLevel.push_back(current);

//                 if (current != nullptr)
//                 {
//                     q.push(current->left);
//                     q.push(current->right);
//                 }
//                 else
//                 {
//                     q.push(nullptr);
//                     q.push(nullptr);
//                 }
//             }

//             levels.push_back(currentLevel);
//         }

//         for (int level = 0; level < treeHeight; level++)
//         {
//             int initialSpaces = (1 << (treeHeight - level - 1)) * 2;
//             int betweenSpaces = (1 << (treeHeight - level)) * 2;

//             for (int i = 0; i < initialSpaces; i++)
//                 cout << " ";

//             for (int i = 0; i < levels[level].size(); i++)
//             {
//                 Node *current = levels[level][i];

//                 if (current != nullptr)
//                     cout << current->data;
//                 else
//                     cout << " ";

//                 if (i < levels[level].size() - 1)
//                 {
//                     for (int j = 0; j < betweenSpaces; j++)
//                         cout << " ";
//                 }
//             }

//             cout << "\n";

//             if (level < treeHeight - 1)
//             {
//                 for (int i = 0; i < initialSpaces - 1; i++)
//                     cout << " ";

//                 for (int i = 0; i < levels[level].size(); i++)
//                 {
//                     Node *current = levels[level][i];

//                     if (current == nullptr)
//                     {
//                         cout << " ";
//                         cout << " ";
//                     }
//                     else
//                     {
//                         cout << (current->left ? '/' : ' ');
//                         cout << " ";
//                         cout << (current->right ? '\\' : ' ');
//                     }

//                     if (i < levels[level].size() - 1)
//                     {
//                         for (int j = 0; j < betweenSpaces - 2; j++)
//                             cout << " ";
//                     }
//                 }

//                 cout << "\n";
//             }
//         }
//     }
// };

// int main()
// {
//     AvlTree avlTree;

//     avlTree.insert(1);
//     avlTree.insert(2);
//     avlTree.insert(3);
//     avlTree.insert(4);
//     avlTree.display();
//     avlTree.insert(5);
//     avlTree.insert(6);
//     avlTree.insert(7);
//     avlTree.insert(8);

//     cout << "preOrder: ";
//     avlTree.preOrder();
//     cout << "\n";

//     cout << "inOrder: ";
//     avlTree.inOrder();
//     cout << "\n";

//     cout << "postOrder: ";
//     avlTree.postOrder();
//     cout << "\n";

//     cout << "levelOrder: ";
//     avlTree.levelOrder();
//     cout << "\n";

//     cout << "height: " << avlTree.height() << "\n";

//     cout << "nodes: " << avlTree.countNodes() << "\n";

//     cout << "leaves: " << avlTree.countLeaves() << "\n";

//     avlTree.remove(7);
//     avlTree.remove(1);

//     cout << "levelOrder: ";
//     avlTree.levelOrder();
//     cout << "\n";

//     cout << "minimum: " << avlTree.findMin()->data << "\n";

//     cout << "maximum: " << avlTree.findMax()->data << "\n";

//     return 0;
// }

/*
            ############################################# Practice round 2 #############################################
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
    int height;
    Node *left;
    Node *right;

    Node(int value)
    {
        data = value;
        left = right = nullptr;
        height = 1;
    }
};

class AvlTree
{
private:
    Node *root;

    void updateHeight(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int getBalanceFactor(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        return getHeight(node->left) - getHeight(node->right);
    }

    Node *leftRotate(Node *node)
    {
        Node *x = node;
        Node *y = node->right;
        Node *temp = y->left;

        y->left = x;
        x->right = temp;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node *rightRotate(Node *node)
    {
        Node *x = node;
        Node *y = node->left;
        Node *temp = y->right;

        y->right = x;
        x->left = temp;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node *insert(Node *node, int value)
    {
        if (node == nullptr)
        {
            return new Node(value);
        }
        else if (value < node->data)
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

        updateHeight(node);

        int balanceFactor = getBalanceFactor(node);

        // LL
        if (balanceFactor > 1 && value < node->left->data)
        {
            return rightRotate(node);
        }

        // RR
        if (balanceFactor < -1 && value > node->right->data)
        {
            return leftRotate(node);
        }

        // LR
        if (balanceFactor > 1 && value > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if (balanceFactor < -1 && value < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
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
            Node *temp = q.front();
            cout << temp->data << " ";
            q.pop();

            if (temp->left != nullptr)
            {

                q.push(temp->left);
            }
            if (temp->right != nullptr)
            {
                q.push(temp->right);
            }
        }
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

        updateHeight(node);

        int balanceFactor = getBalanceFactor(node);

        // LL
        if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
        {
            return rightRotate(node);
        }

        // RR
        if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
        {
            return leftRotate(node);
        }

        // LR
        if (balanceFactor > 1 && getBalanceFactor(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if (balanceFactor < -1 && getBalanceFactor(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node *findMin(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        Node *current = node;

        while (current->left != nullptr)
        {
            current = current->left;
        }

        return current;
    }

    Node *findMax(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        Node *current = node;

        while (current->right != nullptr)
        {
            current = current->right;
        }

        return current;
    }

    int getHeight(Node *node)
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
        return findMin(root);
    }

    Node *findMax()
    {
        return findMax(root);
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
        return getHeight(root);
    }

    int countNodes()
    {
        return countNodes(root);
    }

    int countLeaves()
    {
        return countLeaves(root);
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
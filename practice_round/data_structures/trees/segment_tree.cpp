/*
            ############################################# Practice round 1 #############################################
*/

// #include <iostream>
// #include <array>
// #include <algorithm>
// #include <climits>

// using std::array;
// using std::cout;
// using std::max;
// using std::min;

// struct Node
// {
//     int sum;
//     int min;
//     int max;
// };

// class SegmentTree
// {
// private:
//     const static int arrSize = 10;
//     array<int, arrSize> arr;
//     array<Node, arrSize * 4> sTree;

//     int getLeftChildIndex(int parentIndex)
//     {
//         return (parentIndex * 2) + 1;
//     }

//     int getRightChildIndex(int parentIndex)
//     {
//         return (parentIndex * 2) + 2;
//     }

//     Node merge(Node leftChild, Node rightChild)
//     {
//         Node result;

//         result.sum = leftChild.sum + rightChild.sum;
//         result.min = min(leftChild.min, rightChild.min);
//         result.max = max(leftChild.max, rightChild.max);

//         return result;
//     }

//     void buildSegmentTree(int treeIndex, int arrStartIndex, int arrEndIndex)
//     {
//         if (arrStartIndex == arrEndIndex)
//         {
//             sTree[treeIndex].sum = arr[arrStartIndex];
//             sTree[treeIndex].min = arr[arrStartIndex];
//             sTree[treeIndex].max = arr[arrStartIndex];

//             return;
//         }

//         int midIndex = (arrStartIndex + arrEndIndex) / 2;

//         // build left child
//         buildSegmentTree(getLeftChildIndex(treeIndex), arrStartIndex, midIndex);

//         // build right child
//         buildSegmentTree(getRightChildIndex(treeIndex), midIndex + 1, arrEndIndex);

//         sTree[treeIndex] = merge(sTree[getLeftChildIndex(treeIndex)], sTree[getRightChildIndex(treeIndex)]);
//     }

//     Node query(int treeIndex, int segmentLeft, int segmentRight, int arrLeftIndex, int arrRightIndex)
//     {
//         // no overlap between current segment and required range
//         if (segmentLeft > arrRightIndex || segmentRight < arrLeftIndex)
//         {
//             Node result;
//             result.sum = 0;
//             result.min = INT_MAX;
//             result.max = INT_MIN;

//             return result;
//         }

//         // current segment fully lies in requested range
//         if (segmentLeft >= arrLeftIndex && segmentRight <= arrRightIndex)
//         {
//             return sTree[treeIndex];
//         }

//         // current segment partially lies in requested range
//         int midIndex = (segmentLeft + segmentRight) / 2;

//         Node leftChild = query(getLeftChildIndex(treeIndex), segmentLeft, midIndex, arrLeftIndex, arrRightIndex);
//         Node rightChild = query(getRightChildIndex(treeIndex), midIndex + 1, segmentRight, arrLeftIndex, arrRightIndex);

//         return merge(leftChild, rightChild);
//     }

//     void update(int treeIndex, int segmentLeftIndex, int segmentRightIndex, int arrUpdateIndex, int value)
//     {
//         if (segmentLeftIndex == segmentRightIndex)
//         {
//             arr[arrUpdateIndex] = value;

//             Node nodeToBeUpdated;

//             nodeToBeUpdated.sum = arr[arrUpdateIndex];
//             nodeToBeUpdated.min = arr[arrUpdateIndex];
//             nodeToBeUpdated.max = arr[arrUpdateIndex];

//             sTree[treeIndex] = nodeToBeUpdated;
//             return;
//         }

//         int midIndex = (segmentLeftIndex + segmentRightIndex) / 2;

//         if (arrUpdateIndex <= midIndex)
//         {

//             update(getLeftChildIndex(treeIndex), segmentLeftIndex, midIndex, arrUpdateIndex, value);
//         }
//         else
//         {
//             update(getRightChildIndex(treeIndex), midIndex + 1, segmentRightIndex, arrUpdateIndex, value);
//         }

//         sTree[treeIndex] = merge(sTree[getLeftChildIndex(treeIndex)], sTree[getRightChildIndex(treeIndex)]);
//     }

// public:
//     SegmentTree()
//     {
//         arr = {2, 4, 5, 7, 8, 9, 1, 6, 3, 11};

//         buildSegmentTree(0, 0, (arrSize - 1));
//     }

//     int rangeSum(int arrLeftIndex, int arrRightIndex)
//     {
//         if (arrLeftIndex < 0 || arrRightIndex > (arrSize - 1) || arrLeftIndex > arrRightIndex)
//         {
//             cout << "Invalid indexes";
//             return INT_MIN;
//         }

//         // start with full segment
//         return query(0, 0, arrSize - 1, arrLeftIndex, arrRightIndex).sum;
//     }

//     int rangeMinimum(int arrLeftIndex, int arrRightIndex)
//     {
//         if (arrLeftIndex < 0 || arrRightIndex > (arrSize - 1) || arrLeftIndex > arrRightIndex)
//         {
//             cout << "Invalid indexes";
//             return INT_MAX;
//         }

//         // start with full segment
//         return query(0, 0, arrSize - 1, arrLeftIndex, arrRightIndex).min;
//     }

//     int rangeMaximum(int arrLeftIndex, int arrRightIndex)
//     {
//         if (arrLeftIndex < 0 || arrRightIndex > (arrSize - 1) || arrLeftIndex > arrRightIndex)
//         {
//             cout << "Invalid indexes";
//             return INT_MAX;
//         }

//         // start with full segment
//         return query(0, 0, arrSize - 1, arrLeftIndex, arrRightIndex).max;
//     }

//     void update(int arrUpdateIndex, int value)
//     {
//         if (arrUpdateIndex < 0 || arrUpdateIndex > arrSize - 1)
//         {
//             cout << "Invalid index\n";
//             return;
//         }

//         update(0, 0, arrSize - 1, arrUpdateIndex, value);
//     }

//     void displayTree()
//     {
//         for (Node node : sTree)
//         {
//             cout << "[sum: " << node.sum << " | min:" << node.min << " | max:" << node.max << " ]\n";
//         }
//     }

//     void displayArray()
//     {
//         for (int value : arr)
//         {
//             cout << value << " | ";
//         }
//         cout << "\n";
//     }
// };

// int main()
// {
//     SegmentTree tree;

//     cout << "Initial array values:\n";
//     tree.displayArray();

//     cout << "Sum [0, 9]: "
//          << tree.rangeSum(0, 9) << '\n';

//     cout << "Minimum [0, 9]: "
//          << tree.rangeMinimum(0, 9) << '\n';

//     cout << "Maximum [0, 9]: "
//          << tree.rangeMaximum(0, 9) << '\n';

//     cout << "\nRange [2, 6]:\n";

//     cout << "Sum: "
//          << tree.rangeSum(2, 6) << '\n';

//     cout << "Minimum: "
//          << tree.rangeMinimum(2, 6) << '\n';

//     cout << "Maximum: "
//          << tree.rangeMaximum(2, 6) << '\n';

//     cout << "\nUpdating index 4 from 8 to 34...\n";

//     tree.update(4, 34);

//     cout << "\nRange [2, 6] after update:\n";

//     cout << "Sum: "
//          << tree.rangeSum(2, 6) << '\n';

//     cout << "Minimum: "
//          << tree.rangeMinimum(2, 6) << '\n';

//     cout << "Maximum: "
//          << tree.rangeMaximum(2, 6) << '\n';

//     return 0;
// }

/*
            ############################################# Practice round 2 #############################################
*/

#include <iostream>
#include <array>
#include <climits>
#include <algorithm>

using std::array;
using std::cout;
using std::max;
using std::min;

struct Node
{
    int sum;
    int min;
    int max;
};

class SegmentTree
{
private:
    const static int arrSize = 10;
    array<int, arrSize> arr;
    array<Node, arrSize * 4> sTree;

    int getLeftChild(int parentIndex)
    {
        return parentIndex * 2 + 1;
    }

    int getRightChild(int parentIndex)
    {
        return parentIndex * 2 + 2;
    }

    Node merge(Node leftChild, Node rightChild)
    {
        Node newNode;

        newNode.sum = leftChild.sum + rightChild.sum;
        newNode.min = min(leftChild.min, rightChild.min);
        newNode.max = max(leftChild.max, rightChild.max);

        return newNode;
    }

    void buildSegmentTree(int treeIndex, int segmentLeftIndex, int segmentRightIndex)
    {
        if (segmentLeftIndex == segmentRightIndex)
        {
            sTree[treeIndex].sum = arr[segmentLeftIndex];
            sTree[treeIndex].min = arr[segmentLeftIndex];
            sTree[treeIndex].max = arr[segmentLeftIndex];

            return;
        }

        int midIndex = (segmentLeftIndex + segmentRightIndex) / 2;

        buildSegmentTree(getLeftChild(treeIndex), segmentLeftIndex, midIndex);
        buildSegmentTree(getRightChild(treeIndex), midIndex + 1, segmentRightIndex);

        sTree[treeIndex] = merge(sTree[getLeftChild(treeIndex)], sTree[getRightChild(treeIndex)]);
    }

    Node query(int treeIndex, int segmentLeftIndex, int segmentRightIndex, int arrLeftIndex, int arrRightIndex)
    {
        // no overlap of the current segment in range
        if (segmentLeftIndex > arrRightIndex || segmentRightIndex < arrLeftIndex)
        {
            Node node;

            node.sum = 0;
            node.min = INT_MAX;
            node.max = INT_MIN;

            return node;
        }

        // current segment lies fully within the range
        if (segmentLeftIndex >= arrLeftIndex && segmentRightIndex <= arrRightIndex)
        {
            return sTree[treeIndex];
        }

        // current segment partially lies within the range
        int midIndex = (segmentLeftIndex + segmentRightIndex) / 2;

        Node leftChild = query(getLeftChild(treeIndex), segmentLeftIndex, midIndex, arrLeftIndex, arrRightIndex);
        Node rightChild = query(getRightChild(treeIndex), midIndex + 1, segmentRightIndex, arrLeftIndex, arrRightIndex);

        return merge(leftChild, rightChild);
    }

    void update(int treeIndex, int segmentLeftIndex, int segmentRightIndex, int updateArrIndex, int newValue)
    {
        // the goal is to rebuilt the portion of the tree after update, so it's basically the built method with array update
        if (segmentLeftIndex == segmentRightIndex)
        {
            arr[updateArrIndex] = newValue;

            sTree[treeIndex].sum = arr[segmentLeftIndex];
            sTree[treeIndex].min = arr[segmentLeftIndex];
            sTree[treeIndex].max = arr[segmentLeftIndex];

            return;
        }

        int midIndex = (segmentLeftIndex + segmentRightIndex) / 2;

        if (updateArrIndex <= midIndex)
        {

            update(getLeftChild(treeIndex), segmentLeftIndex, midIndex, updateArrIndex, newValue);
        }
        else
        {
            update(getRightChild(treeIndex), midIndex + 1, segmentRightIndex, updateArrIndex, newValue);
        }

        sTree[treeIndex] = merge(sTree[getLeftChild(treeIndex)], sTree[getRightChild(treeIndex)]);
    }

public:
    SegmentTree()
    {
        arr = {2, 4, 5, 7, 8, 9, 1, 6, 3, 11};

        buildSegmentTree(0, 0, (arrSize - 1));
    }

    int rangeSum(int arrLeftIndex, int arrRightIndex)
    {
        if (arrLeftIndex < 0 || arrRightIndex > arrSize - 1)
        {
            return INT_MIN;
        }

        return query(0, 0, arrSize - 1, arrLeftIndex, arrRightIndex).sum;
    }

    int rangeMin(int arrLeftIndex, int arrRightIndex)
    {
        if (arrLeftIndex < 0 || arrRightIndex > arrSize - 1)
        {
            return INT_MAX;
        }

        return query(0, 0, arrSize - 1, arrLeftIndex, arrRightIndex).min;
    }

    int rangeMax(int arrLeftIndex, int arrRightIndex)
    {
        if (arrLeftIndex < 0 || arrRightIndex > arrSize - 1)
        {
            return INT_MIN;
        }

        return query(0, 0, arrSize - 1, arrLeftIndex, arrRightIndex).max;
    }

    void update(int updateArrIndex, int newValue)
    {
        if (updateArrIndex < 0 || updateArrIndex > arrSize - 1)
        {
            return;
        }

        update(0, 0, arrSize - 1, updateArrIndex, newValue);
    }

    void displayTree()
    {
        for (Node node : sTree)
        {
            cout << "[sum: " << node.sum << " | min:" << node.min << " | max:" << node.max << " ]\n";
        };
    }

    void displayArray()
    {
        for (int value : arr)
        {
            cout << value << " | ";
        }

        cout << "\n";
    }
};

int main()
{
    SegmentTree tree;

    cout << "Initial array values:\n";
    tree.displayArray();

    cout << "Sum [0, 9]: "
         << tree.rangeSum(0, 9) << '\n';

    cout << "Minimum [0, 9]: "
         << tree.rangeMin(0, 9) << '\n';

    cout << "Maximum [0, 9]: "
         << tree.rangeMax(0, 9) << '\n';

    cout << "\nRange [2, 6]:\n";

    cout << "Sum: "
         << tree.rangeSum(2, 6) << '\n';

    cout << "Minimum: "
         << tree.rangeMin(2, 6) << '\n';

    cout << "Maximum: "
         << tree.rangeMax(2, 6) << '\n';

    cout << "\nUpdating index 4 from 8 to 34...\n";

    tree.update(4, 34);

    cout << "\nRange [2, 6] after update:\n";

    cout << "Sum: "
         << tree.rangeSum(2, 6) << '\n';

    cout << "Minimum: "
         << tree.rangeMin(2, 6) << '\n';

    cout << "Maximum: "
         << tree.rangeMax(2, 6) << '\n';

    return 0;
}
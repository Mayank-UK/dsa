/*
            ############################################# Practice round 1 #############################################
*/

// #include <iostream>
// #include <vector>
// #include <climits>

// using std::cout;
// using std::vector;

// class MinHeap
// {
// private:
//     // When the MinHeap object is destroyed, its vector member is automatically destroyed, which releases its allocated memory.
//     vector<int> heap;

//     int parent(int index)
//     {
//         return (index - 1) / 2;
//     }

//     int leftChild(int index)
//     {
//         return (index * 2 + 1);
//     }

//     int rightChild(int index)
//     {
//         return (index * 2 + 2);
//     }

//     void heapifyUp(int index)
//     {
//         while (index > 0 && heap[parent(index)] > heap[index])
//         {
//             int temp = heap[parent(index)];
//             heap[parent(index)] = heap[index];
//             heap[index] = temp;

//             index = parent(index);
//         }
//     }

//     void heapifyDown(int index)
//     {

//         while (true)
//         {
//             int minimumValueIndex = index;

//             if (leftChild(index) < heap.size() && heap[leftChild(index)] < heap[minimumValueIndex])
//             {
//                 minimumValueIndex = leftChild(index);
//             }

//             if (rightChild(index) < heap.size() && heap[rightChild(index)] < heap[minimumValueIndex])
//             {
//                 minimumValueIndex = rightChild(index);
//             }

//             if (minimumValueIndex == index)
//             {
//                 break;
//             }

//             int temp = heap[index];
//             heap[index] = heap[minimumValueIndex];
//             heap[minimumValueIndex] = temp;

//             index = minimumValueIndex;
//         }
//     }

// public:
//     void insert(int value)
//     {
//         heap.push_back(value);
//         heapifyUp(heap.size() - 1);
//     }

//     int extractMin()
//     {
//         if (heap.empty())
//         {
//             return INT_MIN;
//         }

//         int extractedValue = heap[0];
//         heap[0] = heap[heap.size() - 1];

//         heap.pop_back();

//         if (!heap.empty())
//         {
//             heapifyDown(0);
//         }

//         return extractedValue;
//     }

//     int peek()
//     {
//         if (heap.empty())
//         {
//             return INT_MIN;
//         }

//         return heap[0];
//     }

//     bool search(int value)
//     {
//         for (int num : heap)
//         {
//             if (num == value)
//             {
//                 return true;
//             }
//         }

//         return false;
//     }

//     bool remove(int value)
//     {
//         if (heap.empty())
//         {
//             return false;
//         }

//         int index = -1;

//         for (int i = 0; i < heap.size(); i++)
//         {
//             if (value == heap[i])
//             {
//                 index = i;
//                 break;
//             }
//         }

//         if (index == -1)
//         {
//             return false;
//         }

//         heap[index] = heap.back();
//         heap.pop_back();

//         if (index < heap.size())
//         {
//             if (index > 0 && heap[index] < heap[parent(index)])
//             {
//                 heapifyUp(index);
//             }
//             else
//             {
//                 heapifyDown(index);
//             }
//         }

//         return true;
//     }

//     void display()
//     {
//         for (int num : heap)
//         {
//             cout << num << " ";
//         }

//         cout << "\n";
//     }

//     int size()
//     {
//         return heap.size();
//     }

//     void buildHeap(vector<int> values)
//     {
//         heap = values;

//         if (values.empty())
//         {
//             return;
//         }

//         for (int i = parent(heap.size() - 1); i >= 0; --i)
//         {
//             heapifyDown(i);
//         }
//     }

//     void heapSort()
//     {
//         MinHeap temp;

//         temp.heap = heap;

//         for (int num : heap)
//         {
//             cout << temp.extractMin() << " ";
//         }

//         cout << "\n";
//     }
// };

// int main()
// {
//     MinHeap heap;

//     // Insert
//     heap.insert(10);
//     heap.insert(5);
//     heap.insert(20);
//     heap.insert(3);
//     heap.insert(8);
//     heap.insert(15);
//     heap.insert(1);

//     cout << "Heap after insertion: ";
//     heap.display();

//     // Peek
//     cout << "Minimum element: " << heap.peek() << "\n";

//     // Size
//     cout << "Heap size: " << heap.size() << "\n";

//     // Search / Remove
//     cout << "Removing 8...\n";
//     cout << "Removed: " << (heap.remove(8) ? "Yes" : "No") << "\n";

//     cout << "Heap after removing 8: ";
//     heap.display();

//     // Extract minimum
//     cout << "Extracted minimum: " << heap.extractMin() << "\n";

//     cout << "Heap after extractMin: ";
//     heap.display();

//     // Build heap
//     vector<int> values = {20, 5, 15, 3, 10, 8, 1};

//     heap.buildHeap(values);

//     cout << "\nHeap after buildHeap: ";
//     heap.display();

//     // Heap sort
//     cout << "Heap sort: ";
//     heap.heapSort();

//     return 0;
// }

/*
            ############################################# Practice round 2 #############################################
*/

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

class MinHeap
{
private:
    vector<int> heap;

    int parent(int index)
    {
        return (index - 1) / 2;
    }

    int leftChild(int index)
    {
        return (index * 2 + 1);
    }

    int rightChild(int index)
    {
        return (index * 2 + 2);
    }

    void heapifyUp(int index)
    {
        while (index > 0 && heap[parent(index)] > heap[index])
        {
            int temp = heap[index];
            heap[index] = heap[parent(index)];
            heap[parent(index)] = temp;

            index = parent(index);
        }
    }

    void heapifyDown(int index)
    {
        while (true)
        {
            int minimumValueIndex = index;
            int left = leftChild(index);
            int right = rightChild(index);

            if (left < heap.size() && heap[left] < heap[minimumValueIndex])
            {
                minimumValueIndex = left;
            }

            if (right < heap.size() && heap[right] < heap[minimumValueIndex])
            {
                minimumValueIndex = right;
            }

            if (minimumValueIndex == index)
            {
                return;
            }

            int temp = heap[index];
            heap[index] = heap[minimumValueIndex];
            heap[minimumValueIndex] = temp;

            index = minimumValueIndex;
        }
    }

public:
    bool insert(int value)
    {
        heap.push_back(value);

        if (heap.size() > 1)
        {
            heapifyUp(heap.size() - 1);
        }

        return true;
    }

    int extractMin()
    {
        if (heap.empty())
        {
            return INT_MIN;
        }

        int extractedValue = heap[0];

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
        {
            heapifyDown(0);
        }

        return extractedValue;
    }

    bool remove(int value)
    {
        if (heap.empty())
        {
            return false;
        }

        int index = -1;

        for (int i = 0; i < heap.size(); i++)
        {
            if (heap[i] == value)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            return false;
        }

        heap[index] = heap.back();
        heap.pop_back();

        if (index < heap.size())
        {
            if (index > 0 && heap[index] < heap[parent(index)])
            {
                heapifyUp(index);
            }
            else
            {
                heapifyDown(index);
            }
        }

        return true;
    }

    int peek()
    {
        if (heap.empty())
        {
            return INT_MIN;
        }

        return heap[0];
    }

    int size()
    {
        return heap.size();
    }

    void display()
    {
        for (int num : heap)
        {
            cout << num << " ";
        }

        cout << "\n";
    }

    void buildHeap(vector<int> &values)
    {
        heap = values;

        if (heap.empty())
        {
            return;
        }

        for (int i = parent(heap.size() - 1); i >= 0; i--)
        {
            heapifyDown(i);
        }
    }

    void heapSort()
    {
        MinHeap temp;

        temp.heap = heap;

        while (!temp.heap.empty())
        {
            cout << temp.extractMin() << " ";
        }

        cout << "\n";
    }
};

int main()
{
    MinHeap heap;

    // Insert
    heap.insert(10);
    heap.insert(5);
    heap.insert(20);
    heap.insert(3);
    heap.insert(8);
    heap.insert(15);
    heap.insert(1);

    cout << "Heap after insertion: ";
    heap.display();

    // Peek
    cout << "Minimum element: " << heap.peek() << "\n";

    // Size
    cout << "Heap size: " << heap.size() << "\n";

    // Search / Remove
    cout << "Removing 8...\n";
    cout << "Removed: " << (heap.remove(8) ? "Yes" : "No") << "\n";

    cout << "Heap after removing 8: ";
    heap.display();

    // Extract minimum
    cout << "Extracted minimum: " << heap.extractMin() << "\n";

    cout << "Heap after extractMin: ";
    heap.display();

    // Build heap
    vector<int> values = {20, 5, 15, 3, 10, 8, 1};

    heap.buildHeap(values);

    cout << "\nHeap after buildHeap: ";
    heap.display();

    // Heap sort
    cout << "Heap sort: ";
    heap.heapSort();

    return 0;
}
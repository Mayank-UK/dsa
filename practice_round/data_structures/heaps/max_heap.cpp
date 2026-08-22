/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
#include <vector>
#include <climits>

using std::cout;
using std::vector;

class MaxHeap
{
private:
    vector<int> heap;

    int parent(int index)
    {
        return (index - 1) / 2;
    }

    int leftChild(int index)
    {
        return index * 2 + 1;
    }

    int rightChild(int index)
    {
        return index * 2 + 2;
    }

    void heapifyUp(int index)
    {
        while (index > 0 && heap[parent(index)] < heap[index])
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
            int maximumIndex = index;
            int left = leftChild(index);
            int right = rightChild(index);

            if (left < heap.size() && heap[left] > heap[maximumIndex])
            {
                maximumIndex = left;
            }

            if (right < heap.size() && heap[right] > heap[maximumIndex])
            {
                maximumIndex = right;
            }

            if (maximumIndex == index)
            {
                return;
            }

            int temp = heap[index];
            heap[index] = heap[maximumIndex];
            heap[maximumIndex] = temp;

            index = maximumIndex;
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

    int extractMax()
    {
        if (heap.empty())
        {
            return INT_MAX;
        }

        int max = heap[0];

        heap[0] = heap[heap.size() - 1];
        heap.pop_back();

        if (!heap.empty())
        {
            heapifyDown(0);
        }

        return max;
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
            if (value == heap[i])
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            return false;
        }

        heap[index] = heap[heap.size() - 1];
        heap.pop_back();

        if (index < heap.size())
        {
            if (index > 0 && heap[index] > heap[parent(index)])
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
        if (heap.empty())
        {
            return;
        }

        for (int num : heap)
        {
            cout << num << " ";
        }

        cout << "\n";
    }

    void buildHeap(vector<int> values)
    {
        heap = values;

        if (heap.empty())
        {
            return;
        }

        for (int i = parent((heap.size() - 1)); i >= 0; i--)
        {
            heapifyDown(i);
        }
    }

    void heapSort()
    {
        MaxHeap temp;

        temp.heap = heap;

        while (!temp.heap.empty())
        {
            cout << temp.extractMax() << " ";
        }

        cout << "\n";
    }
};

int main()
{
    MaxHeap heap;

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
    cout << "Maximum element: " << heap.peek() << "\n";

    // Size
    cout << "Heap size: " << heap.size() << "\n";

    // Search / Remove
    cout << "Removing 8...\n";
    cout << "Removed: " << (heap.remove(8) ? "Yes" : "No") << "\n";

    cout << "Heap after removing 8: ";
    heap.display();

    // Extract minimum
    cout << "Extracted maximum: " << heap.extractMax() << "\n";

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
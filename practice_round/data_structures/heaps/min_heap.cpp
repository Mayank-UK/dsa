/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
#include <vector>
#include <climits>

using std::cout;
using std::vector;

class MinHeap
{
private:
    // When the MinHeap object is destroyed, its vector member is automatically destroyed, which releases its allocated memory.
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
            int temp = heap[parent(index)];
            heap[parent(index)] = heap[index];
            heap[index] = temp;

            index = parent(index);
        }
    }

    void heapifyDown(int index)
    {

        while (true)
        {
            int minimumValueIndex = index;

            if (leftChild(index) < heap.size() && heap[leftChild(index)] < heap[minimumValueIndex])
            {
                minimumValueIndex = leftChild(index);
            }

            if (rightChild(index) < heap.size() && heap[rightChild(index)] < heap[minimumValueIndex])
            {
                minimumValueIndex = rightChild(index);
            }

            if (minimumValueIndex == index)
            {
                break;
            }

            int temp = heap[index];
            heap[index] = heap[minimumValueIndex];
            heap[minimumValueIndex] = temp;

            index = minimumValueIndex;
        }
    }

public:
    void insert(int value)
    {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int extractMin()
    {
        if (heap.empty())
        {
            return INT_MIN;
        }

        int extractedValue = heap[0];
        heap[0] = heap[heap.size() - 1];

        heap.pop_back();

        if (!heap.empty())
        {
            heapifyDown(0);
        }

        return extractedValue;
    }

    int peek()
    {
        if (heap.empty())
        {
            return INT_MIN;
        }

        return heap[0];
    }

    bool search(int value)
    {
        for (int num : heap)
        {
            if (num == value)
            {
                return true;
            }
        }

        return false;
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

    void display()
    {
        for (int num : heap)
        {
            cout << num << " ";
        }

        cout << "\n";
    }

    int size()
    {
        return heap.size();
    }

    void buildHeap(vector<int> values)
    {
        heap = values;

        if (values.empty())
        {
            return;
        }

        for (int i = parent(heap.size() - 1); i >= 0; --i)
        {
            heapifyDown(i);
        }
    }

    void heapSort()
    {
        MinHeap temp;

        temp.heap = heap;

        for (int num : heap)
        {
            cout << temp.extractMin() << " ";
        }

        cout << "\n";
    }
};

int main() {}
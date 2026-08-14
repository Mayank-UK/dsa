/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
#include <vector>
#include <climits>

using std::cout;
using std::vector;

class PriorityQueue
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
        while (index > 0 && heap[index] > heap[parent(index)])
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
            int maxValueIndex = index;
            int left = leftChild(index);
            int right = rightChild(index);

            if (left < heap.size() && heap[left] > heap[maxValueIndex])
            {
                maxValueIndex = left;
            }

            if (right < heap.size() && heap[right] > heap[maxValueIndex])
            {
                maxValueIndex = right;
            }

            if (maxValueIndex == index)
            {
                return;
            }

            int temp = heap[index];
            heap[index] = heap[maxValueIndex];
            heap[maxValueIndex] = temp;

            index = maxValueIndex;
        }
    }

public:
    bool push(int value)
    {
        heap.push_back(value);

        if (heap.size() > 1)
        {
            heapifyUp(heap.size() - 1);
        }

        return true;
    }

    // remove the highest priority element
    int pop()
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

        heap[index] = heap[heap.size() - 1];
        heap.pop_back();

        // handle edge case where if element is deleted from edge then index may lie outside array size after pop operation
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

    int top()
    {
        if (heap.empty())
        {
            return INT_MAX;
        }

        return heap[0];
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
};

int main()
{
    PriorityQueue pq;

    pq.push(40);
    pq.push(10);
    pq.push(70);
    pq.push(25);
    pq.push(90);
    pq.push(50);
    pq.push(30);

    cout << "Heap: ";
    pq.display();

    cout << "Top: " << pq.top() << "\n";

    cout << "Popped: " << pq.pop() << "\n";

    cout << "Heap after pop: ";
    pq.display();

    cout << "Removing 25: " << pq.remove(25) << "\n";

    cout << "Heap after remove: ";
    pq.display();

    cout << "Top: " << pq.top() << "\n";

    return 0;
}
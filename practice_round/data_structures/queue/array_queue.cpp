/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
using std::cout;

class ArrayQueue
{
private:
    int *queue;
    int queueMaxCapacity;
    int frontIndex;
    int rearIndex;
    int length;

public:
    ArrayQueue(int maxCapacity)
    {
        if (maxCapacity <= 0)
        {
            queueMaxCapacity = 1;
        }
        else
        {
            queueMaxCapacity = maxCapacity;
        }

        queue = new int[queueMaxCapacity];
        frontIndex = rearIndex = -1;
        length = 0;
    }

    ArrayQueue(const ArrayQueue &) = delete;
    ArrayQueue &operator=(const ArrayQueue &) = delete;

    ~ArrayQueue()
    {
        delete[] queue;
    }

    bool enqueue(int value)
    {
        /*
            1. If queue is full, extend queue, insert at rearIndex and return true
            2. For other cases, insert at rearIndex, update rearIndex++, length++, return true
        */

        if (isEmpty())
        {
            frontIndex = rearIndex = 0;
            queue[0] = value;
            length++;
            return true;
        }

        if (isFull())
        {
            queueMaxCapacity *= 2;
            int *newQueue = new int[queueMaxCapacity];

            // length starts from 1, whereas i from 0, i < length will iterate
            for (int i = 0; i < length; i++)
            {
                newQueue[i] = queue[frontIndex + i];
            }

            delete[] queue;
            queue = newQueue;
            frontIndex = 0;
            rearIndex = length - 1;
        }

        /*
            capacity = 3

            1. []
                frontIndex = rearIndex = 0
                queue[0] = value
                rearIndex = 1
                length = 1
            2. [1]
                queue[1] = value
                rearIndex = 2
                length = 2
            3. [1->2]
                queue[2] = value
                rearIndex = 3
                length = 3
            4. [1->2->3]
                length is full
        */

        queue[++rearIndex] = value;
        length++;

        return true;
    }

    bool dequeue(int &dequeuedValue)
    {
        /*
            1. If queue is empty, return false
            2. For other cases, update referenceValue, update frontIndex++, update length--, return true
        */

        if (isEmpty())
        {
            return false;
        }

        dequeuedValue = queue[frontIndex++];
        length--;

        // indexes start from 0, whereas capacity from 1
        if (frontIndex > 0 && rearIndex + 1 == queueMaxCapacity)
        {
            int *newQueue = new int[queueMaxCapacity];

            for (int i = 0; i < length; i++)
            {
                newQueue[i] = queue[frontIndex + i];
            }

            delete[] queue;
            queue = newQueue;

            frontIndex = 0;
            rearIndex = length - 1;
        }

        if (length == 0)
        {
            frontIndex = rearIndex = -1;
        }

        return true;
    }

    bool peek(int &frontValue)
    {
        /*
            1. If queue is empty, return false
            2. For other cases, update referenceValue with element at frontIndex, return true
        */

        if (isEmpty())
        {
            return false;
        }

        frontValue = queue[frontIndex];
        return true;
    }

    void clear()
    {
        frontIndex = rearIndex = -1;
        length = 0;
        cout << "Queue cleared\n";
    }

    void print()
    {
        for (int i = frontIndex; i <= rearIndex; i++)
        {
            cout << queue[i] << "->";
        }

        cout << "\n";
    }

    bool isEmpty()
    {
        return length == 0;
    }

    bool isFull()
    {
        return length == queueMaxCapacity;
    }

    int size()
    {
        cout << "Size is: " << length << "\n";
        return length;
    }
};

void dequeuedPrint(bool isNotEmpty, int dequeuedValue);
void peekPrint(bool isNotEmpty, int frontValue);

int main()
{
    ArrayQueue arrayQueue(5);
    bool dequeuedOperationBool;
    bool peekedOperationBool;
    int dequeuedValue;
    int peekedValue;

    arrayQueue.enqueue(1);
    arrayQueue.print();

    arrayQueue.enqueue(2);
    arrayQueue.print();

    dequeuedOperationBool = arrayQueue.dequeue(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    dequeuedOperationBool = arrayQueue.dequeue(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    dequeuedOperationBool = arrayQueue.dequeue(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    peekedOperationBool = arrayQueue.peek(peekedValue);
    peekPrint(peekedOperationBool, peekedValue);

    arrayQueue.enqueue(1);
    arrayQueue.print();

    peekedOperationBool = arrayQueue.peek(peekedValue);
    peekPrint(peekedOperationBool, peekedValue);

    return 0;
}

void dequeuedPrint(bool isNotEmpty, int dequeuedValue)
{
    if (isNotEmpty)
    {
        cout << "Dequed value: " << dequeuedValue << "\n";
    }
    else
    {
        cout << "Queue is empty\n";
    }
}

void peekPrint(bool isNotEmpty, int frontValue)
{
    if (isNotEmpty)
    {
        cout << "Element at front : " << frontValue << "\n";
    }
    else
    {
        cout << "Queue is empty\n";
    }
}
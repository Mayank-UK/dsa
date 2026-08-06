/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
using std::cout;

class CircularQueue
{
private:
    int *queue;
    int queueMaxCapacity;
    int frontIndex;
    int rearIndex;
    int length;

public:
    CircularQueue(int maxCapacity)
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

    ~CircularQueue()
    {
        delete[] queue;
    }

    CircularQueue(const CircularQueue &) = delete;
    CircularQueue &operator=(const CircularQueue &) = delete;

    bool enqueue(int value)
    {
        /*
            1. If queue is empty
                frontIndex = rearIndex = 0
                Insert value
                length++
                return true

            2. If queue is full
                Double capacity
                Copy queue in logical order
                Reset front = 0
                Reset rear = length - 1

            3. Move rear one step forward using modulo

            4. Insert value
               length++
               return true
        */

        if (isEmpty())
        {
            frontIndex = rearIndex = 0;
            queue[rearIndex] = value;
            length++;
            return true;
        }

        if (isFull())
        {
            int oldCapacity = queueMaxCapacity;
            queueMaxCapacity *= 2;

            int *newQueue = new int[queueMaxCapacity];

            for (int i = 0; i < length; i++)
            {
                newQueue[i] = queue[(frontIndex + i) % oldCapacity];
            }

            delete[] queue;
            queue = newQueue;

            frontIndex = 0;
            rearIndex = length - 1;
        }

        rearIndex = (rearIndex + 1) % queueMaxCapacity;

        queue[rearIndex] = value;
        length++;

        return true;
    }

    bool dequeue(int &dequeuedValue)
    {
        /*
            1. If queue is empty
                return false

            2. Store front element

            3. If queue has only one element
                Reset front and rear
                length--
                return true

            4. Move front one step using modulo

            5. length--
               return true
        */

        if (isEmpty())
        {
            return false;
        }

        dequeuedValue = queue[frontIndex];

        if (length == 1)
        {
            frontIndex = rearIndex = -1;
            length--;
            return true;
        }

        frontIndex = (frontIndex + 1) % queueMaxCapacity;
        length--;

        return true;
    }

    bool peek(int &peekedValue)
    {
        /*
            1. If empty, return false
            2. For other cases, set referenced variable to queue[frontIndex], return true
        */

        if (isEmpty())
        {
            return false;
        }

        peekedValue = queue[frontIndex];
        return true;
    }

    void print()
    {
        if (isEmpty())
        {
            cout << "Queue is empty\n";
            return;
        }

        for (int i = 0; i < length; i++)
        {
            cout << queue[(frontIndex + i) % queueMaxCapacity];

            if (i != length - 1)
                cout << "->";
        }

        cout << "\n";
    }

    bool isEmpty()
    {
        /*
            return length == 0
        */

        return length == 0;
    }

    bool isFull()
    {
        /*
            return length == queueMaxCapacity
        */

        return length == queueMaxCapacity;
    }

    void clear()
    {
        /*
            Set frontIndex = rearIndex = -1, and length = 0
        */

        frontIndex = rearIndex = -1;
        length = 0;
    }
};

void dequeuedPrint(bool isNotEmpty, int dequeuedValue);
void peekPrint(bool isNotEmpty, int frontValue);

int main()
{
    CircularQueue circularQueue(5);
    bool dequeuedOperationBool;
    bool peekedOperationBool;
    int dequeuedValue;
    int peekedValue;

    circularQueue.enqueue(1);
    circularQueue.print();

    circularQueue.enqueue(2);
    circularQueue.print();

    dequeuedOperationBool = circularQueue.dequeue(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    dequeuedOperationBool = circularQueue.dequeue(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    dequeuedOperationBool = circularQueue.dequeue(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    peekedOperationBool = circularQueue.peek(peekedValue);
    peekPrint(peekedOperationBool, peekedValue);

    circularQueue.enqueue(1);
    circularQueue.print();

    peekedOperationBool = circularQueue.peek(peekedValue);
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
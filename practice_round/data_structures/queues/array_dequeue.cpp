/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
using std::cout;

class ArrayDequeue
{
private:
    int queueMaxCapacity;
    int *queue;
    int frontIndex;
    int rearIndex;
    int length;

public:
    ArrayDequeue(int maxCapacity)
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

    ~ArrayDequeue()
    {
        delete[] queue;
        frontIndex = rearIndex = -1;
        length = 0;
    }

    bool pushFront(int value)
    {
        if (isEmpty())
        {
            frontIndex = rearIndex = 0;
            queue[0] = value;

            length++;

            return true;
        }

        if (isFull())
        {
            cout << "Dequeue is full\n";
            return false;
        }

        int newFrontIndex = (frontIndex - 1 + queueMaxCapacity) % queueMaxCapacity;

        queue[newFrontIndex] = value;
        frontIndex = newFrontIndex;
        length++;

        return true;
    }

    bool pushRear(int value)
    {
        if (isEmpty())
        {
            frontIndex = rearIndex = 0;
            queue[0] = value;

            length++;

            return true;
        }

        if (isFull())
        {
            cout << "Dequeue is full\n";
            return false;
        }

        int newRearIndex = (rearIndex + 1) % queueMaxCapacity;

        queue[newRearIndex] = value;
        rearIndex = newRearIndex;
        length++;

        return true;
    }

    bool popFront(int &poppedValue)
    {
        if (isEmpty())
        {
            return false;
        }

        poppedValue = queue[frontIndex];

        int nextFrontIndex = (frontIndex + 1 + queueMaxCapacity) % queueMaxCapacity;

        frontIndex = nextFrontIndex;
        length--;

        if (length == 0)
        {
            frontIndex = rearIndex = -1;
        }

        return true;
    }

    bool popRear(int &poppedValue)
    {
        if (isEmpty())
        {
            return false;
        }

        poppedValue = queue[rearIndex];

        int nextRearIndex = (rearIndex - 1 + queueMaxCapacity) % queueMaxCapacity;

        rearIndex = nextRearIndex;
        length--;

        if (length == 0)
        {
            frontIndex = rearIndex = -1;
        }

        return true;
    }

    bool peek(int &peekedValue)
    {
        if (isEmpty())
        {
            return false;
        }

        peekedValue = queue[frontIndex];

        return true;
    }

    bool clear()
    {
        frontIndex = rearIndex = -1;
        length = 0;

        return true;
    }

    void print() const
    {
        for (int i = 0; i < length; i++)
        {
            cout << queue[(frontIndex + i) % queueMaxCapacity] << "->";
        }

        cout << "\n";
    }

    bool isEmpty() const
    {
        return length == 0;
    }

    bool isFull() const
    {
        return length == queueMaxCapacity;
    }

    int size() const
    {
        return length;
    }
};

void dequeuedPrint(bool isNotEmpty, int dequeuedValue);
void peekPrint(bool isNotEmpty, int frontValue);

int main()
{
    ArrayDequeue arrayDequeue(5);
    bool dequeuedOperationBool;
    bool peekedOperationBool;
    int dequeuedValue;
    int peekedValue;

    arrayDequeue.pushFront(1);
    arrayDequeue.print();

    arrayDequeue.pushRear(2);
    arrayDequeue.print();

    arrayDequeue.pushFront(3);
    arrayDequeue.print();

    arrayDequeue.pushRear(4);
    arrayDequeue.print();

    dequeuedOperationBool = arrayDequeue.popFront(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    dequeuedOperationBool = arrayDequeue.popRear(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    dequeuedOperationBool = arrayDequeue.popFront(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    peekedOperationBool = arrayDequeue.peek(peekedValue);
    peekPrint(peekedOperationBool, peekedValue);

    arrayDequeue.pushFront(1);
    arrayDequeue.print();

    arrayDequeue.pushRear(2);
    arrayDequeue.print();

    peekedOperationBool = arrayDequeue.peek(peekedValue);
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
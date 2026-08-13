/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
using std::cout;

struct Node
{
    int data;
    Node *next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

class LinkedListQueue
{
private:
    Node *front;
    Node *rear;
    int length;

public:
    LinkedListQueue()
    {
        front = rear = nullptr;
        length = 0;
    }

    ~LinkedListQueue()
    {
        Node *current = front;

        while (current != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }

        front = rear = nullptr;
        length = 0;
    }

    bool enqueue(int value)
    {
        Node *newNode = new Node(value);

        if (length == 0)
        {
            front = rear = newNode;
            length++;
            return true;
        }

        rear->next = newNode;
        rear = newNode;
        length++;
        return true;
    }

    bool dequeue(int &dequeuedValue)
    {
        if (length == 0)
        {
            return false;
        }

        dequeuedValue = front->data;

        if (length == 1)
        {
            delete front;
            front = rear = nullptr;
            length--;
            return true;
        }

        Node *newFront = front->next;
        delete front;
        front = newFront;

        length--;
        return true;
    }

    bool peek(int &peekedValue) const
    {
        if (front == nullptr)
        {
            return false;
        }

        peekedValue = front->data;
        return true;
    }

    bool clear()
    {

        Node *current = front;

        while (current != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }

        front = rear = nullptr;
        length = 0;

        return true;
    }

    void print() const
    {
        Node *current = front;

        while (current != nullptr)
        {
            cout << current->data << "->";
            current = current->next;
        }

        cout << "\n";
    }

    bool isEmpty() const
    {
        return length == 0;
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
    LinkedListQueue linkedListQueue;
    bool dequeuedOperationBool;
    bool peekedOperationBool;
    int dequeuedValue;
    int peekedValue;

    linkedListQueue.enqueue(1);
    linkedListQueue.print();

    linkedListQueue.enqueue(2);
    linkedListQueue.print();

    dequeuedOperationBool = linkedListQueue.dequeue(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    dequeuedOperationBool = linkedListQueue.dequeue(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    dequeuedOperationBool = linkedListQueue.dequeue(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    peekedOperationBool = linkedListQueue.peek(peekedValue);
    peekPrint(peekedOperationBool, peekedValue);

    linkedListQueue.enqueue(1);
    linkedListQueue.print();

    linkedListQueue.enqueue(2);
    linkedListQueue.print();

    peekedOperationBool = linkedListQueue.peek(peekedValue);
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
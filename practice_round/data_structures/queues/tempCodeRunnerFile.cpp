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

class LinkedListDequeue
{
private:
    Node *front;
    Node *rear;
    int length;

public:
    LinkedListDequeue()
    {
        front = rear = nullptr;
        length = 0;
    }

    ~LinkedListDequeue()
    {
        Node *current = front;

        while (front != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }

        length = 0;
    }

    bool pushFront(int value)
    {
        /*
            1. If isEmpty
                front = rear = newNode
                length ++
                return true
            2. For other cases
                newNode->next = front
                front = newNoe
                length++;
                return true;
        */

        Node *newNode = new Node(value);

        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            newNode->next = front;
            front = newNode;
        }

        length++;
        return true;
    }

    bool pushRear(int value)
    {
        /*
            1. If isEmpty
                front = rear = newNode
                length ++
                return true
            2. For other cases
                rear->next = newNode
                rear = newNoe
                length++;
                return true;
        */

        Node *newNode = new Node(value);

        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        length++;
        return true;
    }

    bool popFront(int &poppedValue)
    {
        /*
            If isEmpty
                return false
            For other cases
                poppedValue = front->data
                newFront = front->next
                delete front;
                front = newFront
                return true
        */

        if (isEmpty)
        {
            return false;
        }

        poppedValue = front->data;
        Node *newFront = front->next;
        delete front;
        front = newFront;

        return true;
    }

    bool popRear(int &poppedValue)
    {
        /*
            If isEmpty
                return false
            For other cases
                poppedValue = rear->data
                Loop till second last element based on length
                newRear = secondLastNode
                delete rear;
                rear = secondLastNode
                return true
        */

        if (isEmpty())
        {
            return false;
        }

        poppedValue = rear->data;

        Node *current = front;

        for (int i = 1; i < length; i++)
        {
            current = current->next;
        }

        Node *newRear = current;
        delete rear;
        rear = newRear;

        return true;
    }

    bool peek(int &peekedValue) const
    {
        /*
            If isEmpty
                return false
            For other cases
                peekedValue = front
                return true
        */

        if (isEmpty())
        {
            return false;
        }

        peekedValue = front->data;
        return true;
    }

    void print() const
    {
        /*
            1. Start at current = front and loop until current != nullptr
        */

        if (isEmpty())
        {
            cout << "Dequeue is empty\n";
            return;
        }

        Node *current = front;

        while (current != nullptr)
        {
            cout << current->data << "->";
            current = current->next;
        }
    }

    bool isEmpty() const
    {
        /*
            return length == 0
        */

        return length == 0;
    }

    bool size() const
    {
        /*
            return length
        */

        return length;
    }
};

void dequeuedPrint(bool isNotEmpty, int dequeuedValue);
void peekPrint(bool isNotEmpty, int frontValue);

int main()
{
    LinkedListDequeue linkedListDequeue;
    bool dequeuedOperationBool;
    bool peekedOperationBool;
    int dequeuedValue;
    int peekedValue;

    linkedListDequeue.pushFront(1);
    linkedListDequeue.print();

    linkedListDequeue.pushRear(2);
    linkedListDequeue.print();

    linkedListDequeue.pushFront(3);
    linkedListDequeue.print();

    linkedListDequeue.pushRear(4);
    linkedListDequeue.print();

    dequeuedOperationBool = linkedListDequeue.popFront(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    dequeuedOperationBool = linkedListDequeue.popRear(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    dequeuedOperationBool = linkedListDequeue.popFront(dequeuedValue);
    dequeuedPrint(dequeuedOperationBool, dequeuedValue);

    peekedOperationBool = linkedListDequeue.peek(peekedValue);
    peekPrint(peekedOperationBool, peekedValue);

    linkedListDequeue.pushFront(1);
    linkedListDequeue.print();

    linkedListDequeue.pushRear(2);
    linkedListDequeue.print();

    peekedOperationBool = linkedListDequeue.peek(peekedValue);
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
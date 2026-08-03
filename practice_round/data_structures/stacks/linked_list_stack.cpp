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

class LinkedListStack
{
private:
    Node *top;
    int length;

public:
    LinkedListStack()
    {
        top = nullptr;
        length = 0;
    }

    LinkedListStack(const LinkedListStack &) = delete;
    LinkedListStack &operator=(const LinkedListStack &) = delete;

    ~LinkedListStack()
    {

        clear();
    }

    bool push(int value)
    {
        Node *newNode = new Node(value);
        newNode->next = top;
        top = newNode;

        cout << "Pushed value: " << value << "\n";

        length++;

        return true;
    }

    bool pop(int &poppedValue)
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";

            return false;
        }

        poppedValue = top->data;

        Node *newTop = top->next;
        delete top;
        top = newTop;

        length--;

        return true;
    }

    bool peek(int &topValue)
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";

            return false;
        }

        topValue = top->data;

        return true;
    }

    void clear()
    {
        Node *current = top;

        while (current != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }

        length = 0;

        cout << "cleared stack\n";

        top = nullptr;
    }

    void print() const
    {
        if (top == nullptr)
        {
            cout << "Stack is empty\n";
            return;
        }

        Node *current = top;

        cout << "Stack is: \n";

        while (current != nullptr)
        {
            cout << "|" << current->data << "|\n";
            current = current->next;
        }
    }

    bool isEmpty() const
    {
        return top == nullptr;
    }

    int size() const
    {
        cout << "Stack size is: " << length << "\n";
        return length;
    }
};

void peekPrint(bool isNotEmpty, int topValue);
void popPrint(bool isNotEmpty, int poppedValue);

int main()
{
    LinkedListStack linkedListStack;
    int poppedValue;
    int topValue;
    bool peekBool;
    bool popBool;

    linkedListStack.push(1);
    linkedListStack.print();

    linkedListStack.push(2);
    linkedListStack.print();

    peekBool = linkedListStack.peek(topValue);
    peekPrint(peekBool, topValue);

    popBool = linkedListStack.pop(poppedValue);
    popPrint(popBool, poppedValue);
    linkedListStack.print();

    popBool = linkedListStack.pop(poppedValue);
    popPrint(popBool, poppedValue);
    linkedListStack.print();

    popBool = linkedListStack.pop(poppedValue);
    popPrint(popBool, poppedValue);
    linkedListStack.print();

    linkedListStack.push(1);
    linkedListStack.print();

    linkedListStack.clear();
    linkedListStack.print();

    linkedListStack.push(1);
    linkedListStack.print();

    linkedListStack.push(2);
    linkedListStack.print();

    linkedListStack.push(3);
    linkedListStack.print();

    linkedListStack.size();

    return 0;
}

void peekPrint(bool isNotEmpty, int topValue)
{
    if (isNotEmpty)
    {
        cout << "Element at top: " << topValue << "\n";
    }
    else
    {
        cout << "Stack is empty\n";
    }
}

void popPrint(bool isNotEmpty, int poppedValue)
{
    if (isNotEmpty)
    {
        cout << "Popped : " << poppedValue << "\n";
    }
    else
    {
        cout << "Stack is empty\n";
    }
}
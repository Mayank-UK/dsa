/*
            ############################################# Practice round 1 #############################################
*/

#include <iostream>
using std::cout;

class ArrayStack
{
private:
    int topIndex; // store index of top item
    int maxCapacity;
    int *stack;

public:
    ArrayStack()
    {
        maxCapacity = 5;
        stack = new int[maxCapacity];
        topIndex = -1;
    }

    ~ArrayStack()
    {
        delete[] stack;
    }

    bool push(int value)
    {
        /*
            1. If topIndex == maxCapacity-1, then return false
            2. In other cases, stack[++topIndex] = value
        */

        if (topIndex == maxCapacity - 1)
        {
            cout << "Stack is full\n";
            return false;
        }

        stack[++topIndex] = value;

        cout << "Inserted at top: " << value << "\n";

        return true;
    }

    bool pop(int &poppedValue)
    {
        /*
            1. If topIndex == -1, return false
            2. For other cases, --top
        */

        if (topIndex == -1)
        {
            return false;
        }

        poppedValue = stack[topIndex--];

        return true;
    }

    bool peek(int &topValue)
    {
        if (topIndex == -1)
        {
            return false;
        }

        topValue = stack[topIndex];

        return true;
    }

    void clear()
    {
        topIndex = -1;
        cout << "Stack cleared\n";
    }

    void print()
    {
        if (topIndex == -1)
        {
            cout << "Stack is empty\n";
            return;
        }

        for (int i = topIndex; i > -1; i--)
        {
            cout << "|" << stack[i] << "|" << "\n";
        }
    }
};

int main()
{
    ArrayStack arrayStack;
    int poppedValue;
    int topValue;
    bool peekBool;
    bool popBool;

    arrayStack.push(1);
    arrayStack.print();

    arrayStack.push(2);
    arrayStack.print();

    peekBool = arrayStack.peek(topValue);
    peekPrint(peekBool, topValue);
    arrayStack.print();

    popBool = arrayStack.pop(poppedValue);
    popPrint(popBool, poppedValue);
    arrayStack.print();

    popBool = arrayStack.pop(poppedValue);
    popPrint(popBool, poppedValue);
    arrayStack.print();

    popBool = arrayStack.pop(poppedValue);
    popPrint(popBool, poppedValue);
    arrayStack.print();

    arrayStack.push(1);
    arrayStack.print();

    arrayStack.clear();
    arrayStack.print();

    return 0;
}

void peekPrint(bool isNotEmpty, int &topValue)
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

void popPrint(bool isNotEmpty, int &poppedValue)
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
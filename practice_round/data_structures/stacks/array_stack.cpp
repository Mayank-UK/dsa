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
    ArrayStack(int capacity)
    {
        if (capacity <= 0)
        {
            capacity = 1;
        }

        maxCapacity = capacity;
        stack = new int[maxCapacity];
        topIndex = -1;
    }

    /*
        ========================= Copy Protection =========================

        This class manages a dynamically allocated array (`stack`) using `new[]`.
        Therefore, it owns heap memory and is responsible for releasing it inside
        the destructor using `delete[]`.

        If these two functions are NOT deleted, the compiler automatically generates
        a copy constructor and copy assignment operator for us.

        The compiler-generated versions perform a *shallow copy*.

        Example:

            ArrayStack stack1(5);

            stack1
            +---------------------------+
            | stack ------------------+ |
            +-------------------------|-+
                                    |
                                    v
                            +-------------+
                            | Heap Array  |
                            +-------------+

            ArrayStack stack2 = stack1;

            stack1                 stack2
            +---------+            +---------+
            | stack --|------------|         |
            +---------+            +---------+
                \____________________|
                                    |
                                    v
                                +-------------+
                                | Heap Array  |
                                +-------------+

        Notice that only the POINTER is copied.
        The actual array is NOT duplicated.

        Now both objects think they own the same memory.

        When `stack2` goes out of scope:

            ~ArrayStack()
            {
                delete[] stack;
            }

        the heap memory is freed.

        However, `stack1.stack` still points to that freed memory
        (called a dangling pointer).

        Later, when `stack1` is destroyed, its destructor also executes

            delete[] stack;

        on the SAME memory again.

        This is called a DOUBLE DELETE and results in undefined behavior
        (program crash, heap corruption, random bugs, etc.).

        Until a proper deep copy constructor and deep copy assignment operator
        are implemented, copying is intentionally disabled.

        In the future, these deleted functions will be replaced with custom
        implementations that allocate a new array and copy every element,
        allowing each object to own its own independent memory.
    */
    ArrayStack(const ArrayStack &) = delete;
    ArrayStack &operator=(const ArrayStack &) = delete;

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

        if (isFull())
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

        if (isEmpty())
        {
            return false;
        }

        poppedValue = stack[topIndex--];

        return true;
    }

    bool peek(int &topValue) const
    {
        if (isEmpty())
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

    void print() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";
            return;
        }

        for (int i = topIndex; i > -1; i--)
        {
            cout << "|" << stack[i] << "|" << "\n";
        }
    }

    bool isEmpty() const
    {
        return topIndex == -1;
    }

    bool isFull() const
    {
        return topIndex == maxCapacity - 1;
    }

    int size() const
    {
        return topIndex + 1;
    }

    int capacity() const
    {
        return maxCapacity;
    }
};

void peekPrint(bool isNotEmpty, int topValue);
void popPrint(bool isNotEmpty, int poppedValue);

int main()
{
    ArrayStack arrayStack(5);
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
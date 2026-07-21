#include <iostream>
using namespace std;

class Stack {
private:
    static const int MAX = 100;
    int arr[MAX];
    int top;

public:
    Stack() {
        top = -1;
    }

    // Push
    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow\n";
            return;
        }

        arr[++top] = value;
    }

    // Pop
    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return;
        }

        top--;
    }

    // Peek
    int peek() {
        if (isEmpty()) {
            cout << "Stack is Empty\n";
            return -1;
        }

        return arr[top];
    }

    // Check if empty
    bool isEmpty() {
        return top == -1;
    }

    // Check if full
    bool isFull() {
        return top == MAX - 1;
    }

    // Current size
    int size() {
        return top + 1;
    }

    // Display
    void display() {
        if (isEmpty()) {
            cout << "Stack is Empty\n";
            return;
        }

        cout << "Top -> ";

        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }

        cout << endl;
    }
};

int main() {

    Stack s;

    s.push(10);
    s.push(20);
    s.push(30);

    s.display();

    cout << "Top Element: " << s.peek() << endl;

    s.pop();

    s.display();

    cout << "Size: " << s.size() << endl;

    return 0;
}
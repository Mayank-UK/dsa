#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class Stack {
private:
    Node* top;

public:
    Stack() {
        top = nullptr;
    }

    // Push
    void push(int value) {
        Node* newNode = new Node(value);

        newNode->next = top;
        top = newNode;
    }

    // Pop
    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return;
        }

        Node* temp = top;
        top = top->next;

        delete temp;
    }

    // Peek
    int peek() {
        if (isEmpty()) {
            cout << "Stack is Empty\n";
            return -1;
        }

        return top->data;
    }

    // Is Empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Size
    int size() {
        int count = 0;
        Node* current = top;

        while (current != nullptr) {
            count++;
            current = current->next;
        }

        return count;
    }

    // Display
    void display() {
        if (isEmpty()) {
            cout << "Stack is Empty\n";
            return;
        }

        cout << "Top -> ";

        Node* current = top;

        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }

        cout << endl;
    }

    // Destructor
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
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
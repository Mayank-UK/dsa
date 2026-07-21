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

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    // Enqueue
    void enqueue(int value) {

        Node* newNode = new Node(value);

        if (isEmpty()) {
            front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    // Dequeue
    void dequeue() {

        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return;
        }

        Node* temp = front;

        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        delete temp;
    }

    // Peek
    int peek() {

        if (isEmpty()) {
            cout << "Queue is Empty\n";
            return -1;
        }

        return front->data;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    int size() {

        int count = 0;
        Node* current = front;

        while (current != nullptr) {
            count++;
            current = current->next;
        }

        return count;
    }

    void display() {

        if (isEmpty()) {
            cout << "Queue is Empty\n";
            return;
        }

        cout << "Front -> ";

        Node* current = front;

        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }

        cout << "<- Rear\n";
    }

    ~Queue() {

        while (!isEmpty())
            dequeue();
    }
};

int main() {

    Queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    q.display();

    cout << "Front Element: " << q.peek() << endl;

    q.dequeue();

    q.display();

    cout << "Size: " << q.size() << endl;

    return 0;
}
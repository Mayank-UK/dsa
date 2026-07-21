#include <iostream>
using namespace std;

class Queue {
private:
    static const int MAX = 100;
    int arr[MAX];
    int front;
    int rear;

public:
    Queue() {
        front = 0;
        rear = -1;
    }

    // Enqueue
    void enqueue(int value) {

        if (isFull()) {
            cout << "Queue Overflow\n";
            return;
        }

        arr[++rear] = value;
    }

    // Dequeue
    void dequeue() {

        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return;
        }

        front++;
    }

    // Front element
    int peek() {

        if (isEmpty()) {
            cout << "Queue is Empty\n";
            return -1;
        }

        return arr[front];
    }

    bool isEmpty() {
        return front > rear;
    }

    bool isFull() {
        return rear == MAX - 1;
    }

    int size() {
        return rear - front + 1;
    }

    void display() {

        if (isEmpty()) {
            cout << "Queue is Empty\n";
            return;
        }

        cout << "Front -> ";

        for (int i = front; i <= rear; i++)
            cout << arr[i] << " ";

        cout << "<- Rear\n";
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
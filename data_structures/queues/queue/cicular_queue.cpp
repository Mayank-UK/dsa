#include <iostream>
using namespace std;

class CircularQueue {
private:
    static const int MAX = 5;
    int arr[MAX];
    int front;
    int rear;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return (rear + 1) % MAX == front;
    }

    void enqueue(int value) {

        if (isFull()) {
            cout << "Queue Overflow\n";
            return;
        }

        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % MAX;
        }

        arr[rear] = value;
    }

    void dequeue() {

        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return;
        }

        // Last element
        if (front == rear) {
            front = rear = -1;
            return;
        }

        front = (front + 1) % MAX;
    }

    int peek() {

        if (isEmpty()) {
            cout << "Queue is Empty\n";
            return -1;
        }

        return arr[front];
    }

    void display() {

        if (isEmpty()) {
            cout << "Queue is Empty\n";
            return;
        }

        cout << "Front -> ";

        int i = front;

        while (true) {

            cout << arr[i] << " ";

            if (i == rear)
                break;

            i = (i + 1) % MAX;
        }

        cout << "<- Rear\n";
    }
};

int main() {

    CircularQueue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);

    q.display();

    q.dequeue();
    q.dequeue();

    q.display();

    q.enqueue(60);
    q.enqueue(70);

    q.display();

    return 0;
}
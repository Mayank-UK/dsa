#include <iostream>
using namespace std;

class Deque {
private:
    static const int MAX = 5;

    int arr[MAX];
    int front;
    int rear;

public:
    Deque() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return (rear + 1) % MAX == front;
    }

    void pushFront(int value) {

        if (isFull()) {
            cout << "Deque Overflow\n";
            return;
        }

        if (isEmpty()) {
            front = rear = 0;
        }
        else if (front == 0) {
            front = MAX - 1;
        }
        else {
            front--;
        }

        arr[front] = value;
    }

    void pushBack(int value) {

        if (isFull()) {
            cout << "Deque Overflow\n";
            return;
        }

        if (isEmpty()) {
            front = rear = 0;
        }
        else {
            rear = (rear + 1) % MAX;
        }

        arr[rear] = value;
    }

    void popFront() {

        if (isEmpty()) {
            cout << "Deque Underflow\n";
            return;
        }

        if (front == rear) {
            front = rear = -1;
        }
        else {
            front = (front + 1) % MAX;
        }
    }

    void popBack() {

        if (isEmpty()) {
            cout << "Deque Underflow\n";
            return;
        }

        if (front == rear) {
            front = rear = -1;
        }
        else if (rear == 0) {
            rear = MAX - 1;
        }
        else {
            rear--;
        }
    }

    int getFront() {

        if (isEmpty()) {
            cout << "Deque is Empty\n";
            return -1;
        }

        return arr[front];
    }

    int getBack() {

        if (isEmpty()) {
            cout << "Deque is Empty\n";
            return -1;
        }

        return arr[rear];
    }

    int size() {

        if (isEmpty())
            return 0;

        return ((rear - front + MAX) % MAX) + 1;
    }

    void clear() {
        front = rear = -1;
    }

    void display() {

        if (isEmpty()) {
            cout << "Deque is Empty\n";
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

    Deque dq;

    dq.pushBack(20);
    dq.pushBack(30);
    dq.pushBack(40);

    dq.display();

    dq.pushFront(10);

    dq.display();

    dq.pushBack(50);

    dq.display();

    cout << "Front: " << dq.getFront() << endl;
    cout << "Back : " << dq.getBack() << endl;
    cout << "Size : " << dq.size() << endl;

    dq.popFront();

    dq.display();

    dq.popBack();

    dq.display();

    dq.pushFront(5);

    dq.display();

    dq.popFront();
    dq.popFront();
    dq.popFront();
    dq.popFront();

    dq.display();

    return 0;
}
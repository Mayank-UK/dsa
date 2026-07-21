#include <iostream>
using namespace std;

class Deque {
private:

    struct Node {
        int data;
        Node* prev;
        Node* next;

        Node(int value) {
            data = value;
            prev = nullptr;
            next = nullptr;
        }
    };

    Node* front;
    Node* rear;
    int count;

public:

    Deque() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    ~Deque() {
        clear();
    }

    bool isEmpty() {
        return front == nullptr;
    }

    int size() {
        return count;
    }

    void pushFront(int value) {

        Node* newNode = new Node(value);

        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }

        count++;
    }

    void pushBack(int value) {

        Node* newNode = new Node(value);

        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }

        count++;
    }

    void popFront() {

        if (isEmpty()) {
            cout << "Deque Underflow\n";
            return;
        }

        Node* temp = front;

        if (front == rear) {
            front = rear = nullptr;
        }
        else {
            front = front->next;
            front->prev = nullptr;
        }

        delete temp;
        count--;
    }

    void popBack() {

        if (isEmpty()) {
            cout << "Deque Underflow\n";
            return;
        }

        Node* temp = rear;

        if (front == rear) {
            front = rear = nullptr;
        }
        else {
            rear = rear->prev;
            rear->next = nullptr;
        }

        delete temp;
        count--;
    }

    int getFront() {

        if (isEmpty()) {
            cout << "Deque is Empty\n";
            return -1;
        }

        return front->data;
    }

    int getBack() {

        if (isEmpty()) {
            cout << "Deque is Empty\n";
            return -1;
        }

        return rear->data;
    }

    void clear() {

        while (!isEmpty()) {
            popFront();
        }
    }

    void displayForward() {

        if (isEmpty()) {
            cout << "Deque is Empty\n";
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

    void displayBackward() {

        if (isEmpty()) {
            cout << "Deque is Empty\n";
            return;
        }

        cout << "Rear -> ";

        Node* current = rear;

        while (current != nullptr) {
            cout << current->data << " ";
            current = current->prev;
        }

        cout << "<- Front\n";
    }
};

int main() {

    Deque dq;

    dq.pushBack(20);
    dq.pushBack(30);
    dq.pushFront(10);
    dq.pushFront(5);
    dq.pushBack(40);

    cout << "Forward Traversal:\n";
    dq.displayForward();

    cout << "\nBackward Traversal:\n";
    dq.displayBackward();

    cout << "\nFront: " << dq.getFront() << endl;
    cout << "Back : " << dq.getBack() << endl;
    cout << "Size : " << dq.size() << endl;

    cout << "\nPop Front\n";
    dq.popFront();
    dq.displayForward();

    cout << "\nPop Back\n";
    dq.popBack();
    dq.displayForward();

    cout << "\nPush Front (100)\n";
    dq.pushFront(100);
    dq.displayForward();

    cout << "\nPush Back (200)\n";
    dq.pushBack(200);
    dq.displayForward();

    cout << "\nClear\n";
    dq.clear();
    dq.displayForward();

    return 0;
}
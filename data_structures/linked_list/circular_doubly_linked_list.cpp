#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

class CircularDoublyLinkedList {
private:
    Node* head;

public:
    CircularDoublyLinkedList() {
        head = nullptr;
    }

    // Insert at beginning
    void insertAtBeginning(int value) {

        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
            return;
        }

        Node* tail = head->prev;

        newNode->next = head;
        newNode->prev = tail;

        tail->next = newNode;
        head->prev = newNode;

        head = newNode;
    }

    // Insert at end
    void insertAtEnd(int value) {

        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
            return;
        }

        Node* tail = head->prev;

        newNode->next = head;
        newNode->prev = tail;

        tail->next = newNode;
        head->prev = newNode;
    }

    // Delete first occurrence
    void deleteNode(int value) {

        if (head == nullptr)
            return;

        Node* current = head;

        do {

            if (current->data == value) {

                // Only one node
                if (current->next == current) {
                    delete current;
                    head = nullptr;
                    return;
                }

                current->prev->next = current->next;
                current->next->prev = current->prev;

                if (current == head)
                    head = current->next;

                delete current;
                return;
            }

            current = current->next;

        } while (current != head);
    }

    // Search
    bool search(int value) {

        if (head == nullptr)
            return false;

        Node* current = head;

        do {

            if (current->data == value)
                return true;

            current = current->next;

        } while (current != head);

        return false;
    }

    // Display Forward
    void displayForward() {

        if (head == nullptr) {
            cout << "Empty\n";
            return;
        }

        Node* current = head;

        do {
            cout << current->data << " <-> ";
            current = current->next;
        } while (current != head);

        cout << "(head)\n";
    }

    // Display Backward
    void displayBackward() {

        if (head == nullptr) {
            cout << "Empty\n";
            return;
        }

        Node* current = head->prev;

        do {
            cout << current->data << " <-> ";
            current = current->prev;
        } while (current != head->prev);

        cout << "(tail)\n";
    }

    ~CircularDoublyLinkedList() {

        if (head == nullptr)
            return;

        Node* current = head->next;

        while (current != head) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }

        delete head;
    }
};

int main() {

    CircularDoublyLinkedList list;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);

    list.insertAtBeginning(5);

    cout << "Forward : ";
    list.displayForward();

    cout << "Backward: ";
    list.displayBackward();

    list.deleteNode(20);

    cout << "\nAfter deleting 20\n";

    cout << "Forward : ";
    list.displayForward();

    cout << "Backward: ";
    list.displayBackward();

    cout << "\nSearch 30: " << boolalpha << list.search(30) << endl;
    cout << "Search 100: " << boolalpha << list.search(100) << endl;

    return 0;
}
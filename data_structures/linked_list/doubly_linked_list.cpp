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

class DoublyLinkedList {
private:
    Node* head;

public:
    DoublyLinkedList() {
        head = nullptr;
    }

    // Insert at beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);

        newNode->next = head;

        if (head != nullptr)
            head->prev = newNode;

        head = newNode;
    }

    // Insert at end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;

        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = newNode;
        newNode->prev = temp;
    }

    // Delete first occurrence
    void deleteNode(int value) {
        if (head == nullptr)
            return;

        Node* temp = head;

        while (temp != nullptr && temp->data != value)
            temp = temp->next;

        if (temp == nullptr)
            return;

        // Deleting head
        if (temp == head)
            head = head->next;

        if (temp->prev != nullptr)
            temp->prev->next = temp->next;

        if (temp->next != nullptr)
            temp->next->prev = temp->prev;

        delete temp;
    }

    // Search
    bool search(int value) {
        Node* temp = head;

        while (temp != nullptr) {
            if (temp->data == value)
                return true;

            temp = temp->next;
        }

        return false;
    }

    // Display forward
    void displayForward() {
        Node* temp = head;

        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }

        cout << "NULL\n";
    }

    // Display backward
    void displayBackward() {
        if (head == nullptr) {
            cout << "NULL\n";
            return;
        }

        Node* temp = head;

        while (temp->next != nullptr)
            temp = temp->next;

        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }

        cout << "NULL\n";
    }

    ~DoublyLinkedList() {
        Node* temp = head;

        while (temp != nullptr) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

int main() {

    DoublyLinkedList list;

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
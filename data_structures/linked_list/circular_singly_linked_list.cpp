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

class CircularSinglyLinkedList {
private:
    Node* head;

public:
    CircularSinglyLinkedList() {
        head = nullptr;
    }

    // Insert at beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
            return;
        }

        Node* last = head;

        while (last->next != head)
            last = last->next;

        newNode->next = head;
        last->next = newNode;
        head = newNode;
    }

    // Insert at end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
            return;
        }

        Node* last = head;

        while (last->next != head)
            last = last->next;

        last->next = newNode;
        newNode->next = head;
    }

    // Delete first occurrence
    void deleteNode(int value) {
        if (head == nullptr)
            return;

        // Only one node
        if (head->data == value && head->next == head) {
            delete head;
            head = nullptr;
            return;
        }

        // Delete head
        if (head->data == value) {

            Node* last = head;

            while (last->next != head)
                last = last->next;

            Node* temp = head;

            head = head->next;
            last->next = head;

            delete temp;
            return;
        }

        Node* current = head;

        while (current->next != head &&
               current->next->data != value) {
            current = current->next;
        }

        if (current->next == head)
            return;

        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
    }

    // Search
    bool search(int value) {

        if (head == nullptr)
            return false;

        Node* temp = head;

        do {
            if (temp->data == value)
                return true;

            temp = temp->next;

        } while (temp != head);

        return false;
    }

    // Display
    void display() {

        if (head == nullptr) {
            cout << "Empty\n";
            return;
        }

        Node* temp = head;

        do {
            cout << temp->data << " -> ";
            temp = temp->next;

        } while (temp != head);

        cout << "(back to head)\n";
    }

    ~CircularSinglyLinkedList() {

        if (head == nullptr)
            return;

        Node* current = head->next;

        while (current != head) {
            Node* next = current->next;
            delete current;
            current = next;
        }

        delete head;
    }
};

int main() {

    CircularSinglyLinkedList list;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);

    list.insertAtBeginning(5);

    list.display();

    list.deleteNode(20);

    list.display();

    cout << boolalpha;
    cout << list.search(30) << endl;
    cout << list.search(100) << endl;

    return 0;
}
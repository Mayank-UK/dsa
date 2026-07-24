#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Circular Doubly Linked List
//   prev of HEAD points to TAIL, and next of TAIL points to HEAD. Every node
//   has both pointers, so head->prev is the tail in O(1) and we can traverse
//   both directions and wrap around either end. No nullptrs anywhere (until
//   the list is empty).
// ─────────────────────────────────────────────────────────────────────────────

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
    int len;

public:
    CircularDoublyLinkedList() {
        head = nullptr;
        len = 0;
    }

    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
            len++;
            return;
        }
        Node* tail = head->prev;     // O(1) tail access
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
        head = newNode;
        len++;
    }

    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
            len++;
            return;
        }
        Node* tail = head->prev;
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
        len++;
    }

    bool deleteByValue(int value) {
        if (head == nullptr) return false;

        Node* current = head;
        do {
            if (current->data == value) {
                if (current->next == current) {   // only node
                    delete current;
                    head = nullptr;
                    len--;
                    return true;
                }
                current->prev->next = current->next;
                current->next->prev = current->prev;
                if (current == head) head = current->next;
                delete current;
                len--;
                return true;
            }
            current = current->next;
        } while (current != head);
        return false;
    }

    bool search(int value) const {
        if (head == nullptr) return false;
        Node* current = head;
        do {
            if (current->data == value) return true;
            current = current->next;
        } while (current != head);
        return false;
    }

    int size() const { return len; }
    bool isEmpty() const { return head == nullptr; }

    void displayForward() const {
        if (head == nullptr) { cout << "(empty)\n"; return; }
        Node* current = head;
        do {
            cout << current->data << " <-> ";
            current = current->next;
        } while (current != head);
        cout << "(wraps to head: " << head->data << ")\n";
    }

    // Start at the tail (head->prev) and walk backward.
    void displayBackward() const {
        if (head == nullptr) { cout << "(empty)\n"; return; }
        Node* current = head->prev;   // tail
        do {
            cout << current->data << " <-> ";
            current = current->prev;
        } while (current != head->prev);
        cout << "(wraps to tail: " << head->prev->data << ")\n";
    }

    void clear() {
        if (head == nullptr) return;
        Node* current = head->next;
        while (current != head) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
        head = nullptr;
        len = 0;
    }

    ~CircularDoublyLinkedList() { clear(); }
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "========= Circular Doubly Linked List =========\n";

    CircularDoublyLinkedList list;

    // ── [Build] ──────────────────────────────────────────────────────────────
    cout << "\n[Build] insertAtEnd(10,20,30), insertAtBeginning(5)\n";
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtBeginning(5);

    cout << "  Forward  : "; list.displayForward();
    cout << "  Backward : "; list.displayBackward();
    cout << "  Size     : " << list.size() << "\n";

    // ── [Query] ──────────────────────────────────────────────────────────────
    cout << "\n[Query]\n";
    cout << "  search(30)  -> " << (list.search(30)  ? "Found" : "Not Found") << "\n";
    cout << "  search(100) -> " << (list.search(100) ? "Found" : "Not Found") << "\n";

    // ── [Delete] before/after ────────────────────────────────────────────────
    cout << "\n[Delete] deleteByValue(20) — both links heal, list stays circular\n";
    cout << "  Before F : "; list.displayForward();
    list.deleteByValue(20);
    cout << "  After  F : "; list.displayForward();
    cout << "  After  B : "; list.displayBackward();

    cout << "\n[Delete] deleteByValue(5) removes head; O(1) tail rewire\n";
    list.deleteByValue(5);
    cout << "  After  F : "; list.displayForward();

    // ── [Edge] ───────────────────────────────────────────────────────────────
    cout << "\n[Edge] Single-node self-loop (next & prev both point to itself)\n";
    list.deleteByValue(30);
    cout << "  Forward  : "; list.displayForward();
    cout << "  Backward : "; list.displayBackward();

    cout << "\n[Clear] Emptying\n";
    list.clear();
    cout << "  Size after clear : " << list.size() << "\n";
    cout << "  Forward          : "; list.displayForward();

    cout << "\n===============================================\n";
    return 0;
}

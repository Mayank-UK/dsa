#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Doubly Linked List
//   Each node carries prev AND next pointers, enabling O(1) backward traversal
//   and O(1) node deletion when you already hold the node pointer.
//   • Insert/delete at head: O(1). At tail / by value: O(n) (no tail kept here).
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

class DoublyLinkedList {
private:
    Node* head;
    int len;

public:
    DoublyLinkedList() {
        head = nullptr;
        len = 0;
    }

    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        if (head != nullptr)
            head->prev = newNode;
        head = newNode;
        len++;
    }

    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            len++;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
        len++;
    }

    // 0-indexed positional insert.
    bool insertAtPosition(int value, int pos) {
        if (pos < 0 || pos > len) return false;
        if (pos == 0) { insertAtBeginning(value); return true; }
        if (pos == len) { insertAtEnd(value); return true; }

        Node* temp = head;
        for (int i = 0; i < pos; i++) temp = temp->next;

        Node* newNode = new Node(value);
        newNode->prev = temp->prev;
        newNode->next = temp;
        temp->prev->next = newNode;
        temp->prev = newNode;
        len++;
        return true;
    }

    bool deleteByValue(int value) {
        if (head == nullptr) return false;

        Node* temp = head;
        while (temp != nullptr && temp->data != value)
            temp = temp->next;
        if (temp == nullptr) return false;

        if (temp == head) head = head->next;
        if (temp->prev != nullptr) temp->prev->next = temp->next;
        if (temp->next != nullptr) temp->next->prev = temp->prev;

        delete temp;
        len--;
        return true;
    }

    bool deleteByPosition(int pos) {
        if (pos < 0 || pos >= len) return false;

        Node* temp = head;
        for (int i = 0; i < pos; i++) temp = temp->next;

        if (temp == head) head = head->next;
        if (temp->prev != nullptr) temp->prev->next = temp->next;
        if (temp->next != nullptr) temp->next->prev = temp->prev;

        delete temp;
        len--;
        return true;
    }

    bool search(int value) const {
        for (Node* temp = head; temp != nullptr; temp = temp->next)
            if (temp->data == value) return true;
        return false;
    }

    int size() const { return len; }
    bool isEmpty() const { return head == nullptr; }

    // Swap prev/next on every node — head becomes the old tail.
    void reverse() {
        Node* temp = nullptr;
        Node* current = head;
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;   // prev now holds the old next
        }
        if (temp != nullptr)
            head = temp->prev;
    }

    void clear() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
        len = 0;
    }

    void displayForward() const {
        if (head == nullptr) { cout << "(empty)\n"; return; }
        for (Node* t = head; t != nullptr; t = t->next)
            cout << t->data << (t->next ? " <-> " : " <-> NULL\n");
    }

    void displayBackward() const {
        if (head == nullptr) { cout << "(empty)\n"; return; }
        Node* t = head;
        while (t->next != nullptr) t = t->next;   // walk to tail
        for (; t != nullptr; t = t->prev)
            cout << t->data << (t->prev ? " <-> " : " <-> NULL\n");
    }

    ~DoublyLinkedList() { clear(); }
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "=============== Doubly Linked List ===============\n";

    DoublyLinkedList list;

    // ── [Build] ──────────────────────────────────────────────────────────────
    cout << "\n[Build] insertAtEnd(10,20,30), insertAtBeginning(5)\n";
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtBeginning(5);

    cout << "  Forward  : "; list.displayForward();
    cout << "  Backward : "; list.displayBackward();
    cout << "  Size     : " << list.size() << "\n";

    // ── [Insert by position] ─────────────────────────────────────────────────
    cout << "\n[Insert] insertAtPosition(99, 2)\n";
    list.insertAtPosition(99, 2);
    cout << "  Forward  : "; list.displayForward();

    // ── [Query] ──────────────────────────────────────────────────────────────
    cout << "\n[Query]\n";
    cout << "  search(30)  -> " << (list.search(30)  ? "Found" : "Not Found") << "\n";
    cout << "  search(100) -> " << (list.search(100) ? "Found" : "Not Found") << "\n";

    // ── [Delete] before/after ────────────────────────────────────────────────
    cout << "\n[Delete] deleteByValue(20) — prev/next rewired, no leak\n";
    cout << "  Before F : "; list.displayForward();
    list.deleteByValue(20);
    cout << "  After  F : "; list.displayForward();
    cout << "  After  B : "; list.displayBackward();

    // ── [Reverse] ────────────────────────────────────────────────────────────
    cout << "\n[Reverse] swap prev<->next on every node\n";
    cout << "  Before F : "; list.displayForward();
    list.reverse();
    cout << "  After  F : "; list.displayForward();
    cout << "  After  B : "; list.displayBackward();

    // ── [Edge] ───────────────────────────────────────────────────────────────
    cout << "\n[Edge] deleteByPosition(out of range)\n";
    cout << "  -> " << boolalpha << list.deleteByPosition(999) << "\n";

    cout << "\n[Clear] Emptying\n";
    list.clear();
    cout << "  Size after clear : " << list.size() << "\n";
    cout << "  Forward          : "; list.displayForward();

    cout << "\n=================================================\n";
    return 0;
}

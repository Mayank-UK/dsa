#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Singly Linked List
//   Each node points to the NEXT node only (one-way). Head marks the start;
//   the last node's next is nullptr.
//   • Insert/delete at head: O(1). At tail / by value: O(n).
// ─────────────────────────────────────────────────────────────────────────────

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class SinglyLinkedList {
private:
    Node* head;
    int len;

public:
    SinglyLinkedList() {
        head = nullptr;
        len = 0;
    }

    // O(1) head insert.
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        len++;
    }

    // O(n) tail insert (no tail pointer kept).
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
        len++;
    }

    // 0-indexed position insert. pos == size → append at tail.
    bool insertAtPosition(int value, int pos) {
        if (pos < 0 || pos > len) return false;

        if (pos == 0) { insertAtBeginning(value); return true; }
        if (pos == len) { insertAtEnd(value); return true; }

        Node* temp = head;
        for (int i = 0; i < pos - 1; i++)
            temp = temp->next;

        Node* newNode = new Node(value);
        newNode->next = temp->next;
        temp->next = newNode;
        len++;
        return true;
    }

    // Delete the first node holding `value`. Returns true if removed.
    bool deleteByValue(int value) {
        if (head == nullptr) return false;

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            len--;
            return true;
        }

        Node* current = head;
        while (current->next != nullptr && current->next->data != value)
            current = current->next;

        if (current->next == nullptr) return false;

        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        len--;
        return true;
    }

    // 0-indexed positional delete. Returns true if removed.
    bool deleteByPosition(int pos) {
        if (pos < 0 || pos >= len) return false;

        if (pos == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            len--;
            return true;
        }

        Node* current = head;
        for (int i = 0; i < pos - 1; i++)
            current = current->next;

        Node* temp = current->next;
        current->next = temp->next;
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

    // n-th node from the END (1-indexed: 1 = last). Returns false if out of range.
    bool getNthFromEnd(int n, int& out) const {
        if (n < 1 || n > len) return false;

        Node* fast = head;
        Node* slow = head;
        for (int i = 0; i < n; i++) fast = fast->next;
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        out = slow->data;
        return true;
    }

    // Classic 3-pointer in-place reversal.
    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        len = 0;
    }

    void display() const {
        if (head == nullptr) {
            cout << "(empty)\n";
            return;
        }
        for (Node* temp = head; temp != nullptr; temp = temp->next) {
            cout << temp->data;
            cout << (temp->next != nullptr ? " -> " : " -> NULL\n");
        }
    }

    ~SinglyLinkedList() { clear(); }
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "================ Singly Linked List ================\n";

    SinglyLinkedList list;

    // ── [Build] ──────────────────────────────────────────────────────────────
    cout << "\n[Build] insertAtEnd(10,20,30), insertAtBeginning(5)\n";
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtBeginning(5);
    cout << "  List  : "; list.display();
    cout << "  Size  : " << list.size() << "\n";

    // ── [Insert by position] ─────────────────────────────────────────────────
    cout << "\n[Insert] insertAtPosition(99, 2)  →  between 20 and 30\n";
    list.insertAtPosition(99, 2);
    cout << "  List  : "; list.display();

    cout << "\n[Insert] insertAtPosition(7, 0) at head\n";
    list.insertAtPosition(7, 0);
    cout << "  List  : "; list.display();

    // ── [Query] ──────────────────────────────────────────────────────────────
    cout << "\n[Query]\n";
    cout << "  search(30)  -> " << (list.search(30)  ? "Found" : "Not Found") << "\n";
    cout << "  search(100) -> " << (list.search(100) ? "Found" : "Not Found") << "\n";

    int nth;
    if (list.getNthFromEnd(2, nth))
        cout << "  2nd from end -> " << nth << "\n";
    if (list.getNthFromEnd(1, nth))
        cout << "  1st from end -> " << nth << "\n";

    // ── [Delete] before/after ────────────────────────────────────────────────
    cout << "\n[Delete] deleteByValue(20)\n";
    cout << "  Before : "; list.display();
    list.deleteByValue(20);
    cout << "  After  : "; list.display();

    cout << "\n[Delete] deleteByPosition(0) removes the head\n";
    list.deleteByPosition(0);
    cout << "  List   : "; list.display();

    // ── [Reverse] ────────────────────────────────────────────────────────────
    cout << "\n[Reverse] in-place pointer reversal\n";
    cout << "  Before : "; list.display();
    list.reverse();
    cout << "  After  : "; list.display();

    // ── [Edge] ───────────────────────────────────────────────────────────────
    cout << "\n[Edge] Deleting a value that is not present\n";
    cout << "  deleteByValue(4242) -> " << boolalpha << list.deleteByValue(4242) << "\n";

    cout << "\n[Clear] Emptying the list\n";
    list.clear();
    cout << "  Size after clear : " << list.size() << "\n";
    cout << "  isEmpty          : " << boolalpha << list.isEmpty() << "\n";
    cout << "  List             : "; list.display();

    cout << "\n====================================================\n";
    return 0;
}

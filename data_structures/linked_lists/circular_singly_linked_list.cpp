#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Circular Singly Linked List
//   Like a singly list, but the LAST node's next points back to HEAD instead of
//   nullptr — there is no end. Traversal must use a do/while and stop when it
//   returns to head, or it loops forever.
//   • Head insert can be made O(1) by keeping a tail pointer; here we walk to
//     the last node (O(n)) for clarity.
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

class CircularSinglyLinkedList {
private:
    Node* head;
    int len;

    // Walk to the last node (the one whose next == head).
    Node* lastNode() const {
        if (head == nullptr) return nullptr;
        Node* last = head;
        while (last->next != head) last = last->next;
        return last;
    }

public:
    CircularSinglyLinkedList() {
        head = nullptr;
        len = 0;
    }

    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
            len++;
            return;
        }
        Node* last = lastNode();
        newNode->next = head;
        last->next = newNode;
        head = newNode;
        len++;
    }

    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
            len++;
            return;
        }
        Node* last = lastNode();
        last->next = newNode;
        newNode->next = head;
        len++;
    }

    bool deleteByValue(int value) {
        if (head == nullptr) return false;

        // Single-node list holding the value.
        if (head->data == value && head->next == head) {
            delete head;
            head = nullptr;
            len--;
            return true;
        }

        // Value at head — reconnect last to the new head.
        if (head->data == value) {
            Node* last = lastNode();
            Node* temp = head;
            head = head->next;
            last->next = head;
            delete temp;
            len--;
            return true;
        }

        Node* current = head;
        while (current->next != head && current->next->data != value)
            current = current->next;

        if (current->next == head) return false;   // not found

        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        len--;
        return true;
    }

    bool search(int value) const {
        if (head == nullptr) return false;
        Node* temp = head;
        do {
            if (temp->data == value) return true;
            temp = temp->next;
        } while (temp != head);
        return false;
    }

    int size() const { return len; }
    bool isEmpty() const { return head == nullptr; }

    // Show the wrap-around by printing one full loop plus a peek at head again.
    void display() const {
        if (head == nullptr) { cout << "(empty)\n"; return; }
        Node* temp = head;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(wraps to head: " << head->data << ")\n";
    }

    void clear() {
        if (head == nullptr) return;
        Node* current = head->next;
        while (current != head) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        delete head;
        head = nullptr;
        len = 0;
    }

    ~CircularSinglyLinkedList() { clear(); }
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "=========== Circular Singly Linked List ===========\n";

    CircularSinglyLinkedList list;

    // ── [Build] ──────────────────────────────────────────────────────────────
    cout << "\n[Build] insertAtEnd(10,20,30), insertAtBeginning(5)\n";
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtBeginning(5);

    cout << "  List   : "; list.display();
    cout << "  Size   : " << list.size() << "\n";

    // ── [Query] ──────────────────────────────────────────────────────────────
    cout << "\n[Query]\n";
    cout << "  search(30)  -> " << (list.search(30)  ? "Found" : "Not Found") << "\n";
    cout << "  search(100) -> " << (list.search(100) ? "Found" : "Not Found") << "\n";

    // ── [Delete] before/after ────────────────────────────────────────────────
    cout << "\n[Delete] deleteByValue(20) — chain stays circular\n";
    cout << "  Before : "; list.display();
    list.deleteByValue(20);
    cout << "  After  : "; list.display();

    cout << "\n[Delete] deleteByValue(5) removes the head; last node rewires to new head\n";
    list.deleteByValue(5);
    cout << "  After  : "; list.display();

    // ── [Edge] single-node self-loop ─────────────────────────────────────────
    cout << "\n[Edge] Reduce to one node to show the self-loop\n";
    list.deleteByValue(30);
    cout << "  List   : "; list.display();
    cout << "  Size   : " << list.size() << "\n";

    cout << "\n[Delete] removing the last node\n";
    list.deleteByValue(10);
    cout << "  Size   : " << list.size() << "\n";
    cout << "  List   : "; list.display();

    cout << "\n===================================================\n";
    return 0;
}

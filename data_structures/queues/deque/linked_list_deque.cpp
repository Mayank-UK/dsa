#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Deque — Doubly-linked-list-backed (dynamic capacity)
//   Insert/remove at both ends in O(1). front = head, rear = tail. No overflow.
// ─────────────────────────────────────────────────────────────────────────────

class Deque {
private:

    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    int count;

public:

    Deque() : front(nullptr), rear(nullptr), count(0) {}
    ~Deque() { clear(); }

    bool isEmpty() const { return front == nullptr; }
    int  size()    const { return count; }

    void pushFront(int value) {
        Node* n = new Node(value);
        if (isEmpty()) { front = rear = n; }
        else { n->next = front; front->prev = n; front = n; }
        count++;
    }

    void pushBack(int value) {
        Node* n = new Node(value);
        if (isEmpty()) { front = rear = n; }
        else { rear->next = n; n->prev = rear; rear = n; }
        count++;
    }

    int popFront(bool& ok) {
        if (isEmpty()) { cout << "  (underflow: popFront on empty)\n"; ok = false; return -1; }
        ok = true;
        Node* t = front;
        int v = t->data;
        if (front == rear) front = rear = nullptr;
        else { front = front->next; front->prev = nullptr; }
        delete t; count--;
        return v;
    }

    int popBack(bool& ok) {
        if (isEmpty()) { cout << "  (underflow: popBack on empty)\n"; ok = false; return -1; }
        ok = true;
        Node* t = rear;
        int v = t->data;
        if (front == rear) front = rear = nullptr;
        else { rear = rear->prev; rear->next = nullptr; }
        delete t; count--;
        return v;
    }

    int getFront(bool& ok) const {
        if (isEmpty()) { ok = false; return -1; }
        ok = true; return front->data;
    }
    int getBack(bool& ok) const {
        if (isEmpty()) { ok = false; return -1; }
        ok = true; return rear->data;
    }

    void clear() { bool ok; while (!isEmpty()) popFront(ok); }

    void displayForward() const {
        if (isEmpty()) { cout << "  Front -> (empty) <- Rear\n"; return; }
        cout << "  Front -> ";
        for (Node* c = front; c != nullptr; c = c->next) cout << c->data << " ";
        cout << "<- Rear\n";
    }
    void displayBackward() const {
        if (isEmpty()) { cout << "  Rear -> (empty) <- Front\n"; return; }
        cout << "  Rear -> ";
        for (Node* c = rear; c != nullptr; c = c->prev) cout << c->data << " ";
        cout << "<- Front\n";
    }
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "=========== Deque (Doubly Linked List, dynamic) ===========\n";

    Deque dq;
    bool ok;

    // ── [Build] both ends ────────────────────────────────────────────────────
    cout << "\n[Build] pushBack 20,30  pushFront 10  pushBack 40  pushFront 5\n";
    dq.pushBack(20); dq.pushBack(30);
    dq.pushFront(10);
    dq.pushBack(40);
    dq.pushFront(5);

    cout << "  Forward  : "; dq.displayForward();
    cout << "  Backward : "; dq.displayBackward();
    cout << "  front -> " << dq.getFront(ok) << "   back -> " << dq.getBack(ok)
         << "   size -> " << dq.size() << "\n";

    // ── [Pop] both ends ──────────────────────────────────────────────────────
    cout << "\n[Pop] popFront -> " << dq.popFront(ok)
         << "   popBack -> " << dq.popBack(ok) << "\n";
    cout << "  Forward  : "; dq.displayForward();

    // ── [Edge] underflow ─────────────────────────────────────────────────────
    cout << "\n[Edge] drain then pop on empty\n";
    dq.clear();
    cout << "  popFront on empty -> " << dq.popFront(ok) << "  (ok=" << boolalpha << ok << ")\n";
    cout << "  popBack  on empty -> " << dq.popBack(ok)  << "  (ok=" << ok << ")\n";

    cout << "\n==========================================================\n";
    return 0;
}

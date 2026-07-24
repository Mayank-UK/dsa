#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Queue — Linked-list-backed (dynamic capacity)
//   FIFO. front = head (dequeue here), rear = tail (enqueue here). Both O(1).
//   Grows without bound; no overflow.
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

class Queue {
private:
    Node* front;
    Node* rear;
    int len;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
        len = 0;
    }

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        len++;
    }

    int dequeue(bool& ok) {
        if (isEmpty()) {
            cout << "  (underflow: dequeue on empty queue)\n";
            ok = false;
            return -1;
        }
        ok = true;
        Node* temp = front;
        int value = front->data;
        front = front->next;
        if (front == nullptr) rear = nullptr;   // queue became empty
        delete temp;
        len--;
        return value;
    }

    int peek(bool& ok) const {
        if (isEmpty()) { ok = false; return -1; }
        ok = true;
        return front->data;
    }

    bool isEmpty() const { return front == nullptr; }
    int  size()    const { return len; }

    void clear() {
        bool ok;
        while (!isEmpty()) dequeue(ok);
    }

    void display() const {
        if (isEmpty()) { cout << "  Front -> (empty) <- Rear\n"; return; }
        cout << "  Front -> ";
        for (Node* c = front; c != nullptr; c = c->next)
            cout << c->data << " ";
        cout << "<- Rear   (size " << len << ")\n";
    }

    ~Queue() { clear(); }
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "============= Queue (Linked List, dynamic) =============\n";

    Queue q;

    // ── [Enqueue] ────────────────────────────────────────────────────────────
    cout << "\n[Enqueue] 10, 20, 30\n";
    q.enqueue(10); q.enqueue(20); q.enqueue(30);
    q.display();

    // ── [Front] ──────────────────────────────────────────────────────────────
    bool ok;
    cout << "\n[Front] peek -> " << q.peek(ok) << "\n";

    // ── [Dequeue] before/after ───────────────────────────────────────────────
    cout << "\n[Dequeue]\n";
    cout << "  Before: "; q.display();
    cout << "  dequeued -> " << q.dequeue(ok) << "\n";
    cout << "  After : "; q.display();

    // ── [Grow] dynamic ───────────────────────────────────────────────────────
    cout << "\n[Grow] enqueue 5 more — no overflow (dynamic)\n";
    q.enqueue(40); q.enqueue(50); q.enqueue(60); q.enqueue(70); q.enqueue(80);
    q.display();
    cout << "  size: " << q.size() << "\n";

    // ── [Edge] underflow ─────────────────────────────────────────────────────
    cout << "\n[Edge] Drain then operate on empty\n";
    q.clear();
    cout << "  size after clear: " << q.size() << "\n";
    cout << "  dequeue on empty -> " << q.dequeue(ok) << "  (ok=" << boolalpha << ok << ")\n";

    cout << "\n=========================================================\n";
    return 0;
}

#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Queue — Array-backed (linear, sliding front)
//   FIFO: first in, first out. enqueue at rear, dequeue at front.
//   • This simple version lets `front` and `rear` only march FORWARD. After
//     enough operations rear hits MAX and reports "full" even though slots
//     below front are unused — the classic motivation for a CIRCULAR queue
//     (see cicular_queue.cpp).
// ─────────────────────────────────────────────────────────────────────────────

class Queue {
private:
    static const int MAX = 100;
    int arr[MAX];
    int front;
    int rear;

public:
    Queue() {
        front = 0;
        rear = -1;
    }

    bool enqueue(int value) {
        if (isFull()) {
            cout << "  (overflow: queue full at rear index " << rear << ")\n";
            return false;
        }
        arr[++rear] = value;
        return true;
    }

    int dequeue(bool& ok) {
        if (isEmpty()) {
            cout << "  (underflow: dequeue on empty queue)\n";
            ok = false;
            return -1;
        }
        ok = true;
        return arr[front++];
    }

    int peek(bool& ok) const {
        if (isEmpty()) { ok = false; return -1; }
        ok = true;
        return arr[front];
    }

    bool isEmpty() const { return front > rear; }
    bool isFull()  const { return rear == MAX - 1; }
    int  size()    const { return rear - front + 1; }

    void clear() { front = 0; rear = -1; }

    void display() const {
        if (isEmpty()) { cout << "  Front -> (empty) <- Rear\n"; return; }
        cout << "  Front -> ";
        for (int i = front; i <= rear; i++)
            cout << arr[i] << " ";
        cout << "<- Rear   (size " << size() << ", frontIdx " << front
             << ", rearIdx " << rear << ")\n";
    }

    ~Queue() = default;
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "=============== Queue (Array, linear) ===============\n";

    Queue q;

    // ── [Enqueue] ────────────────────────────────────────────────────────────
    cout << "\n[Enqueue] 10, 20, 30\n";
    q.enqueue(10); q.enqueue(20); q.enqueue(30);
    q.display();

    // ── [Front] ──────────────────────────────────────────────────────────────
    bool ok;
    cout << "\n[Front] peek -> " << q.peek(ok) << "  (oldest element)\n";

    // ── [Dequeue] before/after ───────────────────────────────────────────────
    cout << "\n[Dequeue]\n";
    cout << "  Before: "; q.display();
    cout << "  dequeued -> " << q.dequeue(ok) << "\n";
    cout << "  After : "; q.display();

    // ── [Edge] underflow ─────────────────────────────────────────────────────
    cout << "\n[Edge] Drain then operate on empty\n";
    q.clear();
    cout << "  size after clear: " << q.size() << "\n";
    cout << "  dequeue on empty -> " << q.dequeue(ok) << "  (ok=" << boolalpha << ok << ")\n";

    cout << "\n======================================================\n";
    return 0;
}

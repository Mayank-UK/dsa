#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Circular Queue — Array-backed (ring buffer)
//   FIFO, but front and rear wrap around modulo MAX. Reused slots free up by
//   dequeuing, so the queue never falsely reports "full" while space exists —
//   unlike the linear array queue.
//
//   The classic subtlety: with rear chasing front, "empty" and "full" can both
//   look like rear just behind front. We resolve it by:
//     • EMPTY  : front == -1   (a sentinel meaning "never used / just cleared")
//     • FULL   : (rear + 1) % MAX == front   (one slot intentionally wasted so
//       full and empty are distinguishable without a separate counter)
// ─────────────────────────────────────────────────────────────────────────────

class CircularQueue {
private:
    static const int MAX = 5;
    int arr[MAX];
    int front;
    int rear;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() const { return front == -1; }
    bool isFull()  const { return (rear + 1) % MAX == front; }
    int  size() const {
        if (isEmpty()) return 0;
        if (front <= rear) return rear - front + 1;
        return MAX - front + rear + 1;
    }

    bool enqueue(int value) {
        if (isFull()) {
            cout << "  (overflow: ring full)\n";
            return false;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % MAX;     // wrap
        }
        arr[rear] = value;
        return true;
    }

    int dequeue(bool& ok) {
        if (isEmpty()) {
            cout << "  (underflow: ring empty)\n";
            ok = false;
            return -1;
        }
        ok = true;
        int value = arr[front];
        if (front == rear) {            // last element → reset to empty
            front = rear = -1;
        } else {
            front = (front + 1) % MAX;  // wrap
        }
        return value;
    }

    int peek(bool& ok) const {
        if (isEmpty()) { ok = false; return -1; }
        ok = true;
        return arr[front];
    }

    // Show contents AND the raw indices, so the wrap-around is visible.
    void display() const {
        cout << "  slots: [";
        for (int i = 0; i < MAX; i++) {
            bool inUse = false;
            if (!isEmpty()) {
                int idx = front;
                while (true) {
                    if (idx == i) { inUse = true; break; }
                    if (idx == rear) break;
                    idx = (idx + 1) % MAX;
                }
            }
            if (inUse) cout << arr[i]; else cout << '_';
            if (i + 1 < MAX) cout << ",";
        }
        cout << "]   (front=" << front << ", rear=" << rear
             << ", size=" << size() << ")\n";
    }

    ~CircularQueue() = default;
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "=========== Circular Queue (ring buffer, cap 5) ===========\n";

    CircularQueue q;

    // ── [Fill] ───────────────────────────────────────────────────────────────
    cout << "\n[Fill] enqueue 10,20,30,40 (4 of 5 slots — one kept free)\n";
    q.enqueue(10); q.enqueue(20); q.enqueue(30); q.enqueue(40);
    q.display();
    cout << "  isFull: " << boolalpha << q.isFull() << "  (4 usable slots hold ≤4)\n";

    // ── [Wrap] dequeue frees front, then enqueue wraps rear ──────────────────
    cout << "\n[Wrap] dequeue twice (frees slots 0,1), then enqueue 50,60\n";
    bool ok;
    cout << "  dequeued " << q.dequeue(ok) << ", " << q.dequeue(ok) << "\n";
    q.display();
    q.enqueue(50); q.enqueue(60);   // rear wraps from 4 → 0 → 1
    cout << "  after wrap enqueue:\n";
    q.display();
    cout << "  -> rear (1) is now BEHIND front (2): the ring wrapped.\n";

    // ── [Front/peek] ─────────────────────────────────────────────────────────
    cout << "\n[Peek] front -> " << q.peek(ok) << "\n";

    // ── [Full] ───────────────────────────────────────────────────────────────
    cout << "\n[Full] ring now full (4 elements, 1 slot wasted by design)\n";
    cout << "  enqueue(70):\n";
    q.enqueue(70);
    cout << "  isFull: " << boolalpha << q.isFull() << "\n";

    // ── [Drain] ──────────────────────────────────────────────────────────────
    cout << "\n[Drain] dequeue until empty (note FIFO order across the wrap)\n";
    while (!q.isEmpty())
        cout << "  dequeued " << q.dequeue(ok) << "\n";
    cout << "  isEmpty: " << boolalpha << q.isEmpty() << "  (front=rear=-1 reset)\n";

    cout << "\n===========================================================\n";
    return 0;
}

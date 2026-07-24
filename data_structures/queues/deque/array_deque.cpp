#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Deque (Double-Ended Queue) — Array-backed ring buffer
//   Insert/remove at BOTH ends in O(1). Implemented as a circular buffer where
//   front moves backward (wrapping) and rear moves forward (wrapping).
//   • Same empty/full convention as the circular queue:
//       EMPTY : front == -1
//       FULL  : (rear + 1) % MAX == front   (one slot wasted)
// ─────────────────────────────────────────────────────────────────────────────

class Deque {
private:
    static const int MAX = 6;     // 5 usable slots (1 wasted to disambiguate)
    int arr[MAX];
    int front;
    int rear;

public:
    Deque() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() const { return front == -1; }
    bool isFull()  const { return (rear + 1) % MAX == front; }

    int size() const {
        if (isEmpty()) return 0;
        return ((rear - front + MAX) % MAX) + 1;
    }

    bool pushFront(int value) {
        if (isFull()) { cout << "  (overflow: deque full)\n"; return false; }
        if (isEmpty())       front = rear = 0;
        else if (front == 0) front = MAX - 1;   // wrap backward
        else                 front--;
        arr[front] = value;
        return true;
    }

    bool pushBack(int value) {
        if (isFull()) { cout << "  (overflow: deque full)\n"; return false; }
        if (isEmpty()) front = rear = 0;
        else           rear = (rear + 1) % MAX;  // wrap forward
        arr[rear] = value;
        return true;
    }

    int popFront(bool& ok) {
        if (isEmpty()) { cout << "  (underflow: popFront on empty)\n"; ok = false; return -1; }
        ok = true;
        int v = arr[front];
        if (front == rear) front = rear = -1;
        else               front = (front + 1) % MAX;
        return v;
    }

    int popBack(bool& ok) {
        if (isEmpty()) { cout << "  (underflow: popBack on empty)\n"; ok = false; return -1; }
        ok = true;
        int v = arr[rear];
        if (front == rear)   front = rear = -1;
        else if (rear == 0)  rear = MAX - 1;     // wrap backward
        else                 rear--;
        return v;
    }

    int getFront(bool& ok) const {
        if (isEmpty()) { ok = false; return -1; }
        ok = true; return arr[front];
    }
    int getBack(bool& ok) const {
        if (isEmpty()) { ok = false; return -1; }
        ok = true; return arr[rear];
    }

    void clear() { front = rear = -1; }

    void display() const {
        cout << "  Front -> ";
        if (isEmpty()) { cout << "(empty) <- Rear\n"; return; }
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % MAX;
        }
        cout << "<- Rear   (size " << size()
             << ", frontIdx " << front << ", rearIdx " << rear << ")\n";
    }

    ~Deque() = default;
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "=========== Deque (Array ring buffer, cap 5) ===========\n";

    Deque dq;
    bool ok;

    // ── [Build] both ends ────────────────────────────────────────────────────
    cout << "\n[Build] pushBack 20,30,40  then pushFront 10\n";
    dq.pushBack(20); dq.pushBack(30); dq.pushBack(40);
    dq.pushFront(10);
    dq.display();
    cout << "  front -> " << dq.getFront(ok) << "   back -> " << dq.getBack(ok) << "\n";

    // ── [Wrap] pushBack past the end wraps rear around ───────────────────────
    cout << "\n[Wrap] pushBack 50 (fills), then pushFront 5 — front wraps to MAX-1\n";
    dq.pushBack(50);
    dq.display();
    cout << "  isFull: " << boolalpha << dq.isFull() << "\n";
    cout << "  pushFront(5) when full:\n";
    dq.pushFront(5);   // overflow

    // ── [Pop] both ends ──────────────────────────────────────────────────────
    cout << "\n[Pop] popFront -> " << dq.popFront(ok)
         << ", popBack -> " << dq.popBack(ok) << "\n";
    dq.display();

    // ── [Reuse] freed slots are reusable (unlike a linear array queue) ───────
    cout << "\n[Reuse] pushFront(5) now succeeds (slot freed)\n";
    dq.pushFront(5);
    dq.display();

    // ── [Edge] underflow ─────────────────────────────────────────────────────
    cout << "\n[Edge] drain then pop on empty\n";
    dq.clear();
    cout << "  popFront on empty -> " << dq.popFront(ok) << "  (ok=" << boolalpha << ok << ")\n";
    cout << "  popBack  on empty -> " << dq.popBack(ok)  << "  (ok=" << ok << ")\n";

    cout << "\n=======================================================\n";
    return 0;
}

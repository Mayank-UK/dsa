#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Stack — Array-backed (fixed capacity)
//   LIFO: last in, first out. All operations O(1).
//   • Bounded by MAX. Pushing when full → overflow. Popping when empty →
//     underflow. Both are handled gracefully (no crash, returns a sentinel).
// ─────────────────────────────────────────────────────────────────────────────

class Stack {
private:
    static const int MAX = 5;   // small on purpose → demo overflow quickly
    int arr[MAX];
    int top;

public:
    Stack() {
        top = -1;               // -1 means "no element"
    }

    // Returns false on overflow instead of silently dropping the value.
    bool push(int value) {
        if (isFull()) {
            cout << "  (overflow: cannot push " << value << ", stack is full)\n";
            return false;
        }
        arr[++top] = value;
        return true;
    }

    // Pops and returns the value; sets ok=false on underflow.
    int pop(bool& ok) {
        if (isEmpty()) {
            cout << "  (underflow: pop on empty stack)\n";
            ok = false;
            return -1;
        }
        ok = true;
        return arr[top--];
    }

    int peek(bool& ok) const {
        if (isEmpty()) {
            ok = false;
            return -1;
        }
        ok = true;
        return arr[top];
    }

    bool isEmpty() const { return top == -1; }
    bool isFull()  const { return top == MAX - 1; }
    int  size()    const { return top + 1; }
    int  capacity() const { return MAX; }

    void clear() { top = -1; }

    // Prints top-down so the LIFO order is visually obvious.
    void display() const {
        if (isEmpty()) { cout << "  | (empty) |\n"; return; }
        for (int i = top; i >= 0; i--)
            cout << "  |   " << arr[i] << (i == top ? "   <- top" : "") << "\n";
        cout << "  +--------+\n";
    }

    ~Stack() = default;
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "============= Stack (Array, capacity 5) =============\n";

    Stack s;

    // ── [Push] ───────────────────────────────────────────────────────────────
    cout << "\n[Push] 10, 20, 30\n";
    s.push(10); s.push(20); s.push(30);
    s.display();
    cout << "  size: " << s.size() << "  capacity: " << s.capacity() << "\n";

    // ── [Peek] ───────────────────────────────────────────────────────────────
    cout << "\n[Peek]\n";
    bool ok;
    cout << "  top -> " << s.peek(ok) << "\n";

    // ── [Pop] before/after ───────────────────────────────────────────────────
    cout << "\n[Pop]\n";
    cout << "  Before:\n"; s.display();
    cout << "  popped -> " << s.pop(ok) << "\n";
    cout << "  After:\n";  s.display();

    // ── [Edge] overflow ──────────────────────────────────────────────────────
    cout << "\n[Edge] Fill to capacity then overflow\n";
    s.push(40); s.push(50); s.push(60);   // now full (5 elements)
    s.display();
    cout << "  isFull: " << boolalpha << s.isFull() << "\n";
    cout << "  push(70):\n";
    s.push(70);                           // overflow — rejected

    // ── [Edge] underflow ─────────────────────────────────────────────────────
    cout << "\n[Edge] Drain the stack then pop/peek on empty\n";
    s.clear();
    cout << "  size after clear: " << s.size() << "\n";
    cout << "  pop on empty -> " << s.pop(ok) << "  (ok=" << boolalpha << ok << ")\n";
    cout << "  peek on empty -> " << s.peek(ok) << "  (ok=" << ok << ")\n";

    cout << "\n=====================================================\n";
    return 0;
}

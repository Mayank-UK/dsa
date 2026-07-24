#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Stack — Linked-list-backed (dynamic capacity)
//   LIFO. The linked-list head IS the stack top, so push/pop are O(1) and the
//   stack grows without bound (limited only by memory). No overflow possible.
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

class Stack {
private:
    Node* top;
    int len;

public:
    Stack() {
        top = nullptr;
        len = 0;
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;     // new node points at the old top
        top = newNode;
        len++;
    }

    int pop(bool& ok) {
        if (isEmpty()) {
            cout << "  (underflow: pop on empty stack)\n";
            ok = false;
            return -1;
        }
        ok = true;
        Node* temp = top;
        int value = top->data;
        top = top->next;
        delete temp;
        len--;
        return value;
    }

    int peek(bool& ok) const {
        if (isEmpty()) {
            ok = false;
            return -1;
        }
        ok = true;
        return top->data;
    }

    bool isEmpty() const { return top == nullptr; }
    int  size()    const { return len; }

    void clear() {
        bool ok;
        while (!isEmpty()) pop(ok);
    }

    void display() const {
        if (isEmpty()) { cout << "  | (empty) |\n"; return; }
        const Node* current = top;
        bool first = true;
        while (current != nullptr) {
            cout << "  |   " << current->data << (first ? "   <- top" : "") << "\n";
            first = false;
            current = current->next;
        }
        cout << "  +--------+\n";
    }

    ~Stack() { clear(); }
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "=========== Stack (Linked List, dynamic) ===========\n";

    Stack s;

    // ── [Push] ───────────────────────────────────────────────────────────────
    cout << "\n[Push] 10, 20, 30\n";
    s.push(10); s.push(20); s.push(30);
    s.display();
    cout << "  size: " << s.size() << "\n";

    // ── [Peek] ───────────────────────────────────────────────────────────────
    cout << "\n[Peek]\n";
    bool ok;
    cout << "  top -> " << s.peek(ok) << "\n";

    // ── [Pop] before/after ───────────────────────────────────────────────────
    cout << "\n[Pop]\n";
    cout << "  Before:\n"; s.display();
    cout << "  popped -> " << s.pop(ok) << "\n";
    cout << "  After:\n";  s.display();

    // ── [Capacity] grows without bound ───────────────────────────────────────
    cout << "\n[Grow] Pushing 5 more — no overflow (dynamic)\n";
    s.push(40); s.push(50); s.push(60); s.push(70); s.push(80);
    s.display();
    cout << "  size: " << s.size() << "\n";

    // ── [Edge] underflow ─────────────────────────────────────────────────────
    cout << "\n[Edge] Drain the stack then operate on empty\n";
    s.clear();
    cout << "  size after clear: " << s.size() << "\n";
    cout << "  pop on empty -> " << s.pop(ok) << "  (ok=" << boolalpha << ok << ")\n";
    cout << "  peek on empty -> " << s.peek(ok) << "  (ok=" << ok << ")\n";

    cout << "\n====================================================\n";
    return 0;
}

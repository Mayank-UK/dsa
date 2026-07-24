#include <iostream>
#include <stdexcept>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Dynamic Array (vector-like)
//   Backed by a heap array that GROWS. When full, capacity DOUBLES and the
//   contents are copied — amortized O(1) push_back. Shrinking is optional.
// ─────────────────────────────────────────────────────────────────────────────

class Vector {
private:
    int* arr;
    int capacity;
    int length;

    // Double the buffer and copy. This is what makes growth amortized O(1).
    void resizeArray(int oldCap) {
        capacity *= 2;
        int* newArr = new int[capacity];
        for (int i = 0; i < length; i++) newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
        cout << "    [resize] capacity " << oldCap << " -> " << capacity
             << " (copied " << length << " elements)\n";
    }

public:
    Vector() {
        capacity = 1;
        length = 0;
        arr = new int[capacity];
    }

    void push_back(int value) {
        if (length == capacity) resizeArray(capacity);
        arr[length++] = value;
    }

    void pop_back() {
        if (isEmpty()) { cout << "  (vector empty)\n"; return; }
        length--;
    }

    void insert(int index, int value) {
        if (index < 0 || index > length) { cout << "  (invalid index)\n"; return; }
        if (length == capacity) resizeArray(capacity);
        for (int i = length; i > index; i--) arr[i] = arr[i - 1];
        arr[index] = value;
        length++;
    }

    void erase(int index) {
        if (index < 0 || index >= length) { cout << "  (invalid index)\n"; return; }
        for (int i = index; i < length - 1; i++) arr[i] = arr[i + 1];
        length--;
    }

    int at(int index) const {
        if (index < 0 || index >= length) throw out_of_range("Invalid Index");
        return arr[index];
    }

    int operator[](int index) const { return arr[index]; }

    int front() const { return arr[0]; }
    int back()  const { return arr[length - 1]; }
    int size()  const { return length; }
    int getCapacity() const { return capacity; }
    bool isEmpty() const { return length == 0; }

    // Logical clear (keeps the buffer allocated — like std::vector's clear).
    void clear() { length = 0; }

    void display() const {
        cout << "  [ ";
        for (int i = 0; i < length; i++) cout << arr[i] << " ";
        cout << "]   (length " << length << " / capacity " << capacity << ")\n";
    }

    ~Vector() { delete[] arr; }
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "=============== Dynamic Array (vector) ===============\n";

    Vector v;

    // ── [Grow] amortized doubling ────────────────────────────────────────────
    cout << "\n[Grow] push_back 1..8 — watch capacity double 1->2->4->8\n";
    for (int i = 1; i <= 8; i++) v.push_back(i);
    v.display();

    // ── [Stats] ──────────────────────────────────────────────────────────────
    cout << "\n[Stats]\n";
    cout << "  size     : " << v.size() << "\n";
    cout << "  capacity : " << v.getCapacity() << "\n";
    cout << "  front    : " << v.front() << "\n";
    cout << "  back     : " << v.back() << "\n";

    // ── [Insert] forces one more doubling ────────────────────────────────────
    cout << "\n[Insert] insert(2, 99) when length==capacity → another resize\n";
    v.insert(2, 99);
    v.display();

    // ── [Erase] ──────────────────────────────────────────────────────────────
    cout << "\n[Erase] erase(4)\n";
    v.erase(4);
    v.display();

    // ── [Access] bounds-checked ──────────────────────────────────────────────
    cout << "\n[Access]\n";
    cout << "  at(0)  -> " << v.at(0) << "\n";
    try {
        cout << "  at(500)-> "; cout << v.at(500) << "\n";
    } catch (const out_of_range& e) {
        cout << "(rejected: " << e.what() << ")\n";
    }

    // ── [Clear] ──────────────────────────────────────────────────────────────
    cout << "\n[Clear] logical clear — length 0, capacity unchanged\n";
    v.clear();
    v.display();

    cout << "\n======================================================\n";
    return 0;
}

#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Fixed-capacity Array
//   A plain contiguous array with a length tracker. Insert/remove shift
//   elements (O(n)). Bounded by MAX; bounds-checked access.
// ─────────────────────────────────────────────────────────────────────────────

class Array {
private:
    static const int MAX = 100;
    int arr[MAX];
    int length;

public:
    Array() : length(0) {}

    bool push_back(int value) {
        if (isFull()) { cout << "  (array full)\n"; return false; }
        arr[length++] = value;
        return true;
    }

    bool insert(int index, int value) {
        if (isFull())                  { cout << "  (array full)\n";      return false; }
        if (index < 0 || index > length) { cout << "  (invalid index)\n"; return false; }
        for (int i = length; i > index; i--) arr[i] = arr[i - 1];
        arr[index] = value;
        length++;
        return true;
    }

    bool remove(int index) {
        if (index < 0 || index >= length) { cout << "  (invalid index)\n"; return false; }
        for (int i = index; i < length - 1; i++) arr[i] = arr[i + 1];
        length--;
        return true;
    }

    int search(int value) const {
        for (int i = 0; i < length; i++) if (arr[i] == value) return i;
        return -1;
    }

    bool get(int index, int& out) const {
        if (index < 0 || index >= length) return false;
        out = arr[index]; return true;
    }

    bool set(int index, int value) {
        if (index < 0 || index >= length) return false;
        arr[index] = value; return true;
    }

    int  size()     const { return length; }
    bool isEmpty()  const { return length == 0; }
    bool isFull()   const { return length == MAX; }
    int  capacity() const { return MAX; }

    void display() const {
        cout << "  [ ";
        for (int i = 0; i < length; i++) cout << arr[i] << " ";
        cout << "]   (length " << length << " / capacity " << MAX << ")\n";
    }
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "================= Fixed Array =================\n";

    Array arr;

    // ── [Build] ──────────────────────────────────────────────────────────────
    cout << "\n[Build] push_back 10,20,30\n";
    arr.push_back(10); arr.push_back(20); arr.push_back(30);
    arr.display();

    // ── [Insert] with shift ──────────────────────────────────────────────────
    cout << "\n[Insert] insert(1, 15) — elements shift right\n";
    cout << "  Before: "; arr.display();
    arr.insert(1, 15);
    cout << "  After : "; arr.display();

    // ── [Remove] ─────────────────────────────────────────────────────────────
    cout << "\n[Remove] remove(2) — elements shift left\n";
    arr.remove(2);
    arr.display();

    // ── [Query] ──────────────────────────────────────────────────────────────
    cout << "\n[Query]\n";
    cout << "  search(30)  -> index " << arr.search(30) << "\n";
    cout << "  search(999) -> " << (arr.search(999) == -1 ? "not found" : "found") << "\n";
    int v;
    if (arr.get(1, v)) cout << "  get(1)      -> " << v << "\n";
    if (!arr.get(99, v)) cout << "  get(99)     -> out of range (rejected)\n";

    // ── [Set] ────────────────────────────────────────────────────────────────
    cout << "\n[Set] set(1, 100)\n";
    arr.set(1, 100);
    arr.display();

    // ── [Edge] invalid index ─────────────────────────────────────────────────
    cout << "\n[Edge] insert at out-of-range index\n";
    arr.insert(500, 7);

    cout << "\n===============================================\n";
    return 0;
}

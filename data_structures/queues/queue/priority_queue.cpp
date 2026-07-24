
#include <iostream>
#include <vector>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Priority Queue — binary MAX-heap backed by a vector
//   Highest value = highest priority. push/pop/top are O(log n).
//   • Heap invariant: every parent ≥ its children (stored level-order in array).
//   • top() is always the maximum. pop() removes the max and re-heapifies.
// ─────────────────────────────────────────────────────────────────────────────

class PriorityQueue {

private:

    vector<int> heap;

    int parent(int index)     { return (index - 1) / 2; }
    int leftChild(int index)  { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }

    // Sift a newly inserted leaf up to its proper place.
    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)] < heap[index]) {
            swap(heap[parent(index)], heap[index]);
            index = parent(index);
        }
    }

    // Sift the moved-down root into place after a pop.
    void heapifyDown(int index) {

        int size = heap.size();

        while (true) {

            int largest = index;
            int left = leftChild(index);
            int right = rightChild(index);

            if (left < size && heap[left] > heap[largest])
                largest = left;

            if (right < size && heap[right] > heap[largest])
                largest = right;

            if (largest == index)
                break;

            swap(heap[index], heap[largest]);
            index = largest;
        }
    }

public:

    // Insert (O(log n))
    void push(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Remove the highest-priority element (O(log n))
    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
            heapifyDown(0);
    }

    // Highest-priority element (O(1))
    int top() const {
        if (heap.empty()) return -1;
        return heap[0];
    }

    int size() const       { return heap.size(); }
    bool empty() const     { return heap.empty(); }
    void clear()           { heap.clear(); }

    // Linear search (O(n))
    bool contains(int value) const {
        for (int element : heap)
            if (element == value) return true;
        return false;
    }

    // Remove a specific value (O(n) to find + O(log n) to fix).
    void remove(int value) {

        int index = -1;
        for (int i = 0; i < (int)heap.size(); i++) {
            if (heap[i] == value) { index = i; break; }
        }
        if (index == -1) return;

        heap[index] = heap.back();
        heap.pop_back();

        if (index < (int)heap.size()) {
            heapifyUp(index);
            heapifyDown(index);
        }
    }

    // Print the raw array (heap order, NOT sorted).
    void display() const {
        cout << "  [heap array] ";
        for (int value : heap) cout << value << " ";
        cout << "\n";
    }
};

// ─────────────────────────────── Demo ────────────────────────────────────────

int main() {

    cout << "============ Priority Queue (max-heap) ============\n";

    PriorityQueue pq;

    // ── [Build] ──────────────────────────────────────────────────────────────
    cout << "\n[Build] push 40,10,70,30,90,20,80 (arbitrary order)\n";
    pq.push(40); pq.push(10); pq.push(70); pq.push(30);
    pq.push(90); pq.push(20); pq.push(80);
    pq.display();
    cout << "  top (max priority) -> " << pq.top() << "\n";
    cout << "  size                -> " << pq.size() << "\n";

    // ── [Query] ──────────────────────────────────────────────────────────────
    cout << "\n[Query]\n";
    cout << "  contains(30)  -> " << (pq.contains(30)  ? "Yes" : "No") << "\n";
    cout << "  contains(100) -> " << (pq.contains(100) ? "Yes" : "No") << "\n";

    // ── [Pop] always yields the current max ──────────────────────────────────
    cout << "\n[Pop] removing the max twice\n";
    cout << "  popped max -> " << pq.top() << "\n"; pq.pop();
    cout << "  new top    -> " << pq.top() << "\n"; pq.pop();
    pq.display();

    // ── [Drain] by priority — descending order ───────────────────────────────
    cout << "\n[Drain] pop everything → elements emerge in DESCENDING priority\n";
    cout << "  order: ";
    while (!pq.empty()) { cout << pq.top() << " "; pq.pop(); }
    cout << "\n";

    // ── [Remove] arbitrary element ───────────────────────────────────────────
    cout << "\n[Remove] rebuild, then remove a middle element\n";
    pq.push(40); pq.push(10); pq.push(70); pq.push(30); pq.push(90);
    pq.display();
    cout << "  remove(70)\n";
    pq.remove(70);
    pq.display();
    cout << "  top -> " << pq.top() << "  (still 90, heap invariant restored)\n";

    // ── [Clear] ──────────────────────────────────────────────────────────────
    cout << "\n[Clear] empty the queue\n";
    pq.clear();
    cout << "  empty -> " << boolalpha << pq.empty() << "\n";

    cout << "\n===================================================\n";
    return 0;
}

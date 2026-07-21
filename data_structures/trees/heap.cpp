#include <iostream>
#include <vector>

using namespace std;

class MaxHeap {

private:

    vector<int> heap;

    // ---------------- Index Helpers ----------------

    int parent(int index) {
        return (index - 1) / 2;
    }

    int leftChild(int index) {
        return 2 * index + 1;
    }

    int rightChild(int index) {
        return 2 * index + 2;
    }

    // ---------------- Heapify Up ----------------

    void heapifyUp(int index) {

        while (index > 0 &&
               heap[parent(index)] < heap[index]) {

            swap(heap[parent(index)],
                 heap[index]);

            index = parent(index);
        }
    }

    // ---------------- Heapify Down ----------------

    void heapifyDown(int index) {

        int size = heap.size();

        while (true) {

            int largest = index;

            int left = leftChild(index);
            int right = rightChild(index);

            if (left < size &&
                heap[left] > heap[largest])
                largest = left;

            if (right < size &&
                heap[right] > heap[largest])
                largest = right;

            if (largest == index)
                break;

            swap(heap[index],
                 heap[largest]);

            index = largest;
        }
    }

public:

    // ---------------- Insert ----------------

    void insert(int value) {

        heap.push_back(value);

        heapifyUp(heap.size() - 1);
    }

    // ---------------- Extract Max ----------------

    int extractMax() {

        if (heap.empty())
            return -1;

        int maximum = heap[0];

        heap[0] = heap.back();

        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);

        return maximum;
    }

    // ---------------- Peek ----------------

    int peek() {

        if (heap.empty())
            return -1;

        return heap[0];
    }

    // ---------------- Search ----------------

    bool search(int value) {

        for (int num : heap)
            if (num == value)
                return true;

        return false;
    }

    // ---------------- Remove ----------------

    void remove(int value) {

        int index = -1;

        for (int i = 0; i < heap.size(); i++) {

            if (heap[i] == value) {

                index = i;
                break;
            }
        }

        if (index == -1)
            return;

        heap[index] = heap.back();

        heap.pop_back();

        if (index < heap.size()) {

            heapifyUp(index);

            heapifyDown(index);
        }
    }

    // ---------------- Display ----------------

    void display() {

        for (int value : heap)
            cout << value << " ";

        cout << endl;
    }

        // ---------------- Size ----------------

    int size() {
        return heap.size();
    }

    // ---------------- Empty ----------------

    bool empty() {
        return heap.empty();
    }

    // ---------------- Clear ----------------

    void clear() {
        heap.clear();
    }

    // ---------------- Build Heap ----------------

    void buildHeap(const vector<int>& values) {

        heap = values;

        for (int i = parent(heap.size() - 1); i >= 0; i--)
            heapifyDown(i);
    }

    // ---------------- Heap Sort ----------------

    void heapSort() {

        MaxHeap temp;

        temp.heap = heap;

        cout << "Sorted (Descending): ";

        while (!temp.empty()) {

            cout << temp.extractMax() << " ";
        }

        cout << endl;
    }

};

int main() {

    MaxHeap heap;

    cout << "Building Heap...\n";

    vector<int> values = {
        50, 30, 70, 20, 40,
        60, 80, 10, 90, 35
    };

    heap.buildHeap(values);

    cout << "Heap: ";
    heap.display();

    cout << "\nInsert 100\n";
    heap.insert(100);
    heap.display();

    cout << "\nInsert 55\n";
    heap.insert(55);
    heap.display();

    cout << "\nMaximum: " << heap.peek() << endl;

    cout << "Size: " << heap.size() << endl;

    cout << "\nSearch 60: " << (heap.search(60) ? "Found" : "Not Found") << endl;

    cout << "Search 500: " << (heap.search(500) ? "Found" : "Not Found") << endl;

    cout << "\nRemove 70\n";
    heap.remove(70);
    heap.display();

    cout << "\nExtract Max: " << heap.extractMax() << endl;

    cout << "Heap After Extract:\n";
    heap.display();

    cout << "\nHeap Sort\n";
    heap.heapSort();

    cout << "\nClear Heap\n";
    heap.clear();

    cout << "Empty: " << (heap.empty() ? "Yes" : "No") << endl;

    return 0;
}
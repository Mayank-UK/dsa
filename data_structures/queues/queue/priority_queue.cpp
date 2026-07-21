
#include <iostream>
#include <vector>

using namespace std;

class PriorityQueue {

private:

    vector<int> heap;

    int parent(int index) {
        return (index - 1) / 2;
    }

    int leftChild(int index) {
        return 2 * index + 1;
    }

    int rightChild(int index) {
        return 2 * index + 2;
    }

    void heapifyUp(int index) {

        while (index > 0 && heap[parent(index)] < heap[index]) {

            swap(heap[parent(index)], heap[index]);

            index = parent(index);
        }
    }

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

            swap(heap[index], heap[largest]);

            index = largest;
        }
    }

public:

    // Insert element
    void push(int value) {

        heap.push_back(value);

        heapifyUp(heap.size() - 1);
    }

    // Remove highest priority element
    void pop() {

        if (heap.empty())
            return;

        heap[0] = heap.back();

        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);
    }

    // Highest priority element
    int top() {

        if (heap.empty())
            return -1;

        return heap[0];
    }

    // Number of elements
    int size() {

        return heap.size();
    }

    // Is empty?
    bool empty() {

        return heap.empty();
    }

    // Clear queue
    void clear() {

        heap.clear();
    }

    // Search (O(n))
    bool contains(int value) {

        for (int element : heap)
            if (element == value)
                return true;

        return false;
    }

    // Remove a specific value
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

    // Print heap
    void display() {

        for (int value : heap)
            cout << value << " ";

        cout << endl;
    }
};

int main() {

    PriorityQueue pq;

    pq.push(40);
    pq.push(10);
    pq.push(70);
    pq.push(30);
    pq.push(90);
    pq.push(20);
    pq.push(80);

    cout << "Priority Queue: ";
    pq.display();

    cout << "\nTop: " << pq.top() << endl;

    cout << "Size: " << pq.size() << endl;

    cout << "\nContains 30: " << (pq.contains(30) ? "Yes" : "No") << endl;

    cout << "Contains 100: " << (pq.contains(100) ? "Yes" : "No") << endl;

    cout << "\nPop\n";

    pq.pop();

    pq.display();

    cout << "\nTop: " << pq.top() << endl;

    cout << "\nRemove 40\n";

    pq.remove(40);

    pq.display();

    cout << "\nPush 100\n";

    pq.push(100);

    pq.display();

    cout << "\nTop: " << pq.top() << endl;

    cout << "\nClear Queue\n";

    pq.clear();

    cout << "Empty: " << (pq.empty() ? "Yes" : "No") << endl;

    return 0;
}
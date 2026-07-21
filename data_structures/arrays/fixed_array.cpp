#include <iostream>
using namespace std;

class Array {
private:
    static const int MAX = 100;
    int arr[MAX];
    int length;

public:
    Array() {
        length = 0;
    }

    // Insert at end
    void push_back(int value) {

        if (isFull()) {
            cout << "Array is Full\n";
            return;
        }

        arr[length++] = value;
    }

    // Insert at index
    void insert(int index, int value) {

        if (isFull()) {
            cout << "Array is Full\n";
            return;
        }

        if (index < 0 || index > length) {
            cout << "Invalid Index\n";
            return;
        }

        for (int i = length; i > index; i--)
            arr[i] = arr[i - 1];

        arr[index] = value;
        length++;
    }

    // Remove at index
    void remove(int index) {

        if (index < 0 || index >= length) {
            cout << "Invalid Index\n";
            return;
        }

        for (int i = index; i < length - 1; i++)
            arr[i] = arr[i + 1];

        length--;
    }

    // Search
    int search(int value) {

        for (int i = 0; i < length; i++) {
            if (arr[i] == value)
                return i;
        }

        return -1;
    }

    // Get
    int get(int index) {

        if (index < 0 || index >= length) {
            cout << "Invalid Index\n";
            return -1;
        }

        return arr[index];
    }

    // Set
    void set(int index, int value) {

        if (index < 0 || index >= length) {
            cout << "Invalid Index\n";
            return;
        }

        arr[index] = value;
    }

    int size() {
        return length;
    }

    bool isEmpty() {
        return length == 0;
    }

    bool isFull() {
        return length == MAX;
    }

    void display() {

        cout << "[ ";

        for (int i = 0; i < length; i++)
            cout << arr[i] << " ";

        cout << "]\n";
    }
};

int main() {

    Array arr;

    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    arr.display();

    arr.insert(1, 15);

    arr.display();

    arr.remove(2);

    arr.display();

    cout << "Index of 30: " << arr.search(30) << endl;

    cout << "Element at index 1: " << arr.get(1) << endl;

    arr.set(1, 100);

    arr.display();

    cout << "Size: " << arr.size() << endl;

    return 0;
}
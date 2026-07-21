#include <iostream>
using namespace std;

class Vector {
private:
    int* arr;
    int capacity;
    int length;

    void resizeArray() {

        capacity *= 2;

        int* newArr = new int[capacity];

        for (int i = 0; i < length; i++)
            newArr[i] = arr[i];

        delete[] arr;

        arr = newArr;
    }

public:

    Vector() {
        capacity = 1;
        length = 0;
        arr = new int[capacity];
    }

    void push_back(int value) {

        if (length == capacity)
            resizeArray();

        arr[length++] = value;
    }

    void pop_back() {

        if (isEmpty()) {
            cout << "Vector is Empty\n";
            return;
        }

        length--;
    }

    void insert(int index, int value) {

        if (index < 0 || index > length) {
            cout << "Invalid Index\n";
            return;
        }

        if (length == capacity)
            resizeArray();

        for (int i = length; i > index; i--)
            arr[i] = arr[i - 1];

        arr[index] = value;
        length++;
    }

    void erase(int index) {

        if (index < 0 || index >= length) {
            cout << "Invalid Index\n";
            return;
        }

        for (int i = index; i < length - 1; i++)
            arr[i] = arr[i + 1];

        length--;
    }

    int operator[](int index) {
        return arr[index];
    }

    int at(int index) {

        if (index < 0 || index >= length)
            throw out_of_range("Invalid Index");

        return arr[index];
    }

    int front() {
        return arr[0];
    }

    int back() {
        return arr[length - 1];
    }

    int size() {
        return length;
    }

    int getCapacity() {
        return capacity;
    }

    bool isEmpty() {
        return length == 0;
    }

    void clear() {
        length = 0;
    }

    void display() {

        cout << "[ ";

        for (int i = 0; i < length; i++)
            cout << arr[i] << " ";

        cout << "]\n";
    }

    ~Vector() {
        delete[] arr;
    }
};

int main() {

    Vector v;

    for (int i = 1; i <= 10; i++)
        v.push_back(i * 10);

    v.display();

    cout << "Size: " << v.size() << endl;
    cout << "Capacity: " << v.getCapacity() << endl;

    v.insert(2, 25);

    v.display();

    v.erase(4);

    v.display();

    cout << "Front: " << v.front() << endl;
    cout << "Back : " << v.back() << endl;
}
/*
            ############################################# Practice round 1 #############################################
*/

// #include <iostream>
// using namespace std;

// class FxArray {
//     private:
//         static const int arrMaxCapacity = 100;
//         int arrLength = 0;
//         int arr[arrMaxCapacity];

//     public:
//         FxArray() : arrLength(0) {}

//         bool push(int value) {
//             if(arrLength == arrMaxCapacity) {
//                 cout << "Array is full";
//                 return false;
//             }

//             arr[arrLength++] = value;
//             return true;
//         }

//         bool setAtIndex(int index, int value) {
//             if (index < 0 || index > (arrLength-1)) {
//                 cout << "Invalid index " << index << "\n";
//                 return false;
//             }

//             arr[index] = value;

//             if (index >= arrLength && index < arrMaxCapacity) {
//                 arrLength = index+1;
//             }

//             return true;
//         }

//         bool insertAtIndex(int index, int value) {
//             if(arrLength == arrMaxCapacity) {
//                 cout << "Array is full\n";
//                 return false;
//             }

//             if(index < 0 || index > arrLength) {
//                 cout << "Invalid index " << index << "\n";
//                 return false;
//             }

//             for(int i = arrLength; i > index; i--) {
//                 arr[i] = arr[i-1];
//             }

//             arr[index] = value;
//             arrLength++;
//             return true;
//         }

//         bool search(int value) {
//             for (int i = 0; i <= arrLength-1; i++) {
//                 if(arr[i] == value) {
//                     return true;
//                 }
//             }

//             return false;
//         }

//         bool removeAtIndex(int index) {
//             if(index < 0 || index >= arrLength) {
//                 cout << "Invalid index " << index << "\n";
//                 return false;
//             }

//             for(int i = index; i < arrLength-1; i++) {
//                 arr[i] = arr[i+1];
//             }

//             arrLength--;
//             return true;
//         }

//         bool pop() {
//             if (arrLength == 0) {
//                 cout << "Array already empty\n";
//                 return false;
//             }

//             arrLength--;
//             return true;
//         }

//         void printIndex(int index) {
//             cout << "Value at arr[" << index << "]" << arr[index];
//         }

//         void printArray() {
//             cout << "[ ";
//             for (int i = 0; i < arrLength; i++) {
//                 cout << arr[i] << " ";
//             }
//             cout << " ]\n";
//         }

//         int getArrLength() {
//             return arrLength;
//         }
// };

// int main () {
//     FxArray fxArr;

//     fxArr.push(10);
//     fxArr.push(20);
//     fxArr.push(30);
//     fxArr.push(40);
//     fxArr.push(50);

//     cout << "Pushed some values: ";
//     fxArr.printArray();

//     fxArr.setAtIndex(0, 1);
//     fxArr.setAtIndex(1, 2);
//     fxArr.setAtIndex(2, 3);
//     fxArr.setAtIndex(3, 4);
//     fxArr.setAtIndex(4, 5);

//     cout << "Set different values: ";
//     fxArr.printArray();

//     fxArr.push(6);

//     cout << "Pushed a new value: ";
//     fxArr.printArray();

//     fxArr.pop();

//     cout << "Popped";
//     fxArr.printArray();

//     cout << "Set at index 5: ";
//     fxArr.setAtIndex(5, 39);

//     fxArr.insertAtIndex(2, 29);

//     cout << "Insert new value at index 2: ";
//     fxArr.printArray();

//     cout << "Insert new value at index 6: ";
//     fxArr.insertAtIndex(6, 31);

//     fxArr.printArray();

//     cout << "Search for a number: " << fxArr.search(5) << "\n";

//     cout<< "Array length: " << fxArr.getArrLength() << "\n";

//     fxArr.removeAtIndex(2);
//     cout<< "Removed at index 2: ";
//     fxArr.printArray();

//     return 0;

// }

/*
            ############################################# Practice round 2 #############################################
*/

#include <iostream>
using namespace std;

class FixedArray
{
private:
    static const int arrayMaxCapacity = 100;
    int arrayLength;
    int array[arrayMaxCapacity];

public:
    FixedArray() : arrayLength(0) {}

    bool push(int value)
    {
        // 1. Validate arguments
        // 2. Handle edge cases
        // 3. Perform the main algorithm
        // 4. Update metadata/state
        // 5. Return

        // Handle when array is full
        if (arrayLength == arrayMaxCapacity)
        {
            cout << "Array is full\n";
            return false;
        }

        // Handle normal case
        array[arrayLength] = value;
        arrayLength++;

        // Return result
        return true;
    }

    bool setAtIndex(int index, int value)
    {
        if (index < 0 || index >= arrayLength)
        {
            cout << "Invalid index\n";
            return false;
        }

        array[index] = value;

        return true;
    }

    bool insertAtIndex(int index, int value)
    {
        if (arrayLength == arrayMaxCapacity)
        {
            cout << "Array is full\n";
            return false;
        }

        if (index < 0 || index > arrayLength)
        {
            cout << "Invalid index\n";
            return false;
        }

        for (int i = arrayLength; i > index; i--)
        {
            array[i] = array[i - 1];
        }

        array[index] = value;
        arrayLength++;

        return true;
    }

    bool search(int value)
    {
        for (int i = 0; i < arrayLength; i++)
        {
            if (array[i] == value)
            {
                return true;
            }
        }

        return false;
    }

    bool pop()
    {
        if (arrayLength == 0)
        {
            return true;
        }

        arrayLength--;
        return true;
    }

    bool removeAtIndex(int index)
    {
        if (index < 0 || index >= arrayLength)
        {
            cout << "Invalid index\n";
            return false;
        }

        for (int i = index; i < arrayLength - 1; i++)
        {
            array[i] = array[i + 1];
        }

        arrayLength--;
        return true;
    }

    void printArray()
    {
        cout << "[ ";
        for (int i = 0; i < arrayLength; i++)
        {
            cout << array[i] << " ";
        }
        cout << " ]\n";
    }

    int getArrayLength()
    {
        return arrayLength;
    }
};

int main()
{
    FixedArray fxArr;

    fxArr.push(10);
    fxArr.push(20);
    fxArr.push(30);
    fxArr.push(40);
    fxArr.push(50);

    cout << "Pushed some values: ";
    fxArr.printArray();

    fxArr.setAtIndex(0, 1);
    fxArr.setAtIndex(1, 2);
    fxArr.setAtIndex(2, 3);
    fxArr.setAtIndex(3, 4);
    fxArr.setAtIndex(4, 5);

    cout << "Set different values: ";
    fxArr.printArray();

    fxArr.push(6);

    cout << "Pushed a new value: ";
    fxArr.printArray();

    fxArr.pop();

    cout << "Popped";
    fxArr.printArray();

    cout << "Set at index 5: ";
    fxArr.setAtIndex(5, 39);

    fxArr.insertAtIndex(2, 29);

    cout << "Insert new value at index 2: ";
    fxArr.printArray();

    cout << "Insert new value at index 6: ";
    fxArr.insertAtIndex(6, 31);

    fxArr.printArray();

    cout << "Search for a number: " << fxArr.search(5) << "\n";

    cout << "Array length: " << fxArr.getArrayLength() << "\n";

    fxArr.removeAtIndex(2);
    cout << "Removed at index 2: ";
    fxArr.printArray();

    return 0;
}
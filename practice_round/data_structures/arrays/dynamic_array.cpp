/*
            ############################################# Practice round 1 #############################################
*/

// #include <iostream>
// using std::cout;

// class DynamicArray
// {
// private:
//     int arrayMaxCapacity;
//     int arrayLength;
//     int *array;

// public:
//     DynamicArray()
//     {
//         arrayMaxCapacity = 1;
//         arrayLength = 0;
//         array = new int[arrayMaxCapacity];
//     }

//     void resizeArray()
//     {
//         arrayMaxCapacity *= 2;

//         int *newArray = new int[arrayMaxCapacity];

//         for (int i = 0; i < arrayLength; i++)
//         {
//             newArray[i] = array[i];
//         }

//         delete[] array;

//         array = newArray;

//         cout << "Dynamically extended array maxCapacity to " << arrayMaxCapacity << "\n";
//     }

//     bool push(int value)
//     {
//         if (arrayLength == arrayMaxCapacity)
//         {
//             resizeArray();
//         }

//         array[arrayLength] = value;
//         arrayLength++;

//         cout << "Pushed: " << value << "\n";
//         return true;
//     }

//     bool setAtIndex(int index, int value)
//     {
//         if (index < 0 || index >= arrayLength)
//         {
//             cout << "Invalid index\n";
//             return false;
//         }

//         array[index] = value;

//         return true;
//     }

//     bool insertAtIndex(int index, int value)
//     {
//         if (arrayLength == arrayMaxCapacity)
//         {
//             resizeArray();
//         }

//         if (index < 0 || index > arrayLength)
//         {
//             cout << "Invalid index\n";
//             return false;
//         }

//         for (int i = arrayLength; i > index; i--)
//         {
//             array[i] = array[i - 1];
//         }

//         array[index] = value;
//         arrayLength++;

//         return true;
//     }

//     bool search(int value)
//     {
//         for (int i = 0; i < arrayLength; i++)
//         {
//             if (array[i] == value)
//             {
//                 return true;
//             }
//         }

//         return false;
//     }

//     bool pop()
//     {
//         if (arrayLength == 0)
//         {
//             return true;
//         }

//         arrayLength--;
//         return true;
//     }

//     bool removeAtIndex(int index)
//     {
//         if (index < 0 || index >= arrayLength)
//         {
//             cout << "Invalid index\n";
//             return false;
//         }

//         for (int i = index; i < arrayLength - 1; i++)
//         {
//             array[i] = array[i + 1];
//         }

//         arrayLength--;
//         return true;
//     }

//     void printArray()
//     {
//         cout << "[ ";
//         for (int i = 0; i < arrayLength; i++)
//         {
//             cout << array[i] << " ";
//         }
//         cout << " ]\n";
//     }

//     int getArrayLength()
//     {
//         return arrayLength;
//     }
// };

// int main()
// {
//     DynamicArray dyArr;

//     dyArr.push(10);
//     dyArr.push(20);
//     dyArr.push(30);
//     dyArr.push(40);
//     dyArr.push(50);

//     cout << "Pushed some values: ";
//     dyArr.printArray();

//     dyArr.setAtIndex(0, 1);
//     dyArr.setAtIndex(1, 2);
//     dyArr.setAtIndex(2, 3);
//     dyArr.setAtIndex(3, 4);
//     dyArr.setAtIndex(4, 5);

//     cout << "Set different values: ";
//     dyArr.printArray();

//     dyArr.push(6);

//     cout << "Pushed a new value: ";
//     dyArr.printArray();

//     dyArr.pop();

//     cout << "Popped";
//     dyArr.printArray();

//     cout << "Set at index 5: ";
//     dyArr.setAtIndex(5, 39);

//     dyArr.insertAtIndex(2, 29);

//     cout << "Insert new value at index 2: ";
//     dyArr.printArray();

//     cout << "Insert new value at index 6: ";
//     dyArr.insertAtIndex(6, 31);

//     dyArr.printArray();

//     cout << "Search for a number: " << dyArr.search(5) << "\n";

//     cout << "Array length: " << dyArr.getArrayLength() << "\n";

//     dyArr.removeAtIndex(2);
//     cout << "Removed at index 2: ";
//     dyArr.printArray();

//     return 0;
// }

/*
            ############################################# Practice round 2 #############################################
*/

#include <iostream>
using std::cout;

class DynamicArray
{
private:
    int arrayMaxCapacity;
    int arrayLength;
    int *array;

public:
    DynamicArray()
    {
        arrayMaxCapacity = 1;
        arrayLength = 0;
        array = new int[arrayMaxCapacity];
    }

    void resizeArray()
    {
        arrayMaxCapacity *= 2;

        int *newArray = new int[arrayMaxCapacity];

        for (int i = 0; i < arrayLength; i++)
        {
            newArray[i] = array[i];
        }

        delete[] array;

        array = newArray;
    }

    bool push(int value)
    {
        if (arrayLength == arrayMaxCapacity)
        {
            resizeArray();
        }

        array[arrayLength] = value;
        arrayLength++;

        cout << "Pushed: " << value << "\n";
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
            resizeArray();
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
    DynamicArray dyArr;

    dyArr.push(10);
    dyArr.push(20);
    dyArr.push(30);
    dyArr.push(40);
    dyArr.push(50);

    cout << "Pushed some values: ";
    dyArr.printArray();

    dyArr.setAtIndex(0, 1);
    dyArr.setAtIndex(1, 2);
    dyArr.setAtIndex(2, 3);
    dyArr.setAtIndex(3, 4);
    dyArr.setAtIndex(4, 5);

    cout << "Set different values: ";
    dyArr.printArray();

    dyArr.push(6);

    cout << "Pushed a new value: ";
    dyArr.printArray();

    dyArr.pop();

    cout << "Popped";
    dyArr.printArray();

    cout << "Set at index 5: ";
    dyArr.setAtIndex(5, 39);

    dyArr.insertAtIndex(2, 29);

    cout << "Insert new value at index 2: ";
    dyArr.printArray();

    cout << "Insert new value at index 6: ";
    dyArr.insertAtIndex(6, 31);

    dyArr.printArray();

    cout << "Search for a number: " << dyArr.search(5) << "\n";

    cout << "Array length: " << dyArr.getArrayLength() << "\n";

    dyArr.removeAtIndex(2);
    cout << "Removed at index 2: ";
    dyArr.printArray();

    return 0;
}
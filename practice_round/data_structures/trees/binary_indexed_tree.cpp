/*
            ############################################# Practice round 1 #############################################
*/

// #include <iostream>
// #include <array>
// #include <climits>

// using std::array;
// using std::cout;

// /*
//     Binary Indexed Tree is also called Fenwick tree
//     It's called Binary Indexed because it uses binary representation of indexes for calculation
// */

// class FenwickTree
// {
// private:
//     static const int arrSize = 10;
//     array<int, arrSize> arr;
//     // fenArray is 1 indexed (values start from 1 instead of)
//     array<int, arrSize + 1> fenArray{};

//     void buildFenwickTree()
//     {
//         for (int i = 0; i < arrSize; i++)
//         {
//             fenArray[i + 1] = arr[i];
//         }

//         for (int i = 1; i <= arrSize; i++)
//         {
//             int parentIndex = i + (i & -i);

//             if (parentIndex <= arrSize)
//             {
//                 fenArray[parentIndex] += fenArray[i];
//             }
//         }
//     }

//     int prefixSum(int arrIndex)
//     {
//         int fenIndex = arrIndex + 1;
//         int sum = 0;

//         while (fenIndex > 0)
//         {
//             sum += fenArray[fenIndex];
//             fenIndex -= fenIndex & -fenIndex;
//         }

//         return sum;
//     }

// public:
//     FenwickTree()
//     {
//         arr = {2, 4, 5, 7, 8, 9, 1, 6, 3, 11};

//         buildFenwickTree();
//     }

//     int rangeSum(int arrLeftIndex, int arrRightIndex)
//     {
//         if (arrLeftIndex < 0 || arrRightIndex > (arrSize - 1) || arrLeftIndex > arrRightIndex)
//         {
//             cout << "Invalid indexes\n";
//             return INT_MIN;
//         }

//         return prefixSum(arrRightIndex) - prefixSum(arrLeftIndex - 1);
//     }

//     void update(int arrIndex, int value)
//     {
//         if (arrIndex < 0 || arrIndex > (arrSize - 1))
//         {
//             cout << "Invalid index\n";
//             return;
//         }

//         int delta = value - arr[arrIndex];
//         arr[arrIndex] = value;

//         int fenIndex = arrIndex + 1;

//         while (fenIndex <= arrSize)
//         {
//             fenArray[fenIndex] += delta;
//             fenIndex += fenIndex & -fenIndex;
//         }
//     }

//     void displayArray()
//     {
//         for (int i : arr)
//         {
//             cout << i << " ";
//         }

//         cout << "\n";
//     }

//     void displayFenwickTree()
//     {
//         for (int i = 1; i <= arrSize; i++)
//         {
//             cout << fenArray[i] << " ";
//         }

//         cout << "\n";
//     }
// };

// int main()
// {
//     FenwickTree bit;

//     cout << "========== Fenwick Tree ==========\n\n";

//     cout << "===== Original Array =====\n";
//     bit.displayArray();

//     cout << "\n===== Fenwick Tree =====\n";
//     bit.displayFenwickTree();

//     cout << "\n===== Prefix Sum Queries =====\n";

//     cout << "Prefix Sum [0..0] = "
//          << bit.rangeSum(0, 0) << "\n";

//     cout << "Prefix Sum [0..3] = "
//          << bit.rangeSum(0, 3) << "\n";

//     cout << "Prefix Sum [0..7] = "
//          << bit.rangeSum(0, 7) << "\n";

//     cout << "\n===== Range Sum Queries =====\n";

//     cout << "Range Sum [2..5] = "
//          << bit.rangeSum(2, 5) << "\n";

//     cout << "Range Sum [1..6] = "
//          << bit.rangeSum(1, 6) << "\n";

//     cout << "Range Sum [0..9] = "
//          << bit.rangeSum(0, 9) << "\n";

//     cout << "\n===== Update =====\n";

//     cout << "Setting index 3 -> 20\n";
//     bit.update(3, 20);

//     cout << "\nUpdated Array:\n";
//     bit.displayArray();

//     cout << "\nUpdated Fenwick Tree:\n";
//     bit.displayFenwickTree();

//     cout << "\n===== Queries After Update =====\n";

//     cout << "Prefix Sum [0..3] = "
//          << bit.rangeSum(0, 3) << "\n";

//     cout << "Range Sum [2..5] = "
//          << bit.rangeSum(2, 5) << "\n";

//     cout << "Range Sum [0..9] = "
//          << bit.rangeSum(0, 9) << "\n";

//     cout << "\n===== Invalid Index Tests =====\n";

//     bit.update(-1, 50);
//     bit.update(10, 50);

//     cout << "\nInvalid Range Test:\n";
//     cout << bit.rangeSum(7, 3) << "\n";

//     cout << "\n==================================\n";

//     return 0;
// }

/*
            ############################################# Practice round 2 #############################################
*/

#include <iostream>
#include <climits>
#include <array>

using std::array;
using std::cout;

class FenwickTree
{
private:
    static const int arrSize = 10;
    array<int, arrSize> arr;
    array<int, arrSize + 1> fenArray{};

    void buildFenwichTree()
    {
        for (int i = 0; i < arrSize; i++)
        {
            fenArray[i + 1] = arr[i];
        }

        for (int i = 1; i <= arrSize; i++)
        {
            int parent = i + (i & -i);

            if (parent <= arrSize)
            {

                fenArray[parent] += fenArray[i];
            }
        }
    }

    int prefixSum(int arrIndex)
    {
        int fenIndex = arrIndex + 1;
        int sum = 0;

        while (fenIndex > 0)
        {
            sum += fenArray[fenIndex];
            fenIndex -= fenIndex & -fenIndex;
        }

        return sum;
    }

public:
    FenwickTree()
    {
        arr = {2, 4, 5, 7, 8, 9, 1, 6, 3, 11};

        buildFenwichTree();
    }

    int rangeSum(int arrLeftIndex, int arrRightIndex)
    {
        if (arrLeftIndex < 0 || arrRightIndex > (arrSize - 1) || arrLeftIndex > arrRightIndex)
        {
            cout << "Invalid indexes\n";
            return INT_MIN;
        }

        return prefixSum(arrRightIndex) - prefixSum(arrLeftIndex - 1);
    }

    void update(int arrIndex, int newValue)
    {
        if (arrIndex < 0 || arrIndex > (arrSize - 1))
        {
            cout << "Invalid index\n";
            return;
        }

        int delta = newValue - arr[arrIndex];
        arr[arrIndex] = newValue;
        int fenIndex = arrIndex + 1;

        while (fenIndex <= arrSize)
        {
            fenArray[fenIndex] += delta;
            fenIndex += fenIndex & -fenIndex;
        }
    }

    void displayArray()
    {
        for (int i : arr)
        {
            cout << i << " ";
        }

        cout << "\n";
    }

    void displayFenwickTree()
    {
        for (int i = 1; i <= arrSize; i++)
        {
            cout << fenArray[i] << " ";
        }

        cout << "\n";
    }
};

int main()
{
    FenwickTree bit;

    cout << "========== Fenwick Tree ==========\n\n";

    cout << "===== Original Array =====\n";
    bit.displayArray();

    cout << "\n===== Fenwick Tree =====\n";
    bit.displayFenwickTree();

    cout << "\n===== Prefix Sum Queries =====\n";

    cout << "Prefix Sum [0..0] = "
         << bit.rangeSum(0, 0) << "\n";

    cout << "Prefix Sum [0..3] = "
         << bit.rangeSum(0, 3) << "\n";

    cout << "Prefix Sum [0..7] = "
         << bit.rangeSum(0, 7) << "\n";

    cout << "\n===== Range Sum Queries =====\n";

    cout << "Range Sum [2..5] = "
         << bit.rangeSum(2, 5) << "\n";

    cout << "Range Sum [1..6] = "
         << bit.rangeSum(1, 6) << "\n";

    cout << "Range Sum [0..9] = "
         << bit.rangeSum(0, 9) << "\n";

    cout << "\n===== Update =====\n";

    cout << "Setting index 3 -> 20\n";
    bit.update(3, 20);

    cout << "\nUpdated Array:\n";
    bit.displayArray();

    cout << "\nUpdated Fenwick Tree:\n";
    bit.displayFenwickTree();

    cout << "\n===== Queries After Update =====\n";

    cout << "Prefix Sum [0..3] = "
         << bit.rangeSum(0, 3) << "\n";

    cout << "Range Sum [2..5] = "
         << bit.rangeSum(2, 5) << "\n";

    cout << "Range Sum [0..9] = "
         << bit.rangeSum(0, 9) << "\n";

    cout << "\n===== Invalid Index Tests =====\n";

    bit.update(-1, 50);
    bit.update(10, 50);

    cout << "\nInvalid Range Test:\n";
    cout << bit.rangeSum(7, 3) << "\n";

    cout << "\n==================================\n";

    return 0;
}
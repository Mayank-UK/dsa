#include <iostream>
#include <vector>

using namespace std;

// Function to find the maximum element in a unimodal array using ternary search
double ternarySearchPeak(const vector<double>& arr) {
    int low = 0;
    int high = arr.size() - 1;

    while (high - low > 1) {
        int m1 = low + (high - low) / 3;
        int m2 = high - (high - low) / 3;

        if (arr[m1] < arr[m2]) {
            low = m1;
        } else {
            high = m2;
        }
    }

    // Return the maximum value found between low and high
    return max(arr[low], arr[high]);
}

int main() {
    // Unimodal array: strictly increasing then strictly decreasing
    vector<double> arr = {1.2, 3.4, 5.6, 8.9, 12.1, 10.5, 7.2, 4.1};

    double peakValue = ternarySearchPeak(arr);

    cout << "The peak (maximum) value in the unimodal array is: " << peakValue << "\n";

    return 0;
}
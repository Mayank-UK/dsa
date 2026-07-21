#include <iostream>
#include <vector>

using namespace std;

int canCompleteCircuit(const vector<int>& gas, const vector<int>& cost) {
    int totalGas = 0, totalCost = 0;
    int currentTank = 0;
    int startStation = 0;

    for (int i = 0; i < gas.size(); i++) {
        totalGas += gas[i];
        totalCost += cost[i];
        currentTank += gas[i] - cost[i];

        // If the tank drops below zero, we cannot reach the next station from our current start
        if (currentTank < 0) {
            startStation = i + 1; // Try starting at the next station
            currentTank = 0;      // Reset the tank for the new candidate
        }
    }

    // If total gas is less than total cost, completion is impossible
    return (totalGas >= totalCost) ? startStation : -1;
}

int main() {
    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};

    int start = canCompleteCircuit(gas, cost);
    if (start != -1) {
        cout << "Can complete circuit starting at station index: " << start << "\n";
    } else {
        cout << "Cannot complete the circuit.\n";
    }

    return 0;
}
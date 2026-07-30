#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Returns the index of a starting station from which a full clockwise circuit
// is possible, or -1 if no such station exists.
//
// Greedy insight: if total gas >= total cost, a solution always exists, and the
// running surplus (gas - cost) tells us where: once the surplus from a candidate
// start drops negative, no station in [start..i] can work, so advance the
// candidate to i+1 and reset the running tank.
int canCompleteCircuit(const vector<int>& gas, const vector<int>& cost) {
    int totalSurplus = 0;
    int tank = 0;
    int start = 0;

    for (int i = 0; i < (int)gas.size(); i++) {
        int net = gas[i] - cost[i];
        totalSurplus += net;
        tank += net;
        if (tank < 0) {
            start = i + 1;   // every station in the failed run is hopeless
            tank = 0;
        }
    }
    return totalSurplus >= 0 ? start : -1;
}

int main() {
    cout << "================= Gas Station =================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n)   single pass, no nested loop\n";
    cout << "  Space : O(1)\n";
    cout << "  Note  : greedy; valid iff total gas >= total cost\n\n";

    cout << "[Demo]\n";
    vector<int> gas  = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};
    cout << "  gas  = ";
    for (int g : gas)  cout << g << " ";
    cout << "\n  cost = ";
    for (int c : cost) cout << c << " ";
    cout << "\n";
    int start = canCompleteCircuit(gas, cost);
    cout << "  start station = " << (start == -1 ? "Impossible" : to_string(start)) << "\n";
    cout << "  total surplus = " << (gas[0]+gas[1]+gas[2]+gas[3]+gas[4]
                                     - cost[0]-cost[1]-cost[2]-cost[3]-cost[4]) << "\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  impossible (not enough total gas): start = "
         << canCompleteCircuit({1, 2}, {2, 2}) << "  (-1 => Impossible)\n";
    cout << "  single station, feasible : start = "
         << canCompleteCircuit({5}, {4}) << "\n";
    cout << "  single station, infeasible: start = "
         << canCompleteCircuit({3}, {4}) << "\n";
    cout << "  start mid-array        : start = "
         << canCompleteCircuit({4, 5, 1, 2, 3}, {3, 4, 5, 1, 2}) << "\n";
    cout << "\n";

    return 0;
}

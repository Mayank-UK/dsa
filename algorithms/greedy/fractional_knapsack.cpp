#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Structure to represent an item with weight and profit
struct Item {
    int id;
    double weight;
    double profit;
    double ratio;

    // Comparator to sort items in descending order of value-to-weight ratio
    bool operator<(const Item& other) const {
        return ratio > other.ratio;
    }
};

// Structure to track selected items and their fractions
struct ResultItem {
    int id;
    double fractionTaken;
};

// Function to solve the fractional knapsack problem
void fractionalKnapsack(double capacity, vector<Item>& items) {
    // Step 1: Calculate ratios and sort items by ratio descending
    for (auto& item : items) {
        item.ratio = item.profit / item.weight;
    }
    sort(items.begin(), items.end());

    double maxProfit = 0.0;
    double remainingCapacity = capacity;
    vector<ResultItem> takenItems;

    // Step 2: Greedily pick items
    for (const auto& item : items) {
        if (remainingCapacity <= 0) break;

        if (item.weight <= remainingCapacity) {
            // Take the whole item
            remainingCapacity -= item.weight;
            maxProfit += item.profit;
            takenItems.push_back({item.id, 1.0});
        } else {
            // Take a fraction of the item
            double fraction = remainingCapacity / item.weight;
            maxProfit += item.profit * fraction;
            takenItems.push_back({item.id, fraction});
            remainingCapacity = 0; // Knapsack is now full
        }
    }

    // Print the results
    cout << fixed << setprecision(2);
    cout << "Maximum Profit Earned: " << maxProfit << "\n";
    cout << "Items taken (ID and Fraction):\n";
    for (const auto& res : takenItems) {
        cout << "Item ID: " << res.id << " -> Fraction taken: " << (res.fractionTaken * 100.0) << "%\n";
    }
}

int main() {
    double capacity = 50.0; // Maximum weight capacity of knapsack

    // Define items: {id, weight, profit}
    vector<Item> items = {
        {1, 10.0, 60.0},
        {2, 20.0, 100.0},
        {3, 30.0, 120.0}
    };

    fractionalKnapsack(capacity, items);

    return 0;
}
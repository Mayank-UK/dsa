#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

struct Item {
    int id;
    double weight;
    double profit;
};

// One item either taken whole (fraction == 1.0) or split (0 < fraction < 1).
struct Taken {
    int id;
    double fraction;
};

struct KnapsackResult {
    double totalProfit;
    vector<Taken> items;   // in the greedy order they were picked
};

// Greedy choice: take the highest value/weight ratio first, splitting the last
// item if capacity runs out. Optimal for the fractional knapsack (the fraction
// makes the greedy choice provably optimal, unlike 0/1 knapsack).
KnapsackResult fractionalKnapsack(double capacity, vector<Item> items) {
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.profit / a.weight > b.profit / b.weight;
    });

    double profit = 0.0;
    double remaining = capacity;
    vector<Taken> taken;

    for (const auto& it : items) {
        if (remaining <= 0) break;
        if (it.weight <= remaining) {
            remaining -= it.weight;
            profit += it.profit;
            taken.push_back({it.id, 1.0});
        } else {
            double frac = remaining / it.weight;
            profit += it.profit * frac;
            taken.push_back({it.id, frac});
            remaining = 0;
        }
    }
    return {profit, taken};
}

int main() {
    cout << fixed << setprecision(2);
    cout << "=============== Fractional Knapsack ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n log n)   dominated by the ratio sort\n";
    cout << "  Space : O(n)\n";
    cout << "  Note  : fractional => greedy by value/weight is optimal\n\n";

    cout << "[Demo]\n";
    double capacity = 50.0;
    vector<Item> items = {{1, 10.0, 60.0}, {2, 20.0, 100.0}, {3, 30.0, 120.0}};
    cout << "  capacity = " << capacity << "\n";
    cout << "  items (id, weight, profit, ratio):\n";
    for (const auto& it : items)
        cout << "    [" << it.id << "] w=" << it.weight << " p=" << it.profit
             << " r=" << it.profit / it.weight << "\n";
    KnapsackResult r = fractionalKnapsack(capacity, items);
    cout << "  max profit = " << r.totalProfit << "\n";
    cout << "  taken:\n";
    for (const auto& t : r.items)
        cout << "    [" << t.id << "] fraction = " << (t.fraction * 100.0) << "%\n";
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  capacity 0 : profit = "
         << fractionalKnapsack(0.0, {{1, 10, 50}}).totalProfit << "\n";
    cout << "  item heavier than capacity (must split):\n";
    {
        KnapsackResult s = fractionalKnapsack(15.0, {{1, 30.0, 120.0}});
        cout << "    profit=" << s.totalProfit << ", fraction="
             << (s.items.empty() ? 0.0 : s.items.front().fraction * 100.0) << "%\n";
    }
    cout << "  everything fits whole:\n";
    {
        KnapsackResult s = fractionalKnapsack(100.0, {{1, 10, 60}, {2, 20, 100}});
        cout << "    profit=" << s.totalProfit << " (no split)\n";
    }
    cout << "\n";

    return 0;
}

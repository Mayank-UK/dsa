#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// An activity with an id, a start time, and a finish time.
struct Activity {
    int id;
    int start;
    int finish;
};

// Greedy choice: sort by finish time, then always take the activity that
// finishes earliest among those compatible with the last chosen one.
// Sorting by finish (tie-break by start) makes the choice deterministic.
vector<Activity> selectActivities(vector<Activity> activities) {
    sort(activities.begin(), activities.end(), [](const Activity& a, const Activity& b) {
        if (a.finish != b.finish) return a.finish < b.finish;
        return a.start < b.start;
    });

    vector<Activity> chosen;
    for (const auto& act : activities) {
        // Compatible if it starts no earlier than the last chosen activity finishes.
        if (chosen.empty() || act.start >= chosen.back().finish) {
            chosen.push_back(act);
        }
    }
    return chosen;
}

static void printActivities(const vector<Activity>& acts) {
    for (const auto& a : acts)
        cout << "    [id=" << a.id << "] start=" << a.start << " finish=" << a.finish << "\n";
}

int main() {
    cout << "================ Activity Selection ================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n log n)   dominated by the finish-time sort\n";
    cout << "  Space : O(n)\n";
    cout << "  Note  : greedy-choice by earliest finish time is optimal\n\n";

    cout << "[Demo]\n";
    vector<Activity> activities = {
        {1, 1, 4}, {2, 3, 5}, {3, 0, 6}, {4, 5, 7}, {5, 3, 8},
        {6, 5, 9}, {7, 6, 10}, {8, 8, 11}, {9, 8, 12}, {10, 2, 13}, {11, 12, 14}
    };
    cout << "  input activities:\n";
    printActivities(activities);
    vector<Activity> chosen = selectActivities(activities);
    cout << "  selected " << chosen.size() << " non-overlapping activities:\n";
    printActivities(chosen);
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  empty set : selected = " << selectActivities({}).size() << "\n";
    cout << "  single activity:\n";
    printActivities(selectActivities({{1, 2, 5}}));
    cout << "  all overlapping (same slot): selected = "
         << selectActivities({{1, 0, 10}, {2, 0, 10}, {3, 0, 10}}).size() << "\n";
    cout << "  back-to-back (touch ok, 1.finish == 2.start): selected = "
         << selectActivities({{1, 0, 3}, {2, 3, 6}, {3, 6, 9}}).size() << "\n";
    cout << "\n";

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an activity with ID, start time, and finish time
struct Activity {
    int id;
    int start;
    int finish;

    // Comparator to sort activities by finish time in ascending order
    bool operator<(const Activity& other) const {
        return finish < other.finish;
    }
};

// Function to select the maximum number of non-overlapping activities
void selectActivities(vector<Activity>& activities) {
    // Step 1: Sort activities by finish time
    sort(activities.begin(), activities.end());

    vector<int> selectedIndices;

    // Step 2: Always select the first activity
    selectedIndices.push_back(activities[0].id);
    int lastFinishTime = activities[0].finish;

    // Step 3: Iterate through the remaining activities
    for (size_t i = 1; i < activities.size(); i++) {
        // If this activity starts at or after the last finished activity, select it
        if (activities[i].start >= lastFinishTime) {
            selectedIndices.push_back(activities[i].id);
            lastFinishTime = activities[i].finish;
        }
    }

    // Print the results
    cout << "Maximum number of selected activities: " << selectedIndices.size() << "\n";
    cout << "Selected Activity IDs: ";
    for (int id : selectedIndices) {
        cout << id << " ";
    }
    cout << "\n";
}

int main() {
    // Define activities: {id, start_time, finish_time}
    vector<Activity> activities = {
        {1, 1, 4},
        {2, 3, 5},
        {3, 0, 6},
        {4, 5, 7},
        {5, 3, 8},
        {6, 5, 9},
        {7, 6, 10},
        {8, 8, 11},
        {9, 8, 12},
        {10, 2, 13},
        {11, 12, 14}
    };

    selectActivities(activities);

    return 0;
}
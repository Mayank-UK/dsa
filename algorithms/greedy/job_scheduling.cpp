#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a job with ID, deadline, and profit
struct Job {
    int id;
    int deadline;
    int profit;

    // Comparator to sort jobs in descending order of profit
    bool operator<(const Job& other) const {
        return profit > other.profit;
    }
};

// Function to schedule jobs to maximize total profit
void scheduleJobs(vector<Job>& jobs) {
    // Step 1: Sort jobs in descending order of profit
    sort(jobs.begin(), jobs.end());

    // Find the maximum deadline to size our slot array
    int maxDeadline = 0;
    for (const auto& job : jobs) {
        maxDeadline = max(maxDeadline, job.deadline);
    }

    // Slot array to keep track of free time slots (1-indexed)
    vector<int> slot(maxDeadline + 1, -1);
    int totalProfit = 0;
    int countJobs = 0;
    vector<int> scheduledJobIds;

    // Step 2: Iterate through sorted jobs and find latest available slot
    for (const auto& job : jobs) {
        // Search for a free slot from the job's deadline down to 1
        for (int j = min(maxDeadline, job.deadline); j >= 1; j--) {
            if (slot[j] == -1) {
                slot[j] = job.id;       // Allocate slot to this job
                totalProfit += job.profit;
                countJobs++;
                scheduledJobIds.push_back(job.id);
                break;
            }
        }
    }

    // Print the results
    cout << "Maximum Profit Earned: " << totalProfit << "\n";
    cout << "Number of Jobs Done: " << countJobs << "\n";
    cout << "Scheduled Job IDs in order of execution: ";
    for (int id : scheduledJobIds) {
        cout << id << " ";
    }
    cout << "\n";
}

int main() {
    // Define jobs: {id, deadline, profit}
    vector<Job> jobs = {
        {1, 4, 20},
        {2, 1, 10},
        {3, 1, 40},
        {4, 1, 30}
    };

    scheduleJobs(jobs);

    return 0;
}
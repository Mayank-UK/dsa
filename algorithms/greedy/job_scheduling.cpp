#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Job {
    int id;
    int deadline;
    int profit;
};

struct Schedule {
    int jobCount;
    int totalProfit;
    vector<int> slots;   // slots[t] = job id scheduled at time t (0 = free)
};

// Greedy: process jobs in decreasing profit, place each in the latest free
// slot <= its deadline. Latest-slot keeps earlier slots free for tighter jobs.
Schedule scheduleJobs(const vector<Job>& jobs) {
    vector<Job> ordered = jobs;
    sort(ordered.begin(), ordered.end(), [](const Job& a, const Job& b) {
        return a.profit > b.profit;
    });

    int maxDeadline = 0;
    for (const auto& j : ordered) maxDeadline = max(maxDeadline, j.deadline);

    vector<int> slot(maxDeadline + 1, 0);
    int profit = 0, count = 0;

    for (const auto& j : ordered) {
        for (int t = min(maxDeadline, j.deadline); t >= 1; t--) {
            if (slot[t] == 0) {
                slot[t] = j.id;
                profit += j.profit;
                count++;
                break;
            }
        }
    }
    return {count, profit, slot};
}

static void printTimeline(const vector<int>& slot) {
    cout << "  time slot -> job:\n";
    for (int t = 1; t < (int)slot.size(); t++)
        cout << "    t=" << t << " : " << (slot[t] == 0 ? "(free)" : to_string(slot[t])) << "\n";
}

int main() {
    cout << "=============== Job Scheduling ===============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n log n + n*d)   d = max deadline (slot search)\n";
    cout << "  Space : O(d)\n";
    cout << "  Note  : greedy by profit; latest free slot <= deadline\n\n";

    cout << "[Demo]\n";
    vector<Job> jobs = {{1, 4, 20}, {2, 1, 10}, {3, 1, 40}, {4, 1, 30}};
    cout << "  jobs (id, deadline, profit):\n";
    for (const auto& j : jobs)
        cout << "    [" << j.id << "] d=" << j.deadline << " p=" << j.profit << "\n";
    Schedule s = scheduleJobs(jobs);
    cout << "  jobs scheduled = " << s.jobCount << ", total profit = " << s.totalProfit << "\n";
    printTimeline(s.slots);
    cout << "\n";

    cout << "[Edge Cases]\n";
    cout << "  no jobs : count = " << scheduleJobs({}).jobCount << ", profit = "
         << scheduleJobs({}).totalProfit << "\n";
    cout << "  all jobs deadline 1 (only one fits):\n";
    {
        Schedule s2 = scheduleJobs({{1, 1, 50}, {2, 1, 30}, {3, 1, 10}});
        cout << "    count = " << s2.jobCount << ", profit = " << s2.totalProfit
             << " (highest-profit job wins the single slot)\n";
    }
    cout << "  deadline larger than job count:\n";
    {
        Schedule s3 = scheduleJobs({{1, 10, 70}});
        cout << "    count = " << s3.jobCount << ", profit = " << s3.totalProfit << "\n";
    }
    cout << "\n";

    return 0;
}

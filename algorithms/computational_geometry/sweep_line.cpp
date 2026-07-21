#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Structure to represent an Event Point for the Sweep Line
struct Event {
    double x, y;
    int type; // e.g., 0 for start of segment, 1 for end
    int id;   // Segment identifier

    // Custom comparator to sort events from left to right (X-coordinate)
    bool operator<(const Event& other) const {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }
};

void sweepLineDemo(vector<Event>& events) {
    // Step 1: Sort all events by X-coordinate (Event Queue)
    sort(events.begin(), events.end());

    // Step 2: Initialize Sweep Line Status structure
    set<double> activeYCoordinates;

    cout << "Executing Sweep Line Algorithm...\n";
    
    // Step 3: Process each event
    for (const auto& ev : events) {
        if (ev.type == 0) { // Segment Start
            cout << "Sweep line hit start of segment " << ev.id << " at (" << ev.x << ", " << ev.y << ")\n";
            activeYCoordinates.insert(ev.y);
            
            // Check neighbors in status structure for potential intersections
            auto it = activeYCoordinates.find(ev.y);
            // (Neighbor checks would happen here in a full Bentley-Ottmann implementation)
            
        } else { // Segment End
            cout << "Sweep line hit end of segment " << ev.id << " at (" << ev.x << ", " << ev.y << ")\n";
            activeYCoordinates.erase(ev.y);
        }
    }
}

int main() {
    // Sample events representing start and end points of segments
    vector<Event> events = {
        {1.0, 2.0, 0, 1}, // Start of segment 1
        {4.0, 5.0, 1, 1}, // End of segment 1
        {2.0, 3.0, 0, 2}, // Start of segment 2
        {5.0, 1.0, 1, 2}  // End of segment 2
    };

    sweepLineDemo(events);

    return 0;
}
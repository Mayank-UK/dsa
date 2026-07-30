#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// ============================================================
// Sweep Line — the EVENT-DRIVEN paradigm for geometric problems. Imagine a
// vertical line sweeping left to right; the algorithm acts only at discrete
// EVENT points (segment starts/ends, etc.), maintaining a STATUS structure of
// whatever is currently crossed by the line. Sorting events turns an O(n^2)
// spatial problem into O(n log n). This file is a SKELETON: it processes
// segment start/end events and tracks active y-coordinates — the backbone of
// Bentley-Ottmann segment-intersection, without the full neighbor-intersection
// logic (called out in [Limitation] below).
// ============================================================
struct Event {
    double x, y;
    int type;   // 0 = segment start, 1 = segment end
    int id;     // segment identifier

    // Left-to-right order; ties broken by y, then starts-before-ends.
    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return type < other.type;
    }
};

// Process events in x-order, maintaining the set of y-values currently active.
static void sweepLine(const vector<Event>& events) {
    vector<Event> sorted = events;
    sort(sorted.begin(), sorted.end());          // the event queue

    set<double> activeY;                          // the sweep-line status

    for (const Event& ev : sorted) {
        if (ev.type == 0) {                       // segment start: enter status
            cout << "  x=" << ev.x << "  START seg " << ev.id
                 << " at y=" << ev.y
                 << "   active y = {";
            activeY.insert(ev.y);
            // In a full Bentley-Ottmann build, this is where the new segment's
            // neighbors in `activeY` would be checked for a crossing.
        } else {                                  // segment end: leave status
            activeY.erase(ev.y);
            cout << "  x=" << ev.x << "  END   seg " << ev.id
                 << " at y=" << ev.y
                 << "   active y = {";
        }
        for (double y : activeY) cout << y << " ";
        cout << "}" << endl;
    }
}

// ============================================================
int main() {

    cout << "==================== Sweep Line (skeleton) ====================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  time  : O(n log n)   (sort events + O(log n) status insert/erase each)" << endl;
    cout << "  space : O(n)         (event queue + active set)" << endl;
    cout << "  Notes : the win comes from acting only at events, never scanning empty space." << endl;

    cout << endl;
    cout << "[Demo]  two segments: seg 1 = (1,2)->(4,5), seg 2 = (2,3)->(5,1)" << endl;
    vector<Event> events = {
        {1.0, 2.0, 0, 1}, {4.0, 5.0, 1, 1},   // segment 1
        {2.0, 3.0, 0, 2}, {5.0, 1.0, 1, 2}    // segment 2
    };
    sweepLine(events);

    cout << endl;
    cout << "[Edge Cases]" << endl;
    cout << "  Two events at the same x: tie broken by y, then by type (start before end)." << endl;
    sweepLine({{2.0, 1.0, 0, 1}, {2.0, 5.0, 0, 2}, {2.0, 1.0, 1, 1}});
    cout << "  (above: three events at x=2, processed in y then type order)" << endl;

    cout << endl;
    cout << "[Limitation]" << endl;
    cout << "  This is the event-driven FRAMEWORK, not a complete algorithm. A full" << endl;
    cout << "  Bentley-Ottmann segment-intersection finder also (a) represents the status" << endl;
    cout << "  as segments ordered by current y, (b) checks each newly-adjacent pair for a" << endl;
    cout << "  crossing, and (c) inserts crossing events dynamically. For just TESTING" << endl;
    cout << "  whether two specific segments cross, see line_intersection.cpp." << endl;

    cout << endl;
    cout << "[Note]  The same paradigm drives many O(n log n) geometry algorithms:" << endl;
    cout << "       closest-pair (sweep variant), rectangle-area union, and Fortune's" << endl;
    cout << "       Voronoi algorithm. The recurring shape: sort events, maintain a" << endl;
    cout << "       balanced status structure, react at each event." << endl;

    return 0;
}

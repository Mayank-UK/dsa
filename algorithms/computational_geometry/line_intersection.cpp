#include <iostream>
#include <algorithm>

using namespace std;

// ============================================================
// Segment Intersection — do two segments cross? Two segments intersect iff
// each segment STRADDLES the line through the other, i.e. their endpoints sit
// on opposite sides (detected by orientation.cpp's cross product changing
// sign). Collinear pairs are a special case: they need a bounding-box check
// (onSegment) to see whether they actually overlap. Covers both PROPER crossings
// and improper ones (shared endpoint, T-junction, collinear overlap).
// ============================================================
struct Point { int x, y; };

// Given collinear p, q, r: is q within the bounding box of segment pr?
static bool onSegment(Point p, Point q, Point r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
           q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}

// 0 = Collinear, 1 = Clockwise, 2 = Counterclockwise
static int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Do segments p1q1 and p2q2 intersect (proper or improper)?
static bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case: each straddles the other's line.
    if (o1 != o2 && o3 != o4) return true;

    // Special cases: collinear + an endpoint lying on the other segment.
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

static void runCase(const string& label, Point p1, Point q1, Point p2, Point q2, bool expect) {
    bool hit = doIntersect(p1, q1, p2, q2);
    cout << "  " << label << " -> " << (hit ? "INTERSECT" : "no intersection")
         << "  [" << (hit == expect ? "ok" : "WRONG") << "]" << endl;
}

// ============================================================
int main() {

    cout << "==================== Segment Intersection ====================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  time  : O(1)   (four orientation tests + up to four bbox checks)" << endl;
    cout << "  space : O(1)" << endl;
    cout << "  Notes : exact integer arithmetic; handles proper AND improper crossings." << endl;

    cout << endl;
    cout << "[Demo]" << endl;
    runCase("parallel horizontal lines (no)",
            {1, 1}, {10, 1}, {1, 2}, {10, 2}, false);
    runCase("crossing diagonals (yes)",
            {10, 0}, {0, 10}, {0, 0}, {10, 10}, true);
    runCase("collinear but disjoint (no)",
            {-5, -5}, {0, 0}, {1, 1}, {10, 10}, false);

    cout << endl;
    cout << "[Edge Cases]" << endl;
    runCase("collinear, overlapping ranges (yes)",
            {0, 0}, {5, 5}, {3, 3}, {8, 8}, true);
    runCase("shared endpoint (yes, improper)",
            {0, 0}, {2, 2}, {2, 2}, {4, 0}, true);
    runCase("T-junction: endpoint touches the other mid-segment (yes)",
            {0, 0}, {4, 0}, {2, 0}, {2, 4}, true);
    runCase("just-touching at a corner, L-shapes (no)",
            {0, 0}, {0, 4}, {4, 0}, {4, 4}, false);

    cout << endl;
    cout << "[Note]  This tests WHETHER segments cross, not WHERE. Finding the actual" << endl;
    cout << "       intersection point needs the parametric line solve; finding ALL" << endl;
    cout << "       intersections among many segments is the Bentley-Ottmann sweep" << endl;
    cout << "       line — see sweep_line.cpp." << endl;

    return 0;
}

#include <iostream>
#include <algorithm>

using namespace std;

// Structure to represent a 2D point
struct Point {
    int x;
    int y;
};

// Given three collinear points p, q, r, the function checks if
// point q lies on the line segment 'pr'
bool onSegment(Point p, Point q, Point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) {
        return true;
    }
    return false;
}

// To find orientation of ordered triplet (p, q, r).
// Returns:
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r) {
    // Cross product logic
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    // Find the four orientations needed for general and special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case:
    // If o1 and o2 are different AND o3 and o4 are different
    if (o1 != o2 && o3 != o4) {
        return true;
    }

    // Special Cases (Collinear and overlapping):
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall into any of the above cases
}

int main() {
    // Segment 1: (1, 1) to (10, 1)
    Point p1 = {1, 1}, q1 = {10, 1};
    // Segment 2: (1, 2) to (10, 2)
    Point p2 = {1, 2}, q2 = {10, 2};

    if (doIntersect(p1, q1, p2, q2))
        cout << "Segments 1 and 2 intersect.\n";
    else
        cout << "Segments 1 and 2 do not intersect.\n";

    // Segment 3: (10, 0) to (0, 10)
    Point p3 = {10, 0}, q3 = {0, 10};
    // Segment 4: (0, 0) to (10, 10)
    Point p4 = {0, 0}, q4 = {10, 10};

    if (doIntersect(p3, q3, p4, q4))
        cout << "Segments 3 and 4 intersect.\n";
    else
        cout << "Segments 3 and 4 do not intersect.\n";

    // Segment 5: (-5, -5) to (0, 0)
    Point p5 = {-5, -5}, q5 = {0, 0};
    // Segment 6: (1, 1) to (10, 10)
    Point p6 = {1, 1}, q6 = {10, 10};

    if (doIntersect(p5, q5, p6, q6))
        cout << "Segments 5 and 6 intersect.\n";
    else
        cout << "Segments 5 and 6 do not intersect.\n";

    return 0;
}
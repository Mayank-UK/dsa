#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// ============================================================
// Graham Scan — convex hull in O(n log n). Pick a pivot guaranteed on the hull
// (bottom-most, leftmost on ties), sort the rest by polar angle around it, drop
// collinear near-duplicates, then walk: push each point and pop while the top
// two + new point make a non-left (clockwise/right) turn. The stack ends up
// holding the hull in counterclockwise order. Compare jarvis_march.cpp: Graham
// is O(n log n) for ANY input (the sort dominates), Jarvis is O(n*h).
// ============================================================
struct Point { int x, y; };

static Point p0;   // pivot for polar-angle sorting

static Point nextToTop(stack<Point>& S) {
    Point p = S.top(); S.pop();
    Point res = S.top(); S.push(p);
    return res;
}

static void swapPt(Point& p1, Point& p2) { Point t = p1; p1 = p2; p2 = t; }

static int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// 0 = Collinear, 1 = Clockwise, 2 = Counterclockwise
static int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Sort by polar angle around p0; collinear points ordered by distance.
static bool compare(const Point& p1, const Point& p2) {
    int o = orientation(p0, p1, p2);
    if (o == 0) return (distSq(p0, p2) >= distSq(p0, p1));
    return (o == 2);
}

// Returns the convex hull in counterclockwise order. NOTE: sorts `points` in
// place. Empty if fewer than 3 non-collinear points remain.
static vector<Point> grahamScan(vector<Point>& points) {
    int n = (int)points.size();
    if (n < 3) return {};

    // Step 1: bottom-most point (leftmost on ties) — guaranteed on the hull.
    int ymin = points[0].y, minIdx = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[minIdx].x)) {
            ymin = points[i].y;
            minIdx = i;
        }
    }
    swapPt(points[0], points[minIdx]);
    p0 = points[0];

    // Step 2: sort the remaining points by polar angle around p0.
    sort(points.begin() + 1, points.end(), compare);

    // Step 3: drop collinear points, keeping only the furthest on each ray.
    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0) i++;
        points[m] = points[i];
        m++;
    }
    if (m < 3) return {};

    // Step 4: scan, popping while the turn is not counterclockwise.
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    for (int i = 3; i < m; i++) {
        while (S.size() > 1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    // Unroll the stack into a CCW vector.
    vector<Point> hull;
    while (!S.empty()) { hull.push_back(S.top()); S.pop(); }
    return hull;
}

static void printHull(const string& label, const vector<Point>& hull) {
    cout << "  " << label << " (" << hull.size() << " hull verts):";
    for (const Point& p : hull) cout << " (" << p.x << "," << p.y << ")";
    cout << endl;
}

// ============================================================
int main() {

    cout << "==================== Graham Scan (Convex Hull) ====================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  time  : O(n log n)   (dominated by the polar-angle sort)" << endl;
    cout << "  space : O(n)         (stack + sorted copy)" << endl;
    cout << "  Notes : the scan itself is O(n); the sort is the bottleneck." << endl;

    cout << endl;
    cout << "[Demo]" << endl;
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    cout << "  points:";
    for (const Point& p : points) cout << " (" << p.x << "," << p.y << ")";
    cout << endl;
    printHull("hull (stack order)", grahamScan(points));

    cout << endl;
    cout << "[Edge Cases]" << endl;
    vector<Point> tri = {{0, 0}, {4, 0}, {2, 3}};
    printHull("triangle (3 points, all on hull)", grahamScan(tri));
    vector<Point> interior = {{0, 0}, {4, 0}, {4, 4}, {3, 1}};
    printHull("one interior point (4 pts, 3 on hull)", grahamScan(interior));
    vector<Point> two = {{0, 0}, {1, 1}};
    printHull("two points (< 3) -> no hull", grahamScan(two));
    vector<Point> col = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
    printHull("collinear points -> no hull", grahamScan(col));

    cout << endl;
    cout << "[Note]  Hull vertices come out in stack (reverse-push) order — for strict" << endl;
    cout << "       CCW output reverse them. Andrew's monotone-chain is a robust variant" << endl;
    cout << "       that sorts by x then y instead of polar angle (no trig, easier to get" << endl;
    cout << "       collinear handling right). Output-sensitive alt: jarvis_march.cpp." << endl;

    return 0;
}

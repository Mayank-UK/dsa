#include <iostream>
#include <vector>

using namespace std;

// ============================================================
// Jarvis March (Gift Wrapping) — convex hull by simulation. Start at the
// leftmost point and repeatedly "wrap" to the next hull vertex: the point most
// counterclockwise with respect to the current point. Each hull vertex costs a
// full O(n) scan, so the total is O(n*h) where h is the hull size — great when
// h is small, poor when most points are on the hull. Compare graham_scan.cpp's
// O(n log n) which is input-size, not hull-size, bound.
// ============================================================
struct Point { int x, y; };

// 0 = Collinear, 1 = Clockwise, 2 = Counterclockwise
static int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Returns the convex hull vertices in counterclockwise order. Empty if < 3 pts.
static vector<Point> jarvisMarch(const vector<Point>& points) {
    int n = (int)points.size();
    if (n < 3) return {};

    vector<Point> hull;

    // Start at the leftmost point (lowest x, ties broken by lowest y).
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x) l = i;

    int p = l;
    do {
        hull.push_back(points[p]);

        // Candidate next vertex; scan all points for one more CCW than current q.
        int q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }

        p = q;
    } while (p != l);   // wrapped back to the start

    return hull;
}

static void printHull(const string& label, const vector<Point>& hull) {
    cout << "  " << label << " (" << hull.size() << " hull verts):";
    for (const Point& p : hull) cout << " (" << p.x << "," << p.y << ")";
    cout << endl;
}

// ============================================================
int main() {

    cout << "==================== Jarvis March (Convex Hull) ====================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  time  : O(n*h)   (n = #points, h = #hull vertices)" << endl;
    cout << "  space : O(h)     (the hull)" << endl;
    cout << "  Notes : best when few points are on the hull; O(n^2) in the worst case." << endl;

    cout << endl;
    cout << "[Demo]" << endl;
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    cout << "  points:";
    for (const Point& p : points) cout << " (" << p.x << "," << p.y << ")";
    cout << endl;
    printHull("hull (CCW)", jarvisMarch(points));

    cout << endl;
    cout << "[Edge Cases]" << endl;
    printHull("triangle (3 points, all on hull)", jarvisMarch({{0, 0}, {4, 0}, {2, 3}}));
    printHull("one interior point (4 pts, 3 on hull)",
              jarvisMarch({{0, 0}, {4, 0}, {4, 4}, {3, 1}}));
    printHull("two points (< 3) -> no hull", jarvisMarch({{0, 0}, {1, 1}}));
    printHull("collinear points (degenerate: wraps through all)",
              jarvisMarch({{0, 0}, {1, 1}, {2, 2}, {3, 3}}));

    cout << endl;
    cout << "[Note]  Gift wrapping is output-sensitive. For a guaranteed O(n log n)" << endl;
    cout << "       hull regardless of how many points are extreme, use graham_scan.cpp." << endl;

    return 0;
}

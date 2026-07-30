#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// ============================================================
// Polygon Area — the Shoelace formula. Summing (x_i * y_{i+1} - x_{i+1} * y_i)
// around the boundary gives TWICE the signed area; its sign is the winding
// direction (CCW positive, CW negative), and abs(...)/2 is the area. Vertices
// must be given in boundary order (around the perimeter) — NOT sorted. This is
// the same cross-product sum as orientation.cpp, accumulated over all edges.
// ============================================================
struct Point { double x, y; };

// Unsigned area via Shoelace. Returns 0 for fewer than 3 vertices.
static double polygonArea(const vector<Point>& points) {
    int n = (int)points.size();
    if (n < 3) return 0.0;

    double area = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;                          // wrap the last edge back to vertex 0
        area += (points[i].x * points[j].y) - (points[j].x * points[i].y);
    }
    return abs(area) / 2.0;
}

// Signed area — sign reveals the winding (CCW > 0, CW < 0).
static double signedArea(const vector<Point>& points) {
    int n = (int)points.size();
    if (n < 3) return 0.0;

    double area = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += (points[i].x * points[j].y) - (points[j].x * points[i].y);
    }
    return area / 2.0;
}

static void runCase(const string& label, const vector<Point>& poly, double expect) {
    double a = polygonArea(poly);
    cout << "  " << label << " -> area " << a
         << "  (expected " << expect << ")"
         << "  [winding " << (signedArea(poly) > 0 ? "CCW" : "CW") << "]" << endl;
}

// ============================================================
int main() {

    cout << "==================== Polygon Area (Shoelace) ====================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  time  : O(n)   (one pass over the n vertices)" << endl;
    cout << "  space : O(1)" << endl;
    cout << "  Notes : vertices must be in BOUNDARY order (around the perimeter)." << endl;

    cout << endl;
    cout << "[Demo]" << endl;
    runCase("square 4x4",         {{0, 0}, {4, 0}, {4, 4}, {0, 4}}, 16.0);
    runCase("right triangle",     {{0, 0}, {4, 0}, {0, 3}},           6.0);
    runCase("generic pentagon",   {{2, 1}, {4, 5}, {7, 8}, {8, 2}, {5, 0}}, 26.0);

    cout << endl;
    cout << "[Edge Cases]" << endl;
    runCase("same square, REVERSED order (winding flips)", {{0, 4}, {4, 4}, {4, 0}, {0, 0}}, 16.0);
    runCase("degenerate collinear 'polygon'", {{0, 0}, {1, 1}, {2, 2}}, 0.0);
    cout << "  Two vertices { {0,0}, {1,1} } -> area " << polygonArea({{0, 0}, {1, 1}})
         << "  (needs >= 3)" << endl;
    cout << "  Empty polygon -> area " << polygonArea({}) << endl;

    cout << endl;
    cout << "[Note]  The signed sum's sign is the winding direction, reused by point-in-" << endl;
    cout << "       polygon tests. For a CONCAVE polygon the Shoelace still works because" << endl;
    cout << "       opposite-winding edges cancel — it is exact regardless of convexity." << endl;

    return 0;
}

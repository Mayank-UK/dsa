#include <iostream>

using namespace std;

// ============================================================
// Orientation — the fundamental 2D-geometry primitive. The sign of the cross
// product (p2-p1) x (p3-p2) tells how the path p1->p2->p3 turns:
//   0  -> collinear
//   >0 -> clockwise (right turn)
//   <0 -> counterclockwise (left turn)
// Everything else in this category (convex hull, segment intersection, polygon
// winding) is built on this one test, so it uses EXACT integer arithmetic and
// never goes near floating point.
// ============================================================
struct Point { int x, y; };

// 0 = Collinear, 1 = Clockwise, 2 = Counterclockwise
static int orientation(Point p1, Point p2, Point p3) {
    int val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

static const char* name(int o) {
    return o == 0 ? "Collinear" : (o == 1 ? "Clockwise" : "Counterclockwise");
}

static void runCase(const string& label, Point p1, Point p2, Point p3) {
    cout << "  " << label << " -> " << name(orientation(p1, p2, p3)) << endl;
}

// ============================================================
int main() {

    cout << "==================== Orientation ====================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  time  : O(1)   (one cross product)" << endl;
    cout << "  space : O(1)" << endl;
    cout << "  Notes : exact INTEGER cross product — no floating point, no rounding." << endl;

    cout << endl;
    cout << "[Demo]  base segment p1=(0,0) -> p2=(4,4), third point varied" << endl;
    runCase("(1,1) on the line        ", {0, 0}, {4, 4}, {1, 1});   // collinear
    runCase("(1,2) left of the line   ", {0, 0}, {4, 4}, {1, 2});   // CCW
    runCase("(2,1) right of the line  ", {0, 0}, {4, 4}, {2, 1});   // CW

    cout << endl;
    cout << "[Edge Cases]" << endl;
    runCase("horizontal base, up      ", {0, 0}, {4, 0}, {2, 3});   // CCW
    runCase("horizontal base, down    ", {0, 0}, {4, 0}, {2, -3});  // CW
    runCase("vertical base, right     ", {0, 0}, {0, 4}, {3, 2});   // CW
    runCase("reversed segment (4,4)->(0,0), (1,2)", {4, 4}, {0, 0}, {1, 2}); // flips vs demo
    runCase("identical points         ", {2, 2}, {2, 2}, {2, 2});   // collinear

    cout << endl;
    cout << "[Note]  Sign convention follows screen coordinates (y grows downward):" << endl;
    cout << "       positive cross product = CLOCKWISE. Convex-hull code exploits this" << endl;
    cout << "       to keep only left (CCW) turns — see graham_scan.cpp and jarvis_march.cpp." << endl;

    return 0;
}

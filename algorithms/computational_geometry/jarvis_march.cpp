#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
};

// Find orientation of ordered triplet (p, q, r).
// Returns 0: Collinear, 1: Clockwise, 2: Counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; 
    return (val > 0) ? 1 : 2; 
}

// Prints convex hull of a set of n points
void jarvisMarch(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return; // Convex hull is not possible

    vector<Point> hull;

    // Step 1: Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[l].x) {
            l = i;
        }
    }

    // Step 2: Start from leftmost point, keep moving counterclockwise
    int p = l, q;
    do {
        // Add current point to result
        hull.push_back(points[p]);

        // Search for a point 'q' such that orientation(p, x, q) is counterclockwise 
        // for all points 'x'.
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            // If i is more counterclockwise than current q, then update q
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }

        // Set p as q for next iteration, so that q is added to the hull
        p = q;

    } while (p != l); // While we don't reach the first point

    // Print Result
    cout << "Jarvis March Convex Hull:\n";
    for (int i = 0; i < hull.size(); i++) {
        cout << "(" << hull[i].x << ", " << hull[i].y << ")\n";
    }
}

int main() {
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    jarvisMarch(points);
    return 0;
}
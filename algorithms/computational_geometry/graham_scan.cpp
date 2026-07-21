#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

// Global point used for sorting by polar angle
Point p0;

// Utility function to find the next-to-top element in a stack
Point nextToTop(stack<Point>& S) {
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// Utility function to swap two points
void swap(Point& p1, Point& p2) {
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

// Utility function to return square of distance between p1 and p2
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// Find orientation of ordered triplet (p, q, r).
// Returns 0: Collinear, 1: Clockwise, 2: Counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
}

// Function used by sort() to sort an array of points with respect to the first point
bool compare(const Point& p1, const Point& p2) {
    int o = orientation(p0, p1, p2);
    if (o == 0) {
        return (distSq(p0, p2) >= distSq(p0, p1));
    }
    return (o == 2); // Sort in counterclockwise order
}

// Prints convex hull of a set of n points
void grahamScan(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return; // Convex hull is not possible

    // Step 1: Find the bottom-most point (or choose the left-most in case of tie)
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }

    // Step 2: Place the bottom-most point at first position
    swap(points[0], points[min]);
    p0 = points[0];

    // Step 3: Sort n-1 points with respect to the first point
    sort(points.begin() + 1, points.end(), compare);

    // Step 4: Remove collinear points closer to p0, keeping the furthest
    int m = 1; 
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0) {
            i++;
        }
        points[m] = points[i];
        m++; 
    }

    // If less than 3 points remain, hull is not possible
    if (m < 3) return;

    // Step 5: Create an empty stack and push first three points
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Step 6: Process remaining m-3 points
    for (int i = 3; i < m; i++) {
        // Keep removing top while the angle formed makes a non-left turn
        while (S.size() > 1 && orientation(nextToTop(S), S.top(), points[i]) != 2) {
            S.pop();
        }
        S.push(points[i]);
    }

    // Print the stack (Convex Hull vertices)
    cout << "Graham Scan Convex Hull:\n";
    while (!S.empty()) {
        Point p = S.top();
        cout << "(" << p.x << ", " << p.y << ")\n";
        S.pop();
    }
}

int main() {
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    grahamScan(points);
    return 0;
}
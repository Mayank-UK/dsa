#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Structure to represent a 2D point
// Using double to accommodate fractional coordinates and exact area calculations
struct Point {
    double x;
    double y;
};

// Function to calculate the area of a polygon using the Shoelace formula
double polygonArea(const vector<Point>& points) {
    int n = points.size();
    
    // A polygon must have at least 3 vertices
    if (n < 3) return 0.0; 

    double area = 0.0;

    // Apply the shoelace formula
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n; // The next vertex (wraps around to 0 at the end)
        area += (points[i].x * points[j].y) - (points[j].x * points[i].y);
    }

    // Return absolute value divided by 2
    return abs(area) / 2.0;
}

int main() {
    // Test Case 1: A simple square (Area should be 16)
    vector<Point> square = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    cout << "Area of square: " << polygonArea(square) << "\n";

    // Test Case 2: A right-angled triangle (Area should be 6)
    vector<Point> triangle = {{0, 0}, {4, 0}, {0, 3}};
    cout << "Area of triangle: " << polygonArea(triangle) << "\n";

    // Test Case 3: A generic polygon (Concave or Convex)
    vector<Point> poly = {{2, 1}, {4, 5}, {7, 8}, {8, 2}, {5, 0}};
    cout << "Area of generic polygon: " << polygonArea(poly) << "\n";

    return 0;
}
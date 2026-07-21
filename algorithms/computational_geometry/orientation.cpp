#include <iostream>

using namespace std;

// Structure to represent a 2D point
struct Point {
    int x;
    int y;
};

// Function to find orientation of ordered triplet (p1, p2, p3).
// Returns:
// 0 --> Collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p1, Point p2, Point p3) {
    // Cross product logic
    int val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);

    if (val == 0) {
        return 0; // Collinear
    }
    
    // If val is positive, it's clockwise. If negative, counterclockwise.
    return (val > 0) ? 1 : 2; 
}

int main() {
    // Test Case 1: Collinear points
    Point p1 = {0, 0}, p2 = {4, 4}, p3 = {1, 1};
    int o1 = orientation(p1, p2, p3);
    cout << "Orientation 1: ";
    if (o1 == 0) cout << "Collinear\n";
    else if (o1 == 1) cout << "Clockwise\n";
    else cout << "Counterclockwise\n";

    // Test Case 2: Clockwise points
    Point p4 = {0, 0}, p5 = {4, 4}, p6 = {1, 2};
    int o2 = orientation(p4, p5, p6);
    cout << "Orientation 2: ";
    if (o2 == 0) cout << "Collinear\n";
    else if (o2 == 1) cout << "Clockwise\n";
    else cout << "Counterclockwise\n";

    // Test Case 3: Counterclockwise points
    Point p7 = {0, 0}, p8 = {4, 4}, p9 = {2, 1};
    int o3 = orientation(p7, p8, p9);
    cout << "Orientation 3: ";
    if (o3 == 0) cout << "Collinear\n";
    else if (o3 == 1) cout << "Clockwise\n";
    else cout << "Counterclockwise\n";

    return 0;
}
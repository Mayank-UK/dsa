#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cfloat>

using namespace std;

// Structure to represent a 2D point
struct Point {
    double x, y;
};

// Helper function to sort points by their X coordinate
bool compareX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

// Helper function to sort points by their Y coordinate
bool compareY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

// Utility function to calculate the Euclidean distance between two points
double dist(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Brute force method for small base cases (n <= 3)
double bruteForce(const vector<Point>& P, int start, int end) {
    double min_dist = DBL_MAX;
    for (int i = start; i < end; ++i) {
        for (int j = i + 1; j < end; ++j) {
            if (dist(P[i], P[j]) < min_dist) {
                min_dist = dist(P[i], P[j]);
            }
        }
    }
    return min_dist;
}

// Find the closest pair distance across the dividing line (inside the strip)
double stripClosest(vector<Point>& strip, double d) {
    double min_dist = d; 
    
    // Sort the strip by Y coordinates
    sort(strip.begin(), strip.end(), compareY);

    // Pick all points one by one and check the next few points 
    // whose Y-distance is smaller than min_dist.
    // Geometrically, this inner loop runs at most 7 times.
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min_dist; ++j) {
            if (dist(strip[i], strip[j]) < min_dist) {
                min_dist = dist(strip[i], strip[j]);
            }
        }
    }
    return min_dist;
}

// Recursive function to find the closest pair distance
double closestUtil(const vector<Point>& P, int start, int end) {
    int n = end - start;
    
    // Base case: If there are 3 or fewer points, use brute force
    if (n <= 3) {
        return bruteForce(P, start, end);
    }

    // Find the middle point
    int mid = start + n / 2;
    Point midPoint = P[mid];

    // Recursively find the smallest distances in both the left and right halves
    double dl = closestUtil(P, start, mid);
    double dr = closestUtil(P, mid, end);

    // Get the smaller of the two distances
    double d = min(dl, dr);

    // Build a vector 'strip' that contains points close to the dividing line.
    // We only include points whose X-distance to the midPoint is less than 'd'.
    vector<Point> strip;
    for (int i = start; i < end; i++) {
        if (abs(P[i].x - midPoint.x) < d) {
            strip.push_back(P[i]);
        }
    }

    // Find the closest points inside the strip and return the minimum of the two
    return min(d, stripClosest(strip, d));
}

// Main wrapper function
double closest(vector<Point>& P) {
    // Step 1: Sort all points according to their X coordinate
    sort(P.begin(), P.end(), compareX);

    // Step 2: Use recursive utility function to find the closest distance
    return closestUtil(P, 0, P.size());
}

// Driver code to test the algorithm
int main() {
    vector<Point> P = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    
    cout << "The smallest distance is: " << closest(P) << "\n";
    
    return 0;
}
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cfloat>

using namespace std;

// ============================================================
// Closest Pair of Points — divide & conquer in O(n log n). Sort by x, recurse
// on the left and right halves, then the only candidates that can beat the
// best-so-far `d` lie within a vertical strip of width 2d around the split.
// Sort that strip by y and, for each point, compare only the next few (at most
// 7) — provably bounded because points within d must sit in a d-by-2d box that
// holds a constant number of mutually->=d-separated points. Beats the O(n^2)
// all-pairs brute force. (See also divide_and_conquer/maximum_subarray.cpp for
// the same split / conquer / combine shape.)
// ============================================================
struct Point { double x, y; };

static bool compareX(const Point& p1, const Point& p2) { return p1.x < p2.x; }
static bool compareY(const Point& p1, const Point& p2) { return p1.y < p2.y; }

static double dist(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Brute force for the base case (n <= 3).
static double bruteForce(const vector<Point>& P, int start, int end) {
    double min_dist = DBL_MAX;
    for (int i = start; i < end; ++i)
        for (int j = i + 1; j < end; ++j)
            min_dist = min(min_dist, dist(P[i], P[j]));
    return min_dist;
}

// Closest pair within the merge strip, sorted by y. Inner loop is O(1) amortized.
static double stripClosest(vector<Point>& strip, double d) {
    double min_dist = d;
    sort(strip.begin(), strip.end(), compareY);

    for (size_t i = 0; i < strip.size(); ++i)
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min_dist; ++j)
            min_dist = min(min_dist, dist(strip[i], strip[j]));
    return min_dist;
}

static double closestUtil(const vector<Point>& P, int start, int end) {
    int n = end - start;
    if (n <= 3) return bruteForce(P, start, end);

    int mid = start + n / 2;
    Point midPoint = P[mid];

    double dl = closestUtil(P, start, mid);
    double dr = closestUtil(P, mid, end);
    double d = min(dl, dr);

    vector<Point> strip;
    for (int i = start; i < end; i++)
        if (abs(P[i].x - midPoint.x) < d)
            strip.push_back(P[i]);

    return min(d, stripClosest(strip, d));
}

// Wrapper: sort by x, then recurse. NOTE: sorts P in place.
static double closest(vector<Point>& P) {
    sort(P.begin(), P.end(), compareX);
    return closestUtil(P, 0, (int)P.size());
}

// Full O(n^2) brute force — only to verify the D&C answer.
static double bruteAll(const vector<Point>& P) {
    double best = DBL_MAX;
    for (size_t i = 0; i < P.size(); ++i)
        for (size_t j = i + 1; j < P.size(); ++j)
            best = min(best, dist(P[i], P[j]));
    return best;
}

static void runCase(const string& label, const vector<Point>& pts) {
    vector<Point> a = pts, b = pts;
    double dc = closest(a);
    double br = bruteAll(b);
    cout << "  " << label << "\n    D&C = " << dc << "   brute = " << br
         << "   [" << (abs(dc - br) < 1e-9 ? "agree" : "DISAGREE") << "]" << endl;
}

// ============================================================
int main() {

    cout << "==================== Closest Pair of Points ====================" << endl;

    cout << endl;
    cout << "[Complexity]" << endl;
    cout << "  time  : O(n log n)   (T(n) = 2T(n/2) + O(n) merge)" << endl;
    cout << "  space : O(n)         (strip + recursion)" << endl;
    cout << "  Notes : the strip's inner loop runs <= 7 times per point." << endl;

    cout << endl;
    cout << "[Demo]" << endl;
    runCase("classic 6-point set",
            {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}});

    cout << endl;
    cout << "[Edge Cases]" << endl;
    runCase("two close points among spread-out ones",
            {{0, 0}, {10, 10}, {20, 20}, {0.5, 0.5}});
    runCase("all points on a horizontal line",
            {{0, 0}, {1, 0}, {2, 0}, {5, 0}, {9, 0}});
    runCase("duplicate points (distance 0)",
            {{1, 1}, {1, 1}, {5, 5}, {6, 6}});
    runCase("three points (base case)",
            {{0, 0}, {3, 4}, {6, 8}});

    cout << endl;
    cout << "[Note]  Recursion depth is O(log n), so this is safe for large n where an" << endl;
    cout << "       O(n^2) all-pairs scan is infeasible. The same divide-by-x / merge-by-y" << endl;
    cout << "       idea generalizes to kD-trees for nearest-neighbor search." << endl;

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

/*
Convex Hull (Graham Scan)
- Time: O(n log n)
- Returns the convex hull in counterclockwise order
*/
struct Point {
    int x, y;
    bool operator<(const Point& p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
};

long long cross(const Point& O, const Point& A, const Point& B) {
    return 1LL * (A.x - O.x) * (B.y - O.y) - 1LL * (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point> pts) {
    int n = pts.size(), k = 0;
    if (n <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<Point> hull(2 * n);
    // Lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    // Upper hull
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && cross(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    hull.resize(k - 1);
    return hull;
}

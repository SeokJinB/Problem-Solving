#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

class Point
{
public:
    long long x, y;
};

int ccw(const Point& p1, const Point& p2, const Point& p3)
{
    long long val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : -1;
}

vector<Point> convexHull(vector<Point>& points)
{
    int n = points.size();
    if (n < 3)
        return {};

    vector<Point> hull;

    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[leftmost].x)
            leftmost = i;
    }

    int p = leftmost, q;
    do {
        hull.push_back(points[p]);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (ccw(points[p], points[i], points[q]) == -1)
                q = i;
        }
        p = q;
    } while (p != leftmost);

    return hull;
}

int main()
{
    ifstream ifp("hull.inp");
    ofstream ofp("hull.out");

    vector<Point> points;
    int n;
    long long x, y;

    ifp >> n;

    for (int i = 0; i < n; i++) {
        ifp >> x >> y;
        points.push_back({ x, y });
    }

    vector<Point> hull = convexHull(points);

    ofp << hull.size() << endl;

    for (const Point& p : hull) {
        ofp << p.x << " " << p.y << endl;
    }

    ifp.close();
    ofp.close();

    return 0;
}

/*
Didn't get a perfect credit (50/100)
Code modification is required
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <iomanip>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;

class Point
{
public:
    long long x = 0;
    long long y = 0;
    int origin;
};

bool operator==(Point a, Point b)
{
    return (a.x == b.x) && (a.y == b.y);
}
Point p0;
Point nextToTop(stack<Point>& S);

long long distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int orientation(Point p, Point q, Point r) {
    long long val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2; // clock or counterclockwise
}

bool compare(Point p1, Point p2) {
    int o = orientation(p0, p1, p2);
    if (o == 0)
        return distSq(p0, p2) >= distSq(p0, p1);
    return (o == 2);
}

vector<Point> convexHull(std::vector<Point>& points, int n) {
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }

    std::swap(points[0], points[min]);
    p0 = points[0];

    std::sort(points.begin() + 1, points.end(), compare);

    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m] = points[i];
        m++;
    }

    std::stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    for (int i = 3; i < m; i++) {
        while (S.size() > 1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    vector<Point> result;

    while (!S.empty()) {
        Point p = S.top();
        result.emplace_back(p);
        S.pop();
    }

    reverse(result.begin(), result.end());

    return result;
}

Point nextToTop(std::stack<Point>& S) {
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

double calculateArea(vector<Point> p, int n)
{
    int j;
    long long ret = 0;
    for (int i = 0; i < n; i++)
    {
        j = (i + 1) % n;
        ret += (p[i].x * p[j].y - p[i].y * p[j].x);
    }

    return abs(ret) / 2.0;
}

bool between(Point a, Point b, Point c)
{
    if (orientation(a, b, c) != 0)
        return false;
    if (a.x != b.x)
        return (a.x <= c.x && c.x <= b.x) || (b.x <= c.x && c.x <= a.x);
    else
        return (a.y <= c.y && c.y <= b.y) || (b.y <= c.y && c.y <= a.y);
}

pair<Point, Point> findMinDifferenceElements(const vector<Point>& P, const vector<Point>& Q)
{
    long long min_diff = LLONG_MAX;
    pair<Point, Point> min_elements;

    for (Point pi : P) {
        for (Point qi : Q) {
            long long diff = distSq(pi, qi);
            if (diff < min_diff) {
                min_diff = diff;
                min_elements = make_pair(pi, qi);
            }
        }
    }

    return min_elements;
}

int main()
{
    ifstream ifp("tangent.inp");
    ofstream ofp("tangent.out");

    int T;
    int vn;
    Point p;

    ifp >> T;
    for (int t = 0; t < T; t++)
    {
        int Avn = 0;
        double P, Q;
        vector<Point> pointsP, pointsQ, pointsA, convexHullpoints;

        ifp >> vn;
        Avn += vn;
        for (int v = 0; v < vn; v++)
        {
            ifp >> p.x >> p.y;
            p.origin = 0;
            pointsP.emplace_back(p);
        }
        P = calculateArea(pointsP, vn);

        ifp >> vn;
        Avn += vn;
        for (int v = 0; v < vn; v++)
        {
            ifp >> p.x >> p.y;
            p.origin = 1;
            pointsQ.emplace_back(p);
        }
        Q = calculateArea(pointsQ, vn);

        pointsA = pointsP;
        pointsA.insert(pointsA.end(), pointsQ.begin(), pointsQ.end());

        convexHullpoints = convexHull(pointsA, Avn);

        Point P1, P2, Q1, Q2;
        bool findPtoQ = false;
        bool findQtoP = false;

        for (int i = 0; i < convexHullpoints.size() - 1; i++)
        {
            if (convexHullpoints[i].origin == 0 && convexHullpoints[i + 1].origin == 1)
            {
                P1 = convexHullpoints[i];
                Q1 = convexHullpoints[i + 1];
                findPtoQ = true;
            }
            else if (convexHullpoints[i].origin == 1 && convexHullpoints[i + 1].origin == 0)
            {
                Q2 = convexHullpoints[i];
                P2 = convexHullpoints[i + 1];
                findQtoP = true;
            }
            if (findQtoP && findPtoQ)
                break;
        }

        if (P1.x == 0 && P1.y == 0 && Q1.x == 0 && Q1.y == 0)
        {
            P1 = convexHullpoints.back();
            Q1 = convexHullpoints[0];
        }

        if (P2.x == 0 && P2.y == 0 && Q2.x == 0 && Q2.y == 0)
        {
            P2 = convexHullpoints[0];
            Q2 = convexHullpoints.back();
        }

        vector<Point> collinearP;
        vector<Point> collinearQ;

        for (Point a : pointsA)
        {
            if (between(P1, Q1, a))
            {
                if (a.origin == 0)
                    collinearP.emplace_back(a);
                else
                    collinearQ.emplace_back(a);
            }
        }

        P1 = findMinDifferenceElements(collinearP, collinearQ).first;
        Q1 = findMinDifferenceElements(collinearP, collinearQ).second;

        collinearP.clear();
        collinearQ.clear();

        for (Point a : pointsA)
        {
            if (between(P2, Q2, a))
            {
                if (a.origin == 0)
                    collinearP.emplace_back(a);
                else
                    collinearQ.emplace_back(a);
            }
        }

        P2 = findMinDifferenceElements(collinearP, collinearQ).first;
        Q2 = findMinDifferenceElements(collinearP, collinearQ).second;

        auto it1 = find(pointsQ.begin(), pointsQ.end(), Q1);
        auto it2 = find(pointsQ.begin(), pointsQ.end(), Q2);

        vector<Point> connected;

        connected.emplace_back(P1);
        int dis1 = (((it2 - pointsQ.begin()) - (it1 - pointsQ.begin()) + pointsQ.size()) % pointsQ.size());

        for (int i = 0; i < dis1; i++)
        {
            connected.emplace_back(pointsQ[(it1 - pointsQ.begin() + i) % pointsQ.size()]);
        }

        connected.emplace_back(Q2);

        it1 = find(pointsP.begin(), pointsP.end(), P1);
        it2 = find(pointsP.begin(), pointsP.end(), P2);

        int dis2 = (((it1 - pointsP.begin()) - (it2 - pointsP.begin()) + pointsP.size()) % pointsP.size());
        for (int i = 0; i < dis2; i++)
        {
            connected.emplace_back(pointsP[(it2 - pointsP.begin() + i) % pointsP.size()]);
        }

        /*for (Point p : connected)
            cout << p.x << ", " << p.y << endl;
        cout << endl;*/
        double poly = calculateArea(connected, dis1 + dis2 + 2);

        ofp << fixed << setprecision(1) << poly - P - Q << endl;
    }

    ifp.close();
    ofp.close();

    return 0;
}

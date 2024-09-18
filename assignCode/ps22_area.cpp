#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

struct Point
{
    long double x, y;
};
struct Circle
{
    Point center;
    double radius;
};

long double det(long double M[3][3])
{
    long double t1 = (M[1][1] * M[2][2]) - (M[1][2] * M[2][1]);
    long double t2 = (M[1][0] * M[2][2]) - (M[1][2] * M[2][0]);
    long double t3 = (M[1][0] * M[2][1]) - (M[1][1] * M[2][0]);

    return (M[0][0] * t1) + (-M[0][1] * t2) + (M[0][2] * t3);
}

long double calculateArea(Point p1, Point p2, Point p3)
{
    long double M[3][3];

    M[0][0] = p1.x;
    M[0][1] = p1.y;
    M[0][2] = 1;
    M[1][0] = p2.x;
    M[1][1] = p2.y;
    M[1][2] = 1;
    M[2][0] = p3.x;
    M[2][1] = p3.y;
    M[2][2] = 1;

    return fabs(det(M)) * 0.5;
}

long double dist(Point p, Point q)
{
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}


Point findIntersection(const Circle& c1, const Circle& c2, const Circle& c3)
{
    long double d = sqrt(pow((c2.center.x - c1.center.x), 2) + pow((c2.center.y - c1.center.y), 2));

    long double r_sum = c1.radius + c2.radius;
    long double r_diff = fabs(c1.radius - c2.radius);
    long double a = (pow(c1.radius, 2) - pow(c2.radius, 2) + pow(d, 2)) / (2 * d);
    long double h = sqrt(pow(c1.radius, 2) - pow(a, 2));
    long double x3 = c1.center.x + a * (c2.center.x - c1.center.x) / d;
    long double y3 = c1.center.y + a * (c2.center.y - c1.center.y) / d;

    Point p1, p2;
    p1.x = x3 + h * (c2.center.y - c1.center.y) / d;
    p1.y = y3 - h * (c2.center.x - c1.center.x) / d;
    p2.x = x3 - h * (c2.center.y - c1.center.y) / d;
    p2.y = y3 + h * (c2.center.x - c1.center.x) / d;


    if (dist(p1, c3.center) < dist(p2, c3.center))
        return p1;
    else
        return p2;
}

int main()
{
    ifstream ifp("area.inp");
    ofstream ofp("area.out");

    int T;
    ifp >> T;

    Circle a, b, c;
    for (int t = 0; t < T; t++)
    {
        ifp >> a.center.x >> a.center.y >> a.radius;
        ifp >> b.center.x >> b.center.y >> b.radius;
        ifp >> c.center.x >> c.center.y >> c.radius;

        Point p1 = findIntersection(a, b, c);
        Point p2 = findIntersection(b, c, a);
        Point p3 = findIntersection(a, c, b);
        ofp << fixed << setprecision(2);
        ofp << calculateArea(p1, p2, p3) << endl;
    }

    ifp.close();
    ofp.close();

    return 0;
}

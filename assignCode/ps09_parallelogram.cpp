#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

Point operator+(Point& a, Point& b)
{
    Point result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

bool operator==(Point& a, Point& b)
{
    return (a.x == b.x && a.y == b.y);
}

int main()
{
    ifstream ifp("parallelogram.inp");
    ofstream ofp("parallelogram.out");

    while (true)
    {
        Point points[4];
        int count = 0;

        for (int i = 0; i < 4; i++)
        {
            ifp >> points[i].x >> points[i].y;

            if (points[i].x == 0 && points[i].y == 0)
                count++;
        }

        if (count == 4)
            break;

        sort(begin(points), end(points), [](const Point& a, const Point& b){
            return a.x < b.x;
            });
        Point vec[3];

        for (int i = 1; i <= 3; i++)
        {
            vec[i - 1].x = points[i].x - points[0].x;
            vec[i - 1].y = points[i].y - points[0].y;
        }

        bool isPal = false;

        Point v[3];
        v[0] = vec[0] + vec[1];
        v[1] = vec[0] + vec[2];
        v[2] = vec[1] + vec[2];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (v[i] == vec[j])
                {
                    isPal = true;
                    break;
                }
            }
            if (isPal)
                break;
        }

        if (isPal)
            ofp << "1" << endl;
        else
            ofp << "0" << endl;

    }

    ifp.close();
    ofp.close();

    return 0;
}

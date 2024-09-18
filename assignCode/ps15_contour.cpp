#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
ofstream ofp("contour.out");

struct Event
{
    long long x;
    long long height;
    int type;

    bool operator<(const Event& other) const
    {
        if (x != other.x) return x < other.x;
        return type > other.type;
    }
};

void calculateTotalArea(const vector<tuple<long long, long long, long long>>& rectangles, int& count)
{
    vector<Event> events;

    for (const auto& rect : rectangles)
    {
        long long x1, height, x2;
        tie(x1, height, x2) = rect;
        events.push_back({ x1, height, 1 });
        events.push_back({ x2, height, -1 });
    }

    sort(events.begin(), events.end());

    map<long long, long long> activeHeights;
    long long previous_x = 0;
    long long area = 0;
    long long cur_area = 0;
    long long prev_area = 0;
    long long max_height = 0;

    ofp << "Test Case #" << count << " : ";
    for (size_t i = 0; i < events.size(); ++i)
    {
        Event& e = events[i];
        long long current_x = e.x;

        if (!activeHeights.empty() && current_x != previous_x)
        {
            area += (current_x - previous_x) * max_height;
        }

        if (e.type == 1)
        {
            activeHeights[e.height] += 1;
        }
        else 
        {
            if (--activeHeights[e.height] == 0)
            {
                activeHeights.erase(e.height);
            }
        }

        if (!activeHeights.empty())
        {
            max_height = activeHeights.rbegin()->first;
        }
        else
        {
            max_height = 0;
            cur_area = area;
            ofp << area - prev_area << " ";
            prev_area = area;
        }
        previous_x = current_x;

    }
    ofp << endl;
}

int main()
{
    ifstream ifp("contour.inp");

    int count = 1;
    while (true)
    {
        vector<tuple<long long, long long, long long>> rects;
        tuple<long long, long long, long long> t;
        long long lx, rx, y;

        while (true)
        {
            ifp >> lx >> y >> rx;
            if (lx == 0 && rx == 0 && y == 0)
                break;

            t = make_tuple(lx, y, rx);
            rects.emplace_back(t);
        }

        if (ifp.eof())
            break;

        calculateTotalArea(rects, count);

        count++;
    }

    ifp.close();
    ofp.close();

    return 0;
}

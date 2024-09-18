#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Rectangle
{
    long long x1, y1, x2, y2;
};

struct Event
{
    long long x;
    int type;
    long long y1, y2;
};

class SegmentTree
{
private:
    vector<int> tree;
    vector<int> lazy;
    vector<long long> coords;

    int getMid(int s, int e) { return s + (e - s) / 2; }

    void updateRangeUtil(int si, int ss, int se, int us, int ue, int diff)
    {
        if (lazy[si] != 0)
        {
            tree[si] += lazy[si];
            if (ss != se)
            {
                lazy[si * 2 + 1] += lazy[si];
                lazy[si * 2 + 2] += lazy[si];
            }
            lazy[si] = 0;
        }

        if (ss > se || ss > ue || se < us)
            return;

        if (ss >= us && se <= ue)
        {
            tree[si] += diff;
            if (ss != se)
            {
                lazy[si * 2 + 1] += diff;
                lazy[si * 2 + 2] += diff;
            }
            return;
        }

        int mid = getMid(ss, se);
        updateRangeUtil(si * 2 + 1, ss, mid, us, ue, diff);
        updateRangeUtil(si * 2 + 2, mid + 1, se, us, ue, diff);
    }

    long long getTotalActiveLength(int si, int ss, int se)
    {
        if (ss > se)
            return 0;

        if (lazy[si] != 0)
        {
            tree[si] += lazy[si];
            if (ss != se)
            {
                lazy[si * 2 + 1] += lazy[si];
                lazy[si * 2 + 2] += lazy[si];
            }
            lazy[si] = 0;
        }

        if (tree[si] > 0)
        {
            return coords[se + 1] - coords[ss];
        }
        else if (ss != se)
        {
            int mid = getMid(ss, se);
            return getTotalActiveLength(si * 2 + 1, ss, mid) +
                getTotalActiveLength(si * 2 + 2, mid + 1, se);
        }

        return 0;
    }

public:
    SegmentTree(const vector<long long>& unique_coords)
    {
        int n = unique_coords.size();
        coords = unique_coords;
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
    }

    void updateRange(int l, int r, int diff)
    {
        updateRangeUtil(0, 0, coords.size() - 2, l, r - 1, diff);
    }

    long long getTotalActiveLength()
    {
        return getTotalActiveLength(0, 0, coords.size() - 2);
    }
};

long long UnionArea(vector<Rectangle>& rects)
{
    vector<Event> events;
    vector<long long> allY;

    for (const auto& rect : rects)
    {
        events.push_back({ rect.x1, 1, rect.y1, rect.y2 });
        events.push_back({ rect.x2, -1, rect.y1, rect.y2 });
        allY.push_back(rect.y1);
        allY.push_back(rect.y2);
    }

    sort(allY.begin(), allY.end());
    allY.erase(unique(allY.begin(), allY.end()), allY.end());

    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.x < b.x || (a.x == b.x && a.type > b.type);
        });

    SegmentTree st(allY);
    long long lastX = 0;
    long long totalArea = 0;

    for (const auto& event : events)
    {
        long long currentX = event.x;
        if (currentX != lastX)
        {
            long long width = currentX - lastX;
            long long height = st.getTotalActiveLength();
            totalArea += width * height;
            lastX = currentX;
        }
        int y1_idx = lower_bound(allY.begin(), allY.end(), event.y1) - allY.begin();
        int y2_idx = lower_bound(allY.begin(), allY.end(), event.y2) - allY.begin();
        st.updateRange(y1_idx, y2_idx, event.type);
    }

    return totalArea;
}



int main()
{
    ifstream ifp("rectangles.inp");
    ofstream ofp("rectangles.out");

    Rectangle R;
    vector<Rectangle> rects;
    int n;

    ifp >> n;

    for (int i = 0; i < n; i++)
    {
        ifp >> R.x1 >> R.y1 >> R.x2 >> R.y2;
        rects.emplace_back(R);
    }

    ofp << UnionArea(rects);

    ifp.close();
    ofp.close();
}

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <climits>

using namespace std;

struct Point {
    long long x, y;
    int id = -1;
};

struct Edge {
    int v; // Vertex v (or "to" vertex)
    // of a directed edge u-v. "From"
    // vertex u can be obtained using
    // index in adjacent array.

    int flow; // flow of data in edge

    int C; // capacity

    int rev; // To store index of reverse
    // edge in adjacency list so that
    // we can quickly find it.
};

// Residual Graph
class Graph {
    int V; // number of vertex
    int* level; // stores level of a node
    vector<Edge>* adj;

public:
    Graph(int V)
    {
        adj = new vector<Edge>[V];
        this->V = V;
        level = new int[V];
    }

    // add edge to the graph
    void addEdge(int u, int v, int C)
    {
        // Forward edge : 0 flow and C capacity
        Edge a{ v, 0, C, (int)adj[v].size() };

        // Back edge : 0 flow and 0 capacity
        Edge b{ u, 0, 0, (int)adj[u].size() };

        adj[u].push_back(a);
        adj[v].push_back(b); // reverse edge
    }

    bool BFS(int s, int t);
    int sendFlow(int s, int flow, int t, int ptr[]);
    int DinicMaxflow(int s, int t);
};

// Finds if more flow can be sent from s to t.
// Also assigns levels to nodes.
bool Graph::BFS(int s, int t)
{
    for (int i = 0; i < V; i++)
        level[i] = -1;

    level[s] = 0; // Level of source vertex

    // Create a queue, enqueue source vertex
    // and mark source vertex as visited here
    // level[] array works as visited array also.
    list<int> q;
    q.push_back(s);

    vector<Edge>::iterator i;
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (i = adj[u].begin(); i != adj[u].end(); i++) {
            Edge& e = *i;
            if (level[e.v] < 0 && e.flow < e.C) {
                // Level of current vertex is,
                // level of parent + 1
                level[e.v] = level[u] + 1;

                q.push_back(e.v);
            }
        }
    }

    // IF we can not reach to the sink we
    // return false else true
    return level[t] < 0 ? false : true;
}

// A DFS based function to send flow after BFS has
// figured out that there is a possible flow and
// constructed levels. This function called multiple
// times for a single call of BFS.
// flow : Current flow send by parent function call
// start[] : To keep track of next edge to be explored.
//           start[i] stores  count of edges explored
//           from i.
//  u : Current vertex
//  t : Sink
int Graph::sendFlow(int u, int flow, int t, int start[])
{
    // Sink reached
    if (u == t)
        return flow;

    // Traverse all adjacent edges one -by - one.
    for (; start[u] < adj[u].size(); start[u]++) {
        // Pick next edge from adjacency list of u
        Edge& e = adj[u][start[u]];

        if (level[e.v] == level[u] + 1 && e.flow < e.C) {
            // find minimum flow from u to t
            int curr_flow = min(flow, e.C - e.flow);

            int temp_flow
                = sendFlow(e.v, curr_flow, t, start);

            // flow is greater than zero
            if (temp_flow > 0) {
                // add flow  to current edge
                e.flow += temp_flow;

                // subtract flow from reverse edge
                // of current edge
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }

    return 0;
}

// Returns maximum flow in graph
int Graph::DinicMaxflow(int s, int t)
{
    // Corner case
    if (s == t)
        return -1;

    int total = 0; // Initialize result

    // Augment the flow while there is path
    // from source to sink
    while (BFS(s, t) == true) {
        // store how many edges are visited
        // from V { 0 to V }
        int* start = new int[V + 1]{ 0 };

        // while flow is not zero in graph from S to D
        while (int flow = sendFlow(s, INT_MAX, t, start)) {

            // Add path flow to overall flow
            total += flow;
        }

        // Remove allocated array
        delete[] start;
    }

    // return maximum flow
    return total;
}

long long ccw2(Point p, Point q)
{
    return p.x * q.y - p.y * q.x;
}

long long ccw(Point r, Point p, Point q)
{
    Point a;
    a.x = p.x - r.x;
    a.y = p.y - r.y;
    Point b;
    b.x = q.x - r.x;
    b.y = q.y - r.y;
    return ccw2(a, b);
}

int direction(Point a, Point b, Point c)
{
    if (ccw(a, b, c) < 0)
        return -1;
    if (ccw(a, b, c) > 0)
        return 1;
    return 0;
}

bool intersectProp(Point a, Point b, Point c, Point d) {
    return direction(a, b, c) * direction(a, b, d) < 0 &&
        direction(c, d, a) * direction(c, d, b) < 0;
}

bool collinear(Point a, Point b, Point c)
{
    return ccw(a, b, c) == 0;
}

bool between(Point a, Point b, Point c)
{
    if (!collinear(a, b, c))
        return false;
    if (a.x != b.x)
        return a.x <= c.x && c.x <= b.x || b.x <= c.x && c.x <= a.x;
    else
        return a.y <= c.y && c.y <= b.y || b.y <= c.y && c.y <= a.y;
}

bool intersectPolygon(const vector<Point>& polygon, Point p1, Point p2)
{
    int n = polygon.size();
    for (int i = 0; i < n; i++)
    {
        int next = (i + 1) % n;
        if (intersectProp(polygon[i], polygon[next], p1, p2) || between(p1, p2, polygon[i]) || between(p1, p2, polygon[next]))
        {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream ifp("mice.inp");
    ofstream ofp("mice.out");

    int T;
    ifp >> T;

    for (int t = 0; t < T; t++)
    {
        vector<Point> polygon;
        vector<Point> hole;
        int N, k, H, M;
        Point p;

        ifp >> N >> k >> H >> M;

        Graph g(M + H + 2);

        for (int n = 0; n < N; n++)
        {
            ifp >> p.x >> p.y;
            polygon.emplace_back(p);
        }

        for (int h = 0; h < H; h++)
        {
            ifp >> p.x >> p.y;
            p.id = h + M + 1;
            hole.emplace_back(p);
            g.addEdge(p.id, M + H + 1, k);
            //cout << p.id << " ----" << k << "---- " << M + H + 1 << endl;
        }

        for (int m = 0; m < M; m++)
        {
            ifp >> p.x >> p.y;
            p.id = m + 1;
            g.addEdge(0, p.id, 1);
            //cout << 0 << " ----" << 1 << "---- " << p.id << endl;
            for (int h = 0; h < H; h++)
            {
                if (!intersectPolygon(polygon, hole[h], p))
                {
                    g.addEdge(p.id, hole[h].id, 1);
                    //cout << p.id << " -------- " << hole[h].id << endl;
                }
            }
            //cout << endl;
        }

        int maximumFlow = g.DinicMaxflow(0, M + H + 1);
        if (maximumFlow == M)
        {
            ofp << "Possible" << endl;
            //cout << "Possible "<< maximumFlow << endl;
        }
        else
        {
            ofp << "Impossible" << endl;
            //cout << "Impossible " << maximumFlow << endl;
        }
    }

    ifp.close();
    ofp.close();

    return 0;
}

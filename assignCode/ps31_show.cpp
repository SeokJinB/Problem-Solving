#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

class TwoSat {
private:
    int n;
    vector<vector<int>> graph;
    vector<vector<int>> revGraph;
    vector<bool> visited;
    stack<int> order;
    vector<int> component;
    vector<int> assignment;

    void addEdge(int u, int v) {
        graph[u].push_back(v);
        revGraph[v].push_back(u);
    }

    void dfs1(int v) {
        visited[v] = true;
        for (int u : graph[v]) {
            if (!visited[u]) {
                dfs1(u);
            }
        }
        order.push(v);
    }

    void dfs2(int v, int comp) {
        component[v] = comp;
        for (int u : revGraph[v]) {
            if (component[u] == -1) {
                dfs2(u, comp);
            }
        }
    }

public:
    TwoSat(int numVariables) : n(numVariables), graph(2 * numVariables), revGraph(2 * numVariables), visited(2 * numVariables, false), component(2 * numVariables, -1), assignment(numVariables, -1) {}

    void addClause(int x, bool xIsTrue, int y, bool yIsTrue) {
        int notX = x * 2 + (xIsTrue ? 0 : 1);
        int notY = y * 2 + (yIsTrue ? 0 : 1);
        int X = x * 2 + (xIsTrue ? 1 : 0);
        int Y = y * 2 + (yIsTrue ? 1 : 0);
        addEdge(notX, Y);
        addEdge(notY, X);
    }

    bool solve() {
        for (int i = 0; i < 2 * n; ++i) {
            if (!visited[i]) {
                dfs1(i);
            }
        }
        int comp = 0;
        while (!order.empty()) {
            int v = order.top();
            order.pop();
            if (component[v] == -1) {
                dfs2(v, comp++);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (component[2 * i] == component[2 * i + 1]) {
                return false;
            }
            assignment[i] = (component[2 * i] > component[2 * i + 1]);
        }
        return true;
    }

    vector<int> getAssignment() {
        return assignment;
    }
};

int main()
{
    ifstream ifp("show.inp");
    ofstream ofp("show.out");
    
    int T, k, N;

    ifp >> T;

    for (int t = 0; t < T; t++)
    {
        int n1, n2, n3;
        bool c1, c2, c3;

        char color;

        ifp >> k >> N;

        TwoSat result(k);


        for (int i = 0; i < N; i++)
        {
            c1 = true; c2 = true; c3 = true;

            ifp >> n1 >> color;
            if (color == 'B')
                c1 = false;

            ifp >> n2 >> color;
            if (color == 'B')
                c2 = false;

            ifp >> n3 >> color;
            if (color == 'B')
                c3 = false;

            //cout << n1 << "or" << c1 << " and " << n2 << "or" << c2 << " and " << n3 << "or" << c3 << endl;
            result.addClause(n1 - 1, c1, n2 - 1, c2);
            result.addClause(n2 - 1, c2, n3 - 1, c3);
            result.addClause(n1 - 1, c1, n3 - 1, c3);

        }

        if (result.solve())
            ofp << 1 << endl;
        else
            ofp << -1 << endl;

    }

    ifp.close();
    ofp.close();

    return 0;
}

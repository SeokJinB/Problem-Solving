#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <list>
#include <string>

using namespace std;

class Graph {
    int V;
    list<int>* adj;
    void fillOrder(int s, bool visitedV[], stack<int>& Stack);
    void DFS(int s, bool visitedV[]);

public:
    Graph(int V);
    void addEdge(int s, int d);
    int countSCC();
    Graph transpose();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

// DFS
void Graph::DFS(int s, bool visitedV[]) {
    visitedV[s] = true;
    //cout << s << " ";

    list<int>::iterator i;
    for (i = adj[s].begin(); i != adj[s].end(); ++i)
        if (!visitedV[*i])
            DFS(*i, visitedV);
}

// Transpose
Graph Graph::transpose() {
    Graph g(V);
    for (int s = 0; s < V; s++) {
        list<int>::iterator i;
        for (i = adj[s].begin(); i != adj[s].end(); ++i) {
            g.adj[*i].push_back(s);
        }
    }
    return g;
}

// Add edge into the graph
void Graph::addEdge(int s, int d) {
    adj[s].push_back(d);
}

void Graph::fillOrder(int s, bool visitedV[], stack<int>& Stack) {
    visitedV[s] = true;

    list<int>::iterator i;
    for (i = adj[s].begin(); i != adj[s].end(); ++i)
        if (!visitedV[*i])
            fillOrder(*i, visitedV, Stack);

    Stack.push(s);
}

// Print strongly connected component
int Graph::countSCC() {
    stack<int> Stack;
    int count = 0;

    bool* visitedV = new bool[V];
    for (int i = 0; i < V; i++)
        visitedV[i] = false;

    for (int i = 0; i < V; i++)
        if (visitedV[i] == false)
            fillOrder(i, visitedV, Stack);

    Graph gr = transpose();

    for (int i = 0; i < V; i++)
        visitedV[i] = false;

    while (Stack.empty() == false) {
        int s = Stack.top();
        Stack.pop();

        if (visitedV[s] == false) {
            gr.DFS(s, visitedV);
            count++;
            //cout << endl;
        }
    }
    return count;
}

int main() {
    ifstream ifp("scc.inp");
    ofstream ofp("scc.out");

    int vn, n, v, a;
    vector<vector<int>> edges;
    ifp >> vn >> n;
    Graph g(vn);
    for (int i = 0; i < n; i++)
    {
        ifp >> v >> a;
        g.addEdge(v, a);
    }

    ofp << g.countSCC();

    ifp.close();
    ofp.close();

    return 0;
}

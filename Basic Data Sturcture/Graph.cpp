#include <iostream>
#include <vector>
#include <queue>
#include <climits> // for INT_MAX

using namespace std;

class Graph
{
public:
    int vertices;
    vector<vector<int>> adjMatrix;

    // Constructor
    Graph(int vertices)
    {
        this->vertices = vertices;
        adjMatrix.resize(vertices, vector<int>(vertices, INT_MAX)); // 무한대로 초기화

        // 대각선(자기 자신으로의 경로)은 0으로 설정
        for (int i = 0; i < vertices; i++)
            adjMatrix[i][i] = 0;
    }

    // 가중치가 있는 간선 추가
    void addEdge(int v, int w, int weight)
    {
        adjMatrix[v][w] = weight;
        adjMatrix[w][v] = weight; // 무방향 그래프이므로 대칭으로 설정
    }

    // BFS 구현 (가중치와 무관)
    bool BFS(int start, int target)
    {
        vector<bool> visited(vertices, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            if (v == target)
                return true;

            for (int i = 0; i < vertices; i++)
            {
                if (adjMatrix[v][i] != INT_MAX && !visited[i]) // 간선이 존재하는 경우
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        return false;
    }

    // DFS 구현 (가중치와 무관)
    bool DFS(int v, int target, vector<bool>& visited)
    {
        visited[v] = true;

        if (v == target)
            return true;

        for (int i = 0; i < vertices; i++)
        {
            if (adjMatrix[v][i] != INT_MAX && !visited[i]) // 간선이 존재하는 경우
            {
                if (DFS(i, target, visited))
                    return true;
            }
        }
        return false;
    }

    // 그래프 출력
    void printGraph()
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if (adjMatrix[i][j] == INT_MAX)
                    cout << "INF ";
                else
                    cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph g(5);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 4, 1);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 1);

    cout << "Adjacency Matrix with Weights:\n";
    g.printGraph();

    int target = 3;

    if (g.BFS(0, target))
        cout << "Target " << target << " found using BFS!" << endl;
    else
        cout << "Target " << target << " not found using BFS!" << endl;

    vector<bool> visited(g.vertices, false);

    if (g.DFS(0, target, visited))
        cout << "Target " << target << " found using DFS!" << endl;
    else
        cout << "Target " << target << " not found using DFS!" << endl;

    return 0;
}

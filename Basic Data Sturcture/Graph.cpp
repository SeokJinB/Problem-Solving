#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
public:
	int vertices;
	vector<vector<int>> adjMatrix;

	Graph(int vertices)
	{
		this->vertices = vertices;
		adjMatrix.resize(vertices, vector<int>(vertices, 0));
	}

	void addEdge(int v, int w)
	{
		adjMatrix[v][w] = 1;
		adjMatrix[w][v] = 1;
	}

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
			//cout << v << " ";

			if (v == target)
				return true;

			for (int i = 0; i < vertices; i++)
			{
				if (adjMatrix[v][i] == 1 && !visited[i])
				{
					visited[i] = true;
					q.push(i);
				}
			}
		}
		return false;
	}

	bool DFS(int v, int target, vector<bool>& visited)
	{
		visited[v] = true;
		//cout<< v << " ";

		if (v == target)
			return true;

		for (int i = 0; i < vertices; i++)
		{
			if (adjMatrix[v][i] == 1 && !visited[i])
			{
				if (DFS(i, target, visited))
					return true;
			}
		}

		return false;
	}

	void printGraph()
	{
		for (int i = 0; i < vertices; i++)
		{
			for (int j = 0; j < vertices; j++)
			{
				cout << adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
};

int main(void)
{
	Graph g(5);

	g.addEdge(0, 1);
	g.addEdge(0, 4);
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(2, 3);
	g.addEdge(3, 4);

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
}
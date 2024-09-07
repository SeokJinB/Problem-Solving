#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// BFS
int getMinDistance(vector<vector<int>>& maze)
{
    int n = maze.size();
    int m = maze[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<pair<pair<int, int>, int>> path;
    vector<int> upDown = { 0, 0, 1, -1 };
    vector<int> leftRight = { -1, 1, 0, 0 };

    visited[0][0] = true;
    path.push(make_pair(make_pair(0, 0), 1));

    while (!path.empty())
    {
        int x = path.front().first.first;
        int y = path.front().first.second;
        int dist = path.front().second;

        path.pop();

        if (x == n - 1 && y == m - 1)
            return dist;

        int nextX, nextY;
        for (int i = 0; i < 4; i++)
        {
            nextX = x + upDown[i];
            nextY = y + leftRight[i];

            if (nextX >= 0 && nextY >= 0 && nextX < n && nextY < m && !visited[nextX][nextY] && maze[nextX][nextY] == 1)
            {
                visited[nextX][nextY] = true;
                path.push(make_pair(make_pair(nextX, nextY), dist + 1));
            }
        }
    }
    return -1;
}

int main()
{
    // 0: obstacle
    // 1: path
    vector<vector<int>> maze = {
        {1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1},
        {0, 0, 0, 0, 1}
    };

    int row = maze.size();
    int col = maze[0].size();
    int minDistance = getMinDistance(maze);

    cout << "Minimum distance (0,0) to (" << row-1 << ", " << col-1 << "): " << minDistance << endl;
}


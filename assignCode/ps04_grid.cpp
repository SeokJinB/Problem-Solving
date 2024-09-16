/*
Didn't get a perfect credit (0/100) : Time limit(1000ms) exceeded
Code modification is required
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

int x, y, k;
vector<vector<int>> grid;
vector<vector<vector<int>>> dp;

bool isValid(int i, int j)
{
    return i <= x && j <= y && grid[i][j] != -1;
}

int explorePaths(int i, int j, int visitedCount)
{
    if (i == x && j == y && visitedCount >= k)
        return 1;
    if (dp[i][j][visitedCount] != -1)
        return dp[i][j][visitedCount];

    int count = 0;
    int originalValue = grid[i][j];
    grid[i][j] = -1;

    if (isValid(i, j + 1))
        count = (count + explorePaths(i, j + 1, visitedCount + (originalValue == 1))) % MOD;

    if (isValid(i + 1, j))
        count = (count + explorePaths(i + 1, j, visitedCount + (originalValue == 1))) % MOD;

    grid[i][j] = originalValue;
    return dp[i][j][visitedCount] = count;
}

int main()
{
    ifstream ifp("grid.inp");
    ofstream ofp("grid.out");
    int T, a, b, p1, p2;
    ifp >> T;

    for (int t = 0; t < T; t++)
    {
        ifp >> x >> y >> a >> b >> k;
        grid.assign(x + 1, vector<int>(y + 1, 0));
        dp.assign(x + 1, vector<vector<int>>(y + 1, vector<int>(a + 1, -1)));

        for (int i = 0; i < a; i++)
        {
            ifp >> p1 >> p2;
            grid[p1][p2] = 1;
        }

        for (int i = 0; i < b; i++)
        {
            ifp >> p1 >> p2;
            grid[p1][p2] = -1;
        }

        int count = explorePaths(0, 0, 0);
       // cout << count << endl;
        ofp << count << endl;
    }

    ifp.close();
    ofp.close();

    return 0;
}

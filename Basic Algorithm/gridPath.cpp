#include <iostream>
#include <vector>

using namespace std;

int gridPath(vector<vector<int>>& grid)
{
	int m = grid.size();
	int n = grid[0].size();

	grid[0][0] = 1;

	for (int i = 1; i < m; i++)
	{
		if (grid[i][0] != -1)
		{
			grid[i][0] = grid[i - 1][0];
		}
		else
		{
			grid[i][0] = 0;
		}
	}

	for (int i = 1; i < n; i++)
	{
		if (grid[0][i] != -1)
		{
			grid[0][i] = grid[0][i - 1];
		}
		else
		{
			grid[0][i] = 0;
		}
	}

	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (grid[i][j] != -1)
			{
				grid[i][j] = grid[i - 1][j] + grid[i][j - 1];
			}
			else
			{
				grid[i][j] = 0;
			}
		}
	}

	return grid[m - 1][n - 1];
}

int main()
{
	vector<vector<int>> grid =
	{
		{0,0,0,0},
		{0,-1,0,0},
		{0,0,0,0}
	};

	cout << gridPath(grid) << endl;
}

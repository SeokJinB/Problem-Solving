#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<pair<int, int>>& cor, int row, int col)
{
	for (int i = 0; i < cor.size(); i++)
	{
		pair<int, int> q = cor[i];

		if (q.first == row || q.second == col)
			return false;
		if (abs(q.first - row) == abs(q.second - col))
			return false;
	}
	return true;
}

void NQueens(vector<pair<int, int>>& cor, int n, int col, vector<vector<pair<int, int>>>& result)
{
	if (col == n)
	{
		result.emplace_back(cor);
		return;
	}

	for (int row = 0; row < n; row++)
	{

		if (isSafe(cor, row, col))
		{
			cor.emplace_back(make_pair(row, col));
			NQueens(cor, n, col + 1, result);
			cor.pop_back();
		}
	}

}

int main()
{
	int n, m;

	cin >> n;

	vector<pair<int, int>> cor;
	vector<vector<pair<int, int>>> result;

	NQueens(cor, n, 0, result);

	cout << result.size();
}
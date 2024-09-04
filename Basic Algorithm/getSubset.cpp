#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> getSubset(const vector<int>& set)
{
    vector<vector<int>> result;

    result.push_back({});

    for (int n : set)
    {
        int len = result.size();

        for (int i = 0; i < len; ++i)
        {
            vector<int> subset = result[i];
            subset.push_back(n);
            result.push_back(subset);
        }
    }

    return result;
}

int main()
{
    vector<int> set = { 1, 2, 3 };

	vector<vector<int>> subset = getSubset(set);

    for (vector<int> v : subset)
    {
        for (int i : v)
            cout << i << " ";
        cout << '\n';
    }
}


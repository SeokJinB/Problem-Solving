#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	ifstream ifp("jolly.inp");
	ofstream ofp("jolly.out");
	
	int n;

	while (ifp >> n)
	{
		vector<int> values;
		vector<int> vec;
		int prev, cur;
		ifp >> prev;

		for (int i = 1; i < n; i++)
		{
			vec.emplace_back(i);
			ifp >> cur;
			int value = (prev - cur) > 0 ? (prev - cur) : (cur - prev);
			values.emplace_back(value);

			prev = cur;
		}
		sort(values.begin(), values.end());

		
		if (vec == values)
			ofp << "Jolly" << endl;
		else
			ofp << "Not Jolly" << endl;
	}
	ifp.close();
	ofp.close();
}

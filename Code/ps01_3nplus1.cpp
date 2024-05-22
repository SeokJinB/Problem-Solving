#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main()
{
	ifstream ifp("3nplus1.inp");
	ofstream ofp("3nplus1.out");
	int i, j, start, end, count, n, cycle_length;
	unordered_map<int, int> map;

	while(ifp>>i>>j)
	{
		start = min(i, j);
		end = max(i, j);
		cycle_length = 0;
		vector<int> vec;

		for (int a = start; a <= end; a++)
		{
			count = 0;
			n = a;

			while (true)
			{
				if (map.find(n) != map.end())
				{
					count += map[n];
					break;
				}
				count++;
				//cout << n << " ";
				if (n == 1)
					break;
				if (n % 2 == 1)
					n = 3 * n + 1;
				else
					n = n / 2;
			}
			map[a] = count;
			//cout<<endl;
			cycle_length = max(cycle_length, count);
		}
		//cout << cycle_length << endl;

		ofp << i << " " << j << " " << cycle_length << endl;
	}
	ifp.close();
	ofp.close();
}
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> permutationCycle(const vector<int>& permutation, int n)
{
    vector<bool> isVisited(n, false);
    vector<vector<int>> cycles;

    for (int i = 0; i < n; ++i)
    {
        if (!isVisited[i])
        {
            vector<int> cycle;
            int current = i;
            do {
                isVisited[current] = true;
                cycle.emplace_back(current);
                current = permutation[current];
            } while (current != i);

            cycles.emplace_back(cycle);
        }
    }

    return cycles;
}

int main()
{
    ifstream ifp("cycle.inp");
    ofstream ofp("cycle.out");

    int T;

    ifp >> T;

    for (int t = 0; t < T; t++)
    {
        int n, num;
        vector<int> permutation;
        ifp >> n;

        for (int i = 0; i < n; i++)
        {
            ifp >> num;
            num--;
            permutation.emplace_back(num);
        }

        vector<vector<int>> cycles = permutationCycle(permutation, n);

        ofp << cycles.size() << endl;
    }

    ifp.close();
    ofp.close();

    return 0;
}

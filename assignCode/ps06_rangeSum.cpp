#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream ifp("rangeSum.inp");
    ofstream ofp("rangeSum.out");
    
    vector<int> A;
    
    int N, n;
    char op;
    long long a, b, sum;

    ifp >> N;

    for (int i = 0; i < N; i++)
    { 
        ifp >> n;
        A.emplace_back(n);
    }

    while (true)
    {
        ifp >> op;

        if (op == 'q')
            break;

        ifp >> a >> b;
        a--;
        if (op == 'c')
        {
            A[a] = b;
        }
        else if (op == 's')
        {
            sum = 0;
            for (int i = a; i < b; i++)
            {
                sum += A[i];
            }
            ofp << sum << endl;
        }
    }

    ifp.close();
    ofp.close();

    return 0;
}

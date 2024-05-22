#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

int main()
{
    ifstream ifp("dish.inp");
    ofstream ofp("dish.out");
    
    int T, N;
    char dish;

    ifp >> T;
    for (int t = 0; t < T; t++)
    {
        stack<char> dishes;
        int height = 10;

        ifp >> N >> dish;
        dishes.push(dish);

        for (int i = 0; i < N - 1; i++)
        {
            ifp >> dish;

            if (dish == dishes.top())
                height += 5;
            else
                height += 10;

            dishes.push(dish);
        }
        ofp << height << endl;
    }

    ifp.close();
    ofp.close();

    return 0;
}
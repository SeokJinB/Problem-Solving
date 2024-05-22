#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream ifp("trip.inp");
	ofstream ofp("trip.out");
    int n;
    int r;

    while (true)
    {
        double under = 0.0;
        double over = 0.0;

        ifp >> n;
        if (n == 0)
            return;

        vector<double> costs;
        double sum = 0.0;
        double avg;
        for (int i = 0; i < n; i++)
        {
            ifp >> r;
            costs.emplace_back(r);
            sum += r;
        }
        avg = sum / n;

        for (double cost : costs)
        {
            double sub = (int)((cost - avg) * 100) / 100.0;
            
            if (sub < 0)
                under -= sub;
            else
                over += sub;
        }

        //cout.precision(2);
        ofp.precision(2);
        if (under > over)
        {
            ofp << "$" << fixed << under << endl;
            //cout << "$" << fixed << result1 << endl;
        }
        else
        {
            ofp << "$" << fixed << over << endl;
            //cout << "$" << fixed << result2 << endl;
        }
    }
	ifp.close();
	ofp.close();
}
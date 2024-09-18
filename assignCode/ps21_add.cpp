#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ifstream ifp("add.inp");
    ofstream ofp("add.out");
    long long N, n;

    while (ifp >> N && N != 0) 
    {
        priority_queue<long long, vector<long long>, greater<long long>> pq;

        for (long long i = 0; i < N; ++i) 
        {
            ifp >> n;
            pq.push(n);
        }

        long long minimal = 0;
        while (pq.size() > 1)
        {
            long long first = pq.top(); pq.pop();
            long long second = pq.top(); pq.pop();
            long long cost = first + second;
            pq.push(cost);
            minimal += cost;
        }

        ofp << minimal << endl;
    }

    ifp.close();
    ofp.close();

    return 0;
}

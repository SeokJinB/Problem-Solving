#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b)
{
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

vector<pair<long long, long long>> generatePythagoreanTriples(int wireLength)
{
    vector<pair<long long, long long>> triples;
    for (int m = 2; ; ++m) {
        long long mSquare = (long long)m * m;
        for (int n = 1; n < m; ++n) {
            if ((m - n) % 2 == 1 && gcd(m, n) == 1) {
                long long a = mSquare - (long long)n * n;
                long long b = 2LL * (long long)m * n;
                long long perimeter = 2LL * (a + b);
                if (perimeter > wireLength)
                    break;
                triples.emplace_back(a, b);
            }
        }
        if (2LL * (mSquare + m) > wireLength)
            break;
    }
    return triples;
}

int main()
{
    ifstream ifp("rectangles.inp");
    ofstream ofp("rectangles.out");

    int T;
    ifp >> T;

    for (int t = 0; t < T; ++t)
    {
        int wireLength;
        ifp >> wireLength;

        vector<pair<long long, long long>> rectangles = generatePythagoreanTriples(wireLength);

        sort(rectangles.begin(), rectangles.end(), [](const pair<long long, long long>& a, const pair<long long, long long>& b) {
            return (2 * (a.first + a.second)) < (2 * (b.first + b.second));
            });

        long long count = 0;
        for (const auto& rect : rectangles)
        {
            wireLength -= 2 * (rect.first + rect.second);
            if (wireLength < 0)
                break;
            count++;
        }

        ofp << count << endl;
    }

    return 0;
}

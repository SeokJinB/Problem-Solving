#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long modInverse(long long a, long long m)
{
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1)
    {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

bool merge(long long r1, long long m1, long long r2, long long m2, long long& r, long long& m)
{
    long long g = gcd(m1, m2);

    if ((r2 - r1) % g != 0)
        return false;

    m = (m1 / g) * m2;
    long long inv = modInverse(m1 / g, m2 / g);
    long long x = ((r2 - r1) / g) * inv % (m2 / g);
    r = (x * m1 + r1) % m;

    if (r < 0)
        r += m;

    return true;
}

long long generalizedCRT(const std::vector<long long>& rs, const std::vector<long long>& ms)
{
    long long r = rs[0], m = ms[0];

    for (size_t i = 1; i < rs.size(); ++i)
        if (!merge(r, m, rs[i], ms[i], r, m))
            return -1;

    return r;
}

int main()
{
    ifstream ifp("crt.inp");
    ofstream ofp("crt.out");

    long long r, m;
    int T, K;

    ifp >> T;

    for (int t = 0; t < T; t++)
    {
        vector<long long> rs;
        vector<long long> ms;
        ifp >> K;

        for (int k = 0; k < K; k++)
        {
            ifp >> r >> m;
            rs.push_back(r);
            ms.push_back(m);
        }

        long long result = generalizedCRT(rs, ms);
        ofp << result << endl;
    }

    ifp.close();
    ofp.close();

    return 0;
}

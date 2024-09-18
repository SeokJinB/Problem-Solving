#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef vector<vector<long long>> Matrix;
const int MOD = 1e9 + 7;

Matrix multiply(const Matrix& A, const Matrix& B)
{
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j] % MOD) % MOD;
            }
        }
    }
    return C;
}

Matrix identity(int n)
{
    Matrix I(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i)
    {
        I[i][i] = 1;
    }
    return I;
}

Matrix power(Matrix A, long long k)
{
    int n = A.size();
    Matrix result = identity(n);
    while (k > 0)
    {
        if (k % 2 == 1)
        {
            result = multiply(result, A);
        }
        A = multiply(A, A);
        k /= 2;
    }
    return result;
}

int main()
{
    ifstream ifp("bigFibonacci.inp");
    ofstream ofp("bigFibonacci.out");

    int T;
    long long n;
    ifp >> T;

    Matrix A(2, vector<long long>(2));

    A[0][0] = 0;
    A[0][1] = 1;
    A[1][0] = 1;
    A[1][1] = 1;

    for (int t = 0; t < T; t++)
    {
        ifp >> n;
        ofp << n << " ";
        if (n == 0)
        {
            ofp << 0 << endl;
        }
        else
        {
            Matrix result = power(A, n - 1);
            ofp << result[1][1] << endl;
        }
    }

    ifp.close();
    ofp.close();

    return 0;
}

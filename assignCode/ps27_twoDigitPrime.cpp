#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <string>

using namespace std;

bool isPrime(int num) {
    for (int i = 2; i <= std::sqrt(num); ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

bool isTwoDigitPrime(int n) {
    string numStr = to_string(n);
    int length = numStr.length();
    set<int> twoDigitNumbers;

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (i != j && numStr[i] - '0' != 0) {
                int twoDigit = (numStr[i] - '0') * 10 + (numStr[j] - '0');
                twoDigitNumbers.insert(twoDigit);
            }
        }
    }

    for (int num : twoDigitNumbers) {
        if (isPrime(num)) {
            return true;
        }
    }
    return false;
}
int main() {
    ifstream ifp("twoDigitPrime.inp");
    ofstream ofp("twoDigitPrime.out");
    int T, a, b;

    ifp >> T;

    for (int t = 0; t < T; t++)
    {
        ifp >> a >> b;

        if (b <= 10)
        {
            //cout << "0" << endl;
            ofp << "0" << endl;
            continue;
        }

        if (a <= 10)
            a = 11;

        int result = 0;
        for (int i = a; i <= b; i++)
        {
            if (isTwoDigitPrime(i))
            {
                result++;
            }
        }
        ofp << result << endl;
        //cout << result << endl;
    }

    ifp.close();
    ofp.close();

    return 0;
}

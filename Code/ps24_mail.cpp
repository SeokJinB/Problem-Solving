#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

map<string, char> code =
{
    {"000000", 'A'},
    {"001111", 'B'},
    {"010011", 'C'},
    {"011100", 'D'},
    {"100110", 'E'},
    {"101001", 'F'},
    {"110101", 'G'},
    {"111010", 'H'}
};

int main() {
    ifstream ifp("mail.inp");
    ofstream ofp("mail.out");
    int T, n, a, b, c, d, e, f, g, h;

    for (int i = 0; i < 6; i++)
    {
        a = bitset<6>("000000").to_ulong();
        b = bitset<6>("001111").to_ulong();
        c = bitset<6>("010011").to_ulong();
        d = bitset<6>("011100").to_ulong();
        e = bitset<6>("100110").to_ulong();
        f = bitset<6>("101001").to_ulong();
        g = bitset<6>("110101").to_ulong();
        h = bitset<6>("111010").to_ulong();

        a ^= (1 << i);
        b ^= (1 << i);
        c ^= (1 << i);
        d ^= (1 << i);
        e ^= (1 << i);
        f ^= (1 << i);
        g ^= (1 << i);
        h ^= (1 << i);

        code[bitset<6>(a).to_string()] = 'A';
        code[bitset<6>(b).to_string()] = 'B';
        code[bitset<6>(c).to_string()] = 'C';
        code[bitset<6>(d).to_string()] = 'D';
        code[bitset<6>(e).to_string()] = 'E';
        code[bitset<6>(f).to_string()] = 'F';
        code[bitset<6>(g).to_string()] = 'G';
        code[bitset<6>(h).to_string()] = 'H';
    }

    ifp >> T;
    for (int t = 0; t < T; t++)
    {
        ifp >> n;
        for (int i = 0; i < n; i++)
        {
            string s = "";
            char c;
            for (int j = 0; j < 6; j++)
            {
                ifp >> c;
                s += c;
            }

            auto it = code.find(s);
            if (it != code.end())
            {
                ofp << it->second;
            }
            else
            {
                ofp << 'X';
            }
        }
        ofp << endl;
    }

    ifp.close();
    ofp.close();

    return 0;
}

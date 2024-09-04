#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(const string& str, char delimiter)
{
	vector<string> tokens;
	stringstream ss(str);
	string token;
	
	while (getline(ss, token, delimiter))
	{
		if(!token.empty())
			tokens.emplace_back(token);
	}
	return tokens;
}

int main()
{
	string str;
	char delimiter;
	vector<string> results;

	cout << "Enter the string: ";
	cin >> str;
	cout << "Enter the delimiter: ";
	cin >> delimiter;
	
	results = split(str, delimiter);
	cout << "\n---------results-----------" << endl;

	for (string s : results)
		cout << s << "\n";

	return 0;
}


#include <iostream>
#include <string>

using namespace std;

string convert(int n, int k)
{
	string result = "";

	if (n == 0)
		return "0";

	string str = "0123456789ABCDEF";

	while (n > 0)
	{
		int remainder = n % k;
		result = str[remainder] + result;
		n /= k;
	}
	return result;
}

int main()
{
	int n, k;

	cout << "Enter the number: ";
	cin >> n;
	cout << "Enter the base to convert to: ";
	cin >> k;
	cout << n << " in base-" << k << " is " << convert(n, k) << endl;

	return 0;
}


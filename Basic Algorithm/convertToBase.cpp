#include <iostream>
#include <string>

using namespace std;

string convertToBase(int n, int k)
{
	string result = "";
	
	if (n == 0)
		return "0";

	string digits = "0123456789ABCDEF";

	while (n > 0)
	{
		int remainder = n % k;
		result = digits[remainder] + result;
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
	cout << n << " in base-" << k << " is " << convertToBase(n, k) << endl;

	return 0;
}


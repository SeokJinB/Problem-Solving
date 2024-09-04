#include <iostream>

using namespace std;

bool isPrime(long long n)
{
	if (n == 1)
		return false;
	for (long long i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
			return false;
	}

	return true;
}

int main()
{
	long long n;

	cout << "Enter the number : ";
	cin >> n;

	if (isPrime(n))
		cout << n << " is prime number." << endl;
	else
		cout << n << " is not prime number." << endl;

	return 0;
}


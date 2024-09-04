//#include <string>
//#include <vector>
//#include <set>
//#include <iostream>
//#include <random>
//#include <time.h>
//
//using namespace std;
//
//void lottery2(int n)
//{
//    for (int i = 0; i < n; i++)
//    {
//        random_device rd;
//        mt19937 gen(rd());
//        uniform_int_distribution<int> dis(0, 9);
//
//        for (int j = 0; j < 6; j++)
//        {
//            cout << dis(gen) << " ";
//        }
//        cout << endl;
//    }
//}
//
//void lottery1(int n)
//{
//    for (int i = 0; i < n; i++)
//    {
//        set<int> set;
//        random_device rd;
//        mt19937 gen(rd());
//        uniform_int_distribution<int> dis(1, 45);
//
//        while (set.size() != 6)
//        {
//            set.insert(dis(gen));
//        }
//
//        cout << i + 1 << "번째 : ";
//        for (int n : set)
//            cout << n << "\t";
//        cout << endl << endl;
//    }
//}
//
//int main(void)
//{
//    int n, select;
//
//    cout << "1번 : 로또\n2번 : 연금복권" << endl << endl;
//    cout << "복권 종류를 선택하세요 : ";
//    cin >> select;
//
//    if (select == 1)
//    {
//        cout << "로또 구매 개수를 입력하세요 : ";
//        cin >> n;
//        cout << "\n번호" << endl << endl;
//        lottery1(n);
//    }
//    else if (select == 2)
//    {
//        cout << "연금복권 구매 개수를 입력하세요 : ";
//        cin >> n;
//        cout << "\n번호" << endl << endl;
//        lottery2(n);
//    }
//}

#include <iostream>
#include <vector>
#include <string>

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
}
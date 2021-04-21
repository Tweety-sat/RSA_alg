#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <climits> 
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;

//Выбирает все простые числа до заданного
int simple_num(int n)
{
	int* a = new int[n], i, j, k;
	memset(a, 0, sizeof(int) * n);
	for (i = 1; 3 * i + 1 < n; i++)
	{
		for (j = 1; (k = i + j + 2 * i * j) < n && j <= i; j++)
			a[k] = 1;
	}
	for (i = n - 1; i >= 1; i--)
		if (a[i] == 0)
		{
			return (2 * i + 1);
			break;
		}
	delete[] a;
}

//Алгоритм Евклида.
int gcd(int a, int b)
{
	int c;
	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}
namespace classs = boost::multiprecision;

int main()
{
	cout << "Keys:" << endl;

	// Генерация двух чисел и выбор двух простых чисел.

	srand((unsigned)time(NULL));

	int p_temp = rand() % 100+1;
	int q_temp = rand() % 100+1;

	int p = simple_num(p_temp);
	int q = simple_num(q_temp);

	unsigned int n = p * q;

	//Генерация числа d 
	int d_temp, d = 0;
	while (d != 1)
	{
		d_temp = rand() % 1000;
		d = gcd(d_temp, ((p - 1) * (q - 1)));
	}
	
	unsigned int e_temp = 0, e = 0;
	while (e != 1)
	{
		e_temp += 1;
		e = (e_temp * d_temp) % ((p - 1) * (q - 1));
	}

	//Сгенерированные ключи.
	cout << "Open key: " << '{' << e_temp << ',' << n << '}'<< endl;
	cout <<  "Private key: " << '{' << d_temp << ',' << n << '}' << endl << endl;

	//Ввод шифруемых данных.

	cout << "Please enter msg: ";
	int max = 1000;
	char* Text = new char[max];
	string input = "";
	getline(cin, input);
	int size = input.length();

	for (int i = 0; i < max; i++)
	{
		if (i >= size)
			Text[i] = '=';
		else Text[i] = input[i];
	}
	//Массив для хранения шифротекста.
	unsigned int* CryptoText = new unsigned int[max];
	unsigned int* DecryptText = new unsigned int[max];



	int b = 301;
	//Получение из введённых данных десятичного кода ASCII и его преобразование по формуле Ci = (mj^e)mod n.
	for (int j = 0; j < max; j++)
	{
		int c = 1;
		unsigned int i = 0;
		int ASС = (static_cast<int>(Text[j])) + b;
		while (i < e_temp)
		{
			c = c * ASС;
			c = c % n;
			i++;
		}
		CryptoText[j] = c;
		b += 1;
	}


	//classs::cpp_int chislo = classs::pow(classs::cpp_int(82), 364);

	//Расшифровка полученного кода по формуле mi = (ci^d)%n
	b = 301;
	for (int j = 0; j < max; j++)
	{
		int m = 1;
		unsigned int i = 0;
		while (i < d_temp)
		{
			m = m * CryptoText[j];
			m = m % n;
			i++;
		}
		m = m - b;
		DecryptText[j] = m;
		b += 1;
	}

	
	cout << "CryptoText: ";
	for (int j = 0; j < size; j++)
	{
		cout << CryptoText[j];
	}
	cout << "\nDecryptText: ";

	for (int j = 0; j < size; j++)
	{
		cout << static_cast<char>(DecryptText[j]);		
	}
	cout << endl;

	delete[] Text;
	delete[] CryptoText;
	delete[] DecryptText;
	return 0;
}

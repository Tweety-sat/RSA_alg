#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <climits> 
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;

//Выбирает все простые числа до заданного
int sundaram(int n)
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

	int p = sundaram(p_temp);
	int q = sundaram(q_temp);

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
	cout << '{' << e_temp << ',' << n << '}' << " - Open key" << endl;
	cout << '{' << d_temp << ',' << n << '}' << " - Secret key" << endl << endl;

	//Ввод шифруемых данных.

	cout << "Please enter msg: ";
	int MAX = 1000;
	char* Text = new char[MAX];
	string input = "";
	getline(cin, input);
	int size = input.length();

	for (int i = 0; i < MAX; i++)
	{
		if (i >= size)
			Text[i] = '=';
		else Text[i] = input[i];
	}
	//Массив для хранения шифротекста.
	unsigned int* CryptoText = new unsigned int[MAX];
	unsigned int* DecryptText = new unsigned int[MAX];



	int b = 301;
	int c;
	
	//Получение из введённых данных десятичного кода ASCII и его преобразование по формуле Ci = (mj^e)mod n.
	for (int j = 0; j < MAX; j++)
	{
		c = 1;
		unsigned int i = 0;
		int ASCIIcode = (static_cast<int>(Text[j])) + b;
		while (i < e_temp)
		{
			c = c * ASCIIcode;
			c = c % n;
			i++;
		}
		CryptoText[j] = c;
		b += 1;
	}


	classs::cpp_int chislo = classs::pow(classs::cpp_int(82), 364);

	//Расшифровка полученного кода по формуле mi = (ci^d)%n и перевод его в десятичный код ASCII.
	b = 301;
	int m;
	for (int j = 0; j < MAX; j++)
	{
		m = 1;
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
	cout << endl;
	cout << "DecryptText: ";

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

#include <iostream>
#include "JEDNOMIAN.h"

using namespace std;

int main()
{
	Wielomian w1("-10x^10-x^6+2x^2+1");
	Wielomian w2("2x+1");
	Wielomian dzielnik("x^5+1");
	double c = 3;
	//cin >> w1;
	cout << "Pierwszy wielomian: " << w1 << endl;
	cout << "Drugi wielomian: " << w2 << endl;
	cout << "Dzielnik: " << dzielnik << endl;
	Wielomian w3 = w1 + w2;
	cout << "Suma: " << w3 << endl;

	Wielomian w4 = w1 - w2;
	cout << "Roznica: " << w4 << endl;

	Wielomian w5 = w1 * w2;
	cout << "Iloczyn: " << w5 << endl;

	Wielomian w10 = w1 / dzielnik;
	cout << "Iloraz: " << w10 << endl;

	Wielomian w6 = w2 + c;
	cout << "Wielomian + stala: " << w6 << endl;

	Wielomian w7 = w2 - c;
	cout << "Wielomian - stala: " << w7 << endl;

	Wielomian w8 = w2 / c;
	cout << "Wielomian / stala: " << w8 << endl;

	Wielomian w9 = w2 * c;
	cout << "Wielomian * stala: " << w9 << endl;

	Wielomian w11 = w2.Pochodna(1);
	cout << "Pochodna wielomianu " << w11 << endl;

	double y = w2[0];
	cout << "Wspolczynnik przy danej potedze: " << y << endl;

	double z = w2(-3);
	cout << "Wartosc wielomianu w punkcie: " << z << endl;

	system("PAUSE");
	return 0;
}
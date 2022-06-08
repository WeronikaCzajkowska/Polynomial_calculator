#include <cstdio>
#include <iostream>
#include <cstring>
#include "JEDNOMIAN.h"

using namespace std;

Wielomian::Wielomian()
{
	st = 0;
	wsp = new double[1];
	*wsp = 0;
}

Wielomian::~Wielomian()
{
	delete[]wsp;
}

Wielomian::Wielomian(const Wielomian& w)
{
	this->st = w.st;
	this->wsp = new double[st + 1];
	for (int i = 0; i <= w.st; i++)
		this->wsp[i] = w.wsp[i];
}

Wielomian::Wielomian(int st, double* wsp)
{
	this->st = st;
	this->wsp = new double[st + 1];
	//for (int i = 0; i <= st; i++)
	this->wsp = wsp;
	//*(this->wsp + i) = *(wsp + i);
}

Jednomian::Jednomian(int stopien, double wspolczynnik)
{
	st = stopien;
	wsp = new double[st+1];
	wsp[st] = wspolczynnik;
	for (int i = 0; i < st; i++)
		wsp[i] = 0;
}

Jednomian::~Jednomian()
{
	delete[]wsp;
}


//
// Kolejność działań:
// 0. oczyszczenie z odstępów
// 1. określamy stopień wielomianu
// 2. alokacja pamięci, zerowanie, ustawienie stopnia
// 3. analiza jednomianówd
//
Wielomian::Wielomian(const char* napis)/*analizuj przerobiona na konstruktor*/
{
	char* kopia = oczyszczenie_z_odstepow(napis);
	napis = kopia;
	alokacja_wielomianu(stopien_wielomianu(napis));
	while (*napis != 0)
		napis = analiza_jednomianu(napis);
	delete[] kopia;
}


//=====================vv==Operatory==vv=========================

Wielomian& Wielomian::operator=(const Wielomian& w)
{
	int i;
	if (st != w.st)
	{
		st = w.st;
		wsp = new double[st + 1];
	}
	for (i = 0; i <= st; i++)
	{
		wsp[i] = w.wsp[i];
	}
	return *this;
}

ostream& operator<<(ostream& ostrm, Wielomian& w)
{
	for (int i = 0; i <= w.st; i++)
	{
		if (w.wsp[i] >= 0)
		{
			ostrm << "+";
		}
		ostrm << w.wsp[i];
		if (i >= 1)
		{
			ostrm << "x^" << i;
		}
	}
	return ostrm;

}

istream& operator>>(istream& istrm, Wielomian& w)
{
	cout << "Wprowadz stopien:  " << endl;
	istrm >> w.st;
	int i = 0;
	for (i = 0; i <= w.st; i++)
	{
		cout << "Wprowadz wspolczynnik: " << endl;
		istrm >> w.wsp[i];
	}
	return istrm;
}

Wielomian operator*(double c, const Wielomian& w)
{
	Wielomian ww(w);
	ww *= c;
	return ww;
}

Wielomian operator*(const Wielomian& w, double c)
{
	Wielomian ww(w);
	ww *= c;
	return ww;
}

Wielomian& Wielomian::operator*=(double c)
{
	for (double* w = wsp + st + 1; w-- > wsp;)
	{
		*w *= c;
	}
	return *this;
}

Wielomian operator*(const Wielomian& w1, const Wielomian& w2)
{
	Wielomian ww;
	delete[]ww.wsp;
	ww.st = w1.st + w2.st;
	ww.wsp = new double[ww.st + 1];
	for (int i = 0; i <= ww.st; i++)
	{
		ww.wsp[i] = 0;
	}

	for (int i = 0; i <= w1.st; i++)
	{
		for (int j = 0; j <= w2.st; j++)
		{
			ww.wsp[i + j] += w1.wsp[i] * w2.wsp[j];
		}
	}
	return ww;
}

Wielomian& Wielomian::operator*=(const Wielomian& w)
{
	return *this = *this * w;
}

double Wielomian::operator()(double x)
{
	int i = st;
	double ww = wsp[i];
	for (i; i > 0;)
	{
		ww = ww * x + wsp[--i];
	}
	return ww;
}

double Wielomian::operator[](const int x)
{
	if (x >= 0 && x <= st)
	{
		return wsp[x];
	}
	else return 0;
}

Wielomian& Wielomian::operator+=(double c)
{
	return *this = *this + c;
}

Wielomian operator+(const Wielomian& w1, const Wielomian& w2)
{
	const Wielomian& min = w1.st < w2.st ? w1 : w2;

	Wielomian ww = w1.st < w2.st ? w2 : w1;
	for (int i = 0; i <= min.st; i++)
	{
		ww.wsp[i] += min.wsp[i];
	}
	return ww;
}

Wielomian operator+(const Wielomian& w, double c)
{
	Wielomian ww(w);
	ww.wsp[0] += c;
	return ww;
}

Wielomian operator+(double c, const Wielomian& w)
{
	Wielomian ww(w);
	ww.wsp[0] += c;
	return ww;
}

Wielomian& Wielomian::operator+=(const Wielomian& w)
{
	return *this = *this + w;
}

Wielomian& Wielomian::operator-=(const Wielomian& w)
{
	return *this = *this - w;
}

Wielomian& Wielomian::operator-=(double c)
{
	return *this = *this - c;
}

Wielomian operator-(const Wielomian& w1, const Wielomian& w2)
{
	const Wielomian& min = w1.st < w2.st ? w1 : w2;

	Wielomian ww = w1.st < w2.st ? w2 : w1;
	for (int i = 0; i <= min.st; i++)
	{
		ww.wsp[i] -= min.wsp[i];
	}

	return ww;
}

Wielomian operator-(const Wielomian& w, double c)
{
	Wielomian ww(w);
	ww.wsp[0] -= c;
	return ww;
}

Wielomian operator-(double c, const Wielomian& w)
{
	Wielomian ww(w);
	ww.wsp[0] -= c;
	return ww;
}

Wielomian& Wielomian::operator/=(double c)
{
	for (double* w = wsp + st + 1; w-- > wsp;)
		*w = *w / c;
	return *this;
}

Wielomian operator/(const Wielomian& w, double c)
{
	Wielomian ww(w);
	ww /= c;
	return ww;
}
Wielomian& Wielomian::operator/=(const Wielomian& w1)
{
	st = st - w1.st;
	wsp = new double[st + 1];
	Wielomian reszta(*this), w(w1);
	Jednomian jednomian(2, 3);

	for (int k = st; k >= 0; k--)
	{
		wsp[k] = reszta.wsp[reszta.st] / w1.wsp[w1.st];
		int r = reszta.st - w.st;
		w *= wsp[k];
		for (int j = 0; j < r; j++)
		{
			w *= jednomian;
		}
		reszta = reszta - w;
		reszta.st--;
		wsp[r] = wsp[k];
	}
	return *this;
}

Wielomian operator/(const Wielomian& w1, const Wielomian& w2)
{
	Wielomian ww(w1);
	return ww /= w2;
}

Wielomian Wielomian::Pochodna(int ktora)
{
	if (ktora == 1)
	{

		Wielomian w;
		if (this->st > 0)
		{
			w.st = this->st - 1;
			w.wsp = new double[w.st + 1];

			for (int i = 0; i < st; i++)
			{
				w.wsp[i] = wsp[i + 1] * (i + 1);
			}
		}
		return w;
	}
	else return Pochodna().Pochodna(ktora - 1);
}
//====================================================================

char* Wielomian::oczyszczenie_z_odstepow(const char* napis)
{
	int i = 0; int j = 0;
	char* kopia = new char[strlen(napis) + 1];
	while (napis[i])
	{
		if (napis[i] != ' ')
		{
			kopia[j] = napis[i];
			j++;
		}
		i++;
	}
	kopia[j] = 0;
	return kopia;
}

int Wielomian::stopien_wielomianu(const char* napis)
{
	int i = 0;
	int st = 0; //tymczasowy holder stopnia wielomianu
	while (napis[i])
	{
		if (napis[i] == 'x')
		{
			int bufor;
			if (napis[i + 1] == '^')
			{
				char* endptr;
				bufor = strtol(&napis[i + 2], &endptr, 10);
			}
			else bufor = 1;
			if (bufor > st)st = bufor;
		}
		i++;
	}
	return st;
}

const char* Wielomian::analiza_jednomianu(const char* napis)
{
	//2.5x^3
	//-2.5x^2		+x
	double wspolczynnik = 1;
	int wykladnik = 0;
	char* endptr;
	int znak = 1;
	if (*napis == '-' || *napis == '+')
	{
		if (*napis == '-') znak = -1;
		napis++;
	}
	if (*napis != 'x')
	{
		char* endptr;
		wspolczynnik = strtod(napis, &endptr);
		napis = endptr;
	}
	if (*napis == 'x')
	{
		napis++;
		if (*napis == '^')
		{
			napis++;
			wykladnik = strtol(napis, &endptr, 10);
			napis = endptr;
		}
		else wykladnik = 1;
	}
	this->wsp[wykladnik] += znak * wspolczynnik;
	return napis;
}

void Wielomian::alokacja_wielomianu(int Stopien)
{
	int i;
	this->st = Stopien;
	//w->wsp = (double*)malloc(sizeof(double) * (Stopien + 1));
	this->wsp = new double[Stopien + 1];
	for (i = 0; i <= Stopien; i++)
		this->wsp[i] = 0;
}
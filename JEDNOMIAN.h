#ifndef JEDNOMIAN_H
#define JEDNOMIAN_H
#include <iostream>

using namespace std;

class Wielomian
{
protected:
	double* wsp;
	int st;
	int stopien_wielomianu(const char*);
	const char* analiza_jednomianu(const char* napis);

public:
	void alokacja_wielomianu(int Stopien);
	int zwrocStopien()const { return this->st; };
	double zwrocWspolczynnik() { return *wsp; };
	char* oczyszczenie_z_odstepow(const char* napis);
	Wielomian Pochodna(int ktora = 1);

	Wielomian();//Konstruktor
	Wielomian(const char* napis);//Konstruktor
	Wielomian(const Wielomian& w);//Konstruktor kopiujacy
	Wielomian(int st, double* wsp);//Konstruktor
	~Wielomian();//Destruktor

	Wielomian& operator=(const Wielomian& w);
	double operator[](int x);
	Wielomian& operator*=(const Wielomian& w);
	Wielomian& operator *= (double c);
	friend ostream& operator<<(ostream& o, Wielomian& w);
	friend istream& operator >>(istream& in, Wielomian& w);
	Wielomian& operator+=(double c);
	Wielomian& operator+=(const Wielomian& w);
	Wielomian& operator-=(const Wielomian& w);
	Wielomian& operator-=(double c);
	Wielomian& operator/=(double c);
	Wielomian& operator/=(const Wielomian& w);
	double operator()(double x);
	//friend void drukuj_wielomian(Wielomian w);
	friend Wielomian operator*(const Wielomian& w1, const Wielomian& w2);
	friend Wielomian operator/(const Wielomian& w1, const Wielomian& w2);
	friend Wielomian operator+(const Wielomian& w1, const Wielomian& w2);
	friend Wielomian operator+(const Wielomian& w, double c);
	friend Wielomian operator+(double c, const Wielomian& w);

	friend Wielomian operator-(const Wielomian& w1, const Wielomian& w2);
	friend Wielomian operator-(const Wielomian& w, double c);
	friend Wielomian operator-(double c, const Wielomian& w);

};

Wielomian operator*(const Wielomian& w, double c);
Wielomian operator*(double c, const Wielomian& w);
Wielomian operator/(const Wielomian& w, double c);

class Jednomian :public Wielomian
{

public:
	Jednomian() {};
	Jednomian(int stopien, double wspolczynnik);
	~Jednomian();
};

#endif

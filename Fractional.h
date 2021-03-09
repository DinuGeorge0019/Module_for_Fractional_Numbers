#pragma once

#include <iostream>
#include <vector>
using namespace std;

class Fractional
{
private:
	long long numerator;
	int denominator;
public:

	Fractional(long long numerator, long long dominator);
	Fractional(long long number);
	Fractional();
	Fractional& operator! ();
	Fractional& operator = (const Fractional& other);
	friend Fractional operator + (const Fractional& f1, const Fractional& f2);
	friend Fractional operator - (const Fractional& f1, const Fractional& f2);
	friend Fractional operator* (const Fractional& f1, const Fractional& f2);
	friend Fractional operator/ (const Fractional& f1, const Fractional& f2);
	friend bool operator == (const  Fractional& f1, const  Fractional& f2);
	Fractional operator ^ (const int& power);
	friend bool operator < (const  Fractional& f1, const  Fractional& f2);
	friend bool operator > (const  Fractional& f1, const  Fractional& f2);
	friend bool operator <= (const  Fractional& f1, const  Fractional& f2);
	friend bool operator >= (const  Fractional& f1, const  Fractional& f2);

	Fractional get_abs();



	friend ostream& operator<<(ostream& os, const Fractional& c);

	friend istream& operator>>(istream& is, Fractional& c);
};
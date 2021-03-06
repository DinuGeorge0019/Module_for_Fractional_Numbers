#include "fractional.h"


Fractional::Fractional(long long numerator, long long dominator)
{
	this->numerator = numerator;
	this->denominator = dominator;
}

Fractional::Fractional(long long number)
{
	this->numerator = number;
	this->denominator = 1;
}

Fractional::Fractional()
{
	this->numerator = 0;
	this->denominator = 1;
}

Fractional& Fractional::operator = (const Fractional& other)
{
	if (this == &other)
		return *this;

	this->numerator = other.numerator;
	this->denominator = other.denominator;
	return *this;
}

Fractional operator* (const Fractional& f1, const Fractional& f2)
{
	Fractional result;
	result.numerator = f1.numerator * f2.numerator;
	result.denominator = f1.denominator * f2.denominator;
	!result;
	return result;
}


Fractional operator/ (const Fractional& f1, const Fractional& f2)
{
	Fractional result;
	result.numerator = f1.numerator * f2.denominator;
	result.denominator = f1.denominator * f2.numerator;
	!result;
	return result;
}

long long gcd(long long a, long long b)
{
	if (b == 0) return a;
	a %= b;
	return gcd(b, a);
}

Fractional& Fractional::operator! ()
{
	long long GCD = gcd(numerator, denominator);

	numerator = numerator / GCD;
	denominator = denominator / GCD;

	if (denominator < 0)
	{
		denominator = (-1) * denominator;
		numerator = (-1) * numerator;
	}

	return *this;
}

Fractional operator + (const Fractional& f1, const Fractional& f2)
{
	Fractional result;

	if (f1.denominator == f2.denominator)
	{
		result.numerator = f1.numerator + f2.numerator;
		result.denominator = f1.denominator;
		!result;
		return result;
	}
	else
	{
		Fractional  f1_copy = f1;
		Fractional  f2_copy = f2;
		!f1_copy;
		!f2_copy;
		if (f1_copy.denominator == f2_copy.denominator)
		{
			return f1_copy + f2_copy;
		}
		result.numerator = f1.numerator * f2.denominator + f1.denominator * f2.numerator;
		result.denominator = f1.denominator * f2.denominator;
	}

	!result;
	return result;

}

Fractional operator - (const Fractional& f1, const Fractional& f2)
{

	Fractional result;

	if (f1.denominator == f2.denominator)
	{
		result.numerator = f1.numerator - f2.numerator;
		result.denominator = f1.denominator;
		!result;
		return result;
	}
	else
	{
		Fractional  f1_copy = f1;
		Fractional  f2_copy = f2;
		!f1_copy;
		!f2_copy;
		if (f1_copy.denominator == f2_copy.denominator)
		{
			return f1_copy - f2_copy;
		}
		result.numerator = f1.numerator * f2.denominator - f1.denominator * f2.numerator;
		result.denominator = f1.denominator * f2.denominator;
	}

	!result;
	return result;

}

Fractional Fractional::operator ^ (const int& power)
{
	if (power == 0)
	{
		return { 1, 1 };
	}

	if (power <= -1)
	{
		Fractional inversed(1);
		inversed = 1 / (*this);
		return inversed ^ (-power);
	}

	Fractional result = *this;
	for (int i = 1; i < power; i++)
	{
		result = result * (*this);
	}

	return result;

}

ostream& operator<<(ostream& os, const Fractional& c)
{

	if (c.numerator == 0)
	{
		os << "0";
		return os;
	}

	if (c.denominator == 1)
	{
		os << c.numerator;
		return os;
	}

	if (c.denominator == c.numerator)
	{
		os << "1";
		return os;
	}

	os << c.numerator << "/" << c.denominator;

	return os;

}

istream& operator>>(istream& is, Fractional& c)
{
	is >> c.numerator;
	is >> c.denominator;
	return is;

}

bool operator == (const  Fractional& f1, const  Fractional& f2)
{
	Fractional copy_f1 = f1;
	Fractional copy_f2 = f2;
	!copy_f1;
	!copy_f2;

	if (copy_f1.numerator == copy_f2.numerator && copy_f1.denominator == copy_f2.denominator)
		return true;

	return false;
}

bool operator < (const  Fractional& f1, const  Fractional& f2)
{
	Fractional copy_f1 = f1;
	Fractional copy_f2 = f2;
	!copy_f1;
	!copy_f2;

	if (copy_f1.denominator == copy_f2.denominator)
	{
		return copy_f1.numerator < copy_f2.numerator;
	}
	else
	{
		copy_f1.numerator = copy_f1.numerator * copy_f2.denominator;
		copy_f2.numerator = copy_f2.numerator * copy_f1.denominator;

		return copy_f1.numerator < copy_f2.numerator;
	}
}



bool operator > (const  Fractional& f1, const  Fractional& f2)
{
	return !(f1 < f2);
}


bool operator <= (const  Fractional& f1, const  Fractional& f2)
{

	if (f1 == f2 || f1 < f2)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool operator >= (const  Fractional& f1, const  Fractional& f2)
{
	if (f1 == f2 || f1 > f2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

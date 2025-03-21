#include "Fraction.h"
#include <iostream>

Fraction::Fraction(int a, int b) : m_numerator(a)
{
	if (b != 0)
	{
		is_valid = true;
		m_denominator = b;
	}
	else
	{
		std::cout << "denominator must be non-zero\n";
		is_valid = false;
	}
}

Fraction Fraction::operator+(const Fraction& other)
{
	Fraction result(1, 1);

	result.m_numerator = m_numerator * other.m_denominator + other.m_numerator * m_denominator;
	result.m_denominator = m_denominator * other.m_denominator;

	result.Simplify();

	return result;
}

Fraction Fraction::operator-(Fraction& other)
{
	return (*this) + other * (-1);
}

Fraction Fraction::operator*(const Fraction& other)
{
	Fraction result(1, 1);
	result.m_numerator = m_numerator * other.m_numerator;
	result.m_denominator = m_denominator * other.m_denominator;

	result.Simplify();

	return result;
}

Fraction Fraction::operator*(int other)
{
	Fraction temp(other, 1);
	return (*this) * temp;
}

void Fraction::Simplify()
{
	int gcd_ = 1;
	if (m_numerator != 1 && m_denominator != 1)
		gcd_ = GCD(m_numerator, m_denominator);

	if (gcd_ != 1)
	{
		m_numerator /= gcd_;
		m_denominator /= gcd_;
	}
}

int Fraction::GCD(int a, int b)
{
	while (b != 0)
	{
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

Fraction operator*(int mult, const Fraction& other)
{
	return  mult*other;
}

std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
{
	out << fraction.m_numerator << " / " << fraction.m_denominator << '\n';
	return out;
}
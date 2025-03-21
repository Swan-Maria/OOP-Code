#pragma once
#include <ostream>

class Fraction
{
private:
	int GCD(int a, int b);
	int m_numerator;
	int m_denominator;
	bool is_valid;
public:
	Fraction(int a, int b);

	Fraction operator+(const Fraction&);
	Fraction operator-(Fraction&);

	Fraction operator*(const Fraction&);
	Fraction operator*(int);

	friend Fraction operator*(int, const Fraction&);
	friend std::ostream& operator<<(std::ostream&, const Fraction&);

	void Simplify();
};

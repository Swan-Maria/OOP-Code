#pragma once

class Complex
{
private:
	double m_Re;
	double m_Im;
	double m_abs;
	double m_phi;
public:
	Complex();
	Complex(double Re, double Im);

	double Abs()const;

	Complex operator-() const;

	Complex operator+(const Complex&) const;
	Complex operator-(const Complex&) const;

	Complex operator*(const Complex&) const;
	Complex operator*(const double&) const;

	Complex operator/(const Complex&);

	void TrigonometricForm();

};


#include "Complex.h"
#include <iostream>
#include <math.h>

Complex::Complex(double Re, double Im) : m_Re(Re), m_Im(Im)
{
	m_abs = sqrt(m_Re * m_Re + m_Im * m_Im);
	m_phi = atan2(m_Im, m_Re);
}

double Complex::Abs() const {return m_abs;}

Complex::Complex() : Complex(0, 0) {}

Complex Complex::operator-() const
{
	return (*this)*(-1);
}

Complex Complex::operator+(const Complex& other) const
{
	return Complex(m_Re + other.m_Re, m_Im + other.m_Im);
}

Complex Complex::operator-(const Complex& other) const
{
	return Complex(m_Re - other.m_Re, m_Im - other.m_Im);
}

Complex Complex::operator*(const Complex& other) const
{
	return Complex((m_Re * other.m_Re - m_Im * other.m_Im), (m_Re * other.m_Im + other.m_Re * m_Im));
}

Complex Complex::operator*(const double& x) const
{
	return Complex(m_Re * x, m_Im * x);
}

Complex Complex::operator/(const Complex& other)
{
	if (other.m_Re == 0 && other.m_Im == 0)
	{
		std::cout << "Division by zero\n";
		return Complex();
	}
	else
	{
		double abs = other.m_Re * other.m_Re + other.m_Im * other.m_Im;
		double Re = (m_Re * other.m_Re + m_Im * other.m_Im) / abs;
		double Im = (m_Im * other.m_Re - m_Re * other.m_Im) / abs;
		return Complex(Re, Im);
	}
}

void Complex::TrigonometricForm()
{
	const double PI = 3.14159;
	double phi = m_phi * 180 / PI;
	std::cout << m_abs << "*(cos(" << phi << ") + i*sin(" << phi<< "))" << std::endl;
}
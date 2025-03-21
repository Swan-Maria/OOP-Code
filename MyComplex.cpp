include <iostream>
#include "Complex.h"

class Complex 
{
private:
	double m_Re;
	double m_Im;
public:
	Complex():m_Re(0), m_Im(0) {}
	Complex (double Re, double Im) :m_Re(Re), m_Im(Im) {}
	//----------------------------------------------------------
	Complex(const Complex& other) : m_Re(other.m_Re), m_Im(other.m_Im) {}
	Complex& operator=(const Complex& other) 
	{
		if (this != &other) {
			m_Re = other.m_Re;
			m_Im = other.m_Im;
		}
		return *this;
	}
	//----------------------------------------------------------
	Complex(Complex&& other) noexcept 
		: m_Re(other.m_Re), m_Im(other.m_Im) 
	{
		other.m_Re = 0;
		other.m_Im = 0;
	}
	Complex& operator=(Complex&& other) noexcept 
	{
		if (this != &other) {
			m_Re = other.m_Re;
			m_Im = other.m_Im;
			other.m_Re = 0;
			other.m_Im = 0;
		}
		return *this;
	}
	//----------------------------------------------------------
	void Print(const std::string string="") const
	{
		std::cout << string << m_Re << " + " << m_Im << "i\n";
	}
	//----------------------------------------------------------
	Complex operator+(const Complex& y) const
	{
		Complex z;
		z.m_Re = m_Re + y.m_Re;
		z.m_Im = m_Im + y.m_Im;
		return z;
	}

	Complex operator+(const double& x) const
	{
		Complex z;
		z.m_Re = m_Re +x;
		z.m_Im = m_Im;
		return z;
	}

	Complex operator*(const Complex& y) const
	{
		Complex z;
		z.m_Re = m_Re *y.m_Re - m_Im *y.m_Im;
		z.m_Im = m_Re *y.m_Im + y.m_Re * m_Im;
		return z;
	}

	Complex operator*(const double& x) const
	{
		Complex z;
		z.m_Re = m_Re * x;
		z.m_Im = m_Im * x;
		return z;
	}
};

int main() {
	Complex a (1.5, 1.2);
	Complex b (-4.2, 3.7);
	Complex c;
	double x = 1.5;
	//Add objects:
	c = a + b;
	c.Print("c = ");

	//Add number and object:
	c = c+x;
	c.Print("c = ");


	Complex d;
	//Multiply objects:
	d = a * b;
	d.Print("d = ");

	//Multiply number and object:
	d = d * x;
	d.Print("d = ");

	Complex copy_a = a;
	c.Print("copy_a = ");

	Complex moved_b = std::move(b);
	c.Print("moved_b = ");

	return 0;
}
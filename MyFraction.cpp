#include <iostream>
#include <cassert> 

class Fraction
{
private:
	int m_numerator;
	int m_denominator;

	int Gcd(int a, int b) {
		return (b == 0 ? abs(a) : Gcd(b, a % b));
	}

	void Simplify() {
		int g = Gcd(m_numerator, m_denominator);
		m_numerator /= g;
		m_denominator /= g;
		if (m_denominator < 0) {
			m_numerator *=-1 ;
			m_denominator *= -1;
		}
	}

public:
	Fraction() : m_numerator(1), m_denominator(1) {}

	Fraction(int numerator, int denominator) 
		:m_numerator(numerator), m_denominator(denominator) 
	{
		//assert(m_denominator==0 && "Denominator can not be zero!");
        if (denominator == 0) {
            std::cerr << "Error: Denominator cannot be zero!" << std::endl;
            exit(EXIT_FAILURE);
        }
        Simplify();
	}

    //-----------------------------------------------------------------------------------------

    Fraction(const Fraction& other)
		: m_numerator(other.m_numerator), m_denominator(other.m_denominator) 
	{}

    Fraction& operator=(const Fraction& other) {
        if (this != &other) {
            m_numerator = other.m_numerator;
            m_denominator = other.m_denominator;
        }
        return *this;
    }
    //-----------------------------------------------------------------------------------------
    
    Fraction(Fraction&& other) noexcept 
        : m_numerator(other.m_numerator), m_denominator(other.m_denominator) 
    {
        other.m_numerator = 0;
        other.m_denominator = 1;
    }

    Fraction& operator=(Fraction&& other) noexcept {
        if (this != &other) 
        {
            m_numerator = other.m_numerator;
            m_denominator = other.m_denominator;
            other.m_numerator = 0;
            other.m_denominator = 1;
        }
        return *this;
    }

    //-----------------------------------------------------------------------------------------


	void Print(const std::string string="") const {
		std::cout << string << m_numerator << "/" << m_denominator << std::endl;
	}

	double DecimalFraction() const {
		return static_cast<double>(m_numerator) / m_denominator;
	}

	void MixedFraction() const {
		int wholePart = m_numerator / m_denominator;
		int remainder = m_numerator % m_denominator;
		std::cout << wholePart << " " << remainder << "/" << m_denominator << std::endl;
	}

    //----------------------------------------------------------------------------------------

    Fraction operator+(const Fraction& other) const {
        Fraction f;
        f.m_numerator = m_numerator * other.m_denominator + other.m_numerator * m_denominator;
        f.m_denominator = m_denominator * other.m_denominator;
        return f;
    }

    Fraction operator-(const Fraction& other) const {
        Fraction f;
        f.m_numerator = m_numerator * other.m_denominator - other.m_numerator * m_denominator;
        f.m_denominator = m_denominator * other.m_denominator;
        return f;
    }

    Fraction operator*(const Fraction& other) const {
        Fraction f;
        f.m_numerator = m_numerator * other.m_numerator;
        f.m_denominator = m_denominator * other.m_denominator;
        return f;
    }

    Fraction operator/(const Fraction& other) const {
        Fraction f;
        f.m_numerator = m_numerator * other.m_denominator;
        f.m_denominator = m_denominator * other.m_numerator;
        if (f.m_denominator == 0) {
            std::cerr << "Error: Denominator cannot be zero!" << std::endl;
            exit(EXIT_FAILURE);
        }
        return f;
    }

    bool operator==(const Fraction& other) const {
        return m_numerator == other.m_numerator && m_denominator == other.m_denominator;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const {
        return m_numerator * other.m_denominator < other.m_numerator * m_denominator;
    }

    bool operator>(const Fraction& other) const {
        return other < *this;
    }

    bool operator<=(const Fraction& other) const {
        return !(*this > other);
    }

    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }
};

int main()
{
    Fraction f1(3, 4);
    f1.Print("f1 = ");
    
    Fraction f2(2, 5);
    f2.Print("f2 = ");

    Fraction sum = f1 + f2;
    sum.Print("sum = f1 + f2 = ");

    Fraction diff = f1 - f2;
    diff.Print("diff = f1 - f2 = ");

    Fraction prod = f1 * f2;    
    prod.Print("prod = f1 * f2 = ");

    Fraction quot = f1 / f2;
    quot.Print("quot = f1 / f2 = ");

    std::cout << "f1 + f2 = " << sum.DecimalFraction()<<std::endl;
    std::cout << "f1 + f2 = ";
    sum.MixedFraction();

    // Copy constructor
    Fraction f3 = sum;
    f3.Print("f3 = sum = ");

    // Copy operator
    Fraction f4;
    f4 = (diff);
    f4.Print("f4 = diff = ");

    // Move constructor
    Fraction f5 = std::move(prod);
    f5.Print("f5 = prod = ");

    // Move operator
    Fraction f6;
    f6 = std::move(quot); 
    f6.Print("f6 = quot = ");

	return 0;
}
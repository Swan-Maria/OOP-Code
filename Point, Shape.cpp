#include <iostream>
#include <cmath>
#include <exception>
 
const int PI = 3.1415;

class Point 
{
private:
	double m_x, m_y;
public:
	Point(double x = 0.0, double y = 0.0) : m_x(x), m_y(y) {}

	static double distance(const Point& p1, const Point& p2) 
	{
		return std::sqrt(std::pow(p2.m_x - p1.m_x, 2) + std::pow(p2.m_y - p1.m_y, 2));
	}

	friend std::ostream& operator<<(std::ostream& out, const Point& p) 
	{
		return out << "(" << p.m_x << ", " << p.m_y << ")";
	}
};

class Shape
{
public:
	virtual void print(std::ostream& out) const = 0;

	friend std::ostream& operator<<(std::ostream& out, const Shape& shape) 
	{
		shape.print(out);
		return out;
	}

	virtual ~Shape() = default;
	
	virtual double Area() const = 0;
};

class Triangle :public Shape
{
private:
	Point m_p1, m_p2, m_p3;
public:
	Triangle(Point p1, Point p2, Point p3) : m_p1(p1), m_p2(p2), m_p3(p3) {}

	void print(std::ostream& out) const override 
	{
		out << "Triangle[" << m_p1 << ", " << m_p2 << ", " << m_p3 << "]";
	}

	double Area() const override
	{
		double a = Point::distance(m_p1, m_p2);
		double b = Point::distance(m_p2, m_p3);
		double c = Point::distance(m_p3, m_p1);
		double p = (a + b + c) / 2.0;
		double S = p * (p - a) * (p - b) * (p - c);
		if (S < 0.0)
			return 0.0;
		return std::sqrt(S);
	}
};

class Circle :public Shape
{
private:
	Point m_center;
	double m_radius;
public:
	Circle(Point center, int radius) : m_center(center)
	{
		if (radius < 0)
			throw std::invalid_argument("Radius cannot be negative");
		m_radius = radius;
	}

	void print(std::ostream& out) const override 
	{
		out << "Circle[Center: " << m_center << ", Radius " << m_radius<<"]";
	}

	double Area() const override 
	{
		return PI * m_radius * m_radius;
	}
};

int main()
{
	Triangle t(Point(0, 0), Point(3, 0), Point(3, 4));
	Circle c(Point(0, 0), 5);

	std::cout << t << "\nArea: " << t.Area() << "\n";
	std::cout << c << "\nArea: " << c.Area() << "\n";

	return 0;
}
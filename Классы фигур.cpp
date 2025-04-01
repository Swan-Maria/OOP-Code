#include <iostream>

class Shape
{
public:
	void draw () const
	{
		std::cout << "Shape draw\n";
	}
};

class Circle :public Shape
{
public:
	void draw() const
	{
		std::cout << "Circle draw\n";
	}
};

class Rectangle :public Shape
{
public:
	void draw() const
	{
		std::cout << "Rectangle draw\n";
	}
};

class Triangle :public Shape
{
public:
	void draw() const
	{
		std::cout << "Triangle draw\n";
	}
};

int main()
{
	Shape shape;
	shape.draw();
	Circle circle;
	circle.draw();
	Rectangle rectangle;
	rectangle.draw();
	Triangle triangle;
	triangle.draw();

	return 0;
}
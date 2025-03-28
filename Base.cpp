#include <iostream>

class Base {
public:
	Base() { std::cout << "Base constructor\n"; }
    void show() { std::cout << "Base show"<< '\n'; }
	~Base() { std::cout << "Base destructor\n"; }
};

class Derived : public Base 
{
public:
    Derived() {std::cout << "Derived constructor\n"; }
    void show() {std::cout << "Derived show\n";}
	~Derived() { std::cout << "Derived destructor\n"; }
};

int main()
{
    Derived derived;
    Base* ptr = &derived;
    ptr->show();

    return 0;
}
#include <iostream>
#include <utility>
using namespace std;

class A 
{
public:
	explicit A(int value) : value(value) {}

	// Delete the copy constructor
	A(const A&) = delete;

	// Delete the copy assignment operator
	A operator=(const A&) = delete;

	// Delete the move constructor
	A(A&&) = delete;

	// Delete the move assignment operator
	A operator=(A&&) = delete;
private:
	int value;
};

int main()
{
	A a1(1), a2(2), a3(3);

	// Error, the usage of the
    // copy constructor is disabled
	A a4 = a2;
	
	// Error, the usage of the copy
	// assignment operator is disabled
	a3 = a1;    

	// Error, the usage of the
	// move constructor is disabled
	A a5 = std::move(a1); 
	
	// Error, the usage of the move
	// assignment operator is disabled
	a2 = std::move(a3);  

	return 0;
}

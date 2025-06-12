// C++ program to demonstrate
// Run Time Type Identification successfully
// With virtual function

#include <iostream>
using namespace std;

class B {
    virtual void fun() {}
};

class D : public B {
};

int main()
{
    B* b = new D; // Base class pointer
    D* d = dynamic_cast<D*>(b); // Derived class pointer
    if (d != NULL)
        cout << "works";
    else
        cout << "cannot cast B* to D*";
    return 0;
}

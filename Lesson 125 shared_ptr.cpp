#include <iostream>
#include <memory>

class Person
{
private:
	int age = 0;
	char name[30] = "NoName";
public:
	Person() = default;
	Person(int age, const char* name)
		: age(age)
	{
		strcpy_s(this->name, name);
		std::cout << "Constructor called" << std::endl;
	}
	~Person()
	{
		std::cout << "Destructor called" << std::endl;
	}
	void SomeMethod()
	{
		std::cout << "SomeMethod called" << std::endl;
	}
};

void DeleterF(int* p)
{
	std::cout << "Deleter called" << std::endl;
	delete p;
}

struct DeleterC
{
	void operator()(int* p)
	{
		std::cout << "Deleter called" << std::endl;
		delete p;
	}
};

std::shared_ptr<int> CreateInteger(int value)
{
	return std::shared_ptr<int>(new int(value), DeleterF);
}

int main()
{
#pragma region Корструкторы
	{
		std::shared_ptr<int> ptr1{ nullptr };
		std::shared_ptr<int> ptr2{new int{ 10 }};
		int* p = new int{ 10 };
		std::shared_ptr<int> ptr3{ p };
		std::shared_ptr<int> ptr4{ p, DeleterF };
		std::shared_ptr<int> ptr5{ p, DeleterC() };
		std::shared_ptr<int> ptr6{ ptr5 };
		std::shared_ptr<int> ptr7{ CreateInteger(5)};
		std::shared_ptr<Person> ptr8{ new Person(20, "John") };
	}
#pragma endregion

#pragma region Масивы
	{
		std::shared_ptr<Person[]> ptr1{ new Person[10] };
	}
#pragma endregion

#pragma region Псевдоним element_type
	{
		std::shared_ptr<int> ptr1(new int(1));
		std::shared_ptr<int>::element_type variable;
	}
#pragma endregion

#pragma region Перегруженные операторы
	{
		std::shared_ptr<Person> ptr1(new Person());
		ptr1.operator bool();
		ptr1.operator*();
		ptr1.operator->();
		ptr1->SomeMethod();
		ptr1.operator= (nullptr); //nullptr, shared_ptr, l-value, r-value, deleter, auto_ptr
		std::shared_ptr<Person[]> ptr2(new Person[3]);
		ptr2.operator[](0);
		ptr2[0] = Person(10, "John");
	}
#pragma endregion

#pragma region Методы
	{
		std::shared_ptr<int> ptr1(new int(10));
		std::shared_ptr<int> ptr2(new int(20));

		std::cout << "*ptr1 = " << *ptr1 << std::endl;
		std::cout << "*ptr2 = " << *ptr2 << std::endl;
		ptr1.swap(ptr2);
		std::cout << "*ptr1 = " << *ptr1 << std::endl;
		std::cout << "*ptr2 = " << *ptr2 << std::endl;

		std::cout << "&ptr1 = " << &ptr1 << std::endl;
		std::cout << "&ptr1 = " << ptr1.get() << std::endl;

		std::shared_ptr<Person> ptr1(new Person(20, "John"));
		ptr1.reset();
		//ptr1.reset(new Person{10, "Jane"});
		ptr1.use_count();
	}
	{
		std::shared_ptr<int> ptr1(new int(10));
		std::shared_ptr<int> ptr2(ptr1);
		if (ptr1.owner_before(ptr2))
			std::cout << "Ok";
	}
#pragma endregion

#pragma region std::make_unique/std::make_shared
	{	
		std::unique_ptr<int> ptr1{ std::make_unique<int>(10) };
		std::unique_ptr<Person> ptr1_{ std::make_unique<Person>(10,"Jane") };
		std::unique_ptr<int[]> arr{std::make_unique<int[]>(10)};

		std::shared_ptr<int> ptr2(new int{ 20 });
		std::shared_ptr<Person> ptr2_{ std::make_shared<Person>(10, "Jane") };
 	}
#pragma endregion

	return 0;
}
#pragma once
#include <iostream>
#include <cstring>

template <class T>
class BasicString
{
public:
	// constructors
	BasicString() : data(new T[1]{ '\0' }), len(0), cap(1) {}
	
	BasicString(const T* str) : len (std::strlen(str))
	{
		cap = len + 1;
		data = new T[cap];
		std::memcpy(data, str, len+1);
	}

	BasicString(const BasicString& oth) //copy constructor
		: len(oth.len), cap(oth.cap) 
	{
		data=new T[cap];
		std::memcpy(data, oth.data, len + 1);
	}
	
	BasicString(BasicString&& oth) noexcept //move constructor
		: data(oth.data), len(oth.len), cap(oth.cap)
	{
		oth.data = nullptr;
		oth.len = 0;
		oth.cap = 0;
	}

	// destructor
	~BasicString()
	{
		delete[] data;
		data = nullptr;
	}

	// reloading operator =
	BasicString& operator=(const BasicString& oth) //copy
	{
		if (this != &oth)
		{
			delete[] data;
			len = oth.len;
			cap = oth.cap;
			data = new T[cap];
			std::memcpy(data, oth.data, len + 1);
		}
		return *this;
	}
	
	BasicString& operator=(BasicString&& oth) noexcept // move
	{
		if (this != &oth)
		{
			delete[] data;
			data = oth.data;
			len = oth.len;
			cap = oth.cap;
			oth.data = nullptr;
			oth.len = 0;
			oth.cap = 0;
		}
		return *this;
	}

	// reloading operator []
	T& operator[](size_t index) {return data[index];}
	const T& operator[](size_t index) const {return data[index];}

	// methods
	bool empty() const { return len == 0; }
	
	size_t size() const { return len; }
	
	size_t capacity() const { return cap; }
	
	void append(const T* str)
	{
		size_t addLen = std::strlen(str);
		size_t newLen = len + addLen;
		if (newLen + 1 > cap)
		{
			resize(newLen + 1);
		}
		std::memcpy(data + len, str, addLen + 1);
		len = newLen;
	}
	
	int find(const T* str) 
	{ 
		size_t strLen = std::strlen(str);

		if (strLen > len) return -1; // Если искомая строка длиннее текущей

		for (size_t i = 0; i <= len - strLen; i++)
		{
			if (std::memcmp(data + i, str, strLen) == 0)
			{
				return static_cast<int>(i); // Найдено вхождение
			}
		}
		return -1; // Вхождение не найдено
	} 
private:
	T* data;
	size_t len;
	size_t cap;

	void resize(size_t newCapacity)
	{
		if (newCapacity > cap)
		{
			T* newData = new T[newCapacity];
			std::memcpy(newData, data, len * sizeof(T));
			delete[] data;
			data = newData;
			cap = newCapacity;
		}
	}
};
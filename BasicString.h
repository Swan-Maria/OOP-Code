#pragma once
#include <iostream>
#include <cstring>

template <class T>
class BasicString
{
public:
	BasicString() : data(new T[1]{ '\0' }), len(0), cap(1) {}
	
	BasicString(const T* str) : len (std::strlen(str))
	{
		cap = len + 1;
		data = new T[cap];
		std::memcpy(data, str, len+1);
	}

	BasicString(const BasicString& oth)
		: len(oth.len), cap(oth.cap) 
	{
		data=new T[cap];
		std::memcpy(data, oth.data, len + 1);
	}
	
	BasicString(BasicString&& oth) noexcept
		: data(oth.data), len(oth.len), cap(oth.cap)
	{
		oth.data = nullptr;
		oth.len = 0;
		oth.cap = 0;
	}

	~BasicString()
	{
		delete[] data;
		data = nullptr;
	}

	BasicString& operator=(const BasicString& oth) 
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
	
	BasicString& operator=(BasicString&& oth) noexcept
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

	T& operator[](size_t index) {return data[index];}
	const T& operator[](size_t index) const {return data[index];}

	// METHODS
	bool empty() const { return len == 0; }
	size_t size() const { return len; }
	size_t capacity() const { return cap; }
	void append(const T* str)
	{
		size_t addLen = std::strlen(str);
		size_t newLen = len + addLen;
		if (newLen + 1 > cap)
			resize(newLen + 1);
		std::memcpy(data + len, str, addLen + 1);
		len = newLen;
	}
	int find(const T* str) 
	{ 
		size_t strLen = std::strlen(str);
		if (strLen > len) return -1;
		for (size_t i = 0; i <= len - strLen; i++)
			if (std::memcmp(data + i, str, strLen) == 0)
				return static_cast<int>(i);
		return -1;
	} 
	friend BasicString<T> operator+(const BasicString<T>& left, const BasicString<T>& right);
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

template <class T>
BasicString<T> operator+(const BasicString<T>& left, const BasicString<T>& right)
{
	BasicString<T> result;
	result.len = left.len + right.len;
	result.cap = result.len + 1;
	result.data = new T[result.cap];
	std::memcpy(result.data, left.data, left.len);
	std::memcpy(result.data + left.len, right.data, right.len + 1);
	return result;
}
#pragma once

template <class T> class Vector;

template <class T>
class Iterator
{
public:
	using diff_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = const T*;
	using reference = const T&;

private:
	pointer ptr_;

	friend class Vector<T>;

public:
	explicit Iterator(pointer ptr) : ptr_(ptr) {}

	reference operator*() const
	{
		return *ptr_;
	}

	reference operator->() const
	{
		return ptr_;
	}

	Iterator& operator++()
	{
		++ptr_;
		return *this;
	}

	Iterator& operator--()
	{
		--ptr_;
		return *this;
	}

	// ------------------------ Iterator operator+(Iterator) -------------------------
	// One of the features of iterators is the presence of an overloaded operator "-" 
	// and the absence of an overloaded operator "+" for two iterators
	// (addition of an iterator with an int is provided).
	// So this action does not make sense.
	
	Iterator operator+(size_t offset) const
	{
		return Iterator(ptr_ + offset);
	}

	Iterator& operator+=(size_t offset)
	{
		ptr_ += offset;
		return *this;
	}

	bool operator==(const Iterator& other) const
	{
		return ptr_ == other.ptr_;
	}

	bool operator<(const Iterator& other) const
	{
		return ptr_ < other.ptr_;
	}
};
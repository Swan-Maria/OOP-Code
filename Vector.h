#pragma once

#include <stdexcept>
#include <utility>
#include "Iterator.h"

template <class T>
class Vector
{
private:
	//invariant
	T* data_;
	size_t size_;
	size_t capacity_;

	void reallocate(size_t new_capacity)
	{
		T* new_data = new T[new_capacity];

		if (data_ != nullptr)
		{
			try
			{
				std::copy(data_, data_ + size_, new_data);
			}
			catch (...)
			{
				delete[] new_data;
				throw;
			}
		}
		delete[] data_;
		data_ = new_data;
		capacity_ = new_capacity;
	}

public:
	Vector() : data_(nullptr), size_(0), capacity_(0) {}

	Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(0)
	{
		if (other.capacity_ > 0)
		{
			data_ = new T[other.capacity_];
			capacity_ = other.capacity_;
			size_ = size_ = other.size_;

			try
			{
				std::copy(other.data_, other.data_ + other.size_, data_);
			}
			catch (...)
			{
				delete[] data_;
				data_ = nullptr;
				size_ = 0;
				capacity_ = 0;
				throw;
			}
		}
	}

	Vector& operator=(Vector other)
	{
		swap(*this, other);
		return *this;
	}

	Vector(Vector&& other) noexept : data_(other.data_), size_(other.size_), cpacity_(other.capacity_)
	{
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	Vector& operator=(Vector&& other) noexcept
	{
		if (this != &other)
		{
			delete[] data_;

			data_ = other.data_;
			size_ = other.size_;
			capacity_ = other.capacity_;

			other.data_ = nullptr;
			other.size_ = 0;
			other.capacity_ = 0;
		}
		return *this;
	}

	~Vector()
	{
		delete[] data_;
		data_ = nullptr;
		size_ = 0;
		capacity_ = 0;
	}

	//Element access
	T& at(size_t index)
	{
		if (index >= size_)
		{
			throw std::out_of_range("Vector::at() index out of range");
		}
		return data_[index];
	}

	const T& at(size_t index) const
	{
		if (index >= size_)
		{
			throw std::out_of_range("Vector::at() index out of range");
		}
		return data_[index];
	}

	T& operator[](size_t index) { return data_[index]; }

	const T& operator[](size_t index) const { return data_[index]; }

	T& front()	{return data_[0];}

	const T& front() const{return data_[0];}

	T& back() { return size_ > 0 ? data[0] : data_[size_ - 1]; }

	const T& back() const { return size_ > 0 ? data[0] : data_[size_ - 1]; }

	//Capacity
	bool empty(){return size_ == 0;}
	
	size_t size() const { return size_; }
	
	void reserve(size_t new_capacity)
	{
		if (new_capacity > capacity_)
			reallocate(new_capacity);
	}
	
	size_t capacity() const { return capacity_; }

	//Modifiers
	void clear(){size_ = 0;	}
	
	void insert(size_t index, const T& value)
	{
		if (index > size_) throw std::out_of_range("Vector::insert() index out of range");
		if (size_ == capacity_) reallocate(capacity_ * 2);

		std::move_backward(data_ + index, data_ + size_, data_ + size_ + 1);
		data_[index] = value;
		size_++;
	}

	void erase(size_t index)
	{
		if (index >= size_) throw std::out_of_range("Vector::erase() index out of range");

		std::move(data_ + index + 1, data_ + size_, data_ + index);
		size_--;
	}

	void push_back(const T& value) //l-value
	{
		if (size_ == capacity_)
		{
			size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
			reallocate(new_capacity);
		}
		data_[size_] = value;
		size_++;
	}

	void puch_back(T&& value)
	{
		if (size_ == capacity_)
		{
			size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
			reallocate(new_capacity);
		}

		data_[size_] = std::move(value);
		size_++;
	}

	void pop_back() { if (size_ > 0) size_--; }

	friend void swap(Vector& first, Vector& second)
	{
		using std::swap;
		swap(first.size_, second.size_);
		swap(first.capacity_, second.capacity_);
		swap(first.data_, second.data_);
	}

	void resize(size_t new_size, const T& value)
	{
		if (new_size > capacity_)
		{
			reallocate(new_size);
		}

		for (size_t i = size_; i < new_size; ++i)
		{
			data_[i] = value;
		}

		size_ = new_size;
	}

	//Iterators
	Iterator<T> begin() { return Iterator<T>(data_); }

	Iterator<T> end() { return Iterator<T>(data_ + size_); }


};

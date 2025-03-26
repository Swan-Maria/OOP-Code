#include <iostream>
#include <time.h>
#pragma once

template<typename T>
class Matrix
{
private:
	void Destroy();

	static int countObjects;

	T** m_pdata;
	size_t m_rows;
	size_t m_cols;

public:
	Matrix(size_t rows = 2, size_t cols = 2);
	Matrix(size_t rows, size_t cols, T value);
	~Matrix();
	Matrix(const Matrix& oth);
	Matrix(Matrix&& oth); 
	Matrix operator=(const Matrix&);
	Matrix& operator=(Matrix&& other) noexcept;

	Matrix operator+(const Matrix&) const; //binary +
	Matrix operator-(const Matrix&) const; //binary -
	Matrix operator*(const T mult) const;  //multiply by number
	Matrix operator*(const Matrix&) const; //multiply by matrix

	Matrix operator+=(const Matrix&) const;
	Matrix operator-=(const Matrix&) const;
	Matrix operator*=(const T mult) const;
	Matrix operator*=(const Matrix&) const;

	Matrix operator++(); //prefix
	Matrix operator++(int); //postfix
	Matrix operator--(); //prefix
	Matrix operator--(int); //postfix

	Matrix operator-();

	bool operator==(const Matrix&) const;
	bool operator!=(const Matrix&) const;
	bool operator<(const Matrix&) const;
	bool operator>(const Matrix&) const;
	bool operator<=(const Matrix&) const;
	bool operator>=(const Matrix&) const;

	T GetElement(size_t row, size_t col) const;
	size_t GetRowsCount() const;
	size_t GetColsCount() const;

	void FillByRandom();
	void FillByValue(T value);

	T& operator()(size_t row, size_t col);
	T** operator->();
	Matrix operator*();
	int* operator[](size_t row) { return m_pdata[row]; };

	Matrix Transpose(bool& success) const;

	static Matrix createMatrix();

	void Print();

	friend Matrix operator*(T mult, const Matrix& other);
	friend std::ostream& operator<<(std::ostream&, const Matrix&);
};

template <typename T>
int Matrix<T>::countObjects = 0;

template <typename T>
inline Matrix<T>::Matrix(size_t rows, size_t cols)
	: m_pdata(new T* [rows]), m_rows(rows), m_cols(cols)
{
	for (int i = 0; i < m_rows; i++)
	{
		m_pdata[i] = new T[m_cols];
	}
	countObjects++;
}

template <typename T>
inline Matrix<T>::Matrix(size_t rows, size_t cols, T value)
	: Matrix(rows, cols)
{
	FillByValue(value);
}

template <typename T>
inline Matrix<T>::Matrix(const Matrix& other)
	: m_pdata(new int* [other.m_rows]), m_rows(other.m_rows), m_cols(other.m_cols)  //deep copy
{
	std::cout << "Copy constructor\n";
	for (int i = 0; i < m_rows; i++)
	{
		m_pdata[i] = new int[m_cols];
		for (int j = 0; j < m_cols; j++)
		{
			m_pdata[i][j] = other.m_pdata[i][j];
		}
	}
	countObjects++;
}

template <typename T>
inline Matrix<T>::Matrix(Matrix&& other)
	: m_rows(other.m_rows), m_cols(other.m_cols), m_pdata(other.m_pdata)
{
	std::cout << "Move constructor\n";
	other.m_rows = 0;
	other.m_cols = 0;
	other.m_pdata = nullptr;
}

template <typename T>
inline Matrix<T>::~Matrix()
{
	Destroy();
	countObjects--;
}

template <typename T>
inline Matrix<T> Matrix<T>::operator=(const Matrix& other)
{
	if (this != &other)
	{
		Destroy();
		m_rows = other.m_rows;
		m_cols = other.m_cols;
		m_pdata = new int* [other.m_rows];
		for (int i = 0; i < m_rows; i++)
		{
			m_pdata[i] = new int[other.m_cols];
			for (int j = 0; j < m_cols; j++)
			{
				m_pdata[i][j] = other.m_pdata[i][j];
			}
		}
	}
	return *this;
}

template <typename T>
inline Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept //move operator  
{
	if (this != &other)
	{
		Destroy();

		m_rows = other.m_rows;
		m_cols = other.m_cols;
		m_pdata = other.m_pdata;

		other.m_rows = 0;
		other.m_cols = 0;
		other.m_pdata = nullptr;
	}
	return *this;
}

template <typename T>
inline Matrix<T> Matrix<T>::operator+(const Matrix& other) const
{
	Matrix result(this->m_rows, this->m_cols);

	if (this->m_rows != other.m_rows || this->m_cols != other.m_cols)
	{
		std::cout << "Matrices have different sizes and operation can not be done\n";
	}
	else
	{
		for (int i = 0; i < this->m_rows; ++i)
		{
			for (int j = 0; j < this->m_cols; ++j)
			{
				result.m_pdata[i][j] = this->m_pdata[i][j] + other.m_pdata[i][j];
			}
		}
	}
	return Matrix(result);
}

template <typename T>
inline Matrix<T> Matrix<T>::operator-(const Matrix& other) const
{
	return *this + other * (-1);
}

template <typename T>
inline Matrix<T> Matrix<T>::operator*(const T mult) const
{
	Matrix result(m_rows, m_cols);
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			result.m_pdata[i][j] = m_pdata[i][j] * mult;
		}
	}
	return result;
}

template <typename T>
inline Matrix<T> Matrix<T>::operator*(const Matrix& other) const
{
	Matrix result(m_rows, other.m_cols);
	if (m_cols != other.m_rows)
	{
		std::cout << "Matrices have different sizes and operation can not be done\n";
		result.FillByValue(-1);
	}
	else
	{
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < other.m_cols; j++)
			{
				result.m_pdata[i][j] = 0;
				for (int k = 0; k < m_cols; k++)
				{
					result.m_pdata[i][j] += m_pdata[i][k] * other.m_pdata[k][j];
				}
			}
		}
	}
	return result;
}

template <typename T>
inline Matrix<T> Matrix<T>::operator+=(const Matrix& other) const
{
	return (*this) + other;
}

template <typename T>
inline Matrix<T> Matrix<T>::operator-=(const Matrix& other) const
{
	return (*this) - other;
}

template <typename T>
inline Matrix<T> Matrix<T>::operator*=(const T mult) const
{
	return (*this) * mult;
}

template <typename T>
inline Matrix<T> Matrix<T>::operator*=(const Matrix& other) const
{
	return (*this) * other;
}

template <typename T>
inline Matrix<T> Matrix<T>::operator++()
{
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			++m_pdata[i][j];
		}
	}
	return (*this);
}

template <typename T>
inline Matrix<T> Matrix<T>::operator++(int)
{
	Matrix temp{ *this };

	++(*this);

	return temp;
}

template <typename T>
inline Matrix<T> Matrix<T>::operator--()
{
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			--m_pdata[i][j];
		}
	}
	return (*this);
}

template <typename T>
inline Matrix<T> Matrix<T>::operator--(int)
{
	Matrix temp{ *this };

	--(*this);

	return temp;
}

template <typename T>
inline Matrix<T> Matrix<T>::operator-()
{
	return (*this) * (-1);
}

template <typename T>
inline bool Matrix<T>::operator==(const Matrix& other) const
{
	if (m_rows != other.m_rows || m_cols != other.m_cols)
	{
		return false;
	}
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			if (m_pdata[i][j] != other.m_pdata[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

template <typename T>
inline bool Matrix<T>::operator!=(const Matrix& other) const
{
	return !((*this) == other);
}

template <typename T>
inline bool Matrix<T>::operator<(const Matrix& other) const
{
	return m_pdata[0][0] < other.m_pdata[0][0];
}

template <typename T>
inline bool Matrix<T>::operator>(const Matrix& other) const
{
	return other < *this;
}

template <typename T>
inline bool Matrix<T>::operator<=(const Matrix& other) const
{
	return ((*this) < other) || ((*this) == other);
}

template <typename T>
inline bool Matrix<T>::operator>=(const Matrix& other) const
{
	return ((*this) > other) || ((*this) == other);
}

template <typename T>
inline Matrix<T> Matrix<T>::createMatrix()
{
	Matrix temp(2, 2, 1);
	return temp; //RVO
}

template <typename T>
inline T Matrix<T>::GetElement(size_t row, size_t col) const
{
	return m_pdata[row][col];
}

template <typename T>
inline size_t Matrix<T>::GetRowsCount() const
{
	return m_rows;
}

template <typename T>
inline size_t Matrix<T>::GetColsCount() const
{
	return m_cols;
}

template <typename T>
inline void Matrix<T>::FillByRandom()
{
	srand(static_cast<T>(time(NULL)));
	size_t size = m_cols * m_rows;
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			m_pdata[i][j] = rand() % (size - 1) + 1;
		}
	}
}

template <typename T>
inline void Matrix<T>::FillByValue(T value)
{
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			m_pdata[i][j] = value;
		}
	}
}

template <typename T>
inline T& Matrix<T>::operator()(size_t row, size_t col)
{
	return m_pdata[row][col];
}

template <typename T>
inline T** Matrix<T>::operator->()
{
	return m_pdata;
}

template <typename T>
inline Matrix<T> Matrix<T>::operator*()
{
	return *this;
}

template <typename T>
inline Matrix<T> Matrix<T>::Transpose(bool& success) const
{
	Matrix result(m_cols, m_rows);
	for (int i = 0; i < result.m_rows; ++i)
	{
		for (int j = 0; j < result.m_cols; ++j)
		{
			result.m_pdata[i][j] = m_pdata[j][i];
		}
	}
	success = true;
	return result;
}

template <typename T>
inline void Matrix<T>::Print()
{
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			std::cout << m_pdata[i][j] << "       ";
		}
		std::cout << '\n';
	}
}

template <typename T>
void Matrix<T>::Destroy()
{
	for (int i = 0; i < m_rows; ++i)
	{
		delete[] m_pdata[i];
		m_pdata[i] = nullptr;
	}
	delete[] m_pdata;
	m_pdata = nullptr;
}

template <typename T>
Matrix<T> operator*(T mult, const Matrix<T>& other)
{
	return other * mult;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix)
{
	for (int i = 0; i < matrix.m_rows; ++i)
	{
		for (int j = 0; j < matrix.m_cols; ++j)
		{
			out << matrix.m_pdata[i][j] << "       ";
		}
		out << '\n';
	}
	return out;
}
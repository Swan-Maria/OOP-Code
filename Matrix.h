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
	// constructors
	Matrix(size_t rows = 2, size_t cols = 2);
	Matrix(size_t rows, size_t cols, T value);
	Matrix(const Matrix& oth); //copy
	Matrix(Matrix&& oth); //move

	// static
	static Matrix createMatrix();

	// destructor
	~Matrix();

	// getter
	T GetElement(size_t row, size_t col) const;
	size_t GetRowsCount() const;
	size_t GetColsCount() const;

	// setter
	void FillByRandom();
	void FillByValue(T value);

	// operator ()
	T& operator()(size_t row, size_t col);
	T** operator->();
	Matrix operator*();

	// transpose matrix
	Matrix Transpose(bool& success) const;

	// print matrix
	void Print();

	// operator =
	Matrix operator=(const Matrix&); // copy 
	Matrix& operator=(Matrix&& other) noexcept; // move

	// arithmetic operators
	Matrix operator+(const Matrix&) const; //binary +
	Matrix operator-(const Matrix&) const; //binary -
	Matrix operator*(const T mult) const;  //multiply by number
	Matrix operator*(const Matrix&) const; //multiply by matrix

	// short forms of operators
	Matrix operator+=(const Matrix&) const;
	Matrix operator-=(const Matrix&) const;
	Matrix operator*=(const T mult) const;
	Matrix operator*=(const Matrix&) const;

	// increment & decrement
	Matrix operator++(); //prefix
	Matrix operator++(int); //postfix
	Matrix operator--(); //prefix
	Matrix operator--(int); //postfix

	// unary operator -
	Matrix operator-();

	// bool operators
	bool operator==(const Matrix&) const;
	bool operator!=(const Matrix&) const;
	bool operator<(const Matrix&) const;
	bool operator>(const Matrix&) const;
	bool operator<=(const Matrix&) const;
	bool operator>=(const Matrix&) const;

	// operator []
	int* operator[](size_t row) {return m_pdata[row];};


	//friend functions
	friend Matrix operator*(T mult, const Matrix& other);
	friend std::ostream& operator<<(std::ostream&, const Matrix&);
};

////////////////////////////////////////////////////////////////////////

template <typename T>
int Matrix<T>::countObjects = 0;





// constructors
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
	: m_pdata(new T* [rows]), m_rows(rows), m_cols(cols)
{
	for (int i = 0; i < m_rows; i++)
	{
		m_pdata[i] = new T[m_cols];
	}
	countObjects++;
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, T value)
	: Matrix(rows, cols)
{
	FillByValue(value);
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other)
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
Matrix<T>::Matrix(Matrix&& other)
	: m_rows(other.m_rows), m_cols(other.m_cols), m_pdata(other.m_pdata)
{
	std::cout << "Move constructor\n";
	other.m_rows = 0;
	other.m_cols = 0;
	other.m_pdata = nullptr;
}





//static
template <typename T>
Matrix<T> Matrix<T>::createMatrix()
{
	Matrix temp(2, 2, 1);
	return temp; //RVO
}





// destructor
template <typename T>
Matrix<T>::~Matrix()
{
	Destroy();
	countObjects--;
}





//getter
template <typename T>
T Matrix<T>::GetElement(size_t row, size_t col) const
{
	return m_pdata[row][col];
}

template <typename T>
size_t Matrix<T>::GetRowsCount() const
{
	return m_rows;
}

template <typename T>
size_t Matrix<T>::GetColsCount() const
{
	return m_cols;
}





//setter
template <typename T>
void Matrix<T>::FillByRandom()
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
void Matrix<T>::FillByValue(T value)
{
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			m_pdata[i][j] = value;
		}
	}
}





//operator ()
template <typename T>
T& Matrix<T>::operator()(size_t row, size_t col)
{
	return m_pdata[row][col];
}

template <typename T>
T** Matrix<T>::operator->()
{
	return m_pdata;
}

template <typename T>
Matrix<T> Matrix<T>::operator*()
{
	return *this;
}





// transpose matrix
template <typename T>
Matrix<T> Matrix<T>::Transpose(bool& success) const
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





// print matrix
template <typename T>
void Matrix<T>::Print()
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





//Copy operator
template <typename T>
Matrix<T> Matrix<T>::operator=(const Matrix& other)
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





//Move operator
template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept //move operator  
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





//arithmetic operators
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const
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
Matrix<T> Matrix<T>::operator-(const Matrix& other) const
{
	return *this + other * (-1);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T mult) const
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
Matrix<T> Matrix<T>::operator*(const Matrix& other) const
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





//short forms of operators
template <typename T>
Matrix<T> Matrix<T>::operator+=(const Matrix& other) const
{
	return (*this) + other;
}

template <typename T>
Matrix<T> Matrix<T>::operator-=(const Matrix& other) const
{
	return (*this) - other;
}

template <typename T>
Matrix<T> Matrix<T>::operator*=(const T mult) const
{
	return (*this) * mult;
}

template <typename T>
Matrix<T> Matrix<T>::operator*=(const Matrix& other) const
{
	return (*this) * other;
}





// increment & decrement
template <typename T>
Matrix<T> Matrix<T>::operator++()
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
Matrix<T> Matrix<T>::operator++(int)
{
	Matrix temp{ *this };

	++(*this);

	return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator--()
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
Matrix<T> Matrix<T>::operator--(int)
{
	Matrix temp{ *this };

	--(*this);

	return temp;
}





// unary operator -
template <typename T>
Matrix<T> Matrix<T>::operator-()
{
	return (*this) * (-1);
}





// bool operators
template <typename T>
bool Matrix<T>::operator==(const Matrix& other) const
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
bool Matrix<T>::operator!=(const Matrix& other) const
{
	return !((*this) == other);
}

template <typename T>
bool Matrix<T>::operator<(const Matrix& other) const
{
	return m_pdata[0][0] < other.m_pdata[0][0];
}

template <typename T>
bool Matrix<T>::operator>(const Matrix& other) const
{
	return other < *this;
}

template <typename T>
bool Matrix<T>::operator<=(const Matrix& other) const
{
	return ((*this) < other) || ((*this) == other);
}

template <typename T>
bool Matrix<T>::operator>=(const Matrix& other) const
{
	return ((*this) > other) || ((*this) == other);
}





// Destroy
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





//friend functions
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
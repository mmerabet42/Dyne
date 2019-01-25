#include "Matrix.hpp"

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Matrix<Rows, Columns, T>::Matrix(const T &p_identity)
{
	for (dn::t_length i = 0; i < Columns; ++i)
	{
		for (dn::t_length j = 0; j < Rows; ++j)
		{
			if (Columns != Rows || i == j)
				this->_columns[i].get(j) = p_identity;
			else
				this->_columns[i].get(j) = T();
		}
	}
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Matrix<Rows, Columns, T>::Matrix(const std::initializer_list<dn::Vector<Rows, T>> &p_list)
{
	for (dn::t_length i = 0; i < Columns; ++i)
	{
		if (i >= p_list.size())
			this->_columns[i] = dn::Vector<Rows, T>();
		else
			this->_columns[i] = *(p_list.begin() + i);
	}
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Matrix<Rows, Columns, T>::Matrix(const std::initializer_list<std::initializer_list<T>> &p_list)
{
	for (dn::t_length i = 0; i < Columns; ++i)
	{
		if (i >= p_list.size())
			this->_columns[i] = dn::Vector<Rows, T>();
		else
			this->_columns[i] = *(p_list.begin() + i);
	}
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
template <dn::t_length Rows2, dn::t_length Columns2>
dn::Matrix<Rows, Columns, T>::Matrix(const dn::Matrix<Rows2, Columns2, T> &p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] = p_mat.get(i);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
template <typename ... Args>
dn::Matrix<Rows, Columns, T>::Matrix(const Args & ... p_args)
{
	T arr[Rows * Columns] = {(T)(p_args)...};
	for (dn::t_length i = 0; i < Rows; ++i)
		for (dn::t_length j = 0; j < Columns; ++j)
			this->_columns[j][i] = arr[i * Columns + j];
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Vector<Rows, T> dn::Matrix<Rows, Columns, T>::get(dn::t_length p_i) const
{
	while (p_i < 0)
		p_i += Columns;
	while (p_i >= Columns)
		p_i -= Columns;
	return (this->_columns[p_i]);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Vector<Rows, T> &dn::Matrix<Rows, Columns, T>::get(t_length p_i)
{
	while (p_i < 0)
		p_i += Columns;
	while (p_i >= Columns)
		p_i -= Columns;
	return (this->_columns[p_i]);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Vector<Rows, T> dn::Matrix<Rows, Columns, T>::operator[](dn::t_length p_i) const
{
	while (p_i < 0)
		p_i += Columns;
	while (p_i >= Columns)
		p_i -= Columns;
	return (this->_columns[p_i]);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Vector<Rows, T> &dn::Matrix<Rows, Columns, T>::operator[](t_length p_i)
{
	while (p_i < 0)
		p_i += Columns;
	while (p_i >= Columns)
		p_i -= Columns;
	return (this->_columns[p_i]);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
std::ostream &dn::operator<<(std::ostream &p_stream, const dn::Matrix<Rows, Columns, T> &p_mat)
{
	for (dn::t_length i = 0; i < Rows; ++i)
	{
		p_stream << "[";
		for (dn::t_length j = 0; j < Columns; ++j)
			p_stream << p_mat[j][i] << (j + 1 == Columns ? "]" : ", ");
		if (i + 1 < Rows)
			p_stream << std::endl;
	}
	return (p_stream);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Matrix<Rows, Columns, T> &dn::Matrix<Rows, Columns, T>::set(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		for (dn::t_length j = 0; j < Rows; ++j)
			this->_columns[i][j] = p_scalar;
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Matrix<Rows, Columns, T> &dn::Matrix<Rows, Columns, T>::operator+=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] += p_scalar;
	return (*this);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Matrix<Rows, Columns, T> &dn::Matrix<Rows, Columns, T>::operator-=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] -= p_scalar;
	return (*this);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Matrix<Rows, Columns, T> &dn::Matrix<Rows, Columns, T>::operator*=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] *= p_scalar;
	return (*this);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Matrix<Rows, Columns, T> &dn::Matrix<Rows, Columns, T>::operator/=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] /= p_scalar;
	return (*this);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Matrix<Rows, Columns, T> &dn::Matrix<Rows, Columns, T>
	::operator+=(const dn::Matrix<Rows, Columns, T> &p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] += p_mat.get(i);
	return (*this);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Matrix<Rows, Columns, T> &dn::Matrix<Rows, Columns, T>
	::operator-=(const dn::Matrix<Rows, Columns, T> &p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] -= p_mat.get(i);
	return (*this);
}

template <dn::t_length Rows, dn::t_length Columns, dn::t_length Size, typename T>
dn::Matrix<Rows, Size, T> dn
	::operator*(const dn::Matrix<Rows, Columns, T> &p_a, const dn::Matrix<Columns, Size, T> &p_b)
{
	dn::Matrix<Rows, Size, T> result;
	result.set(T());

	for (dn::t_length i = 0; i < Rows; ++i)
		for (dn::t_length j = 0; j < Size; ++j)
			for (dn::t_length k = 0; k < Columns; ++k)
				result[j][i] += p_a[k][i] * p_b[j][k];
	return (result);
}

template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
dn::Matrix<Rows, Columns, T> dn::operator+(dn::Matrix<Rows, Columns, T> p_mat, const U &p_scalar)
{
	p_mat += (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
dn::Matrix<Rows, Columns, T> dn::operator-(dn::Matrix<Rows, Columns, T> p_mat, const U &p_scalar)
{
	p_mat -= (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
dn::Matrix<Rows, Columns, T> dn::operator*(dn::Matrix<Rows, Columns, T> p_mat, const U &p_scalar)
{
	p_mat *= (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
dn::Matrix<Rows, Columns, T> dn::operator/(dn::Matrix<Rows, Columns, T> p_mat, const U &p_scalar)
{
	p_mat /= (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
dn::Matrix<Rows, Columns, T> dn::operator+(const U &p_scalar, dn::Matrix<Rows, Columns, T> p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		p_mat[i] += (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
dn::Matrix<Rows, Columns, T> dn::operator-(const U &p_scalar, dn::Matrix<Rows, Columns, T> p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		p_mat[i] -= (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
dn::Matrix<Rows, Columns, T> dn::operator*(const U &p_scalar, dn::Matrix<Rows, Columns, T> p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		p_mat[i] *= (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
dn::Matrix<Rows, Columns, T> dn::operator/(const U &p_scalar, dn::Matrix<Rows, Columns, T> p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		p_mat[i] /= (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Vector<Rows, T> dn
	::operator*(const dn::Matrix<Rows, Columns, T> &p_mat, const dn::Vector<Columns, T> &p_vec)
{
	dn::Vector<Rows, T> result;

	for (dn::t_length i = 0; i < Rows; ++i)
		for (dn::t_length j = 0; j < Columns; ++j)
			result[i] += p_mat[j][i] * p_vec[j];
	return (result);
}

template <dn::t_length Rows, dn::t_length Columns, typename T>
dn::Vector<Rows, T> dn
	::operator*(const dn::Vector<Columns, T> &p_vec, const dn::Matrix<Rows, Columns, T> &p_mat)
{
	dn::Vector<Rows, T> result;

	for (dn::t_length i = 0; i < Rows; ++i)
		for (dn::t_length j = 0; j < Columns; ++j)
			result[i] += p_vec[j] * p_mat[j][i];
	return (result);
}

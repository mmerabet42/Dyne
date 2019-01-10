#include "Matrix.hpp"

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Matrix<Columns, Rows, T>::Matrix(const T &p_identity)
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

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Matrix<Columns, Rows, T>::Matrix(const std::initializer_list<dn::Vector<Rows, T>> &p_list)
{
	for (dn::t_length i = 0; i < Columns; ++i)
	{
		if (i >= p_list.size())
			this->_columns[i] = dn::Vector<Rows, T>();
		else
			this->_columns[i] = *(p_list.begin() + i);
	}
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Matrix<Columns, Rows, T>::Matrix(const std::initializer_list<std::initializer_list<T>> &p_list)
{
	for (dn::t_length i = 0; i < Columns; ++i)
	{
		if (i >= p_list.size())
			this->_columns[i] = dn::Vector<Rows, T>();
		else
			this->_columns[i] = *(p_list.begin() + i);
	}
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
template <dn::t_length Columns2, dn::t_length Rows2>
dn::Matrix<Columns, Rows, T>::Matrix(const dn::Matrix<Columns2, Rows2, T> &p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] = p_mat.get(i);
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Vector<Rows, T> dn::Matrix<Columns, Rows, T>::get(dn::t_length p_i) const
{
	while (p_i < 0)
		p_i += Columns;
	while (p_i >= Columns)
		p_i -= Columns;
	return (this->_columns[p_i]);
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Vector<Rows, T> &dn::Matrix<Columns, Rows, T>::get(t_length p_i)
{
	while (p_i < 0)
		p_i += Columns;
	while (p_i >= Columns)
		p_i -= Columns;
	return (this->_columns[p_i]);
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Vector<Rows, T> dn::Matrix<Columns, Rows, T>::operator[](dn::t_length p_i) const
{
	while (p_i < 0)
		p_i += Columns;
	while (p_i >= Columns)
		p_i -= Columns;
	return (this->_columns[p_i]);
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Vector<Rows, T> &dn::Matrix<Columns, Rows, T>::operator[](t_length p_i)
{
	while (p_i < 0)
		p_i += Columns;
	while (p_i >= Columns)
		p_i -= Columns;
	return (this->_columns[p_i]);
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
std::ostream &dn::operator<<(std::ostream &p_stream, const dn::Matrix<Columns, Rows, T> &p_mat)
{
	for (dn::t_length i = 0; i < Rows; ++i)
	{
		p_stream << "[";
		for (dn::t_length j = 0; j < Columns; ++j)
			p_stream << p_mat[j][i] << (j + 1 == Columns ? "]" : ", ");
		if (i + 1 < Columns)
			p_stream << std::endl;
	}
	return (p_stream);
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Matrix<Columns, Rows, T> &dn::Matrix<Columns, Rows, T>::set(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		for (dn::t_length j = 0; j < Rows; ++j)
			this->_columns[i][j] = p_scalar;
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Matrix<Columns, Rows, T> &dn::Matrix<Columns, Rows, T>::operator+=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] += p_scalar;
	return (*this);
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Matrix<Columns, Rows, T> &dn::Matrix<Columns, Rows, T>::operator-=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] -= p_scalar;
	return (*this);
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Matrix<Columns, Rows, T> &dn::Matrix<Columns, Rows, T>::operator*=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] *= p_scalar;
	return (*this);
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Matrix<Columns, Rows, T> &dn::Matrix<Columns, Rows, T>::operator/=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] /= p_scalar;
	return (*this);
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Matrix<Columns, Rows, T> &dn::Matrix<Columns, Rows, T>
	::operator+=(const dn::Matrix<Columns, Rows, T> &p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] += p_mat.get(i);
	return (*this);
}

template <dn::t_length Columns, dn::t_length Rows, typename T>
dn::Matrix<Columns, Rows, T> &dn::Matrix<Columns, Rows, T>
	::operator-=(const dn::Matrix<Columns, Rows, T> &p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		this->_columns[i] -= p_mat.get(i);
	return (*this);
}

template <dn::t_length Columns, dn::t_length Rows, dn::t_length Size, typename T>
dn::Matrix<Size, Rows, T> dn
	::operator*(const dn::Matrix<Columns, Rows, T> &p_a, const dn::Matrix<Size, Columns, T> &p_b)
{
	dn::Matrix<Size, Rows, T> result;
	result.set(T());

	for (dn::t_length i = 0; i < Rows; ++i)
		for (dn::t_length j = 0; j < Size; ++j)
			for (dn::t_length k = 0; k < Columns; ++k)
				result[j][i] += p_a[k][i] * p_b[j][k];
	return (result);
}

template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
dn::Matrix<Columns, Rows, T> dn::operator+(dn::Matrix<Columns, Rows, T> p_mat, const U &p_scalar)
{
	p_mat += (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
dn::Matrix<Columns, Rows, T> dn::operator-(dn::Matrix<Columns, Rows, T> p_mat, const U &p_scalar)
{
	p_mat -= (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
dn::Matrix<Columns, Rows, T> dn::operator*(dn::Matrix<Columns, Rows, T> p_mat, const U &p_scalar)
{
	p_mat *= (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
dn::Matrix<Columns, Rows, T> dn::operator/(dn::Matrix<Columns, Rows, T> p_mat, const U &p_scalar)
{
	p_mat /= (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
dn::Matrix<Columns, Rows, T> dn::operator+(const U &p_scalar, dn::Matrix<Columns, Rows, T> p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		p_mat[i] += (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
dn::Matrix<Columns, Rows, T> dn::operator-(const U &p_scalar, dn::Matrix<Columns, Rows, T> p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		p_mat[i] -= (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
dn::Matrix<Columns, Rows, T> dn::operator*(const U &p_scalar, dn::Matrix<Columns, Rows, T> p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		p_mat[i] *= (T)p_scalar;
	return (p_mat);
}

template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
dn::Matrix<Columns, Rows, T> dn::operator/(const U &p_scalar, dn::Matrix<Columns, Rows, T> p_mat)
{
	for (dn::t_length i = 0; i < Columns; ++i)
		p_mat[i] /= (T)p_scalar;
	return (p_mat);
}

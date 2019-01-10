#include "Vector.hpp"

template <dn::t_length Size, typename T>
dn::Vector<Size, T>::Vector(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_rows[i] = p_scalar;
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T>::Vector(const std::initializer_list<T> &p_list)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_rows[i] = (i >= p_list.size() ? T() : *(p_list.begin() + i));
}

template <dn::t_length Size, typename T>
template <typename ... Args>
dn::Vector<Size, T>::Vector(Args ... p_args)
	: _rows{(T)(p_args)...}
{
	for (dn::t_length i = sizeof...(p_args); i < Size; ++i)
		this->_rows[i] = T();
}

template <dn::t_length Size, typename T>
template <dn::t_length Size2>
dn::Vector<Size, T>::Vector(const dn::Vector<Size2, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_rows[i] = p_vec.get(i);
}

template <dn::t_length Size, typename T>
T dn::Vector<Size, T>::get(dn::t_length p_i) const
{
	while (p_i < 0)
		p_i += Size;
	while (p_i >= Size)
		p_i -= Size;
	return (this->_rows[p_i]);
}

template <dn::t_length Size, typename T>
T &dn::Vector<Size, T>::get(dn::t_length p_i)
{
	while (p_i < 0)
		p_i += Size;
	while (p_i >= Size)
		p_i -= Size;
	return (this->_rows[p_i]);
}

template <dn::t_length Size, typename T>
T dn::Vector<Size, T>::operator[](dn::t_length p_i) const
{
	while (p_i < 0)
		p_i += Size;
	while (p_i >= Size)
		p_i -= Size;
	return (this->_rows[p_i]);
}

template <dn::t_length Size, typename T>
T &dn::Vector<Size, T>::operator[](dn::t_length p_i)
{
	while (p_i < 0)
		p_i += Size;
	while (p_i >= Size)
		p_i -= Size;
	return (this->_rows[p_i]);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator+=(const dn::Vector<Size, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_rows[i] += p_vec._rows[i];
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator-=(const dn::Vector<Size, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_rows[i] -= p_vec._rows[i];
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator*=(const dn::Vector<Size, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_rows[i] *= p_vec._rows[i];
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator/=(const dn::Vector<Size, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_rows[i] /= p_vec._rows[i];
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator+=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_rows[i] += p_scalar;
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator-=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_rows[i] -= p_scalar;
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator*=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_rows[i] *= p_scalar;
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator/=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_rows[i] /= p_scalar;
	return (*this);
}

template <dn::t_length Size, typename T>
std::ostream &dn::operator<<(std::ostream &p_stream, const dn::Vector<Size, T> &p_vec)
{
	p_stream << "[";
	for (dn::t_length i = 0; i < Size; ++i)
	{
		p_stream << p_vec.get(i);
		if (i + 1 < Size)
			p_stream << ", ";
	}
	p_stream << "]";
	return (p_stream);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> dn::operator+(const dn::Vector<Size, T> &p_a, const dn::Vector<Size, T> &p_b)
{
	dn::Vector<Size, T> result(p_a);
	return (result += p_b);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> dn::operator-(const dn::Vector<Size, T> &p_a, const dn::Vector<Size, T> &p_b)
{
	dn::Vector<Size, T> result(p_a);
	return (result -= p_b);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> dn::operator*(const dn::Vector<Size, T> &p_a, const dn::Vector<Size, T> &p_b)
{
	dn::Vector<Size, T> result(p_a);
	return (result *= p_b);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> dn::operator/(const dn::Vector<Size, T> &p_a, const dn::Vector<Size, T> &p_b)
{
	dn::Vector<Size, T> result(p_a);
	return (result /= p_b);
}

template <dn::t_length Size, typename T>
T dn::dot(const dn::Vector<Size, T> &p_a, const dn::Vector<Size, T> &p_b)
{
	T res = T();
	for (dn::t_length i = 0; i < Size; ++i)
		res += p_a[i] * p_b[i];
	return (res);
}

template <dn::t_length Size, typename T, typename U>
dn::Vector<Size, T> dn::operator+(const U &p_scalar, dn::Vector<Size, T> p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		p_vec[i] = (T)p_scalar + p_vec[i];
	return (p_vec);
}

template <dn::t_length Size, typename T, typename U>
dn::Vector<Size, T> dn::operator-(const U &p_scalar, dn::Vector<Size, T> p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		p_vec[i] = (T)p_scalar - p_vec[i];
	return (p_vec);
}

template <dn::t_length Size, typename T, typename U>
dn::Vector<Size, T> dn::operator*(const U &p_scalar, dn::Vector<Size, T> p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		p_vec[i] = (T)p_scalar * p_vec[i];
	return (p_vec);
}

template <dn::t_length Size, typename T, typename U>
dn::Vector<Size, T> dn::operator/(const U &p_scalar, dn::Vector<Size, T> p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		p_vec[i] = (T)p_scalar / p_vec[i];
	return (p_vec);
}

template <dn::t_length Size, typename T, typename U>
dn::Vector<Size, T> dn::operator+(dn::Vector<Size, T> p_vec, const U &p_scalar)
{
	p_vec += (T)p_scalar;
	return (p_vec);
}

template <dn::t_length Size, typename T, typename U>
dn::Vector<Size, T> dn::operator-(dn::Vector<Size, T> p_vec, const U &p_scalar)
{
	p_vec -= (T)p_scalar;
	return (p_vec);
}

template <dn::t_length Size, typename T, typename U>
dn::Vector<Size, T> dn::operator*(dn::Vector<Size, T> p_vec, const U &p_scalar)
{
	p_vec *= (T)p_scalar;
	return (p_vec);
}

template <dn::t_length Size, typename T, typename U>
dn::Vector<Size, T> dn::operator/(dn::Vector<Size, T> p_vec, const U &p_scalar)
{
	p_vec /= (T)p_scalar;
	return (p_vec);
}

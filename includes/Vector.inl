#include "Vector.hpp"
#include <cmath>

template <dn::t_length Size, typename T>
dn::Vector<Size, T>::Vector(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] = p_scalar;
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T>::Vector(const std::initializer_list<T> &p_list)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] = (i >= p_list.size() ? T() : *(p_list.begin() + i));
}

template <dn::t_length Size, typename T>
template <typename ... Args>
dn::Vector<Size, T>::Vector(Args ... p_args)
	: _data{(T)(p_args)...}
{
	for (dn::t_length i = sizeof...(p_args); i < Size; ++i)
		this->_data[i] = T();
}

template <dn::t_length Size, typename T>
template <dn::t_length Size2>
dn::Vector<Size, T>::Vector(const dn::Vector<Size2, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] = p_vec.get(i);
}

template <dn::t_length Size, typename T>
T dn::Vector<Size, T>::get(dn::t_length p_i) const
{
	while (p_i < 0)
		p_i += Size;
	while (p_i >= Size)
		p_i -= Size;
	return (this->_data[p_i]);
}

template <dn::t_length Size, typename T>
T &dn::Vector<Size, T>::get(dn::t_length p_i)
{
	while (p_i < 0)
		p_i += Size;
	while (p_i >= Size)
		p_i -= Size;
	return (this->_data[p_i]);
}

template <dn::t_length Size, typename T>
T dn::Vector<Size, T>::length() const
{
	T result;
	for (dn::t_length i = 0; i < Size; ++i)
	{
		if (i == 0)
			result = this->_data[i] * this->_data[i];
		else
			result += this->_data[i] * this->_data[i];
	}
	return (result);
}

template <dn::t_length Size, typename T>
T dn::Vector<Size, T>::lengthSqrt() const
{
	return (std::sqrt(this->length()));
}

template <dn::t_length Size, typename T>
T dn::length(const dn::Vector<Size, T> &p_vec)
{
	T result;
	for (dn::t_length i = 0; i < Size; ++i)
	{
		if (i == 0)
			result = p_vec[i] * p_vec[i];
		else
			result += p_vec[i] * p_vec[i];
	}
	return (result);
}

template <dn::t_length Size, typename T>
T dn::lengthSqrt(const dn::Vector<Size, T> &p_vec)
{
	return (std::sqrt(dn::length(p_vec)));
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> dn::normalize(dn::Vector<Size, T> p_vec)
{
	T mag = p_vec.lengthSqrt();
	if (mag == static_cast<T>(0))
		return (p_vec);
	for (dn::t_length i = 0; i < Size; ++i)
		p_vec.get(i) /= mag;
	return (p_vec);
}

template <dn::t_length Size, typename T>
T dn::Vector<Size, T>::operator[](dn::t_length p_i) const
{
	while (p_i < 0)
		p_i += Size;
	while (p_i >= Size)
		p_i -= Size;
	return (this->_data[p_i]);
}

template <dn::t_length Size, typename T>
T &dn::Vector<Size, T>::operator[](dn::t_length p_i)
{
	while (p_i < 0)
		p_i += Size;
	while (p_i >= Size)
		p_i -= Size;
	return (this->_data[p_i]);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator+=(const dn::Vector<Size, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] += p_vec._rows[i];
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator-=(const dn::Vector<Size, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] -= p_vec._rows[i];
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator*=(const dn::Vector<Size, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] *= p_vec._rows[i];
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator/=(const dn::Vector<Size, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] /= p_vec._rows[i];
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator+=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] += p_scalar;
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator-=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] -= p_scalar;
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator*=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] *= p_scalar;
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator/=(const T &p_scalar)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] /= p_scalar;
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

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
dn::Vector<Size, T>::Vector(Args && ... p_args)
	: _data{std::forward<Args>(p_args)...}
{}

template <dn::t_length Size, typename T>
template <dn::t_length Size2>
dn::Vector<Size, T>::Vector(const dn::Vector<Size2, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] = p_vec.get(i);
}

template <dn::t_length Size, typename T>
template <typename Arg>
void dn::Vector<Size, T>::helper_set(size_t i, Arg && p_arg)
{
	this->_data[i] = p_arg;
}

template <dn::t_length Size, typename T>
template <typename Arg, typename ... Args>
void dn::Vector<Size, T>::helper_set(size_t i, Arg && p_arg, Args && ... p_args)
{
	this->_data[i] = p_arg;
	this->helper_set(i + 1, std::forward<Args>(p_args)...);
}

template <dn::t_length Size, typename T>
template <typename ... Args>
typename std::enable_if_t<(sizeof...(Args) == Size)>
dn::Vector<Size, T>::set(Args && ... p_args)
{
	this->helper_set(0, std::forward<Args>(p_args)...);
}

template <dn::t_length Size, typename T>
T dn::Vector<Size, T>::get(dn::t_length p_i) const
{
	return (this->_data[p_i % Size]);
}

template <dn::t_length Size, typename T>
inline T &dn::Vector<Size, T>::get(dn::t_length p_i)
{
	return (this->_data[p_i % Size]);
}

template <dn::t_length Size, typename T>
inline T dn::Vector<Size, T>::operator[](dn::t_length p_i) const
{
	return (this->get(p_i));
}

template <dn::t_length Size, typename T>
inline T &dn::Vector<Size, T>::operator[](dn::t_length p_i)
{
	return (this->get(p_i));
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
dn::Vector<Size, T> &dn::Vector<Size, T>::operator+=(const dn::Vector<Size, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] += p_vec._data[i];
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator-=(const dn::Vector<Size, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] -= p_vec._data[i];
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator*=(const dn::Vector<Size, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] *= p_vec._data[i];
	return (*this);
}

template <dn::t_length Size, typename T>
dn::Vector<Size, T> &dn::Vector<Size, T>::operator/=(const dn::Vector<Size, T> &p_vec)
{
	for (dn::t_length i = 0; i < Size; ++i)
		this->_data[i] /= p_vec._data[i];
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

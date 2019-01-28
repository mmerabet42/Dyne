#ifndef DN_VECTOR2_INL
# define DN_VECTOR2_INL

#include "dn/Vector2.hpp"

template <typename T>
dn::Vector2<T>::Vector2(const T &p_scalar)
	: Vector<2, T>(p_scalar)
{}

template <typename T>
dn::Vector2<T>::Vector2(const std::initializer_list<T> &p_list)
	: Vector<2, T>(p_list)
{}

template <typename T>
dn::Vector2<T>::Vector2(const T &p_x, const T &p_y)
	: Vector<2, T>(p_x, p_y)
{}

template <typename T>
template <dn::t_length Size2>
dn::Vector2<T>::Vector2(const dn::Vector<Size2, T> &p_vec)
	: Vector<2, T>(p_vec)
{}

template <typename T>
inline T dn::Vector2<T>::x() const { return (this->get(0)); }
template <typename T>
inline T &dn::Vector2<T>::x() { return (this->get(0)); }

template <typename T>
inline T dn::Vector2<T>::y() const { return (this->get(1)); }
template <typename T>
inline T &dn::Vector2<T>::y() { return (this->get(1)); }

#endif // DN_VECTOR2_INL

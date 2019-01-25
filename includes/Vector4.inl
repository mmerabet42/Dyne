#include "Vector4.hpp"

template <typename T>
dn::Vector4<T>::Vector4(const T &p_scalar)
	: Vector<4, T>(p_scalar)
{}

template <typename T>
dn::Vector4<T>::Vector4(const std::initializer_list<T> &p_list)
	: Vector<4, T>(p_list)
{}

template <typename T>
dn::Vector4<T>::Vector4(const T &p_x, const T &p_y, const T &p_z, const T &p_w)
	: Vector<4, T>(p_x, p_y, p_z, p_w)
{}

template <typename T>
template <dn::t_length Size2>
dn::Vector4<T>::Vector4(const dn::Vector<Size2, T> &p_vec)
	: Vector<4, T>(p_vec)
{}

template <typename T>
inline T dn::Vector4<T>::x() const { return (this->get(0)); }
template <typename T>
inline T &dn::Vector4<T>::x() { return (this->get(0)); }

template <typename T>
inline T dn::Vector4<T>::y() const { return (this->get(1)); }
template <typename T>
inline T &dn::Vector4<T>::y() { return (this->get(1)); }

template <typename T>
inline T dn::Vector4<T>::z() const { return (this->get(2)); }
template <typename T>
inline T &dn::Vector4<T>::z() { return (this->get(2)); }

template <typename T>
inline T dn::Vector4<T>::w() const { return (this->get(3)); }
template <typename T>
inline T &dn::Vector4<T>::w() { return (this->get(3)); }

template <typename T>
inline T dn::Vector4<T>::r() const { return (this->get(0)); }
template <typename T>
inline T &dn::Vector4<T>::r() { return (this->get(0)); }

template <typename T>
inline T dn::Vector4<T>::g() const { return (this->get(1)); }
template <typename T>
inline T &dn::Vector4<T>::g() { return (this->get(1)); }

template <typename T>
inline T dn::Vector4<T>::b() const { return (this->get(2)); }
template <typename T>
inline T &dn::Vector4<T>::b() { return (this->get(2)); }

template <typename T>
inline T dn::Vector4<T>::a() const { return (this->get(3)); }
template <typename T>
inline T &dn::Vector4<T>::a() { return (this->get(3)); }

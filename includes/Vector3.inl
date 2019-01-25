#include "Vector3.hpp"

template <typename T>
dn::Vector3<T>::Vector3(const T &p_scalar)
	: Vector<3, T>(p_scalar)
{}

template <typename T>
dn::Vector3<T>::Vector3(const std::initializer_list<T> &p_list)
	: Vector<3, T>(p_list)
{}

template <typename T>
dn::Vector3<T>::Vector3(const T &p_x, const T &p_y, const T &p_z)
	: Vector<3, T>(p_x, p_y, p_z)
{}

template <typename T>
template <dn::t_length Size2>
dn::Vector3<T>::Vector3(const dn::Vector<Size2, T> &p_vec)
	: Vector<3, T>(p_vec)
{}

template <typename T>
inline T dn::Vector3<T>::x() const { return (this->get(0)); }
template <typename T>
inline T &dn::Vector3<T>::x() { return (this->get(0)); }

template <typename T>
inline T dn::Vector3<T>::y() const { return (this->get(1)); }
template <typename T>
inline T &dn::Vector3<T>::y() { return (this->get(1)); }

template <typename T>
inline T dn::Vector3<T>::z() const { return (this->get(2)); }
template <typename T>
inline T &dn::Vector3<T>::z() { return (this->get(2)); }

template <typename T>
inline T dn::Vector3<T>::r() const { return (this->get(0)); }
template <typename T>
inline T &dn::Vector3<T>::r() { return (this->get(0)); }

template <typename T>
inline T dn::Vector3<T>::g() const { return (this->get(1)); }
template <typename T>
inline T &dn::Vector3<T>::g() { return (this->get(1)); }

template <typename T>
inline T dn::Vector3<T>::b() const { return (this->get(2)); }
template <typename T>
inline T &dn::Vector3<T>::b() { return (this->get(2)); }

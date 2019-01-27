#ifndef DN_VECTOR4_HPP
# define DN_VECTOR4_HPP

# include "Vector.hpp"

namespace dn
{
	template <typename T>
	class Vector4: public dn::Vector<4, T>
	{
	public:
		Vector4(const T &p_scalar = T());
		Vector4(const std::initializer_list<T> &p_list);
		Vector4(const T &p_x, const T &p_y, const T &p_z, const T &p_w = T());
		template <dn::t_length Size2>
		Vector4(const dn::Vector<Size2, T> &p_vec);

		T x() const;
		T &x();
		T y() const;
		T &y();
		T z() const;
		T &z();
		T w() const;
		T &w();

		T r() const;
		T &r();
		T g() const;
		T &g();
		T b() const;
		T &b();
		T a() const;
		T &a();
	};

	typedef dn::Vector4<float> Vector4f;
	typedef dn::Vector4<double> Vector4d;
	typedef dn::Vector4<int> Vector4i;

	typedef Vector4f vec4f;
	typedef Vector4d vec4d;
	typedef Vector4i vec4i;
}

# include "Vector4.inl"

#endif // DN_VECTOR4_HPP

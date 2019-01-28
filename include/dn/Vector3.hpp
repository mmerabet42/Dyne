#ifndef DN_VECTOR3_HPP
# define DN_VECTOR3_HPP

# include "dn/Vector.hpp"

namespace dn
{
	template <typename T>
	class Vector3: public dn::Vector<3, T>
	{
	public:
		Vector3(const T &p_scalar = T());
		Vector3(const std::initializer_list<T> &p_list);
		Vector3(const T &p_x, const T &p_y, const T &p_z);
		template <dn::t_length Size2>
		Vector3(const dn::Vector<Size2, T> &p_vec);

		T x() const;
		T &x();
		T y() const;
		T &y();
		T z() const;
		T &z();

		T r() const;
		T &r();
		T g() const;
		T &g();
		T b() const;
		T &b();
	};

	typedef dn::Vector3<float> Vector3f;
	typedef dn::Vector3<double> Vector3d;
	typedef dn::Vector3<int> Vector3i;

	typedef Vector3f vec3f;
	typedef Vector3d vec3d;
	typedef Vector3i vec3i;
}

# include "dn/Vector3.inl"

#endif // DN_VECTOR3_HPP

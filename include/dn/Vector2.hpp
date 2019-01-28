#ifndef DN_VECTOR2_HPP
# define DN_VECTOR2_HPP

# include "dn/Vector.hpp"

namespace dn
{
	template <typename T>
	class Vector2: public dn::Vector<2, T>
	{
	public:
		Vector2(const T &p_scalar = T());
		Vector2(const std::initializer_list<T> &p_list);
		Vector2(const T &p_x, const T &p_y);
		template <dn::t_length Size2>
		Vector2(const dn::Vector<Size2, T> &p_vec);

		T x() const;
		T &x();
		T y() const;
		T &y();
	};

	typedef dn::Vector2<float> Vector2f;
	typedef dn::Vector2<double> Vector2d;
	typedef dn::Vector2<int> Vector2i;

	typedef Vector2f vec2f;
	typedef Vector2d vec2d;
	typedef Vector2i vec2i;
}

# include "dn/Vector2.inl"

#endif // DN_VECTOR2_HPP

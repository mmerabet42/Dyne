#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <initializer_list>

namespace dn
{
	typedef int t_length;

	template <dn::t_length Size, typename T>
	class Vector
	{
	public:
		Vector(const T &p_scalar = T());
		Vector(const std::initializer_list<T> &p_list);
		template <typename ... Args>
		Vector(Args ... p_args);
		template <dn::t_length Size2>
		Vector(const dn::Vector<Size2, T> &p_vec);

		T get(dn::t_length p_i) const;
		T &get(dn::t_length p_i);

		T length() const;
		T lengthSqrt() const;

		T operator[](dn::t_length p_i) const;
		T &operator[](dn::t_length p_i);

		dn::Vector<Size, T> &operator+=(const dn::Vector<Size, T> &p_vec);
		dn::Vector<Size, T> &operator-=(const dn::Vector<Size, T> &p_vec);
		dn::Vector<Size, T> &operator*=(const dn::Vector<Size, T> &p_vec);
		dn::Vector<Size, T> &operator/=(const dn::Vector<Size, T> &p_vec);

		dn::Vector<Size, T> &operator+=(const T &p_scalar);
		dn::Vector<Size, T> &operator-=(const T &p_scalar);
		dn::Vector<Size, T> &operator*=(const T &p_scalar);
		dn::Vector<Size, T> &operator/=(const T &p_scalar);
	private:
		T _data[Size];
	};

	template <dn::t_length Size, typename T>
	std::ostream &operator<<(std::ostream &p_stream, const dn::Vector<Size, T> &p_vec);

	template <dn::t_length Size, typename T>
	dn::Vector<Size, T> operator+(const dn::Vector<Size, T> &p_a, const dn::Vector<Size, T> &p_b);
	template <dn::t_length Size, typename T>
	dn::Vector<Size, T> operator-(const dn::Vector<Size, T> &p_a, const dn::Vector<Size, T> &p_b);
	template <dn::t_length Size, typename T>
	dn::Vector<Size, T> operator*(const dn::Vector<Size, T> &p_a, const dn::Vector<Size, T> &p_b);
	template <dn::t_length Size, typename T>
	dn::Vector<Size, T> operator/(const dn::Vector<Size, T> &p_a, const dn::Vector<Size, T> &p_b);

	template <dn::t_length Size, typename T, typename U>
	dn::Vector<Size, T> operator+(const U &p_scalar, dn::Vector<Size, T> p_vec);
	template <dn::t_length Size, typename T, typename U>
	dn::Vector<Size, T> operator-(const U &p_scalar, dn::Vector<Size, T> p_vec);
	template <dn::t_length Size, typename T, typename U>
	dn::Vector<Size, T> operator*(const U &p_scalar, dn::Vector<Size, T> p_vec);
	template <dn::t_length Size, typename T, typename U>
	dn::Vector<Size, T> operator/(const U &p_scalar, dn::Vector<Size, T> p_vec);

	template <dn::t_length Size, typename T, typename U>
	dn::Vector<Size, T> operator+(dn::Vector<Size, T> p_vec, const U &p_scalar);
	template <dn::t_length Size, typename T, typename U>
	dn::Vector<Size, T> operator-(dn::Vector<Size, T> p_vec, const U &p_scalar);
	template <dn::t_length Size, typename T, typename U>
	dn::Vector<Size, T> operator*(dn::Vector<Size, T> p_vec, const U &p_scalar);
	template <dn::t_length Size, typename T, typename U>
	dn::Vector<Size, T> operator/(dn::Vector<Size, T> p_vec, const U &p_scalar);

	template <dn::t_length Size, typename T>
	T dot(const dn::Vector<Size, T> &p_a, const dn::Vector<Size, T> &p_b);
	template <dn::t_length Size, typename T>
	dn::Vector<Size, T> normalize(dn::Vector<Size, T> p_vec);
	template <dn::t_length Size, typename T>
	T length(const dn::Vector<Size, T> &p_vec);
	template <dn::t_length Size, typename T>
	T lengthSqrt(const dn::Vector<Size, T> &p_vec);

	typedef dn::Vector<2, float> Vector2f;
	typedef dn::Vector<3, float> Vector3f;
	typedef dn::Vector<4, float> Vector4f;

	typedef Vector2f vec2;
	typedef Vector3f vec3;
	typedef Vector4f vec4;
}


# include "Vector.inl"

#endif // VECTOR_HPP

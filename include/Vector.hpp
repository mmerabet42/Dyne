#ifndef DN_VECTOR_HPP
# define DN_VECTOR_HPP

# include <iostream>
# include <initializer_list>
# include <type_traits>

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
		Vector(Args && ... p_args);
		template <dn::t_length Size2>
		Vector(const dn::Vector<Size2, T> &p_vec);

		template <typename ... Args>
		typename std::enable_if_t<(sizeof...(Args) == Size)>
		set(Args && ... p_args);

		T get(dn::t_length p_i) const;
		T &get(dn::t_length p_i);

		T operator[](dn::t_length p_i) const;
		T &operator[](dn::t_length p_i);

		T length() const;
		T lengthSqrt() const;

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

		template <typename Arg>
		void helper_set(size_t i, Arg && p_arg);
		template <typename Arg, typename ... Args>
		void helper_set(size_t i, Arg && p_arg, Args && ... p_args);
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
}


# include "Vector.inl"

#endif // DN_VECTOR_HPP

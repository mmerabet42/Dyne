#ifndef MATRIX_HPP
# define MATRIX_HPP

# include "Vector.hpp"
# include <iostream>

namespace dn
{
	typedef int t_length;

	template <dn::t_length Columns, dn::t_length Rows, typename T>
	class Matrix
	{
	public:
		Matrix(const T &p_identity = T());
		Matrix(const std::initializer_list<dn::Vector<Rows, T>> &p_list);
		Matrix(const std::initializer_list<std::initializer_list<T>> &p_list);
		template <dn::t_length Columns2, dn::t_length Rows2>
		Matrix(const dn::Matrix<Columns2, Rows2, T> &p_mat);

		dn::Vector<Rows, T> get(dn::t_length p_i) const;
		dn::Vector<Rows, T> &get(dn::t_length p_i);

		dn::Vector<Rows, T> operator[](dn::t_length p_i) const;
		dn::Vector<Rows, T> &operator[](dn::t_length p_i);

		dn::Matrix<Columns, Rows, T> &set(const T &p_scalar = T());

		dn::Matrix<Columns, Rows, T> &operator+=(const T &p_scalar);
		dn::Matrix<Columns, Rows, T> &operator-=(const T &p_scalar);
		dn::Matrix<Columns, Rows, T> &operator*=(const T &p_scalar);
		dn::Matrix<Columns, Rows, T> &operator/=(const T &p_scalar);

		dn::Matrix<Columns, Rows, T> &operator+=(const dn::Matrix<Columns, Rows, T> &p_mat);
		dn::Matrix<Columns, Rows, T> &operator-=(const dn::Matrix<Columns, Rows, T> &p_mat);
	private:
		dn::Vector<Rows, T> _columns[Columns];
	};

	template <dn::t_length Columns, dn::t_length Rows, typename T>
	std::ostream &operator<<(std::ostream &p_stream, const dn::Matrix<Columns, Rows, T> & p_mat);

	template <dn::t_length Columns, dn::t_length Rows, dn::t_length Size, typename T>
	dn::Matrix<Size, Rows, T> operator*(const dn::Matrix<Columns, Rows, T> &p_a, const dn::Matrix<Size, Columns, T> &p_b);

	template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
	dn::Matrix<Columns, Rows, T> operator+(dn::Matrix<Columns, Rows, T> p_mat, const U &p_scalar);
	template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
	dn::Matrix<Columns, Rows, T> operator-(dn::Matrix<Columns, Rows, T> p_mat, const U &p_scalar);
	template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
	dn::Matrix<Columns, Rows, T> operator*(dn::Matrix<Columns, Rows, T> p_mat, const U &p_scalar);
	template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
	dn::Matrix<Columns, Rows, T> operator/(dn::Matrix<Columns, Rows, T> p_mat, const U &p_scalar);

	template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
	dn::Matrix<Columns, Rows, T> operator+(const U &p_scalar, dn::Matrix<Columns, Rows, T> p_mat);
	template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
	dn::Matrix<Columns, Rows, T> operator-(const U &p_scalar, dn::Matrix<Columns, Rows, T> p_mat);
	template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
	dn::Matrix<Columns, Rows, T> operator*(const U &p_scalar, dn::Matrix<Columns, Rows, T> p_mat);
	template <dn::t_length Columns, dn::t_length Rows, typename T, typename U>
	dn::Matrix<Columns, Rows, T> operator/(const U &p_scalar, dn::Matrix<Columns, Rows, T> p_mat);

	typedef dn::Matrix<2, 2, float> Matrix2f;
	typedef dn::Matrix<3, 3, float> Matrix3f;
	typedef dn::Matrix<4, 4, float> Matrix4f;

	typedef dn::Matrix2f mat2;
	typedef dn::Matrix3f mat3;
	typedef dn::Matrix4f mat4;
}

# include "Matrix.inl"

#endif // MATRIX_HPP

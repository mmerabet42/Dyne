#ifndef MATRIX_HPP
# define MATRIX_HPP

# include "Vector.hpp"
# include <iostream>

namespace dn
{
	typedef int t_length;

	template <dn::t_length Rows, dn::t_length Columns, typename T>
	class Matrix
	{
	public:
		Matrix(const T &p_identity = T());
		Matrix(const std::initializer_list<dn::Vector<Rows, T>> &p_list);
		Matrix(const std::initializer_list<std::initializer_list<T>> &p_list);
		template <dn::t_length Rows2, dn::t_length Columns2>
		Matrix(const dn::Matrix<Rows2, Columns2, T> &p_mat);
		template <typename ... Args>
		Matrix(Args ... p_args);

		dn::Vector<Rows, T> get(dn::t_length p_i) const;
		dn::Vector<Rows, T> &get(dn::t_length p_i);

		dn::Vector<Rows, T> operator[](dn::t_length p_i) const;
		dn::Vector<Rows, T> &operator[](dn::t_length p_i);

		dn::Matrix<Rows, Columns, T> &set(const T &p_scalar = T());

		dn::Matrix<Rows, Columns, T> &operator+=(const T &p_scalar);
		dn::Matrix<Rows, Columns, T> &operator-=(const T &p_scalar);
		dn::Matrix<Rows, Columns, T> &operator*=(const T &p_scalar);
		dn::Matrix<Rows, Columns, T> &operator/=(const T &p_scalar);

		dn::Matrix<Rows, Columns, T> &operator+=(const dn::Matrix<Rows, Columns, T> &p_mat);
		dn::Matrix<Rows, Columns, T> &operator-=(const dn::Matrix<Rows, Columns, T> &p_mat);
	private:
		dn::Vector<Rows, T> _columns[Columns];
	};

	template <dn::t_length Rows, dn::t_length Columns, typename T>
	std::ostream &operator<<(std::ostream &p_stream, const dn::Matrix<Rows, Columns, T> & p_mat);

	template <dn::t_length Rows, dn::t_length Columns, dn::t_length Size, typename T>
	dn::Matrix<Rows, Size, T> operator*(const dn::Matrix<Rows, Columns, T> &p_a, const dn::Matrix<Columns, Size, T> &p_b);

	template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
	dn::Matrix<Rows, Columns, T> operator+(dn::Matrix<Rows, Columns, T> p_mat, const U &p_scalar);
	template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
	dn::Matrix<Rows, Columns, T> operator-(dn::Matrix<Rows, Columns, T> p_mat, const U &p_scalar);
	template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
	dn::Matrix<Rows, Columns, T> operator*(dn::Matrix<Rows, Columns, T> p_mat, const U &p_scalar);
	template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
	dn::Matrix<Rows, Columns, T> operator/(dn::Matrix<Rows, Columns, T> p_mat, const U &p_scalar);

	template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
	dn::Matrix<Rows, Columns, T> operator+(const U &p_scalar, dn::Matrix<Rows, Columns, T> p_mat);
	template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
	dn::Matrix<Rows, Columns, T> operator-(const U &p_scalar, dn::Matrix<Rows, Columns, T> p_mat);
	template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
	dn::Matrix<Rows, Columns, T> operator*(const U &p_scalar, dn::Matrix<Rows, Columns, T> p_mat);
	template <dn::t_length Rows, dn::t_length Columns, typename T, typename U>
	dn::Matrix<Rows, Columns, T> operator/(const U &p_scalar, dn::Matrix<Rows, Columns, T> p_mat);

	template <dn::t_length Rows, dn::t_length Columns, typename T>
	dn::Vector<Rows, T> operator*(const dn::Matrix<Rows, Columns, T> &p_mat, const dn::Vector<Columns, T> &p_vec);
	template <dn::t_length Rows, dn::t_length Columns, typename T>
	dn::Vector<Rows, T> operator*(const dn::Vector<Columns, T> &p_vec, const dn::Matrix<Rows, Columns, T> &p_mat);

	// 'a la Unity3D'
	template <dn::t_length Rows, dn::t_length Columns>
	using Matrixf = dn::Matrix<Rows, Columns, float>;

	typedef dn::Matrix<2, 2, float> Matrix2f;
	typedef dn::Matrix<3, 3, float> Matrix3f;
	typedef dn::Matrix<4, 4, float> Matrix4f;

	// 'a la glm'
	template <dn::t_length Rows, dn::t_length Columns>
	using matf = dn::Matrix<Rows, Columns, float>;

	typedef dn::Matrix<2, 2, float> mat2;
	typedef dn::Matrix<3, 3, float> mat3;
	typedef dn::Matrix<4, 4, float> mat4;
}

# include "Matrix.inl"

#endif // MATRIX_HPP

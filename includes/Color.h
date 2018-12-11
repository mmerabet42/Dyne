#ifndef COLOR_H
# define COLOR_H

namespace dn
{
	class Color
	{
	public:
		Color(const float &p_r, const float &p_g, const float &p_b, const float &p_a = 1.0f);
		Color(const int &p_r, const int &p_g, const int &p_b, const int &p_a = 255);

		void	set(const float &p_r, const float &p_g, const float &p_b, const float &p_a = 1.0f);
		void	set(const int &p_r, const int &p_g, const int &p_b, const int &p_a = 255);

		float	r() const;
		void	r(const float &p_r);
		void	r(const int &p_r);

		float	g() const;
		void	g(const float &p_g);
		void	g(const int &p_g);

		float	b() const;
		void	b(const float &p_b);
		void	b(const int &p_b);

		float	a() const;
		void	a(const float &p_a);
		void	a(const int &p_a);

	private:
		float	_r;
		float	_g;
		float	_b;
		float	_a;
	};
}

#endif

#ifndef COLOR_H
# define COLOR_H

namespace dn
{
	class Color
	{
	public:
		Color(const float &p_r, const float &p_g, const float &p_b, const float &p_a = 1.0f);

		void	set(const float &p_r, const float &p_g, const float &p_b, const float &p_a = 1.0f);
		
		float	r() const;
		void	r(const float &p_r);

		float	g() const;
		void	g(const float &p_g);

		float	b() const;
		void	b(const float &p_b);

		float	a() const;
		void	a(const float &p_a);

	private:
		float	_r;
		float	_g;
		float	_b;
		float	_a;
	};
}

#endif

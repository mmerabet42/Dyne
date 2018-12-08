#include "Color.h"

dn::Color::Color(const float &p_r, const float &p_g, const float &p_b, const float &p_a)
	: _r(p_r), _g(p_g), _b(p_b), _a(p_a)
{}

void	dn::Color::set(const float &p_r, const float &p_g, const float &p_b, const float &p_a)
{
	this->_r = p_r;
	this->_g = p_g;
	this->_b = p_b;
	this->_a = p_a;
}

float	dn::Color::r() const { return (this->_r); }
float	dn::Color::g() const { return (this->_g); }
float	dn::Color::b() const { return (this->_b); }
float	dn::Color::a() const { return (this->_a); }

void	dn::Color::r(const float &p_r) { this->_r = p_r; }
void	dn::Color::g(const float &p_g) { this->_g = p_g; }
void	dn::Color::b(const float &p_b) { this->_b = p_b; }
void	dn::Color::a(const float &p_a) { this->_a = p_a; }

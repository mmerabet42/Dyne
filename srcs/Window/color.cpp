#include "Color.h"

dn::Color::Color(const float &p_r, const float &p_g, const float &p_b, const float &p_a)
	: _r(p_r), _g(p_g), _b(p_b), _a(p_a)
{}
dn::Color::Color(const int &p_r, const int &p_g, const int &p_b, const int &p_a)
	: _r((float)p_r / 255.0f), _g((float)p_g / 255.0f), _b((float)p_b / 255.0f), _a((float)p_a / 255.0f)
{}

void	dn::Color::set(const float &p_r, const float &p_g, const float &p_b, const float &p_a)
{
	this->_r = p_r;
	this->_g = p_g;
	this->_b = p_b;
	this->_a = p_a;
}

void	dn::Color::set(const int &p_r, const int &p_g, const int &p_b, const int &p_a)
{
	this->_r = (float)p_r / 255.0f;
	this->_g = (float)p_g / 255.0f;
	this->_b = (float)p_b / 255.0f;
	this->_a = (float)p_a / 255.0f;
}

float	dn::Color::r() const { return (this->_r); }
float	dn::Color::g() const { return (this->_g); }
float	dn::Color::b() const { return (this->_b); }
float	dn::Color::a() const { return (this->_a); }

void	dn::Color::r(const float &p_r) { this->_r = p_r; }
void	dn::Color::g(const float &p_g) { this->_g = p_g; }
void	dn::Color::b(const float &p_b) { this->_b = p_b; }
void	dn::Color::a(const float &p_a) { this->_a = p_a; }

void	dn::Color::r(const int &p_r) { this->_r = (float)p_r / 255.0f; }
void	dn::Color::g(const int &p_g) { this->_g = (float)p_g / 255.0f; }
void	dn::Color::b(const int &p_b) { this->_b = (float)p_b / 255.0f; }
void	dn::Color::a(const int &p_a) { this->_a = (float)p_a / 255.0f; }

#include "Window.h"

/* Getters and setters */

int		dn::Window::width() const { return (this->_width); }
void	dn::Window::width(const int &p_width)
{
	if (p_width < 0)
		return ;
	this->_width = p_width;
	if (this->_glfw)
		glfwSetWindowSize(this->_glfw, this->_width, this->_height);
}

int		dn::Window::height() const { return (this->_height); }
void	dn::Window::height(const int &p_height)
{
	if (p_height < 0)
		return ;
	this->_height = p_height;
	if (this->_glfw)
		glfwSetWindowSize(this->_glfw, this->_width, this->_height);
}

void	dn::Window::setSize(const int &p_width, const int &p_height)
{
	if (p_width < 0 || p_height < 0)
		return ;
	this->_width = p_width;
	this->_height = p_height;
	if (this->_glfw)
		glfwSetWindowSize(this->_glfw, this->_width, this->_height);
}

int		dn::Window::x() const { return (this->_x); }
void	dn::Window::x(const int &p_x)
{
	if (p_x < 0)
		return ;
	this->_x = p_x;
	if (this->_glfw)
		glfwSetWindowPos(this->_glfw, this->_x, this->_y);
	else
		this->_flags |= DN_POS_SPECIFIED;
}

int		dn::Window::y() const { return (this->_y); }
void	dn::Window::y(const int &p_y)
{
	if (p_y < 0)
		return ;
	this->_y = p_y;
	if (this->_glfw)
		glfwSetWindowPos(this->_glfw, this->_x, this->_y);
	else
		this->_flags |= DN_POS_SPECIFIED;
}

void	dn::Window::setPos(const int &p_x, const int &p_y)
{
	if (p_x < 0 || p_y < 0)
		return ;
	this->_x = p_x;
	this->_y = p_y;
	if (this->_glfw)
		glfwSetWindowPos(this->_glfw, this->_x, this->_y);
	else
		this->_flags |= DN_POS_SPECIFIED;
}

std::string	dn::Window::title() const { return (this->_title); }
void		dn::Window::title(const std::string &p_title)
{
	this->_title = p_title;
	if (this->_glfw)
		glfwSetWindowTitle(this->_glfw, this->_title.c_str());
}

dn::Color	dn::Window::clearColor() const { return (this->_clearColor); }
void		dn::Window::setClearColor(const float &p_r, const float &p_g, const float &p_b)
{
	this->_clearColor.set(p_r, p_g, p_b);
}

float		dn::Window::opacity() const { return (this->_opacity); }
void		dn::Window::setOpacity(const float &p_opacity)
{
	this->_opacity = p_opacity;
	if (this->_glfw)
		glfwSetWindowOpacity(this->_glfw, this->_opacity);
}

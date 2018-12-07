#include "Window.h"
#include "Application.h"
#include <iostream>

/* Constructors */

dn::Window::Window(const int &p_width, const int &p_height, const std::string &p_title)
	: _x(0), _y(0), _flags(0), _width(p_width), _height(p_height), _title(p_title), _glfw(nullptr),

	_keyCallback(nullptr), _startCallback(nullptr), _updateCallback(nullptr)
{
	this->_windowid = dn::Application::AddWindow(this);
}

dn::Window::Window(const int &p_x, const int &p_y, const int &p_width, const int &p_height, const std::string &p_title)
	: Window(p_width, p_height, p_title)
{
	this->_x = p_x;
	this->_y = p_y;
	this->_flags |= DN_POS_SPECIFIED;
}

void	dn::Window::Close()
{
	if (this->_glfw)
		glfwSetWindowShouldClose(this->_glfw, true);
}

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

void	dn::Window::SetSize(const int &p_width, const int &p_height)
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
}

int		dn::Window::y() const { return (this->_y); }
void	dn::Window::y(const int &p_y)
{
	if (p_y < 0)
		return ;
	this->_y = p_y;
	if (this->_glfw)
		glfwSetWindowPos(this->_glfw, this->_x, this->_y);
}

void	dn::Window::SetPos(const int &p_x, const int &p_y)
{
	if (p_x < 0 || p_y < 0)
		return ;
	this->_x = p_x;
	this->_y = p_y;
	if (this->_glfw)
		glfwSetWindowPos(this->_glfw, this->_x, this->_y);
}

std::string	dn::Window::title() const { return (this->_title); }
void		dn::Window::title(const std::string &p_title)
{
	this->_title = p_title;
	if (this->_glfw)
		glfwSetWindowTitle(this->_glfw, this->_title.c_str());
}

int			dn::Window::GetKey(const int &p_keycode) const
{
	return (glfwGetKey(this->_glfw, p_keycode));
}

int			dn::Window::flags() const { return (this->_flags); }

void	dn::Window::SetKeyCallback(void(*p_keyCallback)(dn::Window *, const int &, const int &))
{
	this->_keyCallback = p_keyCallback;
}

void	dn::Window::SetStartCallback(void(*p_startCallback)(dn::Window *))
{
	this->_startCallback = p_startCallback;
}

void	dn::Window::SetUpdateCallback(void(*p_updateCallback)(dn::Window *))
{
	this->_updateCallback = p_updateCallback;
}

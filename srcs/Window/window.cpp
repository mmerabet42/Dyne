#include "Window.h"
#include "Application.h"
#include <iostream>

/* Constructors */

dn::Window::Window(const int &p_width, const int &p_height, const std::string &p_title)
	: _x(0), _y(0), _width(p_width), _height(p_height), _title(p_title), _glfw(nullptr),
	_flags(DN_VISIBLE), _clearColor(1.f, 1.f, 1.f, 1.f),

	_keyCallback(nullptr), _startCallback(nullptr), _updateCallback(nullptr), _sizeCallback(nullptr),
	_posCallback(nullptr)
{
	this->_windowid = dn::Application::addWindow(this);
}

dn::Window::Window(const int &p_x, const int &p_y, const int &p_width, const int &p_height, const std::string &p_title)
	: Window(p_width, p_height, p_title)
{
	this->_x = p_x;
	this->_y = p_y;
	this->_flags |= DN_POS_SPECIFIED;
}

void	dn::Window::close()
{
	this->_flags |= DN_CLOSED;
	if (this->_glfw)
		glfwSetWindowShouldClose(this->_glfw, true);
}

void		dn::Window::iconify()
{
	this->_flags |= DN_ICONIFIED;
	if (this->_glfw)
		glfwIconifyWindow(this->_glfw);
}

void		dn::Window::restore()
{
	this->_flags &= ~DN_ICONIFIED;
	if (this->_glfw)
		glfwRestoreWindow(this->_glfw);
}

bool		dn::Window::iconified() const { return (this->_flags & DN_ICONIFIED); }
bool		dn::Window::visible() const { return (this->_flags & DN_VISIBLE); }

void		dn::Window::hide()
{
	this->_flags &= ~DN_VISIBLE;
	if (this->_glfw)
		glfwHideWindow(this->_glfw);
}

void		dn::Window::show()
{
	this->_flags |= DN_VISIBLE;
	if (this->_glfw)
		glfwShowWindow(this->_glfw);
}

int			dn::Window::getKey(const int &p_keycode) const
{
	return (glfwGetKey(this->_glfw, p_keycode));
}

int			dn::Window::flags() const { return (this->_flags); }

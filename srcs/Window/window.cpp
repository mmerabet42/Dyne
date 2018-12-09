#include "GL/glew.h"
#include "Window.h"
#include "Application.h"
#include <iostream>

/* Constructors */

dn::Window::Window(const int &p_width, const int &p_height, const std::string &p_title)
	: _x(0), _y(0), _width(p_width), _height(p_height), _title(p_title), _glfw(nullptr),
	_flags(DN_VISIBLE), _clearColor(1.f, 1.f, 1.f, 1.f), _opacity(1.f),

	_keyCb(nullptr), _startCb(nullptr), _updateCb(nullptr), _sizeCb(nullptr),
	_posCb(nullptr), _closeCb(nullptr), _focusCb(nullptr)
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

void	dn::Window::clear() const
{
	this->clear(this->_clearColor.r(), this->_clearColor.g(), this->_clearColor.b(), this->_clearColor.a());
}

void	dn::Window::clear(const float &p_r, const float &p_g, const float &p_b, const float &p_a) const
{
	if (this->_glfw)
	{
		glClearColor(p_r, p_g, p_b, p_a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void	dn::Window::close()
{
	this->_flags |= DN_CLOSED;
	if (this->_glfw)
		glfwSetWindowShouldClose(this->_glfw, true);
	dn::Application::windowCloseCallback(this->_glfw);
}

void	dn::Window::open()
{
	this->_flags &= ~DN_CLOSED;
	if (this->_glfw)
		glfwSetWindowShouldClose(this->_glfw, false);
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

bool		dn::Window::focused() const
{
	return (dn::Application::focusedWindow() == this);
}

void		dn::Window::focus()
{
	dn::Application::_focused = this;
	if (this->_glfw)
		glfwFocusWindow(this->_glfw);
}

int			dn::Window::getKey(const int &p_keycode) const
{
	return (glfwGetKey(this->_glfw, p_keycode));
}

int			dn::Window::flags() const { return (this->_flags); }

void		dn::Window::setFlag(const int &p_flag, const bool &p_set)
{
	if (p_set)
		this->_flags |= p_flag;
	else
		this->_flags &= ~p_flag;
}

bool		dn::Window::getFlag(const int &p_flag) const
{
	return (this->_flags & p_flag);
}

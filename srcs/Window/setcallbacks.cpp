#include "Window.h"

void	dn::Window::setStartCallback(void(*p_startCallback)(dn::Window *))
{
	this->_startCallback = p_startCallback;
}

void	dn::Window::setUpdateCallback(void(*p_updateCallback)(dn::Window *))
{
	this->_updateCallback = p_updateCallback;
}

void	dn::Window::setKeyCallback(void(*p_keyCallback)(dn::Window *, int, int))
{
	this->_keyCallback = p_keyCallback;
}

void	dn::Window::setSizeCallback(void(*p_sizeCallback)(dn::Window *, int, int))
{
	this->_sizeCallback = p_sizeCallback;
}

void	dn::Window::setPosCallback(void(*p_posCallback)(dn::Window *, int, int))
{
	this->_posCallback = p_posCallback;
}

void	dn::Window::setCloseCallback(void(*p_closeCallback)(dn::Window *))
{
	this->_closeCallback = p_closeCallback;
}

#include "Window.h"

void	dn::Window::setStartCallback(dn::startCallbackFunc p_startCallback)
{
	this->_startCallback = p_startCallback;
}

void	dn::Window::setUpdateCallback(dn::updateCallbackFunc p_updateCallback)
{
	this->_updateCallback = p_updateCallback;
}

void	dn::Window::setKeyCallback(dn::keyCallbackFunc p_keyCallback)
{
	this->_keyCallback = p_keyCallback;
}

void	dn::Window::setSizeCallback(dn::sizeCallbackFunc p_sizeCallback)
{
	this->_sizeCallback = p_sizeCallback;
}

void	dn::Window::setPosCallback(dn::posCallbackFunc p_posCallback)
{
	this->_posCallback = p_posCallback;
}

void	dn::Window::setCloseCallback(dn::closeCallbackFunc p_closeCallback)
{
	this->_closeCallback = p_closeCallback;
}

void	dn::Window::setFocusCallback(dn::focusCallbackFunc p_focusCallback)
{
	this->_focusCallback = p_focusCallback;
}

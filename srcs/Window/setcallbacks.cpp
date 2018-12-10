#include "Window.h"

/*
 * Setter for all the different callbacks.
*/

void	dn::Window::setStartCb(const dn::startFunc &p_callback)
{
	this->_startCb = p_callback;
}

void	dn::Window::setUpdateCb(const dn::updateFunc &p_callback)
{
	this->_updateCb = p_callback;
}

void	dn::Window::setKeyCb(const dn::keyFunc &p_callback)
{
	this->_keyCb = p_callback;
}

void	dn::Window::setSizeCb(const dn::sizeFunc &p_callback)
{
	this->_sizeCb = p_callback;
}

void	dn::Window::setPosCb(const dn::posFunc &p_callback)
{
	this->_posCb = p_callback;
}

void	dn::Window::setCloseCb(const dn::closeFunc &p_callback)
{
	this->_closeCb = p_callback;
}

void	dn::Window::setFocusCb(const dn::focusFunc &p_callback)
{
	this->_focusCb = p_callback;
}

void	dn::Window::setMaximizeCb(const dn::maximizeFunc &p_callback)
{
	this->_maximizeCb = p_callback;
}

void	dn::Window::setFramebufferSizeCb(const dn::framebufferSizeFunc &p_callback)
{
	this->_framebufferSizeCb = p_callback;
}

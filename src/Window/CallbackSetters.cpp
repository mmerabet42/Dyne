#include "dn/Window.hpp"

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

void	dn::Window::setKeyPressCb(const dn::keyPressFunc &p_callback)
{
	this->_keyPressCb = p_callback;
}

void	dn::Window::setKeyRepeatCb(const dn::keyRepeatFunc &p_callback)
{
	this->_keyRepeatCb = p_callback;
}

void	dn::Window::setKeyReleaseCb(const dn::keyReleaseFunc &p_callback)
{
	this->_keyReleaseCb = p_callback;
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

void	dn::Window::setRefreshCb(const dn::refreshFunc &p_callback)
{
	this->_refreshCb = p_callback;
}

void	dn::Window::setMouseButtonCb(const dn::mouseButtonFunc &p_callback)
{
	this->_mouseButtonCb = p_callback;
}

void	dn::Window::setMousePressCb(const dn::mousePressFunc &p_callback)
{
	this->_mousePressCb = p_callback;
}

void	dn::Window::setMouseRepeatCb(const dn::mouseRepeatFunc &p_callback)
{
	this->_mouseRepeatCb = p_callback;
}

void	dn::Window::setMouseReleaseCb(const dn::mouseReleaseFunc &p_callback)
{
	this->_mouseReleaseCb = p_callback;
}

void	dn::Window::setMouseMoveCb(const dn::mouseMoveFunc &p_callback)
{
	this->_mouseMoveCb = p_callback;
}

void	dn::Window::setMouseEnterCb(const dn::mouseEnterFunc &p_callback)
{
	this->_mouseEnterCb = p_callback;
}

void	dn::Window::setScrollCb(const dn::scrollFunc &p_callback)
{
	this->_scrollCb = p_callback;
}

void	dn::Window::setDropCb(const dn::dropFunc &p_callback)
{
	this->_dropCb = p_callback;
}

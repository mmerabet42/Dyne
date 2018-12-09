#include "Window.h"

void	dn::Window::setStartCb(dn::startCbFunc p_callback)
{
	this->_startCb = p_callback;
}

void	dn::Window::setUpdateCb(dn::updateCbFunc p_callback)
{
	this->_updateCb = p_callback;
}

void	dn::Window::setKeyCb(dn::keyCbFunc p_callback)
{
	this->_keyCb = p_callback;
}

void	dn::Window::setSizeCb(dn::sizeCbFunc p_callback)
{
	this->_sizeCb = p_callback;
}

void	dn::Window::setPosCb(dn::posCbFunc p_callback)
{
	this->_posCb = p_callback;
}

void	dn::Window::setCloseCb(dn::closeCbFunc p_callback)
{
	this->_closeCb = p_callback;
}

void	dn::Window::setFocusCb(dn::focusCbFunc p_callback)
{
	this->_focusCb = p_callback;
}

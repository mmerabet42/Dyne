#include "Application.h"
#include "Window.h"
#include <iostream>

void	dn::Application::windowKeyCallback(GLFWwindow *p_window, int p_keycode, int p_scancode, int p_action, int p_mods)
{
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win || !win->_keyCb)
		return ;
	win->_keyCb(win, p_keycode, p_action);
}

void	dn::Application::windowStartCallback(dn::Window *p_window)
{
	if (p_window->_startCb)
		p_window->_startCb(p_window);
}

void	dn::Application::windowUpdateCallback(dn::Window *p_window)
{
	if (p_window->_updateCb)
		p_window->_updateCb(p_window);
}

void	dn::Application::windowSizeCallback(GLFWwindow *p_window, int p_width, int p_height)
{
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	win->_width = p_width;
	win->_height = p_height;
	if (win->_sizeCb)
		win->_sizeCb(win, p_width, p_height);
}

void	dn::Application::windowPosCallback(GLFWwindow *p_window, int p_x, int p_y)
{
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	win->_x = p_x;
	win->_y = p_y;
	if (win->_posCb)
		win->_posCb(win, p_x, p_y);
}

void	dn::Application::windowCloseCallback(GLFWwindow *p_window)
{
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	if (win->_closeCb)
		win->_closeCb(win);
}

void	dn::Application::windowFocusCallback(GLFWwindow *p_window, int focused)
{
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	if (focused)
		dn::Application::_focused = win;
	else if (dn::Application::_focused == win)
		dn::Application::_focused = nullptr;
	if (win->_focusCb)
		win->_focusCb(win, focused);
}

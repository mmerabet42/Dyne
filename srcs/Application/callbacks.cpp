#include "Application.h"
#include "Window.h"
#include <iostream>

void	dn::Application::windowKeyCallback(GLFWwindow *p_window, int p_keycode, int p_scancode, int p_action, int p_mods)
{
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win || !win->_keyCallback)
		return ;
	win->_keyCallback(win, p_keycode, p_action);
}

void	dn::Application::windowStartCallback(dn::Window *p_window)
{
	if (p_window->_startCallback)
		p_window->_startCallback(p_window);
}

void	dn::Application::windowUpdateCallback(dn::Window *p_window)
{
	if (p_window->_updateCallback)
		p_window->_updateCallback(p_window);
}

void	dn::Application::windowSizeCallback(GLFWwindow *p_window, int p_width, int p_height)
{
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	win->_width = p_width;
	win->_height = p_height;
	if (win->_sizeCallback)
		win->_sizeCallback(win, p_width, p_height);
}

void	dn::Application::windowPosCallback(GLFWwindow *p_window, int p_x, int p_y)
{
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	win->_x = p_x;
	win->_y = p_y;
	if (win->_posCallback)
		win->_posCallback(win, p_x, p_y);
}

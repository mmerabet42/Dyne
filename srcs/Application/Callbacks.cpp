#include "Application.h"
#include "Window.h"
#include <iostream>

void	dn::Application::WindowKeyCallback(GLFWwindow *p_window, int p_keycode, int p_scancode, int p_action, int p_mods)
{
	dn::Window *win = dn::Application::_glfwWindows.at(p_window);
	if (!win || !win->_keyCallback)
		return ;
	win->_keyCallback(win, p_keycode, p_action);
}

void	dn::Application::WindowStartCallback(dn::Window *p_window)
{
	if (p_window->_startCallback)
		p_window->_startCallback(p_window);
}

void	dn::Application::WindowUpdateCallback(dn::Window *p_window)
{
	if (p_window->_updateCallback)
		p_window->_updateCallback(p_window);
}

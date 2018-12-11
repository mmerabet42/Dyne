#include "Application.h"
#include "Window.h"
#include <iostream>

void	dn::Application::windowStartCallback(dn::Window *p_window)
{
	/* Calling the appropriate callback */
	if (p_window->_startCb)
		p_window->_startCb(p_window);
}

void	dn::Application::windowUpdateCallback(dn::Window *p_window)
{
	/* Calling the appropriate callback */
	if (p_window->_updateCb)
		p_window->_updateCb(p_window);
}

void	dn::Application::windowKeyCallback(GLFWwindow *p_window, int p_keycode, int p_scancode, int p_action, int p_mods)
{
	/* This statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win || !win->_keyCb)
		return ;
	/* Calling the appropriate callback */
	win->_keyCb(win, p_keycode, p_action);
}

void	dn::Application::windowSizeCallback(GLFWwindow *p_window, int p_width, int p_height)
{
	// This statement will always evaluate to true, so it is not necessary to do it.
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	// Update the width and height of the window.
	win->_width = p_width;
	win->_height = p_height;
	// Calling the appropriate callback.
	if (win->_sizeCb)
		win->_sizeCb(win, p_width, p_height);
}

void	dn::Application::windowPosCallback(GLFWwindow *p_window, int p_x, int p_y)
{
	/* This statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* Update the X and Y positions of the window */
	win->_x = p_x;
	win->_y = p_y;
	/* Calling the appropriate callback */
	if (win->_posCb)
		win->_posCb(win, p_x, p_y);
}

void	dn::Application::windowCloseCallback(GLFWwindow *p_window)
{
	/* This statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* Calling the appropriate callback */
	if (win->_closeCb)
		win->_closeCb(win);
}

void	dn::Application::windowFocusCallback(GLFWwindow *p_window, int p_focused)
{
	/* This statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	if (p_focused)
		dn::Application::_focused = win;
	else if (dn::Application::_focused == win)
		dn::Application::_focused = nullptr;
	/* Calling the appropriate callback */
	if (win->_focusCb)
		win->_focusCb(win, p_focused);
}

void	dn::Application::windowMaximizeCallback(GLFWwindow *p_window, int p_maximized)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* update the dn_maximized flag of the window */
	if (p_maximized)
		win->setFlag(DN_MAXIMIZED, true);
	else
		win->setFlag(DN_MAXIMIZED, false);
	/* calling the appropriate callback */
	if (win->_maximizeCb)
		win->_maximizeCb(win, p_maximized);
}

void	dn::Application::windowFramebufferSizeCallback(GLFWwindow *p_window, int p_width, int p_height)
{
	/* This statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* Update the two framebufferSize's attributes of the window */
	win->_framebufferWidth = p_width;
	win->_framebufferHeight = p_height;
	/* Calling the appropriate callback */
	if (win->_framebufferSizeCb)
		win->_framebufferSizeCb(win, p_width, p_height);
}

void	dn::Application::windowRefreshCallback(GLFWwindow *p_window)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* calling the appropriate callback */
	if (win->_refreshCb)
		win->_refreshCb(win);
}

void	dn::Application::windowMouseButtonCallback(GLFWwindow *p_window, int p_button , int p_action, int p_mods)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* calling the appropriate callback */
	if (win->_mouseButtonCb)
		win->_mouseButtonCb(win, p_button, p_action, p_mods);
}

void	dn::Application::windowMouseMoveCallback(GLFWwindow *p_window, double p_x, double p_y)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* calling the appropriate callback */
	if (win->_mouseMoveCb)
		win->_mouseMoveCb(win, p_x, p_y);
}

void	dn::Application::windowMouseEnterCallback(GLFWwindow *p_window, int p_entered)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* calling the appropriate callback */
	if (win->_mouseEnterCb)
		win->_mouseEnterCb(win, p_entered);
}

void	dn::Application::windowScrollCallback(GLFWwindow *p_window, double p_x, double p_y)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* calling the appropriate callback */
	if (win->_scrollCb)
		win->_scrollCb(win, p_x, p_y);
}

void	dn::Application::windowDropCallback(GLFWwindow *p_window, int p_count, const char **p_paths)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* calling the appropriate callback */
	if (win->_dropCb)
		win->_dropCb(win, p_count, p_paths);
}

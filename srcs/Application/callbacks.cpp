#include "Application.hpp"
#include "Window.hpp"
#include "Scene.hpp"

void	dn::Application::windowStartCallback(dn::Window *p_window)
{
	/* Calling the appropriate callback */
	if (p_window->_startCb)
		p_window->_startCb(*p_window);
	if (!p_window->getFlag(DN_CLOSED))
		p_window->startEvent.trigger(*p_window);
	if (!p_window->getFlag(DN_CLOSED) && p_window->_scene)
		p_window->_scene->start();
}

void	dn::Application::windowUpdateCallback(dn::Window *p_window)
{
	/* Calling the appropriate callback */
	if (p_window->_updateCb)
		p_window->_updateCb(*p_window);
	if (!p_window->getFlag(DN_CLOSED))
		p_window->updateEvent.trigger(*p_window);
	if (!p_window->getFlag(DN_CLOSED) && p_window->_scene)
		p_window->_scene->update();
}

void	dn::Application::windowKeyCallback(GLFWwindow *p_window, int p_keycode, int p_scancode, int p_action, int p_mods)
{
	/* This statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	if (p_action == GLFW_PRESS)
		p_action = DN_PRESS;
	else if (p_action == GLFW_REPEAT)
		p_action = DN_REPEAT;
	else if (p_action == GLFW_RELEASE)
		p_action = DN_RELEASE;
	win->_keyLogger[p_keycode] = p_action;

	/* Calling the appropriate callback */
	if (win->_keyCb)
		win->_keyCb(*win, (dn::KeyCode)p_keycode, (dn::Action)p_action, (dn::Mod)p_mods);
	if (!win->getFlag(DN_CLOSED))
		win->keyEvent.trigger(*win, (dn::KeyCode)p_keycode, (dn::Action)p_action, (dn::Mod)p_mods);

	if (!win->getFlag(DN_CLOSED))
	{
		if (p_action == DN_PRESS && win->_keyPressCb)
			win->_keyPressCb(*win, (dn::KeyCode)p_keycode, (dn::Mod)p_mods);
		else if (p_action == DN_REPEAT && win->_keyRepeatCb)
			win->_keyRepeatCb(*win, (dn::KeyCode)p_keycode, (dn::Mod)p_mods);
		else if (p_action == DN_RELEASE && win->_keyReleaseCb)
			win->_keyReleaseCb(*win, (dn::KeyCode)p_keycode, (dn::Mod)p_mods);
	}
	if (!win->getFlag(DN_CLOSED))
	{
		if (p_action == DN_PRESS)
			win->keyPressEvent.trigger(*win, (dn::KeyCode)p_keycode, (dn::Mod)p_mods);
		else if (p_action == DN_REPEAT)
			win->keyRepeatEvent.trigger(*win, (dn::KeyCode)p_keycode, (dn::Mod)p_mods);
		else if (p_action == DN_RELEASE)
			win->keyReleaseEvent.trigger(*win, (dn::KeyCode)p_keycode, (dn::Mod)p_mods);
	}
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
		win->_sizeCb(*win, p_width, p_height);
	if (!win->getFlag(DN_CLOSED))
		win->sizeEvent.trigger(*win, p_width, p_height);
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
		win->_posCb(*win, p_x, p_y);
	if (!win->getFlag(DN_CLOSED))
		win->posEvent.trigger(*win, p_x, p_y);
}

void	dn::Application::windowCloseCallback(GLFWwindow *p_window)
{
	/* This statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* Calling the appropriate callback */
	if (win->_closeCb)
		win->_closeCb(*win);
	win->closeEvent.trigger(*win);
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
		win->_focusCb(*win, p_focused);
	if (!win->getFlag(DN_CLOSED))
		win->focusEvent.trigger(*win, p_focused);
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
		win->_maximizeCb(*win, p_maximized);
	if (!win->getFlag(DN_CLOSED))
		win->maximizeEvent.trigger(*win, p_maximized);
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
		win->_framebufferSizeCb(*win, p_width, p_height);
	if (!win->getFlag(DN_CLOSED))
		win->framebufferSizeEvent.trigger(*win, p_width, p_height);
}

void	dn::Application::windowRefreshCallback(GLFWwindow *p_window)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* calling the appropriate callback */
	if (win->_refreshCb)
		win->_refreshCb(*win);
	if (!win->getFlag(DN_CLOSED))
		win->refreshEvent.trigger(*win);
}

void	dn::Application::windowMouseButtonCallback(GLFWwindow *p_window, int p_button , int p_action, int p_mods)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	if (p_action == GLFW_PRESS)
		win->_mouseLogger[p_button] = DN_PRESS;
	else if (p_action == GLFW_REPEAT)
		win->_mouseLogger[p_button] = DN_REPEAT;
	else if (p_action == GLFW_RELEASE)
		win->_mouseLogger[p_button] = DN_RELEASE;
	/* calling the appropriate callback */
	if (win->_mouseButtonCb)
		win->_mouseButtonCb(*win, (dn::MouseButton)p_button, (dn::Action)p_action, (dn::Mod)p_mods);
	if (!win->getFlag(DN_CLOSED))
		win->mouseButtonEvent.trigger(*win, (dn::MouseButton)p_button, (dn::Action)p_action, (dn::Mod)p_mods);

	if (!win->getFlag(DN_CLOSED))
	{
		if (p_action == DN_PRESS && win->_mousePressCb)
			win->_mousePressCb(*win, (dn::MouseButton)p_button, (dn::Mod)p_mods);
		else if (p_action == DN_REPEAT && win->_mouseRepeatCb)
			win->_mouseRepeatCb(*win, (dn::MouseButton)p_button, (dn::Mod)p_mods);
		else if (p_action == DN_RELEASE && win->_mouseReleaseCb)
			win->_mouseReleaseCb(*win, (dn::MouseButton)p_button, (dn::Mod)p_mods);
	}
	if (!win->getFlag(DN_CLOSED))
	{
		if (p_action == DN_PRESS)
			win->mousePressEvent.trigger(*win, (dn::MouseButton)p_button, (dn::Mod)p_mods);
		else if (p_action == DN_REPEAT)
			win->mouseRepeatEvent.trigger(*win, (dn::MouseButton)p_button, (dn::Mod)p_mods);
		else if (p_action == DN_RELEASE)
			win->mouseReleaseEvent.trigger(*win, (dn::MouseButton)p_button, (dn::Mod)p_mods);
	}
}

void	dn::Application::windowMouseMoveCallback(GLFWwindow *p_window, double p_x, double p_y)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	win->_mousePos[2] = win->_mousePos[0] - p_x;
	win->_mousePos[3] = win->_mousePos[1] - p_y;
	win->_mousePos[0] = p_x;
	win->_mousePos[1] = p_y;
	/* calling the appropriate callback */
	if (win->_mouseMoveCb)
		win->_mouseMoveCb(*win, p_x, p_y);
	if (!win->getFlag(DN_CLOSED))
		win->mouseMoveEvent.trigger(*win, p_x, p_y);
}

void	dn::Application::windowMouseEnterCallback(GLFWwindow *p_window, int p_entered)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* calling the appropriate callback */
	if (win->_mouseEnterCb)
		win->_mouseEnterCb(*win, p_entered);
	if (!win->getFlag(DN_CLOSED))
		win->mouseEnterEvent.trigger(*win, p_entered);
}

void	dn::Application::windowScrollCallback(GLFWwindow *p_window, double p_x, double p_y)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	/* calling the appropriate callback */
	if (win->_scrollCb)
		win->_scrollCb(*win, p_x, p_y);
	if (!win->getFlag(DN_CLOSED))
		win->scrollEvent.trigger(*win, p_x, p_y);
}

void	dn::Application::windowDropCallback(GLFWwindow *p_window, int p_count, const char **p_paths)
{
	/* this statement will always evaluate to true, so it is not necessary to do it */
	dn::Window *win = dn::Application::getWindow(p_window);
	if (!win)
		return ;
	std::vector<std::string> paths(p_paths, p_paths + p_count);
	/* calling the appropriate callback */
	if (win->_dropCb)
		win->_dropCb(*win, paths);
	if (!win->getFlag(DN_CLOSED))
		win->dropEvent.trigger(*win, paths);
}

#include "Application.hpp"
#include "Window.hpp"
#include <algorithm>

dn::Window *dn::Application::getWindow(const size_t &p_index)
{
	if (p_index < dn::Application::_windows.size())
		return (dn::Application::_windows.at(p_index));
	return (nullptr);
}

// It just check if the window is still 'stored' in the application
dn::Window *dn::Application::getWindow(dn::Window *p_window)
{
	if (std::find(dn::Application::_windows.begin(), dn::Application::_windows.end(), p_window) != dn::Application::_windows.end())
		return (p_window);
	return (nullptr);
}

// Requests the DN window from GLFW window.
dn::Window	*dn::Application::getWindow(GLFWwindow *p_window)
{
	std::map<GLFWwindow *, dn::Window *>::iterator it = dn::Application::_glfwWindows.find(p_window);
	if (it == dn::Application::_glfwWindows.end())
		return (nullptr);
	return (it->second);
}

// This function is called by the dn::Window constructor,
// it simply adds the window to the application.
int	dn::Application::addWindow(dn::Window *p_window)
{
	// If the application is running, then we add the window to an other list
	// to not disturb the main loop, once all windows were updated 
	if (dn::Application::_running)
		dn::Application::_windowsQueue.push_back(p_window);
	else
		dn::Application::_windows.push_back(p_window);
	return (dn::Application::_windows.size());
}

void dn::Application::setContext(dn::Window *p_window, const bool &p_force)
{
	dn::Application::_context = p_window;
	if (dn::Application::_running)
		glfwMakeContextCurrent(p_window->_glfw);
}

// Creates a GLFW window.
int	dn::Application::createGLFWwindow(dn::Window *p_window)
{
	// Creates the GLFW window.
	p_window->_glfw = glfwCreateWindow(p_window->_width, p_window->_height, p_window->_title.c_str(), nullptr, nullptr);

	// If GLFW failed to create the window, an error is returned.
	if (!p_window->_glfw)
		return (DN_WINDOW_FAIL);
	glfwMakeContextCurrent(p_window->_glfw);
	dn::Application::_context = p_window;

	// If the position of the window has been specified before the application has started,
	// the GLFW window position is set.
	if (p_window->_flags & DN_POS_SPECIFIED)
	{
		glfwSetWindowPos(p_window->_glfw, p_window->_x, p_window->_y);
		p_window->_flags &= ~DN_POS_SPECIFIED;
	}
	// Otherwise if it has not been specified, the current position of the window
	// is set to the DN window.
	else
		glfwGetWindowPos(p_window->_glfw, &p_window->_x, &p_window->_y);
	// If the window has been iconified before the application has run,
	// the GLFW window is iconified.
	if (p_window->_flags & DN_ICONIFIED)
		p_window->iconify();
	// Same for the visibility.
	if (!(p_window->_flags & DN_VISIBLE))
		p_window->hide();
	// Lock of the mouse
	if (p_window->_flags & DN_MOUSELOCKED)
		p_window->setMouseLock(true);
	// Sets the opacity of the window.
	glfwSetWindowOpacity(p_window->_glfw, p_window->_opacity);
	glfwSetWindowSizeLimits(p_window->_glfw,
		p_window->_minwidth, p_window->_minheight,
		p_window->_maxwidth, p_window->_maxheight);
	glfwGetFramebufferSize(p_window->_glfw, &p_window->_framebufferWidth, &p_window->_framebufferHeight);
	glfwGetCursorPos(p_window->_glfw, &p_window->_mousePos[0], &p_window->_mousePos[1]);

	// Links all the callbacks to the application callbacks.
	glfwSetKeyCallback(p_window->_glfw, dn::Application::windowKeyCallback);
	glfwSetWindowSizeCallback(p_window->_glfw, dn::Application::windowSizeCallback);
	glfwSetWindowPosCallback(p_window->_glfw, dn::Application::windowPosCallback);
	glfwSetWindowCloseCallback(p_window->_glfw, dn::Application::windowCloseCallback);
	glfwSetWindowFocusCallback(p_window->_glfw, dn::Application::windowFocusCallback);
	glfwSetWindowMaximizeCallback(p_window->_glfw, dn::Application::windowMaximizeCallback);
	glfwSetFramebufferSizeCallback(p_window->_glfw, dn::Application::windowFramebufferSizeCallback);
	glfwSetWindowRefreshCallback(p_window->_glfw, dn::Application::windowRefreshCallback);
	glfwSetMouseButtonCallback(p_window->_glfw, dn::Application::windowMouseButtonCallback);
	glfwSetCursorPosCallback(p_window->_glfw, dn::Application::windowMouseMoveCallback);
	glfwSetCursorEnterCallback(p_window->_glfw, dn::Application::windowMouseEnterCallback);
	glfwSetScrollCallback(p_window->_glfw, dn::Application::windowScrollCallback);
	glfwSetDropCallback(p_window->_glfw, dn::Application::windowDropCallback);

	dn::Application::_glfwWindows.insert(std::make_pair(p_window->_glfw, p_window));
	dn::Application::_focused = p_window;

	return (DN_OK);
}

dn::Window	*dn::Application::focusedWindow() { return (dn::Application::_focused); }

void	dn::Application::destroyWindows()
{
	for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end();)
		dn::Application::destroyWindow(it);
	dn::Application::_glfwWindows.clear();
}

// Sets the next iterator of the window vector.
void	dn::Application::destroyWindow(std::vector<dn::Window * >::iterator &p_it)
{
	// Enables the DN_CLOSED flag of the window.
	(*p_it)->setFlag(DN_CLOSED, true);
	dn::Application::_glfwWindows.erase((*p_it)->_glfw);
	glfwDestroyWindow((*p_it)->_glfw);
	// If DN_APPLICATION_FREEWINDOWS_DEFINED is defined,
	// or if the DN_FREEATCLOSE flag of the window is enabled,
	// or if the DN_FREEWINDOWS flag of the application is enabled,
	// the window is freed.
	if ((*p_it)->getFlag(DN_FREEATCLOSE) || (dn::Application::_flags & DN_FREEWINDOWS))
		delete *p_it;
p_it = dn::Application::_windows.erase(p_it);
}

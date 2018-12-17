#include "Application.hpp"
#include "Window.hpp"
#include <algorithm>

// Returns if the run() function has already been called.
bool	dn::Application::running() { return (dn::Application::_running); }
int		dn::Application::run()
{
	// If the application is curently running, we stop the function at this point.
	if (dn::Application::_running)
		return (0);
	// If the application has been stopped before it has run, then DN_STOPPED is returned.
	else if (dn::Application::_stopped)
		return (dn::Application::destroyWindows(), DN_STOPPED);

	// If glfw failed to init, an error is returned.
	if (!glfwInit())
		return (DN_GLFW_FAIL);

	// Settings of some basic window hints.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	glfwWindowHint(GLFW_SAMPLES, 512);

	// Creating the GLFW windows.
	for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
		if (dn::Application::createGLFWwindow(*it) == DN_WINDOW_FAIL)
			return (dn::Application::destroyWindows(), DN_WINDOW_FAIL);

	// If glew failed to init, an error is returned.
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return (dn::Application::destroyWindows(), DN_GLEW_FAIL);

	// Settings of some basic OpenGL flags.
	glEnable(GL_DEPTH);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// At this point the application is running.
	dn::Application::_running = true;
	// Calling the start callback of the application.
	if (dn::Application::_startCallback)
		dn::Application::_startCallback();

	// Calling the start callback of each window.
	for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
	{
		if (dn::Application::_context != *it)
		{
			glfwMakeContextCurrent((*it)->_glfw);
			dn::Application::_context = *it;
		}
		dn::Application::windowStartCallback(*it);
	}

	// The main loop.
	while (dn::Application::_running)
	{
		glfwPollEvents();
		// Calling the update callback of the application.
		if (dn::Application::_updateCallback)
			dn::Application::_updateCallback();
		// Iterating through the windows using iterators.
		for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); dn::Application::_running && it != dn::Application::_windows.end();)
		{
			// Make the current context on the current window, if it is not already.
			if (dn::Application::_context != *it)
			{
				glfwMakeContextCurrent((*it)->_glfw);
				dn::Application::_context = *it;
			}

			// If the DN_AUTOCLEAR flag is enabled,
			// the application calls the clear function of the window automatically.
			if ((*it)->_flags & DN_AUTOCLEAR)
				(*it)->clear();

			// Updating application time and deltaTime
			double etime = glfwGetTime();
			dn::Application::_deltaTime = etime - dn::Application::_time;
			dn::Application::_time = etime;

			// Calling the update callback of the window.
			dn::Application::windowUpdateCallback(*it);
			glfwSwapBuffers((*it)->_glfw);
			// If the window should close, it is remove from the application
			if (glfwWindowShouldClose((*it)->_glfw))
				dn::Application::destroyWindow(it);
			else
				++it;
		}
		if (dn::Application::_windowsQueue.size() != 0)
		{
			for (std::vector<dn::Window *>::iterator it = dn::Application::_windowsQueue.begin(); it != dn::Application::_windowsQueue.end();)
			{
				dn::Application::_windows.push_back(*it);
				createGLFWwindow(*it);
				dn::Application::windowStartCallback(*it);
				it = dn::Application::_windowsQueue.erase(it);
			}
		}

		// If no more windows, the application stops.
		if (dn::Application::_windows.empty())
			dn::Application::_running = false;
	}
	// Once the main loop is done, we clean and free everything.
	dn::Application::destroyWindows();
	glfwTerminate();
	return (0);
}

void		dn::Application::stop()
{
	dn::Application::_running = false;
	dn::Application::_stopped = true;
	for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
		dn::Application::windowCloseCallback((*it)->_glfw);
}

int			dn::Application::terminate()
{
	dn::Application::destroyWindows();
	if (dn::Application::_running)
		glfwTerminate();
	dn::Application::_running = false;
	return (0);
}

// Function the DN window linked to the specified GLFW window.
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
	// Sets the opacity of the window.
	glfwSetWindowOpacity(p_window->_glfw, p_window->_opacity);
	glfwSetWindowSizeLimits(p_window->_glfw,
		p_window->_minwidth, p_window->_minheight,
		p_window->_maxwidth, p_window->_maxheight);
	glfwGetFramebufferSize(p_window->_glfw, &p_window->_framebufferWidth, &p_window->_framebufferHeight);

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

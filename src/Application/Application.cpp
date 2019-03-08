#include "dn/Application.hpp"
#include "dn/Window.hpp"

// Basically it returns if the run() function has already been called
bool	dn::Application::running() { return (dn::Application::_running); }
int		dn::Application::run()
{
	// If the application is curently running, nothing is done
	if (dn::Application::_running)
		return (0);
	// If the application has been stopped before it has run, then DN_STOPPED is returned.
	else if (dn::Application::_stopped)
		return (DN_APPLICATION_STOPPED);

	// We first need to initialize the GLFW API. If it failed, the function stops
	if (!glfwInit())
		return (DN_GLFW_FAIL);

	// Settings of some basic window hints.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	glfwWindowHint(GLFW_SAMPLES, 512);

	// Creating the GLFW window for each created window
	for (auto &&i_window : dn::Application::_windows)
		if (dn::Application::createGLFWwindow(i_window) == DN_WINDOW_FAIL)
			return (dn::Application::destroyWindows(), DN_WINDOW_FAIL);

	// GLEW also needs to be initialized. As above, if it failed, the funtion stops at this point
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		// By destroying all the windows first, then returning
		return (dn::Application::cleanup(), DN_GLEW_FAIL);

	// Settings of some basic OpenGL flags.
	glEnable(GL_DEPTH);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Opening sound device and creating context
	dn::Application::_alcDevice = alcOpenDevice(nullptr);
	dn::Application::_alcContext = alcCreateContext(dn::Application::_alcDevice, nullptr);

	alcMakeContextCurrent(dn::Application::_alcContext);

	dn::Application::createDependents();

	// Everything has been initialized at this point
	dn::Application::_running = true;
	dn::Application::_return  = DN_OK;
	// Calling the start callback of the application.
	if (dn::Application::_startCb)
		dn::Application::_startCb();

	// Calling the start callback of each window.
	for (auto &&i_window : dn::Application::_windows)
	{
		if (dn::Application::_context != i_window)
		{
			glfwMakeContextCurrent(i_window->_glfw);
			dn::Application::_context = i_window;
		}
		dn::Application::windowStartCallback(i_window);
	}

	// The legendary main loop
	while (dn::Application::_running)
	{
		// Polling the events
		glfwPollEvents();

		// Updating application time and deltaTime
		double etime = glfwGetTime();
		dn::Application::_deltaTime = etime - dn::Application::_time;
		dn::Application::_time = etime;

		// Calling the update callback of the application.
		if (dn::Application::_updateCb)
			dn::Application::_updateCb();
		// Iterating through the windows using iterators
		for (auto &&i_window = dn::Application::_windows.begin();
		     dn::Application::_running && i_window != dn::Application::_windows.end();)
		{
			// Make the current context on the current window, if it is not already.
			if (dn::Application::_context != *i_window)
			{
				glfwMakeContextCurrent((*i_window)->_glfw);
				dn::Application::_context = *i_window;
			}

			// If the DN_AUTOCLEAR flag is enabled,
			// the application calls the clear function of the window automatically.
			if ((*i_window)->_flags & DN_AUTOCLEAR)
				(*i_window)->clear();

			// Calling the update callback of the window.
			dn::Application::windowUpdateCallback(*i_window);
			glfwSwapBuffers((*i_window)->_glfw);
			// If the window should close, it is first removed from the application
			if (glfwWindowShouldClose((*i_window)->_glfw))
				dn::Application::destroyWindow(i_window);
			else
				++i_window;
		}
		// If a window has been created during the main loop, it is added to the windows they've all been updated
		if (dn::Application::_windowsQueue.size() != 0)
		{
			for (auto &&i_window = dn::Application::_windowsQueue.begin();
				 i_window != dn::Application::_windowsQueue.end();)
			{
				dn::Application::_windows.push_back(*i_window);
				createGLFWwindow(*i_window);
				dn::Application::windowStartCallback(*i_window);
				i_window = dn::Application::_windowsQueue.erase(i_window);
			}
		}

		// If no more windows, the application stops.
		if (dn::Application::_windows.empty())
			dn::Application::_running = false;
	}
	if (dn::Application::_exitCb)
		dn::Application::_exitCb();
	// Once the main loop is done, we clean and free everything.
	dn::Application::cleanup();
	return (dn::Application::_return);
}

void		dn::Application::stop()
{
	dn::Application::_running = false;
	dn::Application::_stopped = true;
	for (auto &&i_window : dn::Application::_windows)
		dn::Application::windowCloseCallback(i_window->_glfw);
}

int			dn::Application::terminate(const std::string &p_msg, const int &p_return)
{
	dn::Application::destroyWindows();
	if (dn::Application::_running)
		glfwTerminate();
	std::cout << p_msg << std::endl;
	dn::Application::_running = false;
	dn::Application::_return = p_return;
	return (0);
}

void dn::Application::cleanup()
{
	dn::Application::destroyWindows();
	dn::Application::destroyDependents();
	glfwTerminate();
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(dn::Application::_alcContext);
	alcCloseDevice(dn::Application::_alcDevice);
}

#include "Application.hpp"
#include "Window.hpp"

// Basically it returns if the run() function has already been called
bool	dn::Application::running() { return (dn::Application::_running); }
int		dn::Application::run()
{
	// If the application is curently running, nothing is done
	if (dn::Application::_running)
		return (0);
	// If the application has been stopped before it has run, then DN_STOPPED is returned.
	else if (dn::Application::_stopped)
		return (DN_STOPPED);

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
	for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
		if (dn::Application::createGLFWwindow(*it) == DN_WINDOW_FAIL)
			return (dn::Application::destroyWindows(), DN_WINDOW_FAIL);

	// GLEW also needs to be initialized. As above, if it failed, the funtion stops at this point
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
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

	// Creating audios
	dn::Application::createAudios();

	// Compiling the shaders, if a shader has failed to compile, the application stops
	if (dn::Application::compileShaders() == DN_SHADER_FAIL)
		return (dn::Application::cleanup(), DN_SHADER_FAIL);
	// Creating textures
	dn::Application::createTextures();

	// Everything has been initialized at this point
	dn::Application::_running = true;
	dn::Application::_return  = DN_OK;
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

			// Calling the update callback of the window.
			dn::Application::windowUpdateCallback(*it);
			glfwSwapBuffers((*it)->_glfw);
			// If the window should close, it is first removed from the application
			if (glfwWindowShouldClose((*it)->_glfw))
				dn::Application::destroyWindow(it);
			else
				++it;
		}
		// If a window has been created during the for loop above, it is stored
		// in the _windowsQueue list
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
	dn::Application::cleanup();
	return (dn::Application::_return);
}

void		dn::Application::stop()
{
	dn::Application::_running = false;
	dn::Application::_stopped = true;
	for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
		dn::Application::windowCloseCallback((*it)->_glfw);
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
	glfwTerminate();
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(dn::Application::_alcContext);
	alcCloseDevice(dn::Application::_alcDevice);
}

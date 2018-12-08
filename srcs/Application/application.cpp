#include "GL/glew.h"
#include "Application.h"
#include "Window.h"
#include <algorithm>
#include <iostream>

bool	dn::Application::running() { return (dn::Application::_running); }
int		dn::Application::run()
{
	/* If the application is already running, we return an error */
	if (dn::Application::_running)
		return (DN_ALRDY_RUNNING);

	/* If glfw failed to init, we return an error */
	if (!glfwInit())
		return (dn::Application::destroyWindows(), DN_GLFW_FAIL);

	/* Settings of defaults window hints */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	glfwWindowHint(GLFW_SAMPLES, 512);

	/* Creating the GLFWs windows */
	for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
		if (dn::Application::createGLFWwindow(*it) == DN_WINDOW_FAIL)
			return (dn::Application::destroyWindows(), DN_WINDOW_FAIL);

	/* If glew failed to init, we return an error */
	if (glewInit() != GLEW_OK)
		return (dn::Application::destroyWindows(), DN_GLEW_FAIL);

	/* Settings of default OpenGL variable */
	glEnable(GL_DEPTH);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	dn::Application::_running = true;
	/* Calling start callback of the application */
	if (dn::Application::_startCallback)
		dn::Application::_startCallback();

	/* Calling the start callback of each window */
	for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
		dn::Application::windowStartCallback(*it);

	/* The main loop */
	while (dn::Application::_running)
	{
		glfwPollEvents();
		/* Each window must be updated */
		for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end();)
		{
			/* Make the current context on the current window */
			if (dn::Application::_context != *it)
			{
				glfwMakeContextCurrent((*it)->_glfw);
				dn::Application::_context = *it;
			}

			/* Calling update callback of the application */
			if (dn::Application::_updateCallback)
				dn::Application::_updateCallback();
			/* Calling update callback of the current window */
			dn::Application::windowUpdateCallback(*it);
			glfwSwapBuffers((*it)->_glfw);
			/* If the window should close, we simply remove it from the application */
			if (glfwWindowShouldClose((*it)->_glfw))
			{
				dn::Application::_glfwWindows.erase((*it)->_glfw);
				glfwDestroyWindow((*it)->_glfw);
				delete *it;
				it = dn::Application::_windows.erase(it);
			}
			else
				++it;
		}
		/* If no more windows, the application stops */
		if (dn::Application::_windows.empty())
			dn::Application::_running = false;
	}

	glfwTerminate();
	return (0);
}

dn::Window	*dn::Application::getWindow(GLFWwindow *p_window)
{
	std::map<GLFWwindow *, dn::Window *>::iterator it = dn::Application::_glfwWindows.find(p_window);
	if (it == dn::Application::_glfwWindows.end())
		return (nullptr);
	return (it->second);
}

int	dn::Application::addWindow(dn::Window *p_window)
{
	dn::Application::_windows.push_back(p_window);
	return (dn::Application::_windows.size());
}

int	dn::Application::createGLFWwindow(dn::Window *p_window)
{
	std::cout << "Creating GLFW window : " << p_window->width() << ", " << p_window->height() << ", " << p_window->title() << std::endl;
	p_window->_glfw = glfwCreateWindow(p_window->width(), p_window->height(), p_window->title().c_str(), nullptr, nullptr);

	if (!p_window->_glfw)
		return (DN_WINDOW_FAIL);
	glfwMakeContextCurrent(p_window->_glfw);
	dn::Application::_context = p_window;

	if (p_window->_flags & DN_POS_SPECIFIED)
		glfwSetWindowPos(p_window->_glfw, p_window->_x, p_window->_y);
	else
		glfwGetWindowPos(p_window->_glfw, &p_window->_x, &p_window->_y);

	if (p_window->_flags & DN_ICONIFIED)
		p_window->iconify();
	if (!(p_window->_flags & DN_VISIBLE))
		p_window->hide();
	
	glfwSetKeyCallback(p_window->_glfw, dn::Application::windowKeyCallback);
	glfwSetWindowSizeCallback(p_window->_glfw, dn::Application::windowSizeCallback);
	glfwSetWindowPosCallback(p_window->_glfw, dn::Application::windowPosCallback);
	glfwSetWindowCloseCallback(p_window->_glfw, dn::Application::windowCloseCallback);
	glfwSetWindowFocusCallback(p_window->_glfw, dn::Application::windowFocusCallback);

	dn::Application::_glfwWindows.insert(std::make_pair(p_window->_glfw, p_window));
	dn::Application::_focused = p_window;

	return (DN_OK);
}

dn::Window	*dn::Application::focusedWindow() { return (dn::Application::_focused); }

/*
static void	dn::Application::DestroyWindow(dn::Window *&p_window)
{
	if (p_window->_glfw)
		glfwDestroyWindow(p_window->_glfw);
	if (del)
		delete p_window;
	p_window = nullptr;
}
*/

void	dn::Application::destroyWindows()
{
	
/*
	for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
	{
		if (it->_glfw)
			glfwDestroyWindow(it->_glfw);
		delete it;
	}
	dn::Application::_windows.clear();*/
}

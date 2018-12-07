#include "GL/glew.h"
#include "Application.h"
#include "Window.h"
#include <algorithm>
#include <iostream>

int	dn::Application::AddWindow(dn::Window *p_window)
{
	dn::Application::_windows.push_back(p_window);
	return (dn::Application::_windows.size());
}

int	dn::Application::CreateGLFWwindow(dn::Window *p_window)
{
	std::cout << "Creating GLFW window : " << p_window->width() << ", " << p_window->height() << ", " << p_window->title() << std::endl;
	p_window->_glfw = glfwCreateWindow(p_window->width(), p_window->height(), p_window->title().c_str(), nullptr, nullptr);

	if (!p_window->_glfw)
		return (DN_WINDOW_FAIL);
	glfwMakeContextCurrent(p_window->_glfw);

	if (p_window->_flags & DN_POS_SPECIFIED)
		glfwSetWindowPos(p_window->_glfw, p_window->_x, p_window->_y);
	else
		glfwGetWindowPos(p_window->_glfw, &p_window->_x, &p_window->_y);

	glfwSetKeyCallback(p_window->_glfw, dn::Application::WindowKeyCallback);

	dn::Application::_glfwWindows.insert(std::make_pair(p_window->_glfw, p_window));

	return (DN_OK);
}
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

void	dn::Application::DestroyWindows()
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

int		dn::Application::Run()
{
	/* If the application is already running, we return an error */
	if (dn::Application::_running)
		return (dn::Application::DestroyWindows(), DN_ALRDY_RUNNING);

	/* If glfw failed to init, we return an error */
	if (!glfwInit())
		return (dn::Application::DestroyWindows(), DN_GLFW_FAIL);

	/* Settings of defaults window hints */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	glfwWindowHint(GLFW_SAMPLES, 512);

	/* Creating the GLFWs windows */
	for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
		if (dn::Application::CreateGLFWwindow(*it) == DN_WINDOW_FAIL)
			return (dn::Application::DestroyWindows(), DN_WINDOW_FAIL);

	if (glewInit() != GLEW_OK)
		return (dn::Application::DestroyWindows(), DN_GLEW_FAIL);

	glEnable(GL_DEPTH);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	dn::Application::_running = true;

	for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
		dn::Application::WindowStartCallback(*it);

	while (dn::Application::_running)
	{
		glfwPollEvents();
		for (std::vector<dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end();)
		{
			glfwMakeContextCurrent((*it)->_glfw);

			glfwSwapBuffers((*it)->_glfw);
			dn::Application::WindowUpdateCallback(*it);
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
		if (dn::Application::_windows.empty())
			dn::Application::_running = false;
	}

	return (0);
}

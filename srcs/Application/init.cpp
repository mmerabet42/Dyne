#include "Application.hpp"
#include <algorithm>

std::vector<dn::Window *>				dn::Application::_windows;
std::vector<dn::Window *>				dn::Application::_windowsQueue;
std::map<GLFWwindow *, dn::Window *>	dn::Application::_glfwWindows;
std::vector<dn::Shader *>				dn::Application::_shaders;
std::vector<dn::Texture *>				dn::Application::_textures;

std::function<void()>					dn::Application::_startCallback;
std::function<void()>					dn::Application::_updateCallback;
std::function<void()>					dn::Application::_exitCallback;

dn::Window								*dn::Application::_context = nullptr;
dn::Window								*dn::Application::_focused = nullptr;
int										dn::Application::_flags = 0;
int										dn::Application::_return = DN_OK;
bool									dn::Application::_running = false;
bool									dn::Application::_stopped = false;
double									dn::Application::_time = 0;
double									dn::Application::_deltaTime = 0;

void dn::Application::setStartCb(const std::function<void()> &p_callback)
{
	dn::Application::_startCallback = p_callback;
}

void dn::Application::setUpdateCb(const std::function<void()> &p_callback)
{
	dn::Application::_updateCallback = p_callback;
}

void dn::Application::setExitCb(const std::function<void()> &p_callback)
{
	dn::Application::_exitCallback = p_callback;
}

void dn::Application::setFlag(const int &p_flag, const bool &p_set)
{
	if (p_set)
		dn::Application::_flags |= p_flag;
	else
		dn::Application::_flags &= ~p_flag;
}

bool dn::Application::getFlag(const int &p_flag)
{
	return (dn::Application::_flags & p_flag);
}

double dn::Application::time()
{
	return (dn::Application::_time);
}

double dn::Application::deltaTime()
{
	return (dn::Application::_deltaTime);
}

#include "Application.h"
#include <algorithm>

int										dn::Application::_flags = 0;
dn::Window								*dn::Application::_context = nullptr;
dn::Window								*dn::Application::_focused = nullptr;
std::vector<dn::Window *>				dn::Application::_windows;
std::map<GLFWwindow *, dn::Window *>	dn::Application::_glfwWindows;
bool									dn::Application::_running = false;
bool									dn::Application::_stopped = false;
std::function<void()>					dn::Application::_startCallback;
std::function<void()>					dn::Application::_updateCallback;
std::function<void()>					dn::Application::_exitCallback;

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

dn::Window *dn::Application::getWindow(const size_t &p_index)
{
	if (p_index < dn::Application::_windows.size())
		return (dn::Application::_windows.at(p_index));
	return (nullptr);
}

dn::Window *dn::Application::getWindow(dn::Window *p_window)
{
	if (std::find(dn::Application::_windows.begin(), dn::Application::_windows.end(), p_window) != dn::Application::_windows.end())
		return (p_window);
	return (nullptr);
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

#include "Application.h"

dn::Window								*dn::Application::_context = nullptr;
dn::Window								*dn::Application::_focused = nullptr;
std::vector<dn::Window *>				dn::Application::_windows;
std::map<GLFWwindow *, dn::Window *>	dn::Application::_glfwWindows;
bool									dn::Application::_running = false;
void									(*dn::Application::_startCallback)() = nullptr;
void									(*dn::Application::_updateCallback)() = nullptr;

void	dn::Application::onStart(void(*p_callback)())
{
	dn::Application::_startCallback = p_callback;
}

void	dn::Application::onUpdate(void(*p_callback)())
{
	dn::Application::_updateCallback = p_callback;
}

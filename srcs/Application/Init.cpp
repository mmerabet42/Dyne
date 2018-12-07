#include "Application.h"

std::vector<dn::Window *>				dn::Application::_windows;
std::map<GLFWwindow *, dn::Window *>	dn::Application::_glfwWindows;
bool									dn::Application::_running = false;

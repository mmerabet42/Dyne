#include "dn/Application.hpp"
#include <algorithm>

std::function<void()>					dn::Application::_startCb;
std::function<void()>					dn::Application::_updateCb;
std::function<void()>					dn::Application::_exitCb;

ALCdevice								*dn::Application::_alcDevice = nullptr;
ALCcontext								*dn::Application::_alcContext = nullptr;
int										dn::Application::_flags = 0;
int										dn::Application::_return = DN_OK;
bool									dn::Application::_running = false;
bool									dn::Application::_stopped = false;
double									dn::Application::_time = 0.0;
double									dn::Application::_deltaTime = 0.0;

void dn::Application::setStartCb(const std::function<void()> &p_callback)
{
	dn::Application::_startCb = p_callback;
}

void dn::Application::setUpdateCb(const std::function<void()> &p_callback)
{
	dn::Application::_updateCb = p_callback;
}

void dn::Application::setExitCb(const std::function<void()> &p_callback)
{
	dn::Application::_exitCb = p_callback;
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

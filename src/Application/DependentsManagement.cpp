#include "dn/Application.hpp"
#include "dn/ApplicationDependent.hpp"
#include <algorithm>

std::vector<dn::ApplicationDependent *> dn::Application::_dependents;

void dn::Application::addDependent(dn::ApplicationDependent *p_dependent)
{
	std::vector<dn::ApplicationDependent *>::iterator it = std::find(
		dn::Application::_dependents.begin(),
		dn::Application::_dependents.end(),
		p_dependent);
	if (it != dn::Application::_dependents.end())
		return ;
	dn::Application::_dependents.push_back(p_dependent);
	if (dn::Application::_running)
	{
		p_dependent->_created = true;
		p_dependent->create();
	}
}

void dn::Application::createDependents()
{
	for (auto i_dependent : dn::Application::_dependents)
	{
		i_dependent->_created = true;
		i_dependent->create();
	}
}

void dn::Application::destroyDependent(dn::ApplicationDependent *p_dependent)
{
	if (p_dependent->_destroyed)
		return ;
	if (p_dependent->_created)
	{
		p_dependent->_destroyed = true;
		p_dependent->_created = false;
		p_dependent->destroy();
	}
	else
	{
		p_dependent->_destroyed = true;
		std::vector<dn::ApplicationDependent *>::iterator it = std::find(
			dn::Application::_dependents.begin(),
			dn::Application::_dependents.end(),
			p_dependent);
		if (it != dn::Application::_dependents.end())
			dn::Application::_dependents.erase(it);
	}
}

void dn::Application::destroyDependents()
{
	for (auto i_dependent : dn::Application::_dependents)
		dn::Application::destroyDependent(i_dependent);
}

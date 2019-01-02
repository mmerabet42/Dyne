#include "Application.hpp"
#include "ApplicationDependent.hpp"

std::vector<dn::ApplicationDependent *> dn::Application::_dependents;

void dn::Application::addDependent(dn::ApplicationDependent *p_dependent)
{
	dn::Application::_dependents.push_back(p_dependent);
	if (dn::Application::_running)
		p_dependent->create();
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
	p_dependent->_destroyed = true;
	p_dependent->_created = false;
	p_dependent->destroy();
}

void dn::Application::destroyDependents()
{
	for (auto i_dependent : dn::Application::_dependents)
		dn::Application::destroyDependent(i_dependent);
}

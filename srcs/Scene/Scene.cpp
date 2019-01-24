#include "Scene.hpp"
#include <algorithm>

dn::Scene::Scene()
	: _objects(), _systems(), _started(false), _window(nullptr)
{

}

void dn::Scene::addObject(dn::Object &p_object)
{
	auto it = std::find_if(this->_objects.begin(), this->_objects.end(),
		[&p_object](dn::Object *p_o) {
			return (&p_object == p_o);
		});
	if (it != this->_objects.end())
		return ;
	this->_objects.push_back(&p_object);
	p_object.setScene(this);
	// the object is tested on each system
	std::map<size_t, dn::SystemBase<> *>::iterator system;
	for (system = this->_systems.begin(); system != this->_systems.end(); ++system)
		system->second->loadFilters(p_object);
}

void dn::Scene::start()
{
	this->_started = true;
	std::map<size_t, dn::SystemBase<> *>::iterator system;
	for (system = this->_systems.begin(); system != this->_systems.end(); ++system)
		system->second->onStart();
}

void dn::Scene::update()
{
	std::map<size_t, dn::SystemBase<> *>::iterator system;
	for (system = this->_systems.begin(); system != this->_systems.end(); ++system)
		system->second->onUpdate();
}

void dn::Scene::objectUpdated(dn::Object *p_object)
{
	std::map<size_t, dn::SystemBase<> *>::iterator system;
	for (system = this->_systems.begin(); system != this->_systems.end(); ++system)
		system->second->loadFilters(*p_object);
}

dn::Window *dn::Scene::window() const
{
	return (this->_window);
}

void dn::Scene::setWindow(dn::Window *p_window)
{
	this->_window = p_window;
}

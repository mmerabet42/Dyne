#include "dn/Scene.hpp"
#include "dn/Object.hpp"
#include <algorithm>

dn::Scene::Scene()
	: _objects(), _uobjects(), _engines(), _callbackReceivers(),
	_started(false), _window(nullptr)
{

}

dn::Scene::~Scene()
{
	for (auto &&engine: this->_engines)
		delete (engine.second);
}

void dn::Scene::addObject(dn::Object &p_object)
{
	auto it = std::find_if(this->_objects.begin(), this->_objects.end(),
		[&p_object](dn::Object *p_o) {
			return (&p_object == p_o);
		}
	);
	if (it != this->_objects.end())
		return ;
	this->_objects.push_back(&p_object);
	p_object.setScene(this);
	// the object is tested on each system
	this->updateEngines(&p_object);
	this->updateUObject(&p_object);
}

void dn::Scene::start()
{
	this->_started = true;

	for (auto &&uobject : this->_uobjects)
		uobject->start();

	for (auto &&engine : this->_engines)
		engine.second->onStart();

}

void dn::Scene::update()
{
	if (this->_uobjects.size() != 0)
	{
		for (auto &&uobject : this->_uobjects)
			uobject->update();
	}

	for (auto &&engine : this->_engines)
		engine.second->onUpdate();
}

void dn::Scene::updateEngines(dn::Object *p_object)
{
	for (auto &&engine : this->_engines)
		engine.second->loadFilters(*p_object);
}

void dn::Scene::updateUObject(dn::Object *p_object)
{
	if (p_object->mustBeUpdated())
		this->_uobjects.emplace_back(p_object);
	else
	{
		auto it = std::find(this->_uobjects.begin(), this->_uobjects.end(), p_object);
		if (it != this->_uobjects.end())
			this->_uobjects.erase(it);
	}
}

dn::Window *dn::Scene::window() const
{
	return (this->_window);
}

void dn::Scene::setWindow(dn::Window *p_window)
{
	if (this->_window)
	{
		for (auto &&engine : this->_engines)
			engine.second->onWindowUnlink(*this->_window);
	}
	if ((this->_window = p_window))
	{
		for (auto &&engine : this->_engines)
			engine.second->onWindowLink(*this->_window);
	}
}

std::vector<dn::CallbackReceiver *> &dn::Scene::callbackReceivers()
{
	return (this->_callbackReceivers);
}

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
	std::map<size_t, dn::EngineBase<> *>::iterator it;
	for (it = this->_engines.begin(); it != this->_engines.end(); ++it)
		delete (it->second);
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

	auto object = this->_objects.begin();
	for (; object != this->_objects.end(); ++object)
		(*object)->start();

	std::map<size_t, dn::EngineBase<> *>::iterator engine = this->_engines.begin();
	for (; engine != this->_engines.end(); ++engine)
		engine->second->onStart();

}

void dn::Scene::update()
{
	if (this->_uobjects.size() != 0)
	{
		auto object = this->_uobjects.begin();
		for (; object != this->_uobjects.end(); ++object)
			(*object)->update();
	}

	std::map<size_t, dn::EngineBase<> *>::iterator engine = this->_engines.begin();
	for (; engine != this->_engines.end(); ++engine)
		engine->second->onUpdate();
}

void dn::Scene::updateEngines(dn::Object *p_object)
{
	std::map<size_t, dn::EngineBase<> *>::iterator engine = this->_engines.begin();
	for (; engine != this->_engines.end(); ++engine)
		engine->second->loadFilters(*p_object);
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
		std::map<size_t, dn::EngineBase<> *>::iterator engine = this->_engines.begin();
		for (; engine != this->_engines.end(); ++engine)
			engine->second->onWindowUnlink(*this->_window);
	}
	if ((this->_window = p_window))
	{
		std::map<size_t, dn::EngineBase<> *>::iterator engine = this->_engines.begin();
		for (; engine != this->_engines.end(); ++engine)
			engine->second->onWindowLink(*this->_window);
	}
}

std::vector<dn::CallbackReceiver *> &dn::Scene::callbackReceivers()
{
	return (this->_callbackReceivers);
}

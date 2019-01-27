#include "Object.hpp"
#include "Component.hpp"
#include "Scene.hpp"

dn::Object::Object(const std::string &p_name)
	: _name(p_name), _ucomponents(), _components(),
	_running(false), _active(false), _scene(nullptr), _mustBeUpdated(false)
{

}

dn::Object::~Object()
{
	std::map<size_t, dn::UComponent *>::iterator it = this->_ucomponents.begin();
	for (; it != this->_ucomponents.end(); ++it)
		if (it->second)
			delete it->second;
	this->_ucomponents.clear();

	std::map<size_t, dn::Component *>::iterator data_it = this->_components.begin();
	for (; data_it != this->_components.end(); ++data_it)
		if (data_it->second)
			delete data_it->second;
	this->_components.clear();
}

std::string dn::Object::name() const { return (this->_name); }
void dn::Object::setName(const std::string &p_name) { this->_name = p_name; }

bool dn::Object::active() const { return (this->_active); }
void dn::Object::setActive(const bool &p_active) { this->_active = p_active; }

bool dn::Object::mustBeUpdated() const { return (this->_mustBeUpdated); }

dn::Scene *dn::Object::scene() const
{
	return (this->_scene);
}

void dn::Object::setScene(dn::Scene *p_scene)
{
	this->_scene = p_scene;
}

void dn::Object::componentUpdated()
{
	if (this->_scene)
		this->_scene->updateEngines(this);
}

void dn::Object::callUpdateScene()
{
	this->_scene->updateUObject(this);
}

void dn::Object::start()
{
	this->_running = true;
	std::map<size_t, dn::UComponent *>::iterator it = this->_ucomponents.begin();
	for (; it != this->_ucomponents.end(); ++it)
		if (it->second && it->second->active())
			it->second->start();
}

void dn::Object::update()
{
	// updating each attached components
	std::map<size_t, dn::UComponent *>::iterator it = this->_ucomponents.begin();
	for (; it != this->_ucomponents.end(); ++it)
		if (it->second && it->second->active())
			it->second->update();
}

dn::UComponent *dn::Object::getHashUComponent(const size_t &p_hash_code)
{
	std::map<size_t, dn::UComponent *>::iterator it = this->_ucomponents.find(p_hash_code);
	if (it != this->_ucomponents.end())
		return (it->second);
	return (nullptr);
}

dn::Component *dn::Object::getHashDComponent(const size_t &p_hash_code)
{
	std::map<size_t, dn::Component *>::iterator it = this->_components.find(p_hash_code);
	if (it != this->_components.end())
		return (it->second);
	return (nullptr);
}

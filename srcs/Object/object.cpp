#include "Object.hpp"
#include "Component.hpp"
#include "Scene.hpp"

dn::Object::Object(const std::string &p_name)
	: _name(p_name), _running(false), _active(true), _components(), _componentsData(), _scene(nullptr)
{

}

dn::Object::~Object()
{
	std::map<size_t, dn::Component *>::iterator it = this->_components.begin();
	for (; it != this->_components.end(); ++it)
		if (it->second)
			delete it->second;
	this->_components.clear();

	std::map<size_t, dn::ComponentData *>::iterator data_it = this->_componentsData.begin();
	for (; data_it != this->_componentsData.end(); ++data_it)
		if (data_it->second)
			delete data_it->second;
	this->_componentsData.clear();
}

std::string dn::Object::name() const { return (this->_name); }
void dn::Object::setName(const std::string &p_name) { this->_name = p_name; }

bool dn::Object::active() const { return (this->_active); }
void dn::Object::setActive(const bool &p_active) { this->_active = p_active; }

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
		this->_scene->objectUpdated(this);
}

void dn::Object::start()
{
	this->_running = true;
	for (std::map<size_t, dn::Component *>::iterator it = this->_components.begin(); it != this->_components.end(); ++it)
		if (it->second && it->second->active())
			it->second->start();
}

void dn::Object::update()
{
	// The object must have started first
	if (!this->_running)
		return ;
	// updating each attached components
	for (std::map<size_t, dn::Component *>::iterator it = this->_components.begin(); it != this->_components.end(); ++it)
		if (it->second && it->second->active())
			it->second->update();
}

dn::Component *dn::Object::getHashComponent(const size_t &p_hash_code)
{
	std::map<size_t, dn::Component *>::iterator it = this->_components.find(p_hash_code);
	if (it != this->_components.end())
		return (it->second);
	return (nullptr);
}

dn::ComponentData *dn::Object::getHashComponentData(const size_t &p_hash_code)
{
	std::map<size_t, dn::ComponentData *>::iterator it = this->_componentsData.find(p_hash_code);
	if (it != this->_componentsData.end())
		return (it->second);
	return (nullptr);
}

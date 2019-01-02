#include "Object.hpp"
#include "Component.hpp"

dn::Object::Object(const std::string &p_name)
	: _name(p_name), _running(false), _active(true)
{

}

dn::Object::~Object()
{
	for (std::map<size_t, dn::Component *>::iterator it = this->_components.begin(); it != this->_components.end(); ++it)
		if (it->second)
			delete it->second;
	this->_components.clear();
}

std::string dn::Object::name() const { return (this->_name); }
void dn::Object::setName(const std::string &p_name) { this->_name = p_name; }

bool dn::Object::active() const { return (this->_active); }
void dn::Object::setActive(const bool &p_active) { this->_active = p_active; }

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

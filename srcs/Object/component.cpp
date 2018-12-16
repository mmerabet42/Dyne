#include "Component.h"

dn::Component::Component(dn::Object *p_object, const std::string &p_name)
	: _object(p_object), _name(p_name), _active(true)
{

}

dn::Object *dn::Component::object() const
{
	return (this->_object);
}

void dn::Component::setObject(dn::Object *p_object)
{
	this->_object = p_object;
}

std::string dn::Component::name() const
{
	return (this->_name);
}

void dn::Component::setName(const std::string &p_name)
{
	this->_name = p_name;
}

bool dn::Component::active() const
{
	return (this->_active);
}

void dn::Component::setActive(const bool &p_active)
{
	this->_active = p_active;
}

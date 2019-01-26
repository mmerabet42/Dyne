#include "Component.hpp"
#include "Object.hpp"

dn::Component::Component()
	: _active(true), _object(nullptr)
{

}

dn::Component::~Component()
{

}

bool dn::Component::active() const
{
	return (this->_active);
}

void dn::Component::setActive(const bool &p_active)
{
	this->_active = p_active;
	if (this->_object)
		this->_object->componentUpdated();
}

dn::Object *dn::Component::object() const
{
	return (this->_object);
}

void dn::Component::setObject(dn::Object *p_object)
{
	this->_object = p_object;
}

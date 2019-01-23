#include "Component.hpp"
#include "Object.hpp"

dn::ComponentData::ComponentData()
	: _active(true), _object(nullptr)
{

}

dn::ComponentData::~ComponentData()
{

}

bool dn::ComponentData::active() const
{
	return (this->_active);
}

void dn::ComponentData::setActive(const bool &p_active)
{
	this->_active = p_active;
	if (this->_object)
		this->_object->componentUpdated();
}

dn::Object *dn::ComponentData::object() const
{
	return (this->_object);
}

void dn::ComponentData::setObject(dn::Object *p_object)
{
	this->_object = p_object;
}

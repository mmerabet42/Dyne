#include "Component.hpp"

dn::UComponent::UComponent(const std::string &p_name)
	: _object(nullptr), _name(p_name), _active(true)
{

}

dn::UComponent::~UComponent() {}

dn::Object *dn::UComponent::object() const
{
	return (this->_object);
}

void dn::UComponent::setObject(dn::Object *p_object)
{
	this->_object = p_object;
}

std::string dn::UComponent::name() const
{
	return (this->_name);
}

void dn::UComponent::setName(const std::string &p_name)
{
	this->_name = p_name;
}

bool dn::UComponent::active() const
{
	return (this->_active);
}

void dn::UComponent::setActive(const bool &p_active)
{
	this->_active = p_active;
}
